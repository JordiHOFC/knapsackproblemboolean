#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
 
 using namespace std;

 class pmochila{
     public: 
     //ponteiro para fazer leitura de instancias
     ifstream f;

     //string que carrega o nome do arquivo
     string nomearquivo;

     //construtor
     pmochila(string nomearq);
     
     //destrutor
     virtual ~pmochila();

     //capacidade maxima da mochila
     int Wmax;

     //numero de itens
     int n;
     
     //constante para equalizacao, esta constante sera o somatorio dos beneficios dividido por 4
     int M;

     //bonificação do item 
     vector<int> V;

     //peso do item 
     vector<int>W;

     //funcao de mostrar itens
     void mostrarItens();
     //funcao de avaliacao
     int Fo(vector<int>& sol);
     //gerando solucao de forma aleatoria
     vector<int>solucaoAletoria();
 };

 