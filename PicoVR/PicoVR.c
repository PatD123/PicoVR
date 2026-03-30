#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "engine/primitives.h"
#include "engine/math.h"

int main()
{
    stdio_init_all();

    // Have to wait for some time to get UART set up.
    sleep_ms(2000);

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
    vec3_t v0 = {0.0f, 0.0f, -2.0f};
    vertex32_t v1 = {4.0f, 0.0f, -2.0f};
    vertex32_t v2 = {2.0f, 2.0f, -2.0f};
    triangle32_t t = {v0, v1, v2};
    mat4_t m;
    printf("v1 * v2 = %f \n", dot3(&v1, &v2));
    printf("%f %f %f %f\n", m.r0[0], m.r0[1], m.r0[2], m.r0[3]);

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
     * Given that this is a VR application, hopefully I can integrate
     * multiple players connected over Bluetooth or WiFi. But not yet
     * though.

        // Initialise the Wi-Fi chip
        if (cyw43_arch_init())
        {
            printf("Wi-Fi init failed\n");
            return -1;
        }

        // Enable wifi station
        cyw43_arch_enable_sta_mode();

        printf("Connecting to Wi-Fi...\n");
        if (cyw43_arch_wifi_connect_timeout_ms("Your Wi-Fi SSID", "Your Wi-Fi Password", CYW43_AUTH_WPA2_AES_PSK, 30000))
        {
            printf("failed to connect.\n");
            return 1;
        }
        else
        {
            printf("Connected.\n");
            // Read the ip address in a human readable way
            uint8_t *ip_address = (uint8_t *)&(cyw43_state.netif[0].ip_addr.addr);
            printf("IP address %d.%d.%d.%d\n", ip_address[0], ip_address[1], ip_address[2], ip_address[3]);
        }

        while (true)
        {
            printf("Hello, world!\n");
            sleep_ms(1000);
        }
    */
}
