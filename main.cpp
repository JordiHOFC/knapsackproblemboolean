#include "ag.h"
#include<string>
#include<vector>
using namespace std;

int main(){
    string nomearquivo="f1_l-d_kp_10_269";
    //string nomearquivo="knapPI_1_100_1000_1";
    //string nomearquivo="f2_l-d_kp_20_878";
    //string nomearquivo="knapPI_3_10000_1000_1";
    

    AlgoritmoGenetico Ag(150,100,0.6,0.19,nomearquivo);
   
    Ag.cicloGeracional();

    return 1;
}
