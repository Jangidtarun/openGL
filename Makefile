CFLAGS 	= -Wall
LIBS 	= -lglfw -lGL -ldl -Iinclude -lm
SRC 	= main.cpp
OUT 	= main
CC 		= g++
GLAD 	= src/glad.c
DEPEN	= camera.h texture.h shader.h sphere.h
DEPEN_SRC	= camera.cpp sphere.cpp

$(OUT): $(SRC) $(DEPEN)
	$(CC) $(CFLAGS) $(SRC) $(DEPEN_SRC) $(GLAD) $(LIBS) -o $(OUT)

clean:
	rm -f $(OUT)
