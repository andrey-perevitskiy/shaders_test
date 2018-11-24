CXX=g++

CXXFLAGS=-Wall
LDFLAGS=-lGL -lGLEW -lglfw

BINS_DIR=bin

OBJS=main.o

PROG_NAME=prog

all: obj/$(OBJS)
	mkdir -p $(BINS_DIR)
	$(CXX) $(LDFLAGS) -o $(BINS_DIR)/$(PROG_NAME) $^

obj/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY clean:

clean:
	rm -rf $(BINS_DIR) $(OBJS_DIR)/*.o
