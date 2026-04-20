/**
 * @brief
 * The following rasterization methods rasterize triangles
 * to a framebuffer.
 */

#include "engine/rasterize.h"
#include "engine/globals.h"
#include "engine/camera.h"

void rasterize(const triangle32_t *t0)
{
    /**
     * @brief rasterize
     * This function is designated to be on core 1, for dual core usage,
     * for the sole purpose of rasterizing our triangles.
     * @details
     * The triangles should already be in camera space. All that is left for
     * this function is perspective divide, determining visibility, shading
     * within the triangle itself, and updating our framebuffer.
     * @todo
     * - Future work probably implement foveated rendering if need be.
     * - FMA or see if you can do vector register ops for doing edge detection.
     * - Barycentric coordinates for shading.
     */

    // Perspective divide
    vec2_t v0 = {CAMERA_NEAR_PLANE * t0->v0.x / -t0->v0.z,
                 CAMERA_NEAR_PLANE * t0->v0.y / -t0->v0.z};
    vec2_t v1 = {CAMERA_NEAR_PLANE * t0->v1.x / -t0->v1.z,
                 CAMERA_NEAR_PLANE * t0->v1.y / -t0->v1.z};
    vec2_t v2 = {CAMERA_NEAR_PLANE * t0->v2.x / -t0->v2.z,
                 CAMERA_NEAR_PLANE * t0->v2.y / -t0->v2.z};

    // Convert to NDC [-1, 1]
    float a = CAMERA_UPPER_RIGHT_CORNER.x + CAMERA_LOWER_LEFT_CORNER.x;
    float b = CAMERA_UPPER_RIGHT_CORNER.y + CAMERA_LOWER_LEFT_CORNER.y;
    v0.x = 2 * v0.x / CAMERA_WIDTH - a / CAMERA_WIDTH;
    v0.y = 2 * v0.y / CAMERA_HEIGHT - b / CAMERA_HEIGHT;
    v1.x = 2 * v1.x / CAMERA_WIDTH - a / CAMERA_WIDTH;
    v1.y = 2 * v1.y / CAMERA_HEIGHT - b / CAMERA_HEIGHT;
    v2.x = 2 * v2.x / CAMERA_WIDTH - a / CAMERA_WIDTH;
    v2.y = 2 * v2.y / CAMERA_HEIGHT - b / CAMERA_HEIGHT;

    // Convert to raster space [0, 1] maxxed at height and width, with y inverted.
    v0.x = (v0.x + 1) / 2 * SCREEN_WIDTH;
    v0.y = (1 - v0.y) / 2 * SCREEN_HEIGHT;
    v1.x = (v1.x + 1) / 2 * SCREEN_WIDTH;
    v1.y = (1 - v1.y) / 2 * SCREEN_HEIGHT;
    v2.x = (v2.x + 1) / 2 * SCREEN_WIDTH;
    v2.y = (1 - v2.y) / 2 * SCREEN_HEIGHT;

    // Compute triangle bounding box
    uint16_t lp = (uint16_t)MAX(0.0f, MIN(v0.x, MIN(v1.x, v2.x)));
    uint16_t rp = (uint16_t)MIN(SCREEN_WIDTH - 1, ceilf(MAX(v0.x, MAX(v1.x, v2.x))));
    uint16_t bp = (uint16_t)MAX(0.0f, MIN(v0.y, MIN(v1.y, v2.y)));
    uint16_t tp = (uint16_t)MIN(SCREEN_HEIGHT - 1, ceilf(MAX(v0.y, MAX(v1.y, v2.y))));

    // Temp color 9, 20, 16
    color16_t c = 19088;

    // Edge detection given bounding box of triangle
    vec2_t E0 = {v1.x - v0.x, v1.y - v0.y};
    vec2_t E1 = {v2.x - v1.x, v2.y - v1.y};
    vec2_t E2 = {v0.x - v2.x, v0.y - v2.y};
    for (uint16_t j = bp; j <= tp; j++)
    {
        for (uint16_t i = lp; i <= rp; i++)
        {
            vec2_t P = {i + 0.5f, j + 0.5f};
            vec2_t V0_P = {P.x - v0.x, P.y - v0.y};
            vec2_t V1_P = {P.x - v1.x, P.y - v1.y};
            vec2_t V2_P = {P.x - v2.x, P.y - v2.y};

            // Vertices should be specified in CCW order, so to the right
            // of the vector should be (+)

            float e0_cross = V0_P.x * E0.y - V0_P.y * E0.x;
            float e1_cross = V1_P.x * E1.y - V1_P.y * E1.x;
            float e2_cross = V2_P.x * E2.y - V2_P.y * E2.x;
            if (e0_cross >= 0 && e1_cross >= 0 && e2_cross >= 0)
            {
                FRAMEBUFFER[j][i] = c;
            }
        }
    }
}