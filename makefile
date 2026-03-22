FILES:=$(shell find ./src -name "*.c" | grep -v "example")
OPTS:=-lm
BIN_PATH:=./bin
OUT_NAME:=program

wc:
	echo "Lines Words" && find . -name "*" | grep -E "(\.c|\.h)" | xargs wc -wl

create-c-template:
	mkdir -v ./tmp
	mkdir -v ./tmp/bin
	mkdir -v ./tmp/src
	mkdir -v ./tmp/src/headers
	mkdir -v ./tmp/src/imported
	mkdir -v ./tmp/src/imported/headers
	cp -vT def-make ./tmp/makefile
	cp -vT src/main.c ./tmp/src/main.c
	cd tmp && proy template new c .
	rm -v -fr ./tmp

messages:
	proy module create messages ./src/imported/messages.c ./src/imported/headers/messages.h

array: messages handled-mem
	proy module create array messages handled-mem ./src/imported/array.c ./src/imported/headers/array.h

dict: handled-mem strs array
	proy module create dict messages array handled-mem strs ./src/imported/hash-table.c ./src/imported/headers/hash-table.h

list: messages handled-mem
	proy module create list messages handled-mem ./src/imported/linked-list.c ./src/imported/headers/list.h

pq: array
	proy module create pq array ./src/imported/priority_queue.c ./src/imported/headers/priority_queue.h

hmem: array messages
	proy module create hmem array messages ./src/imported/hmem.c ./src/imported/headers/hmem.h

strs: hmem
	proy module create strs hmem ./src/imported/strs.c ./src/imported/headers/strs.h

handled-mem: hmem
	proy module create handled-mem hmem ./src/imported/handled_mem.c ./src/imported/headers/handled_mem.h

add-all:
	make messages
	make handled-mem
	make strs
	make array
	make dict
	make list
	make pq
	make hmem

remove-all:
	proy module delete messages
	proy module delete handled-mem
	proy module delete strs
	proy module delete array
	proy module delete dict
	proy module delete list
	proy module delete pq
	proy module delete hmem

reload:
	make remove-all
	make add-all

test: a != echo "$(MAKECMDGOALS)" | cut -d" " -f2
test: compile_file != find . -name "$(a)_example*"

test: $(compile_file)
	gcc -g -o $(BIN_PATH)/test_$(a) $(OPTS) $(compile_file) $(shell find . -name "*.c" | grep -v "example" | grep -v "main.c")
	valgrind --track-origins=yes --leak-check=full -s $(BIN_PATH)/test_$(a)
	rm -v $(BIN_PATH)/test_$(a)
