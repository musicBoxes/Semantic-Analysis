CC=gcc
FLEX=flex
BISON=bison
splc:
	make clean
	@mkdir bin
	$(FLEX) lex.l
	$(BISON) -t -d syntax.y
	$(CC) -w syntax.tab.c -lfl -ly -o bin/splc
	touch bin/splc
	@chmod +x bin/splc
clean:
	@rm -rf bin/
	@rm -rf syntax.tab.*
	@rm -rf lex.yy.c
	@rm -rf syntax.output
lex_test:
	flex lex.l
	gcc lex.yy.c -lfl -o lex_test.out
	./lex_test.out .
.PHONY: splc