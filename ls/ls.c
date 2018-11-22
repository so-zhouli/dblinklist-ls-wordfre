#include"dbll.h"
#include"ls.h"


int main(int argc, char* argv[])
{
	int opt=0;
	int option_index=0;
	int flag_many=0;//一次查找两个目录
	sort_type=sort_name;
	init_value();
	init_width();
	static struct option long_options[]=
	{
		{"help",no_argument,0,'h'},
		{"all",no_argument,0,'a'},
		{0,0,0,0},
	};
	while((opt=getopt_long(argc,argv,"ahAB1oiLlntfs",long_options,&option_index))!=-1)
	{
		switch(opt)
		{
			case 'a':
				reserve_all=true;
				break;
			case 'A':
				delete_dot_and_dotdot=true;
				break;
			case 'B':
				delete_backup=true;
				break;
			case 'l':
				print_list=true;
				break;
			case '1':
				one_per_line=true;
				break;
			case 'o':
				list_no_group=true;
				break;
			case 'i':
				print_with_inode=true;
				break;
			case 'L':
				show_linkfile=true;
				break;
			case 'n':
				numeric_uid_gid=true;
				break;
			case 't':
				sort_type=sort_mtime;
				break;
			case 'f':
				sort_type=sort_none;
				break;
			case 's':
				sort_type=sort_size;
				break;
			case 'h':
				usage();
				break;
			default:
				printf("other options:%c\n",opt);
				return 0;
		}
	}
		
		if(optind==argc)
		{
			DList*filelist=NULL;
			filelist=create_dbll();
			do_ls(".",filelist);
			opt_operate(filelist);
		}
		else
		{	if(argc-optind>1)
				flag_many=1;
			while(optind!=argc)
			{
				init_width();
				if(flag_many)
					printf("%s:\n",argv[optind]);
				DList*filelist=NULL;
				filelist=create_dbll();
				do_ls(argv[optind],filelist);
				if(filelist->len==0)
				{
					destory_dbll(filelist);
					optind++;
					continue;
				}
				opt_operate(filelist);
				optind++;
				if(optind!=argc)
					printf("\n");
			}
		}
	return 0;
}



void opt_operate(DList* list)
{
	if(reserve_all)
	{
		delete_dot_and_dotdot=false;
	}
	else if(delete_dot_and_dotdot)
	{
		delete_dot_file(list);
	}
	else
	{
		delete_hidden_file(list);
	}
	if(delete_backup)
	{
		delete_backup_file(list);
	}
	dbll_compare_cb compare;
	switch(sort_type)
	{
		case sort_none:
			break;
		case sort_size:
			compare=compare_size;
			break;
		case sort_mtime:
			compare=compare_mtime;
			break;
		default:
			compare=compare_name;
			break;
	}
	if(sort_type!=sort_none)
	{
		quick_sort_dbll(list->head->next,list->tail,1,list->len,compare);
	}
	if(sort_type==sort_mtime)
	{
		reverse_dbll(list);
	}
	get_print_width(list);
	if(print_list||list_no_group||numeric_uid_gid)
	{
		show_list(list);
	}
	else
	{
		show_filename(list);
	}
	free_data(list);
	destory_dbll(list);
	
}
