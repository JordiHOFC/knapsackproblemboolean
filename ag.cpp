#include "ag.h"
#include<string>
//construtor
AlgoritmoGenetico::AlgoritmoGenetico(int tamannhoPop, double probCruza, double probMutacao, string nomearq){
    nomeArquivo=nomearq;
    prob = new pmochila(nomearq);
    tamanhopopulacao=tamannhoPop;
    probDeCruzamento=probCruza;
    probDeMutacao=probMutacao;
    populacao=vector<vector<int>>(tamanhopopulacao);


}

//destrutor
AlgoritmoGenetico::~AlgoritmoGenetico(){
    delete prob;
}
void AlgoritmoGenetico::gerarPopulacaoInicial(){
    for(int i=0;i<tamanhopopulacao;i++){
        populacao[i]= prob->solucaoAletoria();
    }
}

vector<int> AlgoritmoGenetico::selecaoRoleta(){
    int T=0;//somatorio de todos os fitness 
    int R;//valor aleatorio entre 0 e T
    int S=0;//variavel que tera o acumulo dos fitnesse dos individuos 
    
    //calculando o valor de T
    for(int i=0;i<tamanhopopulacao;i++){
        T+=fitnessPopulacao[i];
    }
    //vamos encontrar o valor que definirá quem sera o individuo escolhido
    R=rand()%T;
    //agora iremos selecionar o individuo
    for(int i=0;i<tamanhopopulacao;i++){
        S+=fitnessPopulacao[i];
        if(S>=R){
            return populacao[i];
        }
    }
}
vector<vector<int>> AlgoritmoGenetico:: cruzamentoPontoCorte(vector<int>&pai1,vector<int>&pai2){
    int ponto;//ponto de corte é o indice que o vetor sera dividido 
    vector<vector<int>>filhos(2);
    vector<int>f1(prob->n);
    vector<int>f2(prob->n);

    ponto=rand()%prob->n;
    for(int i=0;i<prob->n;i++){
        if(i<ponto){
            f1[i]=pai1[i];
            f2[i]=pai2[i];
        }else{
            f1[i]=pai2[i];
            f2[i]=pai1[i];
        }
    }
    filhos[0]=f1;
    filhos[1]=f2;
    return filhos;
}
vector<int> AlgoritmoGenetico:: cruzamentoUniformeParametrizado(vector<int>&pai1,vector<int>&pai2){
    vector<int> individuo;
    int moeda;
    int gene;
    for (int i = 0; i < pai1.size(); i++)
    {
        moeda = rand() % 10;
        
        if (moeda < probDeCruzamento)
        {
            gene =pai1[i];
            individuo.push_back(gene);
        }
        else
        {
            gene = pai2[i];
            individuo.push_back(gene);
        }
    }
    
    return individuo;
}
vector<int> AlgoritmoGenetico::mutacao(vector<int>individuo){
    int indice;//vai receber o indice que será invetido 
    int r;
    int Prob=probDeMutacao*100;
    r=rand()%100;
    if(r<=Prob){
        indice=rand()%prob->n;
        if(individuo[indice]==0){
            individuo[indice]=1;
            return individuo;
        }else{
            individuo[indice]=0;
            return individuo;
        }
    }else{
        return individuo;
    }

}
