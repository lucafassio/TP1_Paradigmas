COMPILER = g++
CXXFLAGS = -Wall -Wextra -Wpedantic -Werror -Wconversion -Wsign-conversion -Wshadow -Wnull-dereference -Wfloat-equal -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wformat=2 -Wcast-align -Wstrict-overflow=5 -Wunsafe-loop-optimizations -Wuseless-cast -Wmissing-include-dirs -Wold-style-cast -Woverloaded-virtual -Wnon-virtual-dtor -Wzero-as-null-pointer-constant -Wmissing-declarations -Weffc++ -Wstack-protector
LDFLAGS = -o run
VALGRIND = valgrind --error-exitcode=1 --leak-check=full --show-leak-kinds=all --track-origins=yes -s
COMPILE = $(COMPILER) $(CXXFLAGS) $(LDFLAGS)

EJ2_ABS = Ej2/characters/mages/mage.cpp Ej2/characters/warriors/warrior.cpp Ej2/weapons/combat_weapons/combat.cpp Ej2/weapons/magic_weapons/magic.cpp
EJ2_SRC = Ej2/characters/mages/src/* Ej2/characters/warriors/src/* Ej2/weapons/combat_weapons/src/* Ej2/weapons/magic_weapons/src/*

EJ3 = Ej3/src/*
EJ4 = Ej4/funcs.cpp
UTILS = utils/HUD/src/*

make:
	@$(COMPILE) $(EJ2_ABS) $(EJ2_SRC) $(EJ3) $(EJ4) $(UTILS) main.cpp
	@valgrind --error-exitcode=1 --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./run
	@rm run

run2:
	@$(COMPILE) $(EJ2_ABS) $(EJ2_SRC) $(EJ3) $(EJ4) $(UTILS) Ej2/main.cpp
	@valgrind --error-exitcode=1 --leak-check=full --show-leak-kinds=all --track-origins=yes ./run
	@rm run

run3:
	@$(COMPILE) $(EJ2_ABS) $(EJ2_SRC) $(EJ3) $(EJ4) $(UTILS) Ej3/main.cpp
	@valgrind --error-exitcode=1 --leak-check=full --show-leak-kinds=all --track-origins=yes ./run
	@rm run

run4:
	@$(COMPILE) $(EJ2_ABS) $(EJ2_SRC) $(EJ3) $(EJ4) $(UTILS) Ej4/main.cpp
	@valgrind --error-exitcode=1 --leak-check=full --show-leak-kinds=all --track-origins=yes ./run
	@rm run