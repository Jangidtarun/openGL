OUT		= main
SRC		= main.cpp
CC		= g++
GLAD 	= ../src/glad.c
LIBS	= -lGL -ldl -lglfw -I../include
CFLAGS	= -Wall
DEPEN	= 


$(OUT) : $(SRC) $(DEPEN)
	$(CC) $(SRC) $(LIBS) $(GLAD) $(CFLAGS) -o $(OUT)


.PHONY: clean
clean:
	rm -f main
