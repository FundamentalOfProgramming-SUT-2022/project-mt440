#include<stdio.h>
#include<string.h>
#include<direct.h>
char noe_amaliat[1000];
char matn_amaliat[1000];
char matn_file[100];
char matn[1000];
char name[1000];
FILE *fptr;
void invalids(int n){
    switch (n){
    case 1:
        printf("The file already exists.\n");
        break;
    case 2:
        printf("file does not exists.\n");
        break;
    default:
        break;
    }
}
void creat_file(){
    int flag=1,j=0,a=0;
    int len=strlen(matn_amaliat);
    for(int i=0;i<len;++i){
        if(matn_amaliat[i]=='"'){
            if(flag==1)
                flag=0;
            else if(flag==0)
                flag=1;
        }
        if(matn_amaliat[i]=='/'&&flag){
            memset(name, '\0', sizeof(name));
            if(matn_amaliat[i-1]=='"')
                a=1;
            strncpy(name,matn_amaliat+j+a,i-j-2*a);
            mkdir(name);
            chdir(name);
            j=i+1;
            a=0;
        }
    }
    memset(name, '\0', sizeof(name));
    if(matn_amaliat[j]=='"')
        strncpy(name,matn_amaliat+j+1,len-j-2);
    else
        strncpy(name,matn_amaliat+j,len-j);
    if(fopen(name,"r")!=NULL){
        invalids(1);
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
    int len=strlen(matn_amaliat);
    for(int i=0;i<len;++i){
        if(matn_amaliat[i]=='"'){
            if(flag==1)
                flag=0;
            else if(flag==0)
                flag=1;
        }
        if(matn_amaliat[i]=='/'&&flag){
            memset(name, '\0', sizeof(name));
            if(matn_amaliat[i-1]=='"')
                a=1;
            strncpy(name,matn_amaliat+j+a,i-j-2*a);
            if(chdir(name)==NULL){
                invalids(2);
                return;
            }
            j=i+1;
            a=0;
        }
        if(matn_amaliat[i]==' '&&flag){
            memset(name, '\0', sizeof(name));
            switch (counter){
                case 0:
                    memset(name, '\0', sizeof(name));
                    if(matn_amaliat[i-1]=='"')
                        strncpy(name,matn_amaliat+j+1,i-j-3);
                    else
                        strncpy(name,matn_amaliat+j,i-j);
                    if(fopen(name,"r")==NULL){
                        invalids(2);
                        return;
                    }
                    else{
                        fptr=fopen(name,"r+");
                    }
                    j=i+1;
                    counter++;
                    break;
                case 2:
                if(matn_amaliat[i+1]=='-'&&matn_amaliat[i+2]=='-'&&matn_amaliat[i+3]=='p'&&matn_amaliat[i+4]=='o'){
                    memset(name, '\0', sizeof(name));
                    memset(matn, '\0', sizeof(matn));
                    if(matn_amaliat[i-1]=='"'){
                        strncpy(name,matn_amaliat+j+1,i-j-2);
                        toll_matn=i-j-2;
                    }
                    else{
                        strncpy(name,matn_amaliat+j,i-j);
                        toll_matn=i-j;
                    }
                    int newline=0;
                    for(int z=0;z<toll_matn;z++){
                        if(name[z]==92&&name[z+1]=='n'){
                            if(name[z-1]==92)
                                matn[z-newline]=='n';
                            else
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
                    while (matn_amaliat[i]!=':'){
                        satr=10*satr+matn_amaliat[i]-48;
                        i++;
                    }
                    i++;
                    while (i<len){
                        fasele=10*fasele+matn_amaliat[i]-48;
                        i++;
                    }
                    fseek(fptr,0,SEEK_SET);
                    int shomare_khat=1;
                    char ch;
                    int b=1;
                    while (shomare_khat<satr){
                        do {
                            ch=fgetc(fptr);
                		    fseek(fptr,1,SEEK_CUR);
                    	} while (ch!='\n'&&ch!=EOF);
                            if(ch==EOF){
                                fprintf(fptr,"\n");
                                b=0;
                            }
                        shomare_khat++;
                    }
                    fseek(fptr,fasele-b,SEEK_CUR);
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
void cat(){
    int flag=1,j=0,a=0,counter=0,toll_matn;
    int len=strlen(matn_amaliat);
    for(int i=0;i<len;++i){
        if(matn_amaliat[i]=='"'){
            if(flag==1)
                flag=0;
            else if(flag==0)
                flag=1;
        }
        if(matn_amaliat[i]=='/'&&flag){
            memset(name, '\0', sizeof(name));
            if(matn_amaliat[i-1]=='"')
                a=1;
            strncpy(name,matn_amaliat+j+a,i-j-2*a);
            if(chdir(name)==NULL){
                invalids(2);
                return;
            }
            j=i+1;
            a=0;
        }
    }
    memset(name, '\0', sizeof(name));
    if(matn_amaliat[j]=='"')
        strncpy(name,matn_amaliat+j+1,len-j-2);
    else
        strncpy(name,matn_amaliat+j,len-j);
    if(fopen(name,"r")==NULL){
        invalids(2);
        return;
    }
    else{
        fptr=fopen(name,"r");
        char ch;
        do {
    		ch = fgetc(fptr);
	    	printf("%c", ch);
    	} while (ch!=EOF);
	    fclose(fptr);
    }
}
int main(){
    mkdir("root");
    chdir("root");
    scanf("%s",&noe_amaliat);
    scanf("%[^/]s",&matn_file);
    scanf("/root/%[^\n]s",&matn_amaliat);
    if(!strcmp(noe_amaliat,"createfile")){
        creat_file();
    }
    if(!strcmp(noe_amaliat,"insertstr")){
        insert();
    }
    if(!strcmp(noe_amaliat,"cat")){
        cat();
    }
}