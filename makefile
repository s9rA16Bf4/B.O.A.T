COMPILER := g++
LIB := includes/
SRC := src/
FLAGS := -g3
BIN := boat
RM := rm

compile:
	$(COMPILER) $(FLAGS) -I$(LIB) $(SRC)*.cpp -o $(BIN)

clean:
	-$(RM) $(BIN)
