#!/bin/bash

yacc -d -y 1905021.y 
echo 'Generated the parser C file as well as the header file'
g++ -g -fsanitize=address -w -c -o y.o y.tab.c 
echo 'Generated the parser object file'
flex 1905021_lexical.l
echo 'Generated the scanner C file'
g++ -g -fsanitize=address -w -c -o l.o lex.yy.c 
# if the above command doesn't work try g++ -fpermissive -w -c -o l.o lex.yy.c
echo 'Generated the scanner object file'
g++ -g -fsanitize=address y.o l.o 
echo "All ready, running"
./a.out input.c
