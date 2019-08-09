#include "ag.h"
#include<string>
//construtor
AlgoritmoGenetico::AlgoritmoGenetico(int tamannhoPop, int ngeracoes,int tipocruz,int mutacao,double probCruza, double probMutacao, string nomearq){
    nomeArquivo=nomearq;
    prob = new pmochila(nomearq);
    tamanhopopulacao=tamannhoPop;
    Ngeracoes=ngeracoes;
    probDeCruzamento=probCruza;
    probDeMutacao=probMutacao;
    tipoCruzamento=tipocruz;
    tipoMutacao=mutacao;
    populacao=vector<vector<int>>(tamanhopopulacao);
    fitnessPopulacao=vector<int>(tamanhopopulacao);
    populacaoAux=vector<vector<int>>(tamanhopopulacao);
    FoBest=0;

}

//destrutor
AlgoritmoGenetico::~AlgoritmoGenetico(){
    delete prob;
}
void AlgoritmoGenetico::gerarPopulacaoInicial(){
    for(int i=0;i<tamanhopopulacao;i++){
        populacao[i]= prob->solucaoAletoria();
    }
    avaliarPopulacao(0);
}

vector<int> AlgoritmoGenetico::selecaoTorneio(){
    int T=75;//probabilidade de ser escolhido 
    int R;//valor aleatorio entre 0 e 100
    int indice1=rand()%prob->n,indice2=rand()%prob->n;//selecionando aleatoriamente dois individuos 
    vector<int> melhor,pior;
    //verificando qual individuo é melhor
    if(fitnessPopulacao[indice1]>fitnessPopulacao[indice2]){
        melhor=populacao[indice1];
        pior=populacao[indice2];
    }else{
        melhor=populacao[indice2];
        pior=populacao[indice1];
    }
    //veremos se o melhor ou pior vai ser escolhido
    R=rand()%100;
    if(R<T){
        return melhor;
    }else{
        return pior;
    }
}

int AlgoritmoGenetico::selecaoTorneioCP(){
    int T=75;//probabilidade de ser escolhido 
    int R;//valor aleatorio entre 0 e 100
    int indice1=rand()%prob->n,indice2=rand()%prob->n;//selecionando aleatoriamente dois individuos 
    int melhor,pior;
    //verificando qual individuo é melhor
    if(fitnessPopulacao[indice1]>fitnessPopulacao[indice2]){
        melhor=indice1;
        pior=indice2;
    }else{
        melhor=indice2;
        pior=indice1;
    }
    //veremos se o melhor ou pior vai ser escolhido
    R=rand()%100;
    if(R<T){
        return melhor;
    }else{
        return pior;
    }
}
void AlgoritmoGenetico:: cruzamentoPontoCorte(vector<int>&pai1,vector<int>&pai2){
    int ponto;//ponto de corte é o indice que o vetor sera dividido 
    
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
    pai1=mutacao(f1);
    pai2=mutacao(f2);
    
}
vector<int> AlgoritmoGenetico:: cruzamentoUniformeParametrizado(vector<int>& pai1, vector<int>& pai2){
    vector<int> individuo;
    double moeda;
    
    for (int i = 0; i < pai1.size(); i++)
    {
        moeda =rand() / (RAND_MAX + 1.0);
        
        if (moeda < probDeCruzamento)
        {
           
            individuo.push_back(pai1[i]);
        }
        else
        {
            individuo.push_back(pai2[i]);
        }
    }
    
    return individuo;
}
vector<int> AlgoritmoGenetico::mutacao(vector<int>&individuo){
   //bit flip
   if(tipoMutacao==1){
        int indice;//vai receber o indice que será invetido 
        double r;
        
        r=rand() / (RAND_MAX + 1.0);
        if(r<=probDeMutacao){
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
    //swap
    if(tipoMutacao==2){
        int indice,indice2,aux;//variaveis para identificar os valores que seram trocados, e variavel auxiliar para troca 
        double r;
        
        r=rand() / (RAND_MAX + 1.0);
        
        if(r<=probDeMutacao){ 
             
            do{
                
                indice=rand()%prob->n;
                indice2=rand()%prob->n;
                aux=individuo[indice];
                individuo[indice]=individuo[indice2];
                individuo[indice2]=aux;
            }while(indice==indice2);
            
            return individuo;
         }
         return individuo;
    }
    
}
void AlgoritmoGenetico::avaliarPopulacao(int geracao){
    string nomearq=nomeArquivo+".txt";
    
    ofstream arq=ofstream(nomearq,ios::app);
    
    for(int i=0;i<tamanhopopulacao;i++){
        fitnessPopulacao[i]=prob->Fo(populacao[i]);
        if(fitnessPopulacao[i]>FoBest){
            FoBest=fitnessPopulacao[i];
            best=populacao[i];
            arq<<"Best  -> "<<FoBest<<" Geracao: "<<geracao<<" Tipo de cruzamento "<<tipoCruzamento<<endl;
        }
    }
    arq.close();
}
void AlgoritmoGenetico::imprimirFitnessPop(){
    cout << "Populacao: [";
    for (int i = 0; i < fitnessPopulacao.size(); i++)
    {
        printf("%d,", fitnessPopulacao[i]);
    }
    cout << "]" << endl;
}
void AlgoritmoGenetico::cicloGeracional(){
   if(tipoCruzamento==1){
        vector<vector<int>>pais(2);
    
        vector<int>filho(prob->n);
        int inseridos=0;
        
        //gerando a populacao inicial
        gerarPopulacaoInicial();
        //agora vamos utilizar os operadores geneticos para evoluir nossos individuos
        for(int i=0;i<Ngeracoes;i++){
            //cruzamento e mutacao
            for(int i=0;i<tamanhopopulacao;i++){
                pais[0]=selecaoTorneio();
                pais[1]=selecaoTorneio();
                filho=cruzamentoUniformeParametrizado(pais[0],pais[1]);
                filho=mutacao(filho);
                populacaoAux[inseridos]=filho;
                inseridos++;
                filho.clear();

            }
            inseridos=0;
            //substituicao geracional
            populacao=populacaoAux;
            //avaliar populacao
            avaliarPopulacao(i);
        }
        imprimirFitnessPop();
    }
    if(tipoCruzamento==2){
        int pai1, pai2;
        //gerando a populacao inicial
        gerarPopulacaoInicial();
        //agora vamos utilizar os operadores geneticos para evoluir nossos individuos
        for(int i=0;i<Ngeracoes;i++){
            //cruzamento e mutacao
            for(int i=0;i<(tamanhopopulacao/2);i++){
                pai1=selecaoTorneioCP();
                pai2=selecaoTorneioCP();
                cruzamentoPontoCorte(populacao[pai1],populacao[pai2]);

            }
            
            //avaliar populacao
            avaliarPopulacao(i);
        }
        imprimirFitnessPop();
    }
}