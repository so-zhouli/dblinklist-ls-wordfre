#include"dbll.h"
#include"ls.h"




void do_ls(char *dirname,DList *list)
{
	DIR *dir_ptr;           // the directory
	struct dirent *direntp; // each entry
	
	if( (dir_ptr = opendir(dirname)) == NULL )
	{
		file_info* file_info_new=(file_info*)malloc(sizeof(file_info));
		if(lstat(dirname, &(file_info_new->stat_buf))<0)// cannot stat
		{
			free(file_info_new);
			printf("lstat error for %s",dirname);       // say why;/
		}
		else
		{
			file_info_new->filename_length=strlen(dirname);
			char* filename_new=(char*)malloc(sizeof(char)*(file_info_new->filename_length+1));
			char* filepath_new=(char*)malloc(sizeof(char)*(file_info_new->filename_length+1));
			strcpy(filename_new,dirname);
			strcpy(filepath_new,dirname);
			file_info_new->filename=filename_new;
			file_info_new->filepath=filepath_new;
			get_file_info(dirname,file_info_new);
			TailInsertElem(list,file_info_new);
		}
	}
	else
	{
		while( (direntp = readdir(dir_ptr)) != NULL )
		{
			file_info* file_info_new=(file_info*)malloc(sizeof(file_info));
			file_info_new->filename_length=strlen(direntp->d_name);
			char* filename_new=(char*)malloc(sizeof(char)*(file_info_new->filename_length+1));
			strcpy(filename_new,direntp->d_name);
			file_info_new->filename=filename_new;
			dostat(direntp->d_name,dirname,file_info_new);
			#ifdef DEBUG
				printf("%-3d",file_info_new->filename_length);
				printf("%-20s",file_info_new->filename);
				printf("%-15s",file_info_new->modestr);
				printf("%d\n",file_info_new->stat_buf.st_uid);
			#endif
			TailInsertElem(list,file_info_new);
		}
		closedir(dir_ptr);
	}
}
 
void dostat(char* filename,char* dirpath,file_info* file_info_new)
{
	char* filepath=(char*)malloc(sizeof(char)*(strlen(dirpath)+file_info_new->filename_length+2));
	strcpy(filepath,dirpath);
	strcat(filepath,"/");
	strcat(filepath,filename);
	file_info_new->filepath=filepath;
	if(lstat(filepath, &(file_info_new->stat_buf))<0)// cannot stat
	{
		perror(filename);       // say why;/
	}
	else  // else show information
	{
		get_file_info(filepath,file_info_new);
	}
}
 
/**
* display the information. The information is stored in stuct at *info_p
*/
void get_file_info(char* filepath,file_info* file_info_new)
{
	char *uid_to_name();
	char *ctime();
	char *gid_to_name();
	char *filemode();
 
	mode_to_letters(file_info_new->stat_buf.st_mode, file_info_new->modestr);
 
/*	printf("%s", modestr);
	printf("%4d ", (int)info_p->st_nlink);
	printf("%-8s", uid_to_name(info_p->st_uid) );
	printf("%-8s", gid_to_name(info_p->st_gid) );
	printf("%8ld ", (long)info_p->st_size);
	printf("%.12s ", 4 + ctime(&info_p->st_mtime));
	printf("%s\n", filename);*/
//	printf("%.10s\n",1+p->mtime);
//	printf("%.5s\n",1+p->mtime);
	if(file_info_new->modestr[0]=='l')
	{
		ssize_t size;
		char buf[100];
		if((size=readlink(filepath,buf,100))<0)
		{
			printf("readlink error for %s",filepath);
			return;
		}
		else
		{   
			buf[size]='\0';
			char *path=(char*)malloc((size+1)*sizeof(char));
			strcpy(path,buf);
	//		printf("%d\n",(int)strlen(path));
			file_info_new->linkfile=path;//第一次链接路径
		}
	//	printf("%s\n",p->linkfile);
		if(show_linkfile)
		{	
			if(stat(filepath,&(file_info_new->stat_buf))<0)
				printf("stat error for %s\n",filepath);
			else
			{
				mode_to_letters(file_info_new->stat_buf.st_mode,file_info_new->modestr);
			}
		//	readlink_absolutely(fi_new,dirpath);
		}
	}
}



void mode_to_letters(int mode, char *str)
{
	strcpy(str, "----------");         // defult = no perms
	
	if( S_ISDIR(mode) ) str[0] = 'd'; // directory
	if( S_ISCHR(mode) ) str[0] = 'c'; // char devices
	if( S_ISBLK(mode) ) str[0] = 'b'; // block device
	if( S_ISLNK(mode) ) str[0] = 'l'; // block device
	if( S_ISSOCK(mode)) str[0] = 's';
 
	if( mode & S_IRUSR) str[1] = 'r'; // 3 bits for user
	if( mode & S_IWUSR) str[2] = 'w';
    if( mode & S_IXUSR) str[3] = 'x';
 
    if( mode & S_IRGRP) str[4] = 'r'; // 3 bits for group
	if( mode & S_IWGRP) str[5] = 'w';
	if( mode & S_IXGRP) str[6] = 'x';
 
 
    if( mode & S_IROTH) str[7] = 'r'; // 3 bits for other
	if( mode & S_IWOTH) str[8] = 'w';
	if( mode & S_IXOTH) str[9] = 'x';
	if(mode &  S_ISVTX)//sticky bit
	{
		if(str[9]='x')
			str[9]='t';
		else
			str[9]='T';
	}
	if(mode & S_ISUID)//suid
	{
		if(str[3]='x')
			str[3]='s';
		else
			str[3]='S';
	}
	if(mode & S_ISGID)//sgid
	{
		if(str[6]='x')
			str[6]='s';
		else
			str[6]='S';
	}

}
/**
* the code above :get fileinfo
*/
char *uid_to_name(uid_t uid)
{
	struct passwd *getpwuid();
	struct passwd *pw_ptr;
	static char numstr[10];
 
	if( (pw_ptr = getpwuid(uid)) == NULL )
	{
		sprintf(numstr, "%d", uid);
		return numstr;
	}
	else
	{
		return pw_ptr->pw_name;
	}
}
 
/**
* return pointer to group number gid. used getgrgid(3)
*/
char *gid_to_name(gid_t gid)
{
	struct group *getgrgid();
	struct group *grp_ptr;
	static char numstr[10];
 
	if( (grp_ptr = getgrgid(gid)) == NULL )
	{
		sprintf(numstr, "%d", gid);
		return numstr;
	}
	else
	{
		return grp_ptr->gr_name;
	}
}



void delete_hidden_file(DList*list)//删除隐藏文件
{
	pNODE p1=list->head->next;
	pNODE p2=NULL;
	while(p1!=NULL)
	{
		if(((file_info*)(p1->data))->filename[0]=='.')
		{
			free(((file_info*)(p1->data))->filename);
			free(((file_info*)(p1->data))->filepath);
			p2=p1;
			p1=p1->next;
			DeleteEleDbLinkList(list,p2);
		}
		else
		{
			p1=p1->next;
		}
	}
}

void delete_dot_file(DList*list)//删除隐藏文件
{
	pNODE p1=list->head;
	pNODE p2=list->head;
	char*p_dot=".";
	char*p_dotdot="..";
	compare=compare_dot;
	while(p1!=NULL&&p2!=NULL)
	{
		p1=LookForDbLinkList(list,p_dot,compare);
		p2=LookForDbLinkList(list,p_dotdot,compare);
		if(p1!=NULL)
		{
			free(((file_info*)(p1->data))->filename);
			free(((file_info*)(p1->data))->filepath);
			DeleteEleDbLinkList(list,p1);
		}
		if(p2!=NULL)
		{
			free(((file_info*)(p2->data))->filename);
			free(((file_info*)(p2->data))->filepath);
			DeleteEleDbLinkList(list,p2);
		}
	}
}


void delete_backup_file(DList*list)//删除备份文件
{
	pNODE p1=list->head->next;
	pNODE p2=NULL;
	while(p1!=NULL)
	{
		if(*(((file_info*)(p1->data))->filename+((file_info*)(p1->data))->filename_length-1)=='~')
		{
			free(((file_info*)(p1->data))->filename);
			free(((file_info*)(p1->data))->filepath);
			p2=p1;
			p1=p1->next;
			DeleteEleDbLinkList(list,p2);
		}
		else
		{
			p1=p1->next;
		}
	}
}


int compare_name(void* elem1,void* elem2)
{   
	if(strcmp(((file_info*)elem1)->filename,".")==0&&strcmp(((file_info*)elem2)->filename,"..")==0)
		return -1;
	if(strcmp(((file_info*)elem2)->filename,".")==0&&strcmp(((file_info*)elem1)->filename,"..")==0)
		return 1;
	int i=0;
	int j=0;
	while(i<((file_info*)elem1)->filename_length+1&&j<((file_info*)elem2)->filename_length+1)
	{
		if(((file_info*)elem1)->filename[i]=='.')
			i++;
		if(((file_info*)elem2)->filename[j]=='.')
			j++;
		if(tolower(((file_info*)elem1)->filename[i])>tolower(((file_info*)elem2)->filename[j]))
			return 1;
		else if(tolower(((file_info*)elem1)->filename[i])<tolower(((file_info*)elem2)->filename[j]))
			return -1;
		else
		{
			i++;
			j++;
		}
	}

}

int compare_dot(void* elem1,void*elem2)
{
	if(strcmp(((file_info*)elem1)->filename,(char*)elem2)==0)
		return 0;
	else
		return 1;
}


int compare_size(void* elem1,void* elem2)
{
	if(((file_info*)elem1)->stat_buf.st_size-((file_info*)elem2)->stat_buf.st_size>0)
		return 1;
	else if(((file_info*)elem1)->stat_buf.st_size-((file_info*)elem2)->stat_buf.st_size<0)
		return -1;
	else
		return 0;
	
}


int compare_mtime(void* elem1,void* elem2)
{
	if(((file_info*)elem1)->stat_buf.st_mtime-((file_info*)elem2)->stat_buf.st_mtime>0)
		return 1;
	else if(((file_info*)elem1)->stat_buf.st_mtime-((file_info*)elem2)->stat_buf.st_mtime<0)
		return -1;
	else
		return 0;
}

int get_filename_width(DList*list)
{
	pNODE p1=list->head->next;
	int filename_length=0;
	while(p1!=NULL)
	{
		if(filename_length<((file_info*)(p1->data))->filename_length)
			filename_length=((file_info*)(p1->data))->filename_length;
		p1=p1->next;
	}
//	printf("%d\n",filename_length);
	return filename_length;
}


int get_inode_width(DList* list)
{
	pNODE p1=list->head->next;
	int inode_length=0;
	long int i;
	int j=0;
	while(p1!=NULL)
	{
		i=(long int)(((file_info*)(p1->data))->stat_buf.st_ino);
		if(i==0)
			j=1;
		while(i!=0)
		{
			i=i/10;
			j++;
		}
		if(inode_length<j)
			inode_length=j;
		j=0;
		p1=p1->next;
	}
	return inode_length;
}


int get_nlink_width(DList* list)
{
	pNODE p1=list->head->next;
	int nlink_length=0;
	long int i;
	int j=0;
	while(p1!=NULL)
	{
		i=(long int)(((file_info*)(p1->data))->stat_buf.st_nlink);
		if(i==0)
			j=1;
		while(i!=0)
		{
			i=i/10;
			j++;
		}
		if(nlink_length<j)
			nlink_length=j;
		j=0;
		p1=p1->next;
	}
	return nlink_length;
}

int get_uid_width(DList* list)
{
	pNODE p1=list->head->next;
	int uid_length=0;
	int i;
	int j=0;
	while(p1!=NULL)
	{
		if(numeric_uid_gid)
		{
			i=(int)(((file_info*)(p1->data))->stat_buf.st_uid);
			if(i==0)
				j=1;
			while(i!=0)
			{
				i=i/10;
				j++;
			}
		}
		else
			j=(int)(strlen(uid_to_name(((file_info*)(p1->data))->stat_buf.st_uid)));
		if(uid_length<j)
			uid_length=j;
		j=0;
		p1=p1->next;
	}
	return uid_length;

}


int get_gid_width(DList* list)
{
	pNODE p1=list->head->next;
	int gid_length=0;
	int i;
	int j=0;
	while(p1!=NULL)
	{
		if(numeric_uid_gid)
		{
			i=(int)(((file_info*)(p1->data))->stat_buf.st_gid);		
			if(i==0)
				j=1;
			while(i!=0)
			{
				i=i/10;
				j++;
			}
		}
		else
			j=(int)(strlen(gid_to_name(((file_info*)(p1->data))->stat_buf.st_gid)));
		if(gid_length<j)
			gid_length=j;
		j=0;
		p1=p1->next;
	}
	return gid_length;

}

int get_major_dev_width(DList* list)
{
	pNODE p1=list->head->next;
	int major_dev_length=0;
	int i;
	int j=0;
	while(p1!=NULL)
	{
		if(((file_info*)(p1->data))->modestr[0]=='c'||((file_info*)(p1->data))->modestr[0]=='b')
		{
			i=(int)(major(((file_info*)(p1->data))->stat_buf.st_rdev));		
			while(i!=0)
			{
				i=i/10;
				j++;
			}
		}
		if(major_dev_length<j)
			major_dev_length=j;
		j=0;
		p1=p1->next;
	}
	return major_dev_length;
	
}



int get_minor_dev_width(DList* list)
{
	pNODE p1=list->head->next;
	int minor_dev_length=0;
	int i;
	int j=0;
	while(p1!=NULL)
	{
		if(((file_info*)(p1->data))->modestr[0]=='c'||((file_info*)(p1->data))->modestr[0]=='b')
		{
			i=(int)(minor(((file_info*)(p1->data))->stat_buf.st_rdev));		
			while(i!=0)
			{
				i=i/10;
				j++;
			}
		}
		if(minor_dev_length<j)
			minor_dev_length=j;
		j=0;
		p1=p1->next;
	}
//	if(minor_dev_length>pw.size_width)
//		pw.size_width=minor_dev_length;
//	else
//		minor_dev_length=pw.size_width;
	return minor_dev_length;
	
}


int get_size_width(DList* list)
{
	pNODE p1=list->head->next;
	int size_length=0;
	long int i;
	int j=0;
	while(p1!=NULL)
	{
		i=(long int)(((file_info*)(p1->data))->stat_buf.st_size);
		if(i==0)
			j=1;
		while(i!=0)
		{
			i=i/10;
			j++;
		}
		if(size_length<j)
			size_length=j;
		j=0;
		p1=p1->next;
	}
	return size_length;
}

void get_print_width(DList* list)
{
	pw.filename_width=get_filename_width(list);
	pw.inode_width=get_inode_width(list);
	pw.nlink_width=get_nlink_width(list);
	pw.size_width=get_size_width(list);
//	printf("size:%d\n",pw.size_width);
	pw.uid_width=get_uid_width(list);
	pw.gid_width=get_gid_width(list);
	pw.major_dev_width=get_major_dev_width(list);
//	printf("major:%d\n",pw.major_dev_width);
	pw.minor_dev_width=get_minor_dev_width(list);
//	printf("minor:%d\n",pw.minor_dev_width);
}


int get_col_row_info(DList*list,int max_one_length)
{
	struct winsize size;
	ioctl(STDIN_FILENO,TIOCGWINSZ,&size);
	int rows;
	int cols;
	int row;
	int col;
	cols=size.ws_col/max_one_length;
//	printf("%d\n",size.ws_col);
//	printf("max_length:%d\n",max_filename_length);
//	printf("cols:%d\n",cols);
	rows=list->len/cols+(list->len%cols!=0);
	cols=list->len/rows+(list->len%rows!=0);//确定输出的行数和列数
	pNODE p1=list->head->next;
	for(col=1;col<=cols;col++)
	{
		for(row=1;row<=rows&&p1!=NULL;row++)
		{
			((file_info*)(p1->data))->row_label=row;
			((file_info*)(p1->data))->col_label=col;
			p1=p1->next;
		}
	}//确定链表里面每个文件应该放在哪一行,lie
	return rows;

}
int get_total(DList* list)
{
	pNODE p1=list->head->next;
	long int sum_size=0;
	int block_num=0;
	while(p1!=NULL)
	{
		block_num=block_num+((file_info*)(p1->data))->stat_buf.st_blocks;
		p1=p1->next;
	}
	return block_num/2;

}
void print_inode(pNODE p1,DList* list)
{
	if(print_with_inode)
		printf("%*ld ",pw.inode_width,(long int)(((file_info*)(p1->data))->stat_buf.st_ino));
}

void print_filename(pNODE p1,DList* list)
{
	if(((file_info*)(p1->data))->modestr[9]=='t')
	{
		printf(BLACK_GREEN"%s"NONE,((file_info*)(p1->data))->filename);
		print_spaces(PRINT_WIDTH);
	}
	else if(((file_info*)(p1->data))->modestr[3]=='s')	
	{
		printf(WHITE_RED"%s"NONE,((file_info*)(p1->data))->filename);
		print_spaces(PRINT_WIDTH);
		
	}
	else if(((file_info*)(p1->data))->modestr[0]=='l')	
	{
		printf(L_CYAN"%s"NONE,((file_info*)(p1->data))->filename);
		print_spaces(PRINT_WIDTH);
	}
	else if(((file_info*)(p1->data))->modestr[0]=='c'||((file_info*)(p1->data))->modestr[0]=='b')	
	{
		printf(L_YELLOW"%s"NONE,((file_info*)(p1->data))->filename);
		print_spaces(PRINT_WIDTH);
	}
	else if(((file_info*)(p1->data))->modestr[0]=='s')	
	{
		printf(L_MAGENTA"%s"NONE,((file_info*)(p1->data))->filename);
		print_spaces(PRINT_WIDTH);
	}
	else if(((file_info*)(p1->data))->modestr[0]=='d'&&((file_info*)(p1->data))->modestr[3]=='x')
	{
		printf(BLUE"%s"NONE,((file_info*)(p1->data))->filename);
		print_spaces(PRINT_WIDTH);
	}
	else if(((file_info*)(p1->data))->modestr[3]=='x')
	{
		printf(GREEN"%s"NONE,((file_info*)(p1->data))->filename);
		print_spaces(PRINT_WIDTH);
	}
	else
	{
		printf("%s",((file_info*)(p1->data))->filename);
		print_spaces(PRINT_WIDTH);
	}
}

void print_linkfile(pNODE p1,DList* list)
{
	if(((file_info*)(p1->data))->modestr[0]=='l'&&show_linkfile==false)
	{
		if(stat(((file_info*)(p1->data))->filepath,&(((file_info*)(p1->data))->stat_buf))<0)
			printf("stat error for %s\n",((file_info*)(p1->data))->filepath);
		else
		{
			mode_to_letters(((file_info*)(p1->data))->stat_buf.st_mode,((file_info*)(p1->data))->modestr);
		}
		if(((file_info*)(p1->data))->modestr[9]=='t')
		{
			printf(" -> ");
			printf(BLACK_GREEN"%s"NONE,((file_info*)(p1->data))->linkfile);
		}
		else if(((file_info*)(p1->data))->modestr[3]=='s')	
		{
			printf(" -> ");
			printf(WHITE_RED"%s"NONE,((file_info*)(p1->data))->linkfile);
		}
		else if(((file_info*)(p1->data))->modestr[0]=='l')	
		{
			printf(" -> ");
			printf(L_CYAN"%s"NONE, ((file_info*)(p1->data))->linkfile);
		}
		else if(((file_info*)(p1->data))->modestr[0]=='c'||((file_info*)(p1->data))->modestr[0]=='b')	
		{
			printf(" -> ");
			printf(L_YELLOW"%s"NONE, ((file_info*)(p1->data))->linkfile);
		}
		else if(((file_info*)(p1->data))->modestr[0]=='s')	
		{
			printf(" -> ");
			printf(L_MAGENTA"%s"NONE, ((file_info*)(p1->data))->linkfile);
		}
		else if(((file_info*)(p1->data))->modestr[0]=='d'&&((file_info*)(p1->data))->modestr[3]=='x')
		{
			printf(" -> ");
			printf(BLUE"%s"NONE, ((file_info*)(p1->data))->linkfile);
		}
		else if(((file_info*)(p1->data))->modestr[3]=='x')
		{
			printf(" -> ");
			printf(GREEN"%s"NONE,((file_info*)(p1->data))->linkfile);
		}
		else
		{
			printf(" -> ");
			printf("%s",((file_info*)(p1->data))->linkfile);
		}
	}
	
}

void print_uid_gid(pNODE p1,DList* list)
{
	if(numeric_uid_gid)
	{
		printf("%*d ", pw.uid_width,(int)(((file_info*)(p1->data))->stat_buf.st_uid));
		if(!list_no_group)
			printf("%*d ", pw.gid_width,(int)(((file_info*)(p1->data))->stat_buf.st_gid));
	}
	else
	{
		printf("%-*s ", pw.uid_width,uid_to_name(((file_info*)(p1->data))->stat_buf.st_uid));
		if(!list_no_group)
			printf("%-*s ", pw.gid_width,gid_to_name(((file_info*)(p1->data))->stat_buf.st_gid));
	}
}

void print_size_dev(pNODE p1, DList* list)
{
	if(pw.major_dev_width==0)
		printf("%*ld ",pw.size_width,((file_info*)(p1->data))->stat_buf.st_size);
	else if(((file_info*)(p1->data))->modestr[0]=='c'||((file_info*)(p1->data))->modestr[0]=='b')
	{
		if(DEV_WIDTH<pw.size_width)
			print_spaces(pw.size_width-DEV_WIDTH);
		printf("%*d, ",pw.major_dev_width,major(((file_info*)(p1->data))->stat_buf.st_rdev));
		printf("%*d ",pw.minor_dev_width,minor(((file_info*)(p1->data))->stat_buf.st_rdev));
	}
	else
	{
		if(DEV_WIDTH>pw.size_width)
			print_spaces(DEV_WIDTH-pw.size_width);
		print_spaces(2);
		printf("%*ld ",pw.size_width,((file_info*)(p1->data))->stat_buf.st_size);
	}
}


void show_filename(DList* list)
{
	pNODE p1=list->head->next;
	int flag=0;
	int max_one_length=pw.filename_width+1;//max_one_length include filename andinode(if exsit)
	if(print_with_inode)
	{
		flag=1;
		max_one_length=max_one_length+pw.inode_width+1;
	}
	int rows=get_col_row_info(list,max_one_length);
	int row;
	for(row=1;row<=rows;row++)
	{
		if(one_per_line&&row==2)
			break;
		pNODE p1=list->head->next;
		while(p1!=NULL)
		{
			if(((file_info*)(p1->data))->row_label==row||one_per_line)
			{
				print_inode(p1,list);
				print_filename(p1,list);
				if(one_per_line)
				printf("\n");
					
			}
			p1=p1->next;
		}
		if(!one_per_line)
			printf("\n");
	}
}

	

void show_list(DList* list)
{
	pNODE p1=list->head->next;
	printf("total %d\n",get_total(list));
	while(p1!=NULL)
	{
		print_inode(p1,list);
		printf("%s ", ((file_info*)(p1->data))->modestr);
		printf("%*d ",pw.nlink_width, (int)(((file_info*)(p1->data))->stat_buf.st_nlink));
		print_uid_gid(p1,list);
		print_size_dev(p1,list);
	//	printf("%*ld ",7,((file_info*)(p1->data))->stat_buf.st_size);
		printf("%.12s ", 4 +ctime(&((file_info*)(p1->data))->stat_buf.st_mtime));
		print_filename(p1,list);
		print_linkfile(p1,list);
		printf("\n");
		p1=p1->next;
	}
}



void init_value()
{
	delete_dot_and_dotdot=false;
	delete_backup=false;
	reserve_all=false;
	one_per_line=false;
	list_no_group=false;
	print_with_inode=false;
	show_linkfile=false;
	numeric_uid_gid=false;
	print_list=false;
}

void init_width()
{
	pw.filename_width=0;
	pw.inode_width=0;
	pw.nlink_width=0;
	pw.uid_width=0;
	pw.gid_width=0;
	pw.major_dev_width=0;
	pw.minor_dev_width=0;
	pw.size_width=0;
}

void free_data(DList* list)
{
	pNODE p1=list->head->next;
	while(p1!=NULL)
	{
		free(((file_info*)(p1->data))->filename);
		free(((file_info*)(p1->data))->filepath);
		if(((file_info*)(p1->data))->modestr[0]=='l')
			free(((file_info*)(p1->data))->linkfile);
		p1=p1->next;
	}
}



void print_spaces(int num)
{
	while(num--)
		printf(" ");

}
