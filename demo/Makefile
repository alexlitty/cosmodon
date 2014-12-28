SOURCES=main.cpp
SRCPATH=
INCPATHS=../include/
LIBPATHS=../lib/linux64
OBJPATH=obj/demo/
BINPATH=bin/
LDFLAGS=-lcosmodon -lGL -lGLU -lGLEW -lglfw3 -lX11 -lXxf86vm -pthread -lXi -lXrandr
CFLAGS=-Wall -std=c++11

# Compilers
BG_WHITE=$$(tput setab 7)

# Foreground colors
FG_RED=$$(tput setaf 1)
FG_GREEN=$$(tput setaf 2)
FG_YELLOW=$$(tput setaf 3)
FG_BLUE=$$(tput setaf 4)
FG_MAGENTA=$$(tput setaf 5)
FG_CYAN=$$(tput setaf 6)

# Other colors
COLOR_RESET=$$(tput sgr 0)
 
# Goal-Based variables
GOAL = $(MAKECMDGOALS)
OBJECTS=$(SOURCES:%.cpp=%.o)
SOURCE_FILES=$(SOURCES:%=$(SRCPATH)%)
OBJECT_FILES=$(OBJECTS:%=$(OBJPATH)%)

# Compilers
CC_linux64=g++
CC_win32=/opt/mingw32/cross_win32/bin/i686-w64-mingw32-g++
CC = $(CC_$(GOAL))

INCFLAGS=$(foreach TMP,$(INCPATHS),-I$(TMP))
LIBFLAGS=$(foreach TMP,$(LIBPATHS),-L$(TMP))
BINARY_PREFIX=demo
BINARY=$(BINARY_PREFIX)_$(GOAL)

# Initial Target
$(GOAL): $(SOURCE_FILES) $(BINARY)
	@echo "$(BG_WHITE)$(FG_MAGENTA) Executing $(COLOR_RESET)"
	(cd bin && ./$(BINARY))
	@echo ""

# Link into a library
$(BINARY_PREFIX)_linux64: $(OBJECT_FILES)
	@echo "$(BG_WHITE)$(FG_GREEN) Linking $(COLOR_RESET)"
	mkdir -p $(dir $(BINPATH)$@)
	$(CC) $(OBJECT_FILES) $(LIBFLAGS) $(LDFLAGS) -o $(BINPATH)$@
	@echo ""

# Compile source into objects
$(OBJPATH)%.o: $(SRCPATH)%.cpp
	@echo "$(BG_WHITE)$(FG_BLUE) Compiling $< $(COLOR_RESET)"
	mkdir -p $(dir $@)
	$(CC) $(INCFLAGS) -c $< $(LIBFLAGS) $(LDFLAGS) $(CFLAGS) -o $@
	@echo ""
