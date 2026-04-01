/**
 * @brief
 * Small math library for vector and matrix math
 */

#ifndef ENGINE_MATH
#define ENGINE_MATH

#include "engine/primitives.h"
#include "engine/utils.h"

static inline float dot3(const vec3_t *const v0, const vec3_t *const v1)
{
    return (v0->x * v1->x +
            v0->y * v1->y +
            v0->z * v1->z);
}

static inline float dot4(const vec4_t *const v0, const vec4_t *const v1)
{
    return (v0->x * v1->x +
            v0->y * v1->y +
            v0->z * v1->z +
            v0->w * v1->w);
}

static inline vec4_t mat4_mul_vec4(const mat4_t *const m, const vec4_t *const v)
{

    float v_0 = dot4((vec4_t *)&m->m[0], v);
    float v_1 = dot4((vec4_t *)&m->m[1], v);
    float v_2 = dot4((vec4_t *)&m->m[2], v);
    float v_3 = dot4((vec4_t *)&m->m[3], v);

    return (vec4_t){v_0, v_1, v_2, v_3};
}

static inline mat4_t transpose(const mat4_t *const m)
{
    return (mat4_t){
        {m->m[0][0], m->m[1][0], m->m[2][0], m->m[3][0]},
        {m->m[0][1], m->m[1][1], m->m[2][1], m->m[3][1]},
        {m->m[0][2], m->m[1][2], m->m[2][2], m->m[3][2]},
        {m->m[0][3], m->m[1][3], m->m[2][3], m->m[3][3]}};
}

#endif
