#include <iostream>
#include<fstream>
#include<cstring>
using namespace std;
ifstream fin("CalcRO.in");
int numar,temp;
char cuvInutile[100][100]= {"Care","Ce","Cat","este","sunt","rezultatul","cu","lui","?","dintre","si"},
                         cuvInm[10][20]= {"inmultire","inmultirii","inmultirea","produs","produsul","produsului"},
                                 cuvAdun[10][20]= {"suma","sumei","adunare","adunarea","adunarii"},
                                         cuvScad[10][20]= {"scadere","scaderii","diferenta","diferentei"},
                                                 cuvImp[10][20]= {"impartire","impartirea"};
char num[100][100]= {"o","un","unu","doi","doua","trei","patru","cinci","sase","sapte","opt","noua","zece","unsprezece","doisprezece","treisprezece","paisprezece",
"cincisprezece","saispreceze","saptesprezece","optsprezece","nouasprezece","douazeci","treizeci","patruzeci","cincizeci","saizeci","saptezeci","optzeci","nouazeci"
                    };
int numCif[100]= {1,1,1,2,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,30,40,50,60,70,80,90};
char cuvCheie[100][100]= {"suta","sute","mie","mii","milion","milioane"};
int  cuvCheieCif[100]= {100,100,1000,1000,1000000,1000000};
char s[256],*p;
int i,ok,aFostcuvCheie=0;
int transfLitCif(char s[])
{
    p=strtok(s,"_");
    while(p)
    {
        i=0;
        ok=0;
        while(num[i][0]!='_')
        {
            if(strcmp(p,num[i])==0)
            {
                ok=1;
                if(aFostcuvCheie)
                    {
                        numar=numar+temp;
                        temp=numCif[i];
                    }
                else
                    temp=temp+numCif[i];
            }
            i++;aFostcuvCheie=0;
        }
        if(!ok)
        {
            i=0;
            while(cuvCheie[i][0]!='_')
            {
                if(strcmp(p,cuvCheie[i])==0)
                    {
                        temp=temp*cuvCheieCif[i];
                        aFostcuvCheie=1;
                    }
                i++;
            }
        }
        p=strtok(NULL,"_");
    }
    if(ok && !aFostcuvCheie)numar=numar+temp;
    if(!ok && aFostcuvCheie)numar=numar+temp;
    return numar;
}
int eCuvInutil(char s[]) //verifica daca e cuvant inutil
{
    int i=0;
    while(cuvInutile[i])
    {
        if(strcmp(s,cuvInutile[i])==0)
            return 1;
        i++;
    }
    return 0;
}
int eAdun(char *s)
{
    int i=0;
    while(cuvAdun[i])
    {
        if(strcmp(s,cuvAdun[i])==0)
            return 1;
        i++;
    }
    return 0;
}
int eScad(char *s)
{
    int i=0;
    while(cuvScad[i])
    {
        if(strcmp(s,cuvScad[i])==0)
            return 1;
        i++;
    }
    return 0;
}
int eInm(char *s)
{
    int i=0;
    while(cuvInm[i])
    {
        if(strcmp(s,cuvInm[i])==0)
            return 1;
        i++;
    }
    return 0;
}
int eImp(char *s)
{
    int i=0;
    while(cuvImp[i])
    {
        if(strcmp(s,cuvImp[i])==0)
            return 1;
        i++;
    }
    return 0;
}
void introdVec(char *s)
{
    int i,k=0;
    char prop[256],*p,vecCuv[50][100],cuv[100],aux[100];
    p=strtok(s," ");
    while(p)
    {
        strcpy(cuv,p);
        if(eCuvInutil(cuv))
            continue;

        else if(eAdun(cuv))
            strcpy(vecCuv[k],"+"),k++;

        else if(eScad(cuv))
            strcpy(vecCuv[k],"-"),k++;

        else if(eInm(cuv))
            strcpy(vecCuv[k],"*"),k++;

        else if(eImp(cuv))
            strcpy(vecCuv[k],"\\"),k++;
        else
        {
            for(i=0;i<strlen(cuv);i++)
                        if(cuv[i]=='_')
                            cuv[i]=' ';//pt orice caz
            if(cuv[strlen(cuv)-1]==',')
            {
                 cuv[strlen(cuv)-1]='\0';
                 strcpy(vecCuv[k],cuv);
                 strcpy(vecCuv[k+1],vecCuv[k]);
                 strcpy(vecCuv[k],vecCuv[k-1]);
            }
             else
                 strcpy(vecCuv[k],cuv);
            k++;
        }
        p=strtok(NULL," ");
    }
}
int main()
{
    char a[100];
    fin.get(a,100);

    cout<<transfLitCif(a);
    return 0;
}
