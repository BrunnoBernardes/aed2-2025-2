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
// VERSÃO CORRIGIDA - Com correções de bugs e melhorias
//
// Data........: 15/12/2022
// Atualizado..: 23/11/2025 - Correções de bugs e melhorias de segurança
//==================================================================================================
//
#include <stdio.h>
#include <stdlib.h> 

#define MAXIMUM_HEAP_SIZE 16
#define ROOT_POSITION      0
#define INVALID_KEY       -1

// Macros para tornar o código mais legível
#define LEFT_CHILD(i)  (2 * (i) + 1)
#define RIGHT_CHILD(i) (2 * (i) + 2)
#define PARENT(i)      (((i) - 1) / 2)

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
      
  // CORREÇÃO: Removida mensagem desnecessária para heap de tamanho 1
  if (heapSize <= 1) {
      return; // Nada a fazer
  }
  
  //
  // Identifica qual o maior valor entre: raiz, filhos (à esq e à dir).
  //  
  largestIndex = i;
  leftIndex    = LEFT_CHILD(i);
  rightIndex   = RIGHT_CHILD(i);
  
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

//
// Rotina...: Insert
// Objetivo.: Insere o elemento "newNum" em "heapArray"
// 
// CORREÇÃO: Implementação otimizada com bubble-up O(log n)
//           ao invés de reconstruir heap inteiro O(n)
//
void Insert(int heapArray[], int newNum) {
  // CORREÇÃO: Verificação de overflow adicionada
  if (heapSize >= MAXIMUM_HEAP_SIZE) {
    printf("\nERRO: Heap cheio! Capacidade máxima de %d elementos atingida.\n", MAXIMUM_HEAP_SIZE);
    return;
  }
  
  // Insere no final
  heapArray[heapSize] = newNum;
  int i = heapSize;
  heapSize++;
  
  // Bubble up: move o elemento para cima até encontrar posição correta
  while (i > 0) {
    int parent = PARENT(i);
    if (heapArray[i] <= heapArray[parent]) {
      break; // Propriedade do heap satisfeita
    }
    SwapInt(&heapArray[i], &heapArray[parent]);
    i = parent;
  }
}

//
// Rotina...: DeleteValue
// Objetivo.: Remove o elemento de "heapArray" cujo valor é "num"
// 
// CORREÇÃO: 
// - Renomeada de DeleteMaxVal para DeleteValue (nome mais apropriado)
// - Adicionada validação se elemento existe antes de tentar remover
//
void DeleteValue(int heapArray[], int num)
{
  int i;
  
  // Busca o elemento no heap
  for (i = 0; i < heapSize; i++) {
    if (num == heapArray[i]) {
       break;
    }
  }
  
  // CORREÇÃO: Validação adicionada
  if (i == heapSize) {
    printf("\nERRO: Elemento %d não encontrado no heap.\n", num);
    return;
  }

  // Move último elemento para posição do removido
  SwapInt(&heapArray[i], &heapArray[heapSize - 1]);
  heapSize--;
  
  // Reconstrói o heap
  for (i = ((heapSize / 2) - 1); i >= 0; i--) {
      Heapfy(heapArray, heapSize, i);
  }
}

//
// Rotina...: DeleteMax
// Objetivo.: Remove e retorna o elemento máximo (raiz) do heap
// 
// NOVA FUNÇÃO: Implementa operação padrão de Max Heap
//
int DeleteMax(int heapArray[]) {
  if (heapSize == 0) {
    printf("\nERRO: Heap vazio!\n");
    return INVALID_KEY;
  }
  
  int maxValue = heapArray[ROOT_POSITION];
  
  // Move último elemento para raiz
  heapArray[ROOT_POSITION] = heapArray[heapSize - 1];
  heapSize--;
  
  // Reconstrói heap a partir da raiz
  if (heapSize > 0) {
    Heapfy(heapArray, heapSize, ROOT_POSITION);
  }
  
  return maxValue;
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
// Rotina...: ClearInputBuffer
// Objetivo.: Limpar o buffer de entrada do stdin
//
void ClearInputBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
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
  int  scanf_result;

  printf("MaxHeap [Inteiro] -- Implementação de um MaxHeap de número naturais\n");
  printf("                     Capacidade do Heap: %d números\n\n\n\n", MAXIMUM_HEAP_SIZE);
  acumulated = 0;
  choice     = 'S';
  
  do { 
        do {
              printf("Informe um valor de chave primária a ser inserido no heap ou\n");
              printf("o valor %d para finalizar a operação de inserção.\n", INVALID_KEY);
              printf("Chave primária: ");
              
              // CORREÇÃO: Verificação do retorno do scanf
              scanf_result = scanf("%d", &key);
              if (scanf_result != 1) {
                printf("\nERRO: Entrada inválida! Digite um número inteiro.\n\n");
                ClearInputBuffer();
                continue;
              }
              printf("\n");
        } while ((key != INVALID_KEY) && (key < 0));
        
        if (key != INVALID_KEY) { 
           if (heapSize < MAXIMUM_HEAP_SIZE) {
               printf("\nDeseja acumular valores para executar criação do heap utilizando o Algoritmo de Floyd?\n");
               printf("[S] para sim, [N] para não     Resposta: ");
               
               // CORREÇÃO: Espaço antes de %c para ignorar whitespace
               scanf_result = scanf(" %c", &choice);
               if (scanf_result != 1) {
                 printf("\nERRO: Entrada inválida!\n\n");
                 ClearInputBuffer();
                 continue;
               }
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
      CreateHeap_FloydAlgorithm(heapArray, heapSize); 
      printf("\n\nHeap atual (após execução do Algoritmo de Floyd)\n\n");
      PrintHeap(heapArray, heapSize);
  }

  do { 
        printf("Informe um valor de chave primária a ser removido do heap ou\n");
        printf("o valor %d para finalizar a operação de remoção.\n", INVALID_KEY);
        printf("Chave primária: ");
        
        // CORREÇÃO: Verificação do retorno do scanf
        scanf_result = scanf("%d", &key);
        if (scanf_result != 1) {
          printf("\nERRO: Entrada inválida! Digite um número inteiro.\n\n");
          ClearInputBuffer();
          continue;
        }
        
        if (key != INVALID_KEY) { 
           if (heapSize > 0) {
               DeleteValue(heapArray, key); 
               printf("\n\nHeap atual (após remoção)\n\n");
               PrintHeap(heapArray, heapSize);
           }
           else {
               printf("O heap está vazio.\n\n");    
           }
        }
        // CORREÇÃO: Condição corrigida - verifica se heap não está vazio
  } while ((key != INVALID_KEY) && (heapSize > 0));
  
  return 0;
}
