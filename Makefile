CFLAGS = -Wall
LIBS = -lglfw -lGL -ldl -Iinclude -lm
SRC = main.c
OUT = main
CC = gcc
GLAD = src/glad.c


$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(GLAD) $(LIBS) -o $(OUT)


clean:
	rm -f $(OUT)
