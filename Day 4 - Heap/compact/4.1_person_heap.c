/*
 * Day 4, Q4.1  Min-heap on age over a person record
 *
 * Idea: a heap is just an array read as a tree. The children of index i sit at
 * 2i+1 and 2i+2. down() pushes one wrong element into place by repeatedly
 * swapping it with its smaller child. Calling down() on every index from the
 * last parent, n/2-1, backwards to 0 turns any array into a heap, and doing it
 * bottom up costs O(n) rather than O(n log n).
 *
 * Once built, the root p[0] is the youngest person, so the answer the question
 * wants is one array access away.
 *
 * The %29[^,] in the format string means read up to 29 characters that are not
 * a comma, which is how the name survives the space inside it.
 *
 * Input
 *   data/inPerson.dat holds lines of  id,name,age,height,weight
 *   0,Adarsh Hota,39,77,231 ... 6,Norma Webster,23,75,145
 *
 * Output
 *   Min-heap on age:
 *   Id Name Age Height Weight
 *   6 Norma Webster 23 75 145
 *   4 Florence Smith 24 75 171
 *   5 Erica Anyan 38 73 102
 *   3 Dorothy Helton 47 72 229
 *   1 Levi Maier 56 77 129
 *   0 Adarsh Hota 39 77 231
 *   2 Priya Kumari 63 78 240
 *   Weight of youngest person: 65.77 kg
 *
 *   145 pounds is 65.77 kg, which matches the lab sheet.
 */
#include <stdio.h>
struct P { int id, age, ht, wt; char nm[30]; } p[50], t;
int n = 0;
void down(int i) {
    int l, r, s;
    for (;;) {
        l = 2 * i + 1; r = l + 1; s = i;
        if (l < n && p[l].age < p[s].age) s = l;
        if (r < n && p[r].age < p[s].age) s = r;
        if (s == i) return;
        t = p[i]; p[i] = p[s]; p[s] = t; i = s;
    }
}
int main() {
    FILE *f = fopen("../data/inPerson.dat", "r");
    int i;
    while (fscanf(f, "%d,%29[^,],%d,%d,%d\n", &p[n].id, p[n].nm, &p[n].age, &p[n].ht, &p[n].wt) == 5) n++;
    for (i = n / 2 - 1; i >= 0; i--) down(i);
    printf("Min-heap on age:\nId Name Age Height Weight\n");
    for (i = 0; i < n; i++) printf("%d %s %d %d %d\n", p[i].id, p[i].nm, p[i].age, p[i].ht, p[i].wt);
    printf("Weight of youngest person: %.2f kg\n", p[0].wt * 0.45359237);
    return 0;
}
