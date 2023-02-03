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
void normal_mode();
void insert_mode();
void visual_mode();
FILE *fptr;
void mahal(int starty,int startx);
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
    for(int i=0;i<height-5;i++){
        mvprintw(i,0,"%s",neveshte[i]);    
    }
    start_color();
    init_pair(1,COLOR_BLACK,COLOR_BLUE);
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
    attron(COLOR_PAIR(1));
    int mahdoode=strlen(neveshte[first_y]);
    if(first_y==starty2)
        mahdoode=startx2;
    for(int i=first_y;i<=starty2;i++){
        for(int j=first_x;j<mahdoode;j++){
            move(i,j);
            printw("%c",neveshte[i][j]);
        }
        mahdoode=strlen(neveshte[i+1]);
        if(i+1==starty2)
            mahdoode=startx2;
        first_x=0;
    }
    attroff(COLOR_PAIR(1));
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
            move(i,j);
            printw("%c",neveshte[i][j]);
            clipboard[strlen(clipboard)]=neveshte[i][j];
        }
        clipboard[strlen(clipboard)]='\n';
        mahdoode=strlen(neveshte[i+1]);
        if(i+1==starty2)
            mahdoode=startx2;
        first_x=0;
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
        for(int j=first_x;j<mahdoode;j++){
            for(int z=first_x;z<strlen(neveshte[i]);z++)
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
        move(i,0);
        clrtoeol();
        mvprintw(i,0,"%s",neveshte[i]);
    }
}
void paste2(){
    int x_matn=startx;
    int y_matn=starty;
    for(int i=0;i<strlen(clipboard);i++){
        if(!(i+1==strlen(clipboard) || clipboard[i]=='\n')){
            for(int z=strlen(neveshte[y_matn]);z>x_matn;z--)
                neveshte[y_matn][z]=neveshte[y_matn][z-1];
            neveshte[y_matn][x_matn]=clipboard[i];
        }
        if(clipboard[i]=='\n'&&i+1!=strlen(clipboard)){
            y_matn++;
            int mahdoode=0;
            for(int i=0;vasiat_khat[i];i++)
                mahdoode++;
            vasiat_khat[mahdoode+1]=1;
            for(int i=mahdoode;i>=y_matn;i--)
                strcpy(neveshte[i+1],neveshte[i]);
            strncpy(neveshte[y_matn],neveshte[y_matn-1]+x_matn,strlen(neveshte[y_matn-1])-x_matn);
            neveshte[y_matn-1][x_matn]='\0';
            x_matn=-1;
            mvprintw(10,20,"%c",neveshte[y_matn][0]);
        }
        x_matn++;
    }
    for(int i=0;vasiat_khat[i]!=0;i++){
        move(i,0);
        clrtoeol();
        mvprintw(i,0,"%s",neveshte[i]);
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
void command_checker(){
    move(height,0);
    clrtoeol();
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
        change_dir();
        fptr=fopen(my_file_name,"w");
        for(int i=0;vasiat_khat[i];i++)
            fprintf(fptr,"%s\n",neveshte[i]);
        fclose(fptr);
    }
    else if(!strcmp(command2,"open")){

    }
    else if(!strcmp(command2,"undo2")){

    }
    else if(!strcmp(command2,"find2")){

    }
    else if(!strcmp(command2,"replace2")){

    }
    else if(!strcmp(command2,"auto_indendt2")){

    }
    else{
        mvprintw(height,0,"invalid command");
    }
    move(height,0);
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
    command[0]=':';
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
                move(height,0);
                clrtoeol();
                mvprintw(height,0,"%s",command);
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
                move(height,0);
                clrtoeol();
                mvprintw(height,0,"%s",command);
                startx++;
                break;
        }
        mahal(starty,startx);
        refresh();
    }
}
void mahal(int starty,int startx){
//    if(startx<=0)
//        startx=0;p
//    if(starty<=0)
//        starty=0;
//    if(startx>=strlen(neveshte[starty]))
//        startx= strlen(neveshte[starty]);
//    if(vasiat_khat[starty]==0){
        
//    }
    move(starty,startx);
}
void normal_mode(){
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
                mvprintw(height,0,":");
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
            default:
                strcpy(my_mode,"insert");
                mvprintw(height-2,0,"%s ||  %s  %c",my_mode,my_file_name,file_mode);
                mahal(starty,startx);
                insert_mode();
                break;
        }
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
                for(int i=starty;i<=tedad_khate+1;i++){
                    move(i,0);
                    clrtoeol();
                    mvprintw(i,0,"%s",neveshte[i]);
                }
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
                for(int i=0;vasiat_khat[i]!=0;i++){
                    move(i,0);
                    clrtoeol();
                    mvprintw(i,0,"%s",neveshte[i]);
                }
                --startx;
                break;
            case 27:
                strcpy(my_mode,"normal");
                mvprintw(height-2,0,"%s ||  %s  %c",my_mode,my_file_name,file_mode);
                mahal(starty,startx);
                normal_mode();
                break;
            default:
                for(int i=strlen(neveshte[starty])+1;i>startx;i--)
                    neveshte[starty][i]=neveshte[starty][i-1];
                neveshte[starty][startx]=(char)ch;
                //move(starty,0);
                for(int i=0;vasiat_khat[i]!=0;i++){
                    move(i,0);
                    clrtoeol();
                    mvprintw(i,0,"%s",neveshte[i]);
                }
                startx++;
                break;
        }
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
                for(int i=0;i<height;i++){
                    mvprintw(i,0,"%s",neveshte[i]);    
                }
                move(0,0);
                normal_mode();
                break;
            case 'y':
                copy2(first_y,first_x);
                strcpy(my_mode,"normal");
                mvprintw(height-2,0,"%s ||  %s  %c",my_mode,my_file_name,file_mode);
                for(int i=0;i<height;i++){
                    mvprintw(i,0,"%s",neveshte[i]);    
                }
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
                for(int i=0;i<height;i++){
                    mvprintw(i,0,"%s",neveshte[i]);    
                }
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
    vasiat_khat[0]=1;
    WINDOW *my_win;
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
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