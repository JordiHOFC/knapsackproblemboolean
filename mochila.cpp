#include "mochila.h"
#include<string>

pmochila::pmochila(string nomearq){
    //abrindo o arquivo
    f=ifstream(nomearq);
    //verificamos se foi aberto
    if(!f.is_open()){
        cout << "Erro ao abrir o arquivo" << endl;
    }
    //ler quantidade de itens
    f>>n;
    //ler capacidade da mochila
    f>>Wmax;
    //configurando os vetores de bonificacao e peso
    V=vector<int>(n);
    W=vector<int>(n);
    M=0;
    //agora leremos os itens 
    for(int i=0;i<n;i++){
        f>>V[i];
        M+=V[i];
        f>>W[i];
    }
    f.close();
}
pmochila::~pmochila(){

}
void pmochila::mostrarItens(){
    for(int i=0;i<n;i++){
        cout<<"Item: "<<i<<" valor: "<<V[i]<<" peso: "<<W[i]<<endl;
    }
}
int pmochila::Fo(vector<int>& sol){
    int fo=0, capacidade=0;
    for(int i=0;i<n;i++){
        //caso o item esteja na mochila
        if(sol[i]==1){
            //somamos o seu beneficio
            fo+=V[i];
            //e subtraimos o seu peso na capacidade disponivel da mochila
            capacidade+=W[i];
        }
    }
    if(capacidade<=Wmax){
        return fo;
    }else{
        fo-=M;
        return fo;
    }
}

vector<int>pmochila::solucaoAletoria(){
    vector<int>sol(n);
    int r;
    for(int i=0;i<n;i++){
        r= rand()% 9;
        if(r<4){
            sol[i]=0;
        }else{
            sol[i]=1;
        }
    }
    
    return sol;
}