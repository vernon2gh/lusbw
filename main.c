#include <stdio.h>
#include "word.h"

int main(int argc, unsigned char **argv)
{
    FILE *fstream;
    unsigned char buf[4096];
    struct list_head *shead=NULL, *thead=NULL;
    int i;

    if(argc < 2)
    {
        printf("[usage]: %s <resource> <target>\n", argv[0]);
        return -1;
    }

    for(i=1; i<argc; i++)
    {
        fstream = fopen(argv[i], "r");
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

            if(i < (argc-1)) {
                separate_words(&shead, buf);
            }
            else {
                separate_words(&thead, buf);
            }

            if (feof(fstream))
            {
                // printf("detect EOF flag.\n");
                break;
            }
        }

        fclose(fstream);
    }

    // print_word(shead);
    // print_word(thead);
    compare_word(shead, thead);
    save_sentences(shead);

    return 0;
}