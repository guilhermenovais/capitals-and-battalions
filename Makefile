#---------------------------------------------------------------------
# Arquivo    : Makefile
# Conteúdo   : Compilar o projeto de componentes ligados e patrulhas
# Autor      : Guilherme Novais de Souza
# Histórico  : 2024-11-09 arquivo criado
#---------------------------------------------------------------------
# Opções     : make all   - compila tudo e executa o programa
#            : make clean - remove objetos e executável
#            : make test  - compila e executa o teste com o valgrind e gdb
#---------------------------------------------------------------------

CC = g++

SRC = src
OBJ = obj
INC = include
BIN = bin

CFLAGS = -c -g -I$(INC) -Wall -Wextra -Wpedantic -Wformat-security -Wconversion -Werror

EXE = $(BIN)/program.out

OBJS = $(OBJ)/main.o $(OBJ)/graph.o $(OBJ)/solution.o

HDRS = $(INC)/graph.hpp $(INC)/solution.hpp

mkdir:
	[ -d obj ] || mkdir obj
	[ -d bin ] || mkdir bin

all: mkdir $(EXE)

$(EXE): $(OBJS)
	$(CC) -o $(EXE) $(OBJS)


$(OBJ)/main.o: $(SRC)/main.cpp $(HDRS)
	$(CC) $(CFLAGS) -o $(OBJ)/main.o $(SRC)/main.cpp

$(OBJ)/graph.o: $(SRC)/graph.cpp $(INC)/graph.hpp
	$(CC) $(CFLAGS) -o $(OBJ)/graph.o $(SRC)/graph.cpp

$(OBJ)/solution.o: $(SRC)/solution.cpp $(INC)/solution.hpp
	$(CC) $(CFLAGS) -o $(OBJ)/solution.o $(SRC)/solution.cpp

clean:
	rm -f $(EXE) $(OBJS)

run: all
	./$(EXE)

test: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(EXE) < testcases/inputs/testCase01.txt
	gdb ./$(EXE)
