all:
	gcc smd-to-bin.c -o smd-to-bin
	./smd-to-bin sonic-2.smd
