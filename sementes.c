#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000001

typedef struct semente{ 
    int codigo;
    int nota;
} Semente;

int partition(Semente *c, int l, int r) {
    Semente pivo = c[r];
    
    int j = l;
    
    for(int i = l; i < r; i++) {
        if(c[i].nota <= pivo.nota) {
            if(c[i].nota == pivo.nota) {
                if(c[i].codigo < pivo.codigo) { 
                    Semente aux;
                    aux = c[i];
                    c[i] = c[j];
                    c[j] = aux;
                    j++;
                }
            }
            else { 
                Semente aux;
                aux = c[i];
                c[i] = c[j];
                c[j] = aux;
                j++;
            }
        }
    }
    
    Semente aux;
    aux = c[j];
    c[j] = c[r];
    c[r] = aux;
  
    return j; 
}

int median(Semente *c, int l, int r) {
    Semente aux;
    aux = c[(l+r)/2];
    c[(l+r)/2] = c[r];
    c[r] = aux;

    return partition(c, l, r);
}

void ecc(int i, Semente *c, int l, int r) {
    int med = median(c, l, r);
    if(med == i) {
        return;
    }
    if(med < i){
        ecc(i, c, med+1, r);
    }
    else {
        ecc(i, c, l, med-1);
    }
}

void mergeAB(Semente *c, Semente *a, int sizeA, Semente *b, int sizeB) {
    int i = 0, j = 0, k = 0;

    while(i < sizeA && j < sizeB) {
        if(a[i].codigo <= b[j].codigo) {
            c[k] = a[i];
            i++;
            k++;
        }
        else {
            c[k] = b[j];
            j++;
            k++;
        }
    }
    while(i < sizeA) {
        c[k] = a[i];
        i++;
        k++;
    }
    while(j < sizeB) {
        c[k] = b[j];
        j++;
        k++;
    }
}

void merge(Semente *arr, int l, int m, int r) {
    Semente *c = malloc(sizeof(Semente) * (r - l + 1));

    mergeAB(c, &arr[l], (m - l + 1), &arr[m + 1], (r - (m + 1) + 1));
    int k = 0, i = l;
    while(i <= r) {
        arr[i] = c[k];
        i++;
        k++;
    }

    free(c);
}

void mergesort(Semente *arr, int l, int r) {
    if(l == r) return;

    int m = (l + r) / 2;
    mergesort(arr, l, m);
    mergesort(arr, m+1, r);
    merge(arr, l, m, r);
}

int main() {
    int k;
    scanf("%d", &k);
    
    Semente *arr = malloc(sizeof(Semente) * 10000001);
    
    int size = 0;
    while(scanf("%d %d", &arr[size].codigo, &arr[size].nota) != EOF) {
        size++;
    } 
    
    ecc(k-1, arr, 0, size-1);
    mergesort(arr, 0, k-1);

    for(int i = 0; i < k; i++) {
        printf("%d %d\n", arr[i].codigo, arr[i].nota);
    }

    return 0;
}
