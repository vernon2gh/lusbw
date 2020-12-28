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

int separate_words(struct list_head **head, unsigned char *buf)
{
    unsigned char *word;
    unsigned char tmp[256];
    int i = 0, j = 0, size;
    struct list_head *shead = *head, *whead = NULL;

    memset(tmp, 0, sizeof(tmp));

    if(shead == NULL)
    {
        shead = malloc(sizeof(struct list_head));
        INIT_LIST_HEAD(shead);
        *head = shead;
    }

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

    return 0;
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

void compare_word(struct list_head *shead, struct list_head *thead)
{
    struct list_sentences *stmp, *ttmp;
    struct list_word *wstmp, *wttmp;

    list_for_each_entry(stmp, shead, list) {
        list_for_each_entry(wstmp, stmp->whead, list) {
            list_for_each_entry(ttmp, thead, list) {
                list_for_each_entry(wttmp, ttmp->whead, list) {
                    if(!strcmp(wstmp->word, wttmp->word)) {
                        printf("%s %s\n", wstmp->word, wttmp->word);
                        stmp->hit_number++;
                    }
                }
            }
        }
    }
}
