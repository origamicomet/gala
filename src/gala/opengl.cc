//===-- gala/opengl.cc ----------------------------------*- mode: C++11 -*-===//
//
//                              _____     _
//                             |   __|___| |___
//                             |  |  | .'| | .'|
//                             |_____|__,|_|__,|
//
//       This file is distributed under the terms described in LICENSE.
//
//===----------------------------------------------------------------------===//

#include "gala/opengl.h"

// TODO(mtwilliams): Add paranoid asserts to verify that resources are valid,
// the right type, and have actually been created.

#if GALA_ENABLE_OPENGL

#if GALA_PLATFORM == GALA_PLATFORM_WINDOWS
  #include "gala/wgl.h"

  // Decorator for dynamic imports.
  #define GL_ENTRY_POINT __stdcall

  // REFACTOR(mtwilliams): Into `gala/wgl.h`?
  typedef gala_wgl_context_t gala_ogl_context_t;

  // REFACTOR(mtwilliams): Into `gala/wgl.h`?
  #define gala_ogl_get_proc_address gala_wgl_get_proc_address
#endif

GALA_BEGIN_EXTERN_C

// Not superseded by any extension.
static const gala_bool_t *GALA_OGL_EXTENSION_NONE = NULL;

typedef enum gala_ogl_extension_type {
  // Extension is not required but is nice to have.
  GALA_OGL_EXTENSION_OPTIONAL = (1 << 0),
  // Extension is for debugging.
  GALA_OGL_EXTENSION_DEBUG    = (1 << 1)
} gala_ogl_extension_type_t;

typedef struct gala_ogl_extension {
  const char *name;
  gala_uint32_t type;
  const gala_bool_t *supersede;
  gala_bool_t *flag;
} gala_ogl_extension_t;

static gala_bool_t GL_KHR_debug = false;

// These extensions are only available for OpenGL ES?
// static gala_bool_t GL_EXT_debug_label = false;
// static gala_bool_t GL_EXT_debug_marker = false;

static gala_bool_t GL_ARB_direct_state_access = false;
static gala_bool_t GL_ARB_multi_bind = false;

static gala_bool_t GL_ARB_texture_storage = false;
static gala_bool_t GL_ARB_buffer_storage = false;

static gala_bool_t GL_ARB_sparse_texture = false;

static gala_bool_t GL_ARB_multi_draw_indirect = false;

static gala_bool_t GL_ARB_get_program_binary = false;

static gala_bool_t GL_EXT_framebuffer_multisample_blit_scaled = false;

static const gala_ogl_extension_t EXTENSIONS_OF_INTEREST[] = {
  //
  // Debugging
  //

  { "GL_KHR_debug", GALA_OGL_EXTENSION_DEBUG | GALA_OGL_EXTENSION_OPTIONAL, GALA_OGL_EXTENSION_NONE, &GL_KHR_debug },

  // TODO(mtwilliams): Fallback to these if the `KHR_debug` is not available.
  // { "GL_EXT_debug_label",  GALA_OGL_EXTENSION_DEBUG, &GL_EXT_debug_label },
  // { "GL_EXT_debug_marker", GALA_OGL_EXTENSION_DEBUG, &GL_EXT_debug_marker },

  // TODO(mtwilliams): Integrate with RenderDoc.
  // { "GL_EXT_debug_tool", ... },

  //
  // Optimizations
  //

  // Direct State Access lets us modify objects without having to bind them!
  // The result is a non-negligible performance impact. We fallback to the
  // traditional bind-to-edit model if not available.
  { "GL_ARB_direct_state_access", GALA_OGL_EXTENSION_OPTIONAL, GALA_OGL_EXTENSION_NONE, &GL_ARB_direct_state_access },

  // Multibind lets us bind and unbind multiple contiguous objects with one
  // command like Direct3D 11. We fallback to the traditional call-per-bind
  // model if not available.
  { "GL_ARB_multi_bind", GALA_OGL_EXTENSION_OPTIONAL, GALA_OGL_EXTENSION_NONE, &GL_ARB_multi_bind },

  // PERF(mtwilliams): Separate data format and data source? In practice this
  // won't provide much benefit as we'll be using a large buffers and
  // submitting draw calls using `ARB_multi_draw_indirect`.
  // { "GL_ARB_vertex_attrib_binding", GALA_OGL_EXTENSION_OPTIONAL, GALA_OGL_EXTENSION_NONE, &GL_ARB_vertex_attrib_binding },

  // Immutable storage provides many opportunities for optimization. Most
  // notably, persistent mapping.
  { "GL_ARB_texture_storage", GALA_OGL_EXTENSION_OPTIONAL, GALA_OGL_EXTENSION_NONE, &GL_ARB_texture_storage },
  { "GL_ARB_buffer_storage", GALA_OGL_EXTENSION_OPTIONAL, GALA_OGL_EXTENSION_NONE, &GL_ARB_buffer_storage },

  // TODO(mtwilliams): Bindless.
  // { "GL_ARB_bindless_texture", GALA_OGL_EXTENSION_OPTIONAL, GALA_OGL_EXTENSION_NONE },
  // { "GL_NV_vertex_buffer_unified_memory", GALA_OGL_EXTENSION_OPTIONAL, GALA_OGL_EXTENSION_NONE },
  // { "GL_NV_uniform_buffer_unified_memory", GALA_OGL_EXTENSION_OPTIONAL, GALA_OGL_EXTENSION_NONE },

  // Sparse textures provide many opportunities for high-level and low-level
  // optimizations.
  { "GL_ARB_sparse_texture", GALA_OGL_EXTENSION_OPTIONAL, GALA_OGL_EXTENSION_NONE, &GL_ARB_sparse_texture },

  // This is the bread and butter of our fast path. When paired with a large
  // persistently mapped buffer it drastically reduces the number of draw
  // calls we have to make.
   // https://www.khronos.org/opengl/wiki/Vertex_Rendering#Indirect_rendering
  { "GL_ARB_multi_draw_indirect", GALA_OGL_EXTENSION_OPTIONAL, GALA_OGL_EXTENSION_NONE, &GL_ARB_multi_draw_indirect },

  // Allows us to cache shaders to disk as a way to mitigate the impact of
  // shader compile times.
  { "GL_ARB_get_program_binary", GALA_OGL_EXTENSION_OPTIONAL, GALA_OGL_EXTENSION_NONE, &GL_ARB_get_program_binary },

  // Allows us to resolve and scale multisampled buffers without an
  // intermediate buffer. See `gala_ogl_present`.
  { "GL_EXT_framebuffer_multisample_blit_scaled", GALA_OGL_EXTENSION_OPTIONAL, GALA_OGL_EXTENSION_NONE, &GL_EXT_framebuffer_multisample_blit_scaled },

  //
  // Compatability
  //

  // We require `ARB_clip_control` to setup a sane coordinate system. Luckily
  // for us the extension was added to core, and more importantly Doom (2016)
  // uses it. Driver support reflects that.
  { "ARB_clip_control", 0, GALA_OGL_EXTENSION_NONE, NULL },

  // TODO(mtwilliams): Compute shaders.
  // { "GL_ARB_shader_storage_buffer_object", GALA_OGL_EXTENSION_OPTIONAL, GALA_OGL_EXTENSION_NONE },
};

static const gala_uint32_t NUM_EXTENSIONS_OF_INTEREST =
  sizeof(EXTENSIONS_OF_INTEREST) / sizeof(EXTENSIONS_OF_INTEREST[0]);

//
// General
//

#define GL_MAJOR_VERSION                  0x821B
#define GL_MINOR_VERSION                  0x821C

#define GL_EXTENSIONS                     0x1F03
#define GL_NUM_EXTENSIONS                 0x821D

#define GL_TRUE                           1
#define GL_FALSE                          0

#define GL_LOWER_LEFT                     0x8CA1
#define GL_UPPER_LEFT                     0x8CA2

#define GL_NEGATIVE_ONE_TO_ONE            0x935E
#define GL_ZERO_TO_ONE                    0x935F

#define GL_NONE                           0
#define GL_FRONT                          0x0404
#define GL_BACK                           0x0405
#define GL_FRONT_AND_BACK                 0x0408

//
// Types
//

#define GL_BYTE                           0x1400
#define GL_UNSIGNED_BYTE                  0x1401
#define GL_SHORT                          0x1402
#define GL_UNSIGNED_SHORT                 0x1403
#define GL_INT                            0x1404
#define GL_UNSIGNED_INT                   0x1405
#define GL_FLOAT                          0x1406
#define GL_DOUBLE                         0x140A

//
// Windings
//

#define GL_CW                             0x0900
#define GL_CCW                            0x0901

//
// Operations
//

#define GL_CLEAR                          0x1500
#define GL_AND                            0x1501
#define GL_AND_REVERSE                    0x1502
#define GL_COPY                           0x1503
#define GL_AND_INVERTED                   0x1504
#define GL_NOOP                           0x1505
#define GL_XOR                            0x1506
#define GL_OR                             0x1507
#define GL_NOR                            0x1508
#define GL_EQUIV                          0x1509
#define GL_INVERT                         0x150A
#define GL_OR_REVERSE                     0x150B
#define GL_COPY_INVERTED                  0x150C
#define GL_OR_INVERTED                    0x150D
#define GL_NAND                           0x150E
#define GL_SET                            0x150F

#define GL_KEEP                           0x1E00
#define GL_REPLACE                        0x1E01
#define GL_INCR                           0x1E02
#define GL_DECR                           0x1E03

//
// Comparisons
//

#define GL_NEVER                          0x0200
#define GL_LESS                           0x0201
#define GL_EQUAL                          0x0202
#define GL_LEQUAL                         0x0203
#define GL_GREATER                        0x0204
#define GL_NOTEQUAL                       0x0205
#define GL_GEQUAL                         0x0206
#define GL_ALWAYS                         0x0207

//
// Factors
//

#define GL_ZERO                           0x0000
#define GL_ONE                            0x0001
#define GL_SRC_COLOR                      0x0300
#define GL_ONE_MINUS_SRC_COLOR            0x0301
#define GL_SRC_ALPHA                      0x0302
#define GL_ONE_MINUS_SRC_ALPHA            0x0303
#define GL_DST_COLOR                      0x0306
#define GL_ONE_MINUS_DST_COLOR            0x0307
#define GL_DST_ALPHA                      0x0304
#define GL_ONE_MINUS_DST_ALPHA            0x0305

//
// Formats
//

#define GL_RED                            0x1903
#define GL_RG                             0x8227
#define GL_RGB                            0x1907
#define GL_RGBA                           0x1908

#define GL_DEPTH_COMPONENT                0x1902
#define GL_DEPTH_STENCIL                  0x84F9

#define GL_R8                             0x8229
#define GL_R16F                           0x822D
#define GL_R32F                           0x822E
#define GL_R8I                            0x8231
#define GL_R16I                           0x8233
#define GL_R32I                           0x8235
#define GL_R8UI                           0x8232
#define GL_R16UI                          0x8234
#define GL_R32UI                          0x8236
#define GL_RG8                            0x822B
#define GL_RG16F                          0x822F
#define GL_RG32F                          0x8230
#define GL_RG8I                           0x8237
#define GL_RG16I                          0x8239
#define GL_RG32I                          0x823B
#define GL_RG8UI                          0x8238
#define GL_RG16UI                         0x823A
#define GL_RG32UI                         0x823C
#define GL_RGB16F                         0x881B
#define GL_RGB32F                         0x8815
#define GL_RGB32I                         0x8D83
#define GL_RGB32UI                        0x8D71
#define GL_RGBA8                          0x8058
#define GL_RGBA16F                        0x881A
#define GL_RGBA32F                        0x8814
#define GL_RGBA8I                         0x8D8E
#define GL_RGBA16I                        0x8D88
#define GL_RGBA32I                        0x8D82
#define GL_RGBA8UI                        0x8D7C
#define GL_RGBA16UI                       0x8D76
#define GL_RGBA32UI                       0x8D70

#define GL_RGB8                           0x8051
#define GL_SRGB8                          0x8C41
#define GL_SRGB8_ALPHA8                   0x8C43

#define GL_DEPTH_COMPONENT16              0x81A5
#define GL_DEPTH_COMPONENT24              0x81A6
#define GL_DEPTH_COMPONENT32              0x81A7

#define GL_DEPTH24_STENCIL8               0x88F0

//
// Buffers
//

#define GL_ARRAY_BUFFER                   0x8892
#define GL_UNIFORM_BUFFER                 0x8A11

#define GL_MAP_READ_BIT                   0x0001
#define GL_MAP_WRITE_BIT                  0x0002
#define GL_MAP_INVALIDATE_RANGE_BIT       0x0004
#define GL_MAP_INVALIDATE_BUFFER_BIT      0x0008
#define GL_MAP_FLUSH_EXPLICIT_BIT         0x0010
#define GL_MAP_UNSYNCHRONIZED_BIT         0x0020
#define GL_MAP_PERSISTENT_BIT             0x0040
#define GL_MAP_COHERENT_BIT               0x0080

//
// Textures & Samplers
//

#define GL_TEXTURE_1D                     0x0DE0
#define GL_TEXTURE_2D                     0x0DE1
#define GL_TEXTURE_3D                     0x806F

#define GL_SAMPLER_1D                     0x8B5D
#define GL_SAMPLER_2D                     0x8B5E
#define GL_SAMPLER_3D                     0x8B5F

#define GL_TEXTURE_1D_ARRAY               0x8C18
#define GL_TEXTURE_2D_ARRAY               0x8C1A

#define GL_SAMPLER_1D_ARRAY               0x8DC0
#define GL_SAMPLER_2D_ARRAY               0x8DC1

#define GL_TEXTURE_MAG_FILTER             0x2800
#define GL_TEXTURE_MIN_FILTER             0x2801

#define GL_TEXTURE_WRAP_S                 0x2802
#define GL_TEXTURE_WRAP_T                 0x2803
#define GL_TEXTURE_WRAP_R                 0x8072

#define GL_TEXTURE_MAX_ANISOTROPY         0x84FE

//
// Filters
//

#define GL_NEAREST                        0x2600
#define GL_LINEAR                         0x2601
#define GL_NEAREST_MIPMAP_NEAREST         0x2700
#define GL_LINEAR_MIPMAP_NEAREST          0x2701
#define GL_NEAREST_MIPMAP_LINEAR          0x2702
#define GL_LINEAR_MIPMAP_LINEAR           0x2703

//
// Wrapping
//
#define GL_REPEAT                         0x2901
#define GL_MIRRORED_REPEAT                0x8370
#define GL_CLAMP_TO_EDGE                  0x812F
#define GL_CLAMP_TO_BORDER                0x812D

//
// Targets
//

#define GL_FRAMEBUFFER                    0x8D40
#define GL_READ_FRAMEBUFFER               0x8CA8
#define GL_DRAW_FRAMEBUFFER               0x8CA9

#define GL_COLOR_ATTACHMENT               0x8CE0
#define GL_DEPTH_ATTACHMENT               0x8D00
#define GL_STENCIL_ATTACHMENT             0x8D20
#define GL_DEPTH_STENCIL_ATTACHMENT       0x821A

#define GL_COLOR                          0x1800
#define GL_DEPTH                          0x1801
#define GL_STENCIL                        0x1802

#define GL_DEPTH_BUFFER_BIT               0x00000100
#define GL_STENCIL_BUFFER_BIT             0x00000400
#define GL_COLOR_BUFFER_BIT               0x00004000

#define GL_DRAW_BUFFER                    0x8825

// Topology
#define GL_POINTS                         0x0000
#define GL_LINES                          0x0001
#define GL_LINE_LOOP                      0x0002
#define GL_LINE_STRIP                     0x0003
#define GL_TRIANGLES                      0x0004
#define GL_TRIANGLE_STRIP                 0x0005
#define GL_TRIANGLE_FAN                   0x0006

//
// Imports
//

typedef void (GL_ENTRY_POINT *GLPUSHDEBUGGROUPPROC)(gala_uint32_t source, gala_uint32_t id, gala_uint32_t length, const char *label);
typedef void (GL_ENTRY_POINT *GLPOPDEBUGGROUPPROC)(void);

GLPUSHDEBUGGROUPPROC glPushDebugGroup;
GLPOPDEBUGGROUPPROC glPopDebugGroup;

typedef void (GL_ENTRY_POINT *GLOBJECTLABELPROC)(gala_uint32_t identifier, gala_uint32_t name, gala_uint32_t length, const char *label);

GLOBJECTLABELPROC glObjectLabel;

typedef void (GL_ENTRY_POINT *GLGETBOOLEANVPROC)(gala_uint32_t parameter, gala_bool_t *value);
typedef void (GL_ENTRY_POINT *GLGETINTEGERVPROC)(gala_uint32_t parameter, gala_int32_t *value);
typedef void (GL_ENTRY_POINT *GLGETINTEGER64VPROC)(gala_uint32_t parameter, gala_int64_t *value);
typedef void (GL_ENTRY_POINT *GLGETFLOATVPROC)(gala_uint32_t parameter, gala_float32_t *value);
typedef void (GL_ENTRY_POINT *GLGETDOUBLEVPROC)(gala_uint32_t parameter, gala_float64_t *value);
typedef const char *(GL_ENTRY_POINT *GLGETSTRINGPROC)(gala_uint32_t name);
typedef const char *(GL_ENTRY_POINT *GLGETSTRINGIPROC)(gala_uint32_t name, gala_uint32_t index);

GLGETBOOLEANVPROC glGetBooleanv;
GLGETINTEGERVPROC glGetIntegerv;
GLGETINTEGER64VPROC glGetInteger64v;
GLGETFLOATVPROC glGetFloatv;
GLGETDOUBLEVPROC glGetDoublev;
GLGETSTRINGPROC glGetString;
GLGETSTRINGIPROC glGetStringi;

typedef void (GL_ENTRY_POINT *GLENABLEPROC)(gala_uint32_t capability);
typedef void (GL_ENTRY_POINT *GLDISABLEPROC)(gala_uint32_t capability);

GLENABLEPROC  glEnable;
GLDISABLEPROC glDisable;

typedef void (GL_ENTRY_POINT *GLCLIPCONTROLPROC)(gala_uint32_t origin, gala_uint32_t depth);

GLCLIPCONTROLPROC glClipControl;

typedef void (GL_ENTRY_POINT *GLGENBUFFERSPROC)(gala_uint32_t n, gala_uint32_t *buffers);
typedef void (GL_ENTRY_POINT *GLGENTEXTURESPROC)(gala_uint32_t n, gala_uint32_t *textures);
typedef void (GL_ENTRY_POINT *GLGENSAMPLERSPROC)(gala_uint32_t n, gala_uint32_t *samplers);
typedef void (GL_ENTRY_POINT *GLGENFRAMEBUFFERSPROC)(gala_uint32_t n, gala_uint32_t *framebuffers);

GLGENBUFFERSPROC glGenBuffers;
GLGENTEXTURESPROC glGenTextures;
GLGENSAMPLERSPROC glGenSamplers;
GLGENFRAMEBUFFERSPROC glGenFramebuffers;

typedef void (GL_ENTRY_POINT *GLDELETEBUFFERSPROC)(gala_uint32_t n, const gala_uint32_t *buffers);
typedef void (GL_ENTRY_POINT *GLDELETETEXTURESPROC)(gala_uint32_t n, const gala_uint32_t *textures);
typedef void (GL_ENTRY_POINT *GLDELETESAMPLERSPROC)(gala_uint32_t n, const gala_uint32_t *samplers);
typedef void (GL_ENTRY_POINT *GLDELETEFRAMEBUFFERSPROC)(gala_uint32_t n, const gala_uint32_t *framebuffers);

GLDELETEBUFFERSPROC glDeleteBuffers;
GLDELETETEXTURESPROC glDeleteTextures;
GLDELETESAMPLERSPROC glDeleteSamplers;
GLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers;

// TODO(mtwilliams): Generate vertex array objects for each input layout.
 // https://www.khronos.org/opengl/wiki/Vertex_Specification#Vertex_format
typedef void (GL_ENTRY_POINT *GLGENVERTEXARRAYSPROC)(gala_uint32_t n, gala_uint32_t *arrays);
typedef void (GL_ENTRY_POINT *GLDELETEVERTEXARRAYSPROC)(gala_uint32_t n, const gala_uint32_t *arrays);
typedef void (GL_ENTRY_POINT *GLBINDVERTEXARRAYPROC)(gala_uint32_t array);

GLGENVERTEXARRAYSPROC glGenVertexArrays;
GLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
GLBINDVERTEXARRAYPROC glBindVertexArray;

typedef void (GL_ENTRY_POINT *GLVIEWPORTPROC)(gala_int32_t x, gala_int32_t y, gala_int32_t w, gala_int32_t h);
typedef void (GL_ENTRY_POINT *GLSCISSORPROC)(gala_int32_t x, gala_int32_t y, gala_int32_t w, gala_int32_t h);

GLVIEWPORTPROC glViewport;
GLSCISSORPROC  glScissor;

typedef void (GL_ENTRY_POINT *GLBINDBUFFERPROC)(gala_uint32_t target, gala_uint32_t buffer);

GLBINDBUFFERPROC glBindBuffer;

typedef void (GL_ENTRY_POINT *GLBINDTEXTUREPROC)(gala_uint32_t target, gala_uint32_t texture);
typedef void (GL_ENTRY_POINT *GLBINDSAMPLERPROC)(gala_uint32_t unit, gala_uint32_t sampler);

GLBINDTEXTUREPROC glBindTexture;

typedef void (GL_ENTRY_POINT *GLTEXIMAGE1DPROC)(gala_uint32_t target,
                                                gala_uint32_t level,
                                                gala_uint32_t internal_format,
                                                gala_uint32_t width,
                                                gala_uint32_t border,
                                                gala_uint32_t format,
                                                gala_uint32_t type,
                                                const void *data);

typedef void (GL_ENTRY_POINT *GLTEXIMAGE2DPROC)(gala_uint32_t target,
                                                gala_uint32_t level,
                                                gala_uint32_t internal_format,
                                                gala_uint32_t width,
                                                gala_uint32_t height,
                                                gala_uint32_t border,
                                                gala_uint32_t format,
                                                gala_uint32_t type,
                                                const void *data);

typedef void (GL_ENTRY_POINT *GLTEXIMAGE3DPROC)(gala_uint32_t target,
                                                gala_uint32_t level,
                                                gala_uint32_t internal_format,
                                                gala_uint32_t width,
                                                gala_uint32_t height,
                                                gala_uint32_t depth,
                                                gala_uint32_t border,
                                                gala_uint32_t format,
                                                gala_uint32_t type,
                                                const void *data);

GLTEXIMAGE1DPROC glTexImage1D;
GLTEXIMAGE2DPROC glTexImage2D;
GLTEXIMAGE3DPROC glTexImage3D;

typedef void (GL_ENTRY_POINT *GLTEXPARAMETERFPROC)(gala_uint32_t target, gala_uint32_t name, gala_float32_t value);
typedef void (GL_ENTRY_POINT *GLTEXPARAMETERIPROC)(gala_uint32_t target, gala_uint32_t name, gala_int32_t value);

GLTEXPARAMETERFPROC glTexParameterf;
GLTEXPARAMETERIPROC glTexParameteri;

typedef void (GL_ENTRY_POINT *GLGENERATEMIPMAPPROC)(gala_uint32_t target);

GLGENERATEMIPMAPPROC glGenerateMipmap;

GLBINDSAMPLERPROC glBindSampler;

typedef void (GL_ENTRY_POINT *GLSAMPLERPARAMETERFPROC)(gala_uint32_t sampler, gala_uint32_t name, gala_float32_t value);
typedef void (GL_ENTRY_POINT *GLSAMPLERPARAMETERIPROC)(gala_uint32_t sampler, gala_uint32_t name, gala_int32_t value);

GLSAMPLERPARAMETERFPROC glSamplerParameterf;
GLSAMPLERPARAMETERIPROC glSamplerParameteri;

typedef void (GL_ENTRY_POINT *GLBINDFRAMEBUFFERPROC)(gala_uint32_t target, gala_uint32_t framebuffer);

GLBINDFRAMEBUFFERPROC glBindFramebuffer;

typedef void (GL_ENTRY_POINT *GLFRAMEBUFFERTEXTURE1DPROC)(gala_uint32_t target,
                                                          gala_uint32_t attachment,
                                                          gala_uint32_t textarget,
                                                          gala_uint32_t texture,
                                                          gala_uint32_t level);

typedef void (GL_ENTRY_POINT *GLFRAMEBUFFERTEXTURE2DPROC)(gala_uint32_t target,
                                                          gala_uint32_t attachment,
                                                          gala_uint32_t textarget,
                                                          gala_uint32_t texture,
                                                          gala_uint32_t level);

typedef void (GL_ENTRY_POINT *GLFRAMEBUFFERTEXTURE3DPROC)(gala_uint32_t target,
                                                          gala_uint32_t attachment,
                                                          gala_uint32_t textarget,
                                                          gala_uint32_t texture,
                                                          gala_uint32_t level,
                                                          gala_uint32_t layer);

GLFRAMEBUFFERTEXTURE1DPROC glFramebufferTexture1D;
GLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D;
GLFRAMEBUFFERTEXTURE3DPROC glFramebufferTexture3D;

typedef void (GL_ENTRY_POINT *GLDRAWBUFFERPROC)(gala_uint32_t buffer);
typedef void (GL_ENTRY_POINT *GLDRAWBUFFERSPROC)(gala_uint32_t n, const gala_uint32_t *buffers);

GLDRAWBUFFERPROC glDrawBuffer;
GLDRAWBUFFERSPROC glDrawBuffers;

typedef void (GL_ENTRY_POINT *GLCLEARBUFFERIVPROC)(gala_uint32_t buffer, gala_uint32_t draw_buffer, const gala_int32_t *value);
typedef void (GL_ENTRY_POINT *GLCLEARBUFFERUIVPROC)(gala_uint32_t buffer, gala_uint32_t draw_buffer, const gala_uint32_t *value);
typedef void (GL_ENTRY_POINT *GLCLEARBUFFERFVPROC)(gala_uint32_t buffer, gala_uint32_t draw_buffer, const gala_float32_t *value);

GLCLEARBUFFERIVPROC  glClearBufferiv;
GLCLEARBUFFERUIVPROC glClearBufferuiv;
GLCLEARBUFFERFVPROC  glClearBufferfv;

typedef void (GL_ENTRY_POINT *GLBLITFRAMEBUFFERPROC)(gala_int32_t src_x0,
                                                     gala_int32_t src_y0,
                                                     gala_int32_t src_x1,
                                                     gala_int32_t src_y1,
                                                     gala_int32_t dst_x0,
                                                     gala_int32_t dst_y0,
                                                     gala_int32_t dst_x1,
                                                     gala_int32_t dst_y1,
                                                     gala_uint32_t mask,
                                                     gala_uint32_t filter);

GLBLITFRAMEBUFFERPROC glBlitFramebuffer;

typedef void (GL_ENTRY_POINT *GLFLUSHPROC)(void);
typedef void (GL_ENTRY_POINT *GLFINISHPROC)(void);

GLFLUSHPROC  glFlush;
GLFINISHPROC glFinish;

static void gala_ogl_check_for_extensions(void)
{
  gala_int32_t n = 0;
  glGetIntegerv(GL_NUM_EXTENSIONS, &n);

  gala_bool_t availability[NUM_EXTENSIONS_OF_INTEREST] = { false, };

  for (gala_uint32_t advertised = 0; advertised < n; ++advertised) {
    const char *name = (const char *)glGetStringi(GL_EXTENSIONS, advertised);
    for (gala_uint32_t extension = 0; extension < NUM_EXTENSIONS_OF_INTEREST; ++extension)
      if (strcmp(EXTENSIONS_OF_INTEREST[extension].name, name) == 0)
        availability[extension] = true;
  }

  for (gala_uint32_t index = 0; index < NUM_EXTENSIONS_OF_INTEREST; ++index) {
    const gala_ogl_extension_t *extension = &EXTENSIONS_OF_INTEREST[index];

    const gala_bool_t available = availability[index];
    const gala_bool_t required  = !(extension->type & GALA_OGL_EXTENSION_OPTIONAL);
    const gala_bool_t superseded = (extension->supersede ? *(extension->supersede) : false);

    if (available)
      if (extension->flag)
        *extension->flag = true;

    if (required)
      gala_assertf(!superseded && !available, "Required extension `%s` is not available!", extension->name);
  }
}

static void gala_ogl_wrangle(void)
{
  static gala_bool_t wrangled = false;

  if (wrangled)
    return;

  wrangled = true;

  glGetBooleanv = (GLGETBOOLEANVPROC)gala_ogl_get_proc_address("glGetBooleanv");
  glGetIntegerv = (GLGETINTEGERVPROC)gala_ogl_get_proc_address("glGetIntegerv");
  glGetInteger64v = (GLGETINTEGER64VPROC)gala_ogl_get_proc_address("glGetInteger64v");
  glGetFloatv = (GLGETFLOATVPROC)gala_ogl_get_proc_address("glGetFloatv");
  glGetDoublev = (GLGETDOUBLEVPROC)gala_ogl_get_proc_address("glGetDoublev");
  glGetString = (GLGETSTRINGPROC)gala_ogl_get_proc_address("glGetString");
  glGetStringi = (GLGETSTRINGIPROC)gala_ogl_get_proc_address("glGetStringi");

  glEnable = (GLENABLEPROC)gala_ogl_get_proc_address("glEnable");
  glDisable = (GLDISABLEPROC)gala_ogl_get_proc_address("glDisable");

  glGenBuffers = (GLGENBUFFERSPROC)gala_ogl_get_proc_address("glGenBuffers");
  glGenTextures = (GLGENTEXTURESPROC)gala_ogl_get_proc_address("glGenTextures");
  glGenSamplers = (GLGENSAMPLERSPROC)gala_ogl_get_proc_address("glGenSamplers");
  glGenFramebuffers = (GLGENFRAMEBUFFERSPROC)gala_ogl_get_proc_address("glGenFramebuffers");

  glDeleteBuffers = (GLDELETEBUFFERSPROC)gala_ogl_get_proc_address("glDeleteBuffers");
  glDeleteTextures = (GLDELETETEXTURESPROC)gala_ogl_get_proc_address("glDeleteTextures");
  glDeleteSamplers = (GLDELETESAMPLERSPROC)gala_ogl_get_proc_address("glDeleteSamplers");
  glDeleteFramebuffers = (GLDELETEFRAMEBUFFERSPROC)gala_ogl_get_proc_address("glDeleteFramebuffers");

  glGenVertexArrays = (GLGENVERTEXARRAYSPROC)gala_ogl_get_proc_address("glGenVertexArrays");
  glDeleteVertexArrays = (GLDELETEVERTEXARRAYSPROC)gala_ogl_get_proc_address("glDeleteVertexArrays");
  glBindVertexArray = (GLBINDVERTEXARRAYPROC)gala_ogl_get_proc_address("glBindVertexArray");

  glViewport = (GLVIEWPORTPROC)gala_ogl_get_proc_address("glViewport");
  glScissor = (GLSCISSORPROC)gala_ogl_get_proc_address("glScissor");

  glBindBuffer = (GLBINDBUFFERPROC)gala_ogl_get_proc_address("glBindBuffer");

  glBindTexture = (GLBINDTEXTUREPROC)gala_ogl_get_proc_address("glBindTexture");

  glTexImage1D = (GLTEXIMAGE1DPROC)gala_ogl_get_proc_address("glTexImage1D");
  glTexImage2D = (GLTEXIMAGE2DPROC)gala_ogl_get_proc_address("glTexImage2D");
  glTexImage3D = (GLTEXIMAGE3DPROC)gala_ogl_get_proc_address("glTexImage3D");

  glTexParameterf = (GLTEXPARAMETERFPROC)gala_ogl_get_proc_address("glTexParameterf");
  glTexParameteri = (GLTEXPARAMETERIPROC)gala_ogl_get_proc_address("glTexParameteri");

  glGenerateMipmap = (GLGENERATEMIPMAPPROC)gala_ogl_get_proc_address("glGenerateMipmap");

  glBindSampler = (GLBINDSAMPLERPROC)gala_ogl_get_proc_address("glBindSampler");

  glSamplerParameterf = (GLSAMPLERPARAMETERFPROC)gala_ogl_get_proc_address("glSamplerParameterf");
  glSamplerParameteri = (GLSAMPLERPARAMETERIPROC)gala_ogl_get_proc_address("glSamplerParameteri");

  glBindFramebuffer = (GLBINDFRAMEBUFFERPROC)gala_ogl_get_proc_address("glBindFramebuffer");

  glFramebufferTexture1D = (GLFRAMEBUFFERTEXTURE1DPROC)gala_ogl_get_proc_address("glFramebufferTexture1D");
  glFramebufferTexture2D = (GLFRAMEBUFFERTEXTURE2DPROC)gala_ogl_get_proc_address("glFramebufferTexture2D");
  glFramebufferTexture3D = (GLFRAMEBUFFERTEXTURE3DPROC)gala_ogl_get_proc_address("glFramebufferTexture3D");

  glDrawBuffer = (GLDRAWBUFFERPROC)gala_ogl_get_proc_address("glDrawBuffer");
  glDrawBuffers = (GLDRAWBUFFERSPROC)gala_ogl_get_proc_address("glDrawBuffers");

  glClearBufferiv = (GLCLEARBUFFERIVPROC)gala_ogl_get_proc_address("glClearBufferiv");
  glClearBufferuiv = (GLCLEARBUFFERUIVPROC)gala_ogl_get_proc_address("glClearBufferuiv");
  glClearBufferfv = (GLCLEARBUFFERFVPROC)gala_ogl_get_proc_address("glClearBufferfv");

  glBlitFramebuffer = (GLBLITFRAMEBUFFERPROC)gala_ogl_get_proc_address("glBlitFramebuffer");

  glFlush = (GLFLUSHPROC)gala_ogl_get_proc_address("glFlush");
  glFinish = (GLFINISHPROC)gala_ogl_get_proc_address("glFinish");

  gala_ogl_check_for_extensions();

  if (GL_KHR_debug) {
    glPushDebugGroup = (GLPUSHDEBUGGROUPPROC)gala_ogl_get_proc_address("glPushDebugGroup");
    glPopDebugGroup  = (GLPOPDEBUGGROUPPROC)gala_ogl_get_proc_address("glPopDebugGroup");
    glObjectLabel    = (GLOBJECTLABELPROC)gala_ogl_get_proc_address("glObjectLabel");
  } else {
    glPushDebugGroup = NULL;
    glPopDebugGroup  = NULL;
    glObjectLabel    = NULL;
  }

  glClipControl = (GLCLIPCONTROLPROC)gala_ogl_get_proc_address("glClipControl");
}

void gala_ogl_init(void)
{
#if GALA_PLATFORM == GALA_PLATFORM_WINDOWS
  gala_wgl_init();
#endif
}

void gala_ogl_shutdown(void) {
#if GALA_PLATFORM == GALA_PLATFORM_WINDOWS
  gala_wgl_shutdown();
#endif
}

typedef struct gala_ogl_resource {
  // ...
} gala_ogl_resource_t;

typedef struct gala_ogl_swap_chain {
  gala_pixel_format_t format;

  gala_uint32_t width;
  gala_uint32_t height;

  // We actually render to an texture and copy its contents to the surface
  // prior to presentation. This has many benefits. Most importantly,
  // it prevents draw calls to the swap chain from blocking after presentation.
  gala_uint32_t fbo;
  gala_uint32_t offscreen;

#if GALA_PLATFORM == GALA_PLATFORM_WINDOWS
  // Ostensibly a window.
  gala_wgl_surface_t *surface;
#endif
} gala_ogl_swap_chain_t;

typedef struct gala_ogl_texture {
} gala_ogl_texture_t;

typedef struct gala_ogl_render_target_view {
  gala_pixel_format_t format;

  gala_dimensionality_t dimensionality;

  gala_uint32_t width;
  gala_uint32_t height;

  gala_uint32_t buffer;
} gala_ogl_render_target_view_t;

typedef struct gala_ogl_depth_stencil_target_view {
} gala_ogl_depth_stencil_target_view_t;

typedef struct gala_ogl_sampler {
} gala_ogl_sampler_t;

// NOTE(mtwilliams): Distinct types for supporting multiple viewports and
// scissors in the future.

typedef struct gala_ogl_viewport {
  gala_uint32_t x, y, w, h;
} gala_ogl_viewport_t;

typedef struct gala_ogl_scissor {
  gala_uint32_t x, y, w, h;
} gala_ogl_scissor_t;

typedef struct gala_ogl_engine {
  gala_engine_t generic;

  // We share a context rather than creating one per swap-chain.
  gala_ogl_context_t *context;

  // PERF(mtwilliams) Create another context for submitting asynchronous
  // operations on another thread. Allegedly the fast path. At the very least
  // it protects us from flushes.
  // gala_ogl_context_t *async;

  struct {
    gala_ogl_viewport_t viewport;
    gala_ogl_scissor_t scissor;

    // Composed of bound render-target views and depth-stencil target view.
    gala_uint32_t fbo;

    gala_uint32_t num_render_targets;
    gala_ogl_render_target_view_t *render_targets[8];
    gala_ogl_depth_stencil_target_view_t *depth_stencil_target;
  } state;
} gala_ogl_engine_t;

gala_ogl_context_t *gala_ogl_create_context(
  const gala_ogl_engine_t *engine,
  gala_pixel_format_t format,
  gala_ogl_context_t *share)
{
#if GALA_PLATFORM == GALA_PLATFORM_WINDOWS
  gala_wgl_context_creation_params_t context_creation_params;

  context_creation_params.version.major = 3;
  context_creation_params.version.minor = 3;

  context_creation_params.flags = 0x00000000;

  if (engine->generic.meta.flags & GALA_ENGINE_DEBUG)
    context_creation_params.flags |= GALA_WGL_CONTEXT_DEBUG;

  if (engine->generic.meta.type == GALA_ENGINE_TYPE_HARDWARE)
    context_creation_params.flags |= GALA_WGL_CONTEXT_ACCELERATED;

  context_creation_params.share = share;

  return gala_wgl_create_context(&context_creation_params);
#endif
}

void gala_ogl_destroy_context(
  const gala_ogl_engine_t *engine,
  gala_ogl_context_t *context)
{
  gala_assert_debug(engine != NULL);
  gala_assert_debug(context != NULL);

#if GALA_PLATFORM == GALA_PLATFORM_WINDOWS
  gala_wgl_destroy_context(context);
#endif
}

gala_engine_t *gala_ogl_create_and_init_engine(
  const gala_engine_creation_params_t *engine_creation_params)
{
  gala_assert_debug(engine_creation_params != NULL);

  gala_ogl_engine_t *engine = (gala_ogl_engine_t *)calloc(1, sizeof(gala_ogl_engine_t));

  engine->generic.meta.backend = GALA_BACKEND_OPENGL;
  engine->generic.meta.type = GALA_ENGINE_TYPE_HARDWARE;
  engine->generic.meta.flags = engine_creation_params->flags;

  engine->generic.resource_table = gala_resource_table_create();

  engine->generic.execute = &gala_ogl_engine_execute;

  engine->context = gala_ogl_create_context(engine, GALA_PIXEL_FORMAT_R8G8B8, NULL);
  // engine->async = gala_ogl_create_context(engine, GALA_PIXEL_FORMAT_R8G8B8, engine->context);

#if GALA_PLATFORM == GALA_PLATFORM_WINDOWS
  // REFACTOR(mtwilliams): Bind in `gala_ogl_engine_execute` if not bound.
  // PERF(mtwilliams): Track the current context using a thread-local variable?
  gala_wgl_bind(engine->context, NULL);
#endif

  // TODO(mtwilliams): Move function pointers into `gala_ogl_engine_t`.
  gala_ogl_wrangle();

  // Goes without saying...
  glEnable(0x8DB9 /* GL_FRAMEBUFFER_SRGB */);
  glEnable(0x884F /* GL_TEXTURE_CUBE_MAP_SEAMLESS */);

  // TODO(mtwilliams): Fallback if `ARB_clip_control` is not available.
  //
  //  * glDepthRange(-1.0, 1.0)
  //   + ARB_fragment_coord_conventions
  //   + Mirror prior to presention
  //
  //  * https://github.com/MonoGame/MonoGame/issues/3658#issuecomment-85975756
  //   + ARB_fragment_coord_conventions
  //   + Use math into shaders to map to [-1, 1]?
  //    * Expose through "coordinate system" in `origamicomet/scc`?
  //   + Mirror prior to presention
  //
  // See https://timothylottes.github.io/20140715.html.

  // Setup a sane coordinate system.
  glClipControl(GL_UPPER_LEFT, GL_ZERO_TO_ONE);

  // We draw to the backbuffer for the currently bound surface unless otherwise
  // specified. Don't change this without understanding how presentation works.
  // See `gala_ogl_present` for details.
  glDrawBuffer(GL_BACK);

  // HACK(mtwilliams): OpenGL 3.2 onwards no longer provides an implict vertex
  // array object, but requires a vertex array object for vertex specification.
  gala_uint32_t vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  if (engine_creation_params->flags & GALA_ENGINE_FAST_AND_LOOSE) {
    // If `ARB_buffer_storage` is not available, fallback to persistently
    // mapping with `GL_UNSYNCRONIZED_BIT`.
  } else {
    // If `ARB_buffer_storage` is not available, fallback to mapping and
    // unmapping.
  }

  return &engine->generic;
}

void gala_ogl_destroy_engine(
  gala_engine_t *generic)
{
  gala_assert_debug(generic != NULL);
  gala_assert_debug(generic->meta.backend == GALA_BACKEND_OPENGL);

  gala_ogl_engine_t *engine = (gala_ogl_engine_t *)generic;

  gala_resource_table_destroy(engine->generic.resource_table);

#if GALA_PLATFORM == GALA_PLATFORM_WINDOWS
  // NOTE(mtwilliams): We risk leaking memory if we don't
  // `wglMakeCurrent(NULL, NULL)` prior to exit. This also prevents horrible
  // crashes on some drivers by making sure no context is current prior to its
  // deletion.
  gala_wgl_bind(NULL, NULL);
#endif

  gala_ogl_destroy_context(engine, engine->context);
  // gala_ogl_destroy_context(engine, engine->async);

  free((void *)engine);
}

static void gala_ogl_label(
  gala_ogl_engine_t *engine,
  const gala_label_command_t *cmd)
{
  gala_resource_t *resource =
    gala_resource_table_lookup(engine->generic.resource_table, cmd->handle);

  switch (resource->type) {
    case GALA_RESOURCE_TYPE_TEXTURE_1D:
    case GALA_RESOURCE_TYPE_TEXTURE_2D:
    case GALA_RESOURCE_TYPE_TEXTURE_3D:
    case GALA_RESOURCE_TYPE_VERTEX_BUFFER:
    case GALA_RESOURCE_TYPE_INDEX_BUFFER:
    case GALA_RESOURCE_TYPE_CONSTANT_BUFFER:
    case GALA_RESOURCE_TYPE_RENDER_TARGET_VIEW:
    case GALA_RESOURCE_TYPE_DEPTH_STENCIL_TARGET_VIEW:
    case GALA_RESOURCE_TYPE_VERTEX_SHADER:
    case GALA_RESOURCE_TYPE_PIXEL_SHADER: {
      // ...
    } break;
  }
}

static void gala_ogl_fence_on_submission(
  gala_ogl_engine_t *engine,
  const gala_fence_command_t *cmd)
{
  gala_atomic_store_u64(cmd->fence, cmd->writeback);
}

static void gala_ogl_fence_on_completion(
  gala_ogl_engine_t *engine,
  const gala_fence_command_t *cmd)
{
  // PERF(mtwilliams): Use synchronization objects so that `glFinish` doesn't
  // destroy performance by waiting for all asynchronous operations.

  // Round-trip to wait until all previously submitted commands are complete.
  glFinish();

  gala_atomic_store_u64(cmd->fence, cmd->writeback);
}

static void gala_ogl_swap_chain_create(
  gala_ogl_engine_t *engine,
  const gala_create_swap_chain_command_t *cmd)
{
  gala_ogl_swap_chain_t *swap_chain =
    (gala_ogl_swap_chain_t *)calloc(1, sizeof(gala_ogl_swap_chain_t));

  // TODO(mtwilliams): Respect `cmd->desc.format`.
  swap_chain->format = cmd->desc.format;

  swap_chain->width = cmd->desc.width;
  swap_chain->height = cmd->desc.height;

  // PERF(mtwilliams): Theoretically render buffers can be faster. Likely only
  // matters on mobile.
  glGenTextures(1, &swap_chain->offscreen);
  glBindTexture(GL_TEXTURE_2D, swap_chain->offscreen);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, cmd->desc.width, cmd->desc.height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
  glBindTexture(GL_TEXTURE_2D, 0);

  glGenFramebuffers(1, &swap_chain->fbo);
  glBindFramebuffer(GL_FRAMEBUFFER, swap_chain->fbo);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT + 0, GL_TEXTURE_2D, swap_chain->offscreen, 0);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);

#if GALA_PLATFORM == GALA_PLATFORM_WINDOWS
  gala_uint32_t flags = 0x00000000;

  if (cmd->desc.flags & GALA_SWAP_CHAIN_FULLSCREEN)
    flags |= GALA_WGL_SURFACE_FULLSCREEN;
  if (cmd->desc.flags & GALA_SWAP_CHAIN_BORDERLESS)
    flags |= GALA_WGL_SURFACE_BORDERLESS;

  swap_chain->surface = gala_wgl_create_surface(engine->context, cmd->desc.surface, flags);
#endif

  gala_resource_t *resource = gala_resource_table_lookup(engine->generic.resource_table, cmd->swap_chain_handle);
  resource->internal = (gala_uintptr_t)swap_chain;
}

static void gala_ogl_swap_chain_destroy(
  gala_ogl_engine_t *engine,
  const gala_destroy_swap_chain_command_t *cmd)
{
  GALA_TRAP();
}

static void gala_ogl_resize_swap_chain(
  gala_ogl_engine_t *engine,
  const gala_resize_swap_chain_command_t *cmd)
{
  GALA_TRAP();
}

static void gala_ogl_texture_create_1d(
  gala_ogl_engine_t *engine,
  const gala_create_texture_command_t *cmd)
{
}

static void gala_ogl_texture_create_2d(
  gala_ogl_engine_t *engine,
  const gala_create_texture_command_t *cmd)
{
}

static void gala_ogl_texture_create_3d(
  gala_ogl_engine_t *engine,
  const gala_create_texture_command_t *cmd)
{
}

static void gala_ogl_create_texture(
  gala_ogl_engine_t *engine,
  const gala_create_texture_command_t *cmd)
{
  if (cmd->desc.dimensionality == GALA_ONE_DIMENSIONAL)
    gala_ogl_texture_create_1d(engine, cmd);
  else if (cmd->desc.dimensionality == GALA_TWO_DIMENSIONAL)
    gala_ogl_texture_create_2d(engine, cmd);
  else if (cmd->desc.dimensionality == GALA_THREE_DIMENSIONAL)
    gala_ogl_texture_create_3d(engine, cmd);
}

static void gala_ogl_destroy_texture(
  gala_ogl_engine_t *engine,
  const gala_destroy_texture_command_t *cmd)
{
}

static void gala_ogl_render_target_view_create(
  gala_ogl_engine_t *engine,
  const gala_create_render_target_view_command_t *cmd)
{
  // PERF(mtwilliams): Allocate from pool.
  gala_ogl_render_target_view_t *render_target_view =
    (gala_ogl_render_target_view_t *)calloc(sizeof(gala_ogl_render_target_view_t), 1);

  gala_resource_t *resource = gala_resource_table_lookup(engine->generic.resource_table, cmd->render_target_view_handle);
  resource->internal = (gala_uintptr_t)render_target_view;

  render_target_view->format = cmd->desc.format;

  render_target_view->dimensionality = cmd->desc.dimensionality;

  render_target_view->width = cmd->desc.width;
  render_target_view->height = cmd->desc.height;

  gala_resource_t *storage = gala_resource_table_lookup(engine->generic.resource_table, cmd->desc.storage);

  const gala_bool_t backed_by_swap_chain = (storage->type == GALA_RESOURCE_TYPE_SWAP_CHAIN);
  const gala_bool_t backed_by_texture    = !!(storage->type & GALA_RESOURCE_TYPE_TEXTURE);

  gala_assert_debug(backed_by_swap_chain || backed_by_texture);

  if (backed_by_swap_chain) {
    const gala_ogl_swap_chain_t *swap_chain = (const gala_ogl_swap_chain_t *)storage->internal;
    render_target_view->buffer = swap_chain->offscreen;
  } else if (backed_by_texture) {
    GALA_TRAP();
  }
}

static void gala_ogl_render_target_view_destroy(
  gala_ogl_engine_t *engine,
  const gala_destroy_render_target_view_command_t *cmd)
{
  gala_resource_t *resource = gala_resource_table_lookup(engine->generic.resource_table, cmd->render_target_view_handle);
  free((void *)resource->internal);
}

// ...

static void gala_ogl_sampler_create(
  gala_ogl_engine_t *engine,
  const gala_create_sampler_command_t *cmd)
{
}

static void gala_ogl_sampler_destroy(
  gala_ogl_engine_t *engine,
  const gala_destroy_sampler_command_t *cmd)
{
}

static void gala_ogl_set_viewport(
  gala_ogl_engine_t *engine,
  const gala_uint32_t x,
  const gala_uint32_t y,
  const gala_uint32_t w,
  const gala_uint32_t h)
{
  engine->state.viewport.x = x;
  engine->state.viewport.y = y;
  engine->state.viewport.w = w;
  engine->state.viewport.h = h;

  glViewport(x, h - y, w, h);
}

static void gala_ogl_set_scissor(
  gala_ogl_engine_t *engine,
  const gala_uint32_t x,
  const gala_uint32_t y,
  const gala_uint32_t w,
  const gala_uint32_t h)
{
  engine->state.scissor.x = x;
  engine->state.scissor.y = y;
  engine->state.scissor.w = w;
  engine->state.scissor.h = h;

  glScissor(x, h - y, w, h);
}

static void gala_ogl_reset_viewport_and_scissor(const gala_ogl_engine_t *engine) {
  glViewport(engine->state.viewport.x,
             engine->state.viewport.h - engine->state.viewport.y,
             engine->state.viewport.w,
             engine->state.viewport.h);

  glScissor(engine->state.scissor.x,
            engine->state.scissor.h - engine->state.scissor.y,
            engine->state.scissor.w,
            engine->state.scissor.h);
}

static void gala_ogl_set_render_and_depth_stencil_targets(
  gala_ogl_engine_t *engine,
  const gala_set_render_and_depth_stencil_targets_command_t *cmd)
{
  gala_ogl_render_target_view_t *render_targets[8] = { NULL, };

  for (gala_uint32_t render_target = 0; render_target < cmd->num_render_target_views; ++render_target) {
    gala_resource_t *resource = gala_resource_table_lookup(engine->generic.resource_table,
                                                           cmd->render_target_view_handles[render_target]);
    render_targets[render_target] = (gala_ogl_render_target_view_t *)resource->internal;
  }

  gala_ogl_depth_stencil_target_view_t *depth_stencil_target = NULL;

  if (cmd->depth_stencil_target_view_handle != GALA_INVALID_DEPTH_STENCIL_TARGET_VIEW_HANDLE) {
    gala_resource_t *resource = gala_resource_table_lookup(engine->generic.resource_table, cmd->depth_stencil_target_view_handle);
    depth_stencil_target = (gala_ogl_depth_stencil_target_view_t *)resource->internal;
  }

  const gala_bool_t bind_render_targets       = (cmd->num_render_target_views > 0);
  const gala_bool_t bind_depth_stencil_target = (cmd->depth_stencil_target_view_handle != GALA_INVALID_DEPTH_STENCIL_TARGET_VIEW_HANDLE);

  // PERF(mtwilliams): Cache instead of replace.
  glDeleteFramebuffers(1, &engine->state.fbo);
  glGenFramebuffers(1, &engine->state.fbo);
  glBindFramebuffer(GL_FRAMEBUFFER, engine->state.fbo);

  for (gala_uint32_t render_target = 0; render_target < cmd->num_render_target_views; ++render_target) {
    const gala_dimensionality_t dimensionality = render_targets[render_target]->dimensionality;
    const gala_uint32_t buffer = render_targets[render_target]->buffer;

    if (dimensionality == GALA_ONE_DIMENSIONAL)
      glFramebufferTexture1D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT + render_target, GL_TEXTURE_1D, buffer, 0);
    else if (dimensionality == GALA_TWO_DIMENSIONAL)
      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT + render_target, GL_TEXTURE_2D, buffer, 0);
  }

  // TODO(mtwilliams): Depth-stencil targets.
  // if (depth_stencil_target) {
  //   if (depth_stencil_target->depth)
  //     glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_stencil_target->buffer, 0);
  //   if (depth_stencil_target->stencil)
  //     glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depth_stencil_target->buffer, 0);
  // }

  static const gala_uint32_t attachments[] = {
    GL_COLOR_ATTACHMENT + 0,
    GL_COLOR_ATTACHMENT + 1,
    GL_COLOR_ATTACHMENT + 2,
    GL_COLOR_ATTACHMENT + 3,
    GL_COLOR_ATTACHMENT + 4,
    GL_COLOR_ATTACHMENT + 5,
    GL_COLOR_ATTACHMENT + 6,
    GL_COLOR_ATTACHMENT + 7
  };

  // This state is scoped to bound framebuffer, so we just have to set it once.
  glDrawBuffers(cmd->num_render_target_views, &attachments[0]);

  engine->state.num_render_targets = cmd->num_render_target_views;
  memcpy((void *)&engine->state.render_targets[0], (void *)&render_targets[0], sizeof(render_targets));
  engine->state.depth_stencil_target = depth_stencil_target;
}

static void gala_ogl_clear_render_targets(
  gala_ogl_engine_t *engine,
  const gala_clear_render_targets_command_t *cmd)
{
  if (engine->state.num_render_targets <= 0)
    return;

  // HACK(mtwilliams): Clear operations are masked and `glClearBufferData` is
  // too much of a nuisance to bother.
  glViewport(0, 0, 65535, 65535);
  glScissor(0, 0, 65535, 65535);

  // NOTE(mtwilliams): Since we have a layer of indirection (we render to
  // a texture) between swap-chains (to allow different formats and generally
  // make working with them easier) we don't have to special case them.
  for (gala_uint32_t render_target = 0; render_target < engine->state.num_render_targets; ++render_target)
    glClearBufferfv(GL_COLOR, render_target, &cmd->rgba[0]);

  gala_ogl_reset_viewport_and_scissor(engine);
}

static void gala_ogl_clear_depth_stencil_target(
  gala_ogl_engine_t *engine,
  const gala_clear_depth_stencil_target_command_t *cmd)
{
  if (engine->state.depth_stencil_target == NULL)
    return;

  // HACK(mtwilliams): Clear operations are masked and `glClearBufferData` is
  // too much of a nuisance to bother.
  glViewport(0, 0, 65535, 65535);
  glScissor(0, 0, 65535, 65535);

  if (cmd->channels.depth)
    glClearBufferfv(GL_DEPTH, 0, &cmd->depth);

  if (cmd->channels.stencil)
    glClearBufferuiv(GL_STENCIL, 0, &cmd->stencil);

  gala_ogl_reset_viewport_and_scissor(engine);
}

static void gala_ogl_read_from_texture(
  gala_ogl_engine_t *engine,
  const gala_read_from_texture_command_t *cmd)
{
}

static void gala_ogl_write_to_texture(
  gala_ogl_engine_t *engine,
  const gala_write_to_texture_command_t *cmd)
{
}

static void gala_ogl_present(
  gala_ogl_engine_t *engine,
  const gala_present_command_t *cmd)
{
  // TODO(mtwilliams): Allow users to swap as a group by refactoring to accept
  // more than one swap chain?
   // If we don't have swap groups, we can:
   //  * Swap the first with an interval of 1.
   //  * Then swap the rest with an interval of -1, i.e. tear if we miss.
   // Can `wglSwapMultipleBuffers` be leveraged as a fallback?
  // TODO(mtwilliams): Resolve swap chain if multisampling.
   // GL_EXT_framebuffer_multisample_blit_scaled
  // TODO(mtwilliams): Force a flush?
  // TODO(mtwilliams): Determine if masking applies to `glBlitFramebuffer`.

  gala_resource_t *resource = gala_resource_table_lookup(engine->generic.resource_table, cmd->swap_chain_handle);
  gala_ogl_swap_chain_t *swap_chain = (gala_ogl_swap_chain_t *)resource->internal;

#if GALA_PLATFORM == GALA_PLATFORM_WINDOWS
  gala_uint32_t width, height;
  gala_wgl_dimensions_of_surface(swap_chain->surface, &width, &height);

  // Bind to appropriate surface.
  gala_wgl_bind(engine->context, swap_chain->surface);

  // Resolve and scale into backbuffer.
  glBindFramebuffer(GL_READ_FRAMEBUFFER, swap_chain->fbo);
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
  glBlitFramebuffer(0, 0, swap_chain->width, swap_chain->height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_LINEAR);

  // Swap.
  gala_wgl_present(1, &swap_chain->surface, 0x00000000);

  // Reset state.
  gala_wgl_bind(engine->context, NULL);
  glBindFramebuffer(GL_FRAMEBUFFER, engine->state.fbo);
#endif
}

static void gala_ogl_engine_dispatch(
  gala_ogl_engine_t *engine,
  const gala_command_t *cmd)
{
  switch (cmd->header.type) {
    case GALA_COMMAND_TYPE_NOP:
      // Do absolutely nothing.
      return;

    case GALA_COMMAND_TYPE_LABEL:
      return gala_ogl_label(engine, (gala_label_command_t *)cmd);

    case GALA_COMMAND_TYPE_FENCE_ON_SUBMISSION:
      return gala_ogl_fence_on_submission(engine, (gala_fence_command_t *)cmd);

    case GALA_COMMAND_TYPE_FENCE_ON_COMPLETION:
      return gala_ogl_fence_on_completion(engine, (gala_fence_command_t *)cmd);

    case GALA_COMMAND_TYPE_CREATE_SWAP_CHAIN:
      return gala_ogl_swap_chain_create(engine, (gala_create_swap_chain_command_t *)cmd);

    case GALA_COMMAND_TYPE_DESTROY_SWAP_CHAIN:
      return gala_ogl_swap_chain_destroy(engine, (gala_destroy_swap_chain_command_t *)cmd);

    case GALA_COMMAND_TYPE_RESIZE_SWAP_CHAIN:
      return gala_ogl_resize_swap_chain(engine, (gala_resize_swap_chain_command_t *)cmd);

    case GALA_COMMAND_TYPE_CREATE_TEXTURE:
      return gala_ogl_create_texture(engine, (gala_create_texture_command_t *)cmd);

    case GALA_COMMAND_TYPE_DESTROY_TEXTURE:
      return gala_ogl_destroy_texture(engine, (gala_destroy_texture_command_t *)cmd);

    case GALA_COMMAND_TYPE_CREATE_RENDER_TARGET_VIEW:
      return gala_ogl_render_target_view_create(engine, (gala_create_render_target_view_command_t *)cmd);

    case GALA_COMMAND_TYPE_DESTROY_RENDER_TARGET_VIEW:
      return gala_ogl_render_target_view_destroy(engine, (gala_destroy_render_target_view_command_t *)cmd);

    case GALA_COMMAND_TYPE_CREATE_DEPTH_STENCIL_TARGET_VIEW:
    case GALA_COMMAND_TYPE_DESTROY_DEPTH_STENCIL_TARGET_VIEW:
      // Implement.
      return;

    case GALA_COMMAND_TYPE_CREATE_SAMPLER:
      return gala_ogl_sampler_create(engine, (gala_create_sampler_command_t *)cmd);

    case GALA_COMMAND_TYPE_DESTROY_SAMPLER:
      return gala_ogl_sampler_destroy(engine, (gala_destroy_sampler_command_t *)cmd);

    case GALA_COMMAND_TYPE_SET_RENDER_AND_DEPTH_STENCIL_TARGETS:
      return gala_ogl_set_render_and_depth_stencil_targets(engine, (gala_set_render_and_depth_stencil_targets_command_t *)cmd);

    case GALA_COMMAND_TYPE_CLEAR_RENDER_TARGETS:
      return gala_ogl_clear_render_targets(engine, (gala_clear_render_targets_command_t *)cmd);

    case GALA_COMMAND_TYPE_CLEAR_DEPTH_STENCIL_TARGET:
      return gala_ogl_clear_depth_stencil_target(engine, (gala_clear_depth_stencil_target_command_t *)cmd);

    case GALA_COMMAND_TYPE_READ_FROM_TEXTURE:
      return gala_ogl_read_from_texture(engine, (gala_read_from_texture_command_t *)cmd);

    case GALA_COMMAND_TYPE_WRITE_TO_TEXTURE:
      return gala_ogl_write_to_texture(engine, (gala_write_to_texture_command_t *)cmd);

    case GALA_COMMAND_TYPE_PRESENT:
      return gala_ogl_present(engine, (gala_present_command_t *)cmd);
  }
}

void gala_ogl_engine_execute(
  gala_engine_t *engine,
  const gala_command_buffer_t *commands)
{
  gala_assert_debug(engine != NULL);
  gala_assert_debug(commands != NULL);

  gala_assert_debug(engine->meta.backend == GALA_BACKEND_OPENGL);

  gala_uintptr_t current = commands->start;
  const gala_uintptr_t last = commands->current;

  while (current < last) {
    const gala_command_t *command = (gala_command_t *)current;
    gala_ogl_engine_dispatch((gala_ogl_engine_t *)engine, command);
    current += command->header.size;
  }
}

GALA_END_EXTERN_C

#endif // GALA_ENABLE_OPENGL
