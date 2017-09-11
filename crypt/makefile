crypt: main.o crypt.o
	gcc -o crypt main.o crypt.o
	mkdir -p ~/bin
	cp ./crypt ~/bin/crypt
	cp ./decrypt ~/bin/decrypt
	cp ./encrypt ~/bin/encrypt
main.o: main.c
	gcc -c main.c
crypt.o: crypt.c crypt.h
	gcc -c crypt.c
clean:
	rm main.o crypt.o
