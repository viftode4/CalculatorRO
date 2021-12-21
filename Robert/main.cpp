#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>

using namespace std;
ifstream fin("CalcRO.in");
char cuvInutile[100][100] = {"Care", "Ce", "Cat", "este", "sunt", "rezultatul", "cu", "lui", "?", "dintre", NULL},
        cuvInm[10][20] = {"inmultire", "inmultirii", "inmultirea", "produs", "produsul", "produsului", NULL},
        cuvAdun[10][20] = {"suma", "sumei", "adunare", "adunarea", "adunarii", NULL},
        cuvScad[10][20] = {"scadere", "scaderii", "diferenta", "diferentei", NULL},
        cuvImp[10][20] = {"impartire", "impartirea", NULL};
char num[100][100] = {"o", "un", "unu", "doi", "doua", "trei", "patru", "cinci", "sase", "sapte", "opt", "noua", "zece",
                      "unsprezece", "doisprezece", "treisprezece", "paisprezece",
                      "cincisprezece", "saispreceze", "saptesprezece", "optsprezece", "nouasprezece", "douazeci",
                      "treizeci", "patruzeci", "cincizeci", "saizeci", "saptezeci", "optzeci", "nouazeci"
};
int numCif[100] = {1, 1, 1, 2, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 30, 40, 50, 60, 70,
                   80, 90};
char cuvCheie[100][100] = {"suta", "sute", "mie", "mii", "milion", "milioane", NULL};
int cuvCheieCif[100] = {100, 100, 1000, 1000, 1000000, 1000000};
int i, ok, aFostcuvCheie, k;
char vecCuv[5000][10000];

const char* transfLitCif(char *s) {
    char line[1000];
    int numar, temp;
    for(int i=0;s[i];i++)
        line[i]=s[i];
    char *q;
    strcpy(q,line);
    while (q) {
        i = 0;
        ok = 0;
        while (num[i][0] != '_') {
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
            while (cuvCheie[i][0] != '_') {
                if (strcmp(q, cuvCheie[i]) == 0) {
                    temp = temp * cuvCheieCif[i];
                    aFostcuvCheie = 1;
                }
                i++;
            }
        }
        q = strtok(NULL, "_");
    }
    if (ok && !aFostcuvCheie)numar = numar + temp;
    if (!ok && aFostcuvCheie)numar = numar + temp;
    string x;
    while(numar)
    {
        x+=numar%10+'0';
        numar/=10;
    }
    reverse(x.begin(),x.end());
    return x.c_str();
}
int eCuvInutil(char s[]) //verifica daca e cuvant inutil
{
    int i = 0;
    while (cuvInutile[i][0]!=NULL) {
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
    char prop[25600], cuv[10000];
    const char *p = strtok(s," ");
    int siFlag = 0, nrp = 0;
    while (p) {
        strcpy(cuv, p);
        if (eSi(cuv)) {
            siFlag = 1;
            continue;
        }
        if (eCuvInutil(cuv))
            continue;
        else if (eAdun(cuv)) {
            strcpy(vecCuv[k], "+");
            if (siFlag)
                nrp++;
        } else if (eScad(cuv)) {
            strcpy(vecCuv[k], "-");
            if (siFlag)
                nrp++;
        } else if (eInm(cuv)) {
            strcpy(vecCuv[k], "*");
            if (siFlag)
                nrp++;
        } else if (eImp(cuv)) {
            strcpy(vecCuv[k], "\\");
            if (siFlag)
                nrp++;
        } else {
            if (cuv[strlen(cuv) - 1] == ',') {
                cuv[strlen(cuv) - 1] = '\0';
                strcpy(vecCuv[k],transfLitCif(cuv));
            } else {
                strcpy(vecCuv[k],transfLitCif(cuv));
                if (siFlag) {
                    while (nrp) {
                        nrp--;
                        k++;
                        strcpy(vecCuv[k], ")");
                    }
                }
            }
        }
        k++;
        p = strtok(NULL, " ");
    }
}

int main() {
    char a[1000];
    fin.getline(a, 100);
    introdVec(a);
    for(int i=0;i<k;i++)
        cout<<vecCuv[i];
    return 0;
}
