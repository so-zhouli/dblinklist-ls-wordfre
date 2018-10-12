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

typedef int (* dbll_compare_cb)(void *elem1,void *elem2);
typedef void (* data_operate_cb)(pNODE p_node,void* aide_para);    


DList* create_dbll();
void destory_dbll(DList*list);
void combine_dbll(DList*list1,DList*list2);
void reverse_dbll(DList*list);
int insert_elem_dbll(DList*list, int pos, Elemtype value);
int tail_insert_elem_dbll(DList*list,Elemtype value);
void delete_elem_dbll(DList*list,pNODE p_node);
pNODE search_elem_dbll(DList*list,Elemtype key,dbll_compare_cb compare);
void quick_sort_dbll(pNODE p_left,pNODE p_right,int left,int right,dbll_compare_cb compare);//len初始为1
void travel_dbll(DList* list,data_operate_cb data_operate,void* aide_para);
