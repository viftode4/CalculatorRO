#include <iostream>
#include<graphics.h>
#include<windows.h>
using namespace std;
void startMenu(short &k)
{
    if(k==0)
        initwindow(1720,1000,"Calculator",true);

    k++;
    short startJoc=0;
    short x,y;
    readimagefile("fundal.jpg",0,0,1720,1000);
    butonmuzica();
    readimagefile("start.jpg",startX,startY,startX+300,startY+50);
    readimagefile("exit.jpg",startX,startY+200,startX+300,startY+250);
    int main()
    {
        startMenu(k);
        closegraph();
    }
}
