/*
 * Copyright (c) 2015 Brian Starkey <stark3y@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include <stdio.h>

/* Set the competition parameters here */
#define N_PROBLEMS 20
#define N_SCORES 5
#define N_SLOTS (N_PROBLEMS + (N_SCORES - 1))
char field[N_SLOTS], scores[N_SCORES] = { 10, 7, 4, 1, 0 };

/* Recursively place separators and print rows. */
void place_sep(char *field, int start, int depth) {
	int i;

	for (i = start; i < N_SLOTS; i++) {
		/* Fill in our previous separator */
		if (i > start)
			field[i - 1] = 0;

		/* Place our next separator */
		field[i] = 1;

		if (depth > 0) {
			/* Recursively place the rest of the separators */
			place_sep(field, i + 1, depth - 1);
		} else {
			/* Or calculate the result */
			int hits[N_SCORES] = {0}, j, total = 0, group_no = 0;

			for (j = 0; j <= N_SLOTS; j++) {
				if (field[j] || j == N_SLOTS) {
					total += hits[group_no] * scores[group_no];
					printf("%4u%s", hits[group_no++], ", ");
				} else {
					hits[group_no]++;
				}
			}
			printf("%4u\n", total);
		}
	}

	/* Fill in our final hole */
	field[i - 1] = 0;
}

void  main(int argc, char *argv[]) {

	/* Print the table header */
	for (int i = 0; i < N_SCORES; i++) {
		printf("\"%u\"%s", scores[i], ", ");
	}
	printf("\"total\"\n");

	/* Recursively calculate scores */
	place_sep(field, 0, N_SCORES - 2);
}
