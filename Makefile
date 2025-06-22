CFLAGS 	= -Wall
LIBS 	= -lglfw -lGL -ldl -Iinclude -lm
SRC 	= main.cpp
OUT 	= main
CC 		= g++
GLAD 	= src/glad.c
CAMERA	= camera.cpp
DEPEN	= camera.h texture.h shader.h

$(OUT): $(SRC) $(DEPEN)
	$(CC) $(CFLAGS) $(SRC) $(CAMERA) $(GLAD) $(LIBS) -o $(OUT)

clean:
	rm -f $(OUT)
