#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <omp.h>

struct set{
    int min;
    int max;
    int64_t *values;
};

struct set create_set(int min, int max){
    struct set a;
    int blocks;
    a.min = min;
    a.max = max;
    blocks = (max - min + 1) / 64 + (((max - min + 1) % 64) && 1);
    a.values = calloc(blocks, sizeof(int64_t));
    return(a);
}

void add_value(struct set *s, int value){
    if ((value <= s->max) && (value >= s->min))
        s->values[(value - s->min) / 64] |= (0x8000000000000000 >> ((value - s->min) % 64));
    else
        fprintf(stderr, "Value out of range!\n");
}

void fill_set(struct set *s, int k){
    size_t i = 0;
    int num;
    while(i < k){
        scanf("%d", &num);
        if((num <= s->max) && (num >= s->min))
            if(s->values[(num - s->min) / 64] & (0x8000000000000000 >> ((num - s->min) % 64)))
                fprintf(stderr, "Duplicate value entered!\n");
            else i++;
        add_value(s, num);
    }
}

void output_set(struct set *s){
    printf("{");
    int n = (s->max - s->min + 1) / 64 + (((s->max - s->min + 1) % 64) && 1);
    size_t mask, count;
    count = 0;
    #pragma omp parallel omp_set_num_threads(4)
    #pragma omp parallel default(none) for shared(mask) if (n > 5)
    for(size_t i = 0; i < n; i++){
        mask = 0x8000000000000000;
        for(size_t j = 0; j < 64; j++){
            if(s->values[i] & mask){
                printf("%i, ", s->min + i * 64 + j);
                count++;
            }
            mask >>= 1;
        }
    }
    if(count){
        printf("\b");
        printf("\b");
    }
    printf("}\n");
}

void del_set(struct set *s){
    free(s->values);
}

struct set addition_set(struct set *s){
    struct set r;
    r = create_set(s->min, s->max);
    int n = (r.max - r.min + 1) / 64 + (((r.max - r.min + 1) % 64) && 1);
    #pragma omp parallel omp_set_num_threads(4);
    #pragma omp parallel default(none) for shared(r) if (n > 100)
    for(size_t i = 0; i < n; i++)
        r.values[i] = ~s->values[i];
    size_t mask = 0x1;
    for(size_t i = 64; i > (r.max) % 64; i--){
        if(r.values[n - 1] & mask)
            r.values[n - 1] ^= mask;
        mask <<= 1;
    }
    return(r);
}

struct set union_set(struct set *s1, struct set *s2){
    struct set r;
    r = create_set(s1->min, s1->max);
    int n = (r.max - r.min + 1) / 64 + (((r.max - r.min + 1) % 64) && 1);
    #pragma omp parallel omp_set_num_threads(4);
    #pragma omp parallel default(none) for shared(s1, s2, r) if (n > 100)
    for(size_t i = 0; i < n; i++)
        r.values[i] = s1->values[i] | s2->values[i];
    return(r);
}

struct set intersection_set(struct set *s1, struct set *s2){
    struct set r;
    r = create_set(s1->min, s1->max);
    int n = (r.max - r.min + 1) / 64 + (((r.max - r.min + 1) % 64) && 1);
    #pragma omp parallel omp_set_num_threads(4);
    #pragma omp parallel default(none) for shared(s1, s2, r) if (n > 100)
    for(size_t i = 0; i < n; i++)
        r.values[i] = s1->values[i] & s2->values[i];
    return(r);
}

struct set symm_diff_set(struct set *s1, struct set *s2){
    struct set r;
    r = create_set(s1->min, s1->max);
    int n = (r.max - r.min + 1) / 64 + (((r.max - r.min + 1) % 64) && 1);
    #pragma omp parallel omp_set_num_threads(4);
    #pragma omp parallel default(none) for shared(s1, s2, r) if (n > 100)
    for(size_t i = 0; i < n; i++)
        r.values[i] = s1->values[i] ^ s2->values[i];
    return(r);
}

struct set diff_set(struct set *s1, struct set *s2){
    struct set r, t;
    r = create_set(s1->min, s1->max);
    int n = (r.max - r.min + 1) / 64 + (((r.max - r.min + 1) % 64) && 1);
    t = addition_set(s2);
    r = intersection_set(s1, &t);
    return(r);
}

int inclusion_set(struct set *s1, struct set *s2){
    int i = 0;
    int n = (s1->max - s1->min + 1) / 64 + (((s1->max - s1->min + 1) % 64) && 1);
    while(i < n){
        if((s1->values[i] & s2->values[i]) != s1->values[i])
            return(0);
        i++;
    }
    return(i);
}

int equivalent_sets(struct set* s1, struct set* s2){
    int i = 0;
    int n = (s1->max - s1->min + 1) / 64 + (((s1->max - s1->min + 1) % 64) && 1);
    while(i < n){
        if((s1->values[i] != s2->values[i]))
            return(0);
        i++;
    }
    return(i);
}

// Finding Shannon's phi set by void
struct set phi_void(struct set* a, struct set* b, struct set* c) {
    struct set void_set = create_set(a->min, a->max);
    struct set not_b = create_set(a->min, a->max);
    struct set t_1 = create_set(a->min, a->max);
    struct set t_2 = create_set(a->min, a->max);
    struct set t_3 = create_set(a->min, a->max);
    struct set t_4 = create_set(a->min, a->max);
    struct set t_5 = create_set(a->min, a->max);
    struct set r = create_set(a->min, a->max);
    
    not_b = addition_set(b);
    t_1 = diff_set(&void_set, b);
    t_2 = intersection_set(a, &void_set);
    t_3 = union_set(&t_1, &t_2);
    t_4 = intersection_set(&void_set, &not_b);
    t_5 = diff_set(&t_4, c);
    r = symm_diff_set(&t_3, &t_5);

    del_set(&void_set);
    del_set(&not_b);
    del_set(&t_1);
    del_set(&t_2);
    del_set(&t_3);
    del_set(&t_4);
    del_set(&t_5);
    
    return r;
}

// Finding the negation of Shannon's phi set by the universe
struct set not_phi_uni(struct set* a, struct set* b, struct set* c) {
    struct set uni_set = create_set(a->min, a->max);
    struct set not_b = create_set(a->min, a->max);
    struct set t_1 = create_set(a->min, a->max);
    struct set t_2 = create_set(a->min, a->max);
    struct set t_3 = create_set(a->min, a->max);
    struct set t_4 = create_set(a->min, a->max);
    struct set t_5 = create_set(a->min, a->max);
    struct set t_6 = create_set(a->min, a->max);
    struct set r = create_set(a->min, a->max);

    uni_set = addition_set(&uni_set);
    not_b = addition_set(b);
    t_1 = diff_set(&uni_set, b);
    t_2 = intersection_set(a, &uni_set);
    t_3 = union_set(&t_1, &t_2);
    t_4 = intersection_set(&uni_set, &not_b);
    t_5 = diff_set(&t_4, c);
    t_6 = symm_diff_set(&t_3, &t_5);
    r = addition_set(&t_6);

    del_set(&uni_set);
    del_set(&not_b);
    del_set(&t_1);
    del_set(&t_2);
    del_set(&t_3);
    del_set(&t_4);
    del_set(&t_5);
    del_set(&t_6);
    
    return r;
}

// Checking the proposed solution of the equation
int is_solve(struct set* a, struct set* b, struct set* c, struct set* x) {
    struct set void_set = create_set(a->min, a->max);
    struct set not_b = create_set(a->min, a->max);
    struct set t_1 = create_set(a->min, a->max);
    struct set t_2 = create_set(a->min, a->max);
    struct set t_3 = create_set(a->min, a->max);
    struct set t_4 = create_set(a->min, a->max);
    struct set t_5 = create_set(a->min, a->max);
    struct set r = create_set(a->min, a->max);

    not_b = addition_set(b);
    t_1 = diff_set(x, b);
    t_2 = intersection_set(a, x);
    t_3 = union_set(&t_1, &t_2);
    t_4 = intersection_set(x, &not_b);
    t_5 = diff_set(&t_4, c);
    r = symm_diff_set(&t_3, &t_5);

    del_set(&not_b);
    del_set(&t_1);
    del_set(&t_2);
    del_set(&t_3);
    del_set(&t_4);
    del_set(&t_5);

    int t;
    t = equivalent_sets(&r, &void_set);

    del_set(&void_set);
    del_set(&r);
    
    return t;
}


int main() {
    int max, min, k;
    struct set a, b, c, phi_v, n_phi_u, x;
    
    // Input sets
    printf("Enter the lower and upper bounds for sets A, B, and C:\n");
    printf("min = ");
    scanf("%i", &min);
    printf("max = ");
    scanf("%i", &max);
    a = create_set(min, max);
    b = create_set(min, max);
    c = create_set(min, max);
    
    printf("Enter the number of elements you plan to input into set A:\n");
    printf("k_a = ");
    scanf("%i", &k);
    printf("Enter the values to be added to set A:\n");
    fill_set(&a, k);
    
    printf("Enter the number of elements you plan to input into set B:\n");
    printf("k_b = ");
    scanf("%i", &k);
    printf("Enter the values to be added to set B:\n");
    fill_set(&b, k);
    
    printf("Enter the number of elements you plan to input into set C:\n");
    printf("k_c = ");
    scanf("%i", &k);
    printf("Enter the values to be added to set C:\n");
    fill_set(&c, k);
    
    // Calculating values of set-theoretic expressions with given values
    phi_v = create_set(min, max);
    n_phi_u = create_set(min, max);
    phi_v = phi_void(&a, &b, &c);
    n_phi_u = not_phi_uni(&a, &b, &c);
    
    printf("The set phi of Shannon from the empty set and the negation of the set phi of Shannon from the universe:\n");
    output_set(&phi_v);
    output_set(&n_phi_u);
    
    // Input set X
    x = create_set(min, max);
    printf("Enter the number of elements you plan to input into set X:\n");
    printf("k_x = ");
    scanf("%i", &k);
    printf("Enter the values to be added to set X:\n");
    fill_set(&x, k);
    
    // Output result
    if(is_solve(&a, &b, &c, &x)) {
        printf("The set X is a solution to the set-theoretic equation.\n");
    } else {
        printf("The set X is not a solution to the set-theoretic equation.\n");
    }
    
    del_set(&a);
    del_set(&b);
    del_set(&c);
    del_set(&x);
    del_set(&phi_v);
    del_set(&n_phi_u);
    
    return 0;
}
