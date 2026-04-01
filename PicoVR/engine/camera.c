#include "engine/camera.h"

void camera_init(Camera_t *cam)
{

    /**
     * @brief camera_init
     * Given a pointer to an already declared Camera_t, we initialize
     * all of its inner data such as position and camera coordinate axes.
     */

    cam->p = CAMERA_POS;
    cam->d = CAMERA_FORWARD;
    cam->r = CAMERA_RIGHT;
    cam->u = CAMERA_UP;
    return;
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
     *          lookAt = rot_mat * transl_mat
     *          rot_mat =    [[R_x, U_x, D_x, 0],
     *                        [R_x, U_x, D_x, 0],
     *                        [R_x, U_x, D_x, 0],
     *                        [R_x, U_x, D_x, 1]]
     *          transl_mat = [[1, 0, 0, -P.x],
                              [0, 1, 0, -P.y],
                              [0, 0, 1, -P.z],
                              [0, 0, 0,  1]]
     * where each mat is column-major.
     */

    mat4_t view_mat = {{cam->r.x, cam->u.x, cam->d.x, 0},
                       {cam->r.x, cam->u.x, cam->d.x, 0},
                       {cam->r.x, cam->u.x, cam->d.x, 0},
                       {0.0f, 0.0f, 0.0f, 1}};
    view_mat.m[0][3] = dot3((vec3_t *)&view_mat.m[0], &(vec3_t){-cam->p.x, -cam->p.y, -cam->p.z});
    view_mat.m[1][3] = dot3((vec3_t *)&view_mat.m[1], &(vec3_t){-cam->p.x, -cam->p.y, -cam->p.z});
    view_mat.m[2][3] = dot3((vec3_t *)&view_mat.m[2], &(vec3_t){-cam->p.x, -cam->p.y, -cam->p.z});
    view_mat.m[3][3] = dot3((vec3_t *)&view_mat.m[3], &(vec3_t){-cam->p.x, -cam->p.y, -cam->p.z});
    return view_mat;
}