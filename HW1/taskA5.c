#include <stdio.h>
#include <inttypes.h>


int main(int argc, char **argv)
{
	uint32_t N;
	int count = 0;
	
	scanf("%" SCNu32, &N);
	
	for (uint32_t shift = 0; shift <= 31; shift++)
	{
		uint32_t temp = 1u << shift;
		if(N & temp)
		{
		count++;
		}	
	}
	printf("%d", count);

    return 0;
}

