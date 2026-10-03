#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(void)
{
    const int n = 1000000;
    double *a = malloc((size_t)n * sizeof(*a));
    double *b = malloc((size_t)n * sizeof(*b));
    double *c = malloc((size_t)n * sizeof(*c));

    if (a == NULL || b == NULL || c == NULL) {
        fprintf(stderr, "Allocation failed\n");
        free(a); free(b); free(c);
        return 1;
    }

    for (int i = 0; i < n; ++i) {
        a[i] = (double)i;
        b[i] = 2.0 * i;
    }

    // Tugas 2: Menambahkan variabel alpha
    double alpha = 2.0;

    // Tugas 3: Mengganti arahan gabungan menjadi struktur terpisah
    #pragma omp parallel default(none) shared(a, b, c, n, alpha)
    {
        #pragma omp for schedule(static)
        for (int i = 0; i < n; ++i) {
            // Tugas 2: Menerapkan rumus c_i = alpha * a_i + b_i
            c[i] = alpha * a[i] + b[i]; 
        }
    }

    int errors = 0;
    for (int i = 0; i < n; ++i) {
        // Tugas 2: Mengubah hasil yang diharapkan menjadi 4i
        if (c[i] != 4.0 * i) { 
            ++errors;
        }
    }

    printf("c[0]=%.1f c[n-1]=%.1f errors=%d\n", c[0], c[n - 1], errors);

    free(a); free(b); free(c);
    return errors != 0;
}
