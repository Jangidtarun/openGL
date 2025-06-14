CFLAGS = -Wall
LIBS = -lglfw -lGL -Iinclude
SRC = main.cpp
GLAD = src/glad.c
OUT = main.out
CC = g++

$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(GLAD) -o $(OUT) $(LIBS)

clean:
	rm -f $(OUT)