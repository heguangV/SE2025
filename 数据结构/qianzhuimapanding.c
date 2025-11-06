#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define ALPHABET_SIZE 2  // 只有0和1

typedef struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    bool is_end_of_word;
} TrieNode;

TrieNode* create_node() {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    node->is_end_of_word = false;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        node->children[i] = NULL;
    }
    return node;
}

int char_to_index(char c) {
    return c - '0';  // '0' -> 0, '1' -> 1
}

// 插入单词并检查是否是前缀或包含前缀
int insert_and_check(TrieNode* root, const char* word) {
    TrieNode* current = root;
    
    for (int i = 0; word[i] != '\0'; i++) {
        int index = char_to_index(word[i]);
        
        if (current->children[index] == NULL) {
            current->children[index] = create_node();
        } else {
            // 如果当前节点是某个单词的结尾，说明当前单词包含前缀
            if (current->children[index]->is_end_of_word) {
                return 1;
            }
        }
        
        current = current->children[index];
    }
    
    // 标记单词结束
    current->is_end_of_word = true;
    
    // 检查当前单词是否是其他单词的前缀（有子节点）
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (current->children[i] != NULL) {
            return 1;
        }
    }
    
    return 0;
}

void free_trie(TrieNode* root) {
    if (root == NULL) return;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        free_trie(root->children[i]);
    }
    free(root);
}

int main() {
    int n;
    scanf("%d", &n);
    
    TrieNode* root = create_node();
    char word[100001];
    int found = 0;
    char result[100001];

    for (int i = 0; i < n; i++) {
        scanf("%s", word);
        if (insert_and_check(root, word)) {
            strcpy(result, word);
            found = 1;
            break;
        }
    }
    
    if (found) {
        printf("%s\n", result);
    } else {
        printf("YES\n");
    }
    
    free_trie(root);
    return 0;
}
