all:
	gcc smd-to-bin.c -o smd-to-bin
	gcc bin-rename.c -o bin-rename
	./smd-to-bin *.smd *.SMD
	./bin-rename *.bin *.BIN

bin-rename:
	gcc bin-rename.c -o bin-rename
	./bin-rename *.bin *.BIN

smd-to-bin:
	gcc smd-to-bin.c -o smd-to-bin
	./smd-to-bin *.smd *.SMD
