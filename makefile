# Makefile para compilar a árvore Rubro-Negra

# Nome do executável
target = rb_tree

# Compilador e flags
CC = g++
CFLAGS = -Wall -Wextra -O2 -std=c++17

# Arquivos fonte e objeto
SRC = arvoreRN.cpp
# SRC = arvoreAVL.cpp
OBJ = $(SRC:.cpp=.o)

# Regra padrão para compilar tudo
default: $(target)

# Regra para criar o executável
$(target): $(OBJ)
	$(CC) $(CFLAGS) -o $(target) $(OBJ)

# Regra para compilar os arquivos fonte
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Limpar arquivos gerados
clean:
	rm -f $(OBJ) $(target)

.PHONY: default clean
