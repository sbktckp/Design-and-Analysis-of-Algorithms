/* 4.3 Huffman Coding - compact: build tree with a min-heap, print codes. */
#include <stdio.h>
#include <stdlib.h>

struct node { char ch; int freq; struct node *left, *right; };

static struct node *heap[64];
static int size;

static struct node *mk(char ch, int freq, struct node *l, struct node *r)
{
    struct node *n = malloc(sizeof *n);
    *n = (struct node){ ch, freq, l, r };
    return n;
}

static void push(struct node *n)
{
    int i = size++;
    heap[i] = n;
    while (i > 0 && heap[i]->freq < heap[(i - 1) / 2]->freq) {
        struct node *t = heap[i]; heap[i] = heap[(i - 1) / 2]; heap[(i - 1) / 2] = t;
        i = (i - 1) / 2;
    }
}

static struct node *pop(void)
{
    struct node *top = heap[0];
    heap[0] = heap[--size];
    int i = 0;
    for (;;) {
        int l = 2 * i + 1, r = l + 1, s = i;
        if (l < size && heap[l]->freq < heap[s]->freq) s = l;
        if (r < size && heap[r]->freq < heap[s]->freq) s = r;
        if (s == i) break;
        struct node *t = heap[i]; heap[i] = heap[s]; heap[s] = t;
        i = s;
    }
    return top;
}

static void codes(struct node *n, char *path, int depth)
{
    if (!n->left && !n->right) {
        path[depth] = '\0';
        printf("'%c' %s\n", n->ch, depth == 0 ? "0" : path);
        return;
    }
    path[depth] = '0'; codes(n->left, path, depth + 1);
    path[depth] = '1'; codes(n->right, path, depth + 1);
}

int main(void)
{
    FILE *fp = fopen("data/inHuffman.dat", "r");
    char ch, path[64];
    int freq;

    if (fp == NULL) {
        perror("data/inHuffman.dat");
        return 1;
    }
    while (fscanf(fp, " %c,%d", &ch, &freq) == 2)
        push(mk(ch, freq, NULL, NULL));
    fclose(fp);

    while (size > 1) {
        struct node *l = pop(), *r = pop();
        push(mk('\0', l->freq + r->freq, l, r));
    }
    printf("Huffman codes:\n");
    codes(heap[0], path, 0);
    return 0;
}
