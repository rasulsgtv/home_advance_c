#include <stdio.h>
#include <inttypes.h>


int main(int argc, char **argv)
{
	uint32_t N;
    uint32_t K;
    uint32_t max = 0;

    scanf("%" SCNu32 "%" SCNu32, &N, &K);

    uint32_t mask = (1u << K) - 1u;
    
    for (uint32_t shift = 0; shift <= 32-K; shift++)
	{
		uint32_t temp = (N >> shift) & mask;
		if(temp > max)	
		{
			max = temp;
		}
	}

    printf("%" PRIu32 "\n", max);

    return 0;
}

