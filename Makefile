CXX=g++

CXXFLAGS=-Wall -Iinclude
LDFLAGS=-lGL -lGLEW -lglfw

SRCS_DIR=src
OBJS_DIR=obj
BINS_DIR=bin

OBJS_CLEAN=main.o shader.o
OBJS=$(patsubst %,$(OBJS_DIR)/%,$(OBJS_CLEAN))

PROG_NAME=prog

all: $(OBJS)
	mkdir -p $(BINS_DIR)
	$(CXX) $(LDFLAGS) -o $(BINS_DIR)/$(PROG_NAME) $^

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY clean:

clean:
	rm -rf $(BINS_DIR) $(OBJS_DIR)/*.o
