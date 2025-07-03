# Compiler and flags
CXX     := g++
CXXFLAGS:= -Wall -Iinclude

# Libraries to link
LDLIBS  := -lglfw -lGL -ldl -lm -lassimp

# Output file
TARGET  := main

# Source files
SRCS := \
    main.cpp \
    camera/camera.cpp \
    light/light.cpp \
    shader/shader.cpp \
    helper/stringlib.cpp \
    model/model.cpp \
    mesh/mesh.cpp \
    src/stb_image.cpp \
	texture/texture.cpp \
    src/glad.c

# Object files (replace .cpp and .c with .o)
OBJS := $(SRCS:.cpp=.o)
OBJS := $(OBJS:.c=.o)

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ $(LDLIBS) -o $@

# Compile .cpp to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile .c to .o
%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean

