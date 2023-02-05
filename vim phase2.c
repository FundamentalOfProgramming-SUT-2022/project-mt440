#include <ncurses.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<math.h>
int startx=0, starty=0, width=150, height=40,ch;
char my_file_name[1000];
char my_mode[1000];
char clipboard[10000];
char neveshte [40][150];
char command[10000];
char command2[10000];
char file_mode;
int mahal_find[40][150];
void normal_mode();
void insert_mode();
void visual_mode();
FILE *fptr;
void mahal(int a,int b);
int vasiat_khat[40];
void strrev(char str[]){
    int i=0;
    int j=strlen(str)-1;
    while(i<j){
        char temp=str[i];
        str[i]=str[j];
        str[j]=temp;
        i++;
        j--;
    }    
}
void choose_matn(int first_y,int first_x){
    int sabet;
    int startx2=startx;
    int starty2=starty;
    for(int i=0;vasiat_khat[i];i++){
        move(i,0);
        clrtoeol();
        mvprintw(i,0,"%d %s",i+1,neveshte[i]);    
    }
    if(first_y>starty2){
        sabet=first_y;
        first_y=starty2;
        starty2=sabet;
        sabet=first_x;
        first_x=startx2;
        startx2=sabet;
    }
    if(first_y==starty2 && first_x > startx2){
        sabet=first_x;
        first_x=startx2;
        startx2=sabet;
    }
    attron(COLOR_PAIR(4));
    int mahdoode=strlen(neveshte[first_y]);
    if(first_y==starty2)
        mahdoode=startx2;
    for(int i=first_y;i<=starty2;i++){
        for(int j=first_x;j<mahdoode;j++){
            move(i,j+2);
            printw("%c",neveshte[i][j]);
        }
        mahdoode=strlen(neveshte[i+1]);
        if(i+1==starty2)
            mahdoode=startx2;
        first_x=0;
    }
    attroff(COLOR_PAIR(4));
}
void copy2(int first_y,int first_x){
    int sabet;
    int startx2=startx;
    int starty2=starty;
    if(first_y>starty2){
        sabet=first_y;
        first_y=starty2;
        starty2=sabet;
        sabet=first_x;
        first_x=startx2;
        startx2=sabet;
    }
    if(first_y==starty2 && first_x > startx2){
        sabet=first_x;
        first_x=startx2;
        startx2=sabet;
    }
    int mahdoode=strlen(neveshte[first_y]);
    memset(clipboard,'\0',sizeof(clipboard));
    if(first_y==starty2)
        mahdoode=startx2;
    for(int i=first_y;i<=starty2;i++){
        for(int j=first_x;j<mahdoode;j++){
            clipboard[strlen(clipboard)]=neveshte[i][j];
        }
        clipboard[strlen(clipboard)]='\n';
        mahdoode=strlen(neveshte[i+1]);
        if(i+1==starty2)
            mahdoode=startx2;
        first_x=0;
    }
    for(int i=0;vasiat_khat[i];i++){
        move(i,0);
        clrtoeol();    
        mvprintw(i,0,"%d %s",i+1,neveshte[i]);
    }
}
void cut2(int first_y,int first_x){
    int sabet;
    int startx2=startx;
    int starty2=starty;
    if(first_y>starty2){
        sabet=first_y;
        first_y=starty2;
        starty2=sabet;
        sabet=first_x;
        first_x=startx2;
        startx2=sabet;
    }
    if(first_y==starty2 && first_x > startx2){
        sabet=first_x;
        first_x=startx2;
        startx2=sabet;
    }
    int mahdoode=strlen(neveshte[first_y]);
    memset(clipboard,'\0',sizeof(clipboard));
    if(first_y==starty2)
        mahdoode=startx;
    for(int i=first_y;i<=starty2;i++){
        for(int j=first_x;j<mahdoode;j++){
            clipboard[strlen(clipboard)]=neveshte[i][j];
        }
        for(int j=first_x;j<=mahdoode;j++){
            for(int z=first_x;z<=strlen(neveshte[i]);z++)
                neveshte[i][z]=neveshte[i][z+1];
        }
        clipboard[strlen(clipboard)]='\n';
        mahdoode=strlen(neveshte[i+1]);
        if(i+1==starty2)
            mahdoode=startx2;
        first_x=0;
    }
    if(first_y!=starty2){
        for(int j=starty2;vasiat_khat[j]==1;j++){
            strcpy(neveshte[j-starty2+first_y+1],neveshte[j]);
            mahdoode=j;
        }
        for(int i=1;i<first_y-starty2;i++){
            vasiat_khat[mahdoode-i-1]=0;
            memset(neveshte[mahdoode-i-1],'\0',sizeof(neveshte[mahdoode-i-1]));
        }
    }
    for(int i=0;vasiat_khat[i];i++){
        mvprintw(i,0,"%d ",i+1);
        move(i,2);
        clrtoeol();
        mvprintw(i,2,"%s",neveshte[i]);
    }
}
void paste2(){
    int x_matn=startx;
    int y_matn=starty;
    for(int i=0;i<strlen(clipboard);i++){
        if(clipboard[i]!='\n'){
            for(int z=strlen(neveshte[y_matn]);z>x_matn;z--)
                neveshte[y_matn][z]=neveshte[y_matn][z-1];
            neveshte[y_matn][x_matn]=clipboard[i];
        }
        else if(clipboard[i]=='\n'&&i+1!=strlen(clipboard)){
            y_matn++;
            int mahdoode=0;
            for(int i=0;vasiat_khat[i];i++)
                mahdoode=i;
            vasiat_khat[mahdoode+1]=1;
            for(int i=mahdoode;i>=y_matn;i--)
                strcpy(neveshte[i+1],neveshte[i]);
            char sabet[1000];
            strcpy(sabet,neveshte[y_matn]);
            memset(neveshte[y_matn],'\0',sizeof(neveshte[y_matn]));
            strncpy(neveshte[y_matn],neveshte[y_matn-1]+x_matn,strlen(neveshte[y_matn-1])-x_matn);
            strcat(neveshte[y_matn],sabet);
            neveshte[y_matn-1][x_matn]='\0';
            x_matn=-1;
        }
        x_matn++;
    }
    for(int i=0;vasiat_khat[i];i++){
        move(i,0);
        clrtoeol();
        mvprintw(i,0,"%d %s",i+1,neveshte[i]);
    }
}
void change_dir(){
    strrev(command);
    memset(my_file_name,'\0',sizeof(my_file_name));
    for(int i=0;i<strlen(command);i++){
        if(command[i]=='/')
            break;
        my_file_name[i]=command[i];
    }
    strrev(my_file_name);
    strrev(command);
    int a=strlen(command2);
    strcpy(command2,"/home/morteza");
    strncat(command2,command+a+2,strlen(command)-a-strlen(my_file_name)-3);
    mkdir(command2,0777);
    chdir(command2);
}
void auto_indent(){
    FILE* fptr1;
    FILE* fptr2;
    char name_cheker[10000];
    strcpy(name_cheker,"a");
    while(fopen(name_cheker,"r")!=NULL){
        strcat(name_cheker,"a");
    }
    char name[10000];
    strcpy(name,name_cheker);
    while(fopen(name_cheker,"r")!=NULL){
        strcat(name_cheker,"a");
    }
    fptr1=fopen(name,"w");
    fptr2=fopen(name_cheker,"w");
    fputs(neveshte[0],fptr1);
    fclose(fptr1);
    fptr1=fopen(name,"r");
    char c = fgetc(fptr1);
    char c_cheker=' ';
    int tedad_tab=0;
    int tedad_khate=0;
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
            tedad_khate++;
            tedad_tab--;
            for(int j=0;j<4*tedad_tab;j++)
                fputc(' ',fptr2);
        }
        if(c=='{' && c_cheker!=' ' && c_cheker!='{' && c_cheker !='}')
           fputc(' ',fptr2);
        fputc(c, fptr2);
        if(c=='}'&& tedad_tab==0)
            fputc('\n',fptr2);
            tedad_khate++;
        if(c=='{'){
            tedad_tab++;
            fputc('\n',fptr2);
            tedad_khate++;
            for(int j=0;j<4*tedad_tab;j++)
                fputc(' ',fptr2);
        }
        c_cheker=c;
        c = fgetc(fptr1);
    }
    fclose(fptr1);
    fclose(fptr2);
    fptr=fopen(name_cheker,"r");
    memset(neveshte,'\0',sizeof(neveshte));
    memset(vasiat_khat,0,sizeof(vasiat_khat));
    for(int i=0;1;i++){
        for(int j=0;1;j++){
            c=fgetc(fptr);
            if(c=='\n')
                break;
            if(c==EOF)
                break;
            neveshte[i][j]=c;
            vasiat_khat[i]=1;
        }
        if(c==EOF)
            break;
    }
    fclose(fptr);
    remove(name);
    remove(name_cheker);
    file_mode='-';
    startx=0;
    starty=0;
}
void find(){
    memset(mahal_find,0,sizeof(mahal_find));
    attron(COLOR_PAIR(4));
        char *a=&neveshte[0][0];
    for(int i=0;vasiat_khat[i];i++){
        int index=strstr(neveshte[i],command2)-a;
        for(int j=0;j<i;j++)
            index=index-sizeof(neveshte[j]);
        mahal_find[i][index]=1;
        for(int j=0;j<strlen(command2);j++){
            int z=j+index;
            mvprintw(i,z+2,"%c",neveshte[i][z]);
        }

    }
    attroff(COLOR_PAIR(4));
    int flag=0;
    while((ch = getch()) != KEY_F(1)){
        flag=0;
        move(starty,startx);
        switch(ch){
            case 'n':
                for(int i=starty;vasiat_khat[i];i++){
                    for(int j=0;j<strlen(neveshte[i]);j++){
                        if(mahal_find[i][j]==1){
                            starty=i+2;
                            startx=j+2;
                            flag=1;
                            break;
                        }
                    }
                    if(flag)
                        break;
                }
                break;
            default:
                normal_mode();
                break;
        }
        if(!flag){
            for(int i=0;vasiat_khat[i];i++){
                for(int j=0;j<strlen(neveshte[i]);j++){
                    if(mahal_find[i][j]==1){
                        starty=i;
                        startx=j+2;
                        flag=1;
                        break;
                    }
                }
                if(flag)
                    break;
            }
        }
    }
}
void command_checker(){
    move(height,0);
    clrtoeol();
    if(command[0]=='/'){
        memset(command2,'\0',sizeof(command2));
        strncpy(command2,command+1,strlen(command)-1);
        find();
    }
    else {
        for(int i=1;i<strlen(command);i++){
            if(command[i]==' '||command[i]=='\0')
                break;
            command2[i-1]=command[i];
        }
        if(!strcmp(command2,"save")){
            if(!strcmp(my_file_name,"esmi entekhab nakardeid"))
                mvprintw(height,0,"your file does not have a name yet");
            else{
                file_mode= '+';
                mvprintw(height-2,0,"%s ||  %s  %c",my_mode,my_file_name,file_mode);
                fptr=fopen(my_file_name,"w");
                for(int i=0;vasiat_khat[i];i++)
                    fprintf(fptr,"%s\n",neveshte[i]);
                fclose(fptr);
            }
        }
        else if(!strcmp(command2,"saveas")){
            file_mode='+';
            change_dir();
            fptr=fopen(my_file_name,"w");
            for(int i=0;vasiat_khat[i];i++)
                fprintf(fptr,"%s\n",neveshte[i]);
            fclose(fptr);
        }
        else if(!strcmp(command2,"open")){
            if(strcmp(my_file_name,"esmi entekhab nakardeid")){
                fptr=fopen(my_file_name,"w");
                for(int i=0;vasiat_khat[i];i++)
                    fprintf(fptr,"%s\n",neveshte[i]);
                fclose(fptr);
            }
            for(int i=0;vasiat_khat[i];i++){
                move(i,0);
                clrtoeol();
            }
            memset(neveshte,'\0',sizeof(neveshte));
            memset(vasiat_khat,0,sizeof(vasiat_khat));
            change_dir();
            if(fopen(my_file_name,"r")==NULL){
                fptr=fopen(my_file_name,"w");
                file_mode='-';
                fclose(fptr);
            }        
            else{
                fptr=fopen(my_file_name,"r");
                for(int i=0;1;i++){
                    if(feof(fptr))
                        break;
                    fgets(neveshte[i],width,fptr);
                    vasiat_khat[i]=1;
                }
                fclose(fptr);
                file_mode='+';
            }
        }
        else if(!strcmp(command2,"undo")){

        }
        else if(!strcmp(command2,"replace")){

        }
        else if(!strcmp(command2,"auto_indent")){
            if(strcmp(command,":auto_indent"))
                change_dir();
            auto_indent();
        }
        else{
            mvprintw(height,0,"invalid command");
        }
    }
    move(height-2,0);
    clrtoeol();
    mvprintw(height-2,0,"%s ||  %s  %c",my_mode,my_file_name,file_mode);
    memset(command,'\0',sizeof(command));
    memset(command2,'\0',sizeof(command));
    startx=0;
    starty=0;
    mahal(0,0);
    normal_mode();
}
void bar_command(){
    starty=height,
    startx=1;
    command[0]=(char)ch;
    while((ch = getch()) != KEY_F(1)){
        switch(ch){
            case KEY_LEFT:
                --startx;
                break;
            case KEY_RIGHT:
                ++startx;
                break;
            case KEY_UP:
                break;
            case KEY_DOWN:
                break;
            case '\n':
                command_checker();
                break;
            case KEY_BACKSPACE:
                for(int i=startx-1;i<strlen(command);i++)
                    command[i]=command[i+1];
                --startx;
                break;
            case 27:
                strcpy(my_mode,"normal");
                mvprintw(height-2,0,"%s ||  %s  %c",my_mode,my_file_name,file_mode);
                startx=0;
                starty=0;
                memset(command,'\0',sizeof(command));
                move(height,0);
                clrtoeol();
                mahal(starty,startx);
                normal_mode();
                break;
            default:
                for(int i=strlen(command)+1;i>startx;i--)
                    command[i]=command[i-1];
                command[startx]=(char)ch;
                startx++;
                break;
        }
        move(height,0);
        clrtoeol();
        mvprintw(height,0,"%s",command);
        mahal(starty,startx);
        refresh();
    }
}
void mahal(int a,int b){
    if(b<=1)
        startx=1;
    if(a<=0){
        starty=0;
        a=0;
    }
    if(vasiat_khat[a]==0&&a>0 && a!=height){
            starty--;
            a--;
    }
    if(b>=strlen(neveshte[a])&&a!=height)
        startx= strlen(neveshte[a]);
    if(b>=strlen(command)&&a==height)
        startx= strlen(command);
    if(ch==KEY_DOWN && vasiat_khat[a+2] &&! vasiat_khat[a+3]){
        char end_line[width];
        strcpy(end_line,neveshte[a+2]);
        for(int i=0;vasiat_khat[i+1];i++)
            strcpy(neveshte[i+1],neveshte[i]);
        strcpy(neveshte[0],end_line);
    }
    if(ch==KEY_UP && a==2){
        char first_line[width];
        strcpy(first_line,neveshte[0]);
        int end;
        for(int i=0;vasiat_khat[i+1];i++){
            strcpy(neveshte[i],neveshte[i+1]);
            end=i;
        }
        strcpy(neveshte[end+1],first_line);
    }
    int d=1;
    if(height==a)
        d=0;
    move(starty,startx+d);
}
void normal_mode(){
    for(int i=0;vasiat_khat[i];i++){
            mvprintw(i,0,"%d ",i+1);
            move(i,2);
            clrtoeol();
            mvprintw(i,2,"%s",neveshte[i]);
    }
    while((ch = getch()) != KEY_F(1)){
        switch(ch){
            case KEY_LEFT:
                --startx;
                break;
            case KEY_RIGHT:
                ++startx;
                break;
            case KEY_UP:
                --starty;
                break;
            case KEY_DOWN:
                ++starty;
                break;    
            case 47:
                mvprintw(height,0,"/");
                bar_command();
                break;
            case ':':
                mvprintw(height,0,":");
                bar_command();
                break;
            case 'v':
                strcpy(my_mode,"visual");
                mvprintw(height-2,0,"%s ||  %s  %c",my_mode,my_file_name,file_mode);
                mahal(starty,startx);
                visual_mode();
                break;
            case 'p':
                paste2();
                break;
            case '=':
                auto_indent();
                break;
            default:
                strcpy(my_mode,"insert");
                mvprintw(height-2,0,"%s ||  %s  %c",my_mode,my_file_name,file_mode);
                mahal(starty,startx);
                insert_mode();
                break;
        }
        for(int i=0;vasiat_khat[i];i++){
            mvprintw(i,0,"%d ",i+1);
            move(i,2);
            clrtoeol();
            mvprintw(i,2,"%s",neveshte[i]);
        }
        mvprintw(height-2,0,"%s ||  %s  %c",my_mode,my_file_name,file_mode);
        mahal(starty,startx);
    }
}
void insert_mode(){
    while((ch = getch()) != KEY_F(1)){
        switch(ch){
            case KEY_LEFT:
                --startx;
                break;
            case KEY_RIGHT:
                ++startx;
                break;
            case KEY_UP:
                --starty;
                break;
            case KEY_DOWN:
                ++starty;
                break;
            case '\n':
                int tedad_khate;
                for(int i=0;i<=height;i++){
                    if(vasiat_khat[i]==0){
                        vasiat_khat[i]=1;
                        tedad_khate=i-1;
                        break;
                    }
                }
                for(int i=tedad_khate;i>starty;i--){
                    strcpy(neveshte[i+1],neveshte[i]);
                }
                memset(neveshte[starty+1],'\0',sizeof(neveshte[starty+1]));
                strncpy(neveshte[starty+1],neveshte[starty]+startx,strlen(neveshte[starty])-startx);
                for(int i=startx;i<strlen(neveshte[starty]);i++)
                    neveshte[starty][i]='\0';
                file_mode='-';
                startx=0;
                starty++;
                break;
            case KEY_BACKSPACE:
                for(int i=startx-1;i<strlen(neveshte[starty]);i++)
                    neveshte[starty][i]=neveshte[starty][i+1];
                if(startx==0&&starty!=0){
                    startx=strlen(neveshte[starty-1]);
                    strcat(neveshte[starty-1],neveshte[starty]);
                    for(int i=starty;vasiat_khat[i]!=0;i++){
                        if(vasiat_khat[i]==0){
                            vasiat_khat[i-1]=0;
                            break;
                        }
                        strcpy(neveshte[i],neveshte[i+1]);                
                    }
                    starty--;
                    startx++;
                }
                file_mode='-';
                --startx;
                break;
            case 27:
                strcpy(my_mode,"normal");
                mvprintw(height-2,0,"%s ||  %s  %c",my_mode,my_file_name,file_mode);
                mahal(starty,startx);
                normal_mode();
                break;
            default:
                for(int i=strlen(neveshte[starty])+1;i>=startx;i--)
                    neveshte[starty][i]=neveshte[starty][i-1];
                neveshte[starty][startx]=(char)ch;
                file_mode='-';
                startx++;
                break;
        }
        for(int i=0;vasiat_khat[i];i++){
            mvprintw(i,0,"%d ",i+1);
            move(i,2);
            clrtoeol();
            mvprintw(i,2,"%s",neveshte[i]);
        }
        move(height,0);
        clrtoeol();
        mvprintw(height-2,0,"%s ||  %s  %c",my_mode,my_file_name,file_mode);
        mahal(starty,startx);
        refresh();
    }
}
void visual_mode(){
    int first_x=startx;
    int first_y=starty;
    while((ch = getch()) != KEY_F(1)){
        switch(ch){
            case KEY_LEFT:
                --startx;
                break;
            case KEY_RIGHT:
                ++startx;
                break;
            case KEY_UP:
                --starty;
                break;
            case KEY_DOWN:
                ++starty;
                break;    
            case 27:
                strcpy(my_mode,"normal");
                mvprintw(height-2,0,"%s ||  %s  %c",my_mode,my_file_name,file_mode);
                for(int i=0;i<height;i++){
                    mvprintw(i,0,"%s",neveshte[i]);    
                }
                mahal(starty,startx);
                normal_mode();
                break;
            case 'x':
                cut2(first_y,first_x);
                strcpy(my_mode,"normal");
                mvprintw(height-2,0,"%s ||  %s  %c",my_mode,my_file_name,file_mode);
                move(0,0);
                normal_mode();
                break;
            case 'y':
                copy2(first_y,first_x);
                strcpy(my_mode,"normal");
                mvprintw(height-2,0,"%s ||  %s  %c",my_mode,my_file_name,file_mode);
                mahal(starty,startx);
                normal_mode();
                break;
            case 'd':
                char clipboard_negahdar[10000];
                strcpy(clipboard_negahdar,clipboard);
                cut2(first_y,first_x);
                strcpy(clipboard,clipboard_negahdar);
                strcpy(my_mode,"normal");
                mvprintw(height-2,0,"%s ||  %s  %c",my_mode,my_file_name,file_mode);
                move(0,0);
                normal_mode();
                break;
            default:
                break;
        }
        choose_matn(first_y,first_x);    
        mahal(starty,startx);
    }
}
int main(){
    file_mode='-';
    memset(vasiat_khat,0,sizeof(vasiat_khat));    
    memset(neveshte,'\0',sizeof(neveshte));
    vasiat_khat[0]=1;
    WINDOW *my_win;
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    start_color();
    init_pair(4,COLOR_BLACK,COLOR_BLUE);
    strcpy(my_file_name,"esmi entekhab nakardeid");
    strcpy(my_mode,"normal");
    my_win = newwin(height, width, starty, startx);
    noecho();
    for(int i=0;i<=width;i++){
        mvprintw(height-3,i,"-");
    }
    mvprintw(height-2,0,"%s ||  %s  %c",my_mode,my_file_name,file_mode);
    for(int i=0;i<=width;i++){
        mvprintw(height-1,i,"-");
    }
    move(0,0);
    normal_mode();
    refresh();
    endwin();
}