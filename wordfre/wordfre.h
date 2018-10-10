#include<time.h>
#include<getopt.h>
#include<unistd.h>
#define MAX_LINE 1500
#define WORD_LEN 22

typedef struct word
{
    char w[WORD_LEN];
    int num;
    int pos;
}word;

int compare_word_case(Elemtype elem1, Elemtype elem2);
int compare_findword(Elemtype elem1, Elemtype elem2);
int compare_findword_case(Elemtype elem1, Elemtype elem2);
int compare_word(Elemtype elem1, Elemtype elem2);
int compare_num(Elemtype elem1, Elemtype elem2);
int compare_pos(Elemtype elem1, Elemtype elem2);
void showDbLinkList(DList*list);
void reverseshowDbLinkList(DList*list);
