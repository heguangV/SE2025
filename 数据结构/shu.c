#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node {
    char name[10];
    struct Node** children;
    int child_count;
};

int degree_count[100];

int build(struct Node** rt, const char* s, int pos) {
    pos++;
    if (s[pos] == ')') return pos;
    
    *rt = (struct Node*)malloc(sizeof(struct Node));
    strcpy((*rt)->name, "");
    (*rt)->child_count = 0;
    (*rt)->children = NULL;
    
    int name_len = 0;
    while (pos < strlen(s) && s[pos] != ')' && s[pos] != ',') {
        (*rt)->name[name_len++] = s[pos++];
    }
    (*rt)->name[name_len] = '\0';
    
    while (pos < strlen(s) && s[pos] != ')') {
        if (s[pos] == ',') pos++;
        
        struct Node* child;
        pos = build(&child, s, pos);
        
        if (strlen(child->name) > 0) {
            (*rt)->child_count++;
            (*rt)->children = realloc((*rt)->children, (*rt)->child_count * sizeof(struct Node*));
            (*rt)->children[(*rt)->child_count - 1] = child;
        } else {
            free(child);
        }
    }
    degree_count[(*rt)->child_count]++;
    return pos + 1;
}

void show(struct Node* rt, int depth) {
    if (rt == NULL || strlen(rt->name) == 0) return;
    
    for (int i = 0; i < depth * 4; i++) printf(" ");
    printf("%s\n", rt->name);
    
    for (int i = 0; i < rt->child_count; i++) {
        show(rt->children[i], depth + 1);
    }
}

void show_degrees() {
    int max_degree = 0;
    for(int i = 0; i < 100; i++) {
        if (degree_count[i] != 0) {
            max_degree = i;
        }
    }
    printf("Degree of tree: %d\n", max_degree);
    for (int i = 0; i <= max_degree; i++) {
        printf("Number of nodes of degree %d: %d\n", i, degree_count[i]);
    }
}

int main() {
    char input[1000];
    scanf("%s", input);
    struct Node* root = NULL;
    for(int i=0; i<100; i++) {
        degree_count[i] = 0;
    }
    build(&root, input, 0);
    show(root, 0);
    show_degrees();
    return 0;
}