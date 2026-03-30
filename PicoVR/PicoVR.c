#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "engine/engine_globals.h"

int main()
{
    stdio_init_all();

    vertex32_t v;
    v.x = 0.0f;
    v.y = 0.0f;
    v.z = 6.9f;

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

    // Default blink script for debugging
    if (cyw43_arch_init())
    {
        printf("Wi-Fi init failed");
        return -1;
    }

    while (true)
    {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        sleep_ms(250);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        sleep_ms(250);
        printf("Vertex v: %f, %f, %f", v.x, v.y, v.z);
    }

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
