/*
 * Commodore 1541 D64 dump directory lister
 * by Zoe Blade, 2017
 *
 * Usage: "d64ls *.d64"
 *
 * Public domain
 */

#include <stdio.h>
#include <stdlib.h>

#define SECTOR 256 /* Each disk sector is 256 bytes long */

int main(int argc, char *argv[])
{
	FILE      *inputFilePointer;
	int16_t   byte;
	uint8_t    sectorNumber;
	uint8_t    fileNumber;
	uint8_t    fileType;
	uint8_t    charNumber;
	uint8_t    filenameSize;

	if (argc == 1) {
		return 0; /* Only work with named files, not stdin */
	} else {
		while (--argc > 0) {
			/* Loop through each file */
			inputFilePointer = fopen(*++argv, "rb");

			if (inputFilePointer == NULL) {
				continue;
			}

			fseek(inputFilePointer, 358 * SECTOR, SEEK_SET); /* Skip first 358 sectors */

			for (sectorNumber = 0; sectorNumber < 18; sectorNumber++) {
				fseek(inputFilePointer, 2, SEEK_CUR); /* For a simple first draft, ignore sector linking for now */

				for (fileNumber = 0; fileNumber < 8; fileNumber++) {
					fileType = getc(inputFilePointer);
					fseek(inputFilePointer, 2, SEEK_CUR); /* Ignore where the file is */
					filenameSize = 0;

					for (charNumber = 0; charNumber < 16; charNumber++) {
						byte = getc(inputFilePointer);

						if (byte != 0x00 && byte != 0xa0) {
							putc(byte, stdout);
							filenameSize++;
						}
					}

					fseek(inputFilePointer, 13, SEEK_CUR); /* Ignore other metadata */

					for (charNumber = filenameSize; charNumber < 16; charNumber++) {
						putc(' ', stdout);
					}

					switch (fileType) {
					case 0x00:
						printf(" ---\n");
						break;

					case 0x80:
						printf(" DEL\n");
						break;

					case 0x81:
						printf(" SEQ\n");
						break;

					case 0x82:
						printf(" PRG\n");
						break;

					case 0x83:
						printf(" USR\n");
						break;

					case 0x84:
						printf(" REL\n");
						break;

					}
				}
			}

			fclose(inputFilePointer);
		}
	}

	return 0;
}
