#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

enum item_type {
    _int, _symbol
};

typedef struct {
    union {
        int i;
        char symbol[8];
    };
    enum item_type type;
} stack_item;

stack_item stack[64];
stack_item* stack_pointer = stack;

void push(stack_item* i) {
    if (stack_pointer == stack + sizeof(stack)) {
        printf("stack overflow\n");
        return;
    }
    *stack_pointer = *i;
    ++stack_pointer;
}

void pop(stack_item* i) {
    --stack_pointer;
    if (stack_pointer < stack) {
        stack_pointer = stack;
        printf("stack underflow\n");
    }
    *i = *stack_pointer;
}

void eval_token(char* token)
{
}

#define TOKEN_LENGTH 7
void eval(char* line) {
    stack_item a, b;
    stack_item i;
    int p;
    char c;
    char token[TOKEN_LENGTH+1];
    char* t = token;
    while (c = *line) {
        if (c == ' ') {
            t = token;
            eval_token(token);
        } else if (c == 0) {
            t = token;
            eval_token(token);
            break;
        } else if (t < token + TOKEN_LENGTH) {
            t[0] = c;
            t[1] = 0;
            ++t;
        }
        ++line;
    }
}


    {
        if (c >= '0' && c < '9') {
            sscanf(line, "%d%n", &i.i, &p);
            i.type = _int;
            push(&i);
            line += p;
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            pop(&a);
            pop(&b);
            switch (c) {
            case '+': i.i = a.i+b.i; break;
            case '-': i.i = a.i-b.i; break;
            case '*': i.i = a.i*b.i; break;
            case '/': i.i = a.i/b.i; break;
            }
            i.type = _int;
            push(&i);
            ++line;
        } else if (c == '\'') {
            ++line;
            for (p = 0; 1; ++p, ++line)
            {
                c = *line;
                if (p < 7)
                {
                    i.symbol[p] = c;
                    i.symbol[p+1] = 0;
                }
                if (c == ' ' || c == 0)
                    break;
            }
            i.type = _symbol;
            push(&i);
        } else if (c == 0) {
            break;
        } else if (c == ' ') {
            ++line;
        } else {
            /*sscanf(line, "%7s%n", a.symbol, p);*/
            line += p;
        }
    }
}

void show_stack() {
    char ox, oy, c;
    stack_item *i;

    ox = wherex();
    oy = wherey();

    c = 0;
    while (c < 25) {
        gotoxy(32, c);
        if (c < stack_pointer - stack) {
            i = stack + c;
            switch (i->type) {
            case _int:
                cprintf("%7d", i->i);
                break;
            case _symbol:
                cprintf("%7s", i->symbol);
                break;
            default:
                cprintf("badtype");
                break;
           }
        } else {
            cprintf("       ");
        }
        ++c;
    }

    gotoxy(ox, oy);
}

int main(void) {
    char line[20];

    clrscr();
    while (1) {
        printf("> ");
        gets(line);
        /* printf("\n"); */
        eval(line);
        show_stack();
    }
    return EXIT_SUCCESS;
}
