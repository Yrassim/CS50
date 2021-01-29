#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2) // to check if the user give more than 1 argument
    {
        printf("Usage: ./recover Filename\n");
        return 1;
    }
    else
    {
        FILE *file = fopen(argv[1], "r"); // open the file given on the argument to read it

        if (file == NULL) // if the file is not readable
        {
            printf("Cannot read the %s file\n", argv[1]);
            return 1;
        }
        else
        {
            unsigned char buffer[512]; // defining memory to stock the bytes to check
            int newImage = 0; // integer to check if the iage check is starting or ending
            FILE *imageStore = NULL; // file to store bytes of the image retrived
            char filename[8]; // to store the image name
            int counter = 0; // counter to use for image names

            while (fread(buffer, 512, 1, file) == 1) // read the full 512 bytes of block and countinuing reading
            {
                // if we find these bytes, it means new image
                if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
                {
                    if (newImage == 1)// if we already storing an image, it will be the end. and the start for another image
                    {
                        fclose(imageStore);
                    }
                    else
                    {
                        newImage = 1;// to state that it is not a new image
                    }

                    sprintf(filename, "%03i.jpg", counter++), // give the image name with 3 digit before .jpg
                    imageStore = fopen(filename, "w"); // write the new found jpeg

                }
                // writing the image found to the new file
                if (newImage == 1)
                {
                    fwrite(buffer, 512, 1, imageStore);
                }
            }

            fclose(imageStore); // close file when it is not in use
        }

        fclose(file); // close file when it is not in use
        return 0;
    }

}
