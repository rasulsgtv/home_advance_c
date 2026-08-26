#include <stdio.h>
#include <inttypes.h>

union floatData
{
	float number;
	struct floatbits
	{
	uint32_t mantissa : 23;
	uint32_t exp      : 8;
	uint32_t sigh     : 1;
	} bits;
};

int extractExp(float n)
{
	union floatData data;
	data.number = n;
	
	return data.bits.exp;
	
}
int main(int argc, char **argv)
{ 
	
	float n;
	scanf("%f", &n);
	
	printf("%d",extractExp(n));
	
    return 0;
}

