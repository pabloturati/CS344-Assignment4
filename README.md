# CS344-Assignment4
CS344-Assignment 4 Multi-threaded Producer Consumer Pipeline\
Author: Pablo Turati - turatip@oregonstate.edu\
Licence: MIT. Refer to `LICENSE` for details.

## Project Description

`Multi-threaded Producer Consumer Pipeline` is a simple multi-threaded program that performs the following operations:

- calls an Input Thread, reads in lines of characters from the standard input
- calls a Line Separator Thread, replacing every line separator in the input by a space.
- calls a Plus Sign thread, replacing every pair of plus signs, i.e., "++", by a "^"
- calls the Output Thread, writes this processed data to standard output as lines of exactly 80 characters.

Intercommunication between thereads is done by using the Producer-Consumer approach.

## Compile instructions

This project uses GNU99 compile standards for building the executable.

### Option 1.  Using compile script

This application includes a bash script to build and deploy the runner (compileApp.sh).  To use it, make sure that this file (compileApp.sh) has execution persmissions by running:

`$ chmod +x compileApp.sh`

You may execute the compile instructions by running from the project root:

`$ ./compileApp.sh`

This will generate a `smallsh` exectable file as output. Refer to the next section on how to run the application and pass parameters.

### Option 2.  Individual commands

Refer to the contents of `compileApp.sh` for a detailed command list on how to manually compile using command line.  Notice that this project was designed to be compiled with GNU99 standards.

### Option 3.  Compile and run in sigle step

`compileApp.sh` accepts the flag `-e`, in which case it will compile, generate the executable and immediately run it.  To do this run:

`$ compileApp.sh -e`

### Compile run available commands

The following flags can be passed to the compileApp.sh shell script:
  - e -> run executable
  - v -> run executable with valgrind leak analysis
  - t -> run executable with testscript to stdout
  - r -> run executable with testscript and send results to a report file
  - c -> performs only cleaning of compilation files and creted test files

## Run procedure

Once the application executable has been created `smallsh`. It can be run as follows:

`$ ./smallsh`

To compile and run in a single step run: `$ compileApp.sh -e`

## Additional resources

## Project File structure
```
root
├── .gitignore
├── compileApp.sh
├── main.c
├── LICENSE
├── README.md
├── constants
│   ├── constants.c
│   └── constants.h
└── builtinFunctions
    ├── builtinFunctions.c
    └── builtinFunctions.h
```


## Version control

 Link to the repository is available at [here](https://github.com/pabloturati/CS344-Assignment4).  However, due to this being an Oregon State University assignment, it will remain private and public access will become available after April, 2021.