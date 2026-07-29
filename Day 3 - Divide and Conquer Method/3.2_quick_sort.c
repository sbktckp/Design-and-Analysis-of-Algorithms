/*
 * 3.2 Quick Sort
 *
 * Aim: menu driven program to sort a list of elements in ascending order
 *      using Quick Sort, display the sorted output file and the number of
 *      comparisons, and conclude from the partition positions whether the
 *      input produced best-case or worst-case partitioning.
 *
 *      1 Ascending   data/inAsce.dat -> data/outQuickAsce.dat
 *      2 Descending  data/inDesc.dat -> data/outQuickDesc.dat
 *      3 Random      data/inRand.dat -> data/outQuickRand.dat
 *
 * Method: Lomuto partition with the last element as pivot.
 *         Worst case is a split of n-1 and 0, which is what already sorted
 *         data produces and costs O(n^2). Best case is a split where neither
 *         side exceeds n/2, which costs O(n log n). The verdict is taken from
 *         the comparison count and the recursion depth, measured against the
 *         two theoretical bounds.
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static long long comparisons;
static long long extreme_splits;   /* one side empty, counted for size >= 4 */
static long long balanced_splits;  /* neither side larger than half         */
static int max_depth;

static void swap(int *p, int *q)
{
    int t = *p;
    *p = *q;
    *q = t;
}

static int partition(int *a, int lo, int hi)
{
    int pivot = a[hi], i = lo - 1, j;

    for (j = lo; j < hi; j++) {
        comparisons++;
        if (a[j] <= pivot)
            swap(&a[++i], &a[j]);
    }
    swap(&a[i + 1], &a[hi]);
    return i + 1;
}

/*
 * Tiny subarrays nearly always leave one side empty, so they say nothing about
 * pivot quality. Only partitions of size 4 or more are counted here, and the
 * verdict below leans on comparison count and recursion depth, which are the
 * two measurements that actually separate O(n log n) from O(n^2).
 */
static void classify(int lo, int hi, int q)
{
    int size = hi - lo + 1;
    int left = q - lo;
    int right = hi - q;
    int larger = (left > right) ? left : right;

    if (size < 4)
        return;
    if (left == 0 || right == 0)
        extreme_splits++;
    else if (larger <= size / 2)
        balanced_splits++;
}

static void quick_sort(int *a, int lo, int hi, int depth)
{
    int q;

    if (depth > max_depth)
        max_depth = depth;
    if (lo >= hi)
        return;
    q = partition(a, lo, hi);
    classify(lo, hi, q);
    quick_sort(a, lo, q - 1, depth + 1);
    quick_sort(a, q + 1, hi, depth + 1);
}

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
    int n = 0;
    int *a = read_ints(in_path, &n);

    if (a == NULL)
        return;
    if (n == 0) {
        printf("%s holds no numbers\n", in_path);
        free(a);
        return;
    }

    show_file("Before Sorting", in_path);

    comparisons = extreme_splits = balanced_splits = 0;
    max_depth = 0;
    quick_sort(a, 0, n - 1, 1);

    if (write_ints(out_path, a, n))
        show_file("After Sorting", out_path);

    {
        double best_bound  = (double)n * log2((double)n);      /* even splits  */
        double worst_bound = (double)n * (n - 1) / 2.0;        /* n-1 and 0    */
        double threshold   = sqrt(best_bound * worst_bound);
        double depth_bound = 4.0 * log2((double)n);            /* generous best */
        int worst = (comparisons > threshold) || (max_depth > depth_bound);

        printf("Elements sorted      : %d\n", n);
        printf("Number of Comparisons: %lld\n", comparisons);
        printf("Maximum recursion depth      : %d\n", max_depth);
        printf("Partitions with an empty side: %lld\n", extreme_splits);
        printf("Partitions split evenly      : %lld\n", balanced_splits);
        printf("Best-case bound  n log n     : %.0f\n", best_bound);
        printf("Worst-case bound n(n-1)/2    : %.0f\n", worst_bound);
        printf("Depth expected if balanced   : %.0f\n", log2((double)n));
        printf("Scenario: %s-case partitioning\n", worst ? "Worst" : "Best");
    }

    free(a);
}

int main(void)
{
    int option;

    for (;;) {
        printf("\nMAIN MENU (QUICK SORT)\n"
               "1. Ascending Data\n"
               "2. Descending Data\n"
               "3. Random Data\n"
               "4. ERROR (EXIT)\n"
               "Enter option: ");
        if (scanf("%d", &option) != 1)
            return 0;

        switch (option) {
        case 1:
            run("data/inAsce.dat", "data/outQuickAsce.dat");
            break;
        case 2:
            run("data/inDesc.dat", "data/outQuickDesc.dat");
            break;
        case 3:
            run("data/inRand.dat", "data/outQuickRand.dat");
            break;
        case 4:
            return 0;
        default:
            printf("Invalid option\n");
        }
    }
}
