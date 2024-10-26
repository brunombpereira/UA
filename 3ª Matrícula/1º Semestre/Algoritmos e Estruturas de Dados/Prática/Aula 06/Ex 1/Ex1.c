#include  <stdio.h>


#define K_MAX 10000


unsigned long del_mem[K_MAX+1][K_MAX+1] = {0};


unsigned long del_rec(unsigned long m, unsigned long n, unsigned long* cnt) {
    if (m == 0 || n == 0)
    {
        return 1;
    }

    *cnt += 2;

    return del_rec(m-1, n, cnt) + del_rec(m-1, n-1, cnt) + del_rec(m, n-1, cnt);
}


unsigned long del_int(unsigned long m, unsigned long n, unsigned long* cnt) {
    unsigned long d[m+1][n+1];

    for (unsigned long i = 0; i <= m; i++)
    {
        d[i][0] = 1;
    }

    for (unsigned long i = 0; i <= n; i++)
    {
        d[0][i] = 1;
    }
    
    for (unsigned long i = 1; i <= m; i++)
    {
        for (unsigned long j = 1; j <= n; j++)
        {
            d[i][j] = d[i-1][j] + d[i-1][j-1] + d[i][j-1];
        }
    }

    *cnt = 2 * m * n;

    return d[m][n];
}


unsigned long del_rec_mem(unsigned long m, unsigned long n, unsigned long* cnt) {
    if (m == 0 || n == 0)
    {
        return 1;
    }

    if (del_mem[m-1][n] == 0)
    {
        del_mem[m-1][n] = del_rec_mem(m-1, n, cnt);
    }
    
    if (del_mem[m-1][n-1] == 0)
    {
        del_mem[m-1][n-1] = del_rec_mem(m-1, n-1, cnt);
    }

    if (del_mem[m][n-1] == 0)
    {
        del_mem[m][n-1] = del_rec_mem(m, n-1, cnt);
    }

    *cnt += 2;

    return del_mem[m-1][n] + del_mem[m-1][n-1] + del_mem[m][n-1];
}


int main(int argc, char* argv[]) {
    unsigned long k, cnt, result;

    if (argc < 2)
    {
        return 1;
    }
    
    if (sscanf(argv[1], "%lu", &k) != 1)
    {
        return 2;
    }

    if (k > K_MAX)
    {
        return 3;
    }
    
    cnt = 0;
    result = del_rec(k, k, &cnt);
    printf("Delanney rec(%lu, %lu) = %lu (%lu)\n", k, k, result, cnt);
    cnt = 0;
    result = del_int(k, k, &cnt);
    printf("Delanney iter(%lu, %lu) = %lu (%lu)\n", k, k, result, cnt);
    cnt = 0;
    del_rec_mem(k, k, &cnt);
    printf("Delanney rec_mem(%lu, %lu) = %lu (%lu)\n", k, k, result, cnt);

    return 0;
}