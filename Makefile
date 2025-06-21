CFLAGS = -Wall
LIBS = -lglfw -lGL -ldl -Iinclude -lm
SRC = main.cpp
OUT = main
CC = g++
GLAD = src/glad.c


$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(GLAD) $(LIBS) -o $(OUT)

clean:
	rm -f $(OUT)
