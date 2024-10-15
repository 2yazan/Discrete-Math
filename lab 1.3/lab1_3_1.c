#include <stdio.h>
#include <stdlib.h>

struct table {
    int size;
    int* a;
    int* b;
};

int diff(int v_1, int v_2) {
    return (v_1 & (~v_2));
}

void log_func_2(struct table* t) {
    int a, b, c;
    for (int i = 0; i < t->size; i++) {
        a = (1 << 2 & i) >> 2;
        b = (1 << 1 & i) >> 1;
        c = 1 & i;
        t->a[i] = diff(a, c) | diff(diff(c, a), b);
    }
}

void log_func_4(struct table* t) {
    int a, b, c;
    for (int i = 0; i < t->size; i++) {
        a = (1 << 2 & i) >> 2;
        b = (1 << 1 & i) >> 1;
        c = 1 & i;
        t->b[i] = ~(~(diff(a, c) | diff(diff(c, b), diff(a, b))));
    }
}

int a_equivalent_b(struct table* t) {
    int i = 0;
    int flag = 1;
    while ((i < t->size) && (flag)) {
        flag = (t->a[i] == t->b[i]);
        i++;
    }
    return (flag);
}

void print_table(struct table* t) {
    printf("|A|B|C|expression_2|expression_4|\n");
    printf("---------------------------------\n");
    for (int i = 0; i < t->size; i++) {
        printf("|%d|%d|%d| %d | %d |\n", ((1 << 2 & i) >> 2), ((1 << 1 & i) >> 1), (1 & i), t->a[i], t->b[i]);
    }
    printf("---------------------------------\n");
}

int main() {
    struct table t;
    t.size = 8;
    t.a = malloc(t.size * sizeof(int));
    t.b = malloc(t.size * sizeof(int));
    
    log_func_2(&t);
    log_func_4(&t);
    
    printf("Truth table for the given logical functions:\n");
    print_table(&t);
    
    if (a_equivalent_b(&t)) {
        printf("The truth tables of the given logical expressions are equal -> they are equivalent.");
    } else {
        printf("The truth tables of the given logical expressions are not equal -> they are not equivalent.");
    }
    
    return 0;
}
