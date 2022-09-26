CXX=g++
CFLAGS=-I.
CXXFLAGS += -g -std=c++11 -Wall -Wextra -pedantic-errors
LDLIBS+= -L/usr/lib/x86_64-linux-gnu -lstdc++ -lGL -lGLU -lglut -lSDL2 -lfreeimage

# find cpp files in subdirectories
SOURCES = $(shell find . -name '*.cpp' -o -name '*.c')
# find headers
HEADERS = $(shell find . -name '*.h' -o -name '*.hpp')

OUTPUT = scale

all: $(OUTPUT)

$(OUTPUT): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(OUTPUT) $(SOURCES) $(LDLIBS)

clean:
	$(RM) $(OUTPUT)