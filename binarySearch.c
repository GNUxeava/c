/* Binary search of an array */

#include <stdio.h>

#define SIZE 15

int binarySearch(const int b[], int searchKey, int low, int high);
void printHeader(void);
void printRow(const int b[], int low, int mid, int high);

int main()
{
	int a[SIZE];	/* create array a */
	int i;	/* counter for initializing elements 0-14 of array a */
	int key;	/* value to locate in array a */
	int result;	/* variable to hold location of key or -1 */

	/* create data */
	for (i = 0; i < SIZE; ++i)
	{
		a[i] = 2 * i;
	}

	printf("Enter a number between 0 and 28: ");
	scanf("%d", &key);

	printHeader();

	/* search for key in array a */
	result = binarySearch(a, key, 0, SIZE - 1);

	/* display results */
	if (result != -1)
	{
		printf("\n%d found in array element %d\n", key, result);
	}
	else printf("\n%d not found\n", key);

	return 0;
}

/* function to perform binary search of an array */
int binarySearch(const int b[], int searchKey, int low, int high)
{
	int middle;	/* variable to hold middle element of array */

	/* loop until low subscript is greater than high subscript */
	while (low <= high)
	{
		/* determine middle element of subarray being searched */
		middle = (low + high) / 2;

		/* display subarray used in this loop iteration */
		printRow(b, low, middle, high);

		/* if searchKey matched middle element, return middle */
		if (searchKey == b[middle])
		{
			return middle;
		}

		/* if searchKey is less than middle element, set new high */
		else if (searchKey < b[middle])
		{
			high = middle - 1;	/* search low end of array */
		}

		/* if search key is greater than middle element, set new low */
		else
		{
			low = middle + 1;	/* search high end of array */
		}
	}

	return -1;	/* searchKey not found */
}

/* Print a header for the output */
void printHeader(void)
{
	int i;	/* counter */

	printf("\nSubscripts\n");

	/* output column head */
	for (i = 0; i < SIZE; ++i)
	{
		printf("%3d ", i);
	}

	printf("\n");	/* start new line of output */

	/* output line of - characters */
	for (i = 1; i <= 4 * SIZE; ++i)
	{
		printf("-");
	}

	printf("\n");	/* start new line of output */

	return ;
}

/* Print one row of output showing the current
 * part of the array being processed */
void printRow(const int b[], int low, int mid, int high)
{
	int i;	/* counter for iterating through array b */

	/* loop through entire array */
	for (i = 0; i < SIZE; ++i)
	{
		/* display spaces if outsude of current subarray range */
		if (i < low || i > high)
		{
			printf("    ");
		}
		else if (i == mid)	/* display middle element */
		{
			printf("%3d*", b[i]);	/* mark middle value */
		}
		else	/* display other elements in subarray */
		{
			printf("%3d ", b[i]);
		}
	}

	printf("\n");	/* start new line of output */

	return ;
}

