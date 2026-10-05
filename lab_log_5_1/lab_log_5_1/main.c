#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define N 5

int main(void) {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    srand((unsigned int)time(NULL));

    int adj[N][N];
    int deg[N] = { 0 };
    int edges_count = 0;

    for (int i = 0; i < N; i++) {
        adj[i][i] = 0;
        for (int j = i + 1; j < N; j++) {
            int val = rand() % 2;
            adj[i][j] = val;
            adj[j][i] = val;
        }
    }

    printf("=== МАТРИЦА СМЕЖНОСТИ (%dx%d) ===\n   ", N, N);
    for (int i = 0; i < N; i++) printf("v%d ", i + 1);
    printf("\n");

    for (int i = 0; i < N; i++) {
        printf("v%d ", i + 1);
        for (int j = 0; j < N; j++) {
            printf(" %d ", adj[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (adj[i][j] == 1) {
                deg[i]++;
            }
        }
    }

    int sum_deg = 0;
    for (int i = 0; i < N; i++) {
        sum_deg += deg[i];
    }
    edges_count = sum_deg / 2;

    printf("\n=== ХАРАКТЕРИСТИКИ ГРАФА ===\n");
    printf("Размер графа (число ребер |E|): %d\n\n", edges_count);

    printf("Степени вершин:\n");
    for (int i = 0; i < N; i++) {
        printf("  deg(v%d) = %d", i + 1, deg[i]);

        if (deg[i] == 0) {
            printf(" -> ИЗОЛИРОВАННАЯ вершина");
        }
        else if (deg[i] == 1) {
            printf(" -> КОНЦЕВАЯ (висячая) вершина");
        }

        if (deg[i] == N - 1) {
            printf(" -> ДОМИНИРУЮЩАЯ вершина");
        }
        printf("\n");
    }

    return 0;
}