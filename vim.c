#include<stdio.h>
#include<string.h>
#include<direct.h>
char amaliat[1000];
char matn[1000];
FILE *fptr;
void creat_file(){
    int flag=1,j=0,a=0;
    char name[1000];
    scanf("/root/%[^\n]s",&amaliat);
    int len=strlen(amaliat);
    for(int i=0;i<len;++i){
        if(amaliat[i]=='"'){
            if(flag==1)
                flag=0;
            else if(flag==0)
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
void insert(){
    int flag=1,j=0,a=0,counter=0,toll_matn;
    char name[1000];
    char matn[1000];
    scanf("/root/%[^\n]s",&amaliat);
    int len=strlen(amaliat);
    for(int i=0;i<len;++i){
        if(amaliat[i]=='"'){
            if(flag==1)
                flag=0;
            else if(flag==0)
                flag=1;
        }
        if(amaliat[i]=='/'&&flag){
            memset(name, '\0', sizeof(name));
            if(amaliat[i-1]=='"')
                a=1;
            strncpy(name,amaliat+j+a,i-j-2*a);
            if(chdir(name)==NULL){
                printf("file does not exists.\n");
                return;
            }
            j=i+1;
            a=0;
        }
        if(amaliat[i]==' '&&flag){
            memset(name, '\0', sizeof(name));
            switch (counter){
                case 0:
                    memset(name, '\0', sizeof(name));
                    if(amaliat[i-1]=='"')
                        strncpy(name,amaliat+j+1,i-j-3);
                    else
                        strncpy(name,amaliat+j,i-j);
                    if(fopen(name,"r")==NULL){
                        printf("file does not exists.\n");
                        return;
                    }
                    else{
                        fptr=fopen(name,"w");
                    }
                    j=i+1;
                    counter++;
                    break;
                case 2:
                if(amaliat[i+1]=='-'&&amaliat[i+2]=='p'&&amaliat[i+3]=='o'&&amaliat[i+4]=='s'){
                    memset(name, '\0', sizeof(name));
                    memset(matn, '\0', sizeof(matn));
                    if(amaliat[i-1]=='"'){
                        strncpy(name,amaliat+j+1,i-j-2);
                        toll_matn=i-j-2;
                    }
                    else{
                        strncpy(name,amaliat+j,i-j);
                        toll_matn=i-j;
                    }
                    int newline=0;
                    for(int z=0;z<toll_matn;z++){
                        if(name[z]==92&&name[z+1]=='n'){
                            matn[z-newline]='\n';
                            z++;
                            newline++;
                        }
                        else
                            matn[z-newline]=name[z];
                    }
                    counter++;
                }
                    break;
                case 3:
                    i++;
                    int satr=0,fasele=0;
                    while (amaliat[i]!=':'){
                        satr=10*satr+amaliat[i]-48;
                        i++;
                    }
                    i++;
                    while (i<len){
                        fasele=10*fasele+amaliat[i]-48;
                        i++;
                    }
                    for (int i = 1; i < satr; i++){
                        fprintf(fptr,"\n");
                    }
                    for (int i = 0; i < fasele; i++){
                        fprintf(fptr," ");
                    }
                    fprintf(fptr,"%s",matn);
                    fclose(fptr);
                    i=len;
                    counter++;
                    break;
                default:
                    j=i+1;
                    counter++;
                    
                    break;
            }
        }
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
    if(strstr(amaliat,"insertstr")){
        scanf("%[^/]s",amaliat);
        insert();
    }
}