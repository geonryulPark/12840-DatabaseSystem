#ifndef __BPT_H__
#define __BPT_H__

// Uncomment the line below if you are compiling on Windows.
// #define WINDOWS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <inttypes.h>
#include <string.h>
#define LEAF_MAX 4
#define INTERNAL_MAX 248
#define BUFFER_MAX 8

typedef struct record{
    int64_t key;
    char value[120];
}record;

typedef struct inter_record {
    int64_t key;
    off_t p_offset;
}I_R;

typedef struct Page{
    off_t parent_page_offset;
    int is_leaf;
    int num_of_keys;
    char reserved[104];
    off_t next_offset;
    union{
        I_R b_f[248];
        record records[30];
    };
}page;

typedef struct Header_Page{
    off_t fpo;
    off_t rpo;
    int64_t num_of_pages;
    char reserved[4072];
}H_P;

struct AVLNode;
typedef struct AVLNode *Position;
typedef struct AVLNode *AVLTree;
typedef record ElementType;

typedef struct AVLNode
{
    ElementType element;
    AVLTree left, right;
    int height;
}AVLNode;


extern int fd;

extern page * rt;

extern H_P * hp;
// FUNCTION PROTOTYPES.
int open_table(char * pathname);
H_P * load_header(off_t off);
page * load_page(off_t off);

void reset(off_t off);
off_t new_page();
off_t find_leaf(int64_t key);
char * db_find(int64_t key);
void freetouse(off_t fpo);
int cut(int length);
int parser();

void start_new_file(record rec);
int db_insert(int64_t key, char * value);
off_t insert_into_leaf(off_t leaf, record inst);
off_t insert_into_leaf_as(off_t leaf, record inst);
off_t insert_into_parent(off_t old, int64_t key, off_t newp);
int get_left_index(off_t left);
off_t insert_into_new_root(off_t old, int64_t key, off_t newp);
off_t insert_into_internal(off_t bumo, int left_index, int64_t key, off_t newp);
off_t insert_into_internal_as(off_t bumo, int left_index, int64_t key, off_t newp);

int db_delete(int64_t key);
void delete_entry(int64_t key, off_t deloff);
void redistribute_pages(off_t need_more, int nbor_index, off_t nbor_off, off_t par_off, int64_t k_prime, int k_prime_index);
void coalesce_pages(off_t will_be_coal, int nbor_index, off_t nbor_off, off_t par_off, int64_t k_prime);
void adjust_root(off_t deloff);
void remove_entry_from_page(int64_t key, off_t deloff);
void usetofree(off_t wbf);

// 추가한 함수
int compare(const void *one, const void *two); // qsort 함수 사용
char* isInBuffer(const record *, int bufferSize, int64_t key);
int bf_insert(int64_t key, char *value);
int bf_delete(int64_t key);
char* bf_find(int64_t key);

// AVL tree
int max(int a, int b);
int Height(Position node);
AVLTree FindMin(AVLTree T);
AVLTree Insert(int64_t key, char *value, AVLTree T);
AVLTree Delete(int64_t key, AVLTree T);
Position SingleRotateWithLeft(Position node);
Position SingleRotateWithRight(Position node);
Position DoubleRotateWithLeft(Position node);
Position DoubleRotateWithRight(Position node);
char * Find(int64_t key, AVLTree T);
void PopAllNode(AVLTree T);
void PrintInorder(AVLTree T);
void DeleteTree(AVLTree T);

#endif /* __BPT_H__*/


