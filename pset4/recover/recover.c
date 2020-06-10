#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        return 1;
    }


    int index = 0;
    int num_image = 0;
    BYTE *buffer = malloc(512);
    char *filename = malloc(7);
    FILE *img;

    while(1)
    {
        if (fread(buffer, 512, 1, file) == 0)
        {
            break;
        }
        else
        {
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            {
                sprintf(filename, "%03i.jpg", num_image);
                img = fopen(filename, "w");
                num_image++;
                fwrite(buffer, 512, 1, img);
            }
            else if (num_image != 0)
            {
                fwrite(buffer, 512, 1, img);
            }
            else
            {
                continue;
            }
        }
    }
    free(buffer);
    free(filename);
}
