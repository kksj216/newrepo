#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DOGS 100
#define ALL_DOGS 2000

typedef struct st_abandoneddog{
	int num[3];
	char breed[30];
	char sex[10];
	char color[20];
	float weight;
	char dis[30];
	char st[10];
} A_Record;

struct class{
	char kind[30];
	int num;
};

int a_is_available();
int a_first_available();
int a_count();
int a_allcount();
void a_create(int n1, int n2, int n3, char* b, char* se, char* c, float w, char* d, char* st);
void a_allcreate(int n1, int n2, int n3, char* b, char* se, char* c, float w, char* d, char* st);
A_Record* a_search_by_num(int n);
void a_update(A_Record* p);
void a_delete(A_Record* p);
void a_get_shelter(A_Record* a[]);
void a_get_all(A_Record* a[]);
char* a_to_string(A_Record* p);
char* a_getbreed(A_Record* p);
char* a_getsex(A_Record* p);
char* a_getcolor(A_Record* p);
float a_getweight(A_Record* p);
char* a_getdiscovery(A_Record* p);
char* a_getstatus(A_Record* p);
int a_search_by_breed(A_Record* a[], char* b);
int a_search_by_sex(A_Record* a[], char* se);
int a_search_by_color(A_Record* a[], char* c);
int a_search_by_dis(A_Record* a[], char* d);
int a_search_by_st(A_Record* a[], char* st);
void a_sort(A_Record* p);
char* getnum(A_Record* p);
void before_d(A_Record* p, int h);
int mk_class_b(struct class* breeds[]);
int mk_class_d(struct class* diss[]);
int for_stat(int cn);
