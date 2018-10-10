#include"dbll.h"
#include"wordfre.h"


void find_word_insert(word*ahead,DList*list,DList*total_list)
{
    if(compare==compare_findword)
		printf("compare_findword\n");
	pNODE p=LookForDbLinkList(list,ahead,compare);
    if(p==NULL)
    {
         word* p_new=(word*)malloc(sizeof(word));
         strcpy(p_new->w,ahead->w);
         p_new->num=1;
         p_new->pos=total_list->len+1;
         TailInsertElem(list,p_new);
         total_list->len++;
    }  
    else
        ((word*)(p->data))->num++;

}

void operate(DList*word_list[27],char filename[])
{  
	int i=0,j,t=0;
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
        list_combine(word_list[0],word_list[combine_num++]);
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
    int t1=0;
    int t2=0;
    int t3=0;
    int t4=0;
    int opt=0;
    int flag_create_case=0;
    int flag_create=0;
    int flag_word=0;
    int flag_num=0;
    int flag_pos=0;
    int flag_show=0;
    int flag_reverseshow=0;
    int option_index=0;
    int list_num=0;
    DList*word_list[27];
    while(list_num<27)
    {
        word_list[list_num++]=CreateDbLinkList();
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
                flag_create_case=1;
                break;
            case 'C':
                flag_create=1;
                break;
            case 'w':
                flag_word=1;
                break;
            case 'n':
                flag_num=1;
                break;
            case 'p':
                flag_pos=1;
                break;
            case 's':
                flag_show=1;
                break;
            case 'S':
                flag_reverseshow=1;
                break;
            default:exit(0);

        }
    }
    if((flag_create_case&&flag_create)||(flag_word+flag_num+flag_pos>1)||(flag_show&&flag_reverseshow))
    {    
        printf("command conflict!\n");
        return -1;
    }
    if((flag_create_case||flag_create)==0)
    {    
        printf("command illegal!--'c'or'C'is neccessary for operate.\n");
        return -1;
    }
    if(flag_create_case)
        compare=compare_findword_case;
    else
        compare=compare_findword;
    t1=clock();
    operate(word_list,filename);
    t2=clock();
    if(flag_num||flag_word||flag_pos)
    {
        if(flag_num)
            compare=compare_num;
        else if(flag_pos)
            compare=compare_pos;
        else if(flag_create)
            compare=compare_word;
        else
            compare=compare_word_case;
            
        t3=clock();
        QuickSort(word_list[0]->head->next,word_list[0]->tail,1,word_list[0]->len,compare);
        t4=clock();
    }
    if(flag_show||flag_reverseshow)
    {
        if(flag_show)
            show=showDbLinkList;
        else
            show=reverseshowDbLinkList;
        show(word_list[0]);
    }
    printf("total_lenth:%d\n",word_list[0]->len);
    list_num=0;
    while(list_num<27)
    {
        Destory(word_list[list_num++]);
    }
    printf("create time:%d\n",t2-t1);
    printf("quick sort time:%d\n",t4-t3);
    return 0;
}

