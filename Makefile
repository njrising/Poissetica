
CC=g++
# CFLAGS
CFLAGS= -std=c++11 -lglew32s -lglfw3 -lopengl32 -lglu32 -lgdi32 
LINK=-LC:/GLFW_64/lib-mingw-w64 -LC:/GLEW/lib/Release/x64 
INC=-IC:/GLFW_64/include -IC:/GLEW/include -IC:/glm poissetica.cc

poissetica: poissetica.cc
	$(CC) $(INC) $(LINK) -o poissetica $(CFLAGS)