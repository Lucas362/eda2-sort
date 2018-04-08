#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void createVector(int *vector, int size){
    int i,range;

    printf("Range do vetor: ");
    scanf("%d", &range);

    srand((unsigned)time(NULL));
    for (i = 0; i < size; i++){
        /* gerando valores aleatórios entre zero e o range */
        vector[i] = (rand() % (range));
        printf("%d\n", vector[i]);
    }
    puts("====Vetor gerado com sucesso====");
}

void showVector(int vector[], int size){
    int i;
    puts("====Inicio Vetor");
    for (i = 0; i < size; i++){
        printf("%d\n", vector[i]);
    }
    puts("====Fim Vetor");
}

double heapSort(int vector[], int size) {
   int i = size / 2, pai, filho, t;
   int v2[size];
   /* Cópia do vetor para não interferir com a outra ordenação */
   for(i = 0; i < size; i++){
       v2[i] = vector[i];
   }
   clock_t ti = clock();
   while(1) {
      if (i > 0) {
          i--;
          t = v2[i];
      } else {
          size--;
          if (size == 0){
              return (double)(clock()-ti)/CLOCKS_PER_SEC;
          }
          t = v2[size];
          v2[size] = v2[0];
      }
      pai = i;
      filho = i * 2 + 1;
      while (filho < size) {
          if ((filho + 1 < size)  &&  (v2[filho + 1] > v2[filho]))
              filho++;
          if (v2[filho] > t) {
             v2[pai] = v2[filho];
             pai = filho;
             filho = pai * 2 + 1;
          } else {
             break;
          }
      }
      v2[pai] = t;
   }
}

double quickSort(int vector[], int begin, int end){
  int i, j, pivot, aux;
  i = begin;
  j = end;
  int v2[end];
  /* Cópia do vetor para não interferir com a outra ordenação */
  for(i = 0; i < end; i++){
      v2[i] = vector[i];
  }

  clock_t ti = clock();
  pivot = v2[(i+j)/2];
  while(i <= j){
    while(v2[i] < pivot && i < end){
      i++;
    }
    while(v2[j] > pivot && j > begin){
      j--;
    }
    if(i <= j){
      aux = v2[i];
      v2[i] = v2[j];
      v2[j] = aux;
      i++;
      j--;
    }
  }
  if(j > begin){
    quickSort(v2, begin, j);
  }
  if(i < end){
    quickSort(v2, i, end);
  }
  return (double)(clock()-ti)/CLOCKS_PER_SEC;
}

void menu(){
    puts("1 - Gerar novo vetor");
    puts("2 - Fazer sort (Merge Sort)");
    puts("3 - Fazer sort (Quick Sort)");
    puts("4 - Printar vetor desordenado");
    puts("0 - Sair");
}

int main(){
    int *vector;
    int size=0, op;
    do{
        menu();
        scanf("%d", &op);
        switch (op) {
            case 1:
                printf("Tamanho do vetor: ");
                scanf("%d", &size);
                vector = (int *) malloc(size * sizeof(int));
                createVector(vector, size);
                break;
            case 2:
                size>0 ? printf("====Tempo gasto %lfs====\n\n",
                    heapSort(vector, size)) :
                 printf("Vetor nao inicializado\n");
                break;
            case 3:
                size>0 ? printf("====Tempo gasto %lfs====\n\n",
                    quickSort(vector, 0, size)) :
                 printf("Vetor nao inicializado\n");
                break;
            case 4:
                size>0 ? showVector(vector, size) :
                 printf("Vetor nao inicializado\n");
        }
    }while (op != 0);
    return 0;
}
