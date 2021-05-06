// André Nascimento
// GitHub: https://github.com/AndreNasci
// Linkedin: linkedin.com/in/andré-nascimento-a01095185

//listaEstaticaSequencialInt.c

// Tipo: int (os itens da lista não int)
// Esse código instancia, insere, imprime,
// busca e remove itens de uma lista estatica
// sequencial.

#include<stdio.h>
#define MAX 10 //numero maximo de itens da lista

//Define tipo bool
typedef enum{false, true} bool;

int listaEstSeq[MAX]; //lista estatica sequencial
int dispo=0; //proxima posicao disponivel na lista

// ======== OPERACOES DA LISTA ========
//retorna primeiro item da lista
int primeiroItem();
//retorna ultimo item da lista
int ultimoItem();
//retorna o numero de itens da lista
int numItens();
//retorna verdadeiro se inseriu o item
bool insereItem(int valor);
//retorna verdadeiro se removeu o item
bool removeItem(int valor);
//imprime os itens da lista
void imprimeLista();
//retorna a posicao de um item
int buscaSeq(int chave);
//retorna a posicao de um item
int buscaBin(int chave);

// ======== main ========
int main(void) {
    int aux, i;

    //Seed para numeros aleatorios
    srand(time(0));

    //insere MAX itens na lista
    for(i=0; i<MAX; i++){
        //gera os itens aleatoriamente (menores que 100)
        aux = rand() % 100;
        //busca o item na lista,
        if(buscaSeq(aux) == -1){
            //se nao encontra, insere
            insereItem(aux);
        }//end if
        else{
            //se encontra, repete o passo
            i--;
        }//end else
    }//end for

    imprimeLista();

    //recebe um valor do teclado e busca na lista
    printf("Valor procurado: ");
    scanf("%d", &aux);

    if(buscaBin(aux) + 1){
        printf("Encontrado na posicao %d\n\n", buscaSeq(aux));
    }
    else {
        printf("Valor nao encontrado.\n\n");
    }

    //remove o item, se encontrado
    removeItem(aux);
    imprimeLista();

    return 0;
}//end main


// ======== Funcoes ========

//retorna o primeiro item ou
//-1 se a lista estiver vazia
int primeiroItem(){
    if(dispo == 0)
        return -1;
    else
        return listaEstSeq[0];
}//end primeiroItem

//retorna o ultimo item ou
//-1 se a lista estiver vazia
int ultimoItem(){
    if(dispo == 0)
        return -1;
    else
        return listaEstSeq[dispo-1];
}//end ultimoItem

//retorna o numero de itens da lista
int numItens(){
    return dispo;
}//end numItens

//imprime os itens da lista
void imprimeLista(){
    int i = 0;
    printf("Posicao      Item\n");
    while(i < dispo){
        printf("(%5d)   =%6d\n", i, listaEstSeq[i]);
        i++;
    }//end while
    printf("\n");
}//end imprimeLista

//insere um item na lista e retorna true
//ou nao insere (se a lista estiver cheia)
//  e retorna false
bool insereItem(int valor){
    int i = dispo;

    if(dispo > MAX){
        //se a lista esta cheia, nao insere
        return false;
    }//end if
    else{
        //procura o lugar para inserir de forma ordenada
        while((i > 0) && (listaEstSeq[i-1] > valor)){
            listaEstSeq[i] = listaEstSeq[i-1];
            i--;
        }//end while

        //insere valor
        listaEstSeq[i] = valor;

        //aumenta numero de itens da lista
        dispo++;

        return true;
    }//end else
}//end insereItem

//retorna verdadeiro se removeu o item na lista
bool removeItem(int valor){
    int pos;

    //busca o item
    pos = buscaBin(valor);
    if(pos != -1){
        //se encontrou item
        while(pos < dispo-1){
            //atualiza a posicao dos proximos itens
            listaEstSeq[pos] = listaEstSeq[pos+1];
            pos++;
        }//end while
        //diminui o numero de itens da lista
        dispo--;
        return true;
    }//end if
    else{
        //se nao encontrou o item
        return false;
    }//end else
}//end removeListaEstSeq

//Realiza uma busca sequencial na lista
//retorna a posicao de um elemento
//ou -1 caso nao encontrou
int buscaSeq(int chave){
    int i = 0;
    while((i < dispo) && (listaEstSeq[i] < chave)){
        i++;
    }//end while
    if((i < dispo) && (listaEstSeq[i] == chave)){
        return i;
    }//end if
    else{
        return -1;
    }//end else
}//end buscaSeq

//Realiza uma busca binaria na lista
//retorna a posicao de um elemento ou
//-1 caso nao encontrou
int buscaBin(int chave){
    int meio;
    int inf=0; //limite inferior
    int sup = MAX-1; //limite superior
    while(inf <= sup){
        meio = (inf + sup)/2;
        if(chave == listaEstSeq[meio]){
            //chave encontrada
            return meio;
        }//end if
        else{
            if(chave < listaEstSeq[meio]){
                //chave esta na metade da esquerda
                sup = meio-1;
            }//end if
            else{
                //chave esta na metade da direita
                inf = meio+1;
            }//end else
        }//end else
    }//end while
    return -1; // nao encontrado
}//end buscaBin
