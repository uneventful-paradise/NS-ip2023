#include<iostream>
#include<graphics.h>
#include<winbgim.h>
#define bw 600
#define bh 100
#define WINDOW_HEIGHT 1080
#define WINDOW_WIDTH 1620 //1920
#define maxcond 5
#define defaultheight 50
#define DIAGRAM_WIDTH 1150 //1800
#include <cmath>
#define width 1000
#define height 100
//#include <conio.h>
//#include "AsyncScrollDetect.h"
using namespace std;

void getcol(node*t,int&a, int&b, int&c) //david
{
    //determina culoarea instructiunii in functie de state-ul ei(clicked/not clicked)
    if(t->isclicked == 1)
    {
        a = 0, b = 0, c = 150;
        return;
    }
    for(int i = 1; i <= t->number_of_children; ++i)
    {
        if(t->children[i]->isclicked == 1)
        {
            a = 99, b = 3, c = 48;
            return;
        }
        if(t->type == 1 and t->parent->number_of_children > t->indch and t->parent->children[t->indch+1]->type == 7)
        {
            node*q = t->parent->children[t->indch+1];
            for(int i = 1; i <= q->number_of_children; ++i)
                if(q->children[i]->isclicked == 1)
                {
                    a = 99, b = 3, c = 48;
                    return;
                }
        }
        if(t->type == 5)
        {
            for(int i = 1; i <= t->number_of_children; ++i)
            {
                node*q = t->children[i];
                for(int j = 1; j<= q->number_of_children; ++j)
                {
                    if(q->children[j]->isclicked == 1)
                    {
                    a = 99, b = 3, c = 48;
                    return;
                    }
                }
            }
        }
    }
    for(int i = 1; i <= t->parent->number_of_children; ++i)
    {
        if(t->parent->children[i]->isclicked == 1 and i != t->indch )
        {
            a = 0, b = 90, c = 0;
            return;
        }
    }
    switch(t->type)
    {
        //culorile default
        case 0://atribuire
        {
            //a = 196, b = 180, c = 84;
            a = 33, b=212, c=254;
            break;
        }
        case 1://if
        {
            //a = 255, b = 165, c = 0;
            a=254, b=231, c=78;
            break;
        }
        case 2://while
        {
            //a = 64, b = 181, c = 173;
            a=204, b=153, c=255;
            break;
        }
        case 3://for
        {
            //a = 180, b = 196, c = 36;
            a=255, b=178, c=102;
            break;
        }
        case 4://do while
        {
            //a = 144, b = 238, c = 144;
            a=255, b=153,c=204;
            break;
        }
        case 5://switch
        {
            //a = 255, b = 165, c = 0;
            //a=160, b=160, c=160;
            a=120, b=120, c=120;
            break;
        }
    }
}

void drawAtrib(node*t,char s[], int left, int right, int y) //david+maria
{
    int coord[] = {left+1, y+1, right-1, y+1, right-1, y+defaultheight-1, left+1, y+defaultheight-1,left+1, y+1};
    int r, g, b;
    getcol(t,r,g,b);
    setcolor(WHITE);
    //setcolor(COLOR(120, 120, 120));
    //setcolor(COLOR(0, 0, 0));
    //setcolor(COLOR(129, 129, 129));
    setlinestyle(0, 0, 2);
    setfillstyle(SOLID_FILL, COLOR(r, g, b));
    fillpoly(5, coord);
    setbkcolor(COLOR(r, g, b));
    line(left, y, right, y);
    outtextxy((left+right)/2-textwidth(s)/2, y+defaultheight/2-textheight(s)/2, s);
    line (left, y, left, y+defaultheight);
    line(right, y, right, y+defaultheight);
    line(left, y+defaultheight, right, y+defaultheight);

}
void drawIf(node*t, char s[], int left, int right, int ystart, int yend) //david+maria
{
    int coord[] = {left, ystart, right, ystart, (left+right)/2, ystart+defaultheight, left, ystart};
    int r, g, b;
    getcol(t,r,g,b);
    setfillstyle(SOLID_FILL, COLOR(r, g, b));
    //setfillstyle(SOLID_FILL, COLOR(255, 165, 0));
    fillpoly(4, coord);
    setbkcolor(COLOR(r, g, b));

    int coorda[]={left, ystart, left, ystart+defaultheight, (left+right)/2, ystart+defaultheight,left, ystart};
    setfillstyle(SOLID_FILL, COLOR(93,211, 93));
    fillpoly(4, coorda);

    int coordf[]={right, ystart, right, ystart+defaultheight, (left+right)/2, ystart+defaultheight,right, ystart};
    setfillstyle(SOLID_FILL, COLOR(255, 81, 72));
    fillpoly(4, coordf);

    outtextxy((left+right)/2-textwidth(s)/2, ystart/*+defaultheight/2*/+textheight(s)/2, s);
    line(left, ystart, right, ystart);//upper border
    line(left, ystart, (left+right)/2, ystart+defaultheight);//left diagonal
    line((left+right)/2, ystart+defaultheight, right, ystart);//rightdiagonal
    line(left, ystart+defaultheight, right, ystart+defaultheight);
    line (left, ystart, left, yend);//left border
    line(right, ystart, right, yend);//right border;
    line(left, yend, right, yend);

    setcolor(WHITE);
    setbkcolor(COLOR(93,211, 93));
    outtextxy(left + textwidth("A"), ystart+/*textheight("Adevarat")*/ 25, "A");
    setcolor(4);

    setcolor(WHITE);
    setbkcolor(COLOR(255, 81, 72));
    outtextxy(right - textwidth("F")- 5, ystart+25, "F");
    setcolor(15);
}
void drawWhile(node*t, char s[], int left, int right, int ystart, int yend) //david+maria
{
    int r, g, b;
    getcol(t, r, g, b);
    int coord[] = {left, ystart, right, ystart, right, ystart+defaultheight, left+25, ystart+defaultheight, left+25, yend, left, yend,left, ystart};
    setfillstyle(SOLID_FILL, COLOR(r, g, b));
    fillpoly(7, coord);
    setbkcolor(COLOR(r, g, b));
    outtextxy((left+right)/2-textwidth(s)/2, ystart+defaultheight/2-textheight(s)/2, s);
    line (left, ystart, left, yend);
    line(right, ystart, right, ystart+defaultheight);
    line(left+25, ystart+defaultheight, right, ystart+defaultheight);
    line(left+25, ystart+defaultheight, left+25, yend);
    line(left, yend, left+25, yend);
}
void drawFor(node*t, char s[], int left, int right, int ystart, int yend) //david+maria
{
    int r, g, b;
    getcol(t,r,g,b);
    setfillstyle(SOLID_FILL, COLOR(r, g, b));
    int coord[] = {left, ystart, right, ystart, right, ystart+defaultheight, left+25, ystart+defaultheight, left+25, yend, left, yend,left, ystart};
    //setfillstyle(SOLID_FILL, COLOR(180, 196, 36));
    fillpoly(7, coord);
    setbkcolor(COLOR(r, g, b));
    outtextxy((left+right)/2-textwidth(s)/2, ystart+defaultheight/2-textheight(s)/2, s);
    line(left, ystart, right, ystart);
    line(left, ystart, left, yend);///+50??  left border
    line(right, ystart, right, yend); // right border
    line(left+25, ystart+defaultheight, right, ystart+defaultheight);//sub upper border
    line(left+25, ystart+defaultheight, left+25, yend);//inner left border
    line(left, yend, right, yend);//bottom border
    //line(right, y+200, dr, y+250);
    //line(dr, y+250, st, y+250);
    //line(dr, y+50, dr, y+200);//???
}
void drawDoWhile(node*t, char s[], int left, int right, int ystart, int yend) //david+maria
{
    int r, g, b;
    getcol(t, r, g, b);
    int coord[] = {left, ystart, left, yend+defaultheight, right, yend+defaultheight, right, yend, left+25, yend, left+25, ystart,left, ystart};
    setfillstyle(SOLID_FILL, COLOR(r, g, b));
    fillpoly(7, coord);
    setbkcolor(COLOR(r, g, b));
    outtextxy((left+right)/2-textwidth(s)/2, yend+defaultheight/2-textheight(s)/2, s);
    line(left, ystart, left, yend+defaultheight);///outer left border
    line(right, ystart, right, yend+defaultheight);///outer right border
    line(left, ystart, right, ystart);
    line(left+25, yend, right, yend);
    line(left+25, ystart, left+25, yend);
    line(left, yend+defaultheight, right, yend+defaultheight);///line bottom
}

void drawSwitch(char s[], int left, int right, int ystart, int yend, int number_of_instr, node*t) //david+maria
{
    int r, g, b;
    getcol(t,r,g,b);
    setfillstyle(SOLID_FILL, COLOR(r, g, b));
    int coord[] = {left, ystart, right, ystart, right - (right-left)/number_of_instr, ystart+defaultheight, left, ystart};
    //setfillstyle(SOLID_FILL, COLOR(255, 165, 0));
    fillpoly(4, coord);

    int coorda[]={left, ystart, left, ystart+defaultheight, right - (right-left)/number_of_instr, ystart+defaultheight,left, ystart};
    setfillstyle(SOLID_FILL, COLOR(93,211, 93));
    fillpoly(4, coorda);

    int coordf[]={right, ystart, right, ystart+defaultheight, right - (right-left)/number_of_instr, ystart+defaultheight,right, ystart};
    setfillstyle(SOLID_FILL, COLOR(255, 111, 111));
    fillpoly(4, coordf);


    setbkcolor(COLOR(r, g, b));
    outtextxy((left+right)/2-textwidth(s)/2, ystart+5, s);
    line(left, ystart, right, ystart);//upper border
    line(left, ystart, right - (right-left)/number_of_instr, ystart+defaultheight);//left diagonal
    line(right - (right-left)/number_of_instr, ystart+defaultheight, right, ystart);//rightdiagonal
    line(left, ystart+defaultheight, right, ystart+defaultheight);//fillingborder
    int  n = number_of_instr, w = right - (right-left)/n-left;
    n--;
    for(int i = 1; i <= number_of_instr; ++i)
    {
        setbkcolor(COLOR(93,211, 93));
//        line((left+(right-left))/(number_of_instr-i), ystart, (left+(right-left))/(number_of_instr-i), ystart+defaultheight);
        if(i == number_of_instr)
            setbkcolor(COLOR(255, 111, 111));
        char text[10];
        if(strstr(t->children[i] -> text, "case"))
        {
            strcpy(text, t->children[i] -> text + offset(t->children[i] -> text)+ strlen("case"));
            text[strlen(text)-2]=NULL;
        }
        else
            strcpy(text, "default");
        outtextxy(left+float(i-1)*w/n+w/(2*n)-textwidth(text), ystart+defaultheight-textheight(text)-1, text);
        line(left+float(i-1)*w/n, yend, left+float(i-1)*w/n, ystart + float(i-1)*float(defaultheight)/n);
    }
    line(left, ystart, left, yend);//left border
    line(right, ystart, right, yend);//right border;
    line(left, yend, right, yend);
}
//traduce cuvintele cheie in cele 4 limbi
int d=50, e=100;
char b1[4][200] = {"Romana", "Romanian", "Roumain","Rumanisch"};
char b2[4][200]={"Engleza", "English", "Anglais", "Englisch"};
char b3[4][200]={"Franceza", "French", "Francais", "Franzosisch"};
char b4[4][200]={"Inapoi","Back","Retour","Ruckwarts"};
char b5[4][200]={"Alege-ti limba:", "Choose your language:", "Choisissez votre langue:", "Wahlen deine Sprache:"};
char b6[4][200]={"Incepe", "Start", "Debut", "Starten"};
char b7[4][200]={"Diagrama", "Diagram", "Diagramme", "Diagramm"};
char b8[4][200]={"Limbi", "Languages", "Langues", "Sprachen"};
char b9[4][200]={"Iesire", "Exit", "Quitter", "Ausgang"};
//char b10[4][200]={"Scrie pseudocodul aici:", "Write your pseudocode here:", "Ecrivez votre pseudo-code ici:"};
char b11[4][200]={"Alege un fisier", "Choose file", "Choisir le fichier", "Wahlen eine Datei:"};
char b12[4][200]={"Exemple", "Examples", "Exemples", "Beispiele"};
char b13[4][200]={"Germana", "German", "Allemande", "Deutsch"};
//char b14[4][200]={"Schimba input-ul", "Change input", "Modifier l'entrée"}
char b14[4][200]={"Verifica sintaxa", "Syntax checking", "Verification de la syntaxe", "Syntaxprufung"};
int limba=1;
struct punct //maria
{
    int x, y;
};
struct dreptunghi //maria
{
    punct stangasus, dreaptajos; //pt desenarea chenarelor de butoane
};
void apeleazaMeniulPrincipal();

bool apartine(punct P, dreptunghi D) //punctul apartine dreptunghiului //maria
{
    return D.stangasus.x<=P.x && P.x<=D.dreaptajos.x && D.stangasus.y<=P.y && P.y<=D.dreaptajos.y;
}
struct buton //maria
{
    dreptunghi D;
    int culoare;
    char text[20];
};

buton Buton[20]; //maria
int nrButoane=5; //maria

void deseneazaMeniul() //maria
{
    setcolor(WHITE);
    setlinestyle(0, 0, 3);
    rectangle(90,210,getmaxx(),getmaxy());
    setcolor(BLACK);
    setfillstyle(SOLID_FILL,COLOR(220, 170, 200)); //roz
    setbkcolor(COLOR(220, 170, 200));
    //adaug imaginile de prezentare
    readimagefile("color1.jpg", 130, 250, 550, 650);
    readimagefile("color2.jpg", 580, 250, 1000, 650);
    readimagefile("color3.jpg", 1025, 350, 1250, 650);
    readimagefile("titlu.jpg", 750, 30, 1250, 180);
    int i;
    for (i=1; i<=4; i++)
    {
        Buton[i].D.stangasus.x=150*i;
        Buton[i].D.dreaptajos.x=150*(i+1)-20;
        Buton[i].D.stangasus.y=50;
        Buton[i].D.dreaptajos.y=150;
        switch(i)
        {
        case 1:
            strcpy(Buton[i].text,b6[limba]); //START
            break;
        case 2:
            strcpy(Buton[i].text,b8[limba]); //LANGUAGES
            break;
        case 3:
            strcpy(Buton[i].text,b7[limba]); //DIAGRAM
            break;
        case 4:
            strcpy(Buton[i].text,b9[limba]); //EXIT
            break;
        }
        bar(Buton[i].D.stangasus.x, Buton[i].D.stangasus.y+100, Buton[i].D.dreaptajos.x, Buton[i].D.stangasus.y);
        outtextxy(Buton[i].D.stangasus.x+25,Buton[i].D.stangasus.y+40,Buton[i].text);
    }
}

int butonAles() //maria
{
    int i;
    punct p;
    if(ismouseclick(WM_LBUTTONDOWN))
    {
        clearmouseclick(WM_LBUTTONDOWN);
        p.x=mousex();
        p.y=mousey();
        for (i=1; i<=nrButoane; i++)
            if (apartine(p,Buton[i].D)) //daca am dat scroll la noi pe buton
            {
                setfillstyle(1, COLOR(238, 228, 110));
                bar(Buton[i].D.stangasus.x,Buton[i].D.stangasus.y, Buton[i].D.dreaptajos.x, Buton[i].D.dreaptajos.y);
                return i;
            }
    }
    return 0;
}

void InsereazaPseudocod() //maria
{
    setbkcolor(COLOR(0, 0, 90)); //albastru inchis
    cleardevice();
    setcolor(WHITE);
    outtextxy(60, 60, b11[limba]);
    setfillstyle(SOLID_FILL,COLOR(19, 120, 131)); //turcoaz
    setbkcolor(COLOR(19, 120, 131));

    int i;
    for (i=1; i<=4; i++)
    {
        Buton[i].D.stangasus.x=150*i;
        Buton[i].D.dreaptajos.x=150*(i+1)-10;
        Buton[i].D.stangasus.y=250;
        Buton[i].D.dreaptajos.y=330;
        switch(i)
        {
        case 1:
            strcpy(Buton[i].text,b4[limba]); //BACK
            break;
        case 2:
            strcpy(Buton[i].text,"Input"); //INPUT
            break;
        case 3:
            strcpy(Buton[i].text,b12[limba]); //MODELE PSEUDOCOD
            break;
        case 4:
            strcpy(Buton[i].text,b14[limba]); //SYNTAX CHECKING
            break;

        }
        bar(Buton[i].D.stangasus.x, Buton[i].D.stangasus.y+80, Buton[i].D.dreaptajos.x, Buton[i].D.stangasus.y);
        outtextxy(Buton[i].D.stangasus.x+3,Buton[i].D.stangasus.y+25,Buton[i].text);
    }
    int comanda=0, butonul_apasat;
    do
    {
        butonul_apasat=butonAles();
        if (butonul_apasat!=0)
            {
                comanda=butonul_apasat;
                if(comanda==1) //BACK
                   {
                       apeleazaMeniulPrincipal();
                       comanda=5;
                   }
                else
                    if(comanda==2) //INPUT
                    {
                       system("input.txt");//deschidem fisierul cu care lucreaza diagrama
                    }
                else
                    if(comanda==3)
                        system("modele_pseudocod.txt");//fisier cu modele de diagrame
                else
                    if(comanda==4) //SYNTAX CHECKING
                    {
                       result();
                    }
            }
    }
    while(comanda!=5);
}
void schimbaLimba(int x) //maria
{
    //valorile fiecarei limbi
    if(x==0)
        limba=0; //romana
    else if (x==1)
        limba=1; //engleza
    else if (x==2)
        limba=2; //franceza
    else if(x==3)
        limba=3; //germana
}
void meniuLimbi() //maria
{
    setbkcolor(COLOR(0, 0, 90)); //albastru inchis
    cleardevice();
    setcolor(WHITE);
    outtextxy(40, 40, b5[limba]); //ALEGE LIMBA
    setfillstyle(SOLID_FILL,COLOR(19, 120, 131)); //turcoaz
    setbkcolor(COLOR(19, 120, 131));
    int i;
    for (i=1; i<=5; i++)
    {
        Buton[i].D.stangasus.x=150*i;
        Buton[i].D.dreaptajos.x=150*(i+1)-10;
        Buton[i].D.stangasus.y=250;
        Buton[i].D.dreaptajos.y=330;
        switch(i)
        {
        case 1:
            strcpy(Buton[i].text,b1[limba]); //romana
            break;
        case 2:
            strcpy(Buton[i].text,b2[limba]); //franceza
            break;
        case 3:
            strcpy(Buton[i].text,b3[limba]); //engleza
            break;
        case 4:
            strcpy(Buton[i].text, b13[limba]); //germana
            break;
        case 5:
            strcpy(Buton[i].text,b4[limba]); //back
            break;
        }
        bar(Buton[i].D.stangasus.x, Buton[i].D.stangasus.y+80, Buton[i].D.dreaptajos.x, Buton[i].D.stangasus.y);
        outtextxy(Buton[i].D.stangasus.x+25,Buton[i].D.stangasus.y+25,Buton[i].text);
    }
    int comanda=0, butonul_apasat;
    do
    {
        butonul_apasat=butonAles();
        if (butonul_apasat!=0)
            {

                comanda=butonul_apasat;
                //cout<<comanda<<' ';
                if(comanda==1)
                   schimbaLimba(0); //romana
                else
                    if(comanda==2)
                   schimbaLimba(1); //engleza
                else
                    if(comanda==3)
                    schimbaLimba(2); //franceza
                else
                    if(comanda==4)
                    schimbaLimba(3); //germana
                else
                    if(comanda==5) //back
                    {
                        apeleazaMeniulPrincipal();
                        comanda=6;
                    }
            }
    }
    while(comanda!=6);
}
