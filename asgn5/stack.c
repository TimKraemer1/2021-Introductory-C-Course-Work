#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "stack.h"
#include "node.h"

struct Stack {
    uint32_t top;
    uint32_t capacity;
    Node **items;
};

Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->items = (Node **) calloc(capacity, sizeof(Node));
        if (!s->items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

void stack_delete(Stack **s) {
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
}

uint32_t stack_size(Stack *s) {
    return s->top;
}

bool stack_empty(Stack *s) {
    if (s->top == 0) {
        return true;
    } else {
        return false;
    }
}

bool stack_full(Stack *s) {
    if (s->top >= s->capacity) {
        return true;
    } else {
        return false;
    }
}

bool stack_push(Stack *s, Node *n) {
    if (stack_full(s)) {
        return false;
    } else {
        s->items[s->top] = n;
        s->top += 1;
        return true;
    }
}

bool stack_pop(Stack *s, Node **n) {
    if (stack_empty(s)) {
        return false;
    } else {
        *n = s->items[s->top - 1];
        s->items[s->top - 1] = 0;
        s->top -= 1;
        return true;
    }
}

void stack_print(Stack *s) {
    printf("Stack elements: ");
    for (uint32_t i = 0; i < s->top; i += 1) {
        node_print(s->items[i]);
        printf(", ");
    }
    printf("\n");
    printf("Stack size: %u\n", stack_size(s));
}
