#include <stdlib.h>
#include <stdio.h>



int main(int argc,char** argv)
{
    int num = 0;

    do{
        printf("please enter a number between 0 to 9.\n");
        fflush(stdin);
        scanf("%d",&num);
        if(num < 10 && num > -1) break;
        else{
            printf("%d is an invalid input\n",num);
        }
    }while(1);
    
    printf("you have entered the numeral %d\n",num);
    system("pause");
    return 0;
}
