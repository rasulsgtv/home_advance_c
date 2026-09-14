#include <stdio.h>
#include <string.h>

#define STR_LEN 10001
#define MAX_LEN 20002


void read_str(char *str)
{
    int i = 0;
    int c;

    while ((c = getchar()) != '\n' && c != EOF)
    {
        str[i] = c;
        i++;
    }

    str[i] = '\0';
}

void z_func(const char *str, int *z, int n)
{
	z[0] = 0;
	
	for (int i = 1; i < n; i++)
	{
		int j = 0;
		while (i+j < n && str[j] == str [i+j])
		{
			j++;
		}
		z[i] = j;
	}
}

void combine(char *combined, char *str1, char *str2)
{
	strcpy(combined, str1);
	strcat(combined, "$");
	strcat(combined, str2);
}

int answer(int result, int *z, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (i+z[i] == n)
		{
			if (z[i] > result)
			{
				result = z[i];
			}
		}
	}
	return result;
}

int main(int argc, char **argv)
{
	
	char str1[STR_LEN];
	char str2[STR_LEN];

	read_str(str1);
	read_str(str2);
	
	char combined[MAX_LEN];
	
	combine(combined, str1,str2);
	int n = strlen(combined);
	int z[MAX_LEN];
	
	z_func(combined,z, n);
	
	int result1 = answer(0,z,n);
	
	
	combine(combined, str2,str1);
	n = strlen(combined);
	z_func(combined,z, n);
	
	int result2 = answer(0,z,n);

	
	printf("%d %d", result1, result2);

    return 0;
}

