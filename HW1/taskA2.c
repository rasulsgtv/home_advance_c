#include <stdio.h>
#include <inttypes.h>


int main(int argc, char **argv)
{
	uint32_t N;
    uint32_t K;

    scanf("%" SCNu32 "%" SCNu32, &N, &K);

    uint32_t mask = (1u << K) - 1u;

    uint32_t right_bits = N & mask;

    uint32_t result = (N >> K) | (right_bits << (32 - K));

    printf("%" PRIu32 "\n", result);

    return 0;
}

