/*
By Ashwin Natarajan. No GUI yet. Only supports +,-,/,* for now.


*/
#include "rpn.h"

int main()
{
    struct stack *top = NULL;   //initialize the computation stack
    char buf[BUFFER_SIZE];      //input buffer

    //initialize the menu.
    displayStack(top);
    stackSize(top);
    bzero(buf,BUFFER_SIZE);
   
    while(1)
    {        
        printf("\rInput: ");
        bzero(buf,BUFFER_SIZE);
        scanf("%s",buf);    //load the user stack
        
        if(stricmp(buf,EXIT) == 0)  //check for exit condition
            break;

        if(stricmp(buf,CLEAR) == 0) //check for clear stack condittion
        {
            clearStack(&top);
        }
        else
        {
            push(&top,buf); //push to stack
        }

        displayStack(top);
        stackSize(top);
    }
    clearStack(&top);

    return 0;
}
