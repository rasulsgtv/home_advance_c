#include <stdio.h>
#include <inttypes.h>

typedef struct list 
{
	uint64_t address;
	size_t size;
	char comment[64];
	struct list *next;
} list;

uint64_t findMaxBlock(list *head)
{
	list *current = head;
	
	if (head == NULL)
		return 0;
	
	size_t maxsize = current->size;
	uint64_t maxAddress = current->address;
	
	while(current != NULL)
	{
		if((current->size) > maxsize)
		{
			maxsize = current->size;
			maxAddress = current->address;
		}
		current = current->next;
	}	
	return maxAddress;
}

int main(int argc, char **argv)
{

    return 0;
}

