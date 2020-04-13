.PHONY: clean

all: udpcli udpserv

udpcli: error.o udpcli.o
	gcc -g $^ -o bin/$@

udpserv: error.o udpserv.o
	gcc -g $^ -o bin/$@

%.o: %.c
	gcc -c -g -Wall $< -o $@

clean:
	rm -rf *.o