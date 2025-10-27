//
//==================================================================================================
// Universidade Federal de Goiás - UFG
// Instituto de Informática - INF
// 
// Disciplina..: Estruturas de Dados - 2
// Ano/Semestre: 2022/2
// Professor...: Wanderley de Souza Alencar
//
//
// Implementação didática de um "Max-Heap" na Linguagem de Programação C
//
// Data........: 15/12/2022
//==================================================================================================
//
#include <stdio.h>
#include <stdlib.h> 

#define MAXIMUM_HEAP_SIZE 16
#define ROOT_POSITION      0
#define INVALID_KEY       -1

int heapSize = 0;

//
// Rotina...: Swap
// Objetivo.: Realizar a troca entre os conteúdos de "a" e "b" (inteiros)
//
//
void SwapInt(int *a, int *b) {
  int temp = *b;
  *b = *a;
  *a = temp;
}
//
// Rotina...: Heapfy
// Objetivo.: Reconstruir o "heapArray" após a realização de uma operação de inserção ou de remoção,
//            sabendo que seu tamanho é "heapSize" e que a posição modificada é "i". 
//
//
void Heapfy(int heapArray[], int heapSize, int i) {
  int largestIndex, 
      leftIndex, rightIndex; 
      
  if (heapSize == 1) {
      printf("Há apenas um elemento no heap e,\n");
      printf("por isso, não há necessidade de reorganizá-lo.\n");
  }
  else {
    //
    // Identifica qual o maior valor entre: raiz, filhos (à esq e à dir).
    //  
    largestIndex = i;
    leftIndex    = 2 * i + 1;
    rightIndex   = 2 * i + 2;
    
    if ((leftIndex < heapSize) && (heapArray[leftIndex] > heapArray[largestIndex])) {
       largestIndex = leftIndex;
    }
    if ((rightIndex < heapSize) && (heapArray[rightIndex] > heapArray[largestIndex])) {
       largestIndex = rightIndex;
    }
    //
    // Faz a troca do maior elemento e continua... até que a raiz seja o maior de todos
    //
    if (largestIndex != i) {
       SwapInt(&heapArray[i], &heapArray[largestIndex]);
       Heapfy(heapArray, heapSize, largestIndex);
    }
  }
}

//
// Rotina...: Insert
// Objetivo.: Insere o elemento "newNum" em "heapArray"
//
//
void Insert(int heapArray[], int newNum) {
  int i;
  
  if (heapSize == 0) {
    heapArray[0] = newNum;
    heapSize++;
  }
  else {
    heapArray[heapSize] = newNum;
    heapSize++;
    for (i = ((heapSize / 2) - 1); i >= 0; i--) {
        Heapfy(heapArray, heapSize, i);
    }
  }
}

//
// Rotina...: DeleteMaxVal
// Objetivo.: Remove o elemento de "heapArray" cujo valor é "num"
//
//
void DeleteMaxVal(int heapArray[], int num)
{
  int i;
  
  for (i = 0; i < heapSize; i++) {
    if (num == heapArray[i]) {
       break;
    }
  }

  SwapInt(&heapArray[i], &heapArray[heapSize - 1]);
  heapSize--;
  for (i = ((heapSize / 2) - 1); i >= 0; i--) {
      Heapfy(heapArray, heapSize, i);
  }
}

//
// Rotina...: HeapSort
// Objetivo.: Constrói o "heapArray" executando o Algoritmo HeapSort
//
//
void HeapSort(int heapArray[], int heapSize) {
  int i;

  for (i = ((heapSize / 2) - 1); i >= 0; i--) {
      Heapfy(heapArray, heapSize, i);    
  }  
  
  for (i = (heapSize - 1); i >= 0; i--) {
      SwapInt(&heapArray[ROOT_POSITION], &heapArray[i]);    
      Heapfy(heapArray, i, ROOT_POSITION);
  }  

}
//
// Rotina...: PrintHeap
// Objetivo.: Imprime, na console, todos os elementos que estão no "heapArray", sendo que a 
//            impressão ocorre "nível a nível" (Breadth First Search -- BFS) a partir da raiz.
//
void PrintHeap(int heapArray[], int heapSize) {
  int i;
  
  for (i = 0; i < heapSize; ++i) {
      printf("%d ", heapArray[i]);
  }
  printf("\n");
}

void CreateHeap_FloydAlgorithm(int heapArray[], int heapSize) { 
  int i;

  for (i = (heapSize/2) - 1; i >= 0; i--) {
      Heapfy(heapArray, heapSize, i);   
  }  
}


//
//--------------------------------------------------------------------------------------------------
// Rotina...: Main
// Objetivo.: Corpo principal do gerenciador da estrutura de dados "heap" (Max Heap)
//--------------------------------------------------------------------------------------------------
//
int main() {
    
  int  key, 
       acumulated,
       heapArray[MAXIMUM_HEAP_SIZE];
  char choice;

  printf("MaxHeap [Inteiro] -- Implementação de um MaxHeap de número naturais\n");
  printf("                     Capacidade do Heap: %d números\n\n\n\n", MAXIMUM_HEAP_SIZE);
  acumulated = 0;
  choice     = 'S';
  do { 
        do {
              printf("Informe um valor de chave primária a ser inserido no heap ou\n");
              printf("o valor %d para finalizar a operação de inserção.\n", INVALID_KEY);
              printf("Chave primária: ");
              scanf("%d",&key);
              printf("\n");
        } while ((key != INVALID_KEY) && (key < 0));
        
        if (key != INVALID_KEY) { 
           if (heapSize < MAXIMUM_HEAP_SIZE) {
               printf("\nDeseja acumular valores para executar criação do heap utilizando o Algoritmo de Floyd?\n");
               printf("[S] para sim, [N] para não     Resposta: ");
               scanf("%c",&choice);
               printf("\n\n");
               if ((choice == 'n') || (choice == 'N')) {
                  Insert(heapArray, key); 
                  printf("\n\nHeap atual (após inserção do elemento)\n\n");
                  PrintHeap(heapArray, heapSize);
               }
               else {
                  if (heapSize < MAXIMUM_HEAP_SIZE) { 
                     heapArray[heapSize] = key;
                     acumulated++;  
                     heapSize++;
                     printf("\n\nHeap Atual (com elementos sendo acumulados)\n\n");
                     PrintHeap(heapArray, heapSize);
                  }
               }
           }
           else {
               printf("A capacidade máxima do heap -- %d elementos -- foi atingida.\n", MAXIMUM_HEAP_SIZE);    
           }
        }
  } while ((key != INVALID_KEY) && (heapSize < MAXIMUM_HEAP_SIZE));
  
  //
  // Há elemento "acumulados" para que seja executado o Algoritmo de Floyd
  //
  if (acumulated != 0) {
      CreateHeap_FloydAlgorithm(heapArray,heapSize); 
      printf("\n\nHeap atual (após execução do Algoritmo de Floyd)\n\n");
      PrintHeap(heapArray, heapSize);
  }

  do { 
        printf("Informe um valor de chave primária a ser removido do heap ou\n");
        printf("o valor %d para finalizar a operação de remoção.\n", INVALID_KEY);
        printf("Chave primária: ");
        scanf("%d",&key);
        if (key != INVALID_KEY) { 
           if (heapSize > 0) {
               DeleteMaxVal(heapArray, key); 
               printf("\n\nHeap atual (após remoção)\n\n");
               PrintHeap(heapArray, heapSize);
           }
           else {
               printf("O heap está vazio.\n\n");    
           }
        }
  } while ((key != INVALID_KEY) && (heapSize < MAXIMUM_HEAP_SIZE));
}