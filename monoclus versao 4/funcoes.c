#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void menu();
int NUM_OBJETOS;
int NUM_ATRIBUTOS;
///Estrutura para Lista de Atributos
struct ListaAtributos{
    int dado;
    struct ListaAtributos* prox;
};
///Função que cria e aloca espaço na memória para uma lista de atributos e retorna uma lista vazia
struct ListaAtributos* cria_lista_vazia_atributos(){
    struct ListaAtributos* li;
    li = (struct ListaAtributos*) malloc (sizeof(struct ListaAtributos));
    li->dado=NULL;
    li->prox=NULL;
   // printf("LISTA VAZIA CRIADA COM SUCESSO!!!\n");
    return li;

}
///Função que insere atributo dado em uma lista de atributos li
struct ListaAtributos* Insere_atributos(int dado, struct ListaAtributos* li){
        struct ListaAtributos* aux;
        aux = cria_lista_vazia_atributos();
        aux->dado=dado;
        aux->prox=NULL;
        if(li->prox==NULL){
            li->prox= aux;
            return li;
        }else{
            struct ListaAtributos* ultimo= cria_lista_vazia_atributos();
            ultimo=li->prox;
            while(ultimo->prox!=NULL){
                ultimo=ultimo->prox;
            }
                ultimo->prox=aux;
            return li;
        }
}
///Procedimento para imprimir uma lista de atributos li
void Imprime_atributos(struct ListaAtributos* raiz){
    if(raiz->dado!=NULL){
        printf("\n%d -> ", raiz->dado);
    }
    struct ListaAtributos*aux;
    aux=raiz->prox;
    while(aux->prox!=NULL){
        printf("%d -> ", aux->dado);
        aux=aux->prox;
   }
   printf("%d.", aux->dado);
}
///Estrutura para Objeto
struct Objeto{
    int id;
    struct ListaAtributos* atrib;
};
///Função que aloca espaço na memória para um objeto e retorna um objeto vazio
struct Objeto* cria_objeto_vazio(){
    struct Objeto* obj;
    obj = (struct Objeto*) malloc (sizeof(struct Objeto));
    obj->id=NULL;
    obj->atrib=NULL;
   // printf("OBJETO VAZIO CRIADO COM SUCESSO!\n");
    return obj;
}
///Função que Atribui o id e uma lista de atributos para um objeto.
struct Objeto* atribuiObjeto(int id, struct ListaAtributos* li){
    //cria um objeto
    struct Objeto* o;
    o = cria_objeto_vazio();
    o->id=id;
    o->atrib=li;
    return o;
};
///Procedimento para Imprimir um objeto
void ImprimeObjeto(struct Objeto* o){
    printf("\n\nid do Objeto: %d\n", o->id);
    printf("Lista de Atributos: ");
    Imprime_atributos(o->atrib);
}
///Estrutura para lista de Obejtos
struct ListaObjetos{
    struct Objeto* objeto;
    struct ListaObjetos* prox;
};
///Função para alocar espaço na memória para uma lista de objetos.
struct ListaObjetos* cria_lista_objetos_vazia(){
    struct ListaObjetos* li;
    li = (struct ListaObjetos*) malloc (sizeof(struct ListaObjetos));
    li->objeto=NULL;
    li->prox=NULL;
    //printf("LISTA VAZIA DE OBJETOS CRIADA COM SUCESSO!\n");
    return li;
}
///Função para inserir um novo objeto o em uma lista de objetos raiz.
struct ListaObjetos* insereListaObjetos(struct ListaObjetos* raiz, struct Objeto* o){
    struct ListaObjetos* aux= cria_lista_objetos_vazia();
    aux->objeto = o;
    aux->prox=NULL;

    if (raiz==NULL|| raiz->objeto==NULL){
      // printf("entrou com a raiz vazia\n");
        return aux;
    }
    else{
        if(raiz->prox==NULL){
           // printf("lista de unico no\n");
            if( raiz->objeto != o){
                raiz->prox=aux;
            }
        } else{
           // printf("varrer a lista\n");
            struct ListaObjetos* p= cria_lista_objetos_vazia();
            p=raiz;
            while((p->prox)->prox!=NULL){
                p= p->prox;
            }//sai do while quando chegar no ultimo objeto
            (p->prox)->prox=aux;
        }
        return raiz;
    }
}
///Procedimento para imprimir lista de objetos
void imprimeListaObjetos(struct ListaObjetos* raiz){
    printf("Lista de Objetos:");
    if(raiz==NULL || raiz->objeto==NULL){
        printf("Lista vazia.\n");
    } else{
        struct ListaObjetos* aux =cria_lista_objetos_vazia();
        aux=raiz;
        while(aux!=NULL){
            ImprimeObjeto(aux->objeto);
            aux=aux->prox;
        }
    }
    printf("\n\n");
}
///Função que calcula a distancia eucliadina entre dois objetos com mesmo numero de atributos.
float calculaDistanciaEuclidiana(struct Objeto* x,struct Objeto* y){
    struct ListaAtributos* auxiliarX;
    auxiliarX=x->atrib;
    struct ListaAtributos* auxiliarY;
    auxiliarY=y->atrib;
    float distancia=0;
    float aux=0;
    while(auxiliarX != NULL && auxiliarY!=NULL){
        aux= auxiliarX->dado-auxiliarY->dado;
        distancia= (aux*aux) + distancia;
        auxiliarX= auxiliarX->prox;
        auxiliarY=auxiliarY->prox;
    }
    if (auxiliarX == NULL && auxiliarY==NULL){
        return sqrt(distancia);
    }
    else
        printf("Esses objetos são incompatíveis\n");
}
///Função que faz a LEITURA DO ARQUIVO de entrada  e retorna a lista de objetos lidas no arquivo.
struct ListaObjetos* LeituraDeArquivo(){
    struct ListaObjetos* ListaObjetos= cria_lista_objetos_vazia();
    struct ListaAtributos* lista_atributos_auxiliar= cria_lista_vazia_atributos();
    struct Objeto* objeto_auxiliar= cria_objeto_vazio();
    FILE* txt = fopen("ENTRADA.txt","r");// leitura ; ENTRADA
    if(txt == NULL){// Se arquivo não encontrado retorna NULL
        printf("\nErro a abrir arquivo!");
    }
    else{
        int atributoInteiro;
        int i=0;
        int j=1; //guarda a linha que está sendo lida, ou o id do objeto que está sendo inserido na lista de objetos
        printf("Ocorreu tudo bem na leitura do arquivo!!!\n\n");
        fscanf(txt,"%d %d \n",&NUM_OBJETOS,&NUM_ATRIBUTOS);
        printf("Entrada:\n");
        printf("Numero de Objetos: %d\nNumero de Atributos: %d\n\n",NUM_OBJETOS, NUM_ATRIBUTOS);
        while((fscanf(txt,"%d", &atributoInteiro))!= EOF){
               lista_atributos_auxiliar=Insere_atributos(atributoInteiro,lista_atributos_auxiliar);
            if(i==NUM_ATRIBUTOS-1){
                objeto_auxiliar=atribuiObjeto(j,lista_atributos_auxiliar);
                ListaObjetos=insereListaObjetos(ListaObjetos,objeto_auxiliar);
                struct ListaAtributos* aux2= cria_lista_vazia_atributos();
                lista_atributos_auxiliar=aux2;//reseta a lista de atributos auxiliar
                i=-1; // reseta numero de atributos e lê a próxima linha(te que ser -q pq será incrementado depois do if
                j++; //contador de número de objetos ou de linhas do arquivo, cada linha representa um objeto!
            }
            i++;
        }
         imprimeListaObjetos(ListaObjetos);
    }
    fclose(txt);
    return ListaObjetos;
}
///Função que le todos os valores de um vetor e retorna a media dos valores.
float CalculaMediaVetor (float Vetor[]){
    int i;
    float media=0;
    for (i=0;i<NUM_OBJETOS;i++){
        media=media+Vetor[i];
    }
    media=media/NUM_OBJETOS;
    printf("\nA media das menores distancias de todos os obejtos eh: %.3f\n", media);
    return media;
}
///Procedimento para Imprimir uma matriz que possui numero de colunas igual ao NUM_OBJETOS (variável global)
void ImprimeMatriz(float MAT[][NUM_OBJETOS]){
    int i, j;
    for(i=0;i<NUM_OBJETOS;i++){
        for(j=0;j<NUM_OBJETOS;j++){
            printf("%.1f\t",MAT[i][j]);
        }
        printf("\n");
    }
}
/// Procedimento para imprimir um vetor em formato de lista
void ImprimeVetor(float VETOR[]){
    int i;
    for(i=0;i<NUM_OBJETOS;i++){
        printf("%.2f\t",VETOR[i]);
    }
}
///atribui as distancias de todos os objetos na matriz de distancia e atribui como zero as duas outras matrizes
void AtribuiDistanciaZeraResto(struct ListaObjetos* ListaObjetos, float Distancias[][NUM_OBJETOS], float Adjacente[][NUM_OBJETOS], float NV_Adjacente[][NUM_OBJETOS]){
    int i,j;
    struct ListaObjetos* ListaObjAux1= ListaObjetos;
    struct ListaObjetos* ListaObjAux2= ListaObjetos;
    for(i=0;i<NUM_OBJETOS;i++){
        for(j=0;j<NUM_OBJETOS;j++){
            Distancias[i][j]= calculaDistanciaEuclidiana(ListaObjAux1->objeto,ListaObjAux2->objeto);
            ListaObjAux2=ListaObjAux2->prox;
            Adjacente[i][j]=0;
            NV_Adjacente[i][j]=0;
        }
        ListaObjAux2=ListaObjetos;
        ListaObjAux1=ListaObjAux1->prox;
    }
//    printf("\nMatriz Adjacente:\n");
//    ImprimeMatriz(Adjacente);
//    printf("\nMatriz NV Adjacente:\n");
//    ImprimeMatriz(NV_Adjacente);
    printf("\nMatriz de Distancias:\n");
    ImprimeMatriz(Distancias);
}
///atribui um vetor com as menores distancias de cada objeto
void MenoresDistancias(float vetor_distancias[], float matriz_distancias[][NUM_OBJETOS]){
    float menor= RAND_MAX; //parametro para o vetor. rand_max eh como infinito
    int i,j;
    for(i=0;i<NUM_OBJETOS;i++){
        for(j=0;j<NUM_OBJETOS;j++){
                if (i!=j && matriz_distancias[i][j]<menor){
                    menor=matriz_distancias[i][j];
                }
        }
        vetor_distancias[i]=menor;
        menor =RAND_MAX;
    }
    printf("\nVetor com as menores distancias de cada objeto:\n");
    ImprimeVetor(vetor_distancias);
    printf("\n");
}
///cria um grafo com arestas somente entre os objetos mais próximos
void AtribuiMatrizAdjacente(float Matriz_distancias[][NUM_OBJETOS],float Matriz_adjacente[][NUM_OBJETOS], float Vetor_menores[]){
    int i,j;
    for(i=0;i<NUM_OBJETOS;i++){
        for(j=0;j<NUM_OBJETOS;j++){
            if(Matriz_distancias[i][j]==Vetor_menores[j]){
                Matriz_adjacente[i][j]=1;
            }
        }
    }
    printf("\nA matriz adjacente foi atualizada para:\n");
    ImprimeMatriz(Matriz_adjacente);
}
///cria um grafo com arestas somente entre os objetos menores que uma distancia randomizada
void PreClusterizacao(float VetoresMenores[], float MatrizNVAdjacente[][NUM_OBJETOS], float MatrizDistancias[][NUM_OBJETOS]){
        float media= CalculaMediaVetor(VetoresMenores);
        srand( (unsigned)time(NULL) ); //criar o alfa randomico; srand é fundamental para que a função rand traga valores aleatórios diferentes a cada rodada de execução
        float randomico, limite;

        int i,j;
        for(i=0;i<NUM_OBJETOS;i++){
            for(j=0;j<NUM_OBJETOS;j++){
                randomico= rand() % 101;
                randomico=(randomico/100);//randomico tem valor entre 0 e 1
                if(randomico==0)
                    j--;
                else{
                    limite=randomico*media;
//                    printf("limite= %f e media= %f",limite, media);
//                    printf("MAT[%d][%d]=%f\n", i, j, MatrizDistancias[i][j]);
                    if(MatrizDistancias[i][j]<=limite && i!=j && MatrizNVAdjacente[i][j]!=1){
                        MatrizNVAdjacente[i][j]=1;
                        MatrizNVAdjacente[j][i]=1;
                        printf("\nA distancia do objeto %d ao objeto %d eh %.3f e eh menor que o limite %.3f\n", i,j, MatrizDistancias[i][j], limite);
                    }
                }
            }
        }
        printf(("\nA NV_Adjacente foi atualizada para: \n"));
        ImprimeMatriz(MatrizNVAdjacente);
}
///Libera memória reservada para uma lista de atributos
void LiberaMemoriaAtributos(struct ListaAtributos* li){
    struct ListaAtributos* aux;
    aux=li;
    while(aux!=NULL){
        aux=li->prox;
        free(li);
        li=aux;
    }
}
///Libera memória reservada para uma lista de objetos
void LiberaMemoriaObjetos(struct ListaObjetos* Obj){
    struct ListaObjetos* aux;
    aux=Obj;
    while(aux!=NULL){
        Obj=aux;
        aux=aux->prox;
        LiberaMemoriaAtributos((Obj->objeto)->atrib);
        free(Obj);
    }
}
///Imprime componentes conexas de um grafo
void ComponentesConexas(float adjacente[][NUM_OBJETOS], int componentes_conexas[]){
    int i;
    int num_componente=1;
    i=0;
    while(i<NUM_OBJETOS){
        if(componentes_conexas[i]==0){
            printf("\ncomponente conexa %d:", num_componente);
            componentes_conexas[i]=num_componente;
            visita_linha_marca_vetor(adjacente,componentes_conexas,i, num_componente);
            num_componente++;
        }
        i++;
    }
}
///Visita Linha para Componente conexa
void visita_linha_marca_vetor(float adjacente[][NUM_OBJETOS], int componentes_conexas[], int linha, int num_componente){
    printf("%d -", linha);
    int j;
        for (j=0;j<NUM_OBJETOS;j++){
            if(adjacente[linha][j]!=0 && componentes_conexas[j]==0){
                    componentes_conexas[j]=num_componente;
                    visita_linha_marca_vetor(adjacente,componentes_conexas, j, num_componente);
            }
    }
}
