# Makefile Definitions
include makedefs

# Name of the project
PROJ_NAME = Main

# Paths to other makefiles
ACTIVITIES_MAKEFILE := $(SRC)/Activities/makefile
GRAPH_MAKEFILE := $(SRC)/Graph/makefile
MAIN_MAKEFILE := $(SRC)/makefile

# Compiler and linker
CC = g++

# Command used at clean target
RM = rm -rf

# Default target
all: build

# Object files
OBJ = $(OBJDIR)/Main.o $(wildcard $(OBJDIR)/*.o)

# Creates Main executable
$(PROJ_NAME): $(OBJ)
	@echo 'Building binary using GCC linker: $@'
	$(CC) $^ -o $@
	@echo 'Finished building binary: $@'
	@echo ' '

build: compileSource
	@$(MAKE) -s $(PROJ_NAME)

compileSource:
	@mkdir -p $(OBJDIR)
	@$(MAKE) -s -C $(SRC)/Graph -f $(GRAPH_MAKEFILE)
	@$(MAKE) -s -C $(SRC)/Activities -f $(ACTIVITIES_MAKEFILE)
	@$(MAKE) -s -C $(SRC) -f $(MAIN_MAKEFILE)

clean:
	@$(MAKE) -s -C $(SRC)/Activities -f $(ACTIVITIES_MAKEFILE) clean
	@$(MAKE) -s -C $(SRC)/Graph -f $(GRAPH_MAKEFILE) clean
	@rm -rf $(PROJ_NAME) $(OBJDIR) *~

.PHONY: all clean
