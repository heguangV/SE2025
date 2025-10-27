#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXN 1000

struct opndstack { // 操作数栈
    int data[MAXN];
    int top;
};

struct optrstack { // 运算符栈
    char data[MAXN];
    int top;
};

void opnd_push(struct opndstack* s, int v) { s->data[++s->top] = v; }
int  opnd_pop(struct opndstack* s, int* ok) { if (s->top < 0) { *ok = 0; return 0; } *ok = 1; return s->data[s->top--]; }
int  opnd_empty(struct opndstack* s) { return s->top < 0; }

void optr_push(struct optrstack* s, char v) { s->data[++s->top] = v; }
char optr_pop(struct optrstack* s, int* ok) { if (s->top < 0) { *ok = 0; return 0; } *ok = 1; return s->data[s->top--]; }
char optr_top(struct optrstack* s, int* ok) { if (s->top < 0) { *ok = 0; return 0; } *ok = 1; return s->data[s->top]; }
int  optr_empty(struct optrstack* s) { return s->top < 0; }

// 计算 a (theta) b，错误码：-32768 表示除 0；-32767 表示非法（如负指数）
int Operate(int a, char theta, int b) {
    switch (theta) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return (b == 0) ? -32768 : a / b;
        case '%': return (b == 0) ? -32768 : a % b;
        case '^': {
            if (b < 0) return -32767; // 不支持负指数
            int res = 1;
            for (int i = 0; i < b; i++) res *= a;
            return res;
        }
        default: return -32767;
    }
}

// 返回 1 成功；0 失败。失败时：*err = 1 => 除 0；*err = 2 => 其他错误
int reduce_once(struct opndstack* vs, struct optrstack* os, int* err) {
    int ok;
    char op = optr_pop(os, &ok);
    if (!ok) { *err = 2; return 0; }
    int b = opnd_pop(vs, &ok);
    if (!ok) { *err = 2; return 0; }
    int a = opnd_pop(vs, &ok);
    if (!ok) { *err = 2; return 0; }
    int res = Operate(a, op, b);
    if (res == -32768) { *err = 1; return 0; }
    if (res == -32767) { *err = 2; return 0; }
    opnd_push(vs, res);
    return 1;
}

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
        if (a == '#') return 'E'; // 错误：没有匹配的左括号
        return '>'; // 先规约直到遇到 '('
    }
    if (b == '#') {
        if (a == '#') return '='; // 结束
        if (a == '(') return 'E'; // 错误：有未匹配的左括号
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

        // 初始化栈
        struct opndstack vs; vs.top = -1;
        struct optrstack os; os.top = -1; optr_push(&os, '#');

        int idx = 0;
        int error = 0; // 0 无错；1 除以 0；2 其他错误
        int expect_value = 1; // 开始时期望读到一个“值”（数字或左括号）

        for (;;) {
            // 跳过空白
            while (str[idx] && isspace((unsigned char)str[idx])) idx++;

            char c = str[idx] ? str[idx] : '#';

            // 非法相邻检查：当刚读完一个“值”后（expect_value==0），下一符号不能是数字/一元正负开始的数字/左括号
            if (!expect_value) {
                if (isdigit((unsigned char)c) || c == '(' ) {
                    error = 2;
                    break;
                }
            }

            // 处理带符号整数：当期望值且遇到一元+/-并且后续是数字
            if (expect_value && (c == '+' || c == '-') && isdigit((unsigned char)str[idx + 1])) {
                int sign = (c == '-') ? -1 : 1;
                idx++;
                long long num = 0;
                while (isdigit((unsigned char)str[idx])) {
                    num = num * 10 + (str[idx] - '0');
                    idx++;
                }
                opnd_push(&vs, (int)(sign * num));
                expect_value = 0;
                continue;
            }

            if (isdigit((unsigned char)c)) {
                // 读一个非负整数
                long long num = 0;
                while (isdigit((unsigned char)str[idx])) {
                    num = num * 10 + (str[idx] - '0');
                    idx++;
                }
                opnd_push(&vs, (int)num);
                expect_value = 0;
                continue;
            }

            // 运算符或括号或结束符处理
            int ok;
            char atop = optr_top(&os, &ok);
            if (!ok) { error = 2; }
            char rel = Precede(atop, c);
            if (rel == 'E') { error = 2; }
            if (error) break;
            if (rel == '<') {
                optr_push(&os, c);
                if (c != '#') idx++; // 消费一个输入符号（# 不来自输入行）
                // 状态更新：
                if (c == '(') expect_value = 1; else if (c != '#') expect_value = 1;
            } else if (rel == '=') {
                // 括号匹配：弹出 '(' 并消费 ')'
                if (c == ')') {
                    (void)optr_pop(&os, &ok); // 弹出 '('
                    idx++; // 消费右括号
                    expect_value = 0; // 一个值（括号表达式）已完成
                } else if (c == '#') {
                    // 结束符与哨兵匹配：不弹出 '#'
                }
            } else if (rel == '>') {
                if (!reduce_once(&vs, &os, &error)) {
                    break;
                }
            }

            // 完成条件：输入为 # 且栈顶也为 #
            if (c == '#') {
                (void)optr_top(&os, &ok);
                if (ok && os.data[os.top] == '#') {
                    break;
                }
            }
        }

        if (error == 1) {
            printf("Divide 0.\n");
        } else if (error == 2) {
            printf("error.\n");
        } else if (!opnd_empty(&vs)) {
            printf("%d\n", vs.data[vs.top]);
        } else {
            printf("error.\n");
        }
    }

    return 0;
}
