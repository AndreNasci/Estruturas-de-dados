// André Nascimento
// GitHub: https://github.com/AndreNasci
// Linkedin: linkedin.com/in/andré-nascimento-a01095185

// Estruturas de Dados
// Hash Table

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 26
#define NAME_SIZE 15


typedef struct node
{
    char name[NAME_SIZE];
    struct node *next;
} node;

int hashFunction(char name[NAME_SIZE]);
void initHashTable(node *table[SIZE]);
void printHashTable(node *table[SIZE]);
bool insertElement(node *table[SIZE], int position, char name[NAME_SIZE]);
bool searchElement(node *table[SIZE], int position, char name[NAME_SIZE]);
bool freeTable(node *table[SIZE]);

int main()
{
    node *hashTable[SIZE];
    int op = 0;
    bool exit = false;
    char name[NAME_SIZE];

    initHashTable(hashTable);

    // Client interface loop
    while(!exit)
    {
        // Menu
        printf("\n1. Print HashTable\n2. Insert item");
        printf("\n3. Search\n4. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &op);

        switch(op)
        {
            case 1: // Print Hash Table
                printHashTable(hashTable);
                break;
            case 2: // Insert new item
                printf("Type a name: ");
                scanf("%s", name);
                insertElement(hashTable, hashFunction(name), name);
                break;
            case 3: // Search for an element in the HashTable
                printf("Type a name: ");
                scanf("%s", name);
                searchElement(hashTable, hashFunction(name), name);
                break;
            case 4: // Exit program and free allocated memory
                freeTable(hashTable);
                exit = true;
                break;
            default:
                printf("This option doesn't exist. Try again.\n");
                break;
        }
    }

    return 0;
}

// Function that calculates the position within the HashTable
int hashFunction(char name[NAME_SIZE])
{
    if(name[0] >= 65 && name[0] <= 90)
    {
        // Upper case
        return name[0] - 65;
    }
    else
    {
        // Lower case
        if(name[0] >= 97 && name[0] <= 122) return (name[0] - 97);
    }

    // If it doesn't start with an alfabetic character, returns last position
    return 25;
}

// Fills the table with NULL
void initHashTable(node *table[SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        table[i] = NULL;
    }
}

// Print each element of the table
void printHashTable(node *table[SIZE])
{
    for(int i=0; i<SIZE; i++)
    {
        if(table[i] == NULL) printf("%c NULL\n", 65+i);
        else
        {
            node *ptr = table[i];
            printf("%c", 65+i); // Print position's letter
            while(ptr != NULL)
            {
                printf(" %s", ptr->name); // Print name
                ptr = ptr->next;
            }
            printf("\n");
        }
    }
}

// Inserts new elements in the Table
bool insertElement(node *table[SIZE], int position, char name[NAME_SIZE])
{
    // Not allowed position
    if(position < 0 || position >= SIZE) return false;

    node *newElement = malloc(sizeof(node));
    strcpy(newElement->name, name);

    // If there's no items on that position
    if(table[position] == NULL)
    {
        table[position] = newElement;
        newElement->next = NULL;
    }
    else
    {
        // If there's already an item on that position
        node *ptr = table[position];
        table[position] = newElement;
        newElement->next = ptr;
    }
    return true;
}

// Searches for an element in the HashTable
bool searchElement(node *table[SIZE], int position, char name[NAME_SIZE])
{
    // Not allowed position
    if(position < 0 || position >= SIZE) return false;

    // If the position is empty
    if(table[position] == NULL)
    {
        printf("Name not found.\n");
        return false;
    }
    else    // Otherwise, iterates through the list and looks for the element
    {
        node *ptr = table[position];
        while(ptr != NULL)
        {
            if(strcmp(table[position]->name, name) == 0)
            {
                printf("Name found.\n");
                return true;
            }
            ptr = ptr->next;
        }
        printf("Name not found.\n");
        return false;
    }
}

// Free allocated memory
bool freeTable(node *table[SIZE])
{
    for(int i=0; i<SIZE; i++)
    {
        if(table[i] == NULL) continue;

        node *ptr;
        // Iterate through the list and free each node
        while(table[i] != NULL)
        {
            ptr = table[i]->next;
            printf("Free node with value %s\n", table[i]->name);
            free(table[i]);
            table[i] = ptr;
        }
    }
    return true;
}
