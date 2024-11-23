// read_input.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calc.h"

float load_ans() {
    FILE *file = fopen("ans.txt", "r");
    float ans = 0;
    if (file) {
        fscanf(file, "%f", &ans);
        fclose(file);
    }
    return ans;
}

void save_ans(float ans) {
    FILE *file = fopen("ans.txt", "w");
    if (file) {
        fprintf(file, "%f", ans);
        fclose(file);
    }
}

void wait_and_clear_screen() {
    printf("Press any key to continue...\n");
    getchar();
    system("clear");
}

int main() {
    float a, b, result;
    char operator;
    char input[20];
    char isAns[10];

    while (1) {
        printf("Nhap phep tinh hoac EXIT de thoat: ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("SYNTAX ERROR\n");
            continue;
        }

        if (strncmp(input, "EXIT", 4) == 0) {
            break;
        }

        if (sscanf(input, "%9s %c %f", isAns, &operator, &b) != 3) {
            printf("SYNTAX ERROR\n");
            continue;
        }

        if (strcmp(isAns, "ANS") == 0) {
            a = load_ans();
        } else {
            
        if (sscanf(input, "%f %c %f", &a, &operator, &b) != 3) {
            printf("SYNTAX ERROR\n");
            continue;
        }

        }

        switch (operator) {
            case '+':
                result = add(a, b);
                break;
            case '-':
                result = subtract(a, b);
                break;
            case '*':
                result = multiply(a, b);
                break;
            case '/':
                if (b == 0) {
                    printf("MATH ERROR\n");
                    continue;
                }
                result = divide(a, b);
                break;
            default:
                printf("SYNTAX ERROR\n");
                continue;
        }

        printf("Ket qua: %.2f\n", result);
        save_ans(result);

        wait_and_clear_screen();
    }

    return 0;
}
