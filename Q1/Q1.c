#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	unsigned long id;
	char* name;
	unsigned long salary;
	int yt; //to save the type of year of start
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
worker* CreateWorker();
void PrintWorker(worker*);
WorkerList* addworker(WorkerList* head, worker* w);
int index(WorkerList* head, long unsigned id);
int indexRec(WorkerList* head, long unsigned id);
WorkerList* deleteWorstWorker(WorkerList* head);
void update_worker(WorkerList* head, float percent);
WorkerList* reverse(WorkerList* head);
void freeWorkers(WorkerList* head);
void printWorkersList(WorkerList* head);

void main() {
	worker *w1 = CreateWorker();
	worker *w2 = CreateWorker();
	worker* w3 = CreateWorker();
	worker* w4 = CreateWorker();
	WorkerList* head = NULL;
	head = addworker(&head, w1);
	head = addworker(head, w2);
	head = addworker(head, w3);
	head = addworker(head, w4);
	printWorkersList(head);
	unsigned long id_to_check = 0;
	printf("\nEnter ID to check position in list: ");
	scanf("%lu", &id_to_check);
	int index_res1 = index(head, id_to_check);
	printf("\nposition of %lu is: %d", id_to_check, index_res1);
	printf("\nEnter another ID to check position in list: ");
	scanf("%lu", &id_to_check);
	int index_res2 = indexRec(head, id_to_check);
	printf("\nposition of %lu is: %d", id_to_check, index_res2);
	head = deleteWorstWorker(head);
	printWorkersList(head);
	float sal_raise = 0;
	printf("\nEnter in decimal number the precentage to update all workers salarys: ");
	scanf("%f", &sal_raise); //we assumed that user entered num bigger than 1
	update_worker(head, sal_raise);
	printWorkersList(head);
	head = reverse(head);
	printWorkersList(head);
	freeWorkers(head);
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

worker* CreateWorker() {
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
	w->yt = yearType();
	if (w->yt == 1) //case year type is hebrew year
	{
		printf("year of start: ");
		fseek(stdin, 0, SEEK_END);
		gets(w->hew_year);
	}
	if (w->yt == 0) //case year type is gregorian year
	{
		printf("year of start: ");
		scanf("%ld", &w->geo_year);
	}
	return w;
}

void PrintWorker(worker* w) {
	printf("\nid: %ld", w->id);
	printf("\nname: %s", w->name);
	printf("\nsalary: %ld", w->salary);
	if (w->yt == 1)
		printf("\nyear of start: %s\n", w->hew_year);
	if (w->yt == 0)
		printf("\nyear of start: %ld\n", w->geo_year);
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
	int counter = 1;
	while (ptr->next != NULL)//check the id of all workers without the last one
	{
		if (ptr->data->id == id)
		{
			return counter;
		}
		ptr = ptr->next;
		counter += 1;
	}
	if (ptr->next == NULL && ptr->data->id == id) //case id belongs to last worker
		return counter;
	if (ptr->next == NULL && ptr->data->id != id) //case id isn't belongs to last worker
		return -1;
}

int indexRec(WorkerList* head, long unsigned id) {
	int static i = 1;
	if (head->next == NULL && head->data->id != id) //case id isn't belongs to last worker
		return -1;
	if (head->data->id == id) //case id belongs to worker that in list 
		return i;
	if (head->data->id != id) //check if id of temp head is the id user entered 
	{
		i += 1;
		indexRec(head->next, id);
	}
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
		if (ptr->next->next == NULL)//case worst worker (in case there is two or more workers with the same salary, delete only the last in the list)
		{
			WorkerList* temp = ptr->next;
			ptr->next = NULL;
			free(temp);
			return head;
		}
		ptr = ptr->next;
	}
}

void update_worker(WorkerList* head, float percent) {
	WorkerList* ptr = head;
	while (ptr != NULL) 
	{
		ptr->data->salary *= percent;
		ptr = ptr->next;
	}
}

WorkerList* reverse(WorkerList* head) {
	WorkerList* prev, *current;
	if (head != NULL) //start reverse only if the list isn't empty
	{
		prev = head;
		current = head->next;
		head = head->next;
		prev->next = NULL; // make first worker as last worker in list
		while (head != NULL)
		{
			head = head->next;
			current->next = prev;
			prev = current;
			current = head;
		}
		head = prev; // make last worker as head of the list
	}
	return head;
}

void freeWorkers(WorkerList* head) {
	WorkerList* ptr = head;
	if (head == NULL)
		return;
	if (head->next == NULL)//case when only one worker remains in list
	{
		free(head);
		head == NULL;
		return;
	}
	while (ptr->next != NULL)
	{
		if (ptr->next->next == NULL)
		{
			WorkerList* temp = ptr->next;
			ptr->next = NULL;
			free(temp);
			break;
		}
		ptr = ptr->next;
	}
	freeWorkers(head);
}

void printWorkersList(WorkerList* head) {
	printf("\nWORKERS LIST:\n"); 
	if (head == NULL) //case list is empty
	{
		printf("List is empty!\n");
		return;
	}
	while (head != NULL)
	{
		PrintWorker(head->data); //use PrintWorker func to print the list
		head = head->next;
	}
	return;
}