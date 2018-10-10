#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
//#include<time.h>
//#include<unistd.h>
//#include<getopt.h>
//#define MAX_LINE 1500
//#define WORD_LEN 22
typedef void*  Elemtype;
typedef struct Node
{
    Elemtype data;
    struct Node *pre;
    struct Node *next;
}NODE,*pNODE; //Defining a node, At this point 'NODE' is equivalent to 'struct Node'; '*pNODE' is equivalent to struct 'Node*'
typedef struct DList
{
    int len;
    struct Node *head;
    struct Node *tail;
}DList;

/*typedef struct word
{
  char w[WORD_LEN];
  int num;
  int pos;
}word;*/

    
DList* CreateDbLinkList();
void Destory(DList*list);
void list_combine(DList*list1,DList*list2);
void(*show)(DList*list);
//void showDbLinkList(DList*list);
void ReverseDbLinkList(DList*list);
//int InsertEleDbLinkList(DList*list, int pos, Elemtype value);
int TailInsertElem(DList*list,Elemtype value);
void DeleteEleDbLinkList(DList*list,pNODE p);
//int compare_word_case(Elemtype elem1, Elemtype elem2);
//int compare_findword(Elemtype elem1, Elemtype elem2);
//int compare_findword_case(Elemtype elem1, Elemtype elem2);
//int compare_word(Elemtype elem1, Elemtype elem2);
//int compare_num(Elemtype elem1, Elemtype elem:wq2);
//int compare_pos(Elemtype elem1, Elemtype elem2);
pNODE LookForDbLinkList(DList*list,Elemtype key,int (*compare)(Elemtype elem1, Elemtype elem2));
void QuickSort(pNODE p_left,pNODE p_right,int left,int right,int (*compare)(Elemtype elem1, Elemtype elem2));//len初始为1
int (*compare)(Elemtype elem1, Elemtype elem2);
