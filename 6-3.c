/* Initialize the elements of array s to the even integers from 2 to 20 */

#include <stdio.h>

#define SIZE 10

int main()
{
	int s[SIZE];	/* array s has 10 elements */
	int j;	/* counter */
	
	for (j = 0; j < SIZE; ++j)	/* set the values */
	{
		s[j] = 2 + 2 * j;
	}

	printf("%s%13s\n", "Element", "Value");

	/* output characters of array s in tabular format */
	for (j = 0; j < SIZE; ++j)
	{
		printf("%7d%13d\n", j, s[j]);
	}

	return 0;
}

