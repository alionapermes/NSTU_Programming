#include <stdio.h>

/*
static int A = 12, B = 8, C = 32, D = 123;

int main() {
    printf("\n\t\tИсходные данные:\n\tA=%d, B=%d, C=0%o, D=0%o", A, B, C, D);

    A = A % B + ++C + D++;
    B += 5;
    C = (C + ++A + B--) / 5;
    D = (B & 0b100) & ((C & 0b111110000) << 2);

    printf("\n\t\tРезультаты расчёта:\n\tA=%d, B=%d, C=0%o, D=0%o", A, B, C, D);

    return 0;
}
*/

/*
int main() {
    static int A = 12, B = 8, C = 32, D = 123;
    printf("\n\t\tИсходные данные:\n\tA=%d, B=%d, C=0%o, D=0%o", A, B, C, D);

    A = A % B + ++C + D++;
    B += 5;
    C = (C + ++A + B--) / 5;
    D = (B & 0b100) & ((C & 0b111110000) << 2);

    printf("\n\t\tРезультаты расчёта:\n\tA=%d, B=%d, C=0%o, D=0%o", A, B, C, D);

    return 0;
}
*/

/*
int main() {
    static int A, B, C, D;
    printf("\nВведите A, B, C, D: ");
    scanf("%d %d %d %d", &A, &B, &C, &D);
    printf("\n\t\tИсходные данные:\n\tA=%d, B=%d, C=0%o, D=0%o", A, B, C, D);

    A = A % B + ++C + D++;
    B += 5;
    C = (C + ++A + B--) / 5;
    D = (B & 0b100) & ((C & 0b111110000) << 2);

    printf("\n\t\tРезультаты расчёта:\n\tA=%d, B=%d, C=0%o, D=0%o", A, B, C, D);

    return 0;
}
*/

/*
int main() {
    auto int A, B, C, D;
    printf("\n\t\tДо присваивания:\n\tA=%d, B=%d, C=0%o, D=0%o", A, B, C, D);
    printf("\nВведите A, B, C, D: ");
    scanf("%d %d %d %d", &A, &B, &C, &D);
    printf("\n\t\tИсходные данные:\n\tA=%d, B=%d, C=0%o, D=0%o", A, B, C, D);

    A = A % B + ++C + D++;
    B += 5;
    C = (C + ++A + B--) / 5;
    D = (B & 0b100) & ((C & 0b111110000) << 2);

    printf("\n\t\tРезультаты расчёта:\n\tA=%d, B=%d, C=0%o, D=0%o", A, B, C, D);

    return 0;
}
*/

/*
#include "lab1_8.h"
int main() {
    printf("\nВведите A, B, C, D: ");
    scanf("%d %d %d %d", &A, &B, &C, &D);
    printf("\n\t\tИсходные данные:\n\tA=%d, B=%d, C=0%o, D=0%o", A, B, C, D);

    A = A % B + ++C + D++;
    B += 5;
    C = (C + ++A + B--) / 5;
    D = (B & 0b100) & ((C & 0b111110000) << 2);

    printf("\n\t\tРезультаты расчёта:\n\tA=%d, B=%d, C=0%o, D=0%o", A, B, C, D);

    return 0;
}
*/

/*
static int vars[] = {12, 8, 32, 123};

int main() {
    printf("\n\t\tИсходные данные:\n\tvars[0]=%d, vars[1]=%d, vars[2]=0%o, vars[3]=0%o", vars[0], vars[1], vars[2], vars[3]);

    vars[0] = vars[0] % vars[1] + ++vars[2] + vars[3]++;
    vars[1] += 5;
    vars[2] = (vars[2] + ++vars[0] + vars[1]--) / 5;
    vars[3] = (vars[1] & 0b100) & ((vars[2] & 0b111110000) << 2);

    printf("\n\t\tРезультаты расчёта:\n\tvars[0]=%d, vars[1]=%d, vars[2]=0%o, vars[3]=0%o", vars[0], vars[1], vars[2], vars[3]);

    return 0;
}
*/