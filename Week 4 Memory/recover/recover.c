#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of "block size" 512

const int BLOCK_SIZE = 512;

// New type to store a byte of data

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Accept a single command-line argument

    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card

    FILE *card = fopen(argv[1], "r");
    {
        // check for fail to peon
        if (card == NULL)
        {
            printf("The forensic image cannot be opened for reading\n");
            return 1;
        }
    }

    // 1 block size = 512 bytes
    BYTE buffer[BLOCK_SIZE];

    // Declare jpeg filename size
    char filename[8];

    // Count image
    int count_image = 0;

    FILE *output = NULL;

    // While there's still data left to read from the memory card

    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, card) == BLOCK_SIZE)
    {

        // If start of a new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // if it is the firstc JPEG
            if (count_image == 0)
            {
                sprintf(filename, "%03i.jpg", count_image);
                output = fopen(filename, "w");
                if (output == NULL)
                {
                    printf("jpeg file cannot be opened\n");
                    return 2;
                }
                fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, output);
                count_image++;
            }
            // if already found a JPEG
            else if (count_image > 0)
            {
                fclose(output);
                sprintf(filename, "%03i.jpg", count_image);
                output = fopen(filename, "w");
                if (output == NULL)
                {
                    printf("jpeg file cannot be opened\n");
                    return 2;
                }
                fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, output);
                count_image++;
            }
        }

        // If it is not the start of the JPEG
        // if already found JPEG
        else if (count_image > 0)
        {
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, output);
        }
    }
    fclose(output);
    fclose(card);
}
