#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "monoclus.h"

int main()
{
    void menu();
    NUM_OBJETOS=0;
    NUM_ATRIBUTOS=0;
    int i,j;
    struct ListaObjetos* ListaObjetos=LeituraDeArquivo(); //cria lista de objetos lida de um arquivo
    float MatrizDistancias[NUM_OBJETOS][NUM_OBJETOS];//guarda distancia de todos os objeto para todos objetos
    float MatrizAdjacencia[NUM_OBJETOS][NUM_OBJETOS];//grafo que tem arestas somente entre os vértices mais próximos
    float NV_Adjacente[NUM_OBJETOS][NUM_OBJETOS];//grafo com a pré-clusterização randomizada
    /*Atribui as menores distancias à matriz de distancias, e inicializa as matrizes MatrizAdjacente e NV_Adjacente com 0*/
    AtribuiDistanciaZeraResto(ListaObjetos,MatrizDistancias, MatrizAdjacencia, NV_Adjacente);
    float Menores [NUM_OBJETOS]; //vetor que guarda para todos objetos a distancia do objeto mais próximo.
    /*Atribuir ao vetor as menores distancias para cada objeto*/
    MenoresDistancias(Menores,MatrizDistancias);
    /*Atribuir o grafo com arestas de peso 1, somente entre os objetos mais próximos*/
    AtribuiMatrizAdjacente(MatrizDistancias,MatrizAdjacencia,Menores);
    /*Atribuir o grafo com arestas de peso 1 somente para objetos que possuem uma distancia menor do que a media radomizada*/
    PreClusterizacao(Menores, NV_Adjacente, MatrizDistancias);
    ComponentesConexas(NV_Adjacente);
    LiberaMemoriaObjetos(ListaObjetos);
    return 0;
}
