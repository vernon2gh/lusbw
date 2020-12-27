#include "word.h"

void sentences_enqueue(struct list_head *head, struct list_head *whead)
{
    struct list_sentences *new;

    new = malloc(sizeof(struct list_sentences));
    new->whead = whead;
    list_add_tail(&new->list, head);
}

void word_enqueue(struct list_head *head, unsigned char *word)
{
    struct list_word *new;

    new = malloc(sizeof(struct list_word));
    new->word = word;
    list_add_tail(&new->list, head);
}

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
