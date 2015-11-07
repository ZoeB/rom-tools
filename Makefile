bin-rename:
	gcc bin-rename.c -o bin-rename
	./bin-rename sonic-2.bin

smd-to-bin:
	gcc smd-to-bin.c -o smd-to-bin
	./smd-to-bin sonic-2.smd
