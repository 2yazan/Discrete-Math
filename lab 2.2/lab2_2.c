#include <stdio.h>

#define WHEEL_SIZE 9

// Function to check if the sums of numbers in each diameter of the wheel are equal.
int check_sums(int arr[]) {
    int sum_d1 = arr[0] + arr[4] + arr[8];
    int sum_d2 = arr[1] + arr[5] + arr[8]; 
    int sum_d3 = arr[2] + arr[6] + arr[8];
    int sum_d4 = arr[3] + arr[7] + arr[8]; 

    return (sum_d1 == sum_d2) && (sum_d2 == sum_d3) && (sum_d3 == sum_d4);
}

void print_wheel(int arr[], int *valid_count, int *invalid_count) {
    if (check_sums(arr)) {
        (*valid_count)++;
        printf("[ ");
        for (int i = 0; i < WHEEL_SIZE; i++) {
            printf("%d ", arr[i]);
        }
        printf("] ----> Equal sums\n");
    } else {
        (*invalid_count)++;
    }
}

// Function to swap two numbers.
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to generate all permutations of the array and check each one.
void generate_permutations(int *arr, int start, int end, int *total_count, int *valid_count, int *invalid_count) {
    if (start == end) {
        (*total_count)++;
        print_wheel(arr, valid_count, invalid_count);
        return;
    }
    
    for (int i = start; i <= end; i++) {
        swap(&arr[i], &arr[start]);
        generate_permutations(arr, start + 1, end, total_count, valid_count, invalid_count);
        swap(&arr[i], &arr[start]); 
    }
}

int main() {
    int arr[WHEEL_SIZE];
    int total_count = 0, valid_count = 0, invalid_count = 0;

    printf("Enter the numbers for the wheel (9 numbers):\n");

    for (int i = 0; i < WHEEL_SIZE; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("Invalid input! Please enter numbers only.\n");
            return 1;
        }
    }

    printf("Generating permutations and checking for equal sums across diameters...\n");

    generate_permutations(arr, 0, WHEEL_SIZE - 1, &total_count, &valid_count, &invalid_count);

    printf("\nSummary:\n");
    printf("Total arrangements: %d\n", total_count);
    printf("Valid arrangements (equal sums): %d\n", valid_count);
    printf("Invalid arrangements (unequal sums): %d\n", invalid_count);

    return 0;
}
