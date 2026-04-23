#include <stdio.h>
#include "apc.h"
#include<stdlib.h>

// Function to add two  numbers
void add(APC *tail1, APC *tail2, APC **rhead, APC **rtail)
{
    APC *temp1 = tail1;  // Pointer to  first number 
    APC *temp2 = tail2;  // Pointer to second number 
    int res = 0;          // Store the result of addition of single digits
    int carry = 0;        // Store carry from previous addition

    // Traverse both numbers list
    while(temp1 != NULL || temp2 != NULL)
    {
        if(temp1 != NULL && temp2 != NULL)
        {
            res = temp1->data + temp2->data + carry;  // Add digits and carry
            temp1 = temp1->prev;  // Move to previous node
            temp2 = temp2->prev;
        }
        else if(temp1 != NULL)  // Only first number  list has digits 
        {
            res = temp1->data + carry;
            temp1 = temp1->prev;
        }
        else if(temp2 != NULL)  // Only second number list has digits 
        {
            res = temp2->data + carry;
            temp2 = temp2->prev;
        }

        //  carry for result greater than 9
        if(res > 9)
        {
            res = res % 10;  // Keep only single digit
            carry = 1;       // Carry to next addition
        }
        else
            carry = 0;

        insert_first(rhead, rtail, res);  // Insert res 
    }

    // If carry is left after finishing both lists, add it
    if(carry == 1)
        insert_first(rhead, rtail, carry);
}

// Function to compare two numbers
int compare_list(APC *head1, APC *head2)
{
    int len1 = 0, len2 = 0;
    APC *temp1 = head1;
    APC *temp2 = head2;

    // Calculating length of first number
    while(temp1 != NULL)
    {
        len1++;
        temp1 = temp1->next;
    }

    // Calculating length of second number
    while(temp2 != NULL)
    {
        len2++;
        temp2 = temp2->next;
    }

    // Compare based on length
    if(len1 < len2) //if first number less than second number
        return -1;
    else if(len1 == len2)  // If lengths are equal compare digit by digit
    {
        while(head1 != NULL && head2 != NULL)
        {
            if(head1->data < head2->data)
                return -1;// second number is greater
            else if(head1->data > head2->data)
                return 1;// First number is greater

            head1 = head1->next;
            head2 = head2->next;
        }
        return 0;  // Numbers are equal
    }
    else
        return 1;  // First number is greater
}

// Function to subtract two numbers 
void sub(APC *tail1, APC *tail2, APC **rhead, APC **rtail)
{
    APC *temp1 = tail1;  // Pointer to tail1
    APC *temp2 = tail2;  // Pointer to tail2
    int res = 0;         // Store difference of digits
    int flag = 0;        // Borrow flag
    int d1, d2;          // Temporary storage of digits

    // Traverse both numbers list
    while(temp1 != NULL || temp2 != NULL)
    {
        d1 = 0; d2 = 0; 

        if(temp1 != NULL)
            d1 = temp1->data;//storing temp1 data to d1
        if(temp2 != NULL)
            d2 = temp2->data;//storing temp1 data to d1

        if(flag == 1)  // Apply borrow if previous subtraction required it
            d1 = d1 - 1;

        if(temp1 != NULL && temp2 != NULL)
        {
            if(d1 < d2)  // first number digit less than second number digit
            {
                res = d1 + 10 - d2;
                flag = 1;  // Set borrow flag
            }
            else
            {
                res = d1 - d2;
                flag = 0;  
            }
            temp1 = temp1->prev;
            temp2 = temp2->prev;
        }
        else if(temp1 != NULL && temp2 == NULL)  // Only first list has digits left
        {
            res = d1;
            if(res < 0)  // Borrow needed
            {
                res = 9;
                flag = 1;
            }
            else
                flag = 0;

            temp1 = temp1->prev;
        }

        insert_first(rhead, rtail, res);  // Insert result digit at first
    }
}

// Function to multiply two numbers
void multiplication(APC *tail1, APC *tail2, APC **rhead, APC **rtail)
{
    APC *temp2 = tail2;  // Pointer to traverse multiplier
    APC *res1head = NULL, *res1tail = NULL;  
    APC *res2head = NULL, *res2tail = NULL; 
    int count = 0;  //  multiplier digit position
    int res = 0;    // Store single digit multiplication
    int carry;      // Store carry for multiplication

    // Traverse each digit of multiplier
    while(temp2 != NULL)
    {
        APC *temp1 = tail1;  // Pointer to temp1
        carry = 0;

        
        if(count != 0) // Add zeros for shifting 
        {
            for(int i = 0; i < count; i++)
                insert_first(&res2head, &res2tail, 0);
        }

        // Multiply current digit of multiplier with all digits of multiplicand
        while(temp1 != NULL)
        {
            res = (temp2->data * temp1->data) + carry;  // Multiply digits + carry
            if(res > 9)  // Handle carry
            {
                carry = res / 10;
                res = res % 10;
            }
            else
                carry = 0;

            if(count == 0)
                insert_first(&res1head, &res1tail, res);  // inserting First partial product
            else
                insert_first(&res2head, &res2tail, res);  // inserting partial product

            temp1 = temp1->prev;
        }

        // Insert remaining carry if any
        if(carry != 0)
        {
            if(count == 0)
                insert_first(&res1head, &res1tail, carry);
            else
                insert_first(&res2head, &res2tail, carry);
        }

        count++;  // Move to next multiplier digit

        // Add partial results after second digit multiplication
        if(count >= 2)
        {
            add(res1tail, res2tail, rhead, rtail);  // Sum partial products
            delete_list(&res1head, &res1tail);     // Clear first partial
            delete_list(&res2head, &res2tail);    // Clear second partial
            res1head = *rhead;           // Store addition as new first partial
            res1tail = *rtail;
            *rhead = NULL;              // Reset main result
            *rtail = NULL;
        }

        temp2 = temp2->prev;  // Move to next multiplier digit
    }

    *rhead = res1head;  //storing final multiplication result
    *rtail = res1tail;
}

// Function to divide two numbers 
void division(APC **tail1, APC **head1, APC *tail2, APC *head2, APC **rhead, APC **rtail, APC **counthead, APC **counttail)
{
    // Keep subtracting divisor from dividend until dividend < divisor
    while(compare_list(*head1, head2) == 1 || compare_list(*head1, head2) == 0)
    {
        add_one(counthead, counttail);   // Increment quotient by 1
        sub(*tail1, tail2, rhead, rtail); // Subtract divisor from dividend
        delete_list(head1, tail1);       // Clear old dividend
        *tail1 = *rtail;                 // Update dividend to remainder
        *head1 = *rhead;
        *rhead = NULL;                    
        *rtail = NULL;
        remove_zero(head1);               // Remove leading zeros in new dividend
    }
}

// Function to increment quocient by 1
void add_one(APC **counthead, APC **counttail)
{
    APC *temp = *counttail;  
    int carry = 1;            // Initial increment is 1

    // Traverse digits and add carry
    while(temp != NULL && carry == 1)
    {
        temp->data = temp->data + carry;
        if(temp->data > 9)  // Handle carry
        {
            temp->data = 0;
            carry = 1;
        }
        else
            carry = 0;

        temp = temp->prev;
    }

    if(carry == 1)  // If carry left 
        insert_first(counthead, counttail, carry);
}

// Function to remove leading zeros from a number
void remove_zero(APC **head)
{
    while(*head && (*head)->data == 0 && (*head)->next != NULL)
    {
        APC *temp = *head;
        *head = temp->next;    // Move head
        (*head)->prev = NULL; 
        free(temp);            // Free memory of removed node
    }
}
