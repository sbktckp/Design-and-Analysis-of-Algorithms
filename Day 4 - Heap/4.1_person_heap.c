/*
 * 4.1 Person Heap
 *
 * Aim: read the data of 'n' persons from a file into a dynamically allocated
 *      array of struct person, then run min-heap and max-heap operations from
 *      a menu.
 *
 * File format, one record per line, fields separated by commas so that names
 * may contain spaces:
 *      id,name,age,height,weight
 *
 * Method: the array itself is the heap. BUILD-HEAP is bottom-up heapify,
 *         O(n). Insert sifts up and delete sifts down, both O(log n).
 *         The comparison key is chosen by the active heap kind, so the same
 *         routines serve the min-heap on age and the max-heap on weight.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define POUND_TO_KG 0.45359237

struct person {
    int id;
    char *name;
    int age;
    int height;
    int weight;                 /* pounds */
};

enum heap_kind { HEAP_NONE, HEAP_MIN_AGE, HEAP_MAX_WEIGHT };

static struct person *people;
static int count;
static enum heap_kind kind = HEAP_NONE;

static char *dup_string(const char *s)
{
    size_t len = strlen(s) + 1;
    char *copy = malloc(len);

    if (copy != NULL)
        memcpy(copy, s, len);
    return copy;
}

static void trim_newline(char *s)
{
    size_t len = strlen(s);
    while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r'))
        s[--len] = '\0';
}

/* Returns 1 when a comes before b in the active heap. */
static int precedes(const struct person *a, const struct person *b)
{
    if (kind == HEAP_MAX_WEIGHT)
        return a->weight > b->weight;
    return a->age < b->age;                 /* min-heap on age */
}

static void swap_person(struct person *a, struct person *b)
{
    struct person t = *a;
    *a = *b;
    *b = t;
}

static void sift_down(int i)
{
    for (;;) {
        int left = 2 * i + 1, right = left + 1, best = i;

        if (left < count && precedes(&people[left], &people[best]))
            best = left;
        if (right < count && precedes(&people[right], &people[best]))
            best = right;
        if (best == i)
            return;
        swap_person(&people[i], &people[best]);
        i = best;
    }
}

static void sift_up(int i)
{
    while (i > 0) {
        int parent = (i - 1) / 2;

        if (!precedes(&people[i], &people[parent]))
            return;
        swap_person(&people[i], &people[parent]);
        i = parent;
    }
}

static void build_heap(enum heap_kind wanted)
{
    int i;

    kind = wanted;
    for (i = count / 2 - 1; i >= 0; i--)
        sift_down(i);
}

static void print_table(const char *title)
{
    int i;

    printf("%s\n", title);
    printf("%-4s %-18s %-5s %-7s %s\n", "Id", "Name", "Age", "Height", "Weight(pound)");
    for (i = 0; i < count; i++)
        printf("%-4d %-18s %-5d %-7d %d\n", people[i].id, people[i].name,
               people[i].age, people[i].height, people[i].weight);
}

static void free_people(void)
{
    int i;

    for (i = 0; i < count; i++)
        free(people[i].name);
    free(people);
    people = NULL;
    count = 0;
    kind = HEAP_NONE;
}

static void read_data(const char *path)
{
    FILE *fp = fopen(path, "r");
    char line[256];
    int cap = 0;

    if (fp == NULL) {
        perror(path);
        return;
    }
    free_people();

    while (fgets(line, sizeof line, fp) != NULL) {
        struct person p;
        char name[128];

        trim_newline(line);
        if (line[0] == '\0')
            continue;
        if (sscanf(line, "%d,%127[^,],%d,%d,%d",
                   &p.id, name, &p.age, &p.height, &p.weight) != 5) {
            fprintf(stderr, "Skipping malformed line: %s\n", line);
            continue;
        }
        p.name = dup_string(name);
        if (p.name == NULL) {
            fprintf(stderr, "Out of memory\n");
            break;
        }
        if (count == cap) {
            struct person *grown;
            cap = (cap == 0) ? 8 : cap * 2;
            grown = realloc(people, (size_t)cap * sizeof *people);
            if (grown == NULL) {
                fprintf(stderr, "Out of memory\n");
                free(p.name);
                break;
            }
            people = grown;
        }
        people[count++] = p;
    }
    fclose(fp);

    if (count == 0) {
        printf("No records read from %s\n", path);
        return;
    }
    print_table("Data read from file:");
}

static int youngest_index(void)
{
    int i, best = 0;

    if (kind == HEAP_MIN_AGE)
        return 0;                            /* root of the min-heap */
    for (i = 1; i < count; i++)
        if (people[i].age < people[best].age)
            best = i;
    return best;
}

static int oldest_index(void)
{
    int i, best = 0;

    for (i = 1; i < count; i++)
        if (people[i].age > people[best].age)
            best = i;
    return best;
}

static void insert_person(void)
{
    struct person p;
    char name[128];

    if (kind != HEAP_MIN_AGE) {
        printf("Building the min-heap on age first.\n");
        build_heap(HEAP_MIN_AGE);
    }
    printf("Enter id: ");
    if (scanf("%d", &p.id) != 1)
        return;
    printf("Enter name: ");
    if (scanf(" %127[^\n]", name) != 1)
        return;
    printf("Enter age, height and weight(pound): ");
    if (scanf("%d %d %d", &p.age, &p.height, &p.weight) != 3)
        return;

    p.name = dup_string(name);
    if (p.name == NULL) {
        fprintf(stderr, "Out of memory\n");
        return;
    }
    {
        struct person *grown = realloc(people, (size_t)(count + 1) * sizeof *people);
        if (grown == NULL) {
            fprintf(stderr, "Out of memory\n");
            free(p.name);
            return;
        }
        people = grown;
    }
    people[count++] = p;
    sift_up(count - 1);
    print_table("Min-heap on age after insertion:");
}

static void delete_oldest(void)
{
    int i;

    if (count == 0) {
        printf("No data. Read the file first.\n");
        return;
    }
    if (kind == HEAP_NONE) {
        printf("Building the min-heap on age first.\n");
        build_heap(HEAP_MIN_AGE);
    }
    i = oldest_index();
    printf("Deleting %s, age %d\n", people[i].name, people[i].age);
    free(people[i].name);
    people[i] = people[--count];
    if (i < count) {
        sift_down(i);
        sift_up(i);
    }
    print_table("Heap after deletion:");
}

int main(void)
{
    int option;

    for (;;) {
        printf("\nMAIN MENU (HEAP)\n"
               "1. Read Data\n"
               "2. Create a Min-heap based on the age\n"
               "3. Create a Max-heap based on the weight\n"
               "4. Display weight of the youngest person\n"
               "5. Insert a new person into the Min-heap\n"
               "6. Delete the oldest person\n"
               "7. Exit\n"
               "Enter option: ");
        if (scanf("%d", &option) != 1)
            break;

        if (option != 1 && option != 7 && count == 0) {
            printf("No data in memory. Choose option 1 first.\n");
            continue;
        }

        switch (option) {
        case 1:
            read_data("data/inPerson.dat");
            break;
        case 2:
            build_heap(HEAP_MIN_AGE);
            print_table("Min-heap on age (root is the youngest):");
            break;
        case 3:
            build_heap(HEAP_MAX_WEIGHT);
            print_table("Max-heap on weight (root is the heaviest):");
            break;
        case 4: {
            int i = youngest_index();
            printf("Youngest person: %s, age %d\n", people[i].name, people[i].age);
            printf("Weight of youngest person: %.2f kg\n",
                   people[i].weight * POUND_TO_KG);
            break;
        }
        case 5:
            insert_person();
            break;
        case 6:
            delete_oldest();
            break;
        case 7:
            free_people();
            return 0;
        default:
            printf("Invalid option\n");
        }
    }
    free_people();
    return 0;
}
