#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Ali Adel Ali Hassan     Section 4

char keywords[1000][10],id[1000][20],notid[1000][20],numbers[1000][15],ops[1000][2],strtoken[100][100],specialcahr[1000][2];
int ki,idi,noti,ni,opi,stk,sc;
bool isKeyword(char str[]){
	if (!strcmp(str, "int") || !strcmp(str, "char") || !strcmp(str, "for") ||
        !strcmp(str, "while") || !strcmp(str, "break") || !strcmp(str, "continue") ||
        !strcmp(str, "if") || !strcmp(str, "else") || !strcmp(str, "float") ||
        !strcmp(str, "double") || !strcmp(str, "void") || !strcmp(str, "return") ||
        !strcmp(str, "bool") || !strcmp(str, "scanf") || !strcmp(str, "printf") ||
        !strcmp(str, "true") || !strcmp(str, "false"))
		return (true);
	return (false);
}
bool isOperator(char ch)
{
	if (ch == '+' || ch == '-' || ch == '*' ||
		ch == '/' || ch == '>' || ch == '<' ||
		ch == '=' || ch == '%' || ch == '|' ||
		ch == '&' || ch == '!')
		return (true);
	return (false);
}
bool isDelimiter(char ch, int option)
{
    if(ch==' ' || ch == '\0' || ch == '\t') return true;
	if (ch == ',' || ch == ';' || ch == '(' ||
        ch == ')' || ch == '[' || ch == ']' ||
        ch == '{' || ch == '}'){
        if(option){
            specialcahr[sc][0]=ch;
            sc++;
        }
		return (true);
    }
    if(isOperator(ch)){
        if(option){
            ops[opi][0]=ch;
            opi++;
        }
        return true;
    }
	return (false);
}
bool isDigit(char ch)
{
	if (ch <= '9' && ch >= '0')
		return (true);
	return (false);
}
bool isAlpha(char ch){
    if((ch <= 'z' && ch >= 'a') || (ch <= 'Z' && ch >= 'A')) return true;
    return false;
}
bool validIdentifier(char str[])
{
	if (!isAlpha(str[0]))
		return (false);
    int i=0;
    while(str[i]!='\0'){
        if(!isAlpha(str[i])&&!isDigit(str[i])) return false;
        i++;
    }
	return (true);
}
void parse(char str[]){
    int i = 0,j = 0,w;
    while(str[j]!='\0'){
        char token[100];
        int k=0;
        while(isDelimiter(str[i],1)){
            i++;
            if(str[i]=='\0') return;
        }
        if(str[i]=='"'){
            j=i+1;
            while(str[j]!='"' && str[j]!='\0') j++;
            if(str[j]=='"'){
                for(;i<=j;i++,k++) token[k]=str[i];
                for(w=0;w < k; w++){
                    strtoken[stk][w]=token[w];
                }
                stk++;
                j++;
            }
            else{
                for(;i<j;i++,k++) token[k]=str[i];
                for(w=0;w < k; w++){
                    notid[noti][w]=token[w];
                }
                noti++;
                i=j;
            }
            continue;
        }
        j=i;
        while(!isDelimiter(str[j],0)) j++;
        for(;i<j;i++,k++) token[k]=str[i];
        token[k++]='\0';
        i=j;
        if(isKeyword(token)){
            for(w=0;w < k; w++){
                keywords[ki][w]=token[w];
            }
            ki++;
            continue;
        }
        int d=0,p=0;
        for(w=0;w<k;w++){
            if(isDigit(token[w])) d++;
            else if(token[w]=='.') p++;
        }
        if(d+1==w || (p==1 && d+2==w)){
            for(w=0;w < k; w++){
                numbers[ni][w]=token[w];
            }
            ni++;
            continue;
        }
        if(validIdentifier(token)){
            for(w=0;w < k; w++){
                id[idi][w]=token[w];
            }
            idi++;
        }
        else{
            for(w=0;w < k; w++){
                notid[noti][w]=token[w];
            }
            noti++;
        }
    }
}
int main()
{
	char s[100][100];
	int idx;
	int num=100;
	puts("Enter your program\nType $ when you are done:\n");
	for(idx=0; idx < num; idx++){
        gets(s[idx]);
	    if(!strcmp(s[idx],"$")) break;
	}
	for(idx=0; idx < num; idx++){
	    if(!strcmp(s[idx],"$")) break;
        parse(s[idx]);
	}
	puts("_______________________________________");
    if(ki) printf("Keywords:  ");
    for(idx=0; idx < ki; idx++) printf("(%s) ",keywords[idx]);
    if(ni) printf("\nNumbers:  ");
    for(idx=0; idx < ni; idx++) printf("(%s) ",numbers[idx]);
    if(opi) printf("\nOperators:  ");
    for(idx=0; idx < opi; idx++) printf("(%s) ",ops[idx]);
    if(sc) printf("\nSpecial:  ");
    for(idx=0; idx < sc; idx++) printf("(%s) ",specialcahr[idx]);
    if(idi) printf("\nIdentifiers:  ");
	for(idx=0; idx < idi; idx++) printf("(%s) ",id[idx]);
	if(stk) printf("\nString tokens:  ");
	for(idx=0; idx < stk; idx++) printf("(%s) ",strtoken[idx]);
	if(noti) printf("\nNon valid tokens:  ");
	for(idx=0; idx < noti; idx++) printf("(%s) ",notid[idx]);
	puts("");
	return (0);
}
