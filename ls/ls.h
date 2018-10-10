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
#define PRINT_WIDTH  (print_list||list_no_group||numeric_uid_gid)?(0):(pw.filename_width+1-strlen(((file_info*)(p1->data))->filename))


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

bool list_no_group;

bool print_with_inode;

bool show_linkfile;//SHOW LINKFILE RATHER NOT LINK

bool numeric_uid_gid;

bool print_list;//list detail information 

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

void do_ls(char* dirname,DList* list);
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
void show_test(DList* list);
void init_value();
void init_width();
void show_list(DList* list);
void show_filename(DList* list);
void print_spaces();
void free_data(DList* list);
int get_filename_width(DList* list);
int get_inode_width(DList*list);
int get_nlink_width(DList* list);
int get_size_width(DList*list);
void get_print_width(DList* list);
int get_major_dev_width(DList* list);
int get_minor_dev_width(DList* list);
void print_size_dev(pNODE p1,DList* list);
