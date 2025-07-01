CFLAGS 	= -Wall
LIBS 	= -lglfw -lGL -ldl -Iinclude -lm
SRC 	= main.cpp
OUT 	= main
CC 		= g++
GLAD 	= src/glad.c

CAMERA_SRC	= camera/camera.cpp
CAMERA_HEAD	= camera/camera.h

LIGHT_SRC	= light/light.cpp
LIGHT_HEAD	= light/light.h

SHADER_SRC	= shader/shader.cpp
SHADER_HEAD	= shader/shader.h

TEXTURE_HEAD	= texture/texture.h
MATERIALS_HEAD	= materials/materials.h

STRINGLIB_HEAD = helper/stringlib.h
STRINGLIB_SRC = helper/stringlib.cpp

DEPENDENCIES		= $(CAMERA_HEAD) $(LIGHT_HEAD) $(SHADER_HEAD) $(MATERIALS_HEAD) $(TEXTURE_HEAD) $(STRINGLIB_HEAD)
DEPENDENCIES_SRC	= $(CAMERA_SRC) $(LIGHT_SRC) $(SHADER_SRC) $(STRINGLIB_SRC)

$(OUT): $(SRC) $(DEPENDENCIES) $(DEPENDENCIES_SRC)
	$(CC) $(CFLAGS) $(SRC) $(DEPENDENCIES_SRC) $(GLAD) $(LIBS) -o $(OUT)

clean:
	rm -f $(OUT)
