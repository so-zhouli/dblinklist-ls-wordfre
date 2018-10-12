#include"dbll.h"


void combine_dbll(DList*list1,DList*list2)
{
    pNODE p_node1=list1->tail;
    pNODE p_node2=list2->head->next;
    if(p_node2==NULL)
        return;
    else
    {
        p_node1->next=p_node2;
        p_node2->pre=p_node1;
        list1->tail=list2->tail;
        list2->head->next=NULL;
    }
    return;
}

DList* create_dbll() //Create the first node 
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

void destory_dbll(DList* list)
{ 
        while(list->head->next!=NULL)
                delete_elem_dbll(list,list->head->next);
        free(list->head);
        free(list);
       // printf("List Destoryed!\n");
}



void reverse_dbll(DList*list)
{
	pNODE p_node1=list->tail;
	pNODE p_node2=NULL;
	list->head->next=p_node1;
	p_node2=p_node1->pre;
	p_node1->pre=list->head;
	p_node1->next=p_node2;
	p_node1=p_node2;
	while(p_node2->pre!=list->head)
	{
		p_node2=p_node1->pre;
		p_node1->pre=p_node1->next;
		p_node1->next=p_node2;
		p_node1=p_node2;
	}
	p_node1->pre=p_node1->next;
	p_node1->next=NULL;
	list->tail=p_node1;
}

int insert_elem_dbll(DList*list, int pos, Elemtype value)  //   Pos is the insertion position
{
        pNODE p_node1=list->head, p_node2=NULL,p_new = NULL;
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
                        p_node1 = p_node1->next;
                }

                if (NULL == p_node1->next)
                {
                        p_new->data = data;
                        p_new->next = NULL;
                        p_new->pre =p_node1;
                        p_node1->next=p_new;
                        list->tail=p_new;
                        list->len=list->len+1;
                }
                else
                {   
                        p_node2=p_node1->next;
                        p_new->data=data;
                        p_new->next=p_node2;
                        p_new->pre=p_node1;
                        p_node1->next=p_new;
                        p_node2->pre=p_new;
                        list->len=list->len+1;

                }
                return 1;
        }
        else
                return 0;

}

int tail_insert_elem_dbll(DList*list,Elemtype value)
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

void delete_elem_dbll(DList*list,pNODE p_node)
{
	if(p_node==list->tail)
	{
		p_node->pre->next=NULL;
		list->tail=p_node->pre;
		free(p_node->data);
		free(p_node);
		list->len--;
	}
	else
	{
		p_node->pre->next=p_node->next;
		p_node->next->pre=p_node->pre;
		free(p_node->data);
		free(p_node);
		list->len--;
	}
}

void travel_dbll(DList* list,data_operate_cb data_operate,void* aide_para)
{
	pNODE p_node=list->head->next;
	while(p_node!=NULL)
	{
		data_operate(p_node,aide_para);
		p_node=p_node->next;
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



pNODE search_elem_dbll(DList*list,Elemtype key,dbll_compare_cb compare)
{  
	pNODE p_node=list->head->next;
    while(p_node!=NULL)
    {
    	if(compare(p_node->data, key)==0)
			return p_node;
    	else
    		p_node=p_node->next;
    }
    return NULL;
} //takes 8s


void quick_sort_dbll(pNODE p_left,pNODE p_right,int left,int right,dbll_compare_cb compare)
{
        if(left>=right)
        return;
        Elemtype key=p_left->data,temp;
        pNODE p_node1=p_left,p_node2=p_right;
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
        quick_sort_dbll(p_node1,p_left->pre,left,i-1,compare);
        quick_sort_dbll(p_left->next,p_node2,i+1,right,compare); 
}

