#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int main(void) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    srand((unsigned int)time(NULL));

    int N = 0;
    int prob = 0;

    printf("Введите количество вершин графа (N): ");
    if (scanf("%d", &N) != 1  N <= 0) {
        printf("Ошибка ввода количества вершин!\n");
        return 1;
    }

    printf("Введите вероятность возникновения рёбер/петель (0-100%%): ");
    if (scanf("%d", &prob) != 1  prob < 0 || prob > 100) {
        printf("Ошибка ввода вероятности!\n");
        return 1;
    }

    int** adj = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        adj[i] = (int*)malloc(N * sizeof(int));
    }

    int max_edges = (N * (N - 1)) / 2 + N;
    int** edges_src = (int**)malloc(max_edges * sizeof(int*));
    for (int i = 0; i < max_edges; i++) {
        edges_src[i] = (int*)malloc(2 * sizeof(int));
    }

    int M = 0;

    for (int i = 0; i < N; i++) {
        if ((rand() % 100) < prob) {
            adj[i][i] = 1;
            edges_src[M][0] = i;
            edges_src[M][1] = i;
            M++;
        }
        else {
            adj[i][i] = 0;
        }

        for (int j = i + 1; j < N; j++) {
            if ((rand() % 100) < prob) {
                adj[i][j] = 1;
                adj[j][i] = 1;
                edges_src[M][0] = i;
                edges_src[M][1] = j;
                M++;
            }
            else {
                adj[i][j] = 0;
                adj[j][i] = 0;
            }
        }
    }

    printf("\n========================================\n");
    printf("=== МАТРИЦА СМЕЖНОСТИ (%dx%d) ===\n", N, N);
    printf("========================================\n   ");
    for (int i = 0; i < N; i++) printf("v%-2d ", i + 1);
    printf("\n");

    for (int i = 0; i < N; i++) {
        printf("v%-2d", i + 1);
        for (int j = 0; j < N; j++) {
            printf(" %d  ", adj[i][j]);
        }
        printf("\n");
    }

    int edges_from_adj = 0;
    for (int i = 0; i < N; i++) {
        edges_from_adj += adj[i][i];

        for (int j = i + 1; j < N; j++) {
            edges_from_adj += adj[i][j];
        }
    }

    int* deg_adj = (int*)calloc(N, sizeof(int));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) {
                if (adj[i][i] == 1) {
                    deg_adj[i] += 2;
                }
            }
            else {
                deg_adj[i] += adj[i][j];
            }
        }
    }

    printf("\n--- Характеристики графа (по матрице смежности) ---\n");
    printf("Размер графа (сумма элементов выше диагонали + петли): %d\n", edges_from_adj);
    printf("Степени и типы вершин:\n");
    for (int i = 0; i < N; i++) {
        printf("  deg(v%d) = %d", i + 1, deg_adj[i]);

        if (adj[i][i] == 1) {
            if (deg_adj[i] == 2) {
                printf(" -> ИЗОЛИРОВАННАЯ с петлёй");
            }
        }
        else if (adj[i][i] == 0 && deg_adj[i] == 0) {
            printf(" -> ИЗОЛИРОВАННАЯ");
        }

        else if (deg_adj[i] == 1 && adj[i][i] == 0) {
            printf(" -> КОНЦЕВАЯ (+висячая)");
        }

        if (deg_adj[i] > N && adj[i][i] == 1) {
            printf(" -> ДОМИНИРУЮЩАЯ с петлёй");
        }
        else if (deg_adj[i] == N - 1 && adj[i][i] == 0) {
            printf(" -> ДОМИНИРУЮЩАЯ");
        }

        if (adj[i][i] == 1) {
            printf(" -> КОЛЬЦЕВАЯ (содержит петлю)");
        }

        printf("\n");
    }


    int** inc = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        inc[i] = (int*)calloc(M > 0 ? M : 1, sizeof(int)); // calloc сразу обнуляет
    }

    for (int e = 0; e < M; e++) {
        int v1 = edges_src[e][0];
        int v2 = edges_src[e][1];

        if (v1 == v2) {
            inc[v1][e] = 2;
        }
        else {
            inc[v1][e] = 1;
            inc[v2][e] = 1;
        }
    }
    printf("\n========================================\n");
    printf("=== МАТРИЦА ИНЦИДЕНТНОСТИ (%dx%d) ===\n", N, M);
    printf("========================================\n");

    if (M == 0) {
        printf("Граф не содержит рёбер!\n");
    }
    else {
        printf("   ");
        for (int e = 0; e < M; e++) printf("e%-2d ", e + 1);
        printf("\n");

        for (int i = 0; i < N; i++) {
            printf("v%-2d", i + 1);
            for (int e = 0; e < M; e++) {
                printf(" %d  ", inc[i][e]);
            }
            printf("\n");
        }
    }

    int* deg_inc = (int*)calloc(N, sizeof(int));
    for (int i = 0; i < N; i++) {
        for (int e = 0; e < M; e++) {
            deg_inc[i] += inc[i][e];
        }
    }

    printf("\n--- Характеристики графа (по матрице инцидентности) ---\n");
    printf("Размер графа (число столбцов M): %d\n", M);
    printf("Степени и типы вершин:\n");
    for (int i = 0; i < N; i++) {
        printf("  deg(v%d) = %d", i + 1, deg_inc[i]);

        if (deg_inc[i] == 0) {
            printf(" -> ИЗОЛИРОВАННАЯ");
        }
        else if (deg_inc[i] == 1) {
            printf(" -> КОНЦЕВАЯ (висячая)");
        }

        // Проверяем наличие петли по значению 2 в строке матрицы инцидентности
        int has_loop = 0;
        for (int e = 0; e < M; e++) {
            if (inc[i][e] == 2) {
                has_loop = 1;
                break;
            }
        }
        if (has_loop) {
            printf(" -> КОЛЬЦЕВАЯ (содержит петлю)");
        }

        printf("\n");
    }

    for (int i = 0; i < N; i++) free(adj[i]);
    free(adj);

    for (int i = 0; i < max_edges; i++) free(edges_src[i]);
    free(edges_src);

    for (int i = 0; i < N; i++) free(inc[i]);
    free(inc);

    free(deg_adj);
    free(deg_inc);

    return 0;
}