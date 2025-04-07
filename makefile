# Compilador y flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -MMD -MP

# Carpetas internas (ya estamos en la raíz)
SRC_DIR_EJ2 = Ej2
SRC_DIR_EJ3 = Ej3
SRC_DIR_EJ4 = Ej4
UTILS_DIR = utils
BUILD_DIR = $(UTILS_DIR)/build
BIN_DIR = bin

# Includes
INCLUDES = -I./$(SRC_DIR_EJ2) -I./$(SRC_DIR_EJ3) -I./$(SRC_DIR_EJ4) -I./$(UTILS_DIR)

# Archivos fuente y objetos
CPP_FILES_EJ2 = $(shell find $(SRC_DIR_EJ2) -name '*.cpp')
OBJ_FILES_EJ2 = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(CPP_FILES_EJ2))

CPP_FILES_EJ3 = $(shell find $(SRC_DIR_EJ3) -name '*.cpp' ! -name 'main.cpp')
OBJ_FILES_EJ3 = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(CPP_FILES_EJ3))

CPP_FILES_EJ4 = $(shell find $(SRC_DIR_EJ4) -name '*.cpp' ! -name 'main.cpp')
OBJ_FILES_EJ4 = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(CPP_FILES_EJ4))

UTILS_CPP = $(shell find $(UTILS_DIR) -name '*.cpp')
UTILS_OBJ = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(UTILS_CPP))

MAIN_GLOBAL = $(shell find . -maxdepth 1 -name 'main.cpp')
MAIN_OBJ = $(patsubst %.cpp,%.o,$(MAIN_GLOBAL))

# Ejecutables
BIN_EJ3 = $(BIN_DIR)/ej3
BIN_EJ4 = $(BIN_DIR)/ej4
BIN_JUEGO = $(BIN_DIR)/juego

# Default
default: all
all: $(BIN_EJ3) $(BIN_EJ4) $(BIN_JUEGO)

# Regla general para objetos
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Ejecutable Ej3
$(BIN_EJ3): $(OBJ_FILES_EJ2) $(OBJ_FILES_EJ3) $(BUILD_DIR)/$(SRC_DIR_EJ3)/main.o
	@mkdir -p $(BIN_DIR)
	$(CXX) $^ -o $@

# Ejecutable Ej4
$(BIN_EJ4): $(OBJ_FILES_EJ2) $(OBJ_FILES_EJ3) $(OBJ_FILES_EJ4) $(BUILD_DIR)/$(SRC_DIR_EJ4)/main.o
	@mkdir -p $(BIN_DIR)
	$(CXX) $^ -o $@

# Ejecutable principal con main global
$(BIN_JUEGO): $(OBJ_FILES_EJ2) $(OBJ_FILES_EJ3) $(MAIN_OBJ)
	@mkdir -p $(BIN_DIR)
	$(CXX) $^ -o $@

# Comandos de ejecución
run3: $(BIN_EJ3)
	./$(BIN_EJ3)

run4: $(BIN_EJ4)
	./$(BIN_EJ4)

runjuego: $(BIN_JUEGO)
	./$(BIN_JUEGO)

valgrind3: $(BIN_EJ3)
	valgrind --leak-check=full ./$(BIN_EJ3)

valgrind4: $(BIN_EJ4)
	valgrind --leak-check=full ./$(BIN_EJ4)

valgrindjuego: $(BIN_JUEGO)
	valgrind --leak-check=full ./$(BIN_JUEGO)

# Clean
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR) *.o *.d

-include $(OBJ_FILES_EJ2:.o=.d)
-include $(OBJ_FILES_EJ3:.o=.d)
-include $(OBJ_FILES_EJ4:.o=.d)
-include $(UTILS_OBJ:.o=.d)
