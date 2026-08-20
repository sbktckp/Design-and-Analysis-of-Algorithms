/*
 * 4.3 Huffman Coding
 *
 * Aim: read character frequencies from a file, build a Huffman tree with a
 *      min-heap, then print the code for every character and encode a
 *      sample message.
 *
 * File format, one record per line:
 *      character,frequency
 *
 * Method: repeatedly pull the two lowest-frequency nodes from a min-heap,
 *         merge them into a parent node with combined frequency, push the
 *         parent back, and stop when one node remains. That node is the
 *         root. Walking root to leaf, left is 0 and right is 1, gives every
 *         character's code. O(n log n) overall.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    char ch;
    int freq;
    struct node *left;
    struct node *right;
};

static struct node **heap;
static int heap_size;
static int heap_cap;

static struct node *new_node(char ch, int freq, struct node *left, struct node *right)
{
    struct node *n = malloc(sizeof *n);

    if (n == NULL) {
        fprintf(stderr, "Out of memory\n");
        exit(1);
    }
    n->ch = ch;
    n->freq = freq;
    n->left = left;
    n->right = right;
    return n;
}

static void heap_swap(int i, int j)
{
    struct node *t = heap[i];
    heap[i] = heap[j];
    heap[j] = t;
}

static void sift_up(int i)
{
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap[i]->freq >= heap[parent]->freq)
            return;
        heap_swap(i, parent);
        i = parent;
    }
}

static void sift_down(int i)
{
    for (;;) {
        int left = 2 * i + 1, right = left + 1, smallest = i;

        if (left < heap_size && heap[left]->freq < heap[smallest]->freq)
            smallest = left;
        if (right < heap_size && heap[right]->freq < heap[smallest]->freq)
            smallest = right;
        if (smallest == i)
            return;
        heap_swap(i, smallest);
        i = smallest;
    }
}

static void heap_push(struct node *n)
{
    if (heap_size == heap_cap) {
        struct node **grown;
        heap_cap = (heap_cap == 0) ? 8 : heap_cap * 2;
        grown = realloc(heap, (size_t)heap_cap * sizeof *heap);
        if (grown == NULL) {
            fprintf(stderr, "Out of memory\n");
            exit(1);
        }
        heap = grown;
    }
    heap[heap_size] = n;
    sift_up(heap_size);
    heap_size++;
}

static struct node *heap_pop(void)
{
    struct node *top = heap[0];

    heap_size--;
    heap[0] = heap[heap_size];
    sift_down(0);
    return top;
}

static void free_tree(struct node *n)
{
    if (n == NULL)
        return;
    free_tree(n->left);
    free_tree(n->right);
    free(n);
}

static void reset(void)
{
    free(heap);
    heap = NULL;
    heap_size = 0;
    heap_cap = 0;
}

static struct node *root;

static void print_codes(const struct node *n, char *path, int depth)
{
    if (n == NULL)
        return;
    if (n->left == NULL && n->right == NULL) {
        path[depth] = '\0';
        printf("'%c'  freq %-4d  code %s\n", n->ch, n->freq,
               depth == 0 ? "0" : path);
        return;
    }
    path[depth] = '0';
    print_codes(n->left, path, depth + 1);
    path[depth] = '1';
    print_codes(n->right, path, depth + 1);
}

/*
 * Prints the tree rotated 90 degrees: root on the left, leaves on the
 * right. Right children are printed first (above), left children after
 * (below), which is the standard layout for reading a binary tree
 * sideways in a terminal.
 *
 * `prefix` is the run of guide bars/spaces inherited from ancestors.
 * `branch` is this node's own connector glyph ("+-- ", "\-- ", or ""
 * for the root). `has_sibling_below` says whether a left sibling still
 * needs a "|" to hang off, which is what a right child must pass down
 * to its own children's prefix.
 */
static void print_tree(const struct node *n, const char *prefix,
                        const char *branch, int has_sibling_below)
{
    char child_prefix[256];

    if (n == NULL)
        return;

    if (n->right != NULL) {
        snprintf(child_prefix, sizeof child_prefix, "%s%s", prefix,
                 has_sibling_below ? "|   " : "    ");
        print_tree(n->right, child_prefix, "+-- ", n->left != NULL);
    }

    printf("%s%s", prefix, branch);
    if (n->left == NULL && n->right == NULL)
        printf("'%c' (%d)\n", n->ch, n->freq);
    else
        printf("(%d)\n", n->freq);

    if (n->left != NULL) {
        snprintf(child_prefix, sizeof child_prefix, "%s%s", prefix,
                 has_sibling_below ? "|   " : "    ");
        print_tree(n->left, child_prefix, "\\-- ", 0);
    }
}

static void read_data(const char *path)
{
    FILE *fp = fopen(path, "r");
    char line[128];

    if (fp == NULL) {
        perror(path);
        return;
    }
    if (root != NULL) {
        free_tree(root);
        root = NULL;
    }
    reset();

    while (fgets(line, sizeof line, fp) != NULL) {
        char ch;
        int freq;

        if (sscanf(line, "%c,%d", &ch, &freq) != 2)
            continue;
        heap_push(new_node(ch, freq, NULL, NULL));
    }
    fclose(fp);

    if (heap_size == 0) {
        printf("No records read from %s\n", path);
        return;
    }
    printf("Data read from file: %d characters\n", heap_size);
}

static void build_tree(void)
{
    if (heap_size == 0) {
        printf("No data. Read the file first.\n");
        return;
    }
    while (heap_size > 1) {
        struct node *left = heap_pop();
        struct node *right = heap_pop();
        struct node *parent = new_node('\0', left->freq + right->freq, left, right);
        heap_push(parent);
    }
    root = heap_pop();
    printf("Huffman tree built.\n");
}

static void show_codes(void)
{
    char path[256];

    if (root == NULL) {
        printf("No tree. Build it first (option 2).\n");
        return;
    }
    printf("Huffman codes:\n");
    print_codes(root, path, 0);
}

static void show_tree(void)
{
    if (root == NULL) {
        printf("No tree. Build it first (option 2).\n");
        return;
    }
    printf("Huffman tree:\n");
    print_tree(root, "", "", 0);
}

/* Returns 1 and fills path/len if target is found among n's leaves. */
static int find_code(const struct node *n, char target, char *path, int depth, int *len)
{
    if (n == NULL)
        return 0;
    if (n->left == NULL && n->right == NULL) {
        if (n->ch == target) {
            *len = depth;
            return 1;
        }
        return 0;
    }
    path[depth] = '0';
    if (find_code(n->left, target, path, depth + 1, len))
        return 1;
    path[depth] = '1';
    if (find_code(n->right, target, path, depth + 1, len))
        return 1;
    return 0;
}

static void encode_message(void)
{
    char message[256];
    char path[256];
    int i;

    if (root == NULL) {
        printf("No tree. Build it first (option 2).\n");
        return;
    }
    printf("Enter a message to encode: ");
    if (scanf(" %255[^\n]", message) != 1)
        return;

    printf("Encoded bits:\n");
    for (i = 0; message[i] != '\0'; i++) {
        int len = 0;

        if (find_code(root, message[i], path, 0, &len)) {
            path[len] = '\0';
            printf("%s", len == 0 ? "0" : path);
        } else {
            printf("?");
        }
    }
    printf("\n");
}

int main(void)
{
    int option;

    for (;;) {
        printf("\nMAIN MENU (HUFFMAN CODING)\n"
               "1. Read Data\n"
               "2. Build Huffman Tree\n"
               "3. Display Codes\n"
               "4. Encode a Message\n"
               "5. Display Tree\n"
               "6. Exit\n"
               "Enter option: ");
        if (scanf("%d", &option) != 1)
            break;

        switch (option) {
        case 1:
            read_data("data/inHuffman.dat");
            break;
        case 2:
            build_tree();
            break;
        case 3:
            show_codes();
            break;
        case 4:
            encode_message();
            break;
        case 5:
            show_tree();
            break;
        case 6:
            if (root != NULL)
                free_tree(root);
            reset();
            return 0;
        default:
            printf("Invalid option\n");
        }
    }
    if (root != NULL)
        free_tree(root);
    reset();
    return 0;
}
