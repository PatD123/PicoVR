/**
 * @brief
 * This header file lists the global structs that are needed by the engine in
 * rasterization and other math operations.
 */

/**
 * @brief vertex32_t
 *
 * Struct vertex32_t contains information regarding the
 * x, y, z coordinates representing this vertex.
 *
 * @details
 * According to the RP2350 datasheet (pg 124), it says that the the float
 * type in C automatically uses the FPU on the chip. It also says the FPU
 * has 32 32-bit single-precision registers or 16 64-bit double-precision
 * registers (pg 128).
 *
 */
typedef struct vertex32_t
{
    float x;
    float y;
    float z;
} vertex32_t;

/**
 * @brief triangle32_t
 *
 * Struct triangle32_t contains information regarding the vertices
 * of the triangle and it's colors.
 *
 * @details
 * The triangle's vertices consist of the vertex32_t defined in this file.
 * As a result, each of the triangle's vertices also consist of floats.
 *
 */
typedef struct triangle32_t
{
    vertex32_t v0;
    vertex32_t v1;
    vertex32_t v2;
} triangle32_t;
