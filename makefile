# Variables generales
CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -Werror -fPIC
BUILD_DIR := build
BIN_DIR := bin

# Archivos fuente comunes (sin main.cpp)
SRC_FILES := $(shell find Ej2 Ej3 Ej4 utils -name '*.cpp' ! -name 'main.cpp')
OBJ_FILES := $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES))

# Archivos por ejercicio
MAIN_EJ2 := Ej2/main.cpp
MAIN_EJ3 := Ej3/main.cpp
MAIN_EJ4 := Ej4/main.cpp
MAIN_GENERAL := main.cpp

# Objetos filtrados por módulo
OBJ_EJ2 := $(filter $(BUILD_DIR)/Ej2/%, $(OBJ_FILES))
OBJ_EJ3 := $(filter $(BUILD_DIR)/Ej3/%, $(OBJ_FILES))
OBJ_EJ4 := $(filter $(BUILD_DIR)/Ej4/%, $(OBJ_FILES))
OBJ_UTILS := $(filter $(BUILD_DIR)/utils/%, $(OBJ_FILES))

# Ejecutables
BIN_EJ2 := $(BIN_DIR)/ej2
BIN_EJ3 := $(BIN_DIR)/ej3
BIN_EJ4 := $(BIN_DIR)/ej4
BIN_ALL := $(BIN_DIR)/main

# Targets principales
.PHONY: all ej2 ej3 ej4 clean

all: $(BIN_ALL)
	bin/main

$(BIN_ALL): $(BUILD_DIR)/main.o $(OBJ_EJ2) $(OBJ_EJ3) $(OBJ_UTILS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Reglas para objetos
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Reglas por ejercicio
$(BIN_EJ2): $(OBJ_EJ2) $(OBJ_EJ3) $(BUILD_DIR)/Ej2/main.o | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

ej2: $(BIN_EJ2)
	bin/ej2

$(BIN_EJ3): $(OBJ_EJ3) $(OBJ_EJ2) $(OBJ_UTILS) $(BUILD_DIR)/Ej3/main.o | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

ej3: $(BIN_EJ3)
	bin/ej3

$(BIN_EJ4): $(BUILD_DIR)/Ej4/main.o $(OBJ_EJ4) $(OBJ_EJ3) $(OBJ_EJ2) $(OBJ_UTILS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

ej4: $(BIN_EJ4)
	bin/ej4

$(BUILD_DIR)/main.o: main.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/Ej2/main.o: Ej2/main.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/Ej3/main.o: Ej3/main.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/Ej4/main.o: Ej4/main.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
