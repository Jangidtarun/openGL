CFLAGS 	= -Wall
LIBS 	= -lglfw -lGL -ldl -Iinclude -lm
SRC 	= main.cpp
OUT 	= main
CC 		= g++
GLAD 	= src/glad.c
DEPEN_SRC	= camera.cpp shader.cpp light.cpp
DEPEN	= camera.h texture.h shader.h materials.h light.h

$(OUT): $(SRC) $(DEPEN)
	$(CC) $(CFLAGS) $(SRC) $(DEPEN_SRC) $(GLAD) $(LIBS) -o $(OUT)

clean:
	rm -f $(OUT)
