/**
 * @brief Small math library for vector and matrix math
 */

#include "engine/primitives.h"

inline float dot3(vec3_t *v0, vec3_t *v1)
{
    return (v0->x * v1->x +
            v0->y * v1->y +
            v0->z * v1->z);
}

inline float dot4(vec4_t *v0, vec4_t *v1)
{
    return (v0->x * v1->x +
            v0->y * v1->y +
            v0->z * v1->z +
            v0->w * v1->w);
}
