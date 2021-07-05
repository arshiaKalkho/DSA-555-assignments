CC=g++
CFLAGS+=-Wall
CFLAGS+=-std=c++0x
FILES=a2tester.cpp
FILES+=timer.cpp

a2tester: $(FILES)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *.o a2tester

all: a2tester
