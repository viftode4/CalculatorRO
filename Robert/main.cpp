#include <iostream>
#include <fstream>
#include <cstring>
#include <bits/stdc++.h>

using namespace std;
ifstream fin("CalcRO.in");
char cuvInutile[100][100] = {"Care", "Ce", "Cat", "este", "sunt", "rezultatul", "cu", "lui", "?", "dintre"},
        cuvInm[10][20] = {"inmultire", "inmultirii", "inmultirea", "produs", "produsul", "produsului"},
        cuvAdun[10][20] = {"suma", "sumei", "adunare", "adunarea", "adunarii"},
        cuvScad[10][20] = {"scadere", "scaderii", "diferenta", "diferentei"},
        cuvImp[10][20] = {"impartire", "impartirea"};
char num[100][100] = {"o", "un", "unu", "doi", "doua", "trei", "patru", "cinci", "sase", "sapte", "opt", "noua", "zece",
                      "unsprezece", "doisprezece", "treisprezece", "paisprezece",
                      "cincisprezece", "saispreceze", "saptesprezece", "optsprezece", "nouasprezece", "douazeci",
                      "treizeci", "patruzeci", "cincizeci", "saizeci", "saptezeci", "optzeci", "nouazeci"
};
int numCif[100] = {1, 1, 1, 2, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 30, 40, 50, 60, 70,
                   80, 90
};
char cuvCheie[100][100] = {"suta", "sute", "mie", "mii", "milion", "milioane"};
int cuvCheieCif[100] = {100, 100, 1000, 1000, 1000000, 1000000};
int ok, aFostcuvCheie, k;
char vecCuv[5000][10000];

struct BIG_INT {
    int v[150] = { 0 };
    bool semn = 0;
    int operatie=0;
    int n[50] = { 0 };
};
BIG_INT operator+(BIG_INT& a, BIG_INT& b) {
    BIG_INT c;
    c= a+b;
    return c;
}

char* transfLitCif(char *s) {
    int i = 0;
    char line[1000]= {0};
    int numar = 0, temp = 0;
    strcpy(line, s);
    char *q = new char[1000]();
    strcpy(q,line);
    char *savepointer = NULL;
    q = strtok_r(line, "_", &savepointer);
    while (q) {
        i = 0;
        ok = 0;
        while (num[i][0] != '_' && num[i][0]!='\0') {
            if (strcmp(q, num[i]) == 0) {
                ok = 1;
                if (aFostcuvCheie) {
                    numar = numar + temp;
                    temp = numCif[i];
                } else
                    temp = temp + numCif[i];
            }
            i++;
        }
        aFostcuvCheie = 0;
        if (!ok) {
            i = 0;
            while (cuvCheie[i][0] != '_' && cuvCheie[i][0]!='\0') {
                if (strcmp(q, cuvCheie[i]) == 0) {
                    temp = temp * cuvCheieCif[i];
                    aFostcuvCheie = 1;
                }
                i++;
            }
        }
        q = strtok_r(NULL, "_", &savepointer);
    }
    if (ok && !aFostcuvCheie)numar = numar + temp;
    if (!ok && aFostcuvCheie)numar = numar + temp;
    char* t = new char[1000]();
    int k = 0;
    while(numar)
    {
        t[k++] = numar%10+'0';
        numar/=10;
    }
    for(i=0;i<k/2;i++)
        swap(t[i],t[k-i-1]);

    return t;
}
int eCuvInutil(char s[]) //verifica daca e cuvant inutil
{
    int i = 0;
    while (cuvInutile[i][0]!='\0') {
        if (strcmp(s, cuvInutile[i]) == 0)
            return 1;
        i++;
    }
    return 0;
}

int eSi(char *s) {
    if (strcmp(s, "si") == 0)
        return 1;
    return 0;
}

int eAdun(char *s) {
    int i = 0;
    while (cuvAdun[i][0]) {
        if (strcmp(s, cuvAdun[i]) == 0)
            return 1;
        i++;
    }
    return 0;
}

int eScad(char *s) {
    int i = 0;
    while (cuvScad[i][0]) {
        if (strcmp(s, cuvScad[i]) == 0)
            return 1;
        i++;
    }
    return 0;
}

int eInm(char *s) {
    int i = 0;
    while (cuvInm[i][0]) {
        if (strcmp(s, cuvInm[i]) == 0)
            return 1;
        i++;
    }
    return 0;
}

int eImp(char *s) {
    int i = 0;
    while (cuvImp[i][0]) {
        if (strcmp(s, cuvImp[i]) == 0)
            return 1;
        i++;
    }
    return 0;
}

void introdVec(char *s) {
    int i;
    char prop[25600]= {0}, cuv[10000]= {0};
    char *savepointer = NULL;
    char *p = strtok_r(s, " ", &savepointer);
    int siFlag = 0, nrp = 0;
    while (p) {
        strcpy(cuv, p);
        if (eSi(cuv)) {
            siFlag = 1;
            p = strtok_r(NULL, " ", &savepointer);
            continue;
        }
        if (eCuvInutil(cuv)) {
            p = strtok_r(NULL, " ", &savepointer);
            continue;
        }
        else if (eAdun(cuv)) {
            strcpy(vecCuv[k], "+");
            nrp++;
        } else if (eScad(cuv)) {
            strcpy(vecCuv[k], "-");
            nrp++;
        } else if (eInm(cuv)) {
            strcpy(vecCuv[k], "*");
            nrp++;
        } else if (eImp(cuv)) {
            strcpy(vecCuv[k], "/");
            nrp++;
        } else {
            if (cuv[strlen(cuv) - 1] == ',') {
                cuv[strlen(cuv) - 1] = '\0';
                auto x = transfLitCif(cuv);
                strcpy(vecCuv[k],x);
                delete[] x;
            } else {
                auto x = transfLitCif(cuv);
                strcpy(vecCuv[k],x);
                delete[] x;
                if (siFlag) {
                    if (nrp) {
                        nrp--;
                        k++;
                        strcpy(vecCuv[k], ")");
                    }
                    siFlag=0;
                }
            }
        }
        k++;
        p = strtok_r(NULL, " ", &savepointer);
    }
}
/*
int transfCharInt(char *s)
{
    int nr=0;
    for(int i=0;i<strlen(s);i++)
        nr=nr*10+s[i];
    return nr;
}
int evaluator(char exp[1000])
{
    int temp=0;
    char c[10];
    stack <int> S;
    while(exp[i][0]!='\0')
    {
        if(exp[i][0]=='+' || exp[i][0]=='-' || exp[i][0]=='*' || exp[i][0]=='\\')
            S.push(exp[i]),strcat(c,exp[i]);
        else
            if(exp[i][0]!=')')
                S.push(transfCharInt(exp[i]));
        else //e paranteza
        {
            while(S.top()!='+' && S.top()!='-' && S.top()!='*' && S.top()!='\\')
                temp=
        }
    }
}
*/
int main() {
    char a[1000];
    fin.getline(a, 100);
    introdVec(a);
    for(int i=0; i<k; i++)
        cout<<vecCuv[i];
    char s[1000][100];
    int v = 0;
    stack<char> op;
    for(int i=0;i<k;i++)
    {
        if(vecCuv[i][0]=='*')
            op.push('*');
        else if(vecCuv[i][0]=='+')
            op.push('+');
        else if(vecCuv[i][0]=='/')
            op.push('/');
        else if(vecCuv[i][0]=='-')
            op.push('-');

        strcpy(s[++v],vecCuv[i]);
        if(s[v][0]==')')
        {
            v--;
            int r = 0;
            char cOP = op.top();
            op.pop();
            if(cOP == '*')
            {
                r=1;
                while(s[v][0]!='*')
                {
                    r=r*(stoi(s[v],nullptr));
                    v--;
                }
                strcpy(s[v],to_string(r).c_str());
            }
            else if(cOP=='+')
            {
                r=0;
                while(s[v][0]!='+')
                {
                    r=r+(stoi(s[v],nullptr));
                    v--;
                }
                strcpy(s[v],to_string(r).c_str());
            }
            else if(cOP=='-')
            {
                r=(stoi(s[v],nullptr));
                v--;
                r-=(stoi(s[v],nullptr));
                v--;
                r*=-1;
                strcpy(s[v],to_string(r).c_str());
            }
            else if(cOP=='/')
            {
                r=(stoi(s[v-1],nullptr));
                v--;
                r/=(stoi(s[v+1],nullptr));
                v--;
                strcpy(s[v],to_string(r).c_str());
            }
        }
    }
    cout<<' '<<s[1];


    return 0;
}
