all: main

main:
	clear
	gcc rpn.c -o rpn

warn:
	clear
	gcc rpn.c -o rpn -Wall

clean:
	rm -r rpn
	clear