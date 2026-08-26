#include <stdio.h>
#include <inttypes.h>


int main(int argc, char **argv)
{
	int N;
	scanf("%d", &N);
	
	int count = 0;
		
	int left = 0;
	int right = 0;
	int weight = 1;
	
	while (N > 0)
	{
		int r = N % 3;
		if(r == 0)
		{
			N = N / 3;
		}
		if(r == 1)
		{
			left += weight;
			count++;
			N = (N-1) / 3;
		}
		if (r == 2)
		{
			left += weight;
			count++;
			N = (N+1) / 3;
		}
		if (left > 1000000 || right > 1000000)
		{
			printf("-1");
			return 0;
		}
		weight *= 3;
	}
	
	printf("%d\n", count);
	
    return 0;
}

