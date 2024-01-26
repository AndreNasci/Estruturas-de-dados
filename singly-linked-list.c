// André Nascimento
// GitHub: https://github.com/AndreNasci
// Linkedin: linkedin.com/in/andré-nascimento-a01095185

// Estruturas de Dados
// Singly-Linked List (Lista Dinâmica Simplesmente Encadeada)

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    int value;
    struct node *next;
} node;

// Operations
node *insert_beginning(node *list, int value);
node *insert_end(node *list, int value);
node *insert_ordered(node *list, int value);
bool print_list(node *list);
bool free_list(node *list);

int main(void)
{
    int op = 0;
    bool exit = false;
    int value;

    node *list = NULL;

    // Client interface loop
    while(!exit)
    {
        // Menu
        printf("\n1. Print list\n2. Insert beginning");
        printf("\n3. Insert end\n4. Insert ordered\n5. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &op);

        switch(op)
        {
            case 1: // Print list
                print_list(list);
                break;
            case 2: // Insert new item at the beginning
                printf("Type a value: ");
                scanf("%d", &value);
                list = insert_beginning(list, value);
                break;
            case 3: // Insert new item at the end
                printf("Type a value: ");
                scanf("%d", &value);
                list = insert_end(list, value);
                break;
            case 4: // Insert new item in order (it doesn't sort previous items)
                printf("Type a value: ");
                scanf("%d", &value);
                list = insert_ordered(list, value);
                break;
            case 5: // Exit program and free allocated memory
                free_list(list);
                exit = true;
                break;
            default:
                printf("This option doesn't exist. Try again.\n");
                break;
        }
    }

    return 0;
}


// Insert new item at the beginning of the list
node *insert_beginning(node *list, int value)
{
    // Allocate space in the memory
    node *new_element = malloc(sizeof(node));
    new_element->value = value;

    if(list == NULL) // List is empty
    {
        new_element->next = NULL;
    }
    else            // List is not empty
    {
        new_element->next = list;
    }

    // New element becomes the head of the list
    return new_element;
}

// Insert new item at the end of the list
node *insert_end(node *list, int value)
{
    // Allocate space in the memory
    node *new_element = malloc(sizeof(node));
    new_element->value = value;

    if(list == NULL) // List is empty
    {
        new_element->next = NULL;
        return new_element;
    }
    else            // List is not empty
    {
        node *ptr = list;
        // Goes to the end of the list
        while(ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        // Insert new element
        ptr->next = new_element;
        return list;
    }
}

// Insert new item in order
// it doesn't sort the list, only inserts the element in a ordered position
node *insert_ordered(node *list, int value)
{
    // Allocate space in the memory
    node *new_element = malloc(sizeof(node));
    new_element->value = value;

    if(list == NULL) // List is empty
    {
        new_element->next = NULL;
        return new_element;
    }
    else            // List is not empty
    {
        node *ptr = list;
        node *prev = NULL;
        // Goes to the position in the list where the next
        // value is bigger than the actual value
        while(ptr != NULL)
        {
            if(value < ptr->value)
            {
                // Free memory that won't be necessary
                free(new_element);

                // New value is smaller than the first item of the list
                if(prev == NULL) return insert_beginning(list, value);

                // New value to be inserted in the middle of the list
                prev->next = insert_beginning(ptr, value);
                return list;
            }
            prev = ptr;
            ptr = ptr->next;
        }
        // New value to be inserted at the end of the list
        prev->next = new_element;
        return list;
    }
}

// Print list
bool print_list(node *list)
{
    if(list == NULL) return false;

    node *ptr = list;
    // Iterate through the list and print it
    do
    {
        printf("%d ", ptr->value);
        ptr = ptr->next;
    }while(ptr != NULL);

    printf("\n");
    return true;
}

// Free allocated memory
bool free_list(node *list)
{
    if(list == NULL) return true;

    node *ptr;
    // Iterate through the list and free each node
    while(list != NULL)
    {
        ptr = list->next;
        printf("Free node with value %d\n", list->value);
        free(list);
        list = ptr;
    }
    return true;
}
