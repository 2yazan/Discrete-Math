#include <stdio.h>
#define n 11

// reflexivity
int Reflexive(int A[n][n]){
    int r = 1;
    for (int i = 1; i < n && r==1; i++) {
        r = A[i][i];
    }
    return r;
}

// anti-reflexivity
int AntiReflexive(int A[n][n]){
    int r = 1;
    for (int i = 1; i < n; i++) {
        r =!A[i][i];
    }
    return !r;
}

// symmetry
int Symmetric(int A[n][n]){
    int r = 1;
    for (int i = 1; i < n && r==1; i++) {
        for (int j = 1; j < n && r==1; j++) {
            r = A[i][j] == A[j][i];
        }
    }
    return r;
}

// anti-symmetry
int AntiSymmetric(int A[n][n]){
    int r=1;
    for (int i = 1; i <n && r==1; i++) {
        for (int j = 1; j < n && r==1; j++) {
            if (A[i][j] == 1)
                r = !A[j][i];
        }
    }
    return r;
}

// transitivity
int Transitive(int A[n][n]){
    int r = 1;
    for (int i = 1; i < n && r==1; i++) {
        for (int j = 1; j < n && r==1; j++) {
            for (int k = 1; k < n && r==1; k++) {
                if(A[i][j] && A[j][k])
                    r=(A[i][k]==1);
            }
        }
    }
    return r;
}

// anti-transitivity
int AntiTransitive(int A[n][n]){
    int r = 1;
    for (int i = 1; i < n && r==1; i++) {
        for (int j = 1; j < n && r==1; j++) {
            for (int k = 1; k < n && r==1; k++) {
                if(A[i][j] && A[j][k])
                    r=!(A[i][k]==1);
            }
        }
    }
    return r;
}

// completeness
int Dence(int A[n][n]){
    int r=1;
    for (int i = 1; i < n && r==1; i++) {
        for (int j = 1; j < n && r==1; j++) {
            r = (A[i][j] == 1) || (A[j][i] == 1);
        }
    }
    return r;
}

// tolerance
int Tolerance(int A[n][n]){
    int r = (Reflexive(A) == 1) && (Symmetric(A) == 1);
    return r;
}

// equivalence
int Equivalence(int A[n][n]){
    int r = (Tolerance(A) == 1) && (Transitive(A) == 1);
    return r;
}

// order
int Order(int A[n][n]){
    int r = (AntiSymmetric(A) == 1) && (Transitive(A) == 1);
    return r;
}

// Formation of relation matrix A
void ResultA(int A[n][n]) {
    for (int x = 1; x < n; x++) {
        for (int y = 1; y < n; y++) {
            if ((x%2==0) && y>x)
                A[x][y] = 1;
        }
    }
}

// Formation of relation matrix B
void ResultB(int B[n][n]) {
    for (int x = 1; x < n; x++) {
        for (int y = 1; y < n; y++) {
            if (x-y==1 || x+y==11)
                B[x][y] = 1;
        }
    }
}

// Formation of relation matrix C
void ResultC(int C[n][n]) {
    int Cx[5]={2,5,8,9,10},Cy[4]={1,3,5,10};
    for (int x = 0; x < 5; x++) {
        for (int y = 0; y < 4; y++) {
            C[Cx[x]][Cy[y]]=1;
        }
    }
}

void Equal0(int A[n][n]) {
    for (int x = 1; x < n; x++) {
        for (int y = 1; y < n; y++) {
            A[x][y] = 0;
        }
    }
}

void Check(int A[n][n]){
    if(Reflexive(A)==1)
        printf("R is reflexive\n");
    if(AntiReflexive(A)!=1)
        printf("R is anti-reflexive\n");
    if(Symmetric(A)==1)
        printf("R is symmetric\n");
    if(AntiSymmetric(A)==1)
        printf("R is anti-symmetric\n");
    if(Transitive(A)==1)
        printf("R is transitive\n");
    if(AntiTransitive(A)==1)
        printf("R is anti-transitive\n");
    if(Dence(A)==1)
        printf("R is complete\n");
    if(Tolerance(A)==1)
        printf("R is tolerant\n");
    if(Equivalence(A)==1)
        printf("R is equivalent\n");
    if(Order(A)==1)
        printf("R is ordered\n");
}

int main(){
    int A[n][n];
    int B[n][n];
    int C[n][n];
    Equal0(A);
    Equal0(B);
    Equal0(C);
    ResultA(A);
    ResultB(B);
    ResultC(C);
    printf("________________________________________________________________\n");
    Check(A);
    printf("________________________________________________________________\n");
    Check(B);
    printf("________________________________________________________________\n");
    Check(C);
    return 0;
}
