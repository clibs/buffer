CFLAGS=-std=c99

SRC=buffer.c
OBJ=$(patsubst %.c,%.o,$(SRC))

.PHONY: clean

all: test

build: $(OBJ)

test: build
	$(CC) $(CFLAGS) $@.c $(OBJ) -o $@
	@./test

clean:
	find . -type f -executable -exec rm -f {} \;
	rm -f *.o
