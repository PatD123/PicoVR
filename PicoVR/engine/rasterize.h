/**
 * @brief
 * Method declarations for the rasterization process.
 */

#include <stdio.h>

#include "engine/primitives.h"
#include "engine/utils.h"
#include "engine/globals.h"

// void rasterize(vec3_t *framebuffer, const triangle32_t *t0);

void rasterize(const triangle32_t *t0);