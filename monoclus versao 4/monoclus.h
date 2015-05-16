#ifndef MONOCLUS_H_INCLUDED
#define MONOCLUS_H_INCLUDED
extern int NUM_OBJETOS;
extern int NUM_ATRIBUTOS;
///Estrutura para Lista de Atributos
struct ListaAtributos{
    int dado;
    struct ListaAtributos* prox;
};
///Função que cria e aloca espaço na memória para uma lista de atributos e retorna uma lista vazia
struct ListaAtributos* cria_lista_vazia_atributos();
///Função que insere atributo dado em uma lista de atributos li
struct ListaAtributos* Insere_atributos(int dado, struct ListaAtributos* li);
///Procedimento para imprimir uma lista de atributos li
void Imprime_atributos(struct ListaAtributos* raiz);
///Estrutura para Objeto
struct Objeto{
    int id;
    struct ListaAtributos* atrib;
};
///Função que aloca espaço na memória para um objeto e retorna um objeto vazio
struct Objeto* cria_objeto_vazio();
///Função que Atribui o id e uma lista de atributos para um objeto.
struct Objeto* atribuiObjeto(int id, struct ListaAtributos* li);
///Procedimento para Imprimir um objeto
void ImprimeObjeto(struct Objeto* o);
///Estrutura para lista de Obejtos
struct ListaObjetos{
    struct Objeto* objeto;
    struct ListaObjetos* prox;
};
///Função para alocar espaço na memória para uma lista de objetos.
struct ListaObjetos* cria_lista_objetos_vazia();
///Função para inserir um novo objeto o em uma lista de objetos raiz.
struct ListaObjetos* insereListaObjetos(struct ListaObjetos* raiz, struct Objeto* o);
///Procedimento para imprimir lista de objetos
void imprimeListaObjetos(struct ListaObjetos* raiz);
///Função que calcula a distancia eucliadina entre dois objetos com mesmo numero de atributos.
float calculaDistanciaEuclidiana(struct Objeto* x,struct Objeto* y);
///Função que faz a leitura do arquivo de entrada  e retorna a lista de objetos lidas no arquivo.
struct ListaObjetos* LeituraDeArquivo();
///Função que le todos os valores de um vetor e retorna a media dos valores.
float CalculaMediaVetor (float Vetor[]);
///Procedimento para Imprimir uma matriz que possui numero de colunas igual ao NUM_OBJETOS (variável global)
void ImprimeMatriz(float MAT[][NUM_OBJETOS]);
/// Procedimento para imprimir um vetor em formato de lista
void ImprimeVetor(float VETOR[]);
///atribui as distancias de todos os objetos na matriz de distancia e atribui como zero as duas outras matrizes
void AtribuiDistanciaZeraResto(struct ListaObjetos* ListaObjetos, float Distancias[][NUM_OBJETOS], float Adjacente[][NUM_OBJETOS], float NV_Adjacente[][NUM_OBJETOS]);
///atribui um vetor com as menores distancias de cada objeto
void MenoresDistancias(float vetor_distancias[], float matriz_distancias[][NUM_OBJETOS]);
///cria um grafo com arestas somente entre os objetos mais próximos
void AtribuiMatrizAdjacente(float Matriz_distancias[][NUM_OBJETOS],float Matriz_adjacente[][NUM_OBJETOS], float Vetor_menores[]);
///cria um grafo com arestas somente entre os objetos menores que uma distancia randomizada
void PreClusterizacao(float VetoresMenores[], float MatrizNVAdjacente[][NUM_OBJETOS], float MatrizDistancias[][NUM_OBJETOS]);
///Libera memória reservada para uma lista de atributos
void LiberaMemoriaAtributos(struct ListaAtributos* li);
///Libera memória reservada para uma lista de objetos
void LiberaMemoriaObjetos(struct ListaObjetos* Obj);
#endif // MONOCLUS_H_INCLUDED
