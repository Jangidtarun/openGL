CFLAGS = -Wall
LIBS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -Iinclude
SRC = main.cpp
GLAD = src/glad.c
OUT = main
CC = g++

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(GLAD) -o $(OUT) $(LIBS)

clean:
	rm -f $(OUT)
