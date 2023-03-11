#include <stdio.h>
#include <stdlib.h>

// Ali Adel Ali Hassan     Section 4

int main()
{
    char str[100];
    gets(str);
    if(str[0]=='/'){
        if(str[1]=='/') puts("This is a comment");
        else if(str[1]=='*'){
            int i;
            int flag=0;
            for(i = 2; i < 99; i++){
                if(str[i]=='*' && str[i+1]=='/'){
                    flag=1;
                }
            }
            if(flag) puts("This is a comment");
            else puts("This is not a comment");
        }
        else puts("This is not a comment");
    }
    else puts("This is not a comment");
}
