#include <stdio.h>
#include <inttypes.h>


int main(int argc, char **argv)
{
	uint32_t N;
    uint32_t K;

    scanf("%" SCNu32 "%" SCNu32, &N, &K);

    uint32_t mask = (1u << K) - 1u;
    uint32_t right_bits = N & mask;

    printf("%" PRIu32 "\n", right_bits);

    return 0;
}

