#!/bin/sh

mkdir  -p  Debug

rm  -f  Debug/calc


flex  calc.l    # creates a C file based on the Scanner specifications


bison calc.y    # creates a C file based on the Parser  specifications


# permissive compilation command
# g++   -std=c++17   *.c   -o Debug/calc     # creates the executable program  calc  in  Debug folder


# stricter compilation command
g++   -std=c++17   *.c   -o Debug/calc   -pedantic -Wall -Wextra -Wshadow=local   -Wmisleading-indentation -Wmissing-braces -Wparentheses -Wsequence-point -Wreturn-type -Wswitch-unreachable -Wunused-but-set-parameter -Wunused-but-set-variable -Wunused-const-variable -Wuninitialized -Wsuggest-final-types -Wsuggest-final-methods -Wsuggest-override -Wbool-compare -Wbool-operation -Wduplicated-branches -Wduplicated-cond -Wtautological-compare -Wcast-align -Wpointer-arith -Wdangling-else -Wempty-body -Wextra-semi -Wlogical-op -Wmissing-declarations -Wmissing-field-initializers -Wredundant-decls -Wint-in-bool-context -Wlogical-not-parentheses -Winline -Wundef -Wcast-qual -Wwrite-strings -Wno-unused-parameter -Wno-register -Wno-undef -Wno-sign-compare -Wno-float-equal #-Wconversion -Wuseless-cast

# to run the parser in the terminal, type       Debug/calc
