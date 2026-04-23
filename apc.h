#ifndef APC_H
#define APC_H

#include <stdio.h>

// Macros for function return status
#define SUCCESS 0  
#define FAILURE -1 

// Structure definition for an arbitrary-precision number node
typedef struct node
{
    int data;            
    struct node *prev;  
    struct node *next;   
} APC;

// Function declarations for linked list operations

// Inserts a digit at the end 
int insert_last(APC **head, APC **tail, int data);

// Inserts a digit at the beginning 
int insert_first(APC **head, APC **tail, int data);

// Deletes the entire list and frees memory
int delete_list(APC **head, APC **tail);

// Prints the linked list
void print_list(APC *head);

// Arithmetic operation functions

// Adds two numbers 
void add(APC *tail1, APC *tail2, APC **rhead, APC **rtail);

// Compares two numbers
int compare_list(APC *head1, APC *head2);

// Subtracts two numbers
void sub(APC *tail1, APC *tail2, APC **rhead, APC **rtail);

// Multiplies two numbers
void multiplication(APC *tail1, APC *tail2, APC **rhead, APC **rtail);

// Division of two numbers
void division(APC **tail1, APC **head1, APC *tail2, APC *head2, APC **rhead, APC **rtail, APC **counthead, APC **counttail);

// Adds one to number (used in division)
void add_one(APC **counthead, APC **counttail);

// Removes leading zeros from number
void remove_zero(APC **head);

#endif
