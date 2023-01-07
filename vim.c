#include<stdio.h>
#include<string.h>
#include<direct.h>
char amaliat[100];
void creat_file(){
    int flag=1,j=0,a=0;
    char name[100];
    scanf("/root/%[^\n]s",&amaliat);
    int len=strlen(amaliat);
    for(int i=0;i<len;++i){
        if(amaliat[i]=='"'){
            if(flag==1)
                flag=0;
            if(flag==0)
                flag=1;
        }
        if(amaliat[i]=='/'&&flag){
            memset(name, '\0', sizeof(name));
            if(amaliat[i-1]=='"')
                a=1;
            strncpy(name,amaliat+j+a,i-j-2*a);
            mkdir(name);
            chdir(name);
            j=i+1;
            a=0;
        }
    }
    memset(name, '\0', sizeof(name));
    if(amaliat[j]=='"')
        strncpy(name,amaliat+j+1,len-j-2);
    else
        strncpy(name,amaliat+j,len-j);
    if(fopen(name,"r")!=NULL){
        printf("The file already exists.\n");
        return;
    }
    else{
        fopen(name,"w");
        fclose(name);
        return;
    }
}
int main(){
    mkdir("root");
    chdir("root");
    scanf("%s",&amaliat);
    if(strstr(amaliat,"createfile")){
        scanf("%[^/]s",amaliat);
        creat_file();
    }
}