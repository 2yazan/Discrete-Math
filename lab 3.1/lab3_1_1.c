#include <stdio.h>
#define n 11

// Union
void Union(int A[n][n], int B[n][n], int C[n][n]) {
    for (int x = 1; x < n; x++) {
        for (int y = 1; y < n; y++) {
            C[x][y] = A[x][y] || B[x][y];
        }
    }
}

// Intersection
void Intersection(int A[n][n], int B[n][n], int C[n][n]) {
    for (int x = 1; x < n; x++) {
        for (int y = 1; y < n; y++) {
            C[x][y] = A[x][y] && B[x][y];
        }
    }
}

// Difference
void Difference(int A[n][n], int B[n][n], int C[n][n]) {
    for (int x = 1; x < n; x++) {
        for (int y = 1; y < n; y++) {
            C[x][y] = A[x][y] > B[x][y];
        }
    }
}

// Symmetric Difference
void Symmetric_Difference(int A[n][n], int B[n][n], int C[n][n]) {
    for (int x = 1; x < n; x++) {
        for (int y = 1; y < n; y++) {
            C[x][y] = (!A[x][y] && B[x][y]) || (A[x][y] && !B[x][y]);
        }
    }
}

// Complement A
void Complement(int A[n][n], int C[n][n]) {
    for (int x = 1; x < n; x++) {
        for (int y = 1; y < n; y++) {
            C[x][y] = !A[x][y];
        }
    }
}

// Inverse A
void Inverse(int A[n][n], int C[n][n]) {
    for (int x = 1; x < n; x++) {
        for (int y = 1; y < n; y++) {
            C[x][y] = A[y][x];
        }
    }
}

// Equality
int Equality(int A[n][n], int B[n][n]) {
    int r = 1;
    for (int x = 1; x < n && r == 1; x++) {
        for (int y = 1; y < n && r == 1; y++) {
            r = A[x][y] == B[x][y];
        }
    }
    return r;
}

// Inclusion
int Inclusion(int A[n][n], int B[n][n]) {
    int r = 1;
    for (int x = 1; x < n && r == 1; x++) {
        for (int y = 1; y < n && r == 1; y++) {
            r = A[x][y] <= B[x][y];
        }
    }
    return r;
}

// Composition (superposition or multiplication)
void Composition(int A[n][n], int B[n][n], int C[n][n]) {
    for (int x = 1; x < n; x++) {
        for (int y = 1; y < n; y++) {
            C[x][y] = 0;
            for (int z = 1; z < n; z++) {
                C[x][y] = C[x][y] || (A[x][z] && B[z][y]);
            }
        }
    }
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

void Print_Relation(int A[n][n]) {
    for (int x = 1; x < n; x++) {
        for (int y = 1; y < n; y++) {
            printf("%d ", A[x][y]);
        }
        printf("\n");
    }
}

void Equal0(int A[n][n]) {
    for (int x = 1; x < n; x++) {
        for (int y = 1; y < n; y++) {
            A[x][y] = 0;
        }
    }
}

int main() {
    int A[n][n];
    int B[n][n];
    int C[n][n];
    int D[n][n];
    int R1[n][n];
    int R2[n][n];
    int R3[n][n];
    int R4[n][n];
    Equal0(A);
    Equal0(B);
    Equal0(C);
    ResultA(A);
    ResultB(B);
    ResultC(C);
    printf("A = \n");
    ResultA(A);
    Print_Relation(A);
    printf("________________________________________________________________\n");
    printf("B = \n");
    ResultB(B);
    Print_Relation(B);
    printf("________________________________________________________________\n");
    printf("C = \n");
    ResultC(C);
    Print_Relation(C);
    printf("________________________________________________________________\n");
    printf("A^-1 = \n");
    Inverse(A,R1);
    Print_Relation(R1);
    printf("________________________________________________________________\n");
    printf("~A = \n");
    Complement(A,R2);
    Print_Relation(R2);
    printf("_________________________________________________________________\n");
    printf("A^-1 ∩ B  = \n");
    Intersection(R1,B,R3);
    Print_Relation(R3);
    printf("________________________________________________________________\n");
    printf("A^-1 ∩ B ∪ ~A = \n");
    Union(R3,R2,R4);
    Print_Relation(R4);
    printf("________________________________________________________________\n");
    printf("D = A^-1 ∩ B ∪ ~A - C = \n");
    Difference(R4,C,D);
    Print_Relation(D);
    return 0;
}