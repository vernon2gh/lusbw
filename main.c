#include <stdio.h>

int main(int argc, unsigned char **argv)
{
    FILE *fstream;
    unsigned char buf[4096];

    if(argc != 2)
    {
        printf("[usage]: %s <filename>\n", argv[0]);
        return -1;
    }

    fstream = fopen(argv[1], "r");
    if(fstream == NULL) {
        printf("Open file failed\n");
        return -1;
    }

    while(1)
    {
        fread(buf, 512, 8, fstream); // read 8 item, each 512 bytes. totals is 4096 bytes.
        if(ferror(fstream)) {
            printf("read file failed.\n");
            return -1;
        }

        printf("%s", buf);
        if (feof(fstream))
        {
            // printf("detect EOF flag.\n");
            break;
        }
    }

    fclose(fstream);

    return 0;
}