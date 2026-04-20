#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "engine/primitives.h"
#include "engine/math.h"
#include "engine/utils.h"
#include "engine/camera.h"
#include "engine/rasterize.h"
#include "engine/globals.h"

int main()
{
    stdio_init_all();

    // Have to wait for some time to get UART set up.
    sleep_ms(4000);

    setvbuf(stdout, NULL, _IONBF, 0);

    // TODO
    // 1) Initialize both cores
    // 2) Initialize a global vars
    // 3) Loop (w.r.t. my previous OpenGL stuff)
    //      Update camera
    //      Process inputs
    //      Transform vertices
    //      Rasterization
    //          What triangles are seen vs occluded.
    //          Shading those pixels that represent a visible triangle.

    /**
     * @note Coordinate System
     * Follow RHR. Camera points down -z. Thumb is x. Index is y. Middle is z.
     *
     * @note Winding order
     * Always list vertices in CCW order. Pretend you are looking at the triangle
     * face on, then list them in CCW winding order.
     */

    /** @todo Maybe move these to global constants. Maybe put them in SRAM all the time
     * because we will most likely transform these guys a lot. Caching here should be
     * important.
     */

    vec3_t v0 = {-5.0f, 10.0f, -1.0f};
    vertex32_t v1 = {5.0f, 10.0f, -1.0f};
    vertex32_t v2 = {0.0f, 17.0f, -1.0f};
    vec4_t v3 = {1.0f, 2.0f, 3.0f, 4.0f};
    triangle32_t t = {v0, v1, v2};
    mat4_t m = {{{2.0f, 1.0f, 1.0f, 1.0f},
                 {1.0f, 2.0f, 1.0f, 1.0f},
                 {1.0f, 1.0f, 2.0f, 1.0f},
                 {1.0f, 1.0f, 1.0f, 2.0f}}};
    Camera_t cam;
    camera_init(&cam);
    mat4_t view_mat = get_view_mat(&cam);
    memset(&FRAMEBUFFER[0][0], 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(uint16_t));
    // printf("RASTERIZING\n");
    rasterize(&t);
    printf("P3\n");
    printf("%i %i\n", SCREEN_WIDTH, SCREEN_HEIGHT);
    printf("31\n");
    int cnt = 0;
    for (uint16_t i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (uint16_t j = 0; j < SCREEN_WIDTH; j++)
        {
            // if (FRAMEBUFFER[i][j] != 0)
            // {
            uint8_t r = (FRAMEBUFFER[i][j] >> 11) & 0x1F;
            uint8_t g = (FRAMEBUFFER[i][j] >> 5) & 0x3F;
            uint8_t b = FRAMEBUFFER[i][j] & 0x1F;
            printf("%u %u %u\n", r, g, b);
            sleep_ms(10);
            // }
        }
    }
    fflush(stdout);

    // // Default blink script for debugging
    // if (cyw43_arch_init())
    // {
    //     printf("Wi-Fi init failed");
    //     return -1;
    // }

    // while (true)
    // {
    //     cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    //     sleep_ms(250);
    //     cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    //     sleep_ms(250);
    // }

    /**
     * @note From https://stackoverflow.com/questions/1674005/fast-4x4-matrix-multiplication-in-c
     * - "Don't inline the function. Your matrix multiplication generates quite a bit of code as it's unrolled,
     *    and the ARM only has a very tiny instruction cache. Excessive inlining can make your code slower
     *    because the CPU will be busy loading code into the cache instead of executing it."
     * - "Use the restrict keyword to tell the compiler that the source- and destination pointers don't overlap
     *    in memory. Currently the compiler is forced to reload every source value from memory whenever a result
     *    is written because it has to assume that source and destination may overlap or even point to the same
     *    memory."
     */
}
