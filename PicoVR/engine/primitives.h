/**
 * @brief
 * This header file lists the global structs that are needed by the engine in
 * rasterization and other math operations.
 */

#ifndef ENGINE_PRIMITIVES
#define ENGINE_PRIMITIVES

typedef struct vec3_t
{

    /**
     * @brief vec3_t (heterogeneous)
     *
     * Struct vec3_t contains information regarding the
     * x, y, z coordinates representing this vector.
     *
     * @details
     * According to the RP2350 datasheet (pg 124), it says that the the float
     * type in C automatically uses the FPU on the chip. It also says the FPU
     * has 32 32-bit single-precision registers or 16 64-bit double-precision
     * registers (pg 128).
     *
     */

    float x;
    float y;
    float z;
} vec3_t;

/** @brief vec3_t and vertex32_t are interchangeable. It purely depends on the context you are in. */
typedef vec3_t vertex32_t;

typedef struct vec4_t
{

    /**
     * @brief vec4_t (homogeneous)
     *
     * Struct vec4_t contains information regarding the
     * x, y, z, w coordinates representing this vertex.
     *
     * @details
     * According to the RP2350 datasheet (pg 124), it says that the the float
     * type in C automatically uses the FPU on the chip. It also says the FPU
     * has 32 32-bit single-precision registers or 16 64-bit double-precision
     * registers (pg 128).
     *
     */

    float x;
    float y;
    float z;
    float w;
} vec4_t;

typedef struct triangle32_t
{

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

    vertex32_t v0;
    vertex32_t v1;
    vertex32_t v2;
} triangle32_t;

typedef union mat4_t
{

    /**
     * @brief mat4_t
     *
     * Struct mat4_t provides data for a 4x4 matrix. Each element
     * is a 32-bit float.
     *
     * @details
     * The m member field specifies the underlying matrix itself. The
     * m_flat provides another view of the underlying values.
     *
     */

    float m[4][4];
    float m_flat[16];
} mat4_t;

#endif
