all: test

# demo: src/main.c src/dstring.c include/dstring.h
# 	gcc -g -Iinclude src/main.c src/dstring.c -o demo

test: Test/test.c Operations/createDatabase.c Operations/displayDatabase.c Include/inverted.h
	gcc -g -O0 -Wall -Wextra -IInclude Test/test.c Operations/createDatabase.c Operations/displayDatabase.c Operations/saveDatabase.c Operations/searchDatabase.c -o test_inverted
