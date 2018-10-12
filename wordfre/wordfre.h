#include<time.h>
#include<getopt.h>
#include<unistd.h>
#include<stdbool.h>
#define MAX_LINE 1500
#define WORD_LEN 22

bool opt_create_case;
bool opt_create;
bool opt_num_sort;
bool opt_pos_sort;
bool opt_word_sort;
bool opt_show;
bool opt_reverse_show;


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
void show_word_list(DList*list);
void show_operate(pNODE p_node,void* aide_para);
