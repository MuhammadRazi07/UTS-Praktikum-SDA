#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

typedef struct {
    char array[MAX][MAX];
    int top;
} Stack;

void init(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

void push(Stack *s, char *str) {
    if (s->top < MAX - 1) {
        strcpy(s->array[++(s->top)], str);
    }
}

char* pop(Stack *s) {
    if (!isEmpty(s)) {
        return s->array[(s->top)--];
    }
    return "";
}

char* peek(Stack *s) {
    if (!isEmpty(s)) {
        return s->array[s->top];
    }
    return "";
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

void infixToPostfix(char *infix, char *postfix) {
    Stack s;
    init(&s);
    int i, j = 0;
    for (i = 0; infix[i] != '\0'; i++) {
        if (isalnum(infix[i])) {
            postfix[j++] = infix[i];
        } else if (infix[i] == '(') {
            push(&s, "(");
        } else if (infix[i] == ')') {
            while (!isEmpty(&s) && strcmp(peek(&s), "(") != 0) {
                postfix[j++] = pop(&s)[0];
            }
            pop(&s);
        } else {
            while (!isEmpty(&s) && precedence(peek(&s)[0]) >= precedence(infix[i])) {
                postfix[j++] = pop(&s)[0];
            }
            char op[2] = {infix[i], '\0'};
            push(&s, op);
        }
    }
    while (!isEmpty(&s)) {
        postfix[j++] = pop(&s)[0];
    }
    postfix[j] = '\0';
}

void postfixToInfix(char *postfix, char *infix) {
    Stack s;
    init(&s);
    char temp[MAX];
    for (int i = 0; postfix[i] != '\0'; i++) {
        if (isalnum(postfix[i])) {
            char op[2] = {postfix[i], '\0'};
            push(&s, op);
        } else {
            char op2[MAX], op1[MAX];
            strcpy(op2, pop(&s));
            strcpy(op1, pop(&s));
            sprintf(temp, "(%s%c%s)", op1, postfix[i], op2);
            push(&s, temp);
        }
    }
    strcpy(infix, pop(&s));
}

void infixToPrefix(char *infix, char *prefix) {
    strrev(infix);
    for (int i = 0; infix[i] != '\0'; i++) {
        if (infix[i] == '(') infix[i] = ')';
        else if (infix[i] == ')') infix[i] = '(';
    }
    infixToPostfix(infix, prefix);
    strrev(prefix);
}

void prefixToInfix(char *prefix, char *infix) {
    Stack s;
    init(&s);
    char temp[MAX];
    strrev(prefix);
    for (int i = 0; prefix[i] != '\0'; i++) {
        if (isalnum(prefix[i])) {
            char op[2] = {prefix[i], '\0'};
            push(&s, op);
        } else {
            char op1[MAX], op2[MAX];
            strcpy(op1, pop(&s));
            strcpy(op2, pop(&s));
            sprintf(temp, "(%s%c%s)", op1, prefix[i], op2);
            push(&s, temp);
        }
    }
    strcpy(infix, pop(&s));
}

void prefixToPostfix(char *prefix, char *postfix) {
    char infix[MAX];
    prefixToInfix(prefix, infix);
    infixToPostfix(infix, postfix);
}

void postfixToPrefix(char *postfix, char *prefix) {
    char infix[MAX];
    postfixToInfix(postfix, infix);
    infixToPrefix(infix, prefix);
}

void menu() {
    char infix[MAX], postfix[MAX], prefix[MAX];
    int choice;
    while (1) {
        printf("\nMenu Konversi Ekspresi Aritmatika:\n");
        printf("1. Infix ke Postfix\n");
        printf("2. Postfix ke Infix\n");
        printf("3. Infix ke Prefix\n");
        printf("4. Prefix ke Infix\n");
        printf("5. Prefix ke Postfix\n");
        printf("6. Postfix ke Prefix\n");
        printf("7. Keluar\n");
        printf("Pilih opsi: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Masukkan ekspresi infix: ");
                gets(infix);
                infixToPostfix(infix, postfix);
                printf("Postfix: %s\n", postfix);
                break;
            case 2:
                printf("Masukkan ekspresi postfix: ");
                gets(postfix);
                postfixToInfix(postfix, infix);
                printf("Infix: %s\n", infix);
                break;
            case 3:
                printf("Masukkan ekspresi infix: ");
                gets(infix);
                infixToPrefix(infix, prefix);
                printf("Prefix: %s\n", prefix);
                break;
            case 4:
                printf("Masukkan ekspresi prefix: ");
                gets(prefix);
                prefixToInfix(prefix, infix);
                printf("Infix: %s\n", infix);
                break;
            case 5:
                printf("Masukkan ekspresi prefix: ");
                gets(prefix);
                prefixToPostfix(prefix, postfix);
                printf("Postfix: %s\n", postfix);
                break;
            case 6:
                printf("Masukkan ekspresi postfix: ");
                gets(postfix);
                postfixToPrefix(postfix, prefix);
                printf("Prefix: %s\n", prefix);
                break;
            case 7:
                exit(0);
            default:
                printf("Opsi tidak valid!\n");
        }
    }
}

int main() {
    menu();
    return 0;
}
