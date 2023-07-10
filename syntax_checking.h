#include <fstream>
#include <string.h>

using namespace std;
ifstream fin("input.txt");

char text[100],*p, cuv[10][250];
int nr;

int cont_repeta=0, ok=1, cont_altfel=0, cont_executa=0, cont_switch=0, cont_case=0;

bool checkDaca() //maria
{

    if(strcmp(cuv[1], "daca")==0 && strcmp(cuv[nr], "atunci")!=0) //avem daca dar nu avem si atunci
        return 0;
    else
        return 1;
}
int checkAltfel() //maria
{
    if(cont_altfel<0)
    {
        ok=0;    //altfel fara daca
        return -1;
    }
    if(strcmp(cuv[1], "daca")==0) cont_altfel++;
    if(strcmp(cuv[1], "altfel")==0) cont_altfel--;
    return cont_altfel;
    //putem avea daca fara altfel, dar nu si altfel fara daca
    //deci cont_altfel obligatoriu >=0
}
int checkSwitch() //maria
{
    //verificam sa nu avem switch fara case
    if(strcmp(cuv[1], "switch")==0) cont_switch++;
    if(strcmp(cuv[1], "case")==0) cont_case++;
    if(cont_case>=cont_switch) return 1;
    else return 0;
}
int checkRepetaPanaCand() //maria
{
    if(cont_repeta<0)
    {
        ok=0;
        return -1;
    }
    if(strcmp(cuv[1], "repeta")==0) cont_repeta++;
    if(strcmp(cuv[1], "pana")==0 && strcmp(cuv[2], "cand")==0) cont_repeta--;
    return cont_repeta;
}

int checkExecutaCatTimp() //maria
{
    if(cont_executa<0)
    {
        ok=0;
        return -1;
    }
    if(strcmp(cuv[1], "executa")==0) cont_executa++;
    if(strcmp(cuv[1], "cat")==0 && strcmp(cuv[2], "timp")==0 && strcmp(cuv[nr], "executa")!=0) cont_executa--;  //verificam daca este Executa...Cat timp, si nu Cat timp ... executa
    return cont_executa;
}
int checkPentru() //maria
{
    if(strcmp(cuv[1], "pentru")==0 && strcmp(cuv[nr], "executa")!=0)
        return 0;
    else
        return 1;
}
int checkCatTimpExecuta() //maria
{
    if(strcmp(cuv[1], "cat")==0 && strcmp(cuv[2], "timp")==0 && strcmp(cuv[nr], "executa")!=0)
        return 0; //avem cat timp dar nu avem executa
    else
        return 1;
}
void result() //maria
{
    while(fin.getline(text, 100))
    {
        nr=0;
        p=strtok(text, " ");
        while(p!=NULL)
        {
            strcpy(cuv[++nr],p);
            p=strtok(NULL," ");
        }
        if(checkDaca()!=1)
        {
            ok=0;
            cout<<"Eroare sintaxa-DACA"<<endl;
        }
        if(checkRepetaPanaCand()==-1)
        {
            ok=0;
            cout<<"Eroare sintaxa-REPETA PANA CAND"<<endl; //pana cand inainte de repeta
        }
        if(checkPentru()!=1)
        {
            ok=0;
            cout<<"Eroare sintaxa-PENTRU"<<endl;
        }
        if(checkAltfel()==-1) {cout<<"Eroare sintaxa-Altfel"<<endl; ok=0;}
        if(checkCatTimpExecuta()!=1)
        {
            //ok=0;
            cout<<"Eroare sintaxa-CAT TIMP"<<endl;
        }
        if(checkExecutaCatTimp()!=0)
        {
            ok=0;
            cout<<"Eroare sintaxa-EXECUTA CAT TIMP"<<endl;
        }
    }

    if(cont_repeta!=0&&checkRepetaPanaCand()!=-1)
    {
        cout<<"Eroare sintaxa-REPETA PANA CAND"<<endl;    //nu sunt destui de pana cand
        ok=0;
    }
    if(cont_executa!=0)
    {
        cout<<"Eroare sintaxa-EXECUTA CAT TIMP"<<endl;
        ok=0;
    }
    if(cont_altfel<0&&checkAltfel()!=-1)
    {
        cout<<"Eroare sintaxa-ALTFEL"<<endl;    //avem un altfel fara daca
        ok=0;
    }
    if(checkSwitch()==0) //avem switch fara case
    {
        cout<<"Eroare sintaxa-SWITCH"<<endl;    //avem un altfel fara daca
        ok=0;
    }
    if(ok==1) cout<<"Pseudocodul este CORECT"<<endl;
}

