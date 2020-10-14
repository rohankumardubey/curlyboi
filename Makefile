default: build

build:
	gcc -o snake src/main.c src/backend.c src/frontend.c -lncursesw -ltinfo

run: build
	./snake

tests:
	checkmk test/test.ts > test/test.c
	gcc -o run_tests src/backend.c src/backend.h test/test.c -lncursesw -lcheck
	./run_tests

clean:
	rm snake run_tests
