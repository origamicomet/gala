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

// TODO(mtwilliams): Move `gala_statistics_t` into separate header?
#include "gala/lifecycle.h"

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
// Capabilities
//

#define GL_CULL_FACE                      0x0B44

#define GL_BLEND                          0x0BE2

#define GL_DEPTH_TEST                     0x0B71
#define GL_STENCIL_TEST                   0x0B90
#define GL_SCISSOR_TEST                   0x0C11

#define GL_FRAMEBUFFER_SRGB               0x8DB9
#define GL_TEXTURE_CUBE_MAP_SEAMLESS      0x884F

//
// Types
//

#define GL_BYTE                           0x1400
#define GL_UNSIGNED_BYTE                  0x1401
#define GL_SHORT                          0x1402
#define GL_UNSIGNED_SHORT                 0x1403
#define GL_INT                            0x1404
#define GL_UNSIGNED_INT                   0x1405
#define GL_HALF_FLOAT                     0x140B
#define GL_FLOAT                          0x1406
#define GL_DOUBLE                         0x140A

//
// Windings
//

#define GL_CW                             0x0900
#define GL_CCW                            0x0901

//
// Polygon Modes
//

#define GL_POINT                          0x1B00
#define GL_LINE                           0x1B01
#define GL_FILL                           0x1B02

//
// Functions
//

#define GL_FUNC_ADD                       0x8006
#define GL_FUNC_SUBTRACT                  0x800A
#define GL_FUNC_REVERSE_SUBTRACT          0x800B
#define GL_MIN                            0x8007
#define GL_MAX                            0x8008

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
#define GL_INCR_WRAP                      0x8507
#define GL_DECR_WRAP                      0x8508

//
// Comparisons
//

#define GL_NEVER                          0x0200
#define GL_LESS                           0x0201
#define GL_EQUAL                          0x0202
#define GL_LEQUAL                         0x0203
#define GL_GREATER                        0x0204
#define GL_NOT_EQUAL                      0x0205
#define GL_GEQUAL                         0x0206
#define GL_ALWAYS                         0x0207

//
// Equations
//

#define GL_ZERO                           0x0000
#define GL_ONE                            0x0001
#define GL_SRC_COLOR                      0x0300
#define GL_ONE_MINUS_SRC_COLOR            0x0301
#define GL_SRC_ALPHA                      0x0302
#define GL_ONE_MINUS_SRC_ALPHA            0x0303
#define GL_DST_ALPHA                      0x0304
#define GL_ONE_MINUS_DST_ALPHA            0x0305
#define GL_DST_COLOR                      0x0306
#define GL_ONE_MINUS_DST_COLOR            0x0307
#define GL_SRC_ALPHA_SATURATE             0x0308
#define GL_CONSTANT_COLOR                 0x8001
#define GL_ONE_MINUS_CONSTANT_COLOR       0x8002

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
#define GL_ELEMENT_ARRAY_BUFFER           0x8893
#define GL_UNIFORM_BUFFER                 0x8A11

#define GL_STATIC_DRAW                    0x88E4
#define GL_STREAM_DRAW                    0x88E0
#define GL_DYNAMIC_DRAW                   0x88E8

#define GL_MAP_READ_BIT                   0x0001
#define GL_MAP_WRITE_BIT                  0x0002
#define GL_MAP_INVALIDATE_RANGE_BIT       0x0004
#define GL_MAP_INVALIDATE_BUFFER_BIT      0x0008
#define GL_MAP_FLUSH_EXPLICIT_BIT         0x0010
#define GL_MAP_UNSYNCHRONIZED_BIT         0x0020
#define GL_MAP_PERSISTENT_BIT             0x0040
#define GL_MAP_COHERENT_BIT               0x0080

#define GL_DYNAMIC_STORAGE_BIT            0x0100
#define GL_CLIENT_STORAGE_BIT             0x0200

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
// Shaders
//

#define GL_VERTEX_SHADER                  0x8B31
#define GL_FRAGMENT_SHADER                0x8B30

#define GL_COMPILE_STATUS                 0x8B81
#define GL_LINK_STATUS                    0x8B82
#define GL_VALIDATE_STATUS                0x8B83
#define GL_DELETE_STATUS                  0x8B80

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

typedef void (GL_ENTRY_POINT *GLFRAMETERMINATORGREMEDYPROC)(void);

GLFRAMETERMINATORGREMEDYPROC glFrameTerminatorGREMEDY;

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

typedef void (GL_ENTRY_POINT *GLPOLYGONMODEPROC)(gala_uint32_t face, gala_uint32_t mode);

GLPOLYGONMODEPROC glPolygonMode;

typedef void (GL_ENTRY_POINT *GLFRONTFACEPROC)(gala_uint32_t mode);
typedef void (GL_ENTRY_POINT *GLCULLFACEPROC)(gala_uint32_t mode);

GLFRONTFACEPROC glFrontFace;
GLCULLFACEPROC glCullFace;

typedef void (GL_ENTRY_POINT *GLCLIPCONTROLPROC)(gala_uint32_t origin, gala_uint32_t depth);

GLCLIPCONTROLPROC glClipControl;

typedef void (GL_ENTRY_POINT *GLBLENDFUNCSEPARATEPROC)(gala_uint32_t src_factor_rgb, gala_uint32_t dst_factor_rgb, gala_uint32_t src_factor_alpha, gala_uint32_t dst_factor_alpha);
typedef void (GL_ENTRY_POINT *GLBLENDEQUATIONSEPARATEPROC)(gala_uint32_t rgb, gala_uint32_t alpha);
typedef void (GL_ENTRY_POINT *GLBLENDCOLORPROC)(gala_float32_t red, gala_float32_t green, gala_float32_t blue, gala_float32_t alpha);

GLBLENDFUNCSEPARATEPROC glBlendFuncSeparate;
GLBLENDEQUATIONSEPARATEPROC glBlendEquationSeparate;
GLBLENDCOLORPROC glBlendColor;

typedef void (GL_ENTRY_POINT *GLCOLORMASKIPROC)(gala_uint32_t index, gala_bool_t r, gala_bool_t g, gala_bool_t b, gala_bool_t a);

GLCOLORMASKIPROC glColorMaski;

typedef void (GL_ENTRY_POINT *GLDEPTHFUNCPROC)(gala_uint32_t func);
typedef void (GL_ENTRY_POINT *GLDEPTHMASKPROC)(gala_bool_t flag);

GLDEPTHFUNCPROC glDepthFunc;
GLDEPTHMASKPROC glDepthMask;

typedef void (GL_ENTRY_POINT *GLSTENCILOPSEPARATEPROC)(gala_uint32_t face, gala_uint32_t sfail, gala_uint32_t dpfail, gala_uint32_t dppass);
typedef void (GL_ENTRY_POINT *GLSTENCILFUNCSEPARATEPROC)(gala_uint32_t face, gala_uint32_t func, gala_int32_t ref, gala_uint32_t mask);
typedef void (GL_ENTRY_POINT *GLSTENCILMASKSEPARATEPROC)(gala_uint32_t face, gala_uint32_t mask);

GLSTENCILOPSEPARATEPROC glStencilOpSeparate;
GLSTENCILFUNCSEPARATEPROC glStencilFuncSeparate;
GLSTENCILMASKSEPARATEPROC glStencilMaskSeparate;

typedef void (GL_ENTRY_POINT *GLGENBUFFERSPROC)(gala_uint32_t n, gala_uint32_t *buffers);
typedef void (GL_ENTRY_POINT *GLGENTEXTURESPROC)(gala_uint32_t n, gala_uint32_t *textures);
typedef void (GL_ENTRY_POINT *GLGENSAMPLERSPROC)(gala_uint32_t n, gala_uint32_t *samplers);
typedef void (GL_ENTRY_POINT *GLGENFRAMEBUFFERSPROC)(gala_uint32_t n, gala_uint32_t *framebuffers);
typedef gala_uint32_t (GL_ENTRY_POINT *GLCREATESHADERPROC)(gala_uint32_t type);
typedef gala_uint32_t (GL_ENTRY_POINT *GLCREATEPROGRAMPROC)(void);

GLGENBUFFERSPROC glGenBuffers;
GLGENTEXTURESPROC glGenTextures;
GLGENSAMPLERSPROC glGenSamplers;
GLGENFRAMEBUFFERSPROC glGenFramebuffers;
GLCREATESHADERPROC glCreateShader;
GLCREATEPROGRAMPROC glCreateProgram;

typedef void (GL_ENTRY_POINT *GLDELETEBUFFERSPROC)(gala_uint32_t n, const gala_uint32_t *buffers);
typedef void (GL_ENTRY_POINT *GLDELETETEXTURESPROC)(gala_uint32_t n, const gala_uint32_t *textures);
typedef void (GL_ENTRY_POINT *GLDELETESAMPLERSPROC)(gala_uint32_t n, const gala_uint32_t *samplers);
typedef void (GL_ENTRY_POINT *GLDELETESHADERPROC)(gala_uint32_t shader);
typedef void (GL_ENTRY_POINT *GLDELETEPROGRAMPROC)(gala_uint32_t program);
typedef void (GL_ENTRY_POINT *GLDELETEFRAMEBUFFERSPROC)(gala_uint32_t n, const gala_uint32_t *framebuffers);

GLDELETEBUFFERSPROC glDeleteBuffers;
GLDELETETEXTURESPROC glDeleteTextures;
GLDELETESAMPLERSPROC glDeleteSamplers;
GLDELETESHADERPROC glDeleteShader;
GLDELETEPROGRAMPROC glDeleteProgram;
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

typedef void (GL_ENTRY_POINT *GLBUFFERDATAPROC)(gala_uint32_t target, gala_size_t size, const void *data, gala_uint32_t usage);
typedef void (GL_ENTRY_POINT *GLBUFFERSUBDATAPROC)(gala_uint32_t target, gala_uintptr_t offset, gala_size_t length, const void *data);

GLBUFFERDATAPROC glBufferData;
GLBUFFERSUBDATAPROC glBufferSubData;

typedef void (GL_ENTRY_POINT *GLBUFFERSTORAGEPROC)(gala_uint32_t target, gala_size_t size, const void *data, gala_uint32_t flags);

GLBUFFERSTORAGEPROC glBufferStorage;

typedef void *(GL_ENTRY_POINT *GLMAPBUFFERRANGEPROC)(gala_uint32_t target, gala_uintptr_t offset, gala_size_t length, gala_uint32_t access);

GLMAPBUFFERRANGEPROC glMapBufferRange;

typedef void (GL_ENTRY_POINT *GLUNMAPBUFFERPROC)(gala_uint32_t target);

GLUNMAPBUFFERPROC glUnmapBuffer;

typedef void (GL_ENTRY_POINT *GLFLUSHMAPPEDBUFFERRANGEPROC)(gala_uint32_t target, gala_uintptr_t offset, gala_size_t length);

GLFLUSHMAPPEDBUFFERRANGEPROC glFlushMappedBufferRange;

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

// PERF(mtwilliams): Generate manually. Drivers can be really bad at generating mipmaps.
GLGENERATEMIPMAPPROC glGenerateMipmap;

GLBINDSAMPLERPROC glBindSampler;

typedef void (GL_ENTRY_POINT *GLSAMPLERPARAMETERFPROC)(gala_uint32_t sampler, gala_uint32_t name, gala_float32_t value);
typedef void (GL_ENTRY_POINT *GLSAMPLERPARAMETERIPROC)(gala_uint32_t sampler, gala_uint32_t name, gala_int32_t value);

GLSAMPLERPARAMETERFPROC glSamplerParameterf;
GLSAMPLERPARAMETERIPROC glSamplerParameteri;

typedef void (GL_ENTRY_POINT *GLSHADERSOURCEPROC)(gala_uint32_t shader, gala_uint32_t count, const char * const *sources, const gala_uint32_t *lengths);
typedef void (GL_ENTRY_POINT *GLCOMPILESHADERPROC)(gala_uint32_t shader);

GLSHADERSOURCEPROC glShaderSource;
GLCOMPILESHADERPROC glCompileShader;

typedef void (GL_ENTRY_POINT *GLGETSHADERIVPROC)(gala_uint32_t shader, gala_uint32_t pname, gala_int32_t *params);
typedef void (GL_ENTRY_POINT *GLGETSHADERINFOLOGPROC)(gala_uint32_t shader, gala_int32_t size, gala_int32_t *length, char *buffer);

GLGETSHADERIVPROC glGetShaderiv;
GLGETSHADERINFOLOGPROC glGetShaderInfoLog;

typedef void (GL_ENTRY_POINT *GLATTACHSHADERPROC)(gala_uint32_t program, gala_uint32_t shader);
typedef void (GL_ENTRY_POINT *GLLINKPROGRAMPROC)(gala_uint32_t program);

GLATTACHSHADERPROC glAttachShader;
GLLINKPROGRAMPROC glLinkProgram;

typedef void (GL_ENTRY_POINT *GLGETPROGRAMIVPROC)(gala_uint32_t program, gala_uint32_t pname, gala_int32_t *params);
typedef void (GL_ENTRY_POINT *GLGETPROGRAMINFOLOGPROC)(gala_uint32_t program, gala_int32_t size, gala_int32_t *length, char *buffer);

GLGETPROGRAMIVPROC glGetProgramiv;
GLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;

typedef void (GL_ENTRY_POINT *GLUSEPROGRAMPROC)(gala_uint32_t program);

GLUSEPROGRAMPROC glUseProgram;

typedef void (GL_ENTRY_POINT *GLENABLEVERTEXATTRIBARRAYPROC)(gala_uint32_t index);
typedef void (GL_ENTRY_POINT *GLDISABLEVERTEXATTRIBARRAYPROC)(gala_uint32_t index);

GLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
GLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;

typedef void (GL_ENTRY_POINT *GLVERTEXATTRIBPOINTERPROC)(gala_uint32_t index, gala_uint32_t size, gala_uint32_t type, gala_bool_t normalized, gala_uint32_t stride, const void *pointer);
typedef void (GL_ENTRY_POINT *GLVERTEXATTRIBIPOINTERPROC)(gala_uint32_t index, gala_uint32_t size, gala_uint32_t type, gala_uint32_t stride, const void *pointer);
typedef void (GL_ENTRY_POINT *GLVERTEXATTRIBDIVISORPROC)(gala_uint32_t index, gala_uint32_t divisor);

GLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
GLVERTEXATTRIBIPOINTERPROC glVertexAttribIPointer;
GLVERTEXATTRIBDIVISORPROC glVertexAttribDivisor;

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

typedef void (GL_ENTRY_POINT *GLDRAWARRAYSPROC)(gala_uint32_t mode, gala_uint32_t first, gala_uint32_t count);
typedef void (GL_ENTRY_POINT *GLDRAWELEMENTSBASEVERTEXPROC)(gala_uint32_t mode, gala_uint32_t count, gala_uint32_t type, const void *indices, gala_uint32_t base);

GLDRAWARRAYSPROC glDrawArrays;
GLDRAWELEMENTSBASEVERTEXPROC glDrawElementsBaseVertex;

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

typedef void *(GL_ENTRY_POINT *GLFENCESYNCPROC)(gala_uint32_t condition, gala_uint32_t flags);
typedef gala_uint32_t (GL_ENTRY_POINT *GLCLIENTWAITSYNCPROC)(void *sync, gala_uint32_t flags, gala_uint64_t timeout);
typedef void (GL_ENTRY_POINT *GLWAITSYNCPROC)(void *sync, gala_uint32_t flags, gala_uint64_t timeout);

GLFENCESYNCPROC glFenceSync;
GLCLIENTWAITSYNCPROC glClientWaitSync;
GLWAITSYNCPROC glWaitSync;

typedef void (GL_ENTRY_POINT *GLFLUSHPROC)(void);
typedef void (GL_ENTRY_POINT *GLFINISHPROC)(void);

GLFLUSHPROC  glFlush;
GLFINISHPROC glFinish;

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

static gala_bool_t GL_GREMEDY_frame_terminator = false;

static gala_bool_t GL_ARB_direct_state_access = false;
static gala_bool_t GL_ARB_multi_bind = false;
static gala_bool_t GL_ARB_vertex_attrib_binding = false;

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

  // This older extension allows us to explictly provide a frame terminator,
  // which is really helpful as the heuristics employed by most tools break due
  // to our presentation logic.
  { "GL_GREMEDY_frame_terminator", GALA_OGL_EXTENSION_DEBUG | GALA_OGL_EXTENSION_OPTIONAL, GALA_OGL_EXTENSION_NONE, &GL_GREMEDY_frame_terminator },

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

  // TODO(mtwilliams): Make use of ARB_vertex_attrib_binding.
  // Vertex attribute binding lets us separate vertex format and vertex source,
  // making it easier to switch vertex buffer pools as we don't have to
  // respecify the entire input layout. In practice this isn't a bottleneck as
  // we try to minimize binds.
  { "GL_ARB_vertex_attrib_binding", GALA_OGL_EXTENSION_OPTIONAL, GALA_OGL_EXTENSION_NONE, &GL_ARB_vertex_attrib_binding },

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

  glPolygonMode = (GLPOLYGONMODEPROC)gala_ogl_get_proc_address("glPolygonMode");

  glFrontFace = (GLFRONTFACEPROC)gala_ogl_get_proc_address("glFrontFace");
  glCullFace = (GLCULLFACEPROC)gala_ogl_get_proc_address("glCullFace");

  glBlendFuncSeparate = (GLBLENDFUNCSEPARATEPROC)gala_ogl_get_proc_address("glBlendFuncSeparate");
  glBlendEquationSeparate = (GLBLENDEQUATIONSEPARATEPROC)gala_ogl_get_proc_address("glBlendEquationSeparate");
  glBlendColor = (GLBLENDCOLORPROC)gala_ogl_get_proc_address("glBlendColor");

  glColorMaski = (GLCOLORMASKIPROC)gala_ogl_get_proc_address("glColorMaski");

  glDepthFunc = (GLDEPTHFUNCPROC)gala_ogl_get_proc_address("glDepthFunc");
  glDepthMask = (GLDEPTHMASKPROC)gala_ogl_get_proc_address("glDepthMask");

  glStencilOpSeparate = (GLSTENCILOPSEPARATEPROC)gala_ogl_get_proc_address("glStencilOpSeparate");
  glStencilFuncSeparate = (GLSTENCILFUNCSEPARATEPROC)gala_ogl_get_proc_address("glStencilFuncSeparate");
  glStencilMaskSeparate = (GLSTENCILMASKSEPARATEPROC)gala_ogl_get_proc_address("glStencilMaskSeparate");

  glGenBuffers = (GLGENBUFFERSPROC)gala_ogl_get_proc_address("glGenBuffers");
  glGenTextures = (GLGENTEXTURESPROC)gala_ogl_get_proc_address("glGenTextures");
  glGenSamplers = (GLGENSAMPLERSPROC)gala_ogl_get_proc_address("glGenSamplers");
  glCreateShader = (GLCREATESHADERPROC)gala_ogl_get_proc_address("glCreateShader");
  glCreateProgram = (GLCREATEPROGRAMPROC)gala_ogl_get_proc_address("glCreateProgram");
  glGenFramebuffers = (GLGENFRAMEBUFFERSPROC)gala_ogl_get_proc_address("glGenFramebuffers");

  glDeleteBuffers = (GLDELETEBUFFERSPROC)gala_ogl_get_proc_address("glDeleteBuffers");
  glDeleteTextures = (GLDELETETEXTURESPROC)gala_ogl_get_proc_address("glDeleteTextures");
  glDeleteSamplers = (GLDELETESAMPLERSPROC)gala_ogl_get_proc_address("glDeleteSamplers");
  glDeleteShader = (GLDELETESHADERPROC)gala_ogl_get_proc_address("glDeleteShader");
  glDeleteProgram = (GLDELETEPROGRAMPROC)gala_ogl_get_proc_address("glDeleteProgram");
  glDeleteFramebuffers = (GLDELETEFRAMEBUFFERSPROC)gala_ogl_get_proc_address("glDeleteFramebuffers");

  glGenVertexArrays = (GLGENVERTEXARRAYSPROC)gala_ogl_get_proc_address("glGenVertexArrays");
  glDeleteVertexArrays = (GLDELETEVERTEXARRAYSPROC)gala_ogl_get_proc_address("glDeleteVertexArrays");
  glBindVertexArray = (GLBINDVERTEXARRAYPROC)gala_ogl_get_proc_address("glBindVertexArray");

  glViewport = (GLVIEWPORTPROC)gala_ogl_get_proc_address("glViewport");
  glScissor = (GLSCISSORPROC)gala_ogl_get_proc_address("glScissor");

  glBindBuffer = (GLBINDBUFFERPROC)gala_ogl_get_proc_address("glBindBuffer");

  glBufferData = (GLBUFFERDATAPROC)gala_ogl_get_proc_address("glBufferData");
  glBufferSubData = (GLBUFFERSUBDATAPROC)gala_ogl_get_proc_address("glBufferSubData");

  glMapBufferRange = (GLMAPBUFFERRANGEPROC)gala_ogl_get_proc_address("glMapBufferRange");
  glUnmapBuffer = (GLUNMAPBUFFERPROC)gala_ogl_get_proc_address("glUnmapBuffer");

  glFlushMappedBufferRange = (GLFLUSHMAPPEDBUFFERRANGEPROC)gala_ogl_get_proc_address("glFlushMappedBufferRange");

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

  glShaderSource = (GLSHADERSOURCEPROC)gala_ogl_get_proc_address("glShaderSource");
  glCompileShader = (GLCOMPILESHADERPROC)gala_ogl_get_proc_address("glCompileShader");
  
  glGetShaderiv = (GLGETSHADERIVPROC)gala_ogl_get_proc_address("glGetShaderiv");
  glGetShaderInfoLog = (GLGETSHADERINFOLOGPROC)gala_ogl_get_proc_address("glGetShaderInfoLog");
  
  glAttachShader = (GLATTACHSHADERPROC)gala_ogl_get_proc_address("glAttachShader");
  glLinkProgram = (GLLINKPROGRAMPROC)gala_ogl_get_proc_address("glLinkProgram");
  
  glGetProgramiv = (GLGETPROGRAMIVPROC)gala_ogl_get_proc_address("glGetProgramiv");
  glGetProgramInfoLog = (GLGETPROGRAMINFOLOGPROC)gala_ogl_get_proc_address("glGetProgramInfoLog");
  
  glUseProgram = (GLUSEPROGRAMPROC)gala_ogl_get_proc_address("glUseProgram");

  glEnableVertexAttribArray = (GLENABLEVERTEXATTRIBARRAYPROC)gala_ogl_get_proc_address("glEnableVertexAttribArray");
  glDisableVertexAttribArray = (GLDISABLEVERTEXATTRIBARRAYPROC)gala_ogl_get_proc_address("glDisableVertexAttribArray");

  glVertexAttribPointer = (GLVERTEXATTRIBPOINTERPROC)gala_ogl_get_proc_address("glVertexAttribPointer");
  glVertexAttribIPointer = (GLVERTEXATTRIBIPOINTERPROC)gala_ogl_get_proc_address("glVertexAttribIPointer");
  glVertexAttribDivisor = (GLVERTEXATTRIBDIVISORPROC)gala_ogl_get_proc_address("glVertexAttribDivisor");

  glBindFramebuffer = (GLBINDFRAMEBUFFERPROC)gala_ogl_get_proc_address("glBindFramebuffer");

  glFramebufferTexture1D = (GLFRAMEBUFFERTEXTURE1DPROC)gala_ogl_get_proc_address("glFramebufferTexture1D");
  glFramebufferTexture2D = (GLFRAMEBUFFERTEXTURE2DPROC)gala_ogl_get_proc_address("glFramebufferTexture2D");
  glFramebufferTexture3D = (GLFRAMEBUFFERTEXTURE3DPROC)gala_ogl_get_proc_address("glFramebufferTexture3D");

  glDrawBuffer = (GLDRAWBUFFERPROC)gala_ogl_get_proc_address("glDrawBuffer");
  glDrawBuffers = (GLDRAWBUFFERSPROC)gala_ogl_get_proc_address("glDrawBuffers");

  glClearBufferiv = (GLCLEARBUFFERIVPROC)gala_ogl_get_proc_address("glClearBufferiv");
  glClearBufferuiv = (GLCLEARBUFFERUIVPROC)gala_ogl_get_proc_address("glClearBufferuiv");
  glClearBufferfv = (GLCLEARBUFFERFVPROC)gala_ogl_get_proc_address("glClearBufferfv");

  glDrawArrays = (GLDRAWARRAYSPROC)gala_ogl_get_proc_address("glDrawArrays");
  glDrawElementsBaseVertex = (GLDRAWELEMENTSBASEVERTEXPROC)gala_ogl_get_proc_address("glDrawElementsBaseVertex");

  glBlitFramebuffer = (GLBLITFRAMEBUFFERPROC)gala_ogl_get_proc_address("glBlitFramebuffer");

  glFenceSync = (GLFENCESYNCPROC)gala_ogl_get_proc_address("glFenceSync");
  glClientWaitSync = (GLCLIENTWAITSYNCPROC)gala_ogl_get_proc_address("glClientWaitSync");
  glWaitSync = (GLWAITSYNCPROC)gala_ogl_get_proc_address("glWaitSync");

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

  if (GL_GREMEDY_frame_terminator) {
    glFrameTerminatorGREMEDY = (GLFRAMETERMINATORGREMEDYPROC)gala_ogl_get_proc_address("glFrameTerminatorGREMEDY");
  } else {
    glFrameTerminatorGREMEDY = NULL;
  }

  glClipControl = (GLCLIPCONTROLPROC)gala_ogl_get_proc_address("glClipControl");

  if (GL_ARB_buffer_storage) {
    glBufferStorage = (GLBUFFERSTORAGEPROC)gala_ogl_get_proc_address("glBufferStorage");
  } else {
    glBufferStorage = NULL;
  }

  if (GL_ARB_vertex_attrib_binding) {
  } else {
  }
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

  gala_uint32_t flags;
} gala_ogl_swap_chain_t;

typedef struct gala_ogl_pipeline {
  gala_uint32_t winding;
  gala_uint32_t fill;
  gala_uint32_t cull;

  struct {
    gala_bool_t blend;
    gala_uint32_t src;
    gala_uint32_t dst;
    gala_uint32_t equation;
    gala_float32_t constant[4];
    gala_uint32_t mask;
  } color;

  struct {
    gala_bool_t test;
    gala_uint32_t func;
    gala_bool_t mask;
  } depth;

  struct {
    gala_bool_t test;

    struct {
      gala_uint32_t func;
      gala_uint32_t pass;
      gala_uint32_t fail_to_depth;
      gala_uint32_t fail_to_stencil;
    } front;

    struct {
      gala_uint32_t func;
      gala_uint32_t pass;
      gala_uint32_t fail_to_depth;
      gala_uint32_t fail_to_stencil;
    } back;

    gala_uint8_t ref;

    gala_uint8_t mask;
  } stencil;
} gala_ogl_pipeline_t;

// We maintain five pools for buffers regardless of extension availability.
//
// How memory is allocated and handled for the pools does differ based on
// extension availability and the `GALA_ENGINE_FAST_AND_LOOSE` flag.
//
// 1) Static Indices
// 2) Static Vertices
// 3) Dynamic Indices
// 4) Dynamic Verticies
// 5) Constants

#define GALA_OGL_NUM_BUFFER_POOLS 5

#define GALA_OGL_STATIC_INDICES 0
#define GALA_OGL_STATIC_VERTICES 1
#define GALA_OGL_DYNAMIC_INDICES 2
#define GALA_OGL_DYNAMIC_VERTICES 3
#define GALA_OGL_CONSTANTS 4

// TODO(mtwilliams): Maintain a copy of `memory` for dynamic resize?
// TODO(mtwilliams): Use native width types for occupancy bitset.

typedef struct gala_ogl_buffer_pool {
  // Index, vertex, or constant buffer?
  gala_uint32_t type;

  // Size of pool in bytes.
  gala_uint32_t size;

  // Size of leaf in bytes.
  gala_uint32_t leaf;

  // Base two logarithm of `leaf`.
  gala_uint32_t log_of_leaf;

  // Maximum number of levels. Derived from `size` and `leaf`.
  gala_uint32_t levels;
  gala_uint32_t levels_minus_one;

  // Total number of blocks.
  gala_uint32_t blocks;

  // Chunk of memory to allocate from. May be `NULL` if writes are direct.
  void *memory;

  // Indicates if we own `memory` and should free it.
  gala_bool_t owner_of_memory;

  // Additional bytes allocated at the front of the buffer, to be sacrificed to
  // align vertexes to block boundaries. See `gala_ogl_set_input_layout`.
  gala_uint32_t padding;

  // Bitset indicating a block is not in use.
  gala_uint32_t *unoccupied;

  // Bitset indicating if a block has been split.
  gala_uint32_t *split;

  // Name of the shared buffer object.
  gala_uint32_t id;

  // Target and usage of shared buffer object.
  gala_uint32_t target;
  gala_uint32_t usage;

  // Indicates if a complete flush is required prior to use.
  gala_bool_t dirty;

  // Indicates that flushes should occur immediately.
  gala_bool_t flush_right_away;

  // Statistics tracked for internal heuristics.
  gala_uint64_t writes;
  gala_uint64_t writes_this_frame;
  gala_uint64_t flushes;
  gala_uint64_t flushes_this_frame;
} gala_ogl_buffer_pool_t;

static void gala_ogl_buffer_pool_create(
  gala_ogl_buffer_pool_t *pool,
  gala_uint32_t type,
  gala_uint32_t size,
  gala_bool_t fast_and_loose)
{
  gala_assert_debug(pool != NULL);

  pool->type = type;

  pool->size = size;

  pool->leaf = 256;
  pool->log_of_leaf = 8;

  gala_assert_debug(GALA_IS_POWER_OF_TWO(pool->size));
  gala_assert_debug(GALA_IS_POWER_OF_TWO(pool->leaf));

  pool->levels = gala_log2ul(pool->size / pool->leaf) + 1;
  pool->levels_minus_one = pool->levels - 1;

  pool->blocks = (1 << pool->levels) - 1;

  switch (pool->type) {
    case GALA_OGL_STATIC_INDICES:
    case GALA_OGL_DYNAMIC_INDICES: {
      const gala_bool_t dynamic = (pool->type == GALA_OGL_DYNAMIC_INDICES);
      pool->target = GL_ELEMENT_ARRAY_BUFFER;
      pool->usage = dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW;
      pool->padding = 0;
    } break;

    case GALA_OGL_STATIC_VERTICES:
    case GALA_OGL_DYNAMIC_VERTICES: {
      const gala_bool_t dynamic = (pool->type == GALA_OGL_DYNAMIC_VERTICES);
      pool->target = GL_ARRAY_BUFFER;
      pool->usage = dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW;
      pool->padding = pool->leaf;
    } break;

    case GALA_OGL_CONSTANTS: {
      pool->target = GL_UNIFORM_BUFFER;
      pool->usage = GL_STREAM_DRAW;
      pool->padding = 0;
    } break;
  }

  const gala_uint32_t padded = pool->size + pool->padding;

  glGenBuffers(1, &pool->id);
  glBindBuffer(pool->target, pool->id);

  if (pool->type != GALA_OGL_CONSTANTS) {
    if (GL_ARB_buffer_storage) {
      glBufferStorage(pool->target, padded, NULL, GL_DYNAMIC_STORAGE_BIT |
                                                  GL_MAP_WRITE_BIT |
                                                  GL_MAP_PERSISTENT_BIT);

      pool->memory =
        glMapBufferRange(pool->target, pool->padding, pool->size, GL_MAP_WRITE_BIT |
                                                                  GL_MAP_PERSISTENT_BIT |
                                                                  GL_MAP_INVALIDATE_BUFFER_BIT |
                                                                  GL_MAP_FLUSH_EXPLICIT_BIT);

      gala_assert(pool->memory != NULL);
    } else {
      glBufferData(pool->target, padded, NULL, pool->usage);

      if (fast_and_loose) {
        // HACK(mtwilliams): Treat `GL_MAP_UNSYNCHRONIZED_BIT` the same as a
        // persistently mapped buffer.
        pool->memory =
          glMapBufferRange(pool->target, pool->padding, pool->size, GL_MAP_WRITE_BIT |
                                                                    GL_MAP_UNSYNCHRONIZED_BIT |
                                                                    GL_MAP_INVALIDATE_BUFFER_BIT |
                                                                    GL_MAP_FLUSH_EXPLICIT_BIT);
        
        gala_assert(pool->memory != NULL);
      } else {
        pool->memory = NULL;
      }
    }

    pool->owner_of_memory = false;
  } else {
    pool->memory = calloc(1, padded);
    pool->owner_of_memory = true;
  }

  // We only have 1.5 bits of overhead per block! We could reduce this to 1 bit
  // of overhead per block by storing `a_is_allocated ^ b_is_allocated`.
  // However that comes at the cost of a more complicated allocation strategy
  // because we can't do a linear search to find the first available block.
  const gala_uint32_t bits_for_occupancy = (1 << (pool->levels)) - 1;
  const gala_uint32_t bits_for_splits = (1 << pool->levels_minus_one) - 1;

  // We pad the allocation to a word boundary, as we perform bit operations
  // on words not bits.
  const gala_uint32_t bytes_for_occupancy =
    GALA_ALIGN_TO_BOUNDARY(GALA_BITS_TO_BYTES(bits_for_occupancy), 4);
  const gala_uint32_t bytes_for_splits =
    GALA_ALIGN_TO_BOUNDARY(GALA_BITS_TO_BYTES(bits_for_splits), 4);

  // Both bitsets are allocated separately, rather than reserving a portion of
  // the pool as is common with buddy allocators because we have no guarantees
  // about `pool->memory`.
  pool->unoccupied = (gala_uint32_t *)calloc(1, bytes_for_occupancy);
  pool->split = (gala_uint32_t *)calloc(1, bytes_for_splits);

  // We set bits for unoccupied blocks. This drastically simplifies search
  // for a suitable unoccupied block.
  memset((void *)pool->unoccupied, ~0, bytes_for_occupancy);

  pool->dirty = false;

  pool->flush_right_away = false;

  pool->writes = 0;
  pool->writes_this_frame = 0;
  pool->flushes = 0;
  pool->flushes_this_frame = 0;
}

static void gala_ogl_buffer_pool_destroy(
  gala_ogl_buffer_pool_t *pool)
{
  gala_assert_debug(pool != NULL);

  glDeleteBuffers(1, &pool->id);
  
  if (pool->owner_of_memory)
    free(pool->memory);

  free((void *)pool->unoccupied);
  free((void *)pool->split);
}

static gala_uint32_t gala_ogl_buffer_pool_allocate(
  gala_ogl_buffer_pool_t *pool,
  gala_size_t size)
{
  gala_assert_debug(pool != NULL);
  gala_assert_debug(size <= pool->size);
  gala_assert_debug(size <= 0xFFFFFFFFul);

  const gala_uint32_t level = (size <= pool->leaf) ? pool->levels_minus_one : (pool->levels_minus_one - gala_log2ul_ceil(size) - pool->log_of_leaf);

  const gala_uint32_t first = (1 << level) - 1;
  const gala_uint32_t last  = 2 * first;

  const gala_uint32_t f_word = first / 32;
  const gala_uint32_t l_word = last / 32;

  const gala_uint32_t f_bit = first % 32;
  const gala_uint32_t l_bit = last % 32;

  const gala_uint32_t f_mask = (f_bit < 31) ? ~((1 << (f_bit + 1)) - 1) : 0x80000000;
  const gala_uint32_t l_mask = (l_bit < 31) ? ((1 << (l_bit + 1)) - 1) : ~0;

  // Sometimes the first and last bits are in same word. We take care to
  // mask appropriately so as not to search preceding and following levels.
  const gala_uint32_t same = (last - first) <= (31 - f_bit);
  const gala_uint32_t f_mask_corrected = f_mask & (l_mask | ~same);
  const gala_uint32_t l_mask_corrected = l_mask & (f_mask | ~same);

  gala_uint32_t block = 0;

  // First word.
  const gala_uint32_t f_word_masked = pool->unoccupied[f_word] & f_mask_corrected;
  if (block = f_word_masked ? (gala_ctzul(f_word_masked) + f_word * 32) : 0)
    goto found;

  // Middle words, if any.
  for (gala_uint32_t word = f_word + 1; word < l_word; ++word) {
    const gala_uint32_t candidates = pool->unoccupied[word];
    if (block = candidates ? (gala_ctzul(candidates) + word * 32) : 0)
      goto found;
  }

  // Last word.
  const gala_uint32_t l_word_masked = pool->unoccupied[l_word] & l_mask_corrected;
  if (block = l_word_masked ? (gala_ctzul(l_word_masked) + l_word * 32) : 0)
    goto found;

  // No space. Bummer.
  return 0;

found:
  // PERF(mtwilliams): Update parent and children bits a word at a time.
  // PERF(mtwilliams): Use division remainder to calculate parent instead of
  // relying on the compiler to optimize for us.

  // Mark as occupied.
  pool->unoccupied[block / 32] &= ~(1 << (block % 32));

  // Mark parents as occupied and split.
  gala_uint32_t parent = (block / 2) - (1 - (block % 2));
  do {
    pool->unoccupied[parent / 32] &= ~(1 << (parent % 32));
    pool->split[parent / 32] |= 1 << (parent % 32);  
    parent = (parent / 2) - (1 - (parent % 2));
  } while(parent);

  // Guaranteed to touch root.
  pool->unoccupied[0] &= 0xFFFFFFFE;
  pool->split[0] |= block ? 0 : 0x1;

  // Mark children as occupied.
  const gala_uint32_t blocks = pool->blocks;
  for (gala_uint32_t children = block * 2 + 1, count = 2; children < blocks; children = children * 2 + 1, count = count * 2) {
    // PERF(mtwilliams): Unroll.
    for (gala_uint32_t child = children; child < children + count; ++child)
      pool->unoccupied[child / 32] &= ~(1 << (child % 32));
  }

  return block + 1;
}

static void gala_ogl_buffer_pool_free(
  gala_ogl_buffer_pool_t *pool,
  gala_uint32_t id)
{
  gala_assert_debug(pool != NULL);
  gala_assert_debug(id != 0);

  const gala_uint32_t block = id - 1;

  // Sanity check the block is in bounds.
  gala_assert_debug(block < pool->blocks);

  // Sanity check the block is occupied but not split, indicating the block
  // was allocated.
  gala_assert_debug(pool->unoccupied[block / 32] & (1 << (block % 32)));
  gala_assert_debug(!(pool->split[block / 32] & (1 << (block % 32))));
  
  // Mark as unoccupied.
  pool->unoccupied[block / 32] |= (1 << (block % 32));

  // Mark children as unoccupied.
  const gala_uint32_t blocks = pool->blocks;
  for (gala_uint32_t children = block * 2 + 1, count = 2; children < blocks; children = children * 2 + 1, count = count * 2) {
    // PERF(mtwilliams): Unroll.
    for (gala_uint32_t child = children; child < children + count; ++child)
      pool->unoccupied[child / 32] |= (1 << (child % 32));
  }

  // Mark parent as unoccupied and unsplit if buddy is unoccupied.
  for (gala_uint32_t child = block; child > 0;) {
    const gala_uint32_t left = (child % 2);
    const gala_uint32_t buddy = left ? (child - 1) : (child + 1);
    const gala_bool_t mergeable = (pool->unoccupied[buddy / 32] & (1 << (buddy % 32))) > 0;

    if (!mergeable)
      return;

    const gala_uint32_t parent = (child / 2) - (1 - left);

    pool->unoccupied[parent / 32] |= (1 << (parent % 32));
    pool->split[parent / 32] &= ~(1 << (parent % 32));

    child = parent;
  }
}

static void gala_ogl_buffer_pool_lookup(
  const gala_ogl_buffer_pool_t *pool,
  gala_uint32_t id,
  gala_uintptr_t *offset,
  gala_size_t *size)
{
  gala_assert_debug(pool != NULL);
  gala_assert_debug(id != 0);

  const gala_uint32_t block = id - 1;
  const gala_uint32_t level = gala_log2ul_ceil(block);
  const gala_uint32_t size_at_level = pool->size / (1 << level);

  if (offset)
    *offset = size_at_level * (block - (1 << level) + 1);
  if (size)
    *size = size_at_level;
}

// PERF(mtwilliams): Double or triple buffer dynamic buffers to prevent
// blocking!
  // https://www.khronos.org/opengl/wiki/Buffer_Object_Streaming

typedef struct gala_ogl_buffer {
  // Pool this buffer was allocated from.
  gala_uint32_t pool;

  // Identifier pointing to allocated region.
  gala_uint32_t id;

  // Memory region where the buffer was sub-allocated.
  gala_uintptr_t offset;
  gala_size_t size;

  // Read and write fences we wait on to prevent hazards.
  struct {
    void *read;
    void *write;
  } fences;

  // TODO(mtwilliams): Track name internally.
} gala_ogl_buffer_t;

static void gala_ogl_buffer_write(
  gala_ogl_buffer_pool_t *pool,
  gala_ogl_buffer_t *buffer,
  gala_size_t offset,
  gala_size_t length,
  const void *data)
{
  // TODO(mtwilliams): Coalesce flushes (respect `flush_right_away`).
  // TODO(mtwilliams): Obey fences.
  // TODO(mtwilliams): Use named variants if available.

  gala_assert_debug(pool != NULL);
  gala_assert_debug(buffer != NULL);
  gala_assert_debug(offset + length <= buffer->size);

  // Padding already accounted for when we mapped memory, otherwise we have to
  // offset reads and writes ourself.
  const gala_uint32_t padding =
    pool->memory ? (pool->owner_of_memory ? pool->padding : 0) : pool->padding;

  const gala_uintptr_t offset_in_pool = padding + buffer->offset + offset;

  if (pool->memory) {
    memcpy((void *)((gala_uintptr_t)pool->memory + offset_in_pool), data, length);

    if (pool->owner_of_memory) {
      if (pool->flush_right_away) {
        // Flush the affected portion only.
        glBindBuffer(pool->target, pool->id);
        glBufferSubData(pool->target, offset_in_pool, length, data);

        pool->flushes += 1;
        pool->flushes_this_frame += 1;
      } else {
        // Flush as late as possible and at most once a frame. 
        pool->dirty = true;
      }
    } else {
      glBindBuffer(pool->target, pool->id);
      glFlushMappedBufferRange(pool->target, offset_in_pool, length);

      pool->flushes += 1;
      pool->flushes_this_frame += 1;
    }
  } else {
    glBindBuffer(pool->target, pool->id);
    glBufferSubData(pool->target, offset_in_pool, length, data);

    pool->flushes += 1;
    pool->flushes_this_frame += 1;
  }

  pool->writes += 1;
  pool->writes_this_frame += 1;
}

typedef struct gala_ogl_texture {
} gala_ogl_texture_t;

typedef struct gala_ogl_sampler {
} gala_ogl_sampler_t;

// PERF(mtwilliams): Allow preemptive linking of shaders through `gala_warm`.
// PERF(mtwilliams): Perform shader compilation and linking in a seperate thread.

typedef struct gala_ogl_shader {
  gala_uint32_t type;

  gala_uint32_t id;

  // Indicates if `GL_COMPILE_STATUS` has been checked.
  gala_bool_t validated;
} gala_ogl_shader_t;

static void gala_ogl_shader_validate(
  gala_ogl_shader_t *shader)
{
  if (shader->validated)
    return;

  gala_int32_t status;
  glGetShaderiv(shader->id, GL_COMPILE_STATUS, &status);

  if (status != GL_TRUE) {
    // TODO(mtwilliams): Present error(s) using `glGetShaderInfoLog`.
    GALA_TRAP();
  }

  shader->validated = true;
}

typedef struct gala_ogl_program {
  gala_uint32_t id;

  gala_uint32_t vs;
  gala_uint32_t ps;

  // Indicates if `GL_LINK_STATUS` has been checked.
  gala_bool_t validated;
} gala_ogl_program_t;

static const gala_uint32_t GALA_OGL_PROGRAM_CACHE_SIZE = 256;

// Cache of most recently used shader program combinations.
typedef struct gala_ogl_program_cache {
  gala_uint32_t unused;
  gala_uint32_t mru[GALA_OGL_PROGRAM_CACHE_SIZE / 32];
  gala_uint32_t hashes[GALA_OGL_PROGRAM_CACHE_SIZE];
  gala_ogl_program_t entries[GALA_OGL_PROGRAM_CACHE_SIZE];
} gala_ogl_program_cache_t;

static void gala_ogl_program_cache_initialize(
  gala_ogl_program_cache_t *cache)
{
  cache->unused = GALA_OGL_PROGRAM_CACHE_SIZE;

  memset((void *)&cache->mru[0], 0, sizeof(cache->mru));
  memset((void *)&cache->hashes[0], 0, sizeof(cache->hashes));
  memset((void *)&cache->entries[0], 0, sizeof(cache->entries));
}

static gala_uint32_t gala_ogl_program_cache_lru(
  const gala_ogl_program_cache_t *cache)
{
  for (gala_uint32_t word = 0; word < (GALA_OGL_PROGRAM_CACHE_SIZE / 32); ++word) {
    const gala_uint32_t mru = cache->mru[word];

    if (mru == ~0)
      continue;

    return word * 32 + gala_ctzul(~mru);
  }

  GALA_UNREACHABLE();
}

static void gala_ogl_program_cache_used(
  gala_ogl_program_cache_t *cache,
  gala_uint32_t slot)
{
  const gala_uint32_t word = slot / 32;
  const gala_uint32_t bit  = slot % 32;

  if (cache->mru[word] & (1 << bit))
    return;

  if (--cache->unused == 0) {
    cache->unused = GALA_OGL_PROGRAM_CACHE_SIZE;
    memset((void *)&cache->mru[0], 0, sizeof(cache->mru));
  }

  cache->mru[word] |= (1 << bit);
}

// TODO(mtwilliams): Mix better.
static gala_uint32_t gala_ogl_program_cache_hash(
  gala_uint32_t vertex_shader,
  gala_uint32_t pixel_shader)
{
  const gala_uint32_t K = UINT32_C(2654435761);

  return (
    (vertex_shader * K) ^
    (pixel_shader * K)
  );
}

typedef struct gala_ogl_attribute {
  gala_uint32_t type;
  gala_uint32_t size;
  gala_bool_t normalized;
  gala_bool_t cast;
  gala_uint32_t stride;
  gala_uint32_t offset;
  gala_uint32_t divisor;
} gala_ogl_attribute_t;

typedef struct gala_ogl_input_layout {
  gala_uint32_t stride;
  gala_uint32_t count;
  gala_ogl_attribute attributes[16];
} gala_ogl_input_layout_t;

typedef struct gala_ogl_render_target_view {
  gala_pixel_format_t format;

  gala_dimensionality_t dimensionality;

  gala_uint32_t width;
  gala_uint32_t height;

  gala_uint32_t buffer;
} gala_ogl_render_target_view_t;

typedef struct gala_ogl_depth_stencil_target_view {
} gala_ogl_depth_stencil_target_view_t;

typedef struct gala_ogl_framebuffer {
  gala_uint32_t id;
  gala_uint32_t render_targets[8];
  gala_uint32_t depth_stencil_target;
} gala_ogl_framebuffer_t;

// REFACTOR(mtwilliams): Factor like `gala_ogl_program_cache_t` and some.

// Cache of most recently used framebuffer objects.
typedef struct gala_ogl_framebuffer_cache {
  gala_uint32_t mru;
  gala_uint32_t hashes[32];
  gala_ogl_framebuffer_t entries[32];
} gala_ogl_framebuffer_cache_t;

static void gala_ogl_framebuffer_cache_initialize(
  gala_ogl_framebuffer_cache_t *cache)
{
  cache->mru = 0x00000000;

  memset((void *)&cache->hashes[0], 0, 32 * sizeof(gala_uint32_t));
  memset((void *)&cache->entries[0], 0, 32 * sizeof(gala_ogl_framebuffer_t));
}

// TODO(mtwilliams): Mix better.
static gala_uint32_t gala_ogl_framebuffer_cache_hash(
  gala_uint32_t render_targets[8],
  gala_uint32_t depth_stencil_target)
{
  const gala_uint32_t K = UINT32_C(2654435761);

  return (
    (render_targets[0] * K) ^ (render_targets[1] * K) ^
    (render_targets[2] * K) ^ (render_targets[3] * K) ^
    (render_targets[4] * K) ^ (render_targets[5] * K) ^
    (render_targets[6] * K) ^ (render_targets[7] * K) ^
    (render_targets[8] * K) ^ (depth_stencil_target * K)
  );
}

static void gala_ogl_framebuffer_cache_evict(
  gala_ogl_framebuffer_cache_t *cache,
  gala_uint32_t slot)
{
  glDeleteFramebuffers(1, &cache->entries[slot].id);

  cache->mru &= ~(1 << slot);

  cache->hashes[slot] = 0;

  cache->entries[slot].id = 0;
  cache->entries[slot].render_targets[0] = 0;
  cache->entries[slot].render_targets[1] = 0;
  cache->entries[slot].render_targets[2] = 0;
  cache->entries[slot].render_targets[3] = 0;
  cache->entries[slot].render_targets[4] = 0;
  cache->entries[slot].render_targets[5] = 0;
  cache->entries[slot].render_targets[6] = 0;
  cache->entries[slot].render_targets[7] = 0;
  cache->entries[slot].depth_stencil_target = 0;
}

static void gala_ogl_framebuffer_cache_evict_if_references(
  gala_ogl_framebuffer_cache_t *cache,
  gala_uint32_t render_or_depth_stencil_target)
{
  for (gala_uint32_t slot = 0; slot < 32; ++slot) {
    if (cache->entries[slot].id == 0)
      continue;

    if (cache->entries[slot].depth_stencil_target == render_or_depth_stencil_target) {
      gala_ogl_framebuffer_cache_evict(cache, slot);
      continue;
    }
    
    for (gala_uint32_t ref = 0; ref < 8; ++ref) {
      if (cache->entries[slot].render_targets[ref] == render_or_depth_stencil_target) {
        gala_ogl_framebuffer_cache_evict(cache, slot);
        break;
      }
    }
  }
}

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

    gala_uint32_t topology;

    const gala_ogl_input_layout_t *input_layout;

    const gala_ogl_buffer_t *index_buffer;
    const gala_ogl_buffer_t *vertex_buffer;

    // Composed of bound shaders.
    gala_ogl_program_t *program;

    // Composed of bound render-target views and depth-stencil target view.
    gala_uint32_t fbo;

    gala_uint32_t num_render_targets;
    gala_ogl_render_target_view_t *render_targets[8];
    gala_ogl_depth_stencil_target_view_t *depth_stencil_target;
  } state;

  struct {
    gala_ogl_framebuffer_cache_t framebuffers;
    gala_ogl_program_cache_t programs;
  } caches;

  struct {
    gala_ogl_buffer_pool_t buffers[GALA_OGL_NUM_BUFFER_POOLS];
  } pools;

  struct {
    gala_uint64_t frame;
    gala_uint64_t start_of_build;
    gala_uint64_t start_of_submission;
  } statistics;

  // Indicates that vertex attributes need to be respecified.
  gala_bool_t vertex_attributes_need_respecification;

  // Rolling buffer that tracks late flushes of constant buffers for each frame.
  gala_uint64_t late_flushes_in_recent_history;
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

  engine->statistics.frame = 0;
  engine->statistics.start_of_build = 0;
  engine->statistics.start_of_submission = 0;

#if GALA_PLATFORM == GALA_PLATFORM_WINDOWS
  // REFACTOR(mtwilliams): Bind in `gala_ogl_engine_execute` if not bound.
  // PERF(mtwilliams): Track the current context using a thread-local variable?
  gala_wgl_bind(engine->context, NULL);
#endif

  // TODO(mtwilliams): Move function pointers into `gala_ogl_engine_t`.
  gala_ogl_wrangle();

  // Goes without saying...
  glEnable(GL_FRAMEBUFFER_SRGB);
  glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

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

  // We always run with scissors ;)
  glEnable(GL_SCISSOR_TEST);

  // We draw to the backbuffer for the currently bound surface unless otherwise
  // specified. Don't change this without understanding how presentation works.
  // See `gala_ogl_present` for details.
  glDrawBuffer(GL_BACK);

  // HACK(mtwilliams): OpenGL 3.2 onwards no longer provides an implicit vertex
  // array object, but requires a vertex array object for vertex specification,
  // so we mimic that behavior by generating our own implict vertex array
  // object.
  gala_uint32_t vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  gala_ogl_framebuffer_cache_initialize(&engine->caches.framebuffers);
  gala_ogl_program_cache_initialize(&engine->caches.programs);

  // TODO(mtwilliams): Grow pools dynamically.
  // TODO(mtwilliams): Accept hints about pool size.
  // TODO(mtwilliams): Data drive pool initialization.

  const gala_bool_t fast_and_loose = !!(engine_creation_params->flags & GALA_ENGINE_FAST_AND_LOOSE);

  gala_ogl_buffer_pool_create(&engine->pools.buffers[GALA_OGL_STATIC_INDICES],
                              GALA_OGL_STATIC_INDICES,
                              0x2000000 /* 32MiB */,
                              fast_and_loose);

  gala_ogl_buffer_pool_create(&engine->pools.buffers[GALA_OGL_STATIC_VERTICES],
                              GALA_OGL_STATIC_VERTICES,
                              0x2000000 /* 32MiB */,
                              fast_and_loose);

  gala_ogl_buffer_pool_create(&engine->pools.buffers[GALA_OGL_DYNAMIC_INDICES],
                              GALA_OGL_DYNAMIC_INDICES,
                              0x100000 /* 1MiB */,
                              fast_and_loose);

  gala_ogl_buffer_pool_create(&engine->pools.buffers[GALA_OGL_DYNAMIC_VERTICES],
                              GALA_OGL_DYNAMIC_VERTICES,
                              0x100000 /* 1MiB */,
                              fast_and_loose);

  gala_ogl_buffer_pool_create(&engine->pools.buffers[GALA_OGL_CONSTANTS],
                              GALA_OGL_CONSTANTS,
                              0x100000 /* 1MiB */,
                              fast_and_loose);

  engine->late_flushes_in_recent_history = 0;

  // Insert a frame terminator to prevent "junk" from showing up in the first frame.
  if (GL_GREMEDY_frame_terminator)
    glFrameTerminatorGREMEDY();

  return &engine->generic;
}

void gala_ogl_destroy_engine(
  gala_engine_t *generic)
{
  gala_assert_debug(generic != NULL);
  gala_assert_debug(generic->meta.backend == GALA_BACKEND_OPENGL);

  gala_ogl_engine_t *engine = (gala_ogl_engine_t *)generic;

  gala_resource_table_destroy(engine->generic.resource_table);

  for (gala_uint32_t slot = 0; slot < 32; ++slot)
    if (engine->caches.framebuffers.entries[slot].id)
      glDeleteFramebuffers(1, &engine->caches.framebuffers.entries[slot].id);

  for (gala_uint32_t slot = 0; slot < GALA_OGL_PROGRAM_CACHE_SIZE; ++slot)
    if (engine->caches.programs.entries[slot].id)
      glDeleteProgram(engine->caches.programs.entries[slot].id);

  gala_ogl_buffer_pool_destroy(&engine->pools.buffers[GALA_OGL_STATIC_INDICES]);
  gala_ogl_buffer_pool_destroy(&engine->pools.buffers[GALA_OGL_STATIC_VERTICES]);
  gala_ogl_buffer_pool_destroy(&engine->pools.buffers[GALA_OGL_DYNAMIC_INDICES]);
  gala_ogl_buffer_pool_destroy(&engine->pools.buffers[GALA_OGL_DYNAMIC_VERTICES]);
  gala_ogl_buffer_pool_destroy(&engine->pools.buffers[GALA_OGL_CONSTANTS]);

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

static void gala_ogl_start_of_frame(
  gala_ogl_engine_t *engine,
  const gala_frame_command_t *cmd)
{
  gala_assert_debug(engine->statistics.frame == 0);

  engine->statistics.frame = cmd->id;

  engine->statistics.start_of_build = cmd->timestamp;
  engine->statistics.start_of_submission = 0 /* NOW() */;

  for (gala_uint32_t pool = 0; pool < GALA_OGL_NUM_BUFFER_POOLS; ++pool) {
    engine->pools.buffers[pool].writes_this_frame = 0;
    engine->pools.buffers[pool].flushes_this_frame = 0;
  }
}

static void gala_ogl_end_of_frame(
  gala_ogl_engine_t *engine,
  const gala_frame_command_t *cmd)
{
  gala_assert_debug(engine->statistics.frame != 0);
  gala_assert_debug(engine->statistics.frame == cmd->id);

  engine->late_flushes_in_recent_history =
    engine->late_flushes_in_recent_history << 1;

  if (engine->pools.buffers[GALA_OGL_CONSTANTS].flushes_this_frame > 1) {
    engine->late_flushes_in_recent_history |= 1;
  }

  // TODO(mtwilliams): Raise a warning.
  if (gala_popcntull(engine->late_flushes_in_recent_history) >= 32) {
    // More than half of the frames in recent history have flushed constants
    // more than once a frame, switch to `glBufferSubData` to reduce
    // performance impact.
    engine->pools.buffers[GALA_OGL_CONSTANTS].flush_right_away = true;
  }

  if (cmd->statistics) {
    cmd->statistics->id = engine->statistics.frame; 

    cmd->statistics->build = cmd->timestamp - engine->statistics.start_of_build; 
    cmd->statistics->submission = 0 /* NOW() */ - engine->statistics.start_of_submission; 

    for (gala_uint32_t pool = 0; pool < GALA_OGL_NUM_BUFFER_POOLS; ++pool) {
      cmd->statistics->buffers.writes += engine->pools.buffers[pool].writes_this_frame;
      cmd->statistics->buffers.flushes += engine->pools.buffers[pool].flushes_this_frame;
    }
  }

  engine->statistics.frame = 0;

  if (GL_GREMEDY_frame_terminator)
    glFrameTerminatorGREMEDY();
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

  swap_chain->flags = cmd->desc.flags;

  gala_resource_t *resource = gala_resource_table_lookup(engine->generic.resource_table, cmd->swap_chain_handle);
  resource->internal = (gala_uintptr_t)swap_chain;
}

static void gala_ogl_swap_chain_destroy(
  gala_ogl_engine_t *engine,
  const gala_destroy_swap_chain_command_t *cmd)
{
  gala_resource_t *resource =
    gala_resource_table_lookup(engine->generic.resource_table,
                               cmd->swap_chain_handle);

  gala_ogl_swap_chain_t *swap_chain =
    (gala_ogl_swap_chain_t *)resource->internal;

  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  // Evict any cached framebuffer objects that reference this swap-chain.
  gala_ogl_framebuffer_cache_evict_if_references(&engine->caches.framebuffers,
                                                 swap_chain->offscreen);

  glDeleteFramebuffers(1, &swap_chain->fbo);
  glDeleteTextures(1, &swap_chain->offscreen);

#if GALA_PLATFORM == GALA_PLATFORM_WINDOWS
  gala_wgl_destroy_surface(swap_chain->surface);
#endif

  free((void *)swap_chain);

  gala_resource_table_free(engine->generic.resource_table,
                           cmd->swap_chain_handle);
}

static void gala_ogl_resize_swap_chain(
  gala_ogl_engine_t *engine,
  const gala_resize_swap_chain_command_t *cmd)
{
  GALA_TRAP();
}

static gala_uint32_t gala_comparison_to_gl(const gala_comparison_t comparison) {
  switch (comparison) {
    case GALA_NEVER: return GL_NEVER;
    case GALA_LESS: return GL_LESS;
    case GALA_EQUAL: return GL_EQUAL;
    case GALA_LESS_EQUAL: return GL_LEQUAL;
    case GALA_GREATER: return GL_GREATER;
    case GALA_GREATER_EQUAL: return GL_GEQUAL;
    case GALA_NOT_EQUAL: return GL_NOT_EQUAL;
    case GALA_ALWAYS: return GL_ALWAYS;
  }
}

static gala_uint32_t gala_blend_to_gl(const gala_blend_t blend) {
  switch (blend) {
    case GALA_BLEND_ZERO: return GL_ZERO;
    case GALA_BLEND_ONE: return GL_ONE;
    case GALA_BLEND_SRC_COLOR: return GL_SRC_COLOR;
    case GALA_BLEND_INV_SRC_COLOR: return GL_ONE_MINUS_SRC_COLOR;
    case GALA_BLEND_SRC_ALPHA: return GL_SRC_ALPHA;
    case GALA_BLEND_INV_SRC_ALPHA: return GL_ONE_MINUS_SRC_ALPHA;
    case GALA_BLEND_DEST_ALPHA: return GL_DST_ALPHA;
    case GALA_BLEND_INV_DEST_ALPHA: return GL_ONE_MINUS_DST_ALPHA;
    case GALA_BLEND_DEST_COLOR: return GL_DST_COLOR;
    case GALA_BLEND_INV_DEST_COLOR: return GL_ONE_MINUS_DST_COLOR;
    case GALA_BLEND_SRC_ALPHA_SATURATE: return GL_SRC_ALPHA_SATURATE;
    case GALA_BLEND_BLEND_FACTOR: return GL_CONSTANT_COLOR;
    case GALA_BLEND_INV_BLEND_FACTOR: return GL_ONE_MINUS_CONSTANT_COLOR;
  }
}

static gala_uint32_t gala_blend_operation_to_gl(const gala_blend_operation_t op) {
  switch (op) {
    case GALA_BLEND_OP_ADD: return GL_FUNC_ADD;
    case GALA_BLEND_OP_SUBTRACT: return GL_FUNC_SUBTRACT;
    case GALA_BLEND_OP_REV_SUBTRACT: return GL_FUNC_REVERSE_SUBTRACT;
    case GALA_BLEND_OP_MIN: return GL_MIN;
    case GALA_BLEND_OP_MAX: return GL_MAX;
  }
}

static gala_uint32_t gala_stencil_operation_to_gl(const gala_stencil_operation_t op) {
  switch (op) {
    case GALA_STENCIL_OP_ZERO: return GL_ZERO;
    case GALA_STENCIL_OP_KEEP: return GL_KEEP;
    case GALA_STENCIL_OP_REPLACE: return GL_REPLACE;
    case GALA_STENCIL_OP_INVERT: return GL_INVERT;
    case GALA_STENCIL_OP_INCREMENT: return GL_INCR;
    case GALA_STENCIL_OP_DECREMENT: return GL_DECR;
    case GALA_STENCIL_OP_INCREMENT_SATURATE: return GL_INCR_WRAP;
    case GALA_STENCIL_OP_DECREMENT_SATURATE: return GL_DECR_WRAP;
  }
}

static void gala_ogl_pipeline_create(
  gala_ogl_engine_t *engine,
  const gala_create_pipeline_command_t *cmd)
{
  gala_resource_t *resource =
    gala_resource_table_lookup(engine->generic.resource_table,
                               cmd->pipeline_handle);

  // PERF(mtwilliams): Allocate from a pool.
  gala_ogl_pipeline_t *pipeline =
    (gala_ogl_pipeline_t *)calloc(sizeof(gala_ogl_pipeline_t), 1);

  resource->internal = (gala_uintptr_t)pipeline;

  if (cmd->desc.winding == GALA_CW)
    pipeline->winding = GL_CW;
  else if (cmd->desc.winding == GALA_CCW)
    pipeline->winding = GL_CCW;

  if (cmd->desc.fill == GALA_SOLID)
    pipeline->fill = GL_FILL;
  else if (cmd->desc.fill == GALA_WIREFRAME)
    pipeline->fill = GL_LINE;

  if (cmd->desc.cull == GALA_CULL_NONE)
    pipeline->cull = 0;
  else if (cmd->desc.cull == GALA_CULL_FRONT)
    pipeline->cull = GL_FRONT;
  else if (cmd->desc.cull == GALA_CULL_BACK)
    pipeline->cull = GL_BACK;

  pipeline->color.blend = cmd->desc.color.blend;

  pipeline->color.src = gala_blend_to_gl(cmd->desc.color.src);
  pipeline->color.dst = gala_blend_to_gl(cmd->desc.color.dst);

  pipeline->color.equation = gala_blend_operation_to_gl(cmd->desc.color.op);

  pipeline->color.constant[0] = cmd->desc.color.factor[0];
  pipeline->color.constant[1] = cmd->desc.color.factor[1];
  pipeline->color.constant[2] = cmd->desc.color.factor[2];
  pipeline->color.constant[3] = cmd->desc.color.factor[3];

  pipeline->color.mask = cmd->desc.color.mask;

  pipeline->depth.test = cmd->desc.depth.test;
  pipeline->depth.func = gala_comparison_to_gl(cmd->desc.depth.comparison);
  pipeline->depth.mask = !!(cmd->desc.depth.mask);

  gala_assert_debug((cmd->desc.depth.mask == 0x00000000) ||
                    (cmd->desc.depth.mask == 0xffffffff));

  pipeline->stencil.test = cmd->desc.stencil.test;

  pipeline->stencil.front.func = gala_comparison_to_gl(cmd->desc.stencil.front.comparison);
  pipeline->stencil.front.pass = gala_stencil_operation_to_gl(cmd->desc.stencil.front.pass);
  pipeline->stencil.front.fail_to_depth = gala_stencil_operation_to_gl(cmd->desc.stencil.front.fail_to_depth);
  pipeline->stencil.front.fail_to_stencil = gala_stencil_operation_to_gl(cmd->desc.stencil.front.fail_to_stencil);
  
  pipeline->stencil.back.func = gala_comparison_to_gl(cmd->desc.stencil.back.comparison);
  pipeline->stencil.back.pass = gala_stencil_operation_to_gl(cmd->desc.stencil.back.pass);
  pipeline->stencil.back.fail_to_depth = gala_stencil_operation_to_gl(cmd->desc.stencil.back.fail_to_depth);
  pipeline->stencil.back.fail_to_stencil = gala_stencil_operation_to_gl(cmd->desc.stencil.back.fail_to_stencil);

  pipeline->stencil.ref = cmd->desc.stencil.ref;

  pipeline->stencil.mask = cmd->desc.stencil.mask;
}

static void gala_ogl_pipeline_destroy(
  gala_ogl_engine_t *engine,
  const gala_destroy_pipeline_command_t *cmd)
{
  gala_resource_t *resource =
    gala_resource_table_lookup(engine->generic.resource_table,
                               cmd->pipeline_handle);

  gala_ogl_pipeline_t *pipeline = (gala_ogl_pipeline_t *)resource->internal;

  free((void *)pipeline);
}

static void gala_ogl_buffer_create(
  gala_ogl_engine_t *engine,
  const gala_create_buffer_command_t *cmd)
{
  gala_resource_t *resource =
    gala_resource_table_lookup(engine->generic.resource_table,
                               cmd->buffer_handle);

  // PERF(mtwilliams): Allocate from a pool.
  gala_ogl_buffer_t *buffer =
    (gala_ogl_buffer_t *)calloc(sizeof(gala_ogl_buffer_t), 1);

  resource->internal = (gala_uintptr_t)buffer;

  const gala_bool_t immutable = (cmd->mutability == GALA_IMMUTABLE);

  if (resource->type == GALA_RESOURCE_TYPE_INDEX_BUFFER) {
    buffer->pool = immutable ? GALA_OGL_STATIC_INDICES
                             : GALA_OGL_DYNAMIC_INDICES;
  } else if (resource->type == GALA_RESOURCE_TYPE_VERTEX_BUFFER) {
    buffer->pool = immutable ? GALA_OGL_STATIC_VERTICES
                             : GALA_OGL_DYNAMIC_VERTICES;
  } else if (resource->type == GALA_RESOURCE_TYPE_CONSTANT_BUFFER) {
    buffer->pool = GALA_OGL_CONSTANTS;
  }

  gala_ogl_buffer_pool_t *pool = &engine->pools.buffers[buffer->pool];

  buffer->id = gala_ogl_buffer_pool_allocate(pool, cmd->size);
  
  gala_ogl_buffer_pool_lookup(pool, buffer->id, &buffer->offset, NULL);
  buffer->size = cmd->size;

  buffer->fences.read = NULL;
  buffer->fences.write = NULL;

  if (cmd->data) {
    gala_ogl_buffer_write(pool, buffer, 0, cmd->size, cmd->data);
  }
}

static void gala_ogl_buffer_destroy(
  gala_ogl_engine_t *engine,
  const gala_destroy_buffer_command_t *cmd)
{
  gala_resource_t *resource = gala_resource_table_lookup(engine->generic.resource_table, cmd->buffer_handle);
  gala_ogl_buffer_t *buffer = (gala_ogl_buffer_t *)resource->internal;

  gala_ogl_buffer_pool_t *pool = &engine->pools.buffers[buffer->pool];
  gala_ogl_buffer_pool_free(pool, buffer->id);

  free((void *)buffer);
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

static void gala_ogl_texture_create(
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

static void gala_ogl_texture_destroy(
  gala_ogl_engine_t *engine,
  const gala_destroy_texture_command_t *cmd)
{
}

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

static const char *GALA_OGL_VERTEX_SHADER_PREAMBLE =
  "#version 330 core\n" \
  "#extension GL_ARB_shader_precision          : enable\n" \
  "#extension GL_ARB_shading_language_420pack  : enable\n" \
  "#extension GL_ARB_explicit_uniform_location : enable\n";

static const char *GALA_OGL_FRAGMENT_SHADER_PREAMBLE =
  "#version 330 core\n" \
  "#extension GL_ARB_shader_precision          : enable\n" \
  "#extension GL_ARB_shading_language_420pack  : enable\n" \
  "#extension GL_ARB_explicit_uniform_location : enable\n";

static void gala_ogl_shader_create(
  gala_ogl_engine_t *engine,
  const gala_create_shader_command_t *cmd)
{
  // PERF(mtwilliams): Allocate from pool.
  gala_ogl_shader_t *shader =
    (gala_ogl_shader_t *)calloc(sizeof(gala_ogl_shader_t), 1);

  gala_resource_t *resource =
    gala_resource_table_lookup(engine->generic.resource_table,
                               cmd->shader_handle);

  resource->internal = (gala_uintptr_t)shader;

  switch (resource->type) {
    case GALA_RESOURCE_TYPE_VERTEX_SHADER: shader->type = GL_VERTEX_SHADER; break;
    case GALA_RESOURCE_TYPE_PIXEL_SHADER: shader->type = GL_FRAGMENT_SHADER; break;
  }

  shader->id = glCreateShader(shader->type);

  gala_assert_debug((cmd->desc.encoding == GALA_SHADER_SOURCE) ||
                    (cmd->desc.encoding == GALA_SHADER_CACHED));

  if (cmd->desc.encoding == GALA_SHADER_SOURCE) {
    const char *sources[2] = { NULL, };

    if (shader->type == GL_VERTEX_SHADER)
      sources[0] = GALA_OGL_VERTEX_SHADER_PREAMBLE;
    else if (shader->type == GL_FRAGMENT_SHADER)
      sources[0] = GALA_OGL_FRAGMENT_SHADER_PREAMBLE;

    sources[1] = (const char *)cmd->desc.source;

    glShaderSource(shader->id, 2, &sources[0], NULL);
  } else if (cmd->desc.encoding == GALA_SHADER_CACHED) {
    GALA_TRAP();
  }

  glCompileShader(shader->id);

  shader->validated = false;
}

static void gala_ogl_shader_destroy(
  gala_ogl_engine_t *engine,
  const gala_destroy_shader_command_t *cmd)
{
  gala_resource_t *resource =
    gala_resource_table_lookup(engine->generic.resource_table,
                               cmd->shader_handle);

  gala_ogl_shader_t *shader = (gala_ogl_shader_t *)resource->internal;

  // TODO(mtwilliams): Evict any cached shader program objects that reference
  // this shader.
#if 0
  gala_ogl_program_cache_evict_if_references(&engine->caches.programs,
                                             shader->id);
#endif

  glDeleteShader(shader->id);

  free((void *)shader);
}

static gala_uint32_t gala_format_to_width(const gala_format_t format) {
  switch (format & ~GALA_FORMAT_NORMALIZED) {
    case GALA_FORMAT_X_S8: return 1;
    case GALA_FORMAT_XY_S8: return 2;
    case GALA_FORMAT_XYZ_S8: return 3;
    case GALA_FORMAT_XYZW_S8: return 4;
    case GALA_FORMAT_X_U8: return 1;
    case GALA_FORMAT_XY_U8: return 2;
    case GALA_FORMAT_XYZ_U8: return 3;
    case GALA_FORMAT_XYZW_U8: return 4;
    case GALA_FORMAT_X_S16: return 2;
    case GALA_FORMAT_XY_S16: return 4;
    case GALA_FORMAT_XYZ_S16: return 6;
    case GALA_FORMAT_XYZW_S16: return 8;
    case GALA_FORMAT_X_U16: return 2;
    case GALA_FORMAT_XY_U16: return 4;
    case GALA_FORMAT_XYZ_U16: return 6;
    case GALA_FORMAT_XYZW_U16: return 8;
    case GALA_FORMAT_X_S32: return 4;
    case GALA_FORMAT_XY_S32: return 8;
    case GALA_FORMAT_XYZ_S32: return 12;
    case GALA_FORMAT_XYZW_S32: return 32;
    case GALA_FORMAT_X_U32: return 4;
    case GALA_FORMAT_XY_U32: return 8;
    case GALA_FORMAT_XYZ_U32: return 12;
    case GALA_FORMAT_XYZW_U32: return 32;
    case GALA_FORMAT_X_F16: return 2;
    case GALA_FORMAT_XY_F16: return 4;
    case GALA_FORMAT_XYZ_F16: return 6;
    case GALA_FORMAT_XYZW_F16: return 8;
    case GALA_FORMAT_X_F32: return 4;
    case GALA_FORMAT_XY_F32: return 8;
    case GALA_FORMAT_XYZ_F32: return 12;
    case GALA_FORMAT_XYZW_F32: return 16;
  }
}

static void gala_format_to_gl(
  const gala_format_t format,
  gala_uint32_t *type,
  gala_uint32_t *size,
  gala_bool_t *normalized,
  gala_bool_t *cast)
{
  switch (format & ~GALA_FORMAT_NORMALIZED) {
    case GALA_FORMAT_X_S8: *type = GL_BYTE; *size = 1; break;
    case GALA_FORMAT_XY_S8: *type = GL_BYTE; *size = 2; break;
    case GALA_FORMAT_XYZ_S8: *type = GL_BYTE; *size = 3; break;
    case GALA_FORMAT_XYZW_S8: *type = GL_BYTE; *size = 4; break;
    case GALA_FORMAT_X_U8: *type = GL_UNSIGNED_BYTE; *size = 1; break;
    case GALA_FORMAT_XY_U8: *type = GL_UNSIGNED_BYTE; *size = 2; break;
    case GALA_FORMAT_XYZ_U8: *type = GL_UNSIGNED_BYTE; *size = 3; break;
    case GALA_FORMAT_XYZW_U8: *type = GL_UNSIGNED_BYTE; *size = 4; break;
    case GALA_FORMAT_X_S16: *type = GL_SHORT; *size = 1; break;
    case GALA_FORMAT_XY_S16: *type = GL_SHORT; *size = 2; break;
    case GALA_FORMAT_XYZ_S16: *type = GL_SHORT; *size = 3; break;
    case GALA_FORMAT_XYZW_S16: *type = GL_SHORT; *size = 4; break;
    case GALA_FORMAT_X_U16: *type = GL_UNSIGNED_SHORT; *size = 1; break;
    case GALA_FORMAT_XY_U16: *type = GL_UNSIGNED_SHORT; *size = 2; break;
    case GALA_FORMAT_XYZ_U16: *type = GL_UNSIGNED_SHORT; *size = 3; break;
    case GALA_FORMAT_XYZW_U16: *type = GL_UNSIGNED_SHORT; *size = 4; break;
    case GALA_FORMAT_X_S32: *type = GL_INT; *size = 1; break;
    case GALA_FORMAT_XY_S32: *type = GL_INT; *size = 2; break;
    case GALA_FORMAT_XYZ_S32: *type = GL_INT; *size = 3; break;
    case GALA_FORMAT_XYZW_S32: *type = GL_INT; *size = 4; break;
    case GALA_FORMAT_X_U32: *type = GL_UNSIGNED_INT; *size = 1; break;
    case GALA_FORMAT_XY_U32: *type = GL_UNSIGNED_INT; *size = 2; break;
    case GALA_FORMAT_XYZ_U32: *type = GL_UNSIGNED_INT; *size = 3; break;
    case GALA_FORMAT_XYZW_U32: *type = GL_UNSIGNED_INT; *size = 4; break;
    case GALA_FORMAT_X_F16: *type = GL_HALF_FLOAT; *size = 1; *cast = true; break;
    case GALA_FORMAT_XY_F16: *type = GL_HALF_FLOAT; *size = 2; *cast = true; break;
    case GALA_FORMAT_XYZ_F16: *type = GL_HALF_FLOAT; *size = 3; *cast = true; break;
    case GALA_FORMAT_XYZW_F16: *type = GL_HALF_FLOAT; *size = 4; *cast = true; break;
    case GALA_FORMAT_X_F32: *type = GL_FLOAT; *size = 1; *cast = true; break;
    case GALA_FORMAT_XY_F32: *type = GL_FLOAT; *size = 2; *cast = true; break;
    case GALA_FORMAT_XYZ_F32: *type = GL_FLOAT; *size = 3; *cast = true; break;
    case GALA_FORMAT_XYZW_F32: *type = GL_FLOAT; *size = 4; *cast = true; break;
  }
  
  if (format & GALA_FORMAT_NORMALIZED) {
    // TODO(mtwilliams): Orthogonalize normalization and casting.
    *normalized = true;
    *cast = true;
  }
}

static void gala_ogl_input_layout_create(
  gala_ogl_engine_t *engine,
  const gala_create_input_layout_command_t *cmd)
{
  // TODO(mtwilliams): Allow non-interleaved layouts.
   // * Offsets, including alignment, will vary by slot.
   // * We can bind the static and dynamic buffers upfront and map slots to
   //   offsets.
  for (gala_uint32_t index = 0; index < cmd->desc.count; ++index) {
    gala_assert_debug(cmd->desc.attributes[index].slot == 0);
    gala_assert_debug(cmd->desc.attributes[0].stride == cmd->desc.attributes[index].stride);
  }

  // PERF(mtwilliams): Allocate from pool.
  gala_ogl_input_layout_t *input_layout =
    (gala_ogl_input_layout_t *)calloc(sizeof(gala_ogl_input_layout_t), 1);

  gala_resource_t *resource =
    gala_resource_table_lookup(engine->generic.resource_table,
                               cmd->input_layout_handle);

  resource->internal = (gala_uintptr_t)input_layout;

  gala_uint32_t offsets[17] = { 0, };
  for (gala_uint32_t index = 0; index < cmd->desc.count; ++index)
    offsets[index + 1] = offsets[index] + gala_format_to_width(cmd->desc.attributes[index].format);

  input_layout->count = cmd->desc.count;

  input_layout->stride = cmd->desc.attributes[0].stride;

  if (input_layout->stride == 0)
    // Tightly packed.
    input_layout->stride = offsets[input_layout->count];


  if (!GALA_IS_POWER_OF_TWO(input_layout->stride)) {
    // TODO(mtwilliams): Warn about performance woes.
  }

  // TODO(mtwilliams): Validate index aligns with name?
  for (gala_uint32_t index = 0; index < cmd->desc.count; ++index) {
    gala_ogl_attribute_t *attribute = &input_layout->attributes[index];

    gala_format_to_gl(cmd->desc.attributes[index].format,
                      &attribute->type,
                      &attribute->size,
                      &attribute->normalized,
                      &attribute->cast);

    attribute->stride = cmd->desc.attributes[index].stride;
    attribute->offset = offsets[index];

    attribute->divisor = cmd->desc.attributes[index].rate;
  }
}

static void gala_ogl_input_layout_destroy(
  gala_ogl_engine_t *engine,
  const gala_destroy_input_layout_command_t *cmd)
{
  gala_resource_t *resource =
    gala_resource_table_lookup(engine->generic.resource_table,
                               cmd->input_layout_handle);

  gala_ogl_input_layout_t *input_layout =
    (gala_ogl_input_layout_t *)resource->internal;

  if (engine->state.input_layout == input_layout) {
    // TODO(mtwilliams): Defer destroy?
    engine->state.input_layout = NULL;
    engine->vertex_attributes_need_respecification = true;
  }

  free((void *)input_layout);
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
  gala_resource_t *resource =
    gala_resource_table_lookup(engine->generic.resource_table,
                               cmd->render_target_view_handle);

  gala_ogl_render_target_view_t *render_target_view =
    (gala_ogl_render_target_view_t *)resource->internal;

  free((void *)render_target_view);

  gala_resource_table_free(engine->generic.resource_table,
                           cmd->render_target_view_handle);
}

// TODO(mtwilliams): Depth-stencil targets.

static void gala_ogl_set_viewport(
  gala_ogl_engine_t *engine,
  const gala_set_viewport_command_t *cmd)
{
  engine->state.viewport.x = cmd->x;
  engine->state.viewport.y = cmd->y;
  engine->state.viewport.w = cmd->w;
  engine->state.viewport.h = cmd->h;

  glViewport(cmd->x, cmd->y, cmd->w, cmd->h);
}

static void gala_ogl_set_scissor(
  gala_ogl_engine_t *engine,
  const gala_set_scissor_command_t *cmd)
{
  engine->state.scissor.x = cmd->x;
  engine->state.scissor.y = cmd->y;
  engine->state.scissor.w = cmd->w;
  engine->state.scissor.h = cmd->h;

  glScissor(cmd->x, cmd->y, cmd->w, cmd->h);
}

static void gala_ogl_reset_viewport_and_scissor(const gala_ogl_engine_t *engine) {
  glViewport(engine->state.viewport.x,
             engine->state.viewport.y,
             engine->state.viewport.w,
             engine->state.viewport.h);

  glScissor(engine->state.scissor.x,
            engine->state.scissor.y,
            engine->state.scissor.w,
            engine->state.scissor.h);
}

// PERF(mtwilliams): Shadow state.
static void gala_ogl_set_pipeline(
  gala_ogl_engine_t *engine,
  const gala_set_pipeline_command_t *cmd)
{
  gala_resource_t *resource = gala_resource_table_lookup(engine->generic.resource_table,
                                                         cmd->pipeline_handle);

  const gala_ogl_pipeline_t *pipeline =
    (const gala_ogl_pipeline_t *)resource->internal;
  
  glFrontFace(pipeline->winding);
  
  glPolygonMode(GL_FRONT_AND_BACK, pipeline->fill);

  if (pipeline->cull) {
    glEnable(GL_CULL_FACE);
    glCullFace(pipeline->cull);
  } else {
    glDisable(GL_CULL_FACE);
  }

  if (pipeline->color.blend) {
    glEnable(GL_BLEND);

    glBlendFuncSeparate(pipeline->color.src,
                        pipeline->color.dst,
                        pipeline->color.src,
                        pipeline->color.dst);

    glBlendEquationSeparate(pipeline->color.equation,
                            pipeline->color.equation);

    glBlendColor(pipeline->color.constant[0],
                 pipeline->color.constant[1],
                 pipeline->color.constant[2],
                 pipeline->color.constant[3]);
  } else {
    glDisable(GL_BLEND);
  }

  for (gala_uint32_t render_target = 0; render_target < engine->state.num_render_targets; ++render_target) {
    glColorMaski(
      render_target,
      !!(pipeline->color.mask & (0x1 << (render_target * 4))),
      !!(pipeline->color.mask & (0x2 << (render_target * 4))),
      !!(pipeline->color.mask & (0x4 << (render_target * 4))),
      !!(pipeline->color.mask & (0x8 << (render_target * 4)))
    );
  }

  if (pipeline->depth.test) {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(pipeline->depth.func);
  } else {
    glDisable(GL_DEPTH_TEST);
  }

  glDepthMask(pipeline->depth.mask);

  if (pipeline->stencil.test) {
    glEnable(GL_STENCIL_TEST);

    glStencilFuncSeparate(GL_FRONT,
                          pipeline->stencil.front.func,
                          pipeline->stencil.ref,
                          0xffffffff);

    glStencilOpSeparate(GL_FRONT,
                        pipeline->stencil.front.fail_to_stencil,
                        pipeline->stencil.front.fail_to_depth,
                        pipeline->stencil.front.pass);

    glStencilFuncSeparate(GL_BACK,
                          pipeline->stencil.back.func,
                          pipeline->stencil.ref,
                          0xffffffff);

    glStencilOpSeparate(GL_BACK,
                        pipeline->stencil.back.fail_to_stencil,
                        pipeline->stencil.back.fail_to_depth,
                        pipeline->stencil.back.pass);

  } else {
    glDisable(GL_STENCIL_TEST);
  }

  glStencilMaskSeparate(GL_FRONT_AND_BACK, pipeline->stencil.mask);
}

static void gala_ogl_set_input_layout(
  gala_ogl_engine_t *engine,
  const gala_set_input_layout_command_t *cmd)
{
  const gala_resource_t *resource =
    gala_resource_table_lookup(engine->generic.resource_table,
                               cmd->input_layout_handle);

  const gala_ogl_input_layout_t *input_layout =
    (const gala_ogl_input_layout_t *)resource->internal;

  engine->state.input_layout = input_layout;

  // Defer specification until `gala_ogl_draw`.
  engine->vertex_attributes_need_respecification = true;
}

static void gala_ogl_set_topology(
  gala_ogl_engine_t *engine,
  const gala_set_topology_command_t *cmd)
{
  switch (cmd->topology) {
    case GALA_POINTS: engine->state.topology = GL_POINTS; break;
    case GALA_LINES: engine->state.topology = GL_LINES; break;
    case GALA_TRIANGLES: engine->state.topology = GL_TRIANGLES; break;
  }
}

static void gala_ogl_set_shaders(
  gala_ogl_engine_t *engine,
  const gala_set_shaders_command_t *cmd)
{
  gala_ogl_shader_t *vertex_shader = NULL;
  gala_ogl_shader_t *pixel_shader = NULL;

  if (cmd->vertex_shader_handle != GALA_INVALID_SHADER_HANDLE) {
    gala_resource_t *resource = gala_resource_table_lookup(engine->generic.resource_table, cmd->vertex_shader_handle);
    vertex_shader = (gala_ogl_shader_t *)resource->internal;
    gala_assert_debug(vertex_shader->type == GL_VERTEX_SHADER);
    gala_ogl_shader_validate(vertex_shader);
  }

  if (cmd->pixel_shader_handle != GALA_INVALID_SHADER_HANDLE) {
    gala_resource_t *resource = gala_resource_table_lookup(engine->generic.resource_table, cmd->pixel_shader_handle);
    pixel_shader = (gala_ogl_shader_t *)resource->internal;
    gala_assert_debug(pixel_shader->type == GL_FRAGMENT_SHADER);
    gala_ogl_shader_validate(pixel_shader);
  }

  const gala_uint32_t hash =
    gala_ogl_program_cache_hash(vertex_shader ? vertex_shader->id : 0,
                                pixel_shader ? pixel_shader->id : 0);

  gala_uint32_t index;
  gala_ogl_program_t *program = NULL;

  // PERF(mtwilliams): Do better than a linear search.
  for (index = 0; index < GALA_OGL_PROGRAM_CACHE_SIZE; ++index) {
    if (engine->caches.programs.hashes[index] == hash) {
      program = &engine->caches.programs.entries[index];
      break;
    }
  }

  if (program == NULL) {
    index = gala_ogl_program_cache_lru(&engine->caches.programs);

    engine->caches.programs.hashes[index] = hash;
    program = &engine->caches.programs.entries[index];

    if (program->id)
      glDeleteProgram(program->id);

    program->id = glCreateProgram();

    if (vertex_shader) {
      glAttachShader(program->id, vertex_shader->id);
      program->vs = vertex_shader->id;
    } else {
      program->vs = 0;
    }

    if (pixel_shader) {
      glAttachShader(program->id, pixel_shader->id);
      program->ps = pixel_shader->id;
    } else {
      program->ps = 0;
    }

    glLinkProgram(program->id);

    // TODO(mtwilliams): Detach after linking?
    // if (vertex_shader)
    //   glDetachShader(program->id, vertex_shader->id);    
    // if (pixel_shader)
    //   glDetachShader(program->id, pixel_shader->id);

    program->validated = false;
  }

  if (!program->validated) {
    // TODO(mtwilliams): Explicitly validate with `glValidateProgram`?

    gala_int32_t status;
    glGetProgramiv(program->id, GL_LINK_STATUS, &status);
    
    if (status != GL_TRUE) {
      // TODO(mtwilliams): Present error(s) using `glGetProgramInfoLog`.
      gala_assertf(!0, "Shader linking failed!");
    }

    program->validated = true;
  }

  gala_ogl_program_cache_used(&engine->caches.programs, index);

  glUseProgram(program->id);

  engine->state.program = program;
}

static void gala_ogl_set_render_and_depth_stencil_targets(
  gala_ogl_engine_t *engine,
  const gala_set_render_and_depth_stencil_targets_command_t *cmd)
{
  gala_uint32_t render_target_buffers[8] = { 0, };
  gala_uint32_t depth_stencil_target_buffer = 0;

  gala_ogl_render_target_view_t *render_targets[8] = { NULL, };

  for (gala_uint32_t render_target = 0; render_target < cmd->num_render_target_views; ++render_target) {
    gala_resource_t *resource = gala_resource_table_lookup(engine->generic.resource_table,
                                                           cmd->render_target_view_handles[render_target]);
    render_targets[render_target] = (gala_ogl_render_target_view_t *)resource->internal;
    render_target_buffers[render_target] = render_targets[render_target]->buffer;
  }

  gala_ogl_depth_stencil_target_view_t *depth_stencil_target = NULL;

  if (cmd->depth_stencil_target_view_handle != GALA_INVALID_DEPTH_STENCIL_TARGET_VIEW_HANDLE) {
    gala_resource_t *resource = gala_resource_table_lookup(engine->generic.resource_table, cmd->depth_stencil_target_view_handle);
    depth_stencil_target = (gala_ogl_depth_stencil_target_view_t *)resource->internal;
    // depth_stencil_target_buffer = depth_stencil_target->buffer;
  }

  const gala_uint32_t hash =
    gala_ogl_framebuffer_cache_hash(&render_target_buffers[0],
                                    depth_stencil_target_buffer);

  gala_uint32_t index;
  gala_ogl_framebuffer_t *cached = NULL;

  for (index = 0; index < 32; ++index) {
    if (engine->caches.framebuffers.hashes[index] == hash) {
      cached = &engine->caches.framebuffers.entries[index];
      break;
    }
  }

  if (cached) {
    engine->state.fbo = cached->id;

    engine->caches.framebuffers.mru |= (1 << index);

    if (engine->caches.framebuffers.mru == ~0)
      engine->caches.framebuffers.mru = (1 << index);

    glBindFramebuffer(GL_FRAMEBUFFER, cached->id);
  } else {
    const gala_uint32_t victim =
      engine->caches.framebuffers.mru ? gala_ctzul(~engine->caches.framebuffers.mru) : 0;

    engine->caches.framebuffers.mru |= (1 << victim);

    if (engine->caches.framebuffers.mru == ~0)
      engine->caches.framebuffers.mru = (1 << victim);

    engine->caches.framebuffers.hashes[victim] = hash;

    gala_ogl_framebuffer_t *fb = 
      &engine->caches.framebuffers.entries[victim];

    if (fb->id)
      glDeleteFramebuffers(1, &fb->id);
    
    glGenFramebuffers(1, &fb->id);
    glBindFramebuffer(GL_FRAMEBUFFER, fb->id);

    engine->state.fbo = fb->id;

    fb->render_targets[0] = render_target_buffers[0];
    fb->render_targets[1] = render_target_buffers[1];
    fb->render_targets[2] = render_target_buffers[2];
    fb->render_targets[3] = render_target_buffers[3];
    fb->render_targets[4] = render_target_buffers[4];
    fb->render_targets[5] = render_target_buffers[5];
    fb->render_targets[6] = render_target_buffers[6];
    fb->render_targets[7] = render_target_buffers[7];
    
    fb->depth_stencil_target = depth_stencil_target_buffer;
    
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
  }

  engine->state.num_render_targets = cmd->num_render_target_views;

  memcpy((void *)&engine->state.render_targets[0],
         (void *)&render_targets[0],
         sizeof(render_targets));
  
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

static void gala_ogl_flush_constants_if_dirty(
  gala_ogl_engine_t *engine)
{
  gala_ogl_buffer_pool_t *pool = &engine->pools.buffers[GALA_OGL_CONSTANTS];

  if (!pool->dirty)
    return;

  glBindBuffer(pool->target, pool->id);
  glBufferData(pool->target, pool->size + pool->padding, pool->memory, pool->usage);

  pool->flushes += 1;
  pool->flushes_this_frame += 1;
}

static void gala_ogl_draw(
  gala_ogl_engine_t *engine,
  const gala_draw_command_t *cmd)
{
  gala_ogl_flush_constants_if_dirty(engine);

  // TODO(mtwilliams): Constants.
   // TODO(mtwilliams): Validate that `constants` lines up with shader.
  // TODO(mtwilliams): Just in time batching.
   // PERF(mtwilliams): Track bindings per slot until a barrier, then order
   // draws by longest run to shortest run.
   // PERF(mtwilliams): If shader specifies a buffer, then specifying those
   // constants with a shader storage buffer?

  const gala_ogl_buffer_t *index_buffer = NULL;
  const gala_ogl_buffer_pool_t *index_buffer_pool = NULL;

  const gala_ogl_buffer_t *vertex_buffer = NULL;
  const gala_ogl_buffer_pool_t *vertex_buffer_pool = NULL;

  if (cmd->indicies != GALA_INVALID_BUFFER_HANDLE) {
    gala_resource_t *resource =
      gala_resource_table_lookup(engine->generic.resource_table, cmd->indicies);
    index_buffer = (const gala_ogl_buffer_t *)resource->internal;
    index_buffer_pool = &engine->pools.buffers[index_buffer->pool];
  }

  /* if (cmd->vertices != GALA_INVALID_BUFFER_HANDLE) */ {
    gala_resource_t *resource =
      gala_resource_table_lookup(engine->generic.resource_table, cmd->vertices);
    vertex_buffer = (const gala_ogl_buffer_t *)resource->internal;
    vertex_buffer_pool = &engine->pools.buffers[vertex_buffer->pool];
  }

  if (index_buffer) {
    if (!engine->state.index_buffer || (engine->state.index_buffer->pool != index_buffer->pool)) {
      glBindBuffer(index_buffer_pool->target, index_buffer_pool->id);
    }
  }

  if (!engine->state.vertex_buffer || (engine->state.vertex_buffer->pool != vertex_buffer->pool)) {
    glBindBuffer(vertex_buffer_pool->target, vertex_buffer_pool->id);
    engine->vertex_attributes_need_respecification = true;
  }

  engine->state.index_buffer = index_buffer;
  engine->state.vertex_buffer = vertex_buffer;

  const gala_ogl_input_layout_t *input_layout = engine->state.input_layout;

  if (!GALA_IS_POWER_OF_TWO(input_layout->stride)) {
    // TODO(mtwilliams): Batch into buckets based on offset required to align.
    // TODO(mtwilliams): Make use of NV_bindless_multi_draw_indirect so we can
    // make batching great again!

    // As we can only offset by multiples of `input_layout->stride` with draw
    // commands, we have to offset vertex attributes to align them to block
    // boundaries. As a consequence, we can't address the first block. We work
    // around this by padding our pools by the size of a leaf, effectively
    // creating a sacrificial first block. We also can't address blocks where
    // unless `address % (stride / (padding % stride)) == 1`. Intuitively we
    // can't address blocks at fractional offsets from our first block. For
    // now that means respecifying vertex attributes each time as we have no
    // guarantees about alignment. In the future we can batch by fractional
    // offsets which will reduce the performance impact.
    engine->vertex_attributes_need_respecification = true;
  }

  const gala_uint32_t offset = vertex_buffer->offset + vertex_buffer_pool->padding;
  const gala_uint32_t offset_to_align = offset % input_layout->stride;
  const gala_uint32_t base_to_align = (offset - offset_to_align) / input_layout->stride;
  
  if (engine->vertex_attributes_need_respecification) {
    for (gala_uint32_t index = 0; index < input_layout->count; ++index) {
      const gala_ogl_attribute_t *attribute = &input_layout->attributes[index];
     
      glEnableVertexAttribArray(index);
      
      if (attribute->cast) {
        glVertexAttribPointer(index, attribute->size, attribute->type, attribute->normalized, attribute->stride, (const void *)(attribute->offset + offset_to_align));
      } else {
        glVertexAttribIPointer(index, attribute->size, attribute->type, attribute->stride, (const void *)(attribute->offset + offset_to_align));
      }
      
      glVertexAttribDivisor(index, attribute->divisor);
    }

    for (gala_uint32_t index = input_layout->count; index < 16; ++index) {
      glDisableVertexAttribArray(index);
    }

    engine->vertex_attributes_need_respecification = false;
  }

  if (cmd->indicies != GALA_INVALID_BUFFER_HANDLE) {
    glDrawElementsBaseVertex(engine->state.topology,
                             cmd->count,
                             GL_UNSIGNED_INT,
                             (const void *)((cmd->first * 4) + (index_buffer->offset / 4)),
                             base_to_align);
  } else {
    glDrawArrays(engine->state.topology, cmd->first + base_to_align, cmd->count);
  }
}

static void gala_ogl_read_from_buffer(
  gala_ogl_engine_t *engine,
  const gala_read_from_buffer_command_t *cmd)
{
}

static void gala_ogl_write_to_buffer(
  gala_ogl_engine_t *engine,
  const gala_write_to_buffer_command_t *cmd)
{
  gala_resource_t *resource = gala_resource_table_lookup(engine->generic.resource_table, cmd->buffer_handle);

  gala_ogl_buffer_t *buffer = (gala_ogl_buffer_t *)&resource->internal;
  gala_ogl_buffer_pool_t *pool = &engine->pools.buffers[buffer->pool];

  gala_assert_debug(buffer->pool != GALA_OGL_STATIC_INDICES ||
                    buffer->pool != GALA_OGL_STATIC_VERTICES);

  gala_ogl_buffer_write(pool, buffer, cmd->offset, cmd->length, cmd->data);
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

// TODO(mtwilliams): Allow users to swap as a group by refactoring to accept more than one swap chain?
static void gala_ogl_present(
  gala_ogl_engine_t *engine,
  const gala_present_command_t *cmd)
{
  // TODO(mtwilliams): Resolve swap chain if multisampling.
   // GL_EXT_framebuffer_multisample_blit_scaled
  
  gala_resource_t *resource = gala_resource_table_lookup(engine->generic.resource_table, cmd->swap_chain_handle);
  gala_ogl_swap_chain_t *swap_chain = (gala_ogl_swap_chain_t *)resource->internal;

#if GALA_PLATFORM == GALA_PLATFORM_WINDOWS
  gala_uint32_t width, height;
  gala_wgl_dimensions_of_surface(swap_chain->surface, &width, &height);

  // Bind to appropriate surface.
  gala_wgl_bind(engine->context, swap_chain->surface);

  // HACK(mtwilliams): Prevent erroneous gamma correction on nVidia.
  glDisable(GL_FRAMEBUFFER_SRGB);

  glViewport(0, 0, width, height);
  glScissor(0, 0, width, height);
 
  // Resolve and scale into backbuffer.
  glBindFramebuffer(GL_READ_FRAMEBUFFER, swap_chain->fbo);
  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
  glBlitFramebuffer(0, 0, swap_chain->width, swap_chain->height, 0, 0, width, height, GL_COLOR_BUFFER_BIT, GL_LINEAR);

  gala_uint32_t flags = 0x00000000;
  if (swap_chain->flags & GALA_SWAP_CHAIN_SYNCHRONIZE)
    flags |= GALA_WGL_PRESENT_SYNCHRONIZE;
  if (swap_chain->flags & GALA_SWAP_CHAIN_TEAR_ON_MISS)
    flags |= GALA_WGL_PRESENT_TEAR_ON_MISS;

  // Swap.
  gala_wgl_present(1, &swap_chain->surface, flags);

  // Reset state.
  gala_wgl_bind(engine->context, NULL);
  glEnable(GL_FRAMEBUFFER_SRGB);
  gala_ogl_reset_viewport_and_scissor(engine);
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

    case GALA_COMMAND_TYPE_START_OF_FRAME:
      return gala_ogl_start_of_frame(engine, (gala_frame_command_t *)cmd);

    case GALA_COMMAND_TYPE_END_OF_FRAME:
      return gala_ogl_end_of_frame(engine, (gala_frame_command_t *)cmd);

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

    case GALA_COMMAND_TYPE_CREATE_PIPELINE:
      return gala_ogl_pipeline_create(engine, (gala_create_pipeline_command_t *)cmd);

    case GALA_COMMAND_TYPE_DESTROY_PIPELINE:
      return gala_ogl_pipeline_destroy(engine, (gala_destroy_pipeline_command_t *)cmd);

    case GALA_COMMAND_TYPE_CREATE_BUFFER:
      return gala_ogl_buffer_create(engine, (gala_create_buffer_command_t *)cmd);

    case GALA_COMMAND_TYPE_DESTROY_BUFFER:
      return gala_ogl_buffer_destroy(engine, (gala_destroy_buffer_command_t *)cmd);

    case GALA_COMMAND_TYPE_CREATE_TEXTURE:
      return gala_ogl_texture_create(engine, (gala_create_texture_command_t *)cmd);

    case GALA_COMMAND_TYPE_DESTROY_TEXTURE:
      return gala_ogl_texture_destroy(engine, (gala_destroy_texture_command_t *)cmd);

    case GALA_COMMAND_TYPE_CREATE_SAMPLER:
      return gala_ogl_sampler_create(engine, (gala_create_sampler_command_t *)cmd);

    case GALA_COMMAND_TYPE_DESTROY_SAMPLER:
      return gala_ogl_sampler_destroy(engine, (gala_destroy_sampler_command_t *)cmd);

    case GALA_COMMAND_TYPE_CREATE_SHADER:
      return gala_ogl_shader_create(engine, (gala_create_shader_command_t *)cmd);

    case GALA_COMMAND_TYPE_DESTROY_SHADER:
      return gala_ogl_shader_destroy(engine, (gala_destroy_shader_command_t *)cmd);

    case GALA_COMMAND_TYPE_CREATE_INPUT_LAYOUT:
      return gala_ogl_input_layout_create(engine, (gala_create_input_layout_command_t *)cmd);

    case GALA_COMMAND_TYPE_DESTROY_INPUT_LAYOUT:
      return gala_ogl_input_layout_destroy(engine, (gala_destroy_input_layout_command_t *)cmd);

    case GALA_COMMAND_TYPE_CREATE_RENDER_TARGET_VIEW:
      return gala_ogl_render_target_view_create(engine, (gala_create_render_target_view_command_t *)cmd);

    case GALA_COMMAND_TYPE_DESTROY_RENDER_TARGET_VIEW:
      return gala_ogl_render_target_view_destroy(engine, (gala_destroy_render_target_view_command_t *)cmd);

    case GALA_COMMAND_TYPE_CREATE_DEPTH_STENCIL_TARGET_VIEW:
    case GALA_COMMAND_TYPE_DESTROY_DEPTH_STENCIL_TARGET_VIEW:
      // Implement.
      return;

    case GALA_COMMAND_TYPE_SET_VIEWPORT:
      return gala_ogl_set_viewport(engine, (gala_set_viewport_command_t *)cmd);

    case GALA_COMMAND_TYPE_SET_SCISSOR:
      return gala_ogl_set_scissor(engine, (gala_set_scissor_command_t *)cmd);

    case GALA_COMMAND_TYPE_SET_PIPELINE:
      return gala_ogl_set_pipeline(engine, (gala_set_pipeline_command_t *)cmd);

    case GALA_COMMAND_TYPE_SET_INPUT_LAYOUT:
      return gala_ogl_set_input_layout(engine, (gala_set_input_layout_command_t *)cmd);

    case GALA_COMMAND_TYPE_SET_TOPOLOGY:
      return gala_ogl_set_topology(engine, (gala_set_topology_command_t *)cmd);

    case GALA_COMMAND_TYPE_SET_SHADERS:
      return gala_ogl_set_shaders(engine, (gala_set_shaders_command_t *)cmd);

    case GALA_COMMAND_TYPE_SET_RENDER_AND_DEPTH_STENCIL_TARGETS:
      return gala_ogl_set_render_and_depth_stencil_targets(engine, (gala_set_render_and_depth_stencil_targets_command_t *)cmd);

    case GALA_COMMAND_TYPE_CLEAR_RENDER_TARGETS:
      return gala_ogl_clear_render_targets(engine, (gala_clear_render_targets_command_t *)cmd);

    case GALA_COMMAND_TYPE_CLEAR_DEPTH_STENCIL_TARGET:
      return gala_ogl_clear_depth_stencil_target(engine, (gala_clear_depth_stencil_target_command_t *)cmd);

    case GALA_COMMAND_TYPE_DRAW:
      return gala_ogl_draw(engine, (gala_draw_command_t *)cmd);

    case GALA_COMMAND_TYPE_READ_FROM_BUFFER:
      return gala_ogl_read_from_buffer(engine, (gala_read_from_buffer_command_t *)cmd);

    case GALA_COMMAND_TYPE_WRITE_TO_BUFFER:
      return gala_ogl_write_to_buffer(engine, (gala_write_to_buffer_command_t *)cmd);

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
