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
	uint8_t    fileNumber;
	uint8_t    charNumber;

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

			for (fileNumber = 0; fileNumber < 144; fileNumber++) {
				for (charNumber = 0; charNumber < 32; charNumber++) {
					byte = getc(inputFilePointer);

/*
					if (byte == '\0') {
						break;
					}
*/

					putc(byte, stdout);
				}

				putc('\n', stdout);
			}

			fclose(inputFilePointer);
		}
	}

	return 0;
}
