#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct tree {
datatype key;
struct tree *left, *right;
} tree;

void btUpView(tree *root)
{
	 if (root == NULL)
        return;
        
    struct node_info {
        tree *node;
        int position;
    };

    struct node_info queue[100];

   // хранение первого узла для каждой позиции.
    struct node_info view[100];

    int current_idx = 0;
    int queue_idx = 1;

    int view_count = 0;

    // добавления корня в очередь (массив)
    queue[0].node = root;
    queue[0].position = 0;


    while (current_idx < queue_idx)
    {
        tree *current = queue[current_idx].node;
        int current_position = queue[current_idx].position;

        // флаг была ли такая позиция
        int found = 0;

        for (int i = 0; i < view_count; i++)
        {
            if (view[i].position == current_position)
            {
                found = 1;
                break;
            }
        }

        if (!found)
        {
            view[view_count].node = current;
            view[view_count].position = current_position;
            view_count++;
        }

        if (current->left != NULL)
        {
            queue[queue_idx].node = current->left;
            queue[queue_idx].position = current_position - 1;
            queue_idx++;
        }

        if (current->right != NULL)
        {
            queue[queue_idx].node = current->right;
            queue[queue_idx].position = current_position + 1;
            queue_idx++;
        }

        current_idx++;
    }

   // печать слева направо
    for (int position = -99; position <= 99; position++)
    {
        for (int i = 0; i < view_count; i++)
        {
            if (view[i].position == position)
            {
                printf("%d ", view[i].node->key);
                break;
            }
        }
    }
}


int main(int argc, char **argv)
{
	


	
    return 0;
}

