#include <stdio.h>
#include <stdint.h>
#include <malloc.h>

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
    for (size_t i = 0; i < a.n; ++i)
        printf("%i ", a.values[i]);
}

void print_by_vect(sortset a, uint8_t* vect)
{
    printf("{");
    uint8_t f_to_clear = 0; // for nice output
    for (size_t i = 0; i < a.n; ++i)
        if (vect[i]) {
            f_to_clear = 1;
            printf("%i, ", a.values[i]);
        }
    if (f_to_clear)
        printf("\b\b");
    printf("}\n");
}

void print_subsets_inner(sortset a, size_t i, uint8_t* vect, size_t* p_n)
{
    if (!a.n) {
        (*p_n) = 1;
        printf("{}\n");
        return;
    }

    for (uint8_t x = 0; x <= 1; ++x) {
        vect[i] = x;
        if (i == a.n - 1) {
            (*p_n)++; // increases the number of subsets by 1
            print_by_vect(a, vect);
        }
        else
            print_subsets_inner(a, i + 1, vect, p_n);
    }
}

// returns the number of subsets of set a and prints them
size_t print_subsets(sortset a)
{
    uint8_t* vect = (uint8_t*)malloc(a.size);
    size_t res = 0;
    print_subsets_inner(a, 0, vect, &res);
    free(vect);
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
    printf("Subsets of set A:\n");
    size_t n = print_subsets(a);
    printf("Total subsets: %zu", n);
    return 0;
}
