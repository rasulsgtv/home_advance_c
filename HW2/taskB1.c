#include <stdio.h>
#include <inttypes.h>

typedef struct list 
{
	uint64_t address;
	size_t size;
	char comment[64];
	struct list *next;
} list;

size_t totalMemoryUsage(list *head)
{
	list *current = head;
	
	if (head == NULL)
		return 0;
	
	size_t sumsize = 0;
	
	while (current != NULL)
	{
		sumsize += current->size;
		current = current->next;
	}
	
	return sumsize;
}

int main(int argc, char **argv)
{

    return 0;
}

