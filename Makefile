run:
	clang -lm -O src/main.c -o crpn
	./crpn

compile:
	clang -lm -O2 src/main.c -o crpn

debug:
	clang -lm -Og -g src/main.c -o crpn-dbg
	gdb crpn-dbg
