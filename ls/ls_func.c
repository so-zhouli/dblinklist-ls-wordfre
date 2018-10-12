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
			printf("lstat error for %s\n",dirname);       // say why;/
			return;
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
			tail_insert_elem_dbll(list,file_info_new);
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
			tail_insert_elem_dbll(list,file_info_new);
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
	else
		file_info_new->linkfile=NULL;
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
	pNODE p_node=list->head;
	char *first_char=".";
	dbll_compare_cb compare;
	compare=compare_first_char;
	while(p_node!=NULL)
	{
		p_node=search_elem_dbll(list,first_char,compare);
		if(p_node!=NULL)
		{
			free(((file_info*)(p_node->data))->filename);
			free(((file_info*)(p_node->data))->filepath);
			delete_elem_dbll(list,p_node);
		}	
	}
}



void delete_dot_file(DList*list)//删除隐藏文件
{
	pNODE p_node=list->head;
	pNODE p_node1=list->head;
	char*p_dot=".";
	char*p_dotdot="..";
	dbll_compare_cb compare;
	compare=compare_dot;
	while(p_node!=NULL&&p_node1!=NULL)
	{
		p_node=search_elem_dbll(list,p_dot,compare);
		p_node1=search_elem_dbll(list,p_dotdot,compare);
		if(p_node!=NULL)
		{
			free(((file_info*)(p_node->data))->filename);
			free(((file_info*)(p_node->data))->filepath);
			delete_elem_dbll(list,p_node);
		}
		if(p_node1!=NULL)
		{
			free(((file_info*)(p_node1->data))->filename);
			free(((file_info*)(p_node1->data))->filepath);
			delete_elem_dbll(list,p_node1);
		}
	}
}


void delete_backup_file(DList*list)//删除备份文件
{
	pNODE p_node=list->head;
	char* last_char="~";
	dbll_compare_cb compare;
	compare=compare_last_char;
	while(p_node!=NULL)
	{
		p_node=search_elem_dbll(list,last_char,compare);
		if(p_node!=NULL)
		{
			free(((file_info*)(p_node->data))->filename);
			free(((file_info*)(p_node->data))->filepath);
			delete_elem_dbll(list,p_node);
		}
	}
}


int compare_last_char(void* elem1,void* elem2)
{
	if(*(((file_info*)elem1)->filename+((file_info*)elem1)->filename_length-1)==*((char*)elem2))
		return 0;
	else
		return -1;
		
}


int compare_first_char(void* elem1,void* elem2)
{
	if(*(((file_info*)elem1)->filename)==*((char*)elem2))
		return 0;
	else
		return -1;
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

void get_filename_width(DList*list)
{
	char* p_null=NULL;
	travel_dbll(list,filename_operate,p_null);
}

void filename_operate(pNODE p_node,void* aide_para)
{
	if(pw.filename_width<((file_info*)(p_node->data))->filename_length)
		pw.filename_width=((file_info*)(p_node->data))->filename_length;
}

void get_inode_width(DList*list)
{
	char* p_null=NULL;
	travel_dbll(list,inode_operate,p_null);
}

void inode_operate(pNODE p_node,void* aide_para)
{
	long int inode_value=0;
	int inode_len=0;
	inode_value=(long int)(((file_info*)(p_node->data))->stat_buf.st_ino);
	if(inode_value==0)
		inode_len=1;
	while(inode_value!=0)
	{
		inode_value=inode_value/10;
		inode_len++;
	}
	if(pw.inode_width<inode_len)
		pw.inode_width=inode_len;
}

void get_nlink_width(DList*list)
{
	char* p_null=NULL;
	travel_dbll(list,nlink_operate,p_null);
}

void nlink_operate(pNODE p_node,void* aide_para)
{
	long int nlink_value=0;
	int nlink_len=0;
	nlink_value=(long int)(((file_info*)(p_node->data))->stat_buf.st_nlink);
	if(nlink_value==0)
		nlink_len=1;
	while(nlink_value!=0)
	{
		nlink_value=nlink_value/10;
		nlink_len++;
	}
	if(pw.nlink_width<nlink_len)
		pw.nlink_width=nlink_len;
}

void get_size_width(DList*list)
{
	char* p_null=NULL;
	travel_dbll(list,size_operate,p_null);
}

void size_operate(pNODE p_node,void* aide_para)
{
	long int size_value=0;
	int size_len=0;
	size_value=(long int)(((file_info*)(p_node->data))->stat_buf.st_size);
	if(size_value==0)
		size_len=1;
	while(size_value!=0)
	{
		size_value=size_value/10;
		size_len++;
	}
	if(pw.size_width<size_len)
		pw.size_width=size_len;
}

void get_uid_width(DList* list)
{
	char* p_null=NULL;
	travel_dbll(list,uid_operate,p_null);
}

void uid_operate(pNODE p_node,void* aide_para)
{
	int uid_value=0;
	int uid_len=0;
	if(numeric_uid_gid)
	{
		uid_value=(int)(((file_info*)(p_node->data))->stat_buf.st_uid);
		if(uid_value==0)
			uid_len=1;
		while(uid_value!=0)
		{
			uid_value=uid_value/10;
			uid_len++;
		}
	}
	else
		uid_len=(int)(strlen(uid_to_name(((file_info*)(p_node->data))->stat_buf.st_uid)));
	if(pw.uid_width<uid_len)
		pw.uid_width=uid_len;
}

void get_gid_width(DList* list)
{
	char* p_null=NULL;
	travel_dbll(list,gid_operate,p_null);
}

void gid_operate(pNODE p_node,void* aide_para)
{
	int gid_value=0;
	int gid_len=0;
	if(numeric_uid_gid)
	{
		gid_value=(int)(((file_info*)(p_node->data))->stat_buf.st_gid);
		if(gid_value==0)
			gid_len=1;
		while(gid_value!=0)
		{
			gid_value=gid_value/10;
			gid_len++;
		}
	}
	else
		gid_len=(int)(strlen(gid_to_name(((file_info*)(p_node->data))->stat_buf.st_gid)));
	if(pw.gid_width<gid_len)
		pw.gid_width=gid_len;
}


void get_major_dev_width(DList* list)
{
	char* p_null=NULL;
	travel_dbll(list,major_dev_operate,p_null);
}

void major_dev_operate(pNODE p_node,void* aide_para)
{
	int major_dev_value=0;
	int major_dev_len=0;
	if(((file_info*)(p_node->data))->modestr[0]=='c'||((file_info*)(p_node->data))->modestr[0]=='b')
	{
		major_dev_value=(int)(major(((file_info*)(p_node->data))->stat_buf.st_rdev));		
		while(major_dev_value!=0)
		{
			major_dev_value=major_dev_value/10;
			major_dev_len++;
		}
	}
	if(pw.major_dev_width<major_dev_len)
		pw.major_dev_width=major_dev_len;
}

void get_minor_dev_width(DList* list)
{
	char* p_null=NULL;
	travel_dbll(list,minor_dev_operate,p_null);
}

void minor_dev_operate(pNODE p_node,void* aide_para)
{
	int minor_dev_value=0;
	int minor_dev_len=0;
	if(((file_info*)(p_node->data))->modestr[0]=='c'||((file_info*)(p_node->data))->modestr[0]=='b')
	{
		minor_dev_value=(int)(minor(((file_info*)(p_node->data))->stat_buf.st_rdev));		
		while(minor_dev_value!=0)
		{
			minor_dev_value=minor_dev_value/10;
			minor_dev_len++;
		}
	}
	if(pw.minor_dev_width<minor_dev_len)
		pw.minor_dev_width=minor_dev_len;
}


void get_print_width(DList* list)
{
	get_filename_width(list);
	get_inode_width(list);
	get_nlink_width(list);
	get_size_width(list);
//	printf("size:%d\n",pw.size_width);
	get_uid_width(list);
	get_gid_width(list);
	get_major_dev_width(list);
//	printf("major:%d\n",pw.major_dev_width);
	get_minor_dev_width(list);
//	printf("minor:%d\n",pw.minor_dev_width);
}


int get_col_row_info(DList*list,int max_one_length)
{
	
	struct winsize size;
	ioctl(STDIN_FILENO,TIOCGWINSZ,&size);
	int rows;
	int cols;
	int i=0;
	int col=1;
	col_row_info* p_col_row=malloc(sizeof(col_row_info));
	cols=size.ws_col/max_one_length;
//	printf("size.ws_col:%d\n",size.ws_col);
//	printf("max_length:%d\n",max_filename_length);
//	printf("cols:%d\n",cols);
	rows=list->len/cols+(list->len%cols!=0);
	cols=list->len/rows+(list->len%rows!=0);//确定输出的行数和列数
	p_col_row->rows=rows;
	p_col_row->cols=cols;
//	printf("rows:%d   cols:%d\n",rows,cols);
	while(rows!=0)
	{
		int col_width_array[cols];//每列文件名最大长度
		int sum_col_width=0;
		for(i=0;i<cols;i++)
			col_width_array[i]=0;
		p_col_row->col_width=col_width_array;
		p_col_row->row=1;
		p_col_row->col=1;
		travel_dbll(list,caculate_col_width_operate,p_col_row);
		for(i=0;i<cols;i++)
		{
			sum_col_width+=col_width_array[i];
		//	printf("col:%d  width:%d\n",i+1,col_width_array[i]);
		//	printf("\n");
		}
	//	printf("sum:%d\n",sum_col_width);
	//	printf("inode:%d\n",pw.inode_width*(print_with_inode?1:0));
		if((sum_col_width+cols*2+(pw.inode_width+1)*cols*(print_with_inode?1:0))>size.ws_col)
		{
			p_col_row->rows++;
			p_col_row->cols=list->len/p_col_row->rows+(list->len%p_col_row->rows!=0);
			break;
		}
		if(rows-1==0)
			break;
		rows--;
		cols=list->len/rows+(list->len%rows!=0);//确定输出的行数和列数
		p_col_row->rows=rows;
		p_col_row->cols=cols;
	}
//	printf("final rows:%d  final cols:%d\n",p1->rows,p1->cols);
	p_col_row->row=1;
	p_col_row->col=1;
	travel_dbll(list,label_col_row_operate,p_col_row);//遍历，每个文件名添加行列标志
	rows=p_col_row->rows;
	free(p_col_row);
	return rows;
}

void caculate_col_width_operate(pNODE p_node,void* aide_para)
{
	col_row_info* p_col_row=(col_row_info*)aide_para;
	if(p_col_row->row<=p_col_row->rows)
	{
	//	printf("11\n");
		if(*(p_col_row->col_width+p_col_row->col-1)<((file_info*)(p_node->data))->filename_length)
			*(p_col_row->col_width+p_col_row->col-1)=((file_info*)(p_node->data))->filename_length;
		p_col_row->row++;
	//	printf("33");
	}
	else
	{
	//	printf("22");
		p_col_row->col++;
		p_col_row->row=1;
		if(*(p_col_row->col_width+p_col_row->col-1)<((file_info*)(p_node->data))->filename_length)
			*(p_col_row->col_width+p_col_row->col-1)=((file_info*)(p_node->data))->filename_length;
		p_col_row->row++;
	}
}

void label_col_row_operate(pNODE p_node,void* aide_para)
{
	col_row_info* p_col_row=(col_row_info*)aide_para;
	if(p_col_row->col<=p_col_row->cols)
	{
		if(p_col_row->row<=p_col_row->rows)
		{
			((file_info*)(p_node->data))->row_label=p_col_row->row;
			((file_info*)(p_node->data))->col_label=p_col_row->col;
			p_col_row->row++;
		}
		else
		{
			p_col_row->col++;
			p_col_row->row=1;
			((file_info*)(p_node->data))->row_label=p_col_row->row;
			((file_info*)(p_node->data))->col_label=p_col_row->col;
			p_col_row->row++;
		}
	}

}

int get_total(DList* list)
{
	int block_num=0;
	travel_dbll(list,get_total_operate,&block_num);
	return block_num/2;

}

void get_total_operate(pNODE p_node,void *aide_para)
{
	int *p_block_num=(int*)aide_para;
	*p_block_num+=((file_info*)(p_node->data))->stat_buf.st_blocks;
}


void print_inode(pNODE p_node)
{
	if(print_with_inode)
		printf("%*ld ",pw.inode_width,(long int)(((file_info*)(p_node->data))->stat_buf.st_ino));
}

void print_filename(pNODE p_node,int fmt_width)
{
	if(((file_info*)(p_node->data))->modestr[9]=='t')
	{
		printf(BLACK_GREEN"%s"NONE,((file_info*)(p_node->data))->filename);
		print_spaces(PRINT_WIDTH);
	}
	else if(((file_info*)(p_node->data))->modestr[3]=='s')	
	{
		printf(WHITE_RED"%s"NONE,((file_info*)(p_node->data))->filename);
		print_spaces(PRINT_WIDTH);
		
	}
	else if(((file_info*)(p_node->data))->modestr[0]=='l')	
	{
		printf(L_CYAN"%s"NONE,((file_info*)(p_node->data))->filename);
		print_spaces(PRINT_WIDTH);
	}
	else if(((file_info*)(p_node->data))->modestr[0]=='c'||((file_info*)(p_node->data))->modestr[0]=='b')	
	{
		printf(L_YELLOW"%s"NONE,((file_info*)(p_node->data))->filename);
		print_spaces(PRINT_WIDTH);
	}
	else if(((file_info*)(p_node->data))->modestr[0]=='s')	
	{
		printf(L_MAGENTA"%s"NONE,((file_info*)(p_node->data))->filename);
		print_spaces(PRINT_WIDTH);
	}
	else if(((file_info*)(p_node->data))->modestr[0]=='d'&&((file_info*)(p_node->data))->modestr[3]=='x')
	{
		printf(BLUE"%s"NONE,((file_info*)(p_node->data))->filename);
		print_spaces(PRINT_WIDTH);
	}
	else if(((file_info*)(p_node->data))->modestr[3]=='x')
	{
		printf(GREEN"%s"NONE,((file_info*)(p_node->data))->filename);
		print_spaces(PRINT_WIDTH);
	}
	else
	{
		printf("%s",((file_info*)(p_node->data))->filename);
		print_spaces(PRINT_WIDTH);
	}
}

void print_linkfile(pNODE p_node)
{
	if(((file_info*)(p_node->data))->modestr[0]=='l'&&show_linkfile==false)
	{
		if(stat(((file_info*)(p_node->data))->filepath,&(((file_info*)(p_node->data))->stat_buf))<0)
			printf("stat error for %s\n",((file_info*)(p_node->data))->filepath);
		else
		{
			mode_to_letters(((file_info*)(p_node->data))->stat_buf.st_mode,((file_info*)(p_node->data))->modestr);
		}
		if(((file_info*)(p_node->data))->modestr[9]=='t')
		{
			printf(" -> ");
			printf(BLACK_GREEN"%s"NONE,((file_info*)(p_node->data))->linkfile);
		}
		else if(((file_info*)(p_node->data))->modestr[3]=='s')	
		{
			printf(" -> ");
			printf(WHITE_RED"%s"NONE,((file_info*)(p_node->data))->linkfile);
		}
		else if(((file_info*)(p_node->data))->modestr[0]=='l')	
		{
			printf(" -> ");
			printf(L_CYAN"%s"NONE, ((file_info*)(p_node->data))->linkfile);
		}
		else if(((file_info*)(p_node->data))->modestr[0]=='c'||((file_info*)(p_node->data))->modestr[0]=='b')	
		{
			printf(" -> ");
			printf(L_YELLOW"%s"NONE, ((file_info*)(p_node->data))->linkfile);
		}
		else if(((file_info*)(p_node->data))->modestr[0]=='s')	
		{
			printf(" -> ");
			printf(L_MAGENTA"%s"NONE, ((file_info*)(p_node->data))->linkfile);
		}
		else if(((file_info*)(p_node->data))->modestr[0]=='d'&&((file_info*)(p_node->data))->modestr[3]=='x')
		{
			printf(" -> ");
			printf(BLUE"%s"NONE, ((file_info*)(p_node->data))->linkfile);
		}
		else if(((file_info*)(p_node->data))->modestr[3]=='x')
		{
			printf(" -> ");
			printf(GREEN"%s"NONE,((file_info*)(p_node->data))->linkfile);
		}
		else
		{
			printf(" -> ");
			printf("%s",((file_info*)(p_node->data))->linkfile);
		}
	}
	
}

void print_uid_gid(pNODE p_node)
{
	if(numeric_uid_gid)
	{
		printf("%*d ", pw.uid_width,(int)(((file_info*)(p_node->data))->stat_buf.st_uid));
		if(!list_no_group)
			printf("%*d ", pw.gid_width,(int)(((file_info*)(p_node->data))->stat_buf.st_gid));
	}
	else
	{
		printf("%-*s ", pw.uid_width,uid_to_name(((file_info*)(p_node->data))->stat_buf.st_uid));
		if(!list_no_group)
			printf("%-*s ", pw.gid_width,gid_to_name(((file_info*)(p_node->data))->stat_buf.st_gid));
	}
}

void print_size_dev(pNODE p_node)
{
	if(pw.major_dev_width==0)
		printf("%*ld ",pw.size_width,((file_info*)(p_node->data))->stat_buf.st_size);
	else if(((file_info*)(p_node->data))->modestr[0]=='c'||((file_info*)(p_node->data))->modestr[0]=='b')
	{
		if(DEV_WIDTH<pw.size_width)
			print_spaces(pw.size_width-DEV_WIDTH);
		printf("%*d, ",pw.major_dev_width,major(((file_info*)(p_node->data))->stat_buf.st_rdev));
		printf("%*d ",pw.minor_dev_width,minor(((file_info*)(p_node->data))->stat_buf.st_rdev));
	}
	else
	{
		if(DEV_WIDTH>pw.size_width)
			print_spaces(DEV_WIDTH-pw.size_width);
		print_spaces(2);
		printf("%*ld ",pw.size_width,((file_info*)(p_node->data))->stat_buf.st_size);
	}
}


void show_filename(DList* list)
{
	int flag=0;
	int i_col;
	int max_one_length=pw.filename_width+2;//max_one_length include filename andinode(if exsit)
	if(print_with_inode)
	{
		flag=1;
		max_one_length=max_one_length+pw.inode_width+1;
	}
	col_row_info* p_col_row=malloc(sizeof(col_row_info));
	int row;
	int rows=get_col_row_info(list,max_one_length);
	p_col_row->rows=rows;
	p_col_row->cols=list->len/p_col_row->rows+(list->len%p_col_row->rows!=0);
	p_col_row->col=1;
	p_col_row->row=1;
//	printf("row:%d col:%d\n",p1->rows,p1->cols);
	int col_width_array[p_col_row->cols];
	for(i_col=0;i_col<p_col_row->cols;i_col++)
		col_width_array[i_col]=0;
	p_col_row->col_width=col_width_array;
//	printf("here\n");
	travel_dbll(list,caculate_col_width_operate,p_col_row);
//	printf("hre\n");
	for(p_col_row->row=1;p_col_row->row<=p_col_row->rows;p_col_row->row++)
	{
		if(one_per_line&&row==2)
			break;
		travel_dbll(list,show_filename_operate,p_col_row);
		if(!one_per_line)
			printf("\n");
	}
	free(p_col_row);
}


void show_filename_operate(pNODE p_node,void* aide_para)
{
	col_row_info *p1=(col_row_info*)aide_para;
	if(((file_info*)(p_node->data))->row_label==p1->row||one_per_line)
	{
		print_inode(p_node);
		print_filename(p_node,*(p1->col_width+((file_info*)(p_node->data))->col_label-1));
		if(one_per_line)
			printf("\n");
	}
}
	

void show_list(DList* list)
{
	char* p_null=NULL;
	printf("total %d\n",get_total(list));
	travel_dbll(list,show_list_operate,p_null);
}

void show_list_operate(pNODE p_node,void* aide_para)
{
	print_inode(p_node);
	printf("%s ", ((file_info*)(p_node->data))->modestr);
	printf("%*d ",pw.nlink_width, (int)(((file_info*)(p_node->data))->stat_buf.st_nlink));
	print_uid_gid(p_node);
	print_size_dev(p_node);
//	printf("%*ld ",7,((file_info*)(p1->data))->stat_buf.st_size);
	printf("%.12s ", 4 +ctime(&((file_info*)(p_node->data))->stat_buf.st_mtime));
	print_filename(p_node,1);
	print_linkfile(p_node);
	printf("\n");
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
	char* p_null=NULL;
	travel_dbll(list,free_data_operate,p_null);
}

void free_data_operate(pNODE p_node,void* aide_para)
{
	free(((file_info*)(p_node->data))->filename);
	free(((file_info*)(p_node->data))->filepath);
	if(((file_info*)(p_node->data))->linkfile!=NULL)
		free(((file_info*)(p_node->data))->linkfile);

}

void print_spaces(int num)
{
	while(num--)
		printf(" ");

}
