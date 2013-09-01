/*
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 *
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * For more information, please refer to <http://unlicense.org/>
 */

#include "agl_runtime.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

AGL_RUNTIME size_t aglr_get_num_of_adapters()
{
  return 0;
}

AGL_RUNTIME const agl_adapter_t *aglr_get_adapter(
  const agl_adapter_id_t id)
{
  return NULL;
}

/*struct agl_context {
};*/

AGL_RUNTIME agl_context_t *aglr_create_context(
  const agl_adapter_id_t adapter)
{
  return NULL;
}

AGL_RUNTIME void aglr_destroy_context(
  agl_context_t *context)
{
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
