# Structs

This repository contains useful structures for C programming, along with the command to install them in
[proy](https://github.com/remeedev/proy).

## Basic Explanation

There are currently four structures, along with other "useful" modules that are used by these initial four.

For example usage you can check out the files at `./src/examples`

To run the examples you can do:

`make test <struct_name>`,
It will compile the file at `./src/examples/<struct_name>_example.c` and run it with valgrind, for memory testing.

## Usage with Proy

To install the modules in proy run

`make <module_name>`

or run `make add-all` to install all.

`make remove-all` will remove all modules installed by this repo.

`make reload` will reinstall all modules, helps in case module files were recently updated.
