#ifndef __WORD_H__
#define __WORD_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

struct list_word {
    unsigned char *word;
    struct list_head list;
};

struct list_sentences {
    struct list_head *whead;
    struct list_head list;
};

extern struct list_head *separate_words(unsigned char *buf);
extern void print_word(struct list_head *shead);

#endif