# Compilador y flags (ajustar si es necesario)
CXX := g++
CXXFLAGS := -Wall -O2

# Buscar todos los fuentes .cpp recursivamente
SOURCES := $(shell find . -type f -name '*.cpp' -printf '%P\n')
# Generar lista de objetos en build/ correspondientes a SOURCES
OBJECTS := $(patsubst %.cpp, build/%.o, $(SOURCES))

# Target por defecto: compilar el ejecutable 'bin'
all: bin

# Enlazar el ejecutable final
bin: $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

# Regla de compilación de cualquier .cpp a .o en build/, creando dirs si hace falta
build/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Target para compilar y ejecutar
run: bin
	./bin

# Target para limpiar los archivos generados
clean:
	rm -rf build bin

# Declarar como phony los targets que no son archivos reales
.PHONY: all run clean
