#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>


#define EXIT_NO_FILE 1
int dot_product(int *x,int *y,int n);
void oops(char *s1, const char *s2);
void doubleword(const char *name, FILE *fp);
int getword(FILE *fp,char *buf, int size);

int linenum;

int main(int argc, char const *argv[])
{
    int i;
    for(i=1;i<argc;i++){
        FILE*fp=fopen(argv[i],"r");
        if(fp==NULL){
            oops("Can't view ",argv[i]);
        }else{
            doubleword(argv[i],fp);
            fclose(fp);
        }
    }
    if(argc==1){
        doubleword(NULL,stdin);
    }
    return 0;
}


int dot_product(int *x,int *y,int n)
{
    int sum;
    for(int i=0;i<n;i++){
        sum+=*(x+i) * *(y+i);
    }
    return sum;
}
void oops(char *s1,const char *s2)
{
    fprintf(stderr,"Error : %s ",s1);
    perror(s2);
    exit(EXIT_NO_FILE);
}
int getword(FILE *fp,char *buf, int size)
{
    int c;
    c=getc(fp);
    for(;c!=EOF&&isspace(c);c=getc(fp)){
        if(c=='\n'){
            linenum++;
        }
    }
    int i=0;
    for(;c!=EOF&&!isspace(c);c=getc(fp)){
        if(i<size-1){
            buf[i++]=tolower(c);
        }
    }
    if(i<size){
        buf[i]='\0';
    }
    if(c!=EOF){
        ungetc(c,fp);
    }
    return buf[0]!='\0';
}
void doubleword(const char *name, FILE *fp)
{
    char prev[128],word[128];
    linenum=1;
    prev[0]='\0';
    while(getword(fp,word,sizeof(word))){
        if(isalpha(word[0])&&strcmp(prev,word)==0){
            if(name){
                printf("%s: ",name);
            }
            printf("%d: %s\n",linenum,word);
        }
    }
}