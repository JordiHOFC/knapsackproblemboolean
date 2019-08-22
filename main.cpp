#include "ag.h"
#include<string>
#include<vector>
using namespace std;

int main(){
    srand(1);
    //string nomearquivo="f1_l-d_kp_10_269";
    //string nomearquivo="knapPI_1_100_1000_1";
    //string nomearquivo="f10_l-d_kp_20_879";
    //string nomearquivo="knapPI_3_10000_1000_1";
    string nomearquivo="knapPI_3_2000_1000_1";
    
    

    AlgoritmoGenetico Ag(150,200,2,2,0.5,0.015,nomearquivo);
   
    Ag.cicloGeracional();
  /*  AlgoritmoGenetico Ag2(150,200,2,0.6,0.19,nomearquivo);
    Ag2.cicloGeracional();*/

    return 1;
}
