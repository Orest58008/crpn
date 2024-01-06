run:
	clang src/main.c -o crpn
	./crpn

compile:
	clang -O2 src/main.c -o crpn
