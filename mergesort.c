#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char **argv);
bool mergesort(int arr[], int n, int **out);
void merge(int l[], int r[], int nl, int nr, int *newarr);
void print_arr(int arr[], int n);

#define INIT_SIZE 10
int
main(int argc, char **argv)
{
	size_t arr_cap = INIT_SIZE;
	int *arr = malloc(sizeof(*arr)*arr_cap);
	int i=0;
	int num;
	while (scanf("%d", &num) != EOF) {
		arr[i] = num;
		i++;
		if (i == arr_cap) {
			arr_cap *= 2;
			arr = realloc(arr, sizeof(*arr)*arr_cap);
			if (arr == NULL)
				perror("array realloc failed\n");
		}
	}
	int len = i;
	printf("pre-sort: "); print_arr(arr, len);
	int *newarr;
	mergesort(arr, len, &newarr);
	printf("post-sort: "); print_arr(newarr, len);
	if (newarr != arr)
		free(newarr);
	free(arr);
}

void
print_arr(int arr[], int n)
{
	printf("{ ");
	for (int i=0; i<n; i++)
		printf("%d, ", arr[i]);
	printf("}\n");
}
// Returns whether it malloc'ed a new array or returned the input unchanged.
bool
mergesort(int arr[], int n, int **out)
{
	printf("n=%d\tarr=", n); print_arr(arr, n);
	if (n > 1) {
		int *newarr = malloc(sizeof(*newarr)*n);
		int pivot = n / 2;
		printf("pivot=%d\n", pivot);
		printf("l="); print_arr(arr, pivot);
		printf("r="); print_arr(arr+pivot, n - pivot);

		int *l, *r;
		bool free_l = mergesort(arr, pivot, &l);
		bool free_r = mergesort(arr+pivot, n - pivot, &r);
		merge(l, r, pivot, n - pivot, newarr);
		if (free_l) free(l);
		if (free_r) free(r);
		printf("newarr="); print_arr(newarr, n);
		fputc('\n', stdout);
		*out = newarr;
		return true;
	} else {
		*out = arr;
		return false;
	}
}

void
merge(int l[], int r[], int nl, int nr, int *newarr)
{
	int i=0, j=0, k=0;
	while (i < nl && j < nr) {
		if (l[i] <= r[j]) {
			newarr[k] = l[i];
			i++;
		} else {
			newarr[k] = r[j];
			j++;
		}
		k++;
	}
	while (i < nl) {
		newarr[k] = l[i];
		i++; k++;
	}
	while (j < nr) {
		newarr[k] = r[j];
		j++; k++;
	}
}
