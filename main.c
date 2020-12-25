#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void separate_words(unsigned char *buf)
{
    unsigned char *word;
    unsigned char tmp[256];
    int i = 0, j = 0, size;

    memset(tmp, 0, sizeof(tmp));

    for(i=0; i<strlen(buf); i++)
    {
        if((buf[i] == ' ') || (buf[i] == ',') || (buf[i] == '.') || (buf[i] == ';') || (buf[i] == '\n')) {
            size = j;
            word = malloc(size);
            strncpy(word, tmp, size);
            // store to `list`
            printf("%s ", word);

            memset(tmp, 0, sizeof(tmp));
            j = 0;
        }
        else {
            tmp[j] = buf[i];
            j++;
        }
    }
}

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
        memset(buf, 0, sizeof(buf));

        fread(buf, 512, 8, fstream); // read 8 item, each 512 bytes. totals is 4096 bytes.
        if(ferror(fstream)) {
            printf("read file failed.\n");
            return -1;
        }

        separate_words(buf);
        if (feof(fstream))
        {
            // printf("detect EOF flag.\n");
            break;
        }
    }

    fclose(fstream);

    return 0;
}