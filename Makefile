CFLAGS = -Wall
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

clean:
	rm -f $(OUT)
