#include<stdio.h>
#include<string.h>
#include<direct.h>
char noe_amaliat[1000];
char matn_amaliat[1000];
char matn_file[100];
char matn[10000];
char name[1000];
char name_of_file[1000];
char clipboard[1000];
FILE *fptr;
void invalids(int n){
    switch (n){
    case 1:
        printf("The file already exists.\n");
        break;
    case 2:
        printf("file does not exists.\n");
        break;
    case 3:
        printf("You have reached the EOF, please change the position of the text.\n");
    case 4:
        printf("invalid input.\n");
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
        fptr=fopen(name,"w");
        fclose(fptr);
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
            if(chdir(name)!=NULL){
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
                    if(satr<=0||fasele<0){
                        invalids(4);
                        return;
                    }
                    fseek(fptr,0,SEEK_SET);
                    int shomare_khat=1;
                    char ch;
                    while (shomare_khat<satr){
                        do {
                            ch=fgetc(fptr);
                		    fseek(fptr,1,SEEK_CUR);
                    	} while (ch!='\n'&&ch!=EOF);
                            if(ch==EOF){
                                invalids(3);
                                return;
                            }
                        shomare_khat++;
                    }
                    fseek(fptr,fasele,SEEK_CUR);
                    len=strlen(matn);
                    int z=0,b=0;
                    ch=0;
                    memset(matn_file,"\0",sizeof(matn_file));
                    if(shomare_khat!=1)
                        fseek(fptr,-1,SEEK_CUR);
                    ch=fgetc(fptr);
                    while (ch!=EOF){
                        matn_file[z]=ch;
                        ch=fgetc(fptr);
                        if(ch=='\n')
                            b++;
                        z++;
                    }
                    len=z;
                    fseek(fptr,-z-b,SEEK_CUR);
                    fprintf(fptr,"%s",matn);
                    for(int z=0;z<len;z++){
                        fprintf(fptr,"%c",matn_file[z]);
                    }
                    fclose(fptr);
                    return;
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
            if(chdir(name)!=NULL){
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
void removetstr(){
    int flag=1,j=0,a=0,counter=0,satr=0,fasele=0,toll_matn;
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
            if(chdir(name)!=NULL){
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
                        int len=strlen(name);
                        strncpy(name_of_file,name,len);
                    }
                    j=i+1;
                    counter++;
                    break;
                case 2:
                    i++;
                    int tedad=0;
                    while (matn_amaliat[i]!=32){
                        tedad=tedad*10+matn_amaliat[i]-48;
                        i++;
                    }
                    i++;
                    if(matn_amaliat[i]=='-'&&(matn_amaliat[i+1]=='b'||matn_amaliat[i+1]=='f')){
                        char character;
                        int shomare_satr=1;
                        int check_fasele=0;
                        int z=0,d=1;
                        if(matn_amaliat[i+1]=='b')
                            d=-1;
                        while(shomare_satr<satr){
                            character=fgetc(fptr);
                            if(character=='\n')
                                shomare_satr++;
                            if(character==EOF){
                                invalids(3);
                                return;
                            }
                            matn_file[z]=character;
                            z++;
                        }
                        while(check_fasele<fasele){
                            character=fgetc(fptr);
                            if(character==EOF){
                                invalids(3);
                                return;
                            }
                            check_fasele++;
                            matn_file[z]=character;
                            z++;
                        }
                        len=z;
                        while(character!=EOF){
                            character=fgetc(fptr);
                            matn_file[z]=character;
                            z++;
                        }
                        fclose(fptr);
                        fopen(name_of_file,"w+");
                        for(int i=0;i<z-1;i++){
                            if(d==1){
                                if(i<len||i>=len+tedad)
                                    fprintf(fptr,"%c",matn_file[i]);
                            }
                            else{
                                if(i<len-tedad||i>=len){
                                    fprintf(fptr,"%c",matn_file[i]);
                                }
                            }
                        }
                        fclose(fptr);
                    }
                    else{
                        invalids(4);
                        return;
                    }
                    break;
                case 1:
                    i++;
                    while (matn_amaliat[i]!=':'){
                        satr=10*satr+matn_amaliat[i]-48;
                        
                        i++;
                    }
                    i++;
                    while (matn_amaliat[i]!=' '){
                        fasele=10*fasele+matn_amaliat[i]-48;
                        i++;
                    }
                    if(satr<=0||fasele<0){
                        invalids(4);
                        return;
                    }
                    j=i+1;
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
void copy(){
    memset(clipboard,NULL,sizeof(clipboard));
    int flag=1,j=0,a=0,counter=0,satr=0,fasele=0,toll_matn;
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
            if(chdir(name)!=NULL){
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
                        int len=strlen(name);
                        strncpy(name_of_file,name,len);
                    }
                    j=i+1;
                    counter++;
                    break;
                case 2:
                    i++;
                    int tedad=0;
                    while (matn_amaliat[i]!=32){
                        tedad=tedad*10+matn_amaliat[i]-48;
                        i++;
                    }
                    i++;
                    if(matn_amaliat[i]=='-'&&(matn_amaliat[i+1]=='b'||matn_amaliat[i+1]=='f')){
                        char character;
                        int shomare_satr=1;
                        int check_fasele=0;
                        int z=0,d=1;
                        if(matn_amaliat[i+1]=='b')
                            d=-1;
                        while(shomare_satr<satr){
                            character=fgetc(fptr);
                            if(character=='\n')
                                shomare_satr++;
                            if(character==EOF){
                                invalids(3);
                                return;
                            }
                            matn_file[z]=character;
                            z++;
                        }
                        while(check_fasele<fasele){
                            character=fgetc(fptr);
                            if(character==EOF){
                                invalids(3);
                                return;
                            }
                            check_fasele++;
                            matn_file[z]=character;
                            z++;
                        }
                        len=z;
                        while(character!=EOF){
                            character=fgetc(fptr);
                            matn_file[z]=character;
                            z++;
                        }
                        fclose(fptr);
                        int j=0;
                        for(int i=0;i<z-1;i++){
                            if(d==1){
                                if(i>=len&&i<len+tedad){
                                    clipboard[j]=matn_file[i];
                                    j++;
                                }
                            }
                            else{
                                if(i>=len-tedad&&i<len){
                                    clipboard[j]=matn_file[i];
                                    j++;
                                }
                            }
                        }
                    }
                    else{
                        invalids(4);
                        return;
                    }
                    break;
                case 1:
                    i++;
                    while (matn_amaliat[i]!=':'){
                        satr=10*satr+matn_amaliat[i]-48;
                        
                        i++;
                    }
                    i++;
                    while (matn_amaliat[i]!=' '){
                        fasele=10*fasele+matn_amaliat[i]-48;
                        i++;
                    }
                    if(satr<=0||fasele<0){
                        invalids(4);
                        return;
                    }
                    j=i+1;
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
    while (1){
        chdir("root");
        scanf("%s",&noe_amaliat);
        if(!strcmp(noe_amaliat,"exit"))
            return 0;
        scanf("%[^/]s",&matn_file);
        scanf("/root/%[^\n]s",&matn_amaliat);
        if(!strcmp(noe_amaliat,"createfile")){
            creat_file();
        }
        else if(!strcmp(noe_amaliat,"insertstr")){
            insert();
        }
        else if(!strcmp(noe_amaliat,"cat")){
            cat();
        }
        else if(!strcmp(noe_amaliat,"removetstr")){
            removetstr();
        }
        else if(!strcmp(noe_amaliat,"copystr")){
            copy();
            printf("%s",clipboard);
        }
    }
}