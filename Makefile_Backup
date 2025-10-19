# ===========================
# Project Configuration
# ===========================
CXX       := g++
CXXFLAGS  := -Wall -Wextra -std=c++17 -MMD -MP \
             -Iengine/include -Ivendor/raylib/include -Ivendor/json/include -Igame/include

LDFLAGS   := -Lvendor/raylib/lib -Lengine/lib 
LDLIBS    := -lengine -lraylib -lm -lpthread -ldl

BIN_DIR   := bin
OBJ_DIR   := $(BIN_DIR)/obj
DEP_DIR   := $(BIN_DIR)/dep
ENGINE_LIB_DIR := engine/lib

ENGINE_LIB := $(ENGINE_LIB_DIR)/libengine.a
GAME_BIN   := $(BIN_DIR)/game

# ===========================
# Sources
# ===========================

# Engine sources
ENGINE_SRC := $(shell find engine/src -name '*.cpp')
ENGINE_OBJ := $(ENGINE_SRC:engine/src/%.cpp=$(OBJ_DIR)/engine/%.o)
ENGINE_DEP := $(ENGINE_OBJ:.o=.d)

# Game sources
# main.cpp is now directly under game/
GAME_MAIN := game/main.cpp

# Other game sources remain under game/src/
GAME_SRC := $(shell find game/src -name '*.cpp')

# Combine all game source files
ALL_GAME_SRC := $(GAME_MAIN) $(GAME_SRC)

# Object files for game
GAME_OBJ := $(GAME_MAIN:game/%.cpp=$(OBJ_DIR)/game/%.o) \
            $(GAME_SRC:game/src/%.cpp=$(OBJ_DIR)/game/%.o)

GAME_DEP := $(GAME_OBJ:.o=.d)

# ===========================
# Default Target
# ===========================
.PHONY: all engine game clean rebuild run test

all: engine game

# ===========================
# Engine Build
# ===========================
engine: $(ENGINE_LIB)

$(ENGINE_LIB): $(ENGINE_OBJ)
	@mkdir -p $(ENGINE_LIB_DIR)
	@echo "Archiving Engine -> $@"
	ar rcs $@ $^

$(OBJ_DIR)/engine/%.o: engine/src/%.cpp
	@mkdir -p $(dir $@)
	@echo "Compiling Engine -> $<"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ===========================
# Game Build
# ===========================
game: engine $(GAME_BIN)

$(GAME_BIN): $(GAME_OBJ)
	@echo "Linking Game -> $@"
	$(CXX) $^ $(LDFLAGS) $(LDLIBS) -o $@

# Compile main.cpp directly under game/
$(OBJ_DIR)/game/%.o: game/%.cpp
	@mkdir -p $(dir $@)
	@echo "Compiling Game (root) -> $<"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile all other game sources under game/src/
$(OBJ_DIR)/game/%.o: game/src/%.cpp
	@mkdir -p $(dir $@)
	@echo "Compiling Game -> $<"
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ===========================
# Dependencies
# ===========================
-include $(ENGINE_DEP) $(GAME_DEP)

# ===========================
# Run
# ===========================
run: game
	@echo "Running game..."
	./$(GAME_BIN)

# ===========================
# Clean & Rebuild
# ===========================
clean:
	@echo "Cleaning build files..."
	rm -rf $(BIN_DIR) $(ENGINE_LIB_DIR)

rebuild: clean all

# ===========================
# Tests
# ===========================
test:
	@echo "Running tests..."
	@echo "TODO: Implement test runner"
