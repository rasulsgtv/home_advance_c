#include <stdio.h>

int main(int argc, char **argv)
{
	int n,N;
	int k = 26;
	int p;
	char c;
	
	scanf("%d",&N);
	scanf("%c",&c);
	
	while(c != '.')	
	{	
		if (c >= 'a' && c<= 'z')
		{
			n = c - 'a';
			p = (n + N) % k;
			c = p + 'a';
			printf("%c",c);
		}
		else if (c >= 'A' && c<= 'Z')
		{
			n = c - 'A';
			p = (n + N) % k;
			c = p + 'A';
			printf("%c",c);
		}
		else
		{
			printf("%c",c);
		}
		scanf("%c",&c);
	}
	printf(".");
	
	return 0;
}

