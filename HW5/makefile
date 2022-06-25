all: clear clean compile run

clear:
	@clear

compile: main.c
	@gcc -o ex main.c -lm

run:
	@./ex

clean:
	@rm -f *.o
	@rm -f ex
	@rm -f *.txt
	@rm -f *.out
	@rm -f *.save
