#include <iostream>
#include <graphics.h>
#include <cstring>
#define max_children 100
#include<cmath>
#include "syntax_checking.h"
using namespace std;

char buffer[250];

struct node{ //david
    node*children[max_children];
    int number_of_children = 0;
    node*parent = NULL;
    char text[150];
    int type = -1; ///-1 = ROOT/ 0 = ATRIBUIRE/ 1 = IF/ 2 = WHILE/ 3 = FOR/ 4 = DO WHILE/ 5 = SWITCH/6 = BREAK/7 = ELSE
    int offset = 0;
    bool visited = false;
    int ind;
    char condexec[150];
    int indch;
    node*partner = NULL;//nod partener pentru gasirea perechii
    int isclicked;
};

struct sentence_matrix{ //david
    int offs;
    char instr[200];
}mat[1000];

int offset(char buffer[]) //david
{
    int i = 0;
    while(!isalnum(buffer[i]))i++;
    return i;
}
#include "graphical_blocks.h"

void initialize_node(node*&t, char content[150], int node_offset, int node_type, int ind) //david
{
    //t = NULL;
//    t->children = new node*[max_children];
//    for(int i= 1; i <= 100; i++)
//            t->children[i] = new node;
    strcpy(t->text,content);
    t->offset = node_offset;
    t->type = node_type;
    t->number_of_children = 0;
    t->parent = NULL;
    //t->children[1]= NULL;
    t->visited = false;
    t->ind = ind;
    strcpy(t->condexec, "-1");
    t->indch = 0;
    t->isclicked = -1;
}
void read_code(int&nofsentences) //david
{
    FILE*fis;
    fis = fopen("input.txt", "r");
    nofsentences = 0;
    if (fis == NULL) perror ("Error opening file");
    else
    {
        while(!feof(fis))
        {
            fgets(buffer, 250, fis);
            nofsentences++;
            strcpy(mat[nofsentences].instr, buffer);
            mat[nofsentences].offs = offset(buffer);
        }
    }
}
//debug
void print_node(node*t) //david
{
    if(t->parent!=NULL)
    cout << "parinte: " << t->parent -> ind << " | ";
    cout << "type: " << t -> type << " | ";
    cout << "ind: " << t->ind << " | ";
    cout << "indch: " << t->indch << " | ";
    cout << "text: " << t->text<<endl;
}

void afisare(node*t) //david
{
    print_node(t);
//    if(t->parent != NULL)
//    {
//        cout << "parinte: " << t->parent->ind << " | ";
//    }
    if(t->children[1]!=NULL)
    {
        for(int i = 1; i <= t->number_of_children; ++i)
            afisare(t->children[i]);
    }
}

bool iswhile(node*root) //david
{
    return(strstr(root->text, "cat timp executa"));
}

bool isdowhile(node*root) //david
{
    return(strstr(root->text, "executa") or strstr(root->text, "repeta"));
}

void desenare3(node*t, int x, int&y, int w, int xm, int ym) //david
{
    //trece prin fiecare instructiune, ii calculeaza coordonatele grafice si o deseneaza
    int yinit = y;
    int ycopy;
    for(int i = 1; i <= t->number_of_children; i++)
    {
        node*current=t->children[i];
        switch(current->type)
        {
        case 0:
            {
                if((xm > x and xm < x+w) and (ym > y and ym < y + defaultheight))
                    current->isclicked*=-1, xm = -1, ym = -1, desenare3(current->parent, x, yinit, w,xm, ym);
                drawAtrib(current, current->text, x, x+w, y);
                y+=defaultheight;
                break;
            }
        case 1:
            {
                if((xm > x and xm < x+w) and (ym > y and ym < y + defaultheight))
                    current->isclicked*=-1, xm = -1, ym = -1, desenare3(current->parent, x, yinit, w,xm, ym);
                char cond[150];
                int lenif = strlen("daca "), lenthen = strlen(" atunci");
                int len = strlen(current->text)-lenif - lenthen -offset(current->text);
                strncpy(cond, strstr(current->text, "daca")+lenif, len);
                cond[len] = NULL;
                int ystart = y;
                y+=defaultheight;
                ycopy = y;
                int wcopy = w;
                desenare3(current, x, y, w/2, xm, ym);
                if(current->indch < t->number_of_children and t->children[i+1]->type == 7)
                   /*t->children[i+1]->isclicked = current->isclicked, */desenare3(t->children[i+1], x+w/2, ycopy, w/2, xm, ym);
                y = max(y, ycopy);
                drawIf(current, cond, x, x+w, ystart, y);
                break;
            }
        case 2:
            {
                ycopy = y;
                y+=defaultheight;
                desenare3(current, x+25, y, w-25, xm, ym);
                if(((xm > x and xm < x+w) and (ym > ycopy and ym < ycopy + defaultheight)) or ((xm > x and xm < x+25) and (ym > ycopy + defaultheight and ym < y)))
                    current->isclicked*=-1, xm = -1, ym = -1, desenare3(current->parent, x, yinit, w,xm, ym);
                drawWhile(current, current->text, x, x+w, ycopy, y);
                break;
            }
        case 3:
            {
                ycopy = y;
                y+=defaultheight;
               desenare3(current, x+25, y, w-25, xm, ym);
                if(((xm > x and xm < x+w) and (ym > ycopy and ym < ycopy + defaultheight)) or ((xm > x and xm < x+25) and (ym > ycopy + defaultheight and ym < y)))
                    current->isclicked*=-1, xm = -1, ym = -1, desenare3(current->parent, x, yinit, w,xm, ym);
                drawFor(current, current->text, x, x+w, ycopy, y);
                break;
            }
        case 4:
            {
                //left+float(i-1)*w/n, yend, left+float(i-1)*w/n, ystart + float(i-1)*float(defaultheight)/n
                if(isdowhile(current))
                {
                    ycopy = y;
                    desenare3(current, x+25, y, w-25, xm, ym);
                    //y+=(getdepth(current)+1)*50;
                    if(((xm > x and xm < x+25) and (ym > ycopy and ym < y)) or ((xm > x and xm < x+w) and (ym > y and ym < y+ defaultheight)))
                        current->isclicked*=-1, /*t->children[current->indch+1]->isclicked = current->isclicked*/xm = -1, ym = -1, desenare3(current->parent, x, yinit, w,xm, ym);
                    drawDoWhile(current, current->condexec, x, x+w, ycopy, y);
                    y+=defaultheight;
                }
                break;
            }
        case 5:
            {
                if((xm > x and xm < x+w) and (ym > y and ym < y + defaultheight))
                    current->isclicked*=-1, xm = -1, ym = -1, desenare3(current->parent, x, yinit, w,xm, ym);
                int n = current->number_of_children;
                ycopy = y;
                int ymax = y;
                y+=defaultheight;
                int ycopy2 = y;
                int xcopy = x;
                //cout << n;
                for(int i = 1; i <= n; ++i)
                {
                        //cout << xcopy << endl;
                        desenare3(current->children[i], x+float(i-1)*w/n, ycopy2, w/n, xm ,ym);
                        xcopy+=w/n;
                        //cout << ycopy2<<endl;
                        if(ycopy2 > ymax)ymax = ycopy2;
                        ycopy2 = y;
                }
                char txt[100];
                strcpy(txt, current->text + offset(current->text) + strlen("switch("));
                txt[strlen(txt)-2] = NULL;
                drawSwitch(txt, x, x+w, ycopy ,ymax, n, current);
                y = ymax;
                //cout << ycopy << " " << ymax << " " << n << endl;
                break;
            }
        }
    }
}
void settype(node*&t) //david
{
    //CHECK FOR IF
    if(strstr(t->text+t->offset, "daca"))
        t->type = 1;
    //CHECK FOR ELSE
    else if(strstr(t->text+t->offset, "altfel"))
    {
        t->type = 7;
        t->ind = t->parent->children[t->indch-1]->ind;
        //t->partner = t->parent->children[t->indch-1];
    }
    //CHECK FO DO WHILE
    else if((strstr(t->text+t->offset, "cat timp") and !strstr(t->text+t->offset, "executa")) or strstr(t->text+t->offset, "pana cand"))
    {
        t->type = 4;
        t->ind = t->parent->children[t->indch-1]->ind;
        t->parent->children[t->indch-1]->type = 4;
        strcpy(t->parent->children[t->indch-1]->condexec, t->text);
    }
    //CHECK FOR FOR
    else if(strstr(t->text+t->offset,"pentru"))
    {
        t-> type = 3;
    }
    //CHECK FOR WHILE
    else if(strstr(t->text+t->offset,"cat timp") and strstr(t->text+t->offset,"executa"))
    {
        t->type = 2;
    }
    //CHECK FOR SWITCH
    else if(strstr(t->text+t->offset,"switch"))
    {
        t->type = 5;
    }
    else if(strstr(t->text+t->offset,"break"))
        t->type = 6;
    //CHECK FOR ASSIGNATION
    else t->type = 0;
}
void build_forest(int number_of_nodes, node*root) //david
{
    //functia cauta intr-o stiva parintele instructiunii citite curent, in functie de offset
    node*stak[number_of_nodes];
    int lastindex = 0;
    stak[lastindex] = root;
    for(int i = 1; i <= number_of_nodes; ++i)
    {
        node*t = new node;
        initialize_node(t, mat[i].instr, mat[i].offs, 0, i);
        while(lastindex!=0 and stak[lastindex]->offset >= t->offset)
        {
            lastindex--;
        }
        stak[lastindex]->number_of_children++;
        stak[lastindex]->children[stak[lastindex]->number_of_children] = t;
        t->parent = stak[lastindex];
        t->indch = stak[lastindex]->number_of_children;
        settype(t);
        lastindex++;
        stak[lastindex] = t;
    }
}

void drawscrollbutton() //maria
{
    setcolor(BLACK);
    setfillstyle(SOLID_FILL,COLOR(255, 182, 193)); //roz
    //settextstyle(3, HORIZ_DIR, 3);
    setbkcolor(COLOR(255, 182, 193));
    int i;
    for (i=1; i<=3; i++)
    {
        Buton[i].D.stangasus.x=DIAGRAM_WIDTH+50;
        Buton[i].D.dreaptajos.x=DIAGRAM_WIDTH+100;
        Buton[i].D.stangasus.y=510+40*(i-1);
        Buton[i].D.dreaptajos.y=510+40*i-10;

        switch(i)
        {
        case 1:
            strcpy(Buton[i].text,"ScrollU");
            break;
        case 2:
            strcpy(Buton[i].text,"ScrollD");
            break;
        case 3:
            strcpy(Buton[i].text, b4[limba]);
            break;
        }
        bar(Buton[i].D.stangasus.x, Buton[i].D.stangasus.y+30, Buton[i].D.dreaptajos.x, Buton[i].D.stangasus.y);
        outtextxy(Buton[i].D.stangasus.x+3,Buton[i].D.stangasus.y,Buton[i].text);
    }
    setcolor(WHITE);
}

void checkDiagramButtons(int xm, int ym, int&y) //maria
{
    //actualizeaza y-ul diagramei in functie de butonul apasat, sau se intoarce la meniul principal
    int comanda=0, butonul_apasat;
    butonul_apasat=butonAles();
    //cout << butonul_apasat<<' ';
    if (butonul_apasat!=0)
    {
        comanda=butonul_apasat;
        if(comanda==1) //SCROLLU
        {
            y+=50;
            return;
        }
        else if(comanda==2) //SCROLLD
        {
            y-=50;
            return;
        }
        else if(comanda==3) //BACK
        {
            apeleazaMeniulPrincipal();
            comanda=5;
        }
    }
}

void draw_diagram(int y) //david
{
    int noofsentences = 0;
    int drawy = y;
    read_code(noofsentences);
    ///initialize arbitrary root
    node*root = new node;
    initialize_node(root,"radacina arborelui", -1, -1, 0);
    ///call build forest function to mark nodes
    build_forest(noofsentences, root);
    //int y = defaultheight;
    //setbkcolor(BLACK);
    setbkcolor(BLACK);
    setlinestyle(0, 0, 3);
    cleardevice();
    setcolor(WHITE);
    int xm = -1, ym = -1;
    desenare3(root, 25, drawy, DIAGRAM_WIDTH, xm, ym);
    drawscrollbutton();
    setbkcolor(BLACK);
    int scrolloffset = 0;
    while(1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            drawy = y+scrolloffset;
            //setcolor(BLACK);
            //getmouseclick(WM_LBUTTONDOWN, xm, ym);
            xm = mousex();
            ym = mousey();
            //cout << xm << " " << ym << endl;
            checkDiagramButtons(xm , ym, scrolloffset);
            setbkcolor(BLACK);
            cleardevice();
            setlinestyle(0, 0, 3);
            desenare3(root, 25, drawy, DIAGRAM_WIDTH, xm, ym);
            drawscrollbutton();
            //cout <<  " | scrolloffset: " << scrolloffset<< endl;
            //afisare(root);
        }
    }
}
void apeleazaMeniulPrincipal() //maria
{
    setbkcolor(COLOR(56, 0, 100)); //mov
    cleardevice();
    deseneazaMeniul();
    int comanda=0, butonul_apasat;
    do
    {
        butonul_apasat=butonAles();
        if (butonul_apasat!=0)
            {
                comanda=butonul_apasat;
                if(comanda==4) //EXIT
                    exit(0);
                else
                    if(comanda==1) //START
                        InsereazaPseudocod();
                else
                    if(comanda==2) //LANGUAGES
                    {
                       meniuLimbi();
                       comanda=5;
                    }
                else
                    if (comanda==3) //DIAGRAM
                    {
                    draw_diagram(defaultheight);
                    }
            }
    }
    while(comanda!=5);
}
void draw_menu()
{
    initwindow(WINDOW_WIDTH,WINDOW_HEIGHT,"Nassi - Shneiderman diagram");
    apeleazaMeniulPrincipal();
    getch();
    closegraph();
}
int main()
{
    draw_menu();
    return 0;
}
