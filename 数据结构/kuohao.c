#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10005
int res[MAX_SIZE];

int is_opening_bracket(char ch) {
    return ch == '(' || ch == '{' || ch == '[';
}

int is_closing_bracket(char ch) {
    return ch == ')' || ch == '}' || ch == ']';
}
int brackets_match(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '{' && close == '}') ||
           (open == '[' && close == ']');
}

int main() {
    int top = -1;
    char ch;
    while ((ch = getchar()) != EOF) {
        if (is_opening_bracket(ch)) {
            res[++top] = ch;
        } else if (is_closing_bracket(ch)) {
            if (top == -1 || !brackets_match(res[top], ch)) {
                printf("Match false!\n");
                return 0;
            }
            top--;
        }
    }
    if (top == -1) {
        printf("Match succeed!\n");
    } else {
        printf("Match false!\n");
    }
    return 0;
}