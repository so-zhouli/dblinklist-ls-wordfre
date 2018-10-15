#include<sys/types.h>
#include<dirent.h>
#include<stdbool.h>
#include<sys/stat.h>
#include<grp.h>
#include<pwd.h>
#include<unistd.h>
#include<getopt.h>
#include<sys/ioctl.h>
#include<termios.h>
#include<time.h>
#define NONE "\033[0m"
#define BLUE "\033[1;34m"
#define GREEN "\033[1;32m"
#define L_CYAN "\033[1;36m"
#define L_MAGENTA "\033[1;35m"
#define L_YELLOW "\033[1;33m"
#define BLACK_GREEN "\033[0;30;42m"
#define WHITE_RED "\033[1;37;41m"

//#define DEBUG
#define DEV_WIDTH (pw.major_dev_width+pw.minor_dev_width)
#define PRINT_WIDTH  (print_list||list_no_group||numeric_uid_gid)?(0):(fmt_width+2-strlen(((file_info*)(p_node->data))->filename))

/* three sort types can be selected ,filename,filesize,modified time*/
enum sort_type
{
	sort_none,
	sort_name,
	sort_size,
	sort_mtime,
};
enum sort_type sort_type;

bool delete_dot_and_dotdot;//delete . and ..

bool delete_backup;//delete filename with ~

bool reserve_all;//all files

bool one_per_line;//print one per line

/* list without gopupname or group id*/
bool list_no_group;

/* list inode number before filename*/
bool print_with_inode;

bool show_linkfile;//SHOW LINKFILE RATHER NOT LINK

/*show user id or group id rather than their name */
bool numeric_uid_gid;

bool print_list;//list detail information 

/* print width will be used for print format*/
struct print_width
{
	int filename_width;
	int inode_width;
	int nlink_width;
	int uid_width;
	int gid_width;
	int major_dev_width;
	int minor_dev_width;
	int size_width;
};
struct print_width pw;

typedef struct col_row_caculate
{
	int col;
	int row;
	int cols;
	int rows;
	int *col_width;
}col_row_info;



typedef struct file_info
{
	char* filename;
	char* linkfile; //path of linkfile
	struct stat stat_buf;
	int row_label;
	int col_label;
	int filename_length;
	char modestr[11];
	char* filepath;//dirpath /filename
}file_info;

/* read diretory and get all filename,but if given path is a filename,then stat it directly*/
void do_ls(char* dirname,DList* list);

/* dostat and get_file_info */
void dostat(char* filename,char* dirpath,file_info* file_info_new);
void get_file_info(char* filepath,file_info* file_info_new);
void mode_to_letters(int mode,char* str);
char* uid_to_name(uid_t uid);
char* gid_to_name(gid_t gid);
void opt_operate(DList* list);
void delete_dot_file(DList* list);
void delete_backup_file(DList* list);
void delete_hidden_file(DList* list);

int compare_size(void* elem1,void* elem2);
int compare_name(void* elem1,void* elem2);
int compare_mtime(void* elem1,void* elem2);
int compare_dot(void* elem1,void* elem2);
int compare_first_char(void* elem1,void* elem2);
int compare_last_char(void* elem1,void* elem2);

void show_test(DList* list);
void init_value();
void init_width();
void show_list(DList* list);
void show_filename(DList* list);
void print_spaces();
void free_data(DList* list);


void get_print_width(DList* list);

void get_filename_width(DList* list);
void filename_operate(pNODE p_node,void* aide_para);

void get_inode_width(DList*list);
void inode_operate(pNODE p_node,void* aide_para);

void get_nlink_width(DList* list);
void nlink_operate(pNODE p_node,void* aide_para);

void get_size_width(DList*list);
void size_operate(pNODE p_node,void*aide_para);

void get_uid_width(DList*list);
void uid_operate(pNODE p_node,void*aide_para);

void get_gid_width(DList*list);
void gid_operate(pNODE p_node,void* aide_para);

void get_major_dev_width(DList* list);
void major_dev_operate(pNODE p_node,void*aide_para);

void get_minor_dev_width(DList* list);
void minor_dev_operate(pNODE p_node,void*aide_para);

void label_col_row_operate(pNODE p_node,void* aide_para);
void caculate_col_width_operate(pNODE p_node,void* aide_para);
void get_total_operate(pNODE p_node,void* aide_para);
void show_filename_operate(pNODE p_node,void* aide_para);
void show_list_operate(pNODE p_node,void* aide_para);
void free_data_operate(pNODE p_node,void * aide_para);
