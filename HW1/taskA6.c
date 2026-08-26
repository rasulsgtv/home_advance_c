#include <stdio.h>
#include <inttypes.h>


int main(int argc, char **argv)
{
	uint32_t N;
	
	scanf("%" SCNu32, &N);

	uint32_t right_byte = (1u << 8) - 1u;
	uint32_t mask = right_byte << 24;
	uint32_t result = N ^ mask;
	
	printf("%" PRIu32 "\n", result);

    return 0;
}

