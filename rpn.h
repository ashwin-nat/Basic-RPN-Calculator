/*
By Ashwin Natarajan. No GUI yet. Only supports +,-,/,* for now.

*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define BUFFER_SIZE 20
#define EXIT "exit"
#define CLEAR "clear"

//the basic struct for the stack
struct stack
{
    float val;
    struct stack *next;
};

//case insensitive string compare. from https://stackoverflow.com/questions/5820810/case-insensitive-string-comp-in-c
int stricmp(char const *a, char const *b)
{
    for (;; a++, b++) {
        int d = tolower(*a) - tolower(*b);
        if (d != 0 || !*a)
            return d;
    }
}

//check if input buffer contents is a number
int isnumber(char buf[BUFFER_SIZE])
{
    char *end = NULL;
    strtof(buf,&end); //convert to float
    int len = strlen(end);  //compute length of the remainder of the string
    
    if(len!=0)  //if there is no remainder, then the buffer contains a number
        return 0;
    else    //else not a number
    {
        return 1;
    }
}

//function to create, initialize and return a new node for the stack.
struct stack* newNode (char buf[BUFFER_SIZE])
{
    struct stack *node = malloc(sizeof(struct stack));
    if(isnumber(buf))
    {
        node->val  = (float)strtof(buf,NULL);
    }
    node->next = NULL;
    return node;
}

//only numbers will get pushed onto the stack.
void push (struct stack **top, char buf[BUFFER_SIZE])
{
    //if stack is empty, make new node as top
    if (*(top) == NULL)
    {
        if(isnumber(buf))   //first input cannot be an operator
        {
            *(top) = newNode (buf);
        }
    }

    else
    {
        int operandCount = 0;
        struct stack *temp;
        //if operator, check if enough operands exist in stack. if so, then evaluate. else ignore
        if(isnumber(buf) == 0 && strlen(buf) == 1)
        {
            for(temp = *(top);temp!=NULL;temp=temp->next,operandCount++);   //count the number of operands in the stack

            //if >=2 then evaluate the top two elements using the supplied operator.
            if(operandCount >= 2)
            {
                temp = *(top);
                float operand1 = temp->val;
                float operand2 = temp->next->val;

                switch(buf[0])
                {
                    //after evaluating, remove the top node and store the result in the second node. set the second node as top.
                    case '+':
                        temp->next->val = operand2 + operand1;
                        *(top) = temp->next;
                        free(temp); //free the node to be popped out of the stack.
                        break;

                    case '-':
                        temp->next->val = operand2 - operand1;
                        *(top) = temp->next;
                        free(temp);
                        break;

                    case '*':
                        temp->next->val = operand2 * operand1;
                        *(top) = temp->next;
                        free(temp);
                        break;

                    case '/':
                        temp->next->val = operand2 / operand1;
                        *(top) = temp->next;
                        free(temp);
                        break;
                    
                    default:
                        break;
                }

            }
            
        }
        //if buffer content is a number, then push it onto the stack.
        else if(isnumber(buf))
        {
            temp = newNode (buf);
            temp->next = *(top);
            *(top) = temp;
        }
    }
}

void displayStack (struct stack *top)
{
    //display the stack in the descending order of the stack heirarchy.
    char buf[4][BUFFER_SIZE];
    for(int i=0; i<4;i++)
        bzero(buf[i],BUFFER_SIZE);
    

    char scratchpad[10];
    system("clear");
    
    //load the buffer with the 4 stack contents with formatting.
    int count = 0;
    for(struct stack *temp = top; temp!=NULL && count<4; temp=temp->next,count++)
    {
        bzero(scratchpad,10);
        sprintf(scratchpad,"%c: ",(char)(((int)'A')+count));
        strcat(buf[count],scratchpad);
        sprintf(scratchpad,"%.4f\n",temp->val);
        strcat(buf[count],scratchpad);
    }

    if(count < 4)
    {
        for(; count<4; count++)
        {
            bzero(scratchpad,10);
            sprintf(scratchpad,"%c: \n",(char)(((int)'A')+count));
            strcat(buf[count],scratchpad);
        }
    }

    //print in the reverse order.
    for(int i=3;i>=0;i--)
        printf("%s",buf[i]);
}

//method to print the number of nodes in the stack.
void stackSize(struct stack *top)
{
    int size = 0;
    for(struct stack *temp = top; temp!=NULL; temp=temp->next,size++);
    printf("Stack size = %d\n",size);
}

//remove and free all nodes.
void clearStack(struct stack **top)
{
    if(*(top) != NULL)
    {
        struct stack *temp = *(top);
        struct stack *temp1;
        while(temp)
        {
            temp1 = temp;
            temp = temp->next;
            free(temp1);
        }
        *(top) = temp;
    }
}