/*
Name: Kavana
Project Name: Arbitrary Precision Calculator
Description: This project implements an Arbitrary Precision Calculator (APC)  that performs arithmetic operations on 
integers of unlimited length. Since built-in data types cannot store very large numbers accurately, the calculator uses a 
doubly linked list to store each digit of a number in a separate node, enabling precise computation regardless of number 
size.
The calculator accepts input through command-line arguments and supports addition, subtraction, multiplication, and 
division. It correctly manages carry, borrow, sign handling, and leading zero removal to ensure accurate results.
*/
#include <stdio.h>
#include "apc.h"
#include <string.h>

int main(int argc,char *argv[])
{
    // Heads and tails for operand 1, operand 2 and result
    APC *head1=NULL, *tail1=NULL;
    APC *head2=NULL, *tail2=NULL;
    APC *rhead=NULL, *rtail=NULL;

    // List to store quotient for division
    APC *counthead=NULL;
    APC *counttail=NULL;

    // Initialize quotient list with 0
    insert_first(&counthead,&counttail,0);
    
    // Validate number of command-line arguments
    if(argc!=4)
    {
        printf("ERROR: Invalid arguments\n");
        printf("Usage: ./a.out [operand 1] [operater] [operand 2]\n");
        return 0;
    }

    int i=0, j=0, data;
    int flag1=0, flag2=0;   // Flags to store sign of operands

    // Check sign of first operand
    if(argv[1][i]=='+' || argv[1][i]=='-')
    {
        flag1=1;
        i++;
    }

    // Store operand1 digits into linked list
    while(argv[1][i]!='\0')
    {
        if(argv[1][i]>='0' && argv[1][i]<='9') //checking if it valid number
        {
            data=argv[1][i]-'0';
            insert_last(&head1,&tail1,data);
        }
        else
        {
           printf("Invalid Operand1\n");
           return 0;
        }
        i++;
    }

    // Remove leading zeros from operand1
    remove_zero(&head1);

    // Check sign of second operand
    if(argv[3][j]=='+' || argv[3][j]=='-')
    {
        flag2=1;
        j++;
    }

    // Store operand2 digits into linked list
    while(argv[3][j]!='\0')
    {
        if(argv[3][j]>='0' && argv[3][j]<='9')//checking if it valid number
        {
            data=argv[3][j]-'0';
            insert_last(&head2,&tail2,data);
        }
        else
        {
           printf("Invalid Operand2\n");
           return 0;
        }
        j++;
    }

    // Remove leading zeros from operand2
    remove_zero(&head2);

    // Checking Operator is a single character
    if(strlen(argv[2])!=1)
    {
        printf("Invalid operator\n");
        return 0;
    }

    printf("Result: ");

    // checking operation based on operator
    switch(argv[2][0])
    {
        case '+':
            // Same sign addition
            if(flag1==flag2)
                add(tail1,tail2,&rhead,&rtail);
            else
            {
                // Different signs subtraction
                if(compare_list(head1,head2)==0)
                {
                    printf("0\n");
                    return 0;
                }
                else if(compare_list(head1,head2)==-1)
                {
                    sub(tail2,tail1,&rhead,&rtail);
                    remove_zero(&rhead);
                    if(flag2==1)
                        printf("-");
                }
                else
                {
                    sub(tail1,tail2,&rhead,&rtail);
                    remove_zero(&rhead);
                    if(flag1==1)
                        printf("-");
                }
            }

            // Both operands negative print result with negative
            if(flag1==1 && flag2==1 && rhead->data!=0)
            printf("-");
            print_list(rhead);
            break;

        case '-':
            // operand1 positive and operand2 negative addition
            if(flag1==0 && flag2==1)
                add(tail1,tail2,&rhead,&rtail);

            // operand1 negative and operand2 positive addition with negative sign
            else if(flag1==1 && flag2==0)
            {
                add(tail1,tail2,&rhead,&rtail);
                printf("-");
            }
            else
            {
                // Same sign subtraction
                if(compare_list(head1,head2)==0)
                {
                    printf("0\n");
                    return 0;
                }
                else if(compare_list(head1,head2)==-1)
                {
                    sub(tail2,tail1,&rhead,&rtail);
                    remove_zero(&rhead);
                    if(flag1==0)
                        printf("-");
                }
                else
                {
                    sub(tail1,tail2,&rhead,&rtail);
                    remove_zero(&rhead);
                    if(flag1==1)
                        printf("-");
                }
            }
            print_list(rhead);
            break;

        case 'x':
        case 'X':
            // Multiplication
            multiplication(tail1,tail2,&rhead,&rtail);
            remove_zero(&rhead);//removing leading zero

            // If signs are different negative result
            if((flag1==1 && flag2==0 && rhead->data!=0) || (flag1==0 && flag2==1 && rhead->data!=0))
            printf("-");
            print_list(rhead);
            break;

        case '/':
            // Division by zero check
            if(head2->data==0)
            {
                printf("Error: Divide by zero is not Possible\n");
                return 0;
            }

            // Perform division using repeated subtraction
            division(&tail1,&head1,tail2,head2,&rhead,&rtail,&counthead,&counttail);

            // If signs are different negative result
            if((flag1==1 && flag2==0 && counthead->data!=0) || (flag1==0 && flag2==1 && counthead->data!=0))
                printf("-");
            print_list(counthead);
            break;

        default:
            printf("\nINVALID OPERATOR\n");
    }
    return 0;
}
