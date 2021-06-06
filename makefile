# Makefile TD Flex

# $@ : the current target
# $^ : the current prerequisites
# $< : the first current prerequisite

CC=gcc
CFLAGS=-Wall
LDFLAGS=-Wall -lfl
NAMELEX=tpc-2020-2021
NAMEYACC=tpc-2020-2021
OBJ=./obj/abstract-tree.o ./obj/decl-var.o ./obj/trad.o
EXEC=./bin/tpcc

all: $(EXEC) clean

./obj/abstract-tree.o: ./src/abstract-tree.c ./src/abstract-tree.h
./obj/decl-var.o: ./src/decl-var.c ./src/decl-var.h
./obj/trad.o: ./src/trad.c ./src/trad.h

./obj/%.o: ./src/%.c
	$(CC) -o $@ -c $< $(CFLAGS)

test: $(EXEC) ./src/test.sh
	chmod +x ./src/test.sh
	./src/test.sh $(EXEC) ./test/good/ ./test/warn-err/  ./test/syn-err/ ./test/sem-err/ 

./obj/$(NAMEYACC).tab.c ./obj/$(NAMEYACC).tab.h: ./src/$(NAMEYACC).y
	bison $< --defines=./obj/$(NAMEYACC).tab.h -o ./obj/$(NAMEYACC).tab.c

./obj/lex.yy.c: ./src/$(NAMELEX).lex ./obj/$(NAMEYACC).tab.h
	flex -o $@ $<

./obj/lex.yy.o: ./obj/lex.yy.c ./obj/$(NAMEYACC).tab.h
	$(CC) -o $@ -c $< $(CFLAGS)

./obj/$(NAMEYACC).tab.o: ./obj/$(NAMEYACC).tab.c ./obj/$(NAMEYACC).tab.h
	$(CC) -o $@ -c $< $(CFLAGS)

$(EXEC): ./obj/lex.yy.o ./obj/$(NAMEYACC).tab.o $(OBJ)
	$(CC) -o $(EXEC) $^ $(LDFLAGS)


clean:
	rm -f ./obj/*