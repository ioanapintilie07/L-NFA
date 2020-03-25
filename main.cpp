#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

const int dim = 51;

int cautCaracter(char c, char v[]){
    for(int i=0; i<strlen(v); ++i)
        if(v[i] == c)
            return i;
    return -1;
}

int cautStare(const int v[], int n, int x){
    int i;
    for(i=1; i<=n; ++i)
        if(v[i] == x)
            return 1;
    return -1;
}

bool evaluate(int a[][51][dim], char alfabet[], int m, int stariFinale[], int k, int q0, char cuvant[]){
    int i, j, l, p, stari[dim], stariAux[dim], lambdaStari[dim], lambdaAux[dim], nrStari = 0, nrStariAux = 0, nrLambdaStari, nrLambdaAux = 0, lungime = strlen(cuvant), poz;
    stari[++nrStari] = q0;
    for(i=0; i<lungime; ++i)
    {
        char c = cuvant[i];
        poz = cautCaracter(c, alfabet);
        nrStariAux = 0;
        nrLambdaStari = 0;
        for(j=1; j<=nrStari; ++j)
        {
            if(a[stari[j]][poz][0] != 0)
                for(l=1; l<=a[stari[j]][poz][0]; ++l)
                    stariAux[++nrStariAux] = a[stari[j]][poz][l];
            if(a[stari[j]][m][0] != 0)
                for(l=1; l<=a[stari[j]][m][0]; ++l)
                    lambdaStari[++nrLambdaStari] = a[stari[j]][m][l];
        }
        nrStari = 0;
        for(j=1; j<=nrStariAux; ++j)
            stari[++nrStari] = stariAux[j];
        if(i != lungime-1 && (nrLambdaStari != 0))
        {
            nrLambdaAux = -1;
            while(nrLambdaAux != 0)
            {
                nrLambdaAux = 0;
                for(l=1; l<=nrLambdaStari; ++l)
                {
                    if(a[lambdaStari[l]][m][0] != 0)
                        for(p=1; p<=a[lambdaStari[l]][m][0]; ++p)
                        {
                            if(lambdaStari[l] == a[lambdaStari[l]][poz][p] && cautStare(stari, nrStari, lambdaStari[l]) == 1)
                                p++;
                            lambdaAux[++nrLambdaAux] = a[lambdaStari[l]][m][p];
                        }
                    if(a[lambdaStari[l]][poz][0] != 0)
                        for(p=1; p<=a[lambdaStari[l]][poz][0]; ++p)
                        {
                            if(lambdaStari[l] == a[lambdaStari[l]][poz][p] && cautStare(stari, nrStari, lambdaStari[l]) == 1)
                                p++;
                            stari[++nrStari] = a[lambdaStari[l]][poz][p];
                        }
                }
                nrLambdaStari = nrLambdaAux;
                for(j=1; j<=nrLambdaAux; ++j)
                    lambdaStari[j] = lambdaAux[j];
            }
        }
        for(j=1; j<=nrStari; ++j)
            cout << stari[j] << " ";
        cout << endl;
        if(nrStari == 0 &&nrLambdaStari == 0)
            return false;
    }
    for(i=1; i<=nrStari; ++i)
        if(cautStare(stariFinale, k, stari[i]) == 1)
            return true;
    for(i=1; i<=nrLambdaStari; ++i)
        if(cautStare(stariFinale, k, lambdaStari[i]) == 1)
            return true;
    return false;


}

int main() {
    ifstream fin("automata.in");
    int n, m, q0, k, l, i, j, stare1, stare2, poz, a[dim][51][dim], stariFinale[dim];
    char alfabet[51], tranzitie, cuvant[51];
    fin >> n >> m;
    for(i=0; i<n; ++i)
        for(j=0; j<=m; ++j)
            a[i][j][0] = 0; //aici vom retine numarul de tranzitii pentru a[i][j]
    for(i=0; i<m; ++i)
        fin >> alfabet[i];
    fin >> q0 >> k;
    for(i=1; i<=k; ++i)
        fin >> stariFinale[i];
    fin >> l;
    for(i=1; i<=l; ++i) {       //construire matrice
        fin >> stare1 >> tranzitie >> stare2;
        if(tranzitie == '$')
            a[stare1][m][++a[stare1][m][0]] = stare2;
        else{
            poz = cautCaracter(tranzitie, alfabet);
            a[stare1][poz][++a[stare1][poz][0]] = stare2;
        }
    }
    cout << "Introduceti cuvantul: ";
    cin >> cuvant;
    bool value = evaluate(a, alfabet, m, stariFinale, k, q0, cuvant);
    if(value == 1) cout << "TRUE";
    else cout << "FALSE";
    fin.close();
    return 0;
}
