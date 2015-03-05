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
#include <string.h>

/* Set the competition parameters here */
#define N_PROBLEMS 20
#define N_SCORES 5
const char scores[N_SCORES] = { 10, 7, 4, 1, 0 };

/* Table data separator */
#define TABLE_DELIM ", "

/* This is where we will store the result combination */
#define N_SLOTS (N_PROBLEMS + (N_SCORES - 1))
char field[N_SLOTS];

void get_hits(char *field, int n_slots, int n_scores, int *hits)
{
	int i, group_no = 0, n_hits = 0;

	for (i = 0; i < n_slots; i++) {
		if (field[i] == 0) {
			hits[group_no++] = n_hits;
			n_hits = 0;
		} else {
			n_hits++;
		}
	}

	/* Add on the last set */
	hits[group_no] = n_hits;
}

void print_table_header(int n_scores, const char *scores)
{
	int i;

	for (i = 0; i < n_scores; i++) {
		printf("\"%u\"%s", scores[i], TABLE_DELIM);
	}
	printf("\"total\"\n");
}

void print_table_row(char *field, int n_slots, int n_scores,
		const char *scores)
{
	int hits[n_scores];
	int i, total = 0;

	get_hits(field, n_slots, n_scores, hits);

	for (i = 0; i < n_scores; i++) {
		printf("%4u%s", hits[i], TABLE_DELIM);
		total += hits[i] * scores[i];
	}
	printf("%4u\n", total);
}

/* Recursively place separators. Returns number of combinations */
int place_zero(char *field, int start, int depth)
{
	int i;
	int total = 0;

	for (i = start; i < N_SLOTS; i++)
	{
		/* Fill in our previous separator */
		if (i > start)
			field[i - 1] = 1;

		/* Place our next separator */
		field[i] = 0;

		if (depth > 0) {
			/* Recursively place the rest of the separators */
			total += place_zero(field, i + 1, depth - 1);
		} else {
			/* Or calculate the result */
			print_table_row(field, N_SLOTS, N_SCORES, scores);
			total++;
		}
	}

	/* Fill in our final hole */
	field[i - 1] = 1;
	return total;
}

int main(int argc, char *argv[])
{
	memset(field, 1, sizeof(field));

	print_table_header(N_SCORES, scores);

	/* Recursively calculate scores */
	place_zero(field, 0, N_SCORES - 2);

	return 0;
}
