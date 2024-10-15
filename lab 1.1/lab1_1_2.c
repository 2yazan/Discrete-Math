#include <stdio.h>
#include <malloc.h>

typedef struct
{
    int* values;
    int n;
    int size;
} sortset;

sortset create_sortset(int size)
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
void append_values(sortset* p_a, int n)
{
    for (int i = 0; i < n; ++i)
    {
        int value;
        scanf("%i", &value);
        append(p_a, value);
    }
}
void output_sortset(sortset a)
{
    for (int i = 0; i < a.n; ++i)
        printf("%i ", a.values[i]);
}
char is_in_set(sortset a, int value)
{
    int i = 0;
    while (i < a.n && a.values[i] <= value)
    {
        if (a.values[i] == value) return 1;
        ++i;
    }
    return 0;
}
char is_equal(sortset a, sortset b)
{
    if (a.n != b.n) return 0;
    for (int i = 0; i < a.n; ++i)
        if (a.values[i] != b.values[i])
            return 0;
    return 1;
}
char is_subset(sortset a, sortset b)
{
    if (a.n > b.n || a.values[0] > b.values[0]) return 0;
    int i = 0;
    int j = 0;
    while (i < a.n && j < b.n)
    {
        if (a.values[i] = b.values[j])
        {
            ++i;
            ++j;
        }
        else if (a.values[i] > b.values[j])
            ++j;
        else return 0;
    }
    return (i == a.n);
}
sortset union_sortsets(sortset a, sortset b)
{
    sortset res = create_sortset(a.size + b.size);
    int i = 0;
    int j = 0;
    while (i < a.n && j < b.n)
    {
        if (a.values[i] == b.values[j])
        {
            append(&res, a.values[i]);
            ++i;
            ++j;
        }
        else if (a.values[i] > b.values[j])
        {
            append(&res,b.values[j]);
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
    while (j < b.n)
    {
        append(&res, b.values[j]);
        ++j;
    }
    return res;
}
sortset intersec_sortsets(sortset a, sortset b)
{
    sortset res = create_sortset(a.size);
    int i = 0;
    int j = 0;
    while (i < a.n && j < b.n)
    {
        if (a.values[i] == b.values[j])
        {
            append(&res, a.values[i]);
            ++i;
            ++j;
        }
        else if (a.values[i] > b.values[j])
        {
            ++j;
        }
        else
        {
            ++i;
        }
    }
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
sortset symdiff_sortsets(sortset a, sortset b)
{
    sortset res = create_sortset(a.size + b.size);
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
            append(&res, b.values[j]);
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
    while (j < b.n)
    {
        append(&res, b.values[j]);
        ++j;
    }
    return res;
}
sortset compl_sortset(sortset a, int min, int max)
{
    sortset res = create_sortset(max-min+1);
    int u = min;
    int j = 0;
    while (u <= max && j < a.n)
    {
        if (u == a.values[j])
        {
            ++u;
            ++j;
        }
        else if (u > a.values[j])
        {
            ++j;
        }
        else
        {
            append(&res, u);
            ++u;
        }
    }
    while (u <= max)
    {
        append(&res, u);
        ++u;
    }
    return res;
}

int main()
{
    printf("Task 1:\n");
    int n, m, k;
    printf("Enter the size of set A: ");
    scanf("%i", &n);
    sortset a = create_sortset(n);
    printf("Enter the ordered set A:\n");
    append_values(&a, a.size);
    printf("Enter the size of set B: ");
    scanf("%i", &m);
    sortset b = create_sortset(m);
    printf("Enter the ordered set B:\n");
    append_values(&b, b.size);
    printf("Enter the size of set C: ");
    scanf("%i", &k);
    sortset c = create_sortset(k);
    printf("Enter the ordered set C:\n");
    append_values(&c, c.size);
    sortset step1 = symdiff_sortsets(a, b);
    sortset step2 = diff_sortsets(step1, c);
    sortset step3 = diff_sortsets(c, step1);
    sortset step4 = union_sortsets(step2, step3);

    printf("The desired set:\n");
    output_sortset(step4);
    delete_sortset(&a);
    delete_sortset(&b);
    delete_sortset(&c);
    delete_sortset(&step1);
    delete_sortset(&step2);
    delete_sortset(&step3);
    delete_sortset(&step4);

    printf("\n\nTask two:\n");
    printf("Enter the size of set A: ");
    scanf("%i", &n);
    a = create_sortset(n);
    printf("Enter set A:\n");
    append_values(&a, n);
    printf("Enter the size of set B: ");
    scanf("%i", &m);
    b = create_sortset(m);
    printf("Enter set B:\n");
    append_values(&b, m);
    printf("Enter the size of set C: ");
    scanf("%i", &k);
    c = create_sortset(k);
    printf("Enter set C:\n");
    append_values(&c, k);
    int d_size;
    printf("Enter the size of set D: ");
    scanf("%i", &d_size);
    sortset d = create_sortset(d_size);
    printf("Enter set D:\n");
    append_values(&d, d_size);
    step1 = diff_sortsets(c, a);
    step2 = diff_sortsets(b, c);
    step3 = union_sortsets(step1, step2);
    printf("Result of the obtained expression:\n");
    output_sortset(step3);
    printf("\nSet D:\n");
    output_sortset(d);
    if (is_equal(step2, d))

        printf("\nThe values matched!");
    else
        printf("\nThe values did not match!");

    delete_sortset(&a);
    delete_sortset(&b);
    delete_sortset(&c);
    delete_sortset(&d);
    delete_sortset(&step1);
    delete_sortset(&step2);
    delete_sortset(&step3);
    return 0;
}
