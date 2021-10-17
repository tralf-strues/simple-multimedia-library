# -----------------------------------Constants----------------------------------
AllWarnings    = -Wall -Wextra -pedantic
SomeWarnings   = -Wall -Wextra
LittleWarnings = -Wall
NoWarnings     = 
# -----------------------------------Constants----------------------------------

Mode = RELEASE_MODE
# ----------------------------------Debug-mode----------------------------------
ifeq ($(Mode), DEBUG_MODE)
	ModeLinkerOptions   = -g -fsanitize=address -fno-optimize-sibling-calls
	ModeCompilerOptions = -O0 -g -fsanitize=address -fno-optimize-sibling-calls
endif
# ----------------------------------Debug-mode----------------------------------

# ---------------------------------Release-mode---------------------------------
ifeq ($(Mode), RELEASE_MODE)
	ModeLinkerOptions   = 
	ModeCompilerOptions = -O3
endif
# ---------------------------------Release-mode---------------------------------

# ------------------------------------Options-----------------------------------
LIBS = sdl2 sdl2_ttf sdl2_image

CXX = clang++

LXXFLAGS = $(shell pkg-config --libs $(LIBS)) $(ModeLinkerOptions)
CXXFLAGS = $(shell pkg-config --cflags $(LIBS)) $(ModeCompilerOptions) $(AllWarnings) -std=c++17
# ------------------------------------Options-----------------------------------

# -------------------------------------Files------------------------------------
Program = ray_tracer

IncludeDir = include
SrcDir     = src
BinDir     = bin
IntDir     = $(BinDir)/intermediates

Deps   = $(wildcard $(IncludeDir)/*.h) $(wildcard $(IncludeDir)/**/*.h)
CppSrc = $(notdir $(wildcard $(SrcDir)/*.cpp) $(wildcard $(SrcDir)/**/*.cpp))

Objs = $(addprefix $(IntDir)/, $(CppSrc:.cpp=.o))

OutputDir  = sml
OutputFile = sml.a
# -------------------------------------Files------------------------------------

# ----------------------------------Make rules----------------------------------
.PHONY: install
ifneq ($(OutputPrefix),)
install: init build
	mkdir -p $(OutputPrefix)/$(OutputDir)
	mkdir -p $(OutputPrefix)/$(OutputDir)
	cp $(BinDir)/$(OutputFile) $(OutputPrefix)/$(OutputDir)
	cp -a $(IncludeDir)/. $(OutputPrefix)/$(OutputDir)
else
install:
	@echo "[ERROR] Output directory not specified!"
endif

.PHONY: build
build: $(Objs) $(Deps)
	ar ru $(BinDir)/$(OutputFile) $(Objs)

vpath %.cpp $(SrcDir) $(wildcard $(SrcDir)/**/)
$(IntDir)/%.o: %.cpp $(Deps)
	$(CXX) -I $(IncludeDir) -c $< $(CXXFLAGS) -o $@

.PHONY: init
init:
	mkdir -p bin/intermediates

.PHONY: clean
clean:
	rm -f $(Objs) $(Exec)
# ----------------------------------Make rules----------------------------------