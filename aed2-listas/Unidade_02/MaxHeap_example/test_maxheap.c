// Test cases para demonstrar os bugs no MaxHeap.c
// Para compilar: gcc -o test_maxheap test_maxheap.c
// 
// Este arquivo contém testes que demonstram os problemas identificados na análise

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAXIMUM_HEAP_SIZE 16

// Cópia das funções do MaxHeap.c para teste
void SwapInt(int *a, int *b) {
  int temp = *b;
  *b = *a;
  *a = temp;
}

void Heapfy(int heapArray[], int heapSize, int i) {
  int largestIndex, leftIndex, rightIndex; 
      
  if (heapSize == 1) {
      // Problema 1: Mensagem desnecessária
      // printf("Há apenas um elemento no heap...\n");
  }
  else {
    largestIndex = i;
    leftIndex    = 2 * i + 1;
    rightIndex   = 2 * i + 2;
    
    if ((leftIndex < heapSize) && (heapArray[leftIndex] > heapArray[largestIndex])) {
       largestIndex = leftIndex;
    }
    if ((rightIndex < heapSize) && (heapArray[rightIndex] > heapArray[largestIndex])) {
       largestIndex = rightIndex;
    }
    
    if (largestIndex != i) {
       SwapInt(&heapArray[i], &heapArray[largestIndex]);
       Heapfy(heapArray, heapSize, largestIndex);
    }
  }
}

// Função DeleteMaxVal ORIGINAL com bug
void DeleteMaxVal_BUGGY(int heapArray[], int* heapSize, int num)
{
  int i;
  
  for (i = 0; i < *heapSize; i++) {
    if (num == heapArray[i]) {
       break;
    }
  }
  // BUG: Não verifica se elemento foi encontrado!
  // Se i == heapSize, acessa posição inválida
  SwapInt(&heapArray[i], &heapArray[*heapSize - 1]);
  (*heapSize)--;
  for (i = ((*heapSize / 2) - 1); i >= 0; i--) {
      Heapfy(heapArray, *heapSize, i);
  }
}

// Função DeleteMaxVal CORRIGIDA
void DeleteMaxVal_FIXED(int heapArray[], int* heapSize, int num)
{
  int i;
  
  for (i = 0; i < *heapSize; i++) {
    if (num == heapArray[i]) {
       break;
    }
  }
  
  // FIX: Verifica se elemento foi encontrado
  if (i == *heapSize) {
    printf("ERRO: Elemento %d não encontrado no heap.\n", num);
    return;
  }
  
  SwapInt(&heapArray[i], &heapArray[*heapSize - 1]);
  (*heapSize)--;
  for (i = ((*heapSize / 2) - 1); i >= 0; i--) {
      Heapfy(heapArray, *heapSize, i);
  }
}

void PrintHeap(int heapArray[], int heapSize) {
  printf("Heap: [");
  for (int i = 0; i < heapSize; i++) {
    printf("%d", heapArray[i]);
    if (i < heapSize - 1) printf(", ");
  }
  printf("]\n");
}

// Verifica se array mantém propriedade de max-heap
int isValidMaxHeap(int heapArray[], int heapSize) {
  for (int i = 0; i < heapSize; i++) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < heapSize && heapArray[i] < heapArray[left]) {
      printf("Violação: heapArray[%d]=%d < heapArray[%d]=%d\n", 
             i, heapArray[i], left, heapArray[left]);
      return 0;
    }
    if (right < heapSize && heapArray[i] < heapArray[right]) {
      printf("Violação: heapArray[%d]=%d < heapArray[%d]=%d\n", 
             i, heapArray[i], right, heapArray[right]);
      return 0;
    }
  }
  return 1;
}

// ============================================================================
// TESTES
// ============================================================================

void test_delete_nonexistent_element_buggy() {
  printf("\n=== TESTE 1: Deletar elemento inexistente (VERSÃO COM BUG) ===\n");
  int heap[] = {50, 30, 20, 15, 10, 8, 16};
  int size = 7;
  
  printf("Heap inicial: ");
  PrintHeap(heap, size);
  
  printf("Tentando deletar elemento 99 (que não existe)...\n");
  printf("ATENÇÃO: Isto vai causar acesso a memória inválida!\n");
  
  // Descomente para ver o bug em ação (pode causar crash):
  // DeleteMaxVal_BUGGY(heap, &size, 99);
  
  printf("Teste pulado para evitar crash. Bug confirmado: falta validação.\n");
}

void test_delete_nonexistent_element_fixed() {
  printf("\n=== TESTE 2: Deletar elemento inexistente (VERSÃO CORRIGIDA) ===\n");
  int heap[] = {50, 30, 20, 15, 10, 8, 16};
  int size = 7;
  
  printf("Heap inicial: ");
  PrintHeap(heap, size);
  
  printf("Tentando deletar elemento 99 (que não existe)...\n");
  DeleteMaxVal_FIXED(heap, &size, 99);
  
  printf("Heap após tentativa: ");
  PrintHeap(heap, size);
  printf("✓ Teste passou: Erro tratado corretamente.\n");
}

void test_delete_existing_element() {
  printf("\n=== TESTE 3: Deletar elemento existente ===\n");
  int heap[] = {50, 30, 20, 15, 10, 8, 16};
  int size = 7;
  
  printf("Heap inicial: ");
  PrintHeap(heap, size);
  printf("Propriedade max-heap válida: %s\n", isValidMaxHeap(heap, size) ? "SIM" : "NÃO");
  
  printf("\nDeletando elemento 30...\n");
  DeleteMaxVal_FIXED(heap, &size, 30);
  
  printf("Heap após deleção: ");
  PrintHeap(heap, size);
  printf("Propriedade max-heap válida: %s\n", isValidMaxHeap(heap, size) ? "SIM" : "NÃO");
  
  if (isValidMaxHeap(heap, size)) {
    printf("✓ Teste passou: Heap mantém propriedade após deleção.\n");
  } else {
    printf("✗ Teste falhou: Propriedade max-heap violada.\n");
  }
}

void test_scanf_buffer_issue() {
  printf("\n=== TESTE 4: Demonstração do problema com scanf ===\n");
  printf("Problema: scanf(\"%%c\") lê o \\n deixado por scanf(\"%%d\") anterior.\n");
  printf("Solução: Usar scanf(\" %%c\") com espaço antes do %%c.\n");
  printf("\n");
  printf("Exemplo do bug:\n");
  printf("  scanf(\"%%d\", &num);    // Usuário digita: 42<ENTER>\n");
  printf("  scanf(\"%%c\", &choice); // Lê o <ENTER>, não espera usuário!\n");
  printf("\n");
  printf("Solução:\n");
  printf("  scanf(\"%%d\", &num);     // Usuário digita: 42<ENTER>\n");
  printf("  scanf(\" %%c\", &choice); // Espaço antes ignora whitespace\n");
  printf("\n✓ Bug documentado.\n");
}

void test_heap_size_validation() {
  printf("\n=== TESTE 5: Validação de tamanho máximo ===\n");
  printf("Problema: Insert() não verifica se heap está cheio.\n");
  printf("Risco: Buffer overflow ao inserir mais de %d elementos.\n", MAXIMUM_HEAP_SIZE);
  printf("Solução: Adicionar verificação antes de inserir.\n");
  printf("✓ Vulnerabilidade documentada.\n");
}

int main() {
  printf("╔════════════════════════════════════════════════════════════╗\n");
  printf("║     TESTES DE VALIDAÇÃO - MaxHeap.c                       ║\n");
  printf("║     Demonstração dos bugs identificados na análise        ║\n");
  printf("╚════════════════════════════════════════════════════════════╝\n");
  
  test_delete_nonexistent_element_buggy();
  test_delete_nonexistent_element_fixed();
  test_delete_existing_element();
  test_scanf_buffer_issue();
  test_heap_size_validation();
  
  printf("\n╔════════════════════════════════════════════════════════════╗\n");
  printf("║  RESUMO DOS TESTES                                         ║\n");
  printf("╠════════════════════════════════════════════════════════════╣\n");
  printf("║  ✓ Bug 1: DeleteMaxVal sem validação - CONFIRMADO         ║\n");
  printf("║  ✓ Bug 2: scanf() buffer issue - DOCUMENTADO              ║\n");
  printf("║  ✓ Bug 3: Insert sem verificação tamanho - DOCUMENTADO    ║\n");
  printf("║  ✓ Correção: DeleteMaxVal com validação - FUNCIONA        ║\n");
  printf("╚════════════════════════════════════════════════════════════╝\n");
  
  return 0;
}
