#include <stdio.h>
#include <stdlib.h>

#define EXIT_FAILURE 1

/* Node structure for the stack */
typedef struct Node {
    int data;
    struct Node* next;
} Node;

/* Global variable representing the top of the stack */
Node* top = NULL;

/* Function to push an element onto the stack */
void push(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Error: Unable to allocate memory for new node\n");
        exit(EXIT_FAILURE);
    }

    newNode->data = value;
    newNode->next = top;
    top = newNode;
}

/* Function to print all elements on the stack */
void pall() {
    Node* current = top;
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }
}

/* Function to print the value at the top of the stack */
void pint() {
    if (top == NULL) {
        fprintf(stderr, "L%d: can't pint, stack empty\n", /* Line number */);
        exit(EXIT_FAILURE);
    }

    printf("%d\n", top->data);
}

/* Function to remove the top element from the stack */
void pop() {
    if (top == NULL) {
        fprintf(stderr, "L%d: can't pop an empty stack\n", /* Line number */);
        exit(EXIT_FAILURE);
    }

    Node* temp = top;
    top = top->next;
    free(temp);
}

/* Function to swap the top two elements of the stack */
void swap() {
    if (top == NULL || top->next == NULL) {
        fprintf(stderr, "L%d: can't swap, stack too short\n", /* Line number */);
        exit(EXIT_FAILURE);
    }

    int temp = top->data;
    top->data = top->next->data;
    top->next->data = temp;
}

/* Function to add the top two elements of the stack */
void add() {
    if (top == NULL || top->next == NULL) {
        fprintf(stderr, "L%d: can't add, stack too short\n", /* Line number */);
        exit(EXIT_FAILURE);
    }

    top->next->data += top->data;
    pop();
}

/* Function to free the entire stack when the program exits */
void freeStack() {
    Node* current = top;
    Node* nextNode;

    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
}

int main(int argc, char* argv[]) {
    FILE* file;
    char line[100];
    int line_number = 0;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        line_number++;

        /* Tokenize the input line and process the opcode */
        // You need to implement this part based on your interpreter's logic

        if (/* Check if opcode is push */) {
            int value = /* Extract the integer value from the line */;
            push(value);
        } else if (/* Check if opcode is pall */) {
            pall();
        } else if (/* Check if opcode is pint */) {
            pint();
        } else if (/* Check if opcode is pop */) {
            pop();
        } else if (/* Check if opcode is swap */) {
            swap();
        } else if (/* Check if opcode is add */) {
            add();
        } else {
            fprintf(stderr, "L%d: Unknown opcode\n", line_number);
            exit(EXIT_FAILURE);
        }
    }

    fclose(file);

    /* Free the stack before exiting the program */
    freeStack();

    return 0;
}
