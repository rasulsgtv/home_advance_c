#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define ARR_SIZE 20

typedef struct list {
	char word[20];
	struct list *next;
}list;

void add_to_list(list **head, char word[])
{
	list *new = calloc(1,sizeof(list));
	for (int i = 0; i < ARR_SIZE; i++)
	{
		new->word[i] = word[i];
	}
	new->next = *head;
	*head = new;
}

void swap_elements(list *head, int word_count) 
{
	int i = 0;
	while (i < word_count)
	{
		list *current = head;
		
		while (current->next != NULL)
		{
			if (strcmp(current->word, current->next->word) >0)
			{
			char temp[ARR_SIZE];
			strcpy(temp, current->word);
			strcpy(current->word, current->next->word);
			strcpy(current->next->word, temp);
			}
		current = current->next;
		}
		i++;
	}
}
void print_list(list *p)
{
	while (p)
	{
		printf("%s ", p->word);
		p = p->next;
	}
}
void delete_list(list *head)
{
	list *current = head;
	
	
	while (current != NULL)
	{
	list *next_node = current->next;
	
	free(current);
	
	current = next_node;
	}
	
}

int main(int argc, char **argv)
{
	list *head = NULL;
	char c;
	char word[ARR_SIZE] = {0};
	
	int word_count = 0;
	int i = 0;
	
	while((c=getchar()) != '.')
	{
		if(c == ' ')
		{
			word[i] = '\0';
			add_to_list(&head, word);
			word_count++;
			i = 0;
		}
		else 
		{
			word[i] = c;
			i++;
		}
	}
	
	if(c == '.')
	{
		word[i] = '\0';
		add_to_list(&head, word);
		word_count++;
	}
	
	swap_elements(head, word_count);
	print_list(head);
	
	delete_list(head);
	
    return 0;
}

