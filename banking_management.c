#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for customer records
struct Customer
{
    int account_no;
    char name[80];
    int balance;
};

// Define a structure for stack node
struct StackNode
{
    int operation; // 1: deposit, 2: withdraw
    int account_no;
    int amount;
    struct StackNode* next;
};

// Define a structure for stack
struct Stack
{
    struct StackNode* top;
};

// Function prototypes
void push(struct Stack* stack, int operation, int account_no, int amount);
void pop(struct Stack* stack, struct Customer data[], int* n);
void accept(struct Customer[], int);
void display(struct Customer[], int);
int search(struct Customer[], int, int);
void deposit(struct Customer[], int, int, int, struct Stack* stack);
void withdraw(struct Customer[], int, int, int, struct Stack* stack);
void deleteRecord(struct Customer[], int*, int, struct Stack* stack);
void updateRecord(struct Customer[], int, int, struct Stack* stack);
void miniStatement(struct Customer[], int, int);

int main()
{
    struct Customer data[20];
    int n, choice, account_no, amount;
    struct Stack stack;
    stack.top = NULL;

    printf("Banking Management system\n\n");
    printf("Number of customer records you want to enter? : ");
    scanf("%d", &n);
    accept(data, n);

    do
    {
        printf("Banking System Menu : \n");
        printf("Press 1 to display all records. \n");
        printf("Press 2 to search a record. \n");
        printf("Press 3 to deposit amount. \n");
        printf("Press 4 to withdraw amount. \n");
        printf("Press 5 to delete a record. \n");
        printf("Press 6 to update customer information. \n");
        printf("Press 7 for Mini Statement. \n");
        printf("Press 0 to exit \n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            display(data, n);
            break;
        case 2:
            printf("Enter account number to search : ");
            scanf("%d", &account_no);
            int index = search(data, n, account_no);
            if (index == -1)
            {
                printf("Record not found!! : ");
            }
            else
            {
                printf("A/c Number : %d\n", data[index].account_no);
                printf("Name       : %s\n", data[index].name);
                printf("Balance    : %d\n", data[index].balance);
            }
            break;
        case 3:
            printf("Enter the account number : ");
            scanf("%d", &account_no);
            printf("Enter amount to deposit : ");
            scanf("%d", &amount);
            deposit(data, n, account_no, amount, &stack);
            break;
        case 4:
            printf("Enter account number : ");
            scanf("%d", &account_no);
            printf("Enter amount to withdraw : ");
            scanf("%d", &amount);
            withdraw(data, n, account_no, amount, &stack);
            break;
        case 5:
            printf("Enter account number to delete record: ");
            scanf("%d", &account_no);
            deleteRecord(data, &n, account_no, &stack);
            break;
        case 6:
            printf("Enter account number to update record: ");
            scanf("%d", &account_no);
            updateRecord(data, n, account_no, &stack);
            break;
        case 7:
            printf("Enter account number for Mini Statement: ");
            scanf("%d", &account_no);
            miniStatement(data, n, account_no);
            break;
        }
    } while (choice != 0);

    // Free the memory used by the stack
    while (stack.top != NULL)
    {
        pop(&stack, data, &n);
    }

    return 0;
}

// Function to push an operation onto the stack
void push(struct Stack* stack, int operation, int account_no, int amount)
{
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    if (newNode == NULL)
    {
        printf("Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    newNode->operation = operation;
    newNode->account_no = account_no;
    newNode->amount = amount;
    newNode->next = stack->top;
    stack->top = newNode;
}

// Function to pop an operation from the stack and perform the corresponding operation
void pop(struct Stack* stack, struct Customer data[], int* n)
{
    if (stack->top != NULL)
    {
        struct StackNode* temp = stack->top;
        stack->top = stack->top->next;
        int operation = temp->operation;
        int account_no = temp->account_no;
        int amount = temp->amount;

        free(temp);

        switch (operation)
        {
        case 1:
            deposit(data, *n, account_no, amount, NULL);
            break;
        case 2:
            withdraw(data, *n, account_no, amount, NULL);
            break;
        case 3:
            deleteRecord(data, n, account_no, NULL);
            break;
        case 4:
            updateRecord(data, *n, account_no, NULL);
            break;
        }
    }
}

// Function to accept customer data
void accept(struct Customer list[], int s)
{
    for (int i = 0; i < s; i++)
    {
        printf("\nEnter data for Record #%d\n", i + 1);
        printf("Enter account_no : ");
        scanf("%d", &list[i].account_no);
        getchar(); // to consume the newline character
        printf("Enter name       : ");
        fgets(list[i].name, 80, stdin);
        list[i].name[strcspn(list[i].name, "\n")] = '\0'; // remove newline character from name
        list[i].balance = 0;
    }
}

// Function to display all customer records
void display(struct Customer list[], int s)
{
    printf("\nA/c No\tName\t\tBalance \n");
    for (int i = 0; i < s; i++)
    {
        printf("%d\t\t%s\t\t%d\n", list[i].account_no, list[i].name, list[i].balance);
    }
}

// Function to search for a customer record
int search(struct Customer list[], int s, int number)
{
    for (int i = 0; i < s; i++)
    {
        if (list[i].account_no == number)
        {
            return i;
        }
    }
    return -1;
}

// Function to deposit amount into a customer account
void deposit(struct Customer list[], int s, int number, int amt, struct Stack* stack)
{
    int i = search(list, s, number);
    if (i == -1)
    {
        printf("Record not found\n");
    }
    else
    {
        list[i].balance += amt;
        if (stack != NULL)
        {
            push(stack, 1, number, amt);
        }
    }
}

// Function to withdraw amount from a customer account
void withdraw(struct Customer list[], int s, int number, int amt, struct Stack* stack)
{
    int i = search(list, s, number);
    if (i == -1)
    {
        printf("Record not found\n");
    }
    else if (list[i].balance < amt)
    {
        printf("Insufficient balance\n");
    }
    else
    {
        list[i].balance -= amt;
        if (stack != NULL)
        {
            push(stack, 2, number, amt);
        }
    }
}

// Function to delete a customer record
void deleteRecord(struct Customer list[], int* s, int number, struct Stack* stack)
{
    int index = search(list, *s, number);
    if (index == -1)
    {
        printf("Record not found\n");
    }
    else
    {
        if (stack != NULL)
        {
            push(stack, 3, number, 0);
        }

        for (int i = index; i < *s - 1; i++)
        {
            list[i] = list[i + 1];
        }
        (*s)--;
        printf("Record deleted successfully\n");
    }
}

// Function to update a customer record
void updateRecord(struct Customer list[], int s, int number, struct Stack* stack)
{
    int index = search(list, s, number);
    if (index == -1)
    {
        printf("Record not found\n");
    }
    else
    {
        if (stack != NULL)
        {
            push(stack, 4, number, 0);
        }

        printf("Enter new account_no : ");
        scanf("%d", &list[index].account_no);
        getchar(); // to consume the newline character
        printf("Enter new name       : ");
        fgets(list[index].name, 80, stdin);
        list[index].name[strcspn(list[index].name, "\n")] = '\0'; // remove newline character from names
        printf("Enter new balance    : ");
        scanf("%d", &list[index].balance);
        printf("Record updated successfully\n");
    }
}

// Function to display mini statement for a customer
void miniStatement(struct Customer list[], int s, int number)
{
    int index = search(list, s, number);
    if (index == -1)
    {
        printf("Record not found\n");
    }
    else
    {
        printf("Mini Statement for Account Number %d\n", list[index].account_no);
        printf("Name    : %s\n", list[index].name);
        printf("Balance : %d\n", list[index].balance);
    }
}
