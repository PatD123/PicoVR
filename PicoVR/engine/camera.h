/**
 * @brief
 * File header for camera constants and structs
 */

#ifndef ENGINE_CAMERA
#define ENGINE_CAMERA

#include "engine/math.h"
#include "engine/utils.h"
#include "engine/primitives.h"

// Camera globals (temporary)
const static vec4_t CAMERA_POS = {0.0f, 0.0f, 0.0f, 1.0f};
const static vec4_t CAMERA_FORWARD = {0.0f, 0.0f, -1.0f, 0.0f};
const static vec4_t CAMERA_UP = {0.0f, 1.0f, 0.0f, 0.0f};
const static vec4_t CAMERA_RIGHT = {1.0f, 0.0f, 0.0f, 0.0f};

typedef struct Camera_t
{

    /**
     * @brief Camera
     * Camera class is mainly used for view transform which consists of
     * 1) A translation to the camera position.
     * 2) A remapping (rotation) of our world frame to our new cam frame.
     * @details
     * Our translation matrix is made from the position vector of our camera.
     * Our rotation matrix is made from the the forward, up, and right
     * coordinate axes that respecify what our camera x, y, z axes are.
     *
     * @note MAKE SURE THAT THE CAM COORD AXES ARE NORMALIZED!
     */

    vec4_t p;
    vec4_t d;
    vec4_t r;
    vec4_t u;

} Camera_t;

void camera_init(Camera_t *cam);

mat4_t get_view_mat(const Camera_t *cam);

#endif
