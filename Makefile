all:
	gcc gb-rename.c -o gb-rename
	./gb-rename *.gb *.GB
	gcc smd-to-bin.c -o smd-to-bin
	gcc bin-rename.c -o bin-rename
	./smd-to-bin *.smd *.SMD
	./bin-rename *.bin *.BIN

bin-rename:
	gcc bin-rename.c -o bin-rename
	./bin-rename *.bin *.BIN

gb-rename:
	gcc gb-rename.c -o gb-rename
	./gb-rename *.gb *.GB

smc-rename:
	gcc smc-rename.c -o smc-rename
	./smc-rename *.smc *.SMC

smd-to-bin:
	gcc smd-to-bin.c -o smd-to-bin
	./smd-to-bin *.smd *.SMD
