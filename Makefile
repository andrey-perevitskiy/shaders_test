CXX = g++
CXXFLAGS = -Wall -Wextra -Wno-unused-parameter -Iinclude
LDFLAGS = -lGL -lGLEW -lglfw
SRCDIR = src
OBJDIR = obj
BINDIR = bin
OBJS = $(patsubst %,$(OBJDIR)/%,main.o shader.o)

.PHONY: all
all: $(BINDIR)/prog

$(BINDIR)/prog: $(OBJS) | $(BINDIR)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $^ -o $@

$(OBJDIR):
	mkdir $@

$(BINDIR):
	mkdir $@

.PHONY: clean
clean:
	rm -rf $(BINDIR) $(OBJDIR)
