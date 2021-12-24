#include <cstdio>
#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

#define MAX 100107


int r[MAX], SA[MAX]; 
int posicion[MAX];
int temporal[MAX];
int LCP[MAX]; 
int palabra[MAX]; 
int N, S, gap;
bool hasLCP = false;
int letras[MAX]; 

bool cmp(int i, int j) {
    if (posicion[i] == posicion[j]) {
        i += gap;
        j += gap;
        if (i < S && j < S)
            return posicion[i] < posicion[j];
        else
            return i > j;
    }
    return posicion[i] < posicion[j];
}


void construirSA() {
    for (int i = 0; i < S; ++i) {
        posicion[i] = letras[i];
        SA[i] = i;      
        temporal[i] = 0;     
    }
   
    gap = 1;
    while (true) {
        
        sort(begin(SA), begin(SA) + S, cmp);

        
        for(int i=0; i < S-1; ++i){
        
            int higher = cmp(SA[i], SA[i+1]);     
            temporal[i+1] = temporal[i] + (higher ? 1 : 0);
        }

        for(int i=0; i < S; ++i){
            posicion[SA[i]] = temporal[i]; 
        }
        
        if (temporal[S-1] >= S-1) 
            break;
        gap = gap << 1; 
    }
}

void construirLCP(int tam) {
    for(int i=0; i < tam; ++i){
        r[SA[i]] = i;
    }
   
    
    LCP[0] = 0;
    int h = 0;
    for (int i = 0; i < tam; ++i) {
        if (r[i] == 0) {
            LCP[i] = 0;
            continue;
        }
        if (r[i] > 0) {
            int j = SA[r[i]-1];
            while (i+h < tam && j+h < tam && letras[i+h] == letras[j+h]) ++h;
            LCP[r[i]] = h;
            if (h > 0) {
                --h;
                hasLCP = true;
            }
        }
    }
}
 
bool buscarLCS(int x, int tam, bool siImp) {
    
    bool contadores[N];
    int contador;
    for (int i = 1; i < tam; ++i) {
        if (LCP[i] >= x) {
            for(int i=0; i < N; ++i){
                contadores[i] = false;
            }
            
            contador = 1;
            contadores[palabra[SA[i-1]]] = true;
            int j = i;
            while (j < tam && LCP[j] >= x) { 
                if (palabra[SA[j]] != palabra[SA[j]+x-1]) { 
                    break;
                }
                if (!contadores[palabra[SA[j]]]) {
                    contadores[palabra[SA[j]]] = true;
                    ++contador;
                }
                ++j;
            }
            if (contador > N/2) {
                if (siImp) {
                    printf("%c", 'a' + letras[SA[i]]); 
                    for (int k = 1; k < x; ++k) {
                        printf("%c", 'a' + letras[SA[i]+k]);
                    }
                    printf("\n");
                }
                else { 
                    return true;
                }
            }
            i = j-1; 
        }
    }
    return false;
}


int main() {
    
    int tamPalabra = -1;
    int T, tam; 
    string linea;
    while (scanf("%d", &N) == 1 && N != 0) {
        tam = 0;
        getline(cin, linea); 

        for(int i=0; i < N; ++i){
       
            getline(cin, linea);
            if (linea.length() - tamPalabra > 0)
                tamPalabra = linea.length();
            for (int j = 0; j < linea.length(); ++j) {
               
                palabra[tam] = i;
                letras[tam++] = linea[j] - 'a';
            }
            letras[tam++] = 27+i; 
            letras[tam] = 0;
        }
        letras[tam-1] = 0;

        --tam;
        S = tam;
        construirSA();
        construirLCP(tam);
        
        int bajo = 1, mejor = -1;
        int alto = tamPalabra;
        if (hasLCP) {
            while (alto >= bajo) {
                int mid = bajo + (alto-bajo)/2;
                if (buscarLCS(mid, tam, false)) {
                    bajo = mid + 1;
                    mejor = max(mid,mejor);
                }
                else
                    alto = mid - 1;
            }
        }
        if (mejor != -1) {
            buscarLCS(mejor, tam, true);
        }
        else
            printf ("?\n");
        printf ("\n");
     }
    return 0;
}