
#include<iostream>
#include<algorithm>
#include <cstring>

 
using namespace std;
 

string LCP(string ar_sufijos[], int n)
{
    
    if (n == 0)
        return "";
     
    
    string prefix = ar_sufijos[0];
    
    int nro_coin_mayor = 0;
    
    string prefix_mayor, prefix_;
    
    for(int i = 1; i<n; i++){
        string s = ar_sufijos[i];

        if(n == 0 || prefix =="") return "";
        
        int n_min = min(prefix.size(), s.size());
        
        int nro_coincidencias=0;
        
        
        prefix_ ="";
        for(int j=0; j< n_min; j++){
            if(s[j] == prefix[j]){
                nro_coincidencias++;
                prefix_ = prefix_+s[j];
                
            }
            else
                break;
        }
        prefix=s;
        

        if(nro_coin_mayor< nro_coincidencias){
            nro_coin_mayor = nro_coincidencias;
            prefix_mayor = prefix_; 

        }
        
        

    }

    //cout<<nro_coin_mayor<<endl;
    //cout<<prefix_mayor<<endl;

    return prefix_mayor;

    
}



struct sufijo
{
    int ide;
    char *letra;
};
 

int cmp(struct sufijo a, struct sufijo b)
{
    return strcmp(a.letra, b.letra) < 0? 1 : 0;
}
 

void printArr(int arr[], int n)
{
    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}


void printArr2(string arr2[], int n)
{
    for(int i = 0; i < n; i++)
        cout << arr2[i] << " ";
    cout << endl;
}

string construirsufijoArray(char *txt, int n)
{
    
    
    struct sufijo sufijoes[n];
 
    
    for (int i = 0; i < n; i++)
    {
        sufijoes[i].ide = i;
        sufijoes[i].letra = (txt+i);
        //cout<<sufijoes[i].letra<<endl;
    }
 
    
    sort(sufijoes, sufijoes+n, cmp);
    
    
    int *sufijoArr = new int[n];
    string *sufijoArrLetras = new string[n];
    //string sufijoArrLetras[] ={};

    
    for (int i = 0; i < n; i++){
        sufijoArr[i] = sufijoes[i].ide;
        sufijoArrLetras[i] = sufijoes[i].letra; 
    }
 //
    
    //printArr2(sufijoArrLetras, n);

    //cout << "The longest common prefix is: "<<
    string rpta = LCP(sufijoArrLetras, n);

    
    return  rpta;
}

int main()
{
    
    char txt[] = "bbcaadbbeaa";
    int n = strlen(txt);
    
    //int *sufijoArr = construirsufijoArray(txt,  n);
    
    string rpta_sufijo = construirsufijoArray(txt,  n);

    cout<<rpta_sufijo<<endl;

    //printArr(sufijoArr, n);



    //string ar[] = {"AB","ABABBAB", "ABBAB", "B", "BAB", "BABBAB", "BBAB"};
    
    return 0;
}