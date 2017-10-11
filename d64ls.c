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

int main(int argc, char *argv[])
{
	FILE      *inputFilePointer;
	int16_t   byte;
	int8_t    inputByteNumber;

	if (argc == 1) {
		return 0; /* Only work with named files, not stdin */
	} else {
		while (--argc > 0) {
			/* Loop through each file */
			inputFilePointer = fopen(*++argv, "rb");

			if (inputFilePointer == NULL) {
				continue;
			}

			fseek(inputFilePointer, 0x16500, SEEK_SET);

			for (inputByteNumber = 0; inputByteNumber < 32; inputByteNumber++) {
				byte = getc(inputFilePointer);

/*
				if (byte == '\0') {
					break;
				}
*/

				putc(byte, stdout);
			}

			fclose(inputFilePointer);
		}
	}

	return 0;
}
