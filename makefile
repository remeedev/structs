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

delete-c-template:
	proy template del c

messages:
	proy module create messages ./src/imported/messages.c ./src/imported/headers/messages.h

array:
	proy module create array messages handled-mem ./src/imported/array.c ./src/imported/headers/array.h

dict:
	proy module create dict messages array handled-mem strs ./src/imported/hash-table.c ./src/imported/headers/hash-table.h

list:
	proy module create list messages handled-mem ./src/imported/linked-list.c ./src/imported/headers/list.h

pq:
	proy module create pq array ./src/imported/priority_queue.c ./src/imported/headers/priority_queue.h

hmem:
	proy module create hmem array messages ./src/imported/hmem.c ./src/imported/headers/hmem.h

strs:
	proy module create strs hmem ./src/imported/strs.c ./src/imported/headers/strs.h

handled-mem:
	proy module create handled-mem hmem ./src/imported/handled_mem.c ./src/imported/headers/handled_mem.h

ezstr:
	proy module create ezstr hmem messages strs ./src/imported/ezstr.c ./src/imported/headers/ezstr.h

files:
	proy module create files ezstr ./src/imported/files.c ./src/imported/headers/files.h

bytes:
	proy module create bytes hmem messages ./src/imported/bytes.c ./src/imported/headers/bytes.h

typeless:
	proy module create typeless bytes ezstr hmem array dict messages strs handled-mem files ./src/imported/typeless.c ./src/imported/headers/typeless.h

add-all:
	make messages
	proy module create handled-mem ./makefile
	make array
	proy module delete handled-mem
	make hmem
	make strs
	make handled-mem
	make dict
	make list
	make pq
	make ezstr
	make files
	make bytes
	make typeless

remove-all:
	proy module delete messages
	proy module delete handled-mem
	proy module delete strs
	proy module delete array
	proy module delete dict
	proy module delete list
	proy module delete pq
	proy module delete hmem
	proy module delete ezstr
	proy module delete files
	proy module delete bytes
	proy module delete typeless

install:
	make create-c-template
	make add-all

uninstall:
	make remove-all
	make delete-c-template

reload:
	make uninstall
	make install

get-tests:
	echo "run an example by doing: make test <name_of_file_w/o_example.c>"
	tree ./src/examples

test: a != echo "$(MAKECMDGOALS)" | cut -d" " -f2
test: compile_file != find . -name "$(a)_example*"

test: $(compile_file)
	gcc -g -o $(BIN_PATH)/test_$(a) $(OPTS) $(compile_file) $(shell find . -name "*.c" | grep -v "example" | grep -v "main.c")
	valgrind --track-origins=yes --leak-check=full -s $(BIN_PATH)/test_$(a)
	rm -v $(BIN_PATH)/test_$(a)
