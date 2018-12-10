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
	$(CXX) $(LDFLAGS) -o $(BINS_DIR)/$(PROG_NAME) $^

clean:
	rm -rf $(BINS_DIR) $(OBJS_DIR)/*.o

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

$(OBJS): | $(BINS_DIR)

$(BINS_DIR):
	mkdir $@

.PHONY: all clean
