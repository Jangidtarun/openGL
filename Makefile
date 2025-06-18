CFLAGS = -Wall
<<<<<<< HEAD
LIBS = -lglfw -lGL -ldl -Iinclude -lm
SRC = main.c
OUT = main
CC = gcc
GLAD = src/glad.c


$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(GLAD) $(LIBS) -o $(OUT)

=======
LIBS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -Iinclude
SRC = main.cpp
GLAD = src/glad.c
STBI = stb_image.cpp
OUT = main
CC = g++

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(STBI) $(GLAD) -o $(OUT) $(LIBS)

run:
	./$(OUT)
>>>>>>> origin/main

clean:
	rm -f $(OUT)
