#include"dbll.h"
#include"wordfre.h"

/*search the word in the word list,if already exist,then let the num to one,else insert the new word */
void find_word_insert(word*ahead,DList*list,DList*total_list)
{
	pNODE p;
	if(opt_create_case)
		p=search_elem_dbll(list,ahead,compare_findword_case);
    else
		p=search_elem_dbll(list,ahead,compare_findword);
    if(p==NULL)
    {
         word* p_new=(word*)malloc(sizeof(word));
         strcpy(p_new->w,ahead->w);
         p_new->num=1;
         p_new->pos=total_list->len+1;
         tail_insert_elem_dbll(list,p_new);
         total_list->len++;
    }  
    else
        ((word*)(p->data))->num++;

}
/* read paper*/
void operate(DList*word_list[27],char filename[])
{  
	int i=0,j;
	int flag=0;
	word*ahead=(word*)malloc(sizeof(word));
	FILE*fp;
    int len;
    char buf[MAX_LINE];
	if((fp=fopen(filename,"r"))==NULL)
	{
		printf("open file failed!\n");
		exit(0);
    }
    while(fgets(buf,MAX_LINE,fp)!=NULL)
    {
            len=strlen(buf);
            if(buf[len-1]!='\n')
            {
                    printf("buf is not enough!\n");
                    return ;
            }
         //   printf("%s  %d\n",buf,len);
            for(j=0;j<len;j++)//len而不是len-1，防止某一行是以字母结尾，遗漏该单词
            {
                    if((isalpha(buf[j]))||(buf[j]==39))//36 为'\''
                    {     if(i>WORD_LEN-1)
                          {  
                          printf("the word is:%s\n",ahead->w);
                          printf("word lenth longer than array!\n");
                          return ;
                          }       //单词长度控制
                            ahead->w[i++]=buf[j];
                            if(ahead->w[0]==39)
                                    i=0;
                            else
                                    flag=1;

                    }
                    else if(flag==1)
                    {   
                            if(ahead->w[i-1]==39)
                                    ahead->w[i-1]=0;//结束符
                            else
                                    ahead->w[i]=0;
                            switch(ahead->w[0])
                            {
                                case 'a':
                                case 'A':find_word_insert(ahead,word_list[1],word_list[0]);break;
                                case 'b':
                                case 'B':find_word_insert(ahead,word_list[2],word_list[0]);break;
                                case 'c':
                                case 'C':find_word_insert(ahead,word_list[3],word_list[0]);break;
                                case 'd':
                                case 'D':find_word_insert(ahead,word_list[4],word_list[0]);break;
                                case 'e':
                                case 'E':find_word_insert(ahead,word_list[5],word_list[0]);break;
                                case 'f':
                                case 'F':find_word_insert(ahead,word_list[6],word_list[0]);break;
                                case 'g':
                                case 'G':find_word_insert(ahead,word_list[7],word_list[0]);break;
                                case 'h':
                                case 'H':find_word_insert(ahead,word_list[8],word_list[0]);break;
                                case 'i':
                                case 'I':find_word_insert(ahead,word_list[9],word_list[0]);break;
                                case 'j':
                                case 'J':find_word_insert(ahead,word_list[10],word_list[0]);break;
                                case 'k':
                                case 'K':find_word_insert(ahead,word_list[11],word_list[0]);break;
                                case 'l':
                                case 'L':find_word_insert(ahead,word_list[12],word_list[0]);break;
                                case 'm':
                                case 'M':find_word_insert(ahead,word_list[13],word_list[0]);break;
                                case 'n':
                                case 'N':find_word_insert(ahead,word_list[14],word_list[0]);break;
                                case 'o':
                                case 'O':find_word_insert(ahead,word_list[15],word_list[0]);break;
                                case 'p':
                                case 'P':find_word_insert(ahead,word_list[16],word_list[0]);break;
                                case 'q':
                                case 'Q':find_word_insert(ahead,word_list[17],word_list[0]);break;
                                case 'r':
                                case 'R':find_word_insert(ahead,word_list[18],word_list[0]);break;
                                case 's':
                                case 'S':find_word_insert(ahead,word_list[19],word_list[0]);break;
                                case 't':
                                case 'T':find_word_insert(ahead,word_list[20],word_list[0]);break;
                                case 'u':
                                case 'U':find_word_insert(ahead,word_list[21],word_list[0]);break;
                                case 'v':
                                case 'V':find_word_insert(ahead,word_list[22],word_list[0]);break;
                                case 'w':
                                case 'W':find_word_insert(ahead,word_list[23],word_list[0]);break;
                                case 'x':
                                case 'X':find_word_insert(ahead,word_list[24],word_list[0]);break;
                                case 'y':
                                case 'Y':find_word_insert(ahead,word_list[25],word_list[0]);break;
                                case 'z':
                                case 'Z':find_word_insert(ahead,word_list[26],word_list[0]);break;
                                default:printf("word illagal!\n");return;
                            }
                            i=0;
                            flag=0;
                    }
            }


    }
    int combine_num=1;
    while(combine_num<27)
        combine_dbll(word_list[0],word_list[combine_num++]);
    free(ahead); 
    fclose(fp);
    //printf("lookfor time:%d\n",t);
}

void help(void)
{
                printf("Usage: ./WORK -o[filename] -c[option]\n");
                printf(" or  : ./WORK -c[option] -o[filename]\n");
                printf(" the options are as follow:\n");
                printf("-o:get filename\n");
                printf("-c:create word list\n");
                printf("-C:create word list(ignore capitalization)\n");
                printf("-w:sort the word list by dictionary order\n");
                printf("-n:sort the word list by the number of occurences\n");
                printf("-p:sort the word list by the order of appearance\n");
                printf("-s:show the word list in ascending order\n");
                printf("-S:show the word list in descending order\n");
                printf("--help:display this help and exit\n");
                printf("'-C'and'-c'are neccessary options while running\n");
}       

int main(int argc,char* argv[])
{   
    int opt=0;
    int option_index=0;
    int list_num=0;
    DList*word_list[27];
    while(list_num<27)
    {
        word_list[list_num++]=create_dbll();
    }
    char filename[60];
    static struct option long_options[]=
    {
        {"help",no_argument,0,'h'},
        {0,0,0,0},
    };
    while((opt=getopt_long(argc,argv,"ho:cCwnpsS",long_options,&option_index))!=-1)
    {
        switch(opt)
        {
            case 'h':
                help();
                exit(0);
            case 'o':
                strcpy(filename,optarg);
                break;
            case 'c':
                opt_create_case=true;
                break;
            case 'C':
                opt_create=true;
                break;
            case 'w':
                opt_word_sort=true;
                break;
            case 'n':
                opt_num_sort=true;
                break;
            case 'p':
                opt_pos_sort=true;
                break;
            case 's':
                opt_show=true;
                break;
            case 'S':
                opt_reverse_show=true;
                break;
            default:exit(0);

        }
    }
    if((opt_create_case&&opt_create)||(opt_word_sort+opt_num_sort+opt_pos_sort>1)||(opt_show&&opt_reverse_show))
    {    
        printf("command conflict!\n");
        return -1;
    }
    if((opt_create_case||opt_create)==0)
    {    
        printf("command illegal!--'c'or'C'is neccessary for operate.\n");
        return -1;
    }
    operate(word_list,filename);
    //quicksort by word or pos num
	if(opt_num_sort||opt_word_sort||opt_pos_sort)
    {
		if(opt_num_sort)
 	    	quick_sort_dbll(word_list[0]->head->next,word_list[0]->tail,1,word_list[0]->len,compare_num);
        else if(opt_pos_sort)
        	quick_sort_dbll(word_list[0]->head->next,word_list[0]->tail,1,word_list[0]->len,compare_pos);
        else if(opt_create)
        	quick_sort_dbll(word_list[0]->head->next,word_list[0]->tail,1,word_list[0]->len,compare_word);
        else
        	quick_sort_dbll(word_list[0]->head->next,word_list[0]->tail,1,word_list[0]->len,compare_word_case);
            
    }
    if(opt_show||opt_reverse_show)
    {
        if(opt_reverse_show)
            reverse_dbll(word_list[0]);
		show_word_list(word_list[0]);
    }
    list_num=0;
    while(list_num<27)
    {
        destory_dbll(word_list[list_num++]);
    }
    return 0;
}

