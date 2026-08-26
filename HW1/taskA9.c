#include <stdio.h>
#include <inttypes.h>

struct pack_array 
{
	uint32_t array; // поле для хранения упакованного массива из 0 и 1
	uint32_t count0 : 8; // счетчик нулей в array
	uint32_t count1 : 8; // счетчик единиц в array
}ar1;

void array2struct(int arr[], struct pack_array *result)
{
    result->array = 0;
    result->count0 = 0;
    result->count1 = 0;

    for (int i = 0; i < 32; i++)
    {
        if (arr[i] == 0)
        {
            result->count0++;
        }
        else
        {
            result->count1++;
        }

        result->array |= ((uint32_t)arr[i] << (31 - i));
    }
}

int main(int argc, char **argv)
{
    int arr[32];
    struct pack_array result;

    for (int i = 0; i < 32; i++)
    {
        scanf("%d", &arr[i]);
    }

    array2struct(arr, &result);

    printf("%" PRIu32 " ", result.array);
    printf("%" PRIu32 " ", result.count0);
    printf("%" PRIu32 "\n", result.count1);

    return 0;
}

