# Structs

This repository contains useful structures for C programming, along with the command to install them in
[proy](https://github.com/remeedev/proy).

## Basic Explanation

There are currently four structures, along with other "useful" modules that are used by these initial four.

For example usage you can check out the files at `./src/examples`

To run the examples you can do:

`make test <struct_name>`,
It will compile the file at `./src/examples/<struct_name>_example.c` and run it with valgrind, for memory testing.

## READMES

Even though this "main" readme doesn't contain any information on the structures written, the [README](https://github.com/remeedev/structs/tree/main/README) folder contains a readme for every structure that contains at least one (1) example in the
[examples](https://github.com/remeedev/structs/tree/main/src/examples) folder, these are all structures meant to be added as modules in proy, therefore basic understanding of them is crucial to their usage.

Nevertheless, some structures don't contain any explanation whatsoever for their existence, that is because those files have been used as dependencies for main structures and their functions could be deemed somewhat "useless". However, since they are added as modules inside `proy` you can check out [./README/extras.md](https://github.com/remeedev/structs/blob/main/README/extras.md) to check out the basic explanation of each module that doesn't have its own file.

Also, **all** readmes contain the name of the structure along with the name you should use when importing using `proy`.

## Usage with Proy

Once `proy` is installed just run:

`make install`

It will create the c template that all the imports follow and it will also create all of the imports in the right order (yes, there is a right order because there are some circular imports).

## C template

The c template installed by `structs` is the following, when you run `tree` on it:

```
.
├── bin
├── makefile
└── src
    ├── headers
    ├── imported
    │   └── headers
    └── main.c
```

It contains a folder for binaries, a folder for the source, for the files and headers. It contains by default a basic print program in `main.c`, however this can be changed, if needed, by changing the content at `./src/main.c`, also, the makefile comes with the following commands:

- `make compile`, which compiles a program to bin, by default the program name is stored in the makefile, in case it wants to be changed, additionally it has variables for any extra compile arguments you need to pass.

- `make run`, first compiles, then runs the program.

- `make compile-debug`, compiles the program with debugging information.

- `make mem-test`, does compile-debug, then runs through valgrind for memory tests.

- `make wc`, does nothing with the program, just returns the word count of all files not **imported**.
