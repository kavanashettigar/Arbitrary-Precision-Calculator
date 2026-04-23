#include<stdio.h>
#include "apc.h"
#include <stdlib.h>

int insert_last(APC **head, APC **tail, int data)
{
    APC *new=malloc(sizeof(APC));//create new node
    if(new==NULL) //checking new node created or not
    return FAILURE;
    //updating new node data and links
    new->data=data;
    new->prev=NULL;
    new->next=NULL;
    
    if(*head==NULL)//checking list is empty
    {
        //updating head and tail
        *head=new;
        *tail=new;
    }
    
    else
    {
        //list is not empty
        new->prev=*tail; // updating new node previous link
        (*tail)->next=new;// updating last node next link
        *tail=new; //updating tail with new node address
    }
    return SUCCESS;

}

int insert_first(APC **head, APC **tail, int data)
{
    APC *new=malloc(sizeof(APC));//create new node
    if(new==NULL) //checking new node created or not
    return FAILURE;
    //updating new node data and links
    new->data=data;
    new->prev=NULL;
    new->next=NULL;
    
    
    if(*head==NULL)//checking list is empty
    {
        //updating head and tail
        *head=new;
        *tail=new;
    }
    else
    {
        //list is not empty
        new->next=*head; //updating new node next link
        (*head)->prev=new; //first node previous link
        *head=new; //updating head
    }
    return SUCCESS;

}
int delete_list(APC **head, APC **tail)
{
    if (*head == NULL)
    {
        return FAILURE;   // list is empty
    }

    APC *temp = *head;  

    while (temp != NULL)
    {
        *head = temp->next; // move head to next node
        free(temp);         // free current node
        temp = *head;      // update temp
    }

    *tail = NULL;          // list is now empty

    return SUCCESS;
}

void print_list(APC *head)
{
	/* Cheking the list is empty or not */
	if (head == NULL)
	{
		printf("INFO : List is empty\n");
	}
	else
	{
	    while (head)		
	    {
		    /* Printing the list */
		    printf("%d", head -> data);

		    /* Travering in forward direction */
		    head = head -> next;
		    
	    }
        printf("\n");
    	
    }
}
