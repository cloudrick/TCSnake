
// Written by Rick-Yang 2000/05/03
// Snake V2.9

#include<iostream.h>
#include<conio.h>
#include<dos.h>
#include<stdlib.h>
#include<bios.h>

int x,y ;
int ax,ay ;
int tx,ty ;
int stop = 0 ;

const MAXX=80 ;
const MAXY=25 ;

struct pro1{
        int body[512] ;
        int last ;
        int gold ;
        int s ;
        int g ;
        int lives;
        char h ;
}snake ;

union {
        int key ;
        char ch[2] ;
}var ;

int r_xy(int rx,int ry)
{
        return(rx*100+ry) ;
}

int r_x_y(int xy,int c)
{
        switch(c){
        case 0 : return(xy/100) ;
        case 1 : return(xy%100) ;
        }
        return 0 ;
}

void ex()
{
        textcolor(WHITE) ;
        textbackground(BLACK) ;
        clrscr() ;
        cout << "You get " << snake.g << endl ;
        cout << "Programer : Rick-Yang \n" ;
        cout << "E-Mail  : rick.yang@msa.hinet.net \n" ;
        cout << "Date    : 2000/05/03\n" ;
        cout << "Ver     : 2.9 " ;
        cout << "\nBye-Bye!\n" ;
        exit(0) ;
}

int rnd_gold()
{
        int a,b,c ;
        randomize() ;
        while(1){
                a = random(MAXX-10) + 3 ;
                b = random(MAXY-10) + 3 ;
                if(a%2) a+=1 ;
                c = r_xy(a,b) ;
                for(int i=0;i<=snake.last;i++){
                        if(c==snake.body[i])
                            break ;
                }
                if(i==snake.last + 1)
                        return(c) ;
        }
}

void print_gold()
{
        int px,py ;
        px = r_x_y(snake.gold,0) ;
        py = r_x_y(snake.gold,1) ;
        gotoxy(23,1) ;
        cout << snake.g ;
        gotoxy(px,py) ;
        cout << "*" ;
}

void reset()
{
        if(stop==0){
                snake.h = '>' ;
                ax = 2 ;
                ay = 0 ;
                x = MAXX/2 ;
                y = MAXY/2 ;
                snake.last = 2 ;
                snake.gold = 4005 ;
                snake.s = 200 ;
        }
        window(1,1,80,25) ;
        textcolor(WHITE) ;
        textbackground(BLUE) ;
        clrscr() ;
        print_gold() ;
        gotoxy(15,1) ;
        cout << "You get " ;
        gotoxy(29,1) ;
        cout << "now" ;
        gotoxy(37,1);
        cout << "Lives:" << snake.lives ;
        window(55,1,80,1);
        cout << "Press P to PAUSE";
        window(1,1,80,25);
        for(int ix=1 ;ix<=79;ix++){
                gotoxy(ix,2) ;
                cout << char(219) ;
                gotoxy(ix,MAXY) ;
                cout << char(219) ;
        }
        for(int iy=3 ;iy<=25;iy++){
                gotoxy(1,iy) ;
                cout << char(219) ;
                gotoxy(MAXX-1,iy) ;
                cout << char(219) ;
        }
}

void if_continue()
{
        window(1,1,80,25) ;
        textbackground(BLUE) ;
        char ans ;
        do{
                textcolor(YELLOW);
                clrscr() ;
                gotoxy(30,12) ;
                cout << "Continue(y/n) ? " ;
                ans = getch() ;
                if(ans=='N' || ans=='n')
                        ex() ;
    }while(ans!='Y' && ans!='y' && ans!='N' && ans!='n') ;
        snake.lives = 3 ;
        snake.g = 0 ;
        reset() ;
}

void life_down()
{
        if(snake.lives==1)
                if_continue() ;
        else{
                snake.lives-- ;
                reset() ;
        }
}

void check_if_body()
{
        for(int q=2;q<=snake.last;q++){
                if(snake.body[0]==snake.body[q] && snake.body[0]!=snake.gold)
                        life_down() ;
        }
}

void main()
{
        snake.lives=3;
        textbackground(BLUE) ;
        textcolor(WHITE);
        reset();
        window(33,12,45,14) ;
        gotoxy(4,1) ;
        cout << "Ready.." ;
        gotoxy(6,2) ;
        for(tx=3;tx;tx--){
                cout << tx ;
                delay(1000);
                gotoxy(6,2) ;
        }
        cout << "Go!" ;
        delay(500) ;
        reset();
        while(1){
                snake.body[0] = r_xy(x,y) ;
                gotoxy(x,y) ;
                cout << snake.h ;
                delay(snake.s) ;
                for(int j=snake.last;j>=1;j--){
                        snake.body[j] = snake.body[j-1] ;
                        tx = r_x_y(snake.body[j],0) ;
                        ty = r_x_y(snake.body[j],1) ;
                        gotoxy(tx,ty) ;
                        cout << "o" ;
                }
                tx=r_x_y(snake.body[snake.last],0) ;
                ty=r_x_y(snake.body[snake.last],1) ;
                gotoxy(tx,ty) ;
                cout << " " ;
                if(bioskey(1)){
                        var.key = bioskey(0);
                        switch(var.ch[0]){
                        case 27 :
                                if_continue() ; break ;
                        case 80 :
                        case 112 :
                                int oax,oay ;
                                window(26,13,55,14) ;
                                textbackground(BLACK) ;
                                clrscr() ;
                                window(25,12,54,13) ;
                                textcolor(YELLOW) ;
                                textbackground(RED) ;
                                clrscr() ;
                                gotoxy(10,1) ;
                                cout << " PAUSING...." ;
                                gotoxy(5,2) ;
                                cout << "press \"P\" to continue.." ;
                                oax=ax;
                                oay=ay;
                                ax = 0 ;
                                ay = 0 ;
                                stop = 1 ;
                                do{
                                        var.key = bioskey(0);
                                        switch(var.ch[0]){
                                        case 80 :
                                        case 112 :
                                                ax = oax ;
                                                ay = oay ;
                                                reset() ;
                                                stop = 0 ;
                                                break;
                                        case 27 :if_continue();
                                        }
                                }while(stop) ;
                                break;
                        case 0 :
                                switch(var.ch[1]){
                            case 72:
                                        if(ay==1)
                                                break ;
                                        ax = 0 ;
                                        ay = -1 ;
                                        snake.h = '^' ;
                                        break ;
                                case 80:
                                        if(ay==-1)
                                                break ;
                                        ax = 0 ;
                                        ay = 1 ;
                                        snake.h = 'v' ;
                                        break ;
                            case 77:
                                        if(ax==-2)
                                                  break ;
                                        ax = 2 ;
                                        ay = 0 ;
                                        snake.h = '>' ;
                                        break ;
                            case 75:
                                        if(ax==2)
                                                  break ;
                                        ax = -2 ;
                                        ay = 0 ;
                                        snake.h = '<' ;
                                        break;
                                }
                        }
                }
                x += ax ;
                y += ay ;
                if(x==0||x==MAXX||y==2||y==MAXY )
                        life_down() ;
                if(snake.body[0]==snake.gold){
                        snake.last++ ;
                        snake.g += 9 ;
                        snake.gold=rnd_gold() ;
                        print_gold() ;
                        if(snake.s>80)
                                snake.s -= 20 ;
                }
                check_if_body() ;
        }
}

