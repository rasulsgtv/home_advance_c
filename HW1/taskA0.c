#include <stdio.h>

int main(int argc, char **argv)
{
	int a;
	int n;
	int max;
	
	scanf("%d",&n);
	
	scanf("%d",&a);
	max = a;
	int count = 1;
	
	for(int i = 0; i < n-1; i++)
	{
		scanf("%d",&a);
		if(a > max)
		{
			max = a;
			count = 1;
		}
		else if( a == max)	
		{
			count++;
		}
	}
	printf("%d",count);
	return 0;
}

