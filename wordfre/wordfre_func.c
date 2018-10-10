#include"dbll.h"
#include"wordfre.h"

void showDbLinkList(DList*list)  //Traversing the linked list
{   if(list->len==0)
        {
                printf("the list is empty!\n");
                return;
        }
        pNODE p= list->head->next;
        printf("Print list as follow：  \n ");
        while (p!= NULL)
        {
                printf("word:%-20s\tfrequance:%-5d\t\tposition:%-5d\n ", ((word*)(p->data))->w,((word*)(p->data))->num,((word*)(p->data))->pos);
                p = p->next;
        }
        putchar('\n');
        printf("The length of the list is:%d\n",list->len);
}

void reverseshowDbLinkList(DList*list)  //Traversing the linked list
{   if(list->len==0)
        {
                printf("the list is empty!\n");
                return;
        }
        pNODE p= list->tail;
        printf("Print list as follow：  \n ");
        while (p!= list->head)
        {
                printf("word:%-20s\tfrequance:%-5d\t\tposition:%-5d\n ", ((word*)(p->data))->w,((word*)(p->data))->num,((word*)(p->data))->pos);
                p = p->pre;
        }
        putchar('\n');
        printf("The length of the list is:%d\n",list->len);
}






int 
compare_num(void* elem1, void* elem2){
        if(((word*)elem1)->num - ((word*)elem2)->num < 0)
                return -1;
        else if(((word*)elem1)->num - ((word*)elem2)->num == 0)
                return 0;
        else
                return 1;
}
int 
compare_pos(void* elem1, void* elem2){
        if(((word*)elem1)->pos - ((word*)elem2)->pos < 0)
                return -1;
        else if(((word*)elem1)->pos - ((word*)elem2)->pos == 0)
                return 0;
        else
                return 1;
}

int 
compare_word_case(void* elem1, void* elem2){
        if( strcmp(((word*)elem1)->w, ((word*)elem2)->w) < 0)
                return -1;
        else if( strcmp(((word*)elem1)->w, ((word*)elem2)->w) == 0)
                return 0;
        else
                return 1;

}
int compare_findword(void*elem1,void*elem2)
{       
        if( strcasecmp(((word*)elem1)->w, ((word*)elem2)->w) == 0)
                return 0;
        else
                return -1;
    
}
int compare_findword_case(void*elem1,void*elem2)
{
        if(((word*)elem1)->w[0]!=((word*)elem2)->w[0])
                return -1;
        if( strcmp(((word*)elem1)->w, ((word*)elem2)->w) == 0)
                return 0;
        else
                return -1;
    
}

int compare_word(void* elem1,void* elem2)
{
        if( strcasecmp(((word*)elem1)->w, ((word*)elem2)->w) < 0)
                return -1;
        else if( strcasecmp(((word*)elem1)->w, ((word*)elem2)->w) == 0)
                return 0;
        else
                return 1;

}

