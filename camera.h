#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum CAMERA_MOVEMENTS {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// default camera values
const float YAW				= -90.0f;
const float PITCH			=   0.0f;
const float SPEED			=	5.0f;
const float SENSITIVITY		=	0.1f;
const float ZOOM			=  45.0f;
const float PITCH_CONSTRAIN	=  89.0f;
const float ZOOM_MIN		=	1.0f;
const float ZOOM_MAX		=  45.0f;

typedef struct {
	// camera attributes
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldup;

	// euler angles
	float yaw;
	float pitch;

	// camera options
	float move_speed;
	float mouse_sensitivity;
	float zoom;
} CAMERA;


void update_cam_vecs(CAMERA *cam);
CAMERA create_camera(
		glm::vec3 position	= glm::vec3(0.0f, 0.0f,  3.0f),
		glm::vec3 up		= glm::vec3(0.0f, 1.0f,  0.0f),
		glm::vec3 front		= glm::vec3(0.0f, 0.0f, -1.0f),
		float move_speed	= SPEED,
		float mouse_sensitivity	= SENSITIVITY,
		float zoom			= ZOOM,
		float yaw			= YAW,
		float pitch			= PITCH
		);	

glm::mat4 get_view_matrix(CAMERA *cam);
void get_cam_keyboard_input(CAMERA *cam, CAMERA_MOVEMENTS direction, float delta_time);
void get_cam_mouse_input(CAMERA *cam, 
		float xoffset, 
		float yoffset, 
		bool constrain_pitch = true
		); 

void get_cam_mouse_scroll(CAMERA *cam, float yoffset);

#endif
