#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXN 1000

struct optrstack { // 运算符栈
    char data[MAXN];
    int top;
};

void optr_push(struct optrstack* s, char v) { s->data[++s->top] = v; }
char optr_pop(struct optrstack* s, int* ok) { if (s->top < 0) { *ok = 0; return 0; } *ok = 1; return s->data[s->top--]; }
char optr_top(struct optrstack* s, int* ok) { if (s->top < 0) { *ok = 0; return 0; } *ok = 1; return s->data[s->top]; }
int  optr_empty(struct optrstack* s) { return s->top < 0; }

int prec(char op) {
    switch (op) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        case '^': return 3; // 右结合
        default: return 0;
    }
}

char Precede(char a, char b) {
    if (b == '(') return '<';
    if (b == ')') {
        if (a == '(') return '='; // 匹配括号
        return '>'; // 先规约直到遇到 '('
    }
    if (b == '#') {
        return '>'; // 归约到只剩 '#'
    }

    if (a == '#' || a == '(') return '<';

    int pa = prec(a), pb = prec(b);
    if (pa < pb) return '<';
    if (pa > pb) return '>';
    // 相同优先级：^ 为右结合（新来的 b 先入栈），其余为左结合（先规约）
    if (b == '^') return '<';
    return '>';
}

int main() {
    int N;
    scanf("%d", &N);
    int ch;
    // 吃掉行末换行
    while ((ch = getchar()) != '\n' && ch != EOF) {}

    for (int i = 0; i < N; i++) {
    char str[MAXN];
    fgets(str, sizeof(str), stdin);
    struct optrstack os; os.top = -1;
    optr_push(&os, '#');
        int idx = 0;

        for (;;) {
            // 跳过空白
            while (str[idx] && isspace((unsigned char)str[idx])) idx++;
            char c = str[idx] ? str[idx] : '#';

            if (isalpha((unsigned char)c)) {
                putchar(c);
                idx++;
                continue;
            }

            // 运算符或括号或结束符处理
            int ok;
            for (;;) {
                char atop = optr_top(&os, &ok);
                if (!ok) { break; }
                char rel = Precede(atop, c);
                if (rel == '<') {
                    optr_push(&os, c);
                    if (c != '#') idx++;
                    break;
                } else if (rel == '=') {
                    // 括号匹配或结束符匹配
                    if (c == ')') {
                        (void)optr_pop(&os, &ok); // 丢弃 '('
                    }
                    idx++; // 消费 ')' 或 '#'
                    break;
                } else if (rel == '>') {
                    char op = optr_pop(&os, &ok);
                    if (op == '#') break; 
                    putchar(op);
                }
            }
            if (c == '#') {
                break;
            }
        }
        int ok;
        while (!optr_empty(&os)) {
            char op = optr_pop(&os, &ok);
            if (op != '#') {
                putchar(op);
            }
        }
        putchar('\n');
    }
    return 0;
}