#include <stdio.h>
#include <windows.h>

/* returns 1 if there is an element with the value in the array a of size n,
otherwise 0 */
int is_in_set(int *a, int n, int value){
    int i;
    for(i = 0; i < n; ++i)
        if(a[i] == value)
            return 1;
    return 0;
}

/* performs the union operation of sets a of size n and b of size m,
writes the result in the array res,
returns the size of the array res */
int union_sets(int *a, int *b, int n, int m, int *res){
    int i;
    for(i = 0; i < n; ++i)
        res[i] = a[i];
    int c = n;
    for(i = 0; i < m; ++i)
        if(!is_in_set(a, n, b[i])){
            res[c] = b[i];
            ++c;
        }
    return c;
}

/* performs the intersection operation of sets a of size n and b of size m,
writes the result in the array res,
returns the size of the array res */
int intersec_sets(int *a, int *b, int n, int m, int *res){
    int c = 0;
    int i;
    for(i = 0; i < n; ++i)
        if(is_in_set(b, m, a[i])){
            res[c] = a[i];
            ++c;
        }
    return c;
}

/* finds the complement of set a of size n in the universal set with boundaries min and max,
writes the result in the array res,
returns the size of the array res */
int comp_set(int *a, int n, int min, int max, int *res){
    int c = 0;
    int i;
    for(i = min; i <= max; ++i)
        if(!is_in_set(a, n, i)){
            res[c] = i;
            ++c;
        }
    return c;
}

/* performs the difference operation of sets a of size n and b of size m,
writes the result in the array res,
returns the size of the array res */
int diff_sets(int *a, int *b, int n, int m, int *res){
    int c = 0;
    int i;
    for(i = 0; i < n; ++i)
        if(!is_in_set(b, m, a[i])){
            res[c] = a[i];
            ++c;
        }
    return c;
}

/* performs the symmetric difference operation
of sets a of size n and b of size m,
writes the result in the array res,
returns the size of the array res */
int symm_diff_sets(int *a, int *b, int n, int m, int *res){
    int c = diff_sets(a, b, n, m, res);
    int t = diff_sets(b, a, m, n, res+c);
    return c+t;
}

/* returns 1 if set a of size n
is a subset of set b of size m,
otherwise 0 */
int is_subset(int *a, int *b, int n, int m){
    int i;
    for(i = 0; i < n; ++i){
        if(!is_in_set(b, m, a[i])) return 0;
    }
    return 1;
}

/* returns 1 if set a of size n is equal to set b of size m,
otherwise 0 */
int is_equal(int *a, int *b, int n, int m){
    if(is_subset(a, b, n, m) && is_subset(b, a, m, n))
        return 1;
    else
        return 0;
}

void input_arr(int *a, int n){
    int i;
    for(i = 0; i < n; ++i)
        scanf("%i", &a[i]);
}

void output_arr(int *a, int n){
    int i;
    for(i = 0; i < n; ++i)
        printf("%i ", a[i]);
}

int main(){
    SetConsoleOutputCP(CP_UTF8);// Connect Russian language
    printf("Task one:\n");
    int n, m, k;
    printf("Enter the size of set A: ");
    scanf("%d", &n);
    int *a = calloc(n, sizeof(int));
    printf("Enter set A:\n");
    input_arr(a, n);
    printf("Enter the size of set B: ");
    scanf("%d", &m);
    int *b = calloc(m, sizeof(int));
    printf("Enter set B:\n");
    input_arr(b, m);
    printf("Enter the size of set C: ");
    scanf("%d", &k);
    int *c = calloc(k, sizeof(int));
    printf("Enter set C:\n");
    input_arr(c, k);

    int *step1, *step2, *step3, *step4;
    step1 = malloc(sizeof(int));
    step2 = malloc(sizeof(int));
    step3 = malloc(sizeof(int));
    step4 = malloc(sizeof(int));
    int size1, size2, size3, size4;

    size1 = symm_diff_sets(a,b,n,m,step1);
    size2 = diff_sets(step1,c,size1,k,step2);
    size3 = diff_sets(c,step1,k,size1,step3);
    size4 = union_sets(step2,step3,size2,size3,step4);
    printf("The resulting set:\n");
    output_arr(step4, size4);

    printf("\n\nTask two:\n");
    printf("Enter the size of set A: ");
    scanf("%d", &n);
    printf("Enter set A:\n");
    input_arr(a, n);
    printf("Enter the size of set B: ");
    scanf("%d", &m);
    printf("Enter set B:\n");
    input_arr(b, m);
    printf("Enter the size of set C: ");
    scanf("%d", &k);
    printf("Enter set C:\n");
    input_arr(c, k);
    printf("Enter the size of set D: ");
    int size_res;
    scanf("%d", &size_res);
    int d[20];
    printf("Enter set D:\n");
    input_arr(d, size_res);

    size1 = diff_sets(c,a,k,n,step1);
    size2 = diff_sets(b,c,m,k,step2);
    size3 = union_sets(step1,step2,size1,size2,step3);
    printf("Result of the obtained expression:\n");
    output_arr(step3, size3);
    printf("\nSet D:\n");
    output_arr(d, size_res);
    if(is_equal(step3, d, size3, size_res))
        printf("\nValues matched!");
    else
        printf("\nValues did not match!");
    return 0;
}
