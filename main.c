#include "abandoned.h"

void create_record();
void read_record();
void update_record();
void delete_record();
void list_record();
void save_record();
void load_record();
void search_record();
void sort_record();
void stat_record();

void search_by_breed();
void search_by_sex();
void search_by_color();
void search_by_dis();
void search_by_st();

int main(){
	int menu;
	FILE* f = fopen("dogs.txt","a+");
	int size;
	A_Record* records[ALL_DOGS];
	while(1){
		printf("\nMenu : \t1.Create 2.Read 3.Update 4.Delete 5.List 6.Save to file 7.Load from file 8.Search 9.Sort list 10.Stats 0.Quit > ");
		scanf("%d", &menu);
		printf("\n");
		switch(menu){
			case 1:
				create_record();
				break;
			case 2:
				read_record();
				break;
			case 3:
				update_record();
				break;
			case 4:
				delete_record();
				break;
			case 5:
				list_record();
				break;
			case 6:
				save_record();
				break;
			case 7:
				load_record();
				break;
			case 8:
				search_record();
				break;
			case 9:
				sort_record();
				break;
			case 10:
				stat_record();
				break;
			case 0:
				size = a_allcount();
				a_get_all(records);
				for(int i=0;i<size;i++){
				fprintf(f,"%s %d %d %d %s %s %s %f %s\n", records[i]->st, records[i]->num[0], records[i]->num[1], records[i]->num[2], records[i]->breed, records[i]->sex, records[i]->color, records[i]->weight, records[i]->dis);
				}		
				fclose(f);
			default:
				return 0;
		}
	}
	return 0;
}

void create_record(){
	FILE* fp = fopen("dogs.txt", "r");
	int size;
	fseek(fp,0,SEEK_END);
	size = ftell(fp);
	if(size > 1){
		fseek(fp,0,SEEK_SET);
		int num[3];
		char breed[30], sex[10], color[20], dis[30], st[20];
		float weight;
		while(!feof(fp)){
			int n = fscanf(fp,"%s %d %d %d %s %s %s %f %s\n",st, &num[0], &num[1], &num[2], breed, sex, color, &weight, dis);
			if(n<1) break;
			a_allcreate(num[0],num[1],num[2],breed,sex,color,weight,dis,st);
		}
		FILE* f = fopen("dogs.txt","w");
		fprintf(f," ");
		fclose(f);
	}
	fclose(fp);

	if(a_is_available() == 0){
		printf("There is no space!\n");
		return;
	}
	char breed[20], sex[20], color[20], dis[30], st[20];
	float weight;
	printf("Enter a new dog's info.\n");
	printf("Dog breed > ");
	scanf("%s", breed);
	printf("Sex > ");
	scanf("%s", sex);
	printf("Fur color > ");
	scanf("%s", color);
	printf("Weight > ");
	scanf("%f", &weight);
	getchar();
	printf("Discovery > ");
	fgets(dis,30,stdin);
	dis[strlen(dis)-1] = '\0';
	strcpy(st,"first");
	a_create(-1,-1,-1,breed, sex, color, weight, dis, st);
}

void list_record(){
	printf("All records. \n");
	int size = a_count();
	A_Record* records[MAX_DOGS];
	a_get_shelter(records);
	for(int i=0;i<size;i++){
		A_Record* p = records[i];
		printf("%d. %s\n", i+1, a_to_string(p));
	}
}

void read_record(){
	int num;
	printf("Enter a classification number > ");
	scanf("%d", &num);
	if(a_search_by_num(num) == 0){
		printf("No such number!\n");
		return;
	}
	A_Record* p = a_search_by_num(num);
	printf("\nDog's info\n");
	printf("Classification number : %s호\n", getnum(p));
	printf("Dog breed : %s\n", p->breed);
	printf("Sex : %s\n", p->sex);
	printf("Fur color : %s\n", p->color);
	printf("Weight : %.1fkg\n", p->weight);
	printf("Discovered in %s\n", p->dis);
	printf("[%s]\n", p->st);
}

void update_record(){
	int num;
	printf("Enter a classification number > ");
	scanf("%d",&num);
	if(a_search_by_num(num) == 0){
		printf("No such number!\n");
		return;
	}
	A_Record* p = a_search_by_num(num);
	a_update(p);
}

void delete_record(){
	int num;
	printf("Enter a classification number > ");
	scanf("%d", &num);
	if(a_search_by_num(num)==0){
		printf("No such number!\n");
		return;
	}
	A_Record* p = a_search_by_num(num);
	int hap;
	printf("\nWhat happend to the dog? : 1.Adoption 2.Temporary Protection 3.Return 4.Death > ");
	scanf("%d", &hap);
	printf("\n");
	before_d(p,hap);
	a_delete(p);
	printf("The record is deleted!\n");
}

void save_record(){
	FILE* f = fopen("shelter.txt","w");
	int i, size = a_count();
	A_Record* records[MAX_DOGS];
	a_get_shelter(records);
	for(i=0;i<size;i++){
		fprintf(f,"%s %d %d %d %s %s %s %f %s\n", records[i]->st, records[i]->num[0], records[i]->num[1], records[i]->num[2], records[i]->breed, records[i]->sex, records[i]->color, records[i]->weight, records[i]->dis);
	}
	fclose(f);
}

void load_record(){
	FILE* f = fopen("shelter.txt","r");
	int num[3];
	char breed[30], sex[10], color[20], dis[30], st[20];
	float weight;
	while(!feof(f)){
		if(a_is_available()==0){
			printf("[Load] There is no space!\n");
			break;
		}
		int n = fscanf(f,"%s %d %d %d %s %s %s %f %s\n", st, &num[0], &num[1], &num[2], breed, sex, color, &weight, dis);
		if(n<1) break;
		a_create(num[0], num[1], num[2], breed, sex, color, weight, dis, st);
	}
}

void search_record(){
	int schby;
	while(1){
		printf("\nSearch by : 1.Breed 2.Sex 3.Color 4.Discovery 5.Status 0.Quit > ");
		scanf("%d", &schby);
		printf("\n");
		switch(schby){
			case 1:
				search_by_breed();
				break;
			case 2:
				search_by_sex();
				break;
			case 3:
				search_by_color();
				break;
			case 4:
				search_by_dis();
				break;
			case 5:
				search_by_st();
				break;
			case 0:
			default:
				return ;
		}
	}
}
void search_by_breed(){
	char breed[20];
	printf("What breed do you want to search? ");
	scanf("%s", breed);
	A_Record* records[MAX_DOGS];
	int size = a_search_by_breed(records,breed);
	for(int i=0;i<size;i++){
		A_Record* p = records[i];
		printf("%d. %s\n", i+1,a_to_string(p));
	}
}
void search_by_sex(){
	char sex[20];
	printf("What sex do you want to search? ");
	scanf("%s", sex);
	A_Record* records[MAX_DOGS];
	int size = a_search_by_sex(records,sex);
	for(int i=0;i<size;i++){
		A_Record* p = records[i];
		printf("%d. %s\n", i+1,a_to_string(p));
	}
}
void search_by_color(){
	char color[20];
	printf("What color do you want to search? ");
	scanf("%s", color);
	A_Record* records[MAX_DOGS];
	int size = a_search_by_color(records,color);
	for(int i=0;i<size;i++){
		A_Record* p = records[i];
		printf("%d. %s\n", i+1,a_to_string(p));
	}
}
void search_by_dis(){
	char dis[20];
	printf("What discovery do you want to search? ");
	scanf("%s", dis);
	A_Record* records[MAX_DOGS];
	int size = a_search_by_dis(records,dis);
	for(int i=0;i<size;i++){
		A_Record* p = records[i];
		printf("%d. %s\n", i+1,a_to_string(p));
	}
}
void search_by_st(){
	char st[20];
	printf("What status do you want to search? ");
	scanf("%s", st);
	A_Record* records[MAX_DOGS];
	int size = a_search_by_st(records,st);
	for(int i=0;i<size;i++){
		A_Record* p = records[i];
		printf("%d. %s\n", i+1,a_to_string(p));
	}
}

void sort_record(){
	printf("Sorting records...\n");
	a_sort();
	printf("Completed sorting\n");
	A_Record* records[MAX_DOGS];
	a_get_shelter(records);
	int size = a_count();
	for(int i=0;i<size;i++){
		A_Record* p = records[i];
		printf("%d. %s\n", i+1, a_to_string(p));
	}
}

void stat_record(){
	int i, size;
	struct class* p[ALL_DOGS];
	FILE* f = fopen("stat.txt","rw");
	fprintf(f,"[전체 유기견 통계]\n\n");
	fprintf(f,"0. 총\t%d마리\n",for_stat(0));
	fprintf(f,"1. 보호시설\t%d마리\n",for_stat(1));
	fprintf(f,"2. 입양\t%d마리\n",for_stat(4));
	fprintf(f,"3. 입시보호\t%d마리\n",for_stat(5));
	fprintf(f,"4. 반환\t%d마리\n",for_stat(6));
	fprintf(f,"5. 사망\t%d마리\n\n",for_stat(7));
	fprintf(f,"[현재 보호시설 통계]\n\n");
	fprintf(f,"공고중\t%d마리",for_stat(2));
	fprintf(f,"공고만\t%d료마리",for_stat(3));
	fprintf(f,"암:\t%d마리, 수:\t%d마리",for_stat(8),for_stat(9));
	fprintf(f,"견종\n");
	size = mk_class_b(p);
	for(i=0;i<size;i++){
		fprintf(f,"\t%s  %d마리\n",p[i]->kind,p[i]->num);
	}
	fprintf(f,"발견지\n");
	size = mk_class_d(p);
	for(i=0;i<size;i++){
		fprintf(f,"\t%s  %d마리\n",p[i]->kind,p[i]->num);
	}
	fclose(f);
}
