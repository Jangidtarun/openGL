#include "camera.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/io.hpp>

#include <iostream>


static float clamp(float value, float min_val, float max_val) {
	if (value < min_val) return min_val;
	if (value > max_val) return max_val;
	return value;
}


static glm::mat4 lookAt(glm::vec3 pos, glm::vec3 target, glm::vec3 worldup) {
	glm::vec3 cam_z	= glm::normalize(pos - target);
	glm::vec3 cam_x	= glm::normalize(glm::cross(worldup, cam_z));
	glm::vec3 cam_y	= glm::normalize(glm::cross(cam_z, cam_x));

	glm::mat4 rotation	= glm::mat4(1.0f);
	rotation[0][0]	= cam_x.x;
	rotation[1][0]	= cam_x.y;
	rotation[2][0]	= cam_x.z;

	rotation[0][1]	= cam_y.x;
	rotation[1][1]	= cam_y.y;
	rotation[2][1]	= cam_y.z;

	rotation[0][2]	= cam_z.x;
	rotation[1][2]	= cam_z.y;
	rotation[2][2]	= cam_z.z;

	glm::mat4 translation	= glm::mat4(1.0f);
	translation[3][0]		= -pos.x;
	translation[3][1]		= -pos.y;
	translation[3][2]		= -pos.z;

	glm::mat4 view	= rotation * translation;
	return view;
}


void update_cam_vecs(CAMERA *cam) {
	glm::vec3 front;

	front.x	= cos(glm::radians(cam->yaw)) * cos(glm::radians(cam->pitch));
	front.y = sin(glm::radians(cam->pitch));
	front.z = sin(glm::radians(cam->yaw)) * cos(glm::radians(cam->pitch));

	cam->front	= glm::normalize(front);
	cam->right 	= glm::normalize(glm::cross(cam->front, cam->worldup));
	cam->up		= glm::normalize(glm::cross(cam->right, cam->front));
}


CAMERA create_camera(
    glm::vec3 position,
    glm::vec3 up, 
    glm::vec3 front,
    float move_speed,
    float mouse_sensitivity,	
    float zoom,	
    float yaw,			
    float pitch
) {
	CAMERA cam;
	cam.position	= position;
	cam.front		= front;
	cam.worldup		= up;
	cam.yaw			= yaw;
	cam.pitch		= pitch;
	cam.move_speed	= move_speed;
	cam.mouse_sensitivity	= mouse_sensitivity;
	cam.zoom		= zoom;
	update_cam_vecs(&cam);
	return cam;
}


glm::mat4 get_view_matrix(CAMERA *cam) {
	return lookAt(cam->position, cam->position + cam->front, cam->up);
}


void get_cam_keyboard_input(CAMERA *cam, CAMERA_MOVEMENTS direction, float delta_time) {
    float velocity = cam->move_speed * delta_time;
    if (direction == FORWARD) {
        cam->position += cam->front * velocity;
    }
    if (direction == BACKWARD) {
        cam->position -= cam->front * velocity;
    }
    if (direction == LEFT) {
        cam->position -= cam->right * velocity;
    }
    if (direction == RIGHT) {
        cam->position += cam->right * velocity;
    }
}


void get_cam_mouse_input(CAMERA *cam, float xoffset, float yoffset, bool constrain_pitch) {
    xoffset *= cam->mouse_sensitivity;
    yoffset *= cam->mouse_sensitivity;

    cam->yaw	+= xoffset;
    cam->pitch	+= yoffset;

    if (constrain_pitch) {
		cam->pitch = clamp(cam->pitch, -PITCH_CONSTRAIN, PITCH_CONSTRAIN);
    }

    update_cam_vecs(cam);
}


void get_cam_mouse_scroll(CAMERA *cam, float yoffset) {
    cam->zoom -= yoffset;
    cam->zoom = clamp(cam->zoom, ZOOM_MIN, ZOOM_MAX);
}
