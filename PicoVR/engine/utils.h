/**
 * @brief
 * This file implements several utility functions such as
 * those used for debugging purposes.
 */

#ifndef ENGINE_UTILS
#define ENGINE_UTILS

#include <stdio.h>
#include <time.h>

#include "engine/primitives.h"

static int time_taken(clock_t start, clock_t end)
{

    /**
     * @brief time_taken
     * Given a start clock time and an end clock time, we compute the amount of time
     * a certain set of instructions took on the processor. I'm going to use this
     * hopefully for optimization purposes.
     *
     * @details
     * clock_t start = clock();
     * ... do something ...
     * clock_t end = clock();
     * time_taken(start, end);
     */

    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    int s = (int)seconds;
    int ms = (int)((seconds - s) * 1e3);
    int us = (int)((seconds - s - ms / 1e3) * 1e6);
    printf("Time taken: %ds %dms %dus\n", s, ms, us);
}

static void print_vec2(const vec2_t *const v)
{
    /**
     * @brief Printing the components of a vec2.
     */

    printf("[%f %f]\n", v->x, v->y);
}

static void print_vec3(const vec3_t *const v)
{

    /**
     * @brief Printing the components of a vec3.
     */

    printf("[%f %f %f]\n", v->x, v->y, v->z);
}

static void print_vec4(const vec4_t *const v)
{

    /**
     * @brief Printing the components of a vec4.
     */

    printf("[%f %f %f %f]\n", v->x, v->y, v->z, v->w);
}

static void print_mat4(const mat4_t *const m)
{

    /**
     * @brief Printing the components of a mat4.
     *
     * @todo Do timing of flat vs non-flat and see which is faster.
     *       https://stackoverflow.com/questions/459691/what-is-the-best-timing-method-in-c
     */

    printf("[[%f %f %f %f] \n", m->m_flat[0], m->m_flat[1], m->m_flat[2], m->m_flat[3]);
    printf(" [%f %f %f %f] \n", m->m_flat[4], m->m_flat[5], m->m_flat[6], m->m_flat[7]);
    printf(" [%f %f %f %f] \n", m->m_flat[8], m->m_flat[9], m->m_flat[10], m->m_flat[11]);
    printf(" [%f %f %f %f]]\n", m->m_flat[12], m->m_flat[13], m->m_flat[14], m->m_flat[15]);
}

#endif