#include"dbll.h"


void list_combine(DList*list1,DList*list2)
{
    pNODE p1=list1->tail;
    pNODE p2=list2->head->next;
    if(p2==NULL)
        printf("list2 is empty!please go ahead!\n");
    else
    {
        p1->next=p2;
        p2->pre=p1;
        list1->tail=list2->tail;
        list2->head->next=NULL;
    }
    return;
}

DList* CreateDbLinkList() //Create the first node 
{
        int i;
        DList*list=(DList*)malloc(sizeof(DList));
        list->len=0;
        pNODE ptail=NULL;
        pNODE phead=(pNODE)malloc(sizeof(NODE));
        if (NULL == phead)
        {
                printf("Memory allocation failed！\n");
                exit(EXIT_FAILURE);
        }
        phead->data =NULL;
        phead->pre = NULL;
        phead->next = NULL;
        ptail = phead;     //Create the first node
        list->tail=ptail;
        list->head=phead;

        return list;

}

void Destory(DList* list)
{ 
        while(list->head->next!=NULL)
                DeleteEleDbLinkList(list,list->head->next);
        free(list->head);
        free(list);
       // printf("List Destoryed!\n");
}



void ReverseDbLinkList(DList*list)
{
	pNODE p1=list->tail;
	pNODE p2=NULL;
	list->head->next=p1;
	p2=p1->pre;
	p1->pre=list->head;
	p1->next=p2;
	p1=p2;
	while(p2->pre!=list->head)
	{
		p2=p1->pre;
		p1->pre=p1->next;
		p1->next=p2;
		p1=p2;
	}
	p1->pre=p1->next;
	p1->next=NULL;
	list->tail=p1;
}
int InsertEleDbLinkList(DList*list, int pos, Elemtype value)  //   Pos is the insertion position
{
        pNODE p1=list->head, p2=NULL,p_new = NULL;
        Elemtype data=value;
        if (pos > 0 && pos < list->len + 2)
        {
                p_new = (pNODE)malloc(sizeof(NODE));

                if (NULL == p_new)
                {
                        printf("Memory allocation failed！\n");
                        exit(EXIT_FAILURE);
                }

                while (1)
                {
                        pos--;
                        if (0 == pos)
                                break;
                        p1 = p1->next;
                }

                if (NULL == p1->next)
                {
                        p_new->data = data;
                        p_new->next = NULL;
                        p_new->pre =p1;
                        p1->next=p_new;
                        list->tail=p_new;
                        list->len=list->len+1;
                }
                else
                {   
                        p2=p1->next;
                        p_new->data=data;
                        p_new->next=p2;
                        p_new->pre=p1;
                        p1->next=p_new;
                        p2->pre=p_new;
                        list->len=list->len+1;

                }
                return 1;
        }
        else
                return 0;

}

int TailInsertElem(DList*list,Elemtype value)
{
        pNODE p_new;
        p_new=(pNODE)malloc(sizeof(NODE));
        p_new->data=value;
        p_new->next=NULL;
        p_new->pre=list->tail;
        list->tail->next=p_new;
        list->tail=p_new;
        list->len++;
}

void DeleteEleDbLinkList(DList*list,pNODE p)
{
	if(p==list->tail)
	{
		p->pre->next=NULL;
		list->tail=p->pre;
		free(p->data);
		free(p);
		list->len--;
	}
	else
	{
		p->pre->next=p->next;
		p->next->pre=p->pre;
		free(p->data);
		free(p);
		list->len--;
	}
}


/*int DeleteEleDbLinkList(DList*list, int pos)
{
        pNODE p1 = list->head,p2=NULL;

        if (pos > 0 && pos < list->len + 1)
        {
                while (1)
                {
                        pos--;
                        if (0 == pos)
                                break;
                        p1 = p1->next;
                }

                p2 = p1->next;    //The location of the node to be delete 
                if(p2->next!=NULL)

                {
                        p1->next=p2->next;                
                        p2=p2->next;
                        free(p2->pre->data);
                        free(p2->pre); 
                        p2->pre=p1;
                        list->len=list->len-1;

                }

                else 
                {   free(p1->next->data);
                        free(p1->next);
                        p1->next=NULL;
                        list->tail=p1;
                        list->len=list->len-1;
                } 
                return 1;
        }
        else
                return 0;
}*/



pNODE LookForDbLinkList(DList*list,Elemtype key,int (*compare)(Elemtype elem1, Elemtype elem2))
{  
	pNODE p1=list->head->next;
    while(p1!=NULL)
    {
    	if(compare(p1->data, key)==0)
			return p1;
    	else
    		p1=p1->next;
    }
    return NULL;
} //takes 8s


void QuickSort(pNODE p_left,pNODE p_right,int left,int right,int (*compare)(Elemtype elem1, Elemtype elem2))
{
        if(left>=right)
        return;
        Elemtype key=p_left->data,temp;
        pNODE p1=p_left,p2=p_right;
        int i=left;
        int j=right;
        while(i<j)
        {
				while(i<j&&(compare(p_right->data,key)>=0))
                { p_right=p_right->pre;j--; }
                temp=p_left->data;
                p_left->data=p_right->data;

                p_right->data=temp;
                while(i<j&&(compare(p_left->data,key)<=0))
                { p_left=p_left->next;i++; }
                temp=p_left->data;
                p_left->data=p_right->data;
                p_right->data=temp;
        }
        QuickSort(p1,p_left->pre,left,i-1,compare);
        QuickSort(p_left->next,p2,i+1,right,compare); 
}

