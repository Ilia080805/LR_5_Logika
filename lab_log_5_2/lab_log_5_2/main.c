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
    int edges_src[N * N][2];
    int M = 0;

    for (int i = 0; i < N; i++) {
        adj[i][i] = 0;
        for (int j = i + 1; j < N; j++) {
            int val = rand() % 2;
            adj[i][j] = val;
            adj[j][i] = val;
            if (val == 1) {
                edges_src[M][0] = i;
                edges_src[M][1] = j;
                M++;
            }
        }
    }

    int inc[N][100] = { 0 };

    for (int e = 0; e < M; e++) {
        int v1 = edges_src[e][0];
        int v2 = edges_src[e][1];
        inc[v1][e] = 1;
        inc[v2][e] = 1;
    }

    printf("=== ÌÀÒÐÈÖÀ ÈÍÖÈÄÅÍÒÍÎÑÒÈ (%dx%d) ===\n", N, M);
    if (M == 0) {
        printf("Ãðàô íå ñîäåðæèò ðåáåð!\n");
    }
    else {
        printf("   ");
        for (int e = 0; e < M; e++) printf("e%-2d ", e + 1);
        printf("\n");

        for (int i = 0; i < N; i++) {
            printf("v%d ", i + 1);
            for (int e = 0; e < M; e++) {
                printf(" %d  ", inc[i][e]);
            }
            printf("\n");
        }
    }

    printf("\n=== ÕÀÐÀÊÒÅÐÈÑÒÈÊÈ ÃÐÀÔÀ ===\n");
    printf("Ðàçìåð ãðàôà (êîëè÷åñòâî ñòîëáöîâ/ðåáåð M): %d\n\n", M);

    int deg[N] = { 0 };
    for (int i = 0; i < N; i++) {
        for (int e = 0; e < M; e++) {
            deg[i] += inc[i][e];
        }
    }

    printf("Ñòåïåíè âåðøèí:\n");
    for (int i = 0; i < N; i++) {
        printf("  deg(v%d) = %d", i + 1, deg[i]);

        if (deg[i] == 0) {
            printf(" -> ÈÇÎËÈÐÎÂÀÍÍÀß âåðøèíà");
        }
        else if (deg[i] == 1) {
            printf(" -> ÊÎÍÖÅÂÀß (âèñÿ÷àÿ) âåðøèíà");
        }

        if (deg[i] == N - 1) {
            printf(" -> ÄÎÌÈÍÈÐÓÞÙÀß âåðøèíà");
        }
        printf("\n");
    }

    return 0;
}