# Compilador y flags
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -MMD -MP -I./Ej2 -I./Ej3 -I./utils

# Carpetas
SRC_DIRS := Ej2 Ej3 utils
BUILD_DIR := utils/build
BIN_DIR := bin

# Main general (para pruebas integradas)
MAIN_GLOBAL := main.cpp
EXEC_GLOBAL := $(BIN_DIR)/juego

# Mains por ejercicio
MAIN_EJ2 := Ej2/main.cpp
EXEC_EJ2 := $(BIN_DIR)/ej2

MAIN_EJ3 := Ej3/main.cpp
EXEC_EJ3 := $(BIN_DIR)/ej3

# Buscar todos los archivos .cpp en subdirectorios
CPP_FILES := $(shell find $(SRC_DIRS) -name '*.cpp')
OBJ_FILES := $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(CPP_FILES))
DEP_FILES := $(OBJ_FILES:.o=.d)

# Archivos de objeto por ejercicio
OBJ_EJ2 := $(filter-out $(BUILD_DIR)/Ej3/main.o $(BUILD_DIR)/main.o,$(filter $(BUILD_DIR)/Ej2/% $(BUILD_DIR)/utils/%, $(OBJ_FILES)))
OBJ_EJ3 := $(filter-out $(BUILD_DIR)/Ej2/main.o $(BUILD_DIR)/main.o,$(filter $(BUILD_DIR)/Ej3/% $(BUILD_DIR)/Ej2/% $(BUILD_DIR)/utils/%, $(OBJ_FILES)))

# Target por defecto
.PHONY: all
all: $(EXEC_GLOBAL)

# Ejecutables por ejercicio y global
$(EXEC_GLOBAL): $(filter-out $(BUILD_DIR)/Ej2/main.o $(BUILD_DIR)/Ej3/main.o, $(OBJ_FILES)) $(MAIN_GLOBAL:.cpp=.o) | $(BIN_DIR)
	$(CXX) $^ -o $@

$(EXEC_EJ2): $(OBJ_EJ2) | $(BIN_DIR)
	$(CXX) $^ -o $@

$(EXEC_EJ3): $(OBJ_EJ3) | $(BIN_DIR)
	$(CXX) $^ -o $@

# Compilación de cualquier .cpp a .o dentro de BUILD_DIR
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compilación de main global y específicos
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Carpetas necesarias
$(BIN_DIR):
	@mkdir -p $@

# Targets individuales
.PHONY: ej2 ej3 clean run run2 run3

ej2: $(EXEC_EJ2)
ej3: $(EXEC_EJ3)

run: $(EXEC_GLOBAL)
	./$<

run2: $(EXEC_EJ2)
	./$<

run3: $(EXEC_EJ3)
	./$<

# Limpieza total
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR) *.o *.d

# Incluir dependencias si existen
-include $(DEP_FILES)