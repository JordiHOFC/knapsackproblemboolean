#include "mochila.h"
#include<string>
#include<vector>
using namespace std;

int main(){
  
    pmochila prob("knapPI_1_100_1000_1");
    //pmochila prob("f1_l-d_kp_10_269");
    //pmochila prob("f2_l-d_kp_20_878");
    prob.mostrarItens();

    int v[]={1,0,0,1,1,0,0,1,1,1};
    vector<int> sol;
    /* for(int i=0;i<10;i++){
        sol.push_back(v[i]);
    }*/
    for(int i=0;i<15;i++){
        sol=prob.solucaoAletoria();
        for(int i=0;i<prob.n;i++){
            cout<<sol[i];
        }
        cout<<endl;
        int valor=prob.Fo(sol);
        cout<<"Fo -> "<<valor<<endl;
    }

    
    return 1;
}
