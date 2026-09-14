#include <stdio.h>
#include <stdbool.h>



int main(int argc, char **argv)
{
	
	bool digits[10]     = {false};
	bool decades[100]   = {false};
	bool hundreds[1000] = {false};
	
	char c;
	
	while ((c = getchar()) != '\n')
	{
		if (c>= '0' && c<= '9')
		{
			int digit = c - '0';
			
			for (int i = 10; i < 100; i++)
			{
				if (decades[i])
				{
					hundreds[i*10 + digit] = true;
				}
			}
			for (int i = 1; i < 10; i++)
			{
				if (digits[i])
				{
					decades[i*10 + digit] = true;
				}
			}
			digits[digit] = true;
		}
	}
	int count = 0;
	
	for (int i = 100; i < 1000; i++)
	{
		if (hundreds[i])
		{
			count++;
		}
	}
	
	printf("%d\n", count);

    return 0;
}

