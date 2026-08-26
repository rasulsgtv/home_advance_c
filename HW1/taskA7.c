#include <stdio.h>
#include <inttypes.h>


int main(int argc, char **argv)
{
	int N,x;
	int result = 0;
	
	scanf("%d", &N);
	
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &x);
		result = result ^ x;
	}	
	printf("%d\n", result);

    return 0;
}

