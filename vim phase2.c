#include <ncurses.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
int startx=0, starty=0, width=150, height=40,ch;
char my_file_name[1000];
char my_mode[1000];
char clipboard[10000];
char neveshte [40][150];
char file_mode;
void normal_mode();
void insert_mode();
void visual_mode();
int vasiat_khat[40];
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
        mahdoode=startx2;
    for(int i=first_y;i<=starty2;i++){
        for(int j=first_x;j<mahdoode;j++){
            move(i,j);
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
    for(int j=starty2;vasiat_khat[j]==1;j++){
        strcpy(neveshte[j-starty2+first_y+1],neveshte[j]);
        mahdoode=j;
    }
    for(int i=1;i<first_y-starty2;i++){
        vasiat_khat[mahdoode-i-1]=0;
        memset(neveshte[mahdoode-i-1],'\0',sizeof(neveshte[mahdoode-i-1]));
    }
    for(int i=0;i<height-5;i++){
        move(i,0);
        clrtoeol();
        printw("%s",neveshte[i]);
    }
}
void mahal(int starty,int startx){
//    if(startx<=0)
//        startx=0;
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
                move(height,0);
                break;
            case ':':
                move(height,0);
                break;
            case 'v':
                strcpy(my_mode,"visual");
                mvprintw(height-2,0,"%s ||  %s  %c",my_mode,my_file_name,file_mode);
                mahal(starty,startx);
                visual_mode();
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
    strcpy(my_file_name,"untitledfile");
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
