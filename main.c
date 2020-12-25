#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

struct list_head *separate_words(unsigned char *buf)
{
    unsigned char *word;
    unsigned char tmp[256];
    int i = 0, j = 0, size;
    struct list_head *shead = NULL, *whead = NULL;

    memset(tmp, 0, sizeof(tmp));

    shead = malloc(sizeof(struct list_head));
    INIT_LIST_HEAD(shead);

    for(i=0; i<strlen(buf); i++)
    {
        if((buf[i] == ' ') || (buf[i] == '\n') || (buf[i] == ',') || (buf[i] == '.') || (buf[i] == ';'))
        {
            if(j == 0)
                continue;

            if (whead == NULL) {
                whead = malloc(sizeof(struct list_head));
                INIT_LIST_HEAD(whead);
            }

            size = j;
            word = malloc(size);
            strncpy(word, tmp, size);
            word_enqueue(whead, word);

            if((buf[i] == ',') || (buf[i] == '.') || (buf[i] == ';'))
            {
                sentences_enqueue(shead, whead);
                whead = NULL;
            }

            memset(tmp, 0, sizeof(tmp));
            j = 0;
        }
        else
        {
            tmp[j] = buf[i];
            j++;
        }
    }

    return shead;
}

void print_word(struct list_head *shead)
{
    struct list_sentences *stmp;
    struct list_word *wtmp;

    list_for_each_entry(stmp, shead, list) {
        list_for_each_entry(wtmp, stmp->whead, list) {
            printf("%s ", wtmp->word);
        }
        printf("\n");
    }
}

int main(int argc, unsigned char **argv)
{
    FILE *fstream;
    unsigned char buf[4096];
    struct list_head *shead;

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

        shead = separate_words(buf);
        print_word(shead);

        if (feof(fstream))
        {
            // printf("detect EOF flag.\n");
            break;
        }
    }

    fclose(fstream);

    return 0;
}