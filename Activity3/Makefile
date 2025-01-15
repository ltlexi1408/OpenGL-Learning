# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -I/usr/include

# Libraries
LIBS = -lglfw -lGLEW -lGL

# Target executable
TARGET = window

# Source files
SRCS = main.cpp

# Object files (replace .cpp with .o)
OBJS = $(SRCS:.cpp=.o)

# Build rules
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
