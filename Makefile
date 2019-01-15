jc: jc.c output.c output.h token.c token.h stack.c stack.h
	clang -o jc jc.c token.c output.c stack.c

clean:
	rm -f jc *.o