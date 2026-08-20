/*
 * 5.2 Huffman Coding
 *
 * Aim: given a set of characters with their frequencies, construct a Huffman
 *      tree using a min-priority queue keyed on frequency, and display the
 *      in-order traversal of the tree.
 *
 * Method: repeatedly extract the two smallest frequencies, join them under a
 *         new internal node whose frequency is their sum, and put that node
 *         back. n-1 merges, each O(log n), so O(n log n) overall.
 */
#include <stdio.h>
#include <stdlib.h>

struct SYMBOL {
    char alphabet;
    int frequency;
};

struct node {
    struct SYMBOL symbol;
    struct node *left, *right;
};

/* Min-priority queue keyed on frequency, implemented as a binary heap. */
struct min_pq {
    struct node **item;
    int size;
};

static void pq_swap(struct node **a, struct node **b)
{
    struct node *t = *a;
    *a = *b;
    *b = t;
}

static void pq_sift_up(struct min_pq *q, int i)
{
    while (i > 0) {
        int parent = (i - 1) / 2;

        if (q->item[parent]->symbol.frequency <= q->item[i]->symbol.frequency)
            return;
        pq_swap(&q->item[parent], &q->item[i]);
        i = parent;
    }
}

static void pq_sift_down(struct min_pq *q, int i)
{
    for (;;) {
        int left = 2 * i + 1, right = left + 1, small = i;

        if (left < q->size
            && q->item[left]->symbol.frequency < q->item[small]->symbol.frequency)
            small = left;
        if (right < q->size
            && q->item[right]->symbol.frequency < q->item[small]->symbol.frequency)
            small = right;
        if (small == i)
            return;
        pq_swap(&q->item[i], &q->item[small]);
        i = small;
    }
}

static void pq_insert(struct min_pq *q, struct node *value)
{
    q->item[q->size] = value;
    pq_sift_up(q, q->size);
    q->size++;
}

static struct node *pq_extract_min(struct min_pq *q)
{
    struct node *top = q->item[0];

    q->item[0] = q->item[--q->size];
    pq_sift_down(q, 0);
    return top;
}

static struct node *make_node(char alphabet, int frequency,
                              struct node *left, struct node *right)
{
    struct node *p = malloc(sizeof *p);

    if (p == NULL) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    p->symbol.alphabet = alphabet;
    p->symbol.frequency = frequency;
    p->left = left;
    p->right = right;
    return p;
}

static void inorder(const struct node *p)
{
    if (p == NULL)
        return;
    inorder(p->left);
    if (p->left == NULL && p->right == NULL)     /* leaves carry the alphabets */
        printf("%c ", p->symbol.alphabet);
    inorder(p->right);
}

static void print_codes(const struct node *p, char *code, int depth)
{
    if (p == NULL)
        return;
    if (p->left == NULL && p->right == NULL) {
        code[depth] = '\0';
        printf("  %c  %-5d %s\n", p->symbol.alphabet, p->symbol.frequency,
               (depth == 0) ? "0" : code);
        return;
    }
    code[depth] = '0';
    print_codes(p->left, code, depth + 1);
    code[depth] = '1';
    print_codes(p->right, code, depth + 1);
}

/*
 * Draws the tree rotated 90 degrees: root at the left margin, leaves at the
 * right. The right subtree prints above the node and the left subtree below,
 * so reading top to bottom matches the usual picture turned on its side.
 *
 * `pad` is the indentation inherited from the ancestors, `branch` is this
 * node's own connector, and `bar` says whether a vertical guide is still
 * needed in the column this node's children occupy, which is the case only
 * while a sibling is still waiting to be drawn below.
 */
static void print_tree(const struct node *p, const char *pad,
                       const char *branch, int bar)
{
    char child_pad[256];

    if (p == NULL)
        return;

    snprintf(child_pad, sizeof child_pad, "%s%s", pad, bar ? "|   " : "    ");

    print_tree(p->right, child_pad, "+-- ", p->left != NULL);

    printf("%s%s%c (%d)\n", pad, branch, p->symbol.alphabet, p->symbol.frequency);

    print_tree(p->left, child_pad, "\\-- ", 0);
}

static void free_tree(struct node *p)
{
    if (p == NULL)
        return;
    free_tree(p->left);
    free_tree(p->right);
    free(p);
}

int main(void)
{
    struct min_pq q;
    struct node *root;
    char *code;
    int n, i;

    printf("Enter the number of distinct alphabets: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Count must be a positive integer\n");
        return 1;
    }

    q.item = malloc((size_t)(2 * n) * sizeof *q.item);
    code = malloc((size_t)(n + 1));
    if (q.item == NULL || code == NULL) {
        fprintf(stderr, "Out of memory\n");
        free(q.item);
        free(code);
        return 1;
    }
    q.size = 0;

    {
        char *letters = malloc((size_t)n);
        if (letters == NULL) {
            fprintf(stderr, "Out of memory\n");
            free(q.item);
            free(code);
            return 1;
        }
        printf("Enter the alphabets: ");
        for (i = 0; i < n; i++)
            if (scanf(" %c", &letters[i]) != 1) {
                fprintf(stderr, "Invalid input\n");
                free(letters);
                free(q.item);
                free(code);
                return 1;
            }
        printf("Enter its frequencies: ");
        for (i = 0; i < n; i++) {
            int f;
            if (scanf("%d", &f) != 1) {
                fprintf(stderr, "Invalid input\n");
                free(letters);
                free(q.item);
                free(code);
                return 1;
            }
            pq_insert(&q, make_node(letters[i], f, NULL, NULL));
        }
        free(letters);
    }

    while (q.size > 1) {
        struct node *x = pq_extract_min(&q);
        struct node *y = pq_extract_min(&q);

        pq_insert(&q, make_node('*', x->symbol.frequency + y->symbol.frequency, x, y));
    }
    root = pq_extract_min(&q);

    printf("In-order traversal of the tree (Huffman): ");
    inorder(root);
    putchar('\n');

    printf("Character codes:\n  Ch Freq  Code\n");
    print_codes(root, code, 0);

    printf("Huffman tree:\n");
    print_tree(root, "", "", 0);

    free_tree(root);
    free(q.item);
    free(code);
    return 0;
}
