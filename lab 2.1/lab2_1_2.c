#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include <locale.h>

typedef struct
{
    int* values;
    size_t n;
    size_t size;
} sortset;

sortset create_sortset(size_t size)
{
    sortset res;
    res.n = 0;
    res.size = size;
    res.values = (int*)malloc(size * sizeof(int));
    return res;
}

void delete_sortset(sortset* p_a)
{
    free(p_a->values);
}

void append(sortset* p_a, int value)
{
    if (p_a->n == p_a->size)
    {
        p_a->size *= 2;
        p_a->values = (int*)realloc(p_a->values, p_a->size * sizeof(int));
    }
    (p_a->values)[p_a->n] = value;
    ++(p_a->n);
}

void append_values(sortset* p_a, size_t n)
{
    for (size_t i = 0; i < n; ++i)
    {
        int value;
        scanf("%i", &value);
        append(p_a, value);
    }
}

void print_sortset(sortset a)
{
    if (!a.n) {
        printf("{}");
        return;
    }
    printf("{");
    for (size_t i = 0; i < a.n; ++i)
        printf("%i, ", a.values[i]);
    printf("\b\b}\n");
}

void print_combinations_inner(size_t i, size_t b_i, sortset a, // b_i - index of the minimum element
                                size_t k, sortset C, size_t* p_n)
{
    for (size_t x_i = b_i; x_i <= a.n - k + i; ++x_i) {
        C.values[i] = a.values[x_i];
        if (i == k-1) {
            (*p_n)++; // increases the number of subsets by 1
            print_sortset(C);
        }
        else
            print_combinations_inner(i + 1, x_i + 1, a, k, C, p_n);
    }
}

// returns the number of subsets of set a, prints them
size_t print_combinations(sortset a, size_t k)
{
    if (!k) {
        printf("{}\n");
        return 1;
    }
    sortset C = create_sortset(k);
    C.n = k;
    size_t res = 0;
    print_combinations_inner(0, 0, a, k, C, &res);
    delete_sortset(&C);
    return res;
}

int main()
{
    printf("Enter the size of set A: ");
    size_t size;
    scanf("%zu", &size);
    printf("Enter set A:\n");
    sortset a = create_sortset(size);
    append_values(&a, size);
    for (size_t i = 0; i <= size; ++i) {
        printf("Combinations of set A of size %zu:\n", i);
        size_t n = print_combinations(a, i);
        printf("Total combinations of set A of size %zu: %zu\n\n", i, n);
    }
    delete_sortset(&a);
    return 0;
}
