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

sortset copy_sortset(sortset a)
{
    sortset res = create_sortset(a.size);
    for (size_t i = 0; i < a.n; ++i)
        append(&res, a.values[i]);
    return res;
}

sortset diff_sortsets(sortset a, sortset b)
{
    sortset res = create_sortset(a.size);
    int i = 0;
    int j = 0;
    while (i < a.n && j < b.n)
    {
        if (a.values[i] == b.values[j])
        {
            ++i;
            ++j;
        }
        else if (a.values[i] > b.values[j])
        {
            ++j;
        }
        else
        {
            append(&res, a.values[i]);
            ++i;
        }
    }

    while (i < a.n)
    {
        append(&res, a.values[i]);
        ++i;
    }

    return res;
}

sortset diff_sortset_with_value(sortset a, int value)
{
    sortset s_value = create_sortset(1);
    append(&s_value, value);
    return diff_sortsets(a, s_value);
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

void print_permutations_inner(sortset M, size_t i, sortset P, size_t* p_n)
{
    for (size_t x_i = 0; x_i < M.n; ++x_i) {
        P.values[i] = M.values[x_i];
        if (i == P.n - 1) {
            (*p_n)++; // increases the number of subsets by 1
            print_sortset(P);
        }
        else
            print_permutations_inner(diff_sortset_with_value(M, M.values[x_i]), i+1, P, p_n);
    }
}

// returns the number of subsets of set a, prints them
size_t print_permutations(sortset a)
{
    if (!a.n) {
        printf("{}\n");
        return 1;
    }

    sortset P = create_sortset(a.n);
    P.n = a.n;
    sortset M_first = copy_sortset(a);
    size_t res = 0;
    print_permutations_inner(M_first, 0, P, &res);
    delete_sortset(&P);
    delete_sortset(&M_first);
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
    printf("Permutations of set A:\n");
    size_t res = print_permutations(a);
    printf("Total permutations: %zu", res);
    delete_sortset(&a);
    return 0;
}
