/*
 * 3.1 Merge Sort
 *
 * Aim: menu driven program to sort a list of array elements using the Merge
 *      Sort technique, counting the number of comparisons and measuring the
 *      time taken only by the sort itself.
 *
 * Each menu option reads its own input file and writes its own output file:
 *      1 Ascending   data/inAsce.dat -> data/outMergeAsce.dat
 *      2 Descending  data/inDesc.dat -> data/outMergeDesc.dat
 *      3 Random      data/inRand.dat -> data/outMergeRand.dat
 *
 * Method: classic divide and conquer. Split the range in half, sort both
 *         halves recursively, then merge. Time O(n log n) in every case,
 *         space O(n) for the scratch buffer.
 */
#define _POSIX_C_SOURCE 199309L   /* clock_gettime under -std=c17 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static long long comparisons;

static void merge(int *a, int lo, int mid, int hi, int *tmp)
{
    int i = lo, j = mid + 1, k = lo;

    while (i <= mid && j <= hi) {
        comparisons++;
        if (a[i] <= a[j])
            tmp[k++] = a[i++];
        else
            tmp[k++] = a[j++];
    }
    while (i <= mid)
        tmp[k++] = a[i++];
    while (j <= hi)
        tmp[k++] = a[j++];
    for (i = lo; i <= hi; i++)
        a[i] = tmp[i];
}

static void merge_sort(int *a, int lo, int hi, int *tmp)
{
    int mid;

    if (lo >= hi)
        return;
    mid = lo + (hi - lo) / 2;
    merge_sort(a, lo, mid, tmp);
    merge_sort(a, mid + 1, hi, tmp);
    merge(a, lo, mid, hi, tmp);
}

/* Reads every integer of a file into a grown-on-demand array. */
static int *read_ints(const char *path, int *count)
{
    FILE *fp = fopen(path, "r");
    int *a = NULL, value, n = 0, cap = 0;

    if (fp == NULL) {
        perror(path);
        return NULL;
    }
    while (fscanf(fp, "%d", &value) == 1) {
        if (n == cap) {
            int *grown;
            cap = (cap == 0) ? 64 : cap * 2;
            grown = realloc(a, (size_t)cap * sizeof *a);
            if (grown == NULL) {
                free(a);
                fclose(fp);
                fprintf(stderr, "Out of memory\n");
                return NULL;
            }
            a = grown;
        }
        a[n++] = value;
    }
    fclose(fp);
    *count = n;
    return a;
}

static int write_ints(const char *path, const int *a, int n)
{
    FILE *fp = fopen(path, "w");
    int i;

    if (fp == NULL) {
        perror(path);
        return 0;
    }
    for (i = 0; i < n; i++)
        fprintf(fp, "%d%c", a[i], ((i + 1) % 20 == 0) ? '\n' : ' ');
    fputc('\n', fp);
    fclose(fp);
    return 1;
}

static void show_file(const char *label, const char *path)
{
    FILE *fp = fopen(path, "r");
    char line[512];

    printf("%s (%s):\n", label, path);
    if (fp == NULL) {
        perror(path);
        return;
    }
    while (fgets(line, sizeof line, fp) != NULL)
        fputs(line, stdout);
    fclose(fp);
}

static void run(const char *in_path, const char *out_path)
{
    struct timespec t0, t1;
    long long elapsed_ns;
    int n = 0;
    int *a = read_ints(in_path, &n), *tmp;

    if (a == NULL)
        return;
    if (n == 0) {
        printf("%s holds no numbers\n", in_path);
        free(a);
        return;
    }
    tmp = malloc((size_t)n * sizeof *tmp);
    if (tmp == NULL) {
        fprintf(stderr, "Out of memory\n");
        free(a);
        return;
    }

    show_file("Before Sorting", in_path);

    comparisons = 0;
    clock_gettime(CLOCK_MONOTONIC, &t0);
    merge_sort(a, 0, n - 1, tmp);
    clock_gettime(CLOCK_MONOTONIC, &t1);
    elapsed_ns = (long long)(t1.tv_sec - t0.tv_sec) * 1000000000LL
               + (t1.tv_nsec - t0.tv_nsec);

    if (write_ints(out_path, a, n))
        show_file("After Sorting", out_path);

    printf("Elements sorted    : %d\n", n);
    printf("Number of Comparisons: %lld\n", comparisons);
    printf("Execution Time     : %lld nanoseconds\n", elapsed_ns);

    free(tmp);
    free(a);
}

int main(void)
{
    int option;

    for (;;) {
        printf("\nMAIN MENU (MERGE SORT)\n"
               "1. Ascending Data\n"
               "2. Descending Data\n"
               "3. Random Data\n"
               "4. ERROR (EXIT)\n"
               "Enter option: ");
        if (scanf("%d", &option) != 1)
            return 0;

        switch (option) {
        case 1:
            run("data/inAsce.dat", "data/outMergeAsce.dat");
            break;
        case 2:
            run("data/inDesc.dat", "data/outMergeDesc.dat");
            break;
        case 3:
            run("data/inRand.dat", "data/outMergeRand.dat");
            break;
        case 4:
            return 0;
        default:
            printf("Invalid option\n");
        }
    }
}
