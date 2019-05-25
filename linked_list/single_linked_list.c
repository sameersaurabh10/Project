#include <stdio.h>
#include <stdlib.h>


struct object {
	int value;
};

struct node {
	struct object data;
	struct node *next;
};

void * create_node(void)
{
	struct node * ptr = NULL;
	ptr = malloc(sizeof(struct node));
	if (ptr == NULL) 
		return NULL;
	
	ptr->next = NULL;
	ptr->data.value = 0;
	return ptr;	
}//END of create node

struct node * init_list(struct node **list, int data)
{
	*list = create_node();
	if(*list == NULL) 
		return NULL;

	(*list)->data.value = data;
	return *list;
}//END of init_list function

struct node * add_node(struct node **list, int data)
{
	struct node *temp = NULL;
	if(*list == NULL) {
		if (!init_list(list, data)) {
			printf("add_node : Failed to allocate memory !!!\n");
		} else {
			return *list;
		}
	}

	temp = *list;
	while(temp->next ) {
		temp = temp->next;
	}//END of while LOOP
	
	struct node *new = NULL;
	new = create_node();
	if(new == NULL) {
		printf("add_node : Failed to allocate memory !!!\n");
		return NULL;
	}
	new->data.value = data;
	temp->next = new;
	return *list;
} //END of add_node function

void display(struct node *list)
{
	struct node *temp = NULL;
	temp = list;

	if(!temp) {	
		printf("DISPLAY : List is empty !!!\n");
		return;
	}

	printf("\n========== List data ==========\n");
	while(temp) {
		printf("%d ", temp->data.value);
		if(temp->next)
			printf("-> ");
		temp = temp->next;
	}
	printf("\n===============================\n");
}//END of display function

void destroy(struct node *list)
{
	printf("\nDESTROY : Deleting the list and freeing it...\n");
	free(list);
}//END of destroy function

struct node * merge_list(struct node *list1, struct node *list2) 
{
	if(!list1) {
		printf("Reutning list2 element : %d", list2->data.value);
		return list2;
	}
	if(!list2) {
		printf("Reutning list1 element : %d", list1->data.value);
		return list1;
	}

	if(list1->data.value <= list2->data.value) {
		list1->next = merge_list(list1->next, list2);
		return list1;
	} else {
		list2->next = merge_list(list1, list2->next);
		return list2;
	}
	
}//END of funcion merge_list

int main()
{
	struct node *list1 = NULL, *list2=NULL;
	struct node *list3 = NULL;
	add_node(&list1, 10);
	add_node(&list1, 50);
	add_node(&list1, 70);
	add_node(&list1, 20);
	add_node(&list1, 5);

	add_node(&list2, 300);
	add_node(&list2, 100);
	add_node(&list2, 10);
	add_node(&list2, 30);
	add_node(&list2, 43);

	display(list1);
	display(list2);
	
	list3 = merge_list(list1, list2);
	printf("\n==== Output  of merged list ====");
	display(list3);

	destroy(list1);
	destroy(list2);
	destroy(list3);
}//END of main function
