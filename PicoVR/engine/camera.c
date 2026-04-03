#include "engine/camera.h"

void camera_init(Camera_t *cam)
{

    /**
     * @brief camera_init
     * Given a pointer to an already declared Camera_t, we initialize
     * all of its inner data such as position and camera coordinate axes.
     */

    cam->p = CAMERA_POS;
    cam->d = normalize(&CAMERA_FORWARD);
    vec3_t cam_r = cross(&CAMERA_UP, &CAMERA_FORWARD);
    cam->r = normalize(&cam_r);
    vec3_t cam_u = cross(&CAMERA_FORWARD, &cam->r);
    cam->u = normalize(&cam_u);
}

mat4_t get_view_mat(const Camera_t *cam)
{

    /**
     * @brief get_view_mat
     * Function that, when called given a pointer to a camera, returns
     * the camera's according view matrix.
     * @details
     * A camera's view matrix is computed by translating, then rotating
     * the world's coordinate frame to the camera's new coordinate frame.
     * As a result, we have
     *          view_mat = rot_mat * transl_mat
     *          transl_mat = [[1, 0, 0, -P.x],
                              [0, 1, 0, -P.y],
                              [0, 0, 1, -P.z],
                              [0, 0, 0,  1]]
                rot_mat =    [[R_x, R_y, R_z, 0],
     *                        [U_x, U_y, U_z, 0],
     *                        [D_x, D_y, D_z, 0],
     *                        [0, 0, 0, 1]]
     * We translate first to the eye location, then rotate around our new center.
     * Let's say we rotated first. If we rotated first, then our translation would
     * be using our new rotated axes, when our original translation is based on our
     * original world frame. As a result, we translate along our original frame axes,
     * then we rotate around our new world frame (rotating around new origin).s
     */

    mat4_t view_mat = {
        .m = {{cam->r.x, cam->r.y, cam->r.z, 0.0f},
              {cam->u.x, cam->u.y, cam->u.z, 0.0f},
              {cam->d.x, cam->d.y, cam->d.z, 0.0f},
              {0.0f, 0.0f, 0.0f, 1.0f}}};
    view_mat.m[0][3] = dot3((vec3_t *)&view_mat.m[0], &(vec3_t){-cam->p.x, -cam->p.y, -cam->p.z});
    view_mat.m[1][3] = dot3((vec3_t *)&view_mat.m[1], &(vec3_t){-cam->p.x, -cam->p.y, -cam->p.z});
    view_mat.m[2][3] = dot3((vec3_t *)&view_mat.m[2], &(vec3_t){-cam->p.x, -cam->p.y, -cam->p.z});
    return view_mat;
}