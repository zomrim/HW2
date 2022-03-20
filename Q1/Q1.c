#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	unsigned long id;
	char* name;
	unsigned long salary;
	union yearOfStart{
		char hew_year[6];
		unsigned long geo_year;
	};
}worker;

typedef struct WorkerList
{
	worker* data;
	struct WorkerList* next;
} WorkerList;

int yearType();
worker* CreateWorker(int);
void PrintWorker(worker*, int);
WorkerList* addworker(worker* head, worker* w);

void main() {
	int yt = yearType();	
	worker *w1 = CreateWorker(yt);
	PrintWorker(w1, yt);
	free();
}

int yearType() {
	int type = 0;
	printf("for Hebrew year enter '1', for Gregorian year enter '0': ");
	scanf("%d", &type);
	switch (type){
		case (1):
			return 1;
		case (0):
			return 0;
		default:
			do
			{
				printf("Invaild number, please try again: ");
				scanf("%d", &type);
			} while (type != 0 && type != 1);
			break;
	}
}

worker* CreateWorker(int yt) {
	worker* w = (worker*)malloc(sizeof(worker));
	if (!w) { printf("allocation failed"); exit(0); }
	printf("id: ");
	scanf("%ld", &w->id);
	printf("name: ");
	char* temp_name = (char*)malloc(sizeof(char) * 50);
	if (!temp_name) { printf("allocation failed"); exit(0); }
	fseek(stdin, 0, SEEK_END);
	gets(temp_name);
	w->name = (char*)malloc(sizeof(char)* strlen(temp_name));
	if (!w->name) { printf("allocation failed"); exit(0); }
	strcpy(w->name, temp_name);
	printf("salary: ");
	scanf("%ld", &w->salary);
	printf("year of start: ");
	if (yt == 1) {
		printf("year of start: ");
		fseek(stdin, 0, SEEK_END);
		gets(w->hew_year);
	}
	if (yt == 0)
	{
		printf("year of start: ");
		scanf("%ld", &w->geo_year);
	}
	return w;
}

void PrintWorker(worker* w, int yt) {
	printf("\nid: %ld", w->id);
	printf("\nname: %s", w->name);
	printf("\nsalary: %ld", w->salary);
	if (yt == 1) 
		printf("\nyear of start: %s", w->hew_year);
	if (yt == 0)
		printf("\nyear of start: %ld", w->geo_year);
}

WorkerList* addworker(worker* head, worker* w) {
	WorkerList wl1 = { 0 };
}
