#include "camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


static float clamp(float value, float min_val, float max_val) {
	if (value < min_val) return min_val;
	if (value > max_val) return max_val;
	return value;
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
	return glm::lookAt(cam->position, cam->position + cam->front, cam->up);
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
        if (cam->pitch > PITCH_CONSTRAIN)
            cam->pitch = PITCH_CONSTRAIN;
        if (cam->pitch < -PITCH_CONSTRAIN)
            cam->pitch = -PITCH_CONSTRAIN;
    }

    update_cam_vecs(cam);
}


void get_cam_mouse_scroll(CAMERA *cam, float yoffset) {
    cam->zoom -= yoffset;
    cam->zoom = clamp(cam->zoom, ZOOM_MIN, ZOOM_MAX);
}
