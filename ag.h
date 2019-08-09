#include <string>
#include <iostream>
#include<fstream>
#include <vector>
#include <math.h>
#include <algorithm>
#include "mochila.h"

using namespace std;

class AlgoritmoGenetico{
    public:
    
    int tamanhopopulacao;
    
    double probDeCruzamento;
    
    double probDeMutacao;
    
    int Ngeracoes;
    int tipoCruzamento,tipoMutacao;
    
    vector<int>best;
    double FoBest;
    
    vector<vector<int>>populacao;
    vector<int>fitnessPopulacao;
    vector<vector<int>>populacaoAux;
    
    string nomeArquivo;
    
    pmochila *prob;

    //construtor
    AlgoritmoGenetico(int tamannhoPop, int ngeracoes, int tipocruz,int mutacao,double probCruza, double probMutacao, string nomearq);
    //destrutor
    virtual ~AlgoritmoGenetico();

    //funcoes 
    void cruzamentoPontoCorte(vector<int>&pai1,vector<int>&pai2);
    vector<int>cruzamentoUniformeParametrizado(vector<int>&pai1,vector<int>&pai2);
    vector<int>mutacao(vector<int>&individuo);
    vector<int>selecaoTorneio();
    int selecaoTorneioCP();
    void avaliarPopulacao(int geracao);
    void gerarPopulacaoInicial();
    void cicloGeracional();
    void imprimirFitnessPop();
    




};
