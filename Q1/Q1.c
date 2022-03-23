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
WorkerList* addworker(WorkerList* head, worker* w);
int index(WorkerList* head, long unsigned id);
WorkerList* deleteWorstWorker(WorkerList* head);

void main() {
	int yt = yearType();	
	worker *w1 = CreateWorker(yt);
	worker *w2 = CreateWorker(yt);
	worker* w3 = CreateWorker(yt);
	/*worker* w4 = CreateWorker(yt);*/
	/*PrintWorker(w1, yt);*/
	WorkerList* head = NULL;
	head = addworker(&head, w1);
	head = addworker(head, w2);
	head = addworker(head, w3);
	/*head = addworker(head, w4);
	int checkID = index(head, 5680);*/
	head = deleteWorstWorker(head);
}

//function to choose year type
int yearType() {
	int type = 0;
	printf("for Hebrew year enter '1', for Gregorian year enter '0': ");
	scanf("%d", &type);
	switch (type){
		case (1): //case hebrew year
			return 1;
		case (0): //case gregorian year
			return 0;
		default:
			do //case user enterd other nums than 1 or 0
			{
				printf("Invaild number, please try again: ");
				scanf("%d", &type);
			} while (type != 0 && type != 1);
			break;
	}
}

worker* CreateWorker(int yt) {
	worker* w = (worker*)malloc(sizeof(worker));
	if (!w) { printf("\nallocation failed"); exit(0); }
	printf("\nid: ");
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

WorkerList* addworker(WorkerList* head, worker* w) {
	WorkerList* ptr = head;
	WorkerList* newW = (WorkerList*)malloc(sizeof(WorkerList));
	if (!newW) { printf("allocation failed"); exit(0); } //check and print error message if allocation failed
	newW->data = w;

	if (head->data == NULL) //case list is empty
	{
		head->data = newW->data;
		newW->next = NULL;
		return newW;
	}

	if (w->salary > head->data->salary) //case worker has the highest salsry - worker needs to be first in list
	{
		WorkerList* temp = head;
		head = newW;
		head->next = temp;
		return head;
	}

	while (w->salary < ptr->data->salary) //cases worker is not the first in list
	{
		if (ptr->next == NULL) //case worker has the lowest salsry - worker needs to be last in list
		{
			ptr->next = newW;
			newW->next = NULL;
			return head;
		}
		
		if (w->salary <= ptr->data->salary && w->salary >= ptr->next->data->salary) //case worker has everage salary - worker needs to be in the middle of the list
		{
			WorkerList* temp = ptr;
			newW->next = temp->next;
			ptr->next = newW;
			return head;
		}
		ptr = ptr->next;
	}
}

int index(WorkerList* head, long unsigned id) {
	WorkerList* ptr = head;
	int counter = 0;
	if (ptr->next == NULL && ptr->data->id == id) //case list is one worker and id belongs to first worker
		return 1;
	if (ptr->next == NULL && ptr->data->id != id) //case list is one worker and id isn't belongs to first worker
		return -1;
	while (ptr->next != NULL)//case id is belongs to worker in the middle of list
	{
		counter += 1;
		if (ptr->data->id == id)
		{
			return counter;
		}
		ptr = ptr->next;
	}
	if (ptr->next == NULL && ptr->data->id == id) //case id belongs to last worker
		return counter;
	if (ptr->next == NULL && ptr->data->id != id) //case id isn't belongs to last worker
		return -1;
}

WorkerList* deleteWorstWorker(WorkerList* head) {
	WorkerList* ptr = head;
	if (ptr->next == NULL || ptr == NULL)//case list is only one worker or empty
	{
		printf("\nYou can't delete worst worker when the list is empty or when there is only one worker!");
		return head;
	}
	while (ptr->next != NULL)
	{
		if (ptr->next->next == NULL)//case worst worker
		{
			WorkerList* temp = ptr->next;
			ptr->next = NULL;
			free(temp);
			return head;
		}
		ptr = ptr->next;
	}
	//case of equal salarys
}