# Comparação Visual: MaxHeap.c vs MaxHeap_CORRIGIDO.c

Este documento mostra lado a lado as principais diferenças entre as versões original e corrigida.

---

## Bug #1: DeleteMaxVal - Validação de Elemento

### ❌ ORIGINAL (MaxHeap.c - linhas 99-114)
```c
void DeleteMaxVal(int heapArray[], int num)
{
  int i;
  
  for (i = 0; i < heapSize; i++) {
    if (num == heapArray[i]) {
       break;
    }
  }
  // 🐛 BUG: Se elemento não existe, i == heapSize
  //     causando acesso a heapArray[heapSize] (fora dos limites!)
  SwapInt(&heapArray[i], &heapArray[heapSize - 1]);
  heapSize--;
  for (i = ((heapSize / 2) - 1); i >= 0; i--) {
      Heapfy(heapArray, heapSize, i);
  }
}
```

### ✅ CORRIGIDO (MaxHeap_CORRIGIDO.c - linhas 100-124)
```c
void DeleteValue(int heapArray[], int num)  // Nome mais apropriado
{
  int i;
  
  // Busca o elemento no heap
  for (i = 0; i < heapSize; i++) {
    if (num == heapArray[i]) {
       break;
    }
  }
  
  // ✅ CORREÇÃO: Validação adicionada
  if (i == heapSize) {
    printf("\nERRO: Elemento %d não encontrado no heap.\n", num);
    return;  // Retorna sem fazer nada se não encontrou
  }

  // Move último elemento para posição do removido
  SwapInt(&heapArray[i], &heapArray[heapSize - 1]);
  heapSize--;
  
  // Reconstrói o heap
  for (i = ((heapSize / 2) - 1); i >= 0; i--) {
      Heapfy(heapArray, heapSize, i);
  }
}
```

**Impacto**: Evita acesso a memória inválida e crash do programa.

---

## Bug #2: scanf - Buffer do Teclado

### ❌ ORIGINAL (MaxHeap.c - linha 187)
```c
scanf("%d",&key);      // Usuário digita: 42<ENTER>
printf("\n");
// ... algumas linhas depois ...
scanf("%c",&choice);   // 🐛 BUG: Lê o <ENTER> ao invés de esperar!
```

**Problema**: O `\n` (ENTER) do scanf anterior fica no buffer e é lido pelo segundo scanf, impedindo a entrada do usuário.

### ✅ CORRIGIDO (MaxHeap_CORRIGIDO.c - linha 255)
```c
scanf("%d", &key);        // Usuário digita: 42<ENTER>
printf("\n");
// ... algumas linhas depois ...
scanf(" %c", &choice);    // ✅ Espaço antes de %c ignora whitespace!
//     ↑ Este espaço faz toda a diferença!
```

**Impacto**: Usuário consegue inserir sua escolha corretamente.

---

## Bug #3: Insert - Verificação de Overflow

### ❌ ORIGINAL (MaxHeap.c - linhas 78-92)
```c
void Insert(int heapArray[], int newNum) {
  int i;
  
  if (heapSize == 0) {
    heapArray[0] = newNum;
    heapSize++;
  }
  else {
    // 🐛 BUG: Não verifica se heapSize < MAXIMUM_HEAP_SIZE
    //     Pode escrever além dos limites do array!
    heapArray[heapSize] = newNum;
    heapSize++;
    for (i = ((heapSize / 2) - 1); i >= 0; i--) {
        Heapfy(heapArray, heapSize, i);
    }
  }
}
```

### ✅ CORRIGIDO (MaxHeap_CORRIGIDO.c - linhas 76-96)
```c
void Insert(int heapArray[], int newNum) {
  // ✅ CORREÇÃO: Verificação de overflow adicionada
  if (heapSize >= MAXIMUM_HEAP_SIZE) {
    printf("\nERRO: Heap cheio! Capacidade máxima de %d elementos atingida.\n", 
           MAXIMUM_HEAP_SIZE);
    return;
  }
  
  // Insere no final
  heapArray[heapSize] = newNum;
  int i = heapSize;
  heapSize++;
  
  // ⚡ OTIMIZAÇÃO: Bubble up - O(log n) ao invés de O(n)
  while (i > 0) {
    int parent = PARENT(i);
    if (heapArray[i] <= heapArray[parent]) {
      break; // Propriedade do heap satisfeita
    }
    SwapInt(&heapArray[i], &heapArray[parent]);
    i = parent;
  }
}
```

**Impacto**: Evita buffer overflow e melhora performance de O(n) para O(log n).

---

## Melhoria #4: Heapfy - Mensagem Desnecessária

### ❌ ORIGINAL (MaxHeap.c - linhas 45-48)
```c
if (heapSize == 1) {
    // 🐛 PROBLEMA: Mensagem poluindo saída toda vez
    printf("Há apenas um elemento no heap e,\n");
    printf("por isso, não há necessidade de reorganizá-lo.\n");
}
```

### ✅ CORRIGIDO (MaxHeap_CORRIGIDO.c - linhas 48-51)
```c
// ✅ CORREÇÃO: Removida mensagem desnecessária
if (heapSize <= 1) {
    return; // Nada a fazer
}
```

**Impacto**: Saída limpa e profissional.

---

## Melhoria #5: Macros para Legibilidade

### ❌ ORIGINAL (MaxHeap.c - linhas 54-55)
```c
leftIndex  = 2 * i + 1;   // Números mágicos
rightIndex = 2 * i + 2;
```

### ✅ CORRIGIDO (MaxHeap_CORRIGIDO.c - linhas 24-26 e 56-57)
```c
// Definição das macros
#define LEFT_CHILD(i)  (2 * (i) + 1)
#define RIGHT_CHILD(i) (2 * (i) + 2)
#define PARENT(i)      (((i) - 1) / 2)

// Uso no código
leftIndex  = LEFT_CHILD(i);    // ✅ Muito mais claro!
rightIndex = RIGHT_CHILD(i);
```

**Impacto**: Código mais legível e manutenível.

---

## Melhoria #6: Tratamento de Erro do scanf

### ❌ ORIGINAL (MaxHeap.c - linha 179)
```c
scanf("%d",&key);  // 🐛 Não verifica retorno
printf("\n");      // Se usuário digitar "abc", comportamento indefinido
```

### ✅ CORRIGIDO (MaxHeap_CORRIGIDO.c - linhas 228-235)
```c
// ✅ CORREÇÃO: Verificação do retorno do scanf
scanf_result = scanf("%d", &key);
if (scanf_result != 1) {
  printf("\nERRO: Entrada inválida! Digite um número inteiro.\n\n");
  ClearInputBuffer();  // Limpa buffer
  continue;            // Pede nova entrada
}
printf("\n");
```

**Impacto**: Programa robusto contra entrada inválida.

---

## Nova Funcionalidade: DeleteMax

### ❌ ORIGINAL
Não existe função dedicada para remover o máximo (operação padrão de Max Heap).

### ✅ CORRIGIDO (MaxHeap_CORRIGIDO.c - linhas 126-144)
```c
// ✅ NOVA FUNÇÃO: Implementa operação padrão de Max Heap
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
```

**Impacto**: API mais completa e conforme especificação de Max Heap.

---

## Resumo das Diferenças

| # | Tipo | Original | Corrigido |
|---|------|----------|-----------|
| 1 | 🔴 Bug Crítico | DeleteMaxVal sem validação | ✅ DeleteValue com validação |
| 2 | 🔴 Bug Crítico | scanf buffer issue | ✅ scanf com espaço " %c" |
| 3 | 🔴 Bug Crítico | Insert sem verificação | ✅ Insert com verificação |
| 4 | 🟡 Performance | Insert O(n) | ✅ Insert O(log n) bubble-up |
| 5 | 🟡 Usabilidade | Mensagens em Heapfy | ✅ Sem mensagens |
| 6 | 🟡 Robustez | scanf sem tratamento | ✅ scanf com tratamento |
| 7 | 🟢 Legibilidade | Números mágicos | ✅ Macros descritivas |
| 8 | 🟢 Funcionalidade | Sem DeleteMax | ✅ DeleteMax dedicada |

---

## Como Usar Esta Comparação

1. **Para aprender**: Estude cada par de código lado a lado
2. **Para ensinar**: Use este documento em aulas de debugging
3. **Para revisar**: Use como checklist ao revisar código similar

---

**Conclusão**: A versão corrigida mantém toda a funcionalidade original enquanto elimina bugs críticos, melhora performance e adiciona robustez profissional ao código.
