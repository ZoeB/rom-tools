#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 16384
#define HALF_BLOCK_SIZE 8192

int main(int argc, char *argv[])
{
	FILE      *inputFilePointer;
	FILE      *outputFilePointer;
	uint8_t   inputBlock[BLOCK_SIZE];
	uint8_t   outputBlock[BLOCK_SIZE];
	int16_t   byte;
	int16_t   byteNumber;

	if (argc == 1) {
		return 0; /* Only work with named files, not stdin */
	} else {
		while (--argc > 0) {
			/* Loop through each file */
			inputFilePointer = fopen(*++argv, "r");
			fseek(inputFilePointer, 512, SEEK_SET);
			outputFilePointer = fopen("out.bin", "w");

			if (inputFilePointer == NULL) {
				continue;
			}

			byteNumber = 0;

			do {
				byte = getc(inputFilePointer);
				inputBlock[byteNumber] = byte;

				if (byteNumber == BLOCK_SIZE - 1) {
					/* The 16KiB block's full.  Convert it. */
					for (byteNumber = 0; byteNumber < HALF_BLOCK_SIZE; byteNumber++) {
						outputBlock[byteNumber * 2] = inputBlock[byteNumber + HALF_BLOCK_SIZE];
						outputBlock[byteNumber * 2 + 1] = inputBlock[byteNumber];
					}

					for (byteNumber = 0; byteNumber < BLOCK_SIZE; byteNumber++) {
						putc(outputBlock[byteNumber], outputFilePointer);
					}

					byteNumber = 0;
					putc('.', stdout);
				} else {
					byteNumber++;
				}
			} while (byte != EOF);

			fclose(inputFilePointer);
			fclose(outputFilePointer);
			putc('\n', stdout);
		}
	}

	return 0;
}
