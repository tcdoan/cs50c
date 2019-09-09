#include <stdio.h>

void merge(int a[], int aux[], int lo, int mid, int hi);
void sort(int a[], int aux[], int lo, int hi);
#define N 8
int main()
{
    // in-place merge
    int a[] = {8, 7, 5, 6, 3, 5, 4, 10};
    int aux[N];
    sort(a, aux, 0, N-1);
    for (int i = 0; i < N; i++)
    {
        printf("%d ", a[i]);
    }
}

void merge(int a[], int aux[], int lo, int mid, int hi)
{
    for (int i = lo; i <= hi; i++)
    {
        aux[i] = a[i];
    }

    int i = lo;
    int j = mid + 1;

    for (int k = lo; k <= hi; k++)
    {
        if (i > mid)
        {
            a[k] = aux[j++];
        }
        else if (j > hi)
        {
            a[k] = aux[i++];
        }
        else if (aux[i] <= aux[j])
        {
            a[k] = aux[i++];
        }
        else 
        {
            a[k] = aux[j++];
        }
    }
}

void sort(int a[], int aux[], int lo, int hi)
{
    if (lo >= hi)
    {
        return;
    }
    int mid = (lo + hi) / 2;
    sort(a, aux, lo, mid);
    sort(a, aux, mid + 1, hi);
    merge(a, aux, lo, mid, hi);
}