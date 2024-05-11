#include <stdio.h>

int main() {
    int p[] = {100, 500, 200, 300, 600};
    int stat[] = {1, 1, 1, 1, 1};
    int PS[4];
    int tm = 0;
    for (int i = 0; i < n; i++) {
        tm += p[i];
    }

    printf("Enter the size of processes\n");

    for(int i = 0; i < 4; i++)
    {
        printf("P%d: ", i + 1);
        scanf("%d", &p[i]);
    }

    int sizeofProc = sizeof(PS) / sizeof(PS[0]);
    int n = sizeof(p) / sizeof(p[0]);

    int amf = 0;
    int ambf = 0;
    int amwf = 0;

    printf("\nFirst Fit:\n");
    for (int i = 0; i < sizeofProc ; i++) {
        int fp = 0;
        for (int j = 0; j < n; j++) {
            if (PS[i] <= p[j] && stat[j] == 1) {
                printf("PS%d -> P%d\n", i + 1, j + 1);
                stat[j] = 0;
                amf += PS[i];
                fp = 1;
                break;
            }
        }
        if (!fp) {
            printf("N/A for PS%d\n", i + 1);
        }
    }

    printf("\nFirst Fit- MU: %.2f%%\n", ((double)amf / tm) * 100);

    for (int i = 0; i < sizeof(stat) / sizeof(stat[0]); i++) {
        stat[i] = 1;
    }

    printf("\nBest Fit:\n");
    for (int i = 0; i < sizeofProc ; i++) {
        int frg = 10000;
        int idx = 10000;
        for (int j = 0; j < n ; j++) {
            if (PS[i] <= p[j] && stat[j] == 1 && frg > p[j] - PS[i]) {
                frg = p[j] - PS[i];
                idx = j;
            }
        }
        if (idx == 10000) {
            printf("N/A for PS%d\n", i + 1);
        } else {
            printf("PS%d -> P%d\n", i + 1, idx + 1);
            stat[idx] = 0;
            ambf += PS[i];
        }
    }

    printf("Best Fit- MU: %.2f%%\n", ((double)ambf / tm) * 100);

    for (int i = 0; i < sizeof(stat) / sizeof(stat[0]); i++) {
        stat[i] = 1;
    }

    printf("\nWorst Fit:\n");
    for (int i = 0; i < sizeofProc; i++) {
        int frg = -10000;
        int idx = 10000;
        for (int j = 0; j < n ; j++) {//check for the largest fragment //PS[i] <= p[j] && stat[j] == 1 && frg < p[j] - PS[i]
            if (PS[i] <= p[j] && stat[j] == 1 && frg < p[j] - PS[i]) 
            { 
                frg = p[j] - PS[i];
                idx = j;
            }
        }
        if (idx == 10000) {
            printf("N/A for PS%d\n", i + 1);
        } else {
            printf("PS%d -> P%d\n", i + 1, idx + 1);
            stat[idx] = 0;
            amwf += PS[i];
        }
    }

    printf("Worst Fit- MU: %.2f%%\n", ((double)amwf / tm) * 100);

    return 0;
}
