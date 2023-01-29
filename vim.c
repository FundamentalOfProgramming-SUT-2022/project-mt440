#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include<direct.h>
char noe_amaliat[1000];
char matn_amaliat[1000];
char matn_file[100];
char matn[10000];
char name[1000];
char name_of_file[1000];
char clipboard[1000];
char files[100][1000];
char* token;
FILE *fptr;
FILE *fptr1;
FILE *fptr2;
void invalids(int n){
    switch (n){
    case 1:
        printf("The file already exists.\n");
        break;
    case 2:
        printf("file or directory does not exists.\n");
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
                                matn[z-newline]='n';
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
                        memset(clipboard,NULL,sizeof(clipboard));                        
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
void cut(){
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
                        fptr=fopen(name_of_file,"w");
                        memset(clipboard,NULL,sizeof(clipboard));
                        int j=0;
                        for(int i=0;i<z-1;i++){
                            if(d==1){
                                if(i>=len&&i<len+tedad){
                                    clipboard[j]=matn_file[i];
                                    j++;
                                }
                                else
                                    fprintf(fptr,"%c",matn_file[i]);
                            }
                            else{
                                if(i>=len-tedad&&i<len){
                                    clipboard[j]=matn_file[i];
                                    j++;
                                }
                                else
                                    fprintf(fptr,"%c",matn_file[i]);   
                            }
                        }
                        fclose(fptr);
                        return;
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
void pastestr(){
    int flag=1,j=0,a=0,counter=0,fasele=0,satr=0,toll_matn;
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
                case 1:
                    i++;
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
                default :
                    j=i+1;
                    counter++;
                    break;
            }
        }
    }
    int tedad=("%d",strlen(clipboard));
        char character;
        int shomare_satr=1;
        int check_fasele=0;
        int z=0,d=1;
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
        fptr=fopen(name_of_file,"w");
        j=0;
        for(int i=0;i<z-1+j;i++){
            if(i>=len&&i<len+tedad){
                fprintf(fptr,"%c",clipboard[j]);
                j++;
            }
            else
                fprintf(fptr,"%c",matn_file[i-j]);
        }
        fclose(fptr);
        return;    
}

void grep(){
    token--;
    if(!(*(token-1)=='-' &&*(token)=='-'&&*(token+1)=='s' && *(token+2)=='t' && *(token+3)=='r' && *(token+4)=='\0')){
        invalids(4);
        return;
    }
	token = strtok(NULL, "\n");
	strcpy(matn_amaliat,token);
    int i=0,toll_matn,flag=1,tedad_file=0;
    while(1){
        if(matn_amaliat[i+1]=='-'&&matn_amaliat[i+2]=='-'&&matn_amaliat[i+3]=='f' && matn_amaliat[i+4]=='i' && matn_amaliat[i+5]=='l' && matn_amaliat[i+6]=='e' && matn_amaliat[i+7]=='s'){
            memset(name, '\0', sizeof(name));
            memset(matn, '\0', sizeof(matn));
            if(matn_amaliat[i-1]=='"'){
                strncpy(name,matn_amaliat+1,i-2);
                toll_matn=i-2;
            }
            else{
                strncpy(name,matn_amaliat,i);
                toll_matn=i;
            }
            break;
        }
        i++;
    }
    strcpy(matn_file,name);
    i+=9;
    i++;
    int j=i;
    int a=0;
    int len=strlen(matn_amaliat);
    for(i;i<=len;++i){
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
                printf("%s ",name);
                invalids(2);
                return;
            }
            j=i+1;
            a=0;
        }
        if((matn_amaliat[i]==' ' || i==len)&&flag){
            memset(name, '\0', sizeof(name));
            memset(name, '\0', sizeof(name));
            if(matn_amaliat[i-1]=='"')
                strncpy(name,matn_amaliat+j+1,i-j-3);
            else
                strncpy(name,matn_amaliat+j,i-j);
            if(fopen(name,"r")==NULL){
                printf("%s ",name);
                invalids(2);
                    return;
                }
            else{
                strcpy(files[tedad_file],name);
                tedad_file++;
                chdir("C:\\Users\\torab\\OneDrive\\Documents\\codes\\proje");
                i++;
            }
            j=i+1;
        }
    }
    int num=0;
    chdir("root");
    for(i=0 ; i< tedad_file ; i++){
        fptr= fopen(files[i],"r");
        while(!feof(fptr)){
            fgets(name,100,fptr);
            if(strstr(name, matn_file)){
                printf("%s: %s",files[i],name);
                num++;
            }
        }
    }
    if(num==0)
        printf("This string does not exist in these files.\n");
}

void grep_counter(){
	token = strtok(NULL, " ");
    token++;
    if(!(*(token)=='-'&&*(token+1)=='s' && *(token+2)=='t' && *(token+3)=='r' && *(token+4)=='\0')){
        invalids(4);
        return;
    }
	token = strtok(NULL, "\n");
	strcpy(matn_amaliat,token);
    int i=0,toll_matn,flag=1,tedad_file=0;
    while(1){
        if(matn_amaliat[i+1]=='-'&&matn_amaliat[i+2]=='-'&&matn_amaliat[i+3]=='f' && matn_amaliat[i+4]=='i' && matn_amaliat[i+5]=='l' && matn_amaliat[i+6]=='e' && matn_amaliat[i+7]=='s'){
            memset(name, '\0', sizeof(name));
            memset(matn, '\0', sizeof(matn));
            if(matn_amaliat[i-1]=='"'){
                strncpy(name,matn_amaliat+1,i-2);
                toll_matn=i-2;
            }
            else{
                strncpy(name,matn_amaliat,i);
                toll_matn=i;
            }
            break;
        }
        i++;
    }
    strcpy(matn_file,name);
    i+=9;
    i++;
    int j=i;
    int a=0;
    int len=strlen(matn_amaliat);
    for(i;i<=len;++i){
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
        if((matn_amaliat[i]==' ' || i==len)&&flag){
            memset(name, '\0', sizeof(name));
            memset(name, '\0', sizeof(name));
            if(matn_amaliat[i-1]=='"')
                strncpy(name,matn_amaliat+j+1,i-j-3);
            else
                strncpy(name,matn_amaliat+j,i-j);
            if(fopen(name,"r")==NULL){
                printf("%s ",name);
                invalids(2);
                    return;
                }
            else{
                strcpy(files[tedad_file],name);
                tedad_file++;
                chdir("C:\\Users\\torab\\OneDrive\\Documents\\codes\\proje");
                i++;
            }
            j=i+1;
        }
    }
    int num=0;
    chdir("root");
    for(i=0 ; i< tedad_file ; i++){
        fptr= fopen(files[i],"r");
        while(!feof(fptr)){
            fgets(name,100,fptr);
            if(strstr(name, matn_file))
                num++;
        }
    }
    printf("%d\n",num);
}

void grep_files(){
    	token = strtok(NULL, " ");
        token++;
    if(!(*(token)=='-'&&*(token+1)=='s' && *(token+2)=='t' && *(token+3)=='r' && *(token+4)=='\0')){
        invalids(4);
        return;
    }
	token = strtok(NULL, "\n");
	strcpy(matn_amaliat,token);
    int i=0,toll_matn,flag=1,tedad_file=0;
    while(1){
        if(matn_amaliat[i+1]=='-'&&matn_amaliat[i+2]=='-'&&matn_amaliat[i+3]=='f' && matn_amaliat[i+4]=='i' && matn_amaliat[i+5]=='l' && matn_amaliat[i+6]=='e' && matn_amaliat[i+7]=='s'){
            memset(name, '\0', sizeof(name));
            memset(matn, '\0', sizeof(matn));
            if(matn_amaliat[i-1]=='"'){
                strncpy(name,matn_amaliat+1,i-2);
                toll_matn=i-2;
            }
            else{
                strncpy(name,matn_amaliat,i);
                toll_matn=i;
            }
            break;
        }
        i++;
    }
    strcpy(matn_file,name);
    i+=9;
    i++;
    int j=i;
    int a=0;
    int len=strlen(matn_amaliat);
    for(i;i<=len;++i){
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
        if((matn_amaliat[i]==' ' || i==len)&&flag){
            memset(name, '\0', sizeof(name));
            memset(name, '\0', sizeof(name));
            if(matn_amaliat[i-1]=='"')
                strncpy(name,matn_amaliat+j+1,i-j-3);
            else
                strncpy(name,matn_amaliat+j,i-j);
            if(fopen(name,"r")==NULL){
                printf("%s ",name);
                invalids(2);
                    return;
                }
            else{
                strcpy(files[tedad_file],name);
                tedad_file++;
                chdir("C:\\Users\\torab\\OneDrive\\Documents\\codes\\proje");
                i++;
            }
            j=i+1;
        }
    }
    int num=0;
    chdir("root");
    for(i=0 ; i< tedad_file ; i++){
        fptr= fopen(files[i],"r");
        while(!feof(fptr)){
            fgets(name,100,fptr);
            if(strstr(name, matn_file)){
                printf("%s\n",files[i]);
                num++;
            }
        }
        fclose(fptr);
        if(num==0)
            printf("This string does not exist in these files.\n");
    }
}

void grep_checker(){
    token = strtok(matn_amaliat, " - ");
    switch (*token)
    {
    case 'c':
        grep_counter();
        break;
    case 'l':
        grep_files();
        break;
    case 's':
        grep();
        break;
    default:
        invalids(4);
        break;
    }
}
auto_indent(){
    int j=0,a=0,flag=1;
    int len=strlen(matn_amaliat);
    for(int i=0;i<=len;++i){
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
        if(i==len&&flag){
            memset(name, '\0', sizeof(name));
            memset(name, '\0', sizeof(name));
            if(matn_amaliat[i-1]=='"')
                strncpy(name,matn_amaliat+j+1,i-j-3);
            else
                strncpy(name,matn_amaliat+j,i-j);
            if(fptr1=fopen(name,"r")==NULL){
                printf("%s ",name);
                invalids(2);
                    return;
            }
        }
    }
    fclose(fptr1);
    fptr1=fopen(name,"r");
    char name_cheker[1000];
    strcpy(name_cheker,name);
    while(fptr2=fopen(name_cheker,"r")!=NULL){
        strcat(name_cheker,"a");
    }
    fclose(fptr2);
    fptr2=fopen(name_cheker,"w");
    char c = fgetc(fptr1);
    char c_cheker=' ';
    int tedad_tab=0;
    while (c != EOF)
    {
        if(c==' '){
            while(c==' ')
                c = fgetc(fptr1);
            if(c_cheker!='}' && c_cheker!='{')
                fputc(' ',fptr2);
            c_cheker=' ';
        }
        if(c=='}'){
            fputc('\n',fptr2);
            tedad_tab--;
            for(j=0;j<4*tedad_tab;j++)
                fputc(' ',fptr2);
        }
        if(c=='{' && c_cheker!=' ' && c_cheker!='{' && c_cheker !='}')
           fputc(' ',fptr2);
        fputc(c, fptr2);
        if(c=='}'&& tedad_tab==0)
            fputc('\n',fptr2);
        if(c=='{'){
            tedad_tab++;
            fputc('\n',fptr2);
            for(j=0;j<4*tedad_tab;j++)
                fputc(' ',fptr2);
        }
        c_cheker=c;
        c = fgetc(fptr1);
    }
    fclose(fptr1);
    fclose(fptr2);
    fptr1=fopen(name_cheker,"r");
    fptr2=fopen(name,"w");
    c_cheker = fgetc(fptr1);
    c = fgetc(fptr1);
    while (c != EOF)
    {
        fputc(c_cheker, fptr2);
        c_cheker=c;
        c = fgetc(fptr1);
    }
    if(c_cheker!='\n')
        fputc(c_cheker,fptr2);
    fclose(fptr1);
    fclose(fptr2);
    remove(name_cheker);
}
int main(){
    while (1){
        chdir("C:\\Users\\torab\\OneDrive\\Documents\\codes\\proje\\root");
        scanf("%s",&noe_amaliat);
        if(!strcmp(noe_amaliat,"exit"))
            return 0;
        if(!strcmp(noe_amaliat,"createfile")){
            scanf("%[^/]s",&matn_file);
            scanf("/root/%[^\n]s",&matn_amaliat);
            creat_file();
        }
        else if(!strcmp(noe_amaliat,"insertstr")){
            scanf("%[^/]s",&matn_file);
            scanf("/root/%[^\n]s",&matn_amaliat);
            insert();
        }
        else if(!strcmp(noe_amaliat,"cat")){
            scanf("%[^/]s",&matn_file);
            scanf("/root/%[^\n]s",&matn_amaliat);
            cat();
        }
        else if(!strcmp(noe_amaliat,"removetstr")){
            scanf("%[^/]s",&matn_file);
            scanf("/root/%[^\n]s",&matn_amaliat);
            removetstr();
        }
        else if(!strcmp(noe_amaliat,"copystr")){
            scanf("%[^/]s",&matn_file);
            scanf("/root/%[^\n]s",&matn_amaliat);
            copy();
        }
        else if(!strcmp(noe_amaliat,"cutstr")){
            scanf("%[^/]s",&matn_file);
            scanf("/root/%[^\n]s",&matn_amaliat);
            cut();
        }
        else if(!strcmp(noe_amaliat,"pastestr")){
            scanf("%[^/]s",&matn_file);
            scanf("/root/%[^\n]s",&matn_amaliat); 
            pastestr();
        }
        else if(!strcmp(noe_amaliat,"grep")){
            scanf("%[^\n]s",&matn_amaliat);
            chdir(".."); 
            grep_checker();
        }
        else if(!strcmp(noe_amaliat,"auto-indent")){
            scanf("%[^/]s",&matn_file);
            scanf("/root/%[^\n]s",&matn_amaliat);
            auto_indent();
        }
    }
}