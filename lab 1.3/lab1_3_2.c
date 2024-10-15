#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <omp.h>

struct set {
    int min;
    int max;
    int64_t *values;
};

// Memory allocation for the set
struct set create_set(int min, int max) {
    struct set a;
    int blocks;
    a.min = min;
    a.max = max;
    blocks = (max - min + 1) / 64 + (((max - min + 1) % 64) && 1);
    a.values = calloc(blocks, sizeof(int64_t));
    return a;
}

// Adding a value to the set
void add_value(struct set *s, int value) {
    if ((value <= s->max) && (value >= s->min))
        s->values[(value - s->min) / 64] |= (0x8000000000000000 >> ((value - s->min) % 64));
    else
        fprintf(stderr, "Entered value is not within the range!\n");
}

// Filling the set with elements
void fill_set(struct set *s, int k) {
    size_t i = 0;
    int num;
    while (i < k) {
        scanf("%d", &num);
        if ((num <= s->max) && (num >= s->min)) {
            if (s->values[(num - s->min) / 64] & (0x8000000000000000 >> ((num - s->min) % 64)))
                fprintf(stderr, "This value has already been entered earlier!\n");
            else
                i++;
            add_value(s, num);
        }
    }
}

// Outputting the set
void output_set(struct set *s) {
    printf("{");
    int n = (s->max - s->min + 1) / 64 + (((s->max - s->min + 1) % 64) && 1);
    size_t mask, count;
    count = 0;
    #pragma omp parallel num_threads(4)
    #pragma omp for shared(mask) if (n > 5)
    for (size_t i = 0; i < n; i++) {
        mask = 0x8000000000000000;
        for (size_t j = 0; j < 64; j++) {
            if (s->values[i] & mask) {
                printf("%i, ", s->min + i * 64 + j);
                count++;
            }
            mask >>= 1;
        }
    }
    if (count) {
        printf("\b");
        printf("\b");
    }
    printf("}\n");
}

// Freeing memory occupied by the set
void del_set(struct set *s) {
    free(s->values);
}

// Complement of the set to the universe
struct set addition_set(struct set *s) {
    struct set r = create_set(s->min, s->max);
    int n = (r.max - r.min + 1) / 64 + (((r.max - r.min + 1) % 64) && 1);
    #pragma omp parallel num_threads(4)
    #pragma omp for shared(r) if (n > 100)
    for (size_t i = 0; i < n; i++)
        r.values[i] = ~s->values[i];
    size_t mask = 0x1;
    for (size_t i = 64; i > (r.max + 1) % 64; i--) {
        if (r.values[n - 1] & mask)
            r.values[n - 1] ^= mask;
        mask <<= 1;
    }
    return r;
}

// Union of two sets with the same universe
struct set union_set(struct set *s1, struct set *s2) {
    struct set r = create_set(s1->min, s1->max);
    int n = (r.max - r.min + 1) / 64 + (((r.max - r.min + 1) % 64) && 1);
    #pragma omp parallel num_threads(4)
    #pragma omp for shared(s1, s2, r) if (n > 100)
    for (size_t i = 0; i < n; i++)
        r.values[i] = s1->values[i] | s2->values[i];
    return r;
}

// Intersection of two sets with the same universe
struct set intersection_set(struct set *s1, struct set *s2) {
    struct set r = create_set(s1->min, s1->max);
    int n = (r.max - r.min + 1) / 64 + (((r.max - r.min + 1) % 64) && 1);
    #pragma omp parallel num_threads(4)
    #pragma omp for shared(s1, s2, r) if (n > 100)
    for (size_t i = 0; i < n; i++)
        r.values[i] = s1->values[i] & s2->values[i];
    return r;
}

// Symmetric difference of two sets with the same universe
struct set symm_diff_set(struct set *s1, struct set *s2) {
    struct set r = create_set(s1->min, s1->max);
    int n = (r.max - r.min + 1) / 64 + (((r.max - r.min + 1) % 64) && 1);
    #pragma omp parallel num_threads(4)
    #pragma omp for shared(s1, s2, r) if (n > 100)
    for (size_t i = 0; i < n; i++)
        r.values[i] = s1->values[i] ^ s2->values[i];
    return r;
}

// Difference of two sets with the same universe
struct set diff_set(struct set *s1, struct set *s2) {
    struct set r = create_set(s1->min, s1->max);
    int n = (r.max - r.min + 1) / 64 + (((r.max - r.min + 1) % 64) && 1);
    struct set t = addition_set(s2);
    r = intersection_set(s1, &t);
    return r;
}

// Checking if one set is included in another set (sets have the same universe)
int inclusion_set(struct set *s1, struct set *s2) {
    int i = 0;
    int n = (s1->max - s1->min + 1) / 64 + (((s1->max - s1->min + 1) % 64) && 1);
    while (i < n) {
        if ((s1->values[i] & s2->values[i]) != s1->values[i])
            return 0;
        i++;
    }
    return i;
}

// Checking equality of sets A and B
int equivalent_sets(struct set *s1, struct set *s2) {
    int i = 0;
    int n = (s1->max - s1->min + 1) / 64 + (((s1->max - s1->min + 1) % 64) && 1);
    while (i < n) {
        if (s1->values[i] != s2->values[i])
            return 0;
        i++;
    }
    return i;
}

// Solving set 3
struct set func_3(struct set *a, struct set *b, struct set *c) {
    struct set t_1 = create_set(a->min, a->max);
    struct set t_2 = create_set(a->min, a->max);
    struct set t_3 = create_set(a->min, a->max);
    struct set t_4 = create_set(a->min, a->max);
    struct set t_5 = create_set(a->min, a->max);
    struct set t_6 = create_set(a->min, a->max);
    struct set r = create_set(a->min, a->max);
    t_1 = diff_set(a, c);
    t_2 = diff_set(c, a);
    t_3 = diff_set(&t_2, b);
    t_4 = addition_set(&t_1);
    t_5 = addition_set(&t_3);
    t_6 = intersection_set(&t_4, &t_5);
    r = addition_set(&t_6);
    del_set(&t_1);
    del_set(&t_2);
    del_set(&t_3);
    del_set(&t_4);
    del_set(&t_5);
    del_set(&t_6);
    return r;
}

// Solving set 4
struct set func_4(struct set *a, struct set *b, struct set *c) {
    struct set t_1 = create_set(a->min, a->max);
    struct set t_2 = create_set(a->min, a->max);
    struct set t_3 = create_set(a->min, a->max);
    struct set t_4 = create_set(a->min, a->max);
    struct set t_5 = create_set(a->min, a->max);
    struct set t_6 = create_set(a->min, a->max);
    struct set r = create_set(a->min, a->max);
    t_1 = diff_set(a, c);
    t_2 = diff_set(c, b);
    t_3 = diff_set(a, b);
    t_4 = diff_set(&t_2, &t_3);
    t_5 = union_set(&t_1, &t_4);
    t_6 = addition_set(&t_5);
    r = addition_set(&t_6);
    del_set(&t_1);
    del_set(&t_2);
    del_set(&t_3);
    del_set(&t_4);
    del_set(&t_5);
    del_set(&t_6);
    return r;
}

// Program start
int main() {
    system("chcp 1251");
    system("cls");
    int max, min, k;
    struct set a, b, c, r_3, r_4;

    // Input sets
    printf("Enter the lower and upper bounds of sets A, B, and C:\n");
    printf("min = ");
    scanf("%i", &min);
    printf("max = ");
    scanf("%i", &max);
    a = create_set(min, max);
    b = create_set(min, max);
    c = create_set(min, max);

    printf("Enter the number of elements you want to input for set A:\n");
    printf("k_a = ");
    scanf("%i", &k);
    printf("Enter the values to be added to set A:\n");
    fill_set(&a, k);

    printf("Enter the number of elements you want to input for set B:\n");
    printf("k_b = ");
    scanf("%i", &k);
    printf("Enter the values to be added to set B:\n");
    fill_set(&b, k);

    printf("Enter the number of elements you want to input for set C:\n");
    printf("k_c = ");
    scanf("%i", &k);
    printf("Enter the values to be added to set C:\n");
    fill_set(&c, k);

    // Calculating values of set-theoretic expressions for given values
    r_3 = create_set(min, max);
    r_4 = create_set(min, max);
    r_3 = func_3(&a, &b, &c);
    r_4 = func_4(&a, &b, &c);

    // Output result
    if (equivalent_sets(&r_3, &r_4)) {
        printf("These sets are equal:\n");
        output_set(&r_3);
    } else {
        printf("These sets are not equal:\n");
        output_set(&r_3);
        output_set(&r_4);
    }
    printf("\n");

    del_set(&a);
    del_set(&b);
    del_set(&c);
    del_set(&r_3);
    del_set(&r_4);
    return 42;
}