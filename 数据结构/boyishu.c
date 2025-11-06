#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CHILDREN 10
#define MAX_NAME_LENGTH 10

// 树节点结构
typedef struct Node {
    char name[MAX_NAME_LENGTH];
    int is_leaf;
    int height;
    struct Node* children[MAX_CHILDREN];
    int child_count;
    struct Node* parent;
} Node;

// 全局变量
Node* root = NULL;
Node* current = NULL;

// 函数声明
Node* create_node(const char* name);
Node* parse_tree(const char* str, int* index);
void calculate_heights(Node* node);
void print_tree(Node* node, int depth);
Node* find_node(Node* node, const char* name);
int is_legal_move(Node* from, Node* to);
Node* computer_move();
void free_tree(Node* node);
void print_all_nodes(Node* node);

// 创建新节点
Node* create_node(const char* name) {
    Node* node = (Node*)malloc(sizeof(Node));
    strcpy(node->name, name);
    node->is_leaf = 0;
    node->height = 0;
    node->child_count = 0;
    node->parent = NULL;
    for (int i = 0; i < MAX_CHILDREN; i++) {
        node->children[i] = NULL;
    }
    return node;
}

// 解析博弈树字符串
Node* parse_tree(const char* str, int* index) {
    int len = strlen(str);
    char name[MAX_NAME_LENGTH] = {0};
    int name_index = 0;
    while (*index < len && str[*index] == ',') {
        (*index)++;
    }
    
    if (*index >= len) return NULL;
    
    // 解析节点名称
    if (str[*index] == '(') {
        (*index)++; // 跳过 '('
        
        // 读取节点名称
        while (*index < len && str[*index] != '(' && str[*index] != ')' && str[*index] != ',') {
            if (!isspace(str[*index])) {
                name[name_index++] = str[*index];
            }
            (*index)++;
        }
        name[name_index] = '\0';
        
        if (strlen(name) == 0) {
            return NULL;
        }
        
        Node* node = create_node(name);
        
        // 解析子节点
        while (*index < len && str[*index] != ')') {
            Node* child = parse_tree(str, index);
            if (child != NULL) {
                child->parent = node;
                node->children[node->child_count++] = child;
            }
        }
        
        if (*index < len && str[*index] == ')') {
            (*index)++; // 跳过 ')'
        }
        
        return node;
    }
    
    return NULL;
}

// 计算节点高度和判断叶子节点
void calculate_heights(Node* node) {
    if (node == NULL) return;
    
    if (node->child_count == 0) {
        node->is_leaf = 1;
        node->height = 0;
        return;
    }
    
    node->is_leaf = 0;
    int max_height = -1;
    
    for (int i = 0; i < node->child_count; i++) {
        calculate_heights(node->children[i]);
        if (node->children[i]->height > max_height) {
            max_height = node->children[i]->height;
        }
    }
    
    node->height = max_height + 1;
}

// 打印所有节点（按题目要求格式）
void print_all_nodes(Node* node) {
    if (node == NULL) return;
    
    printf("%s\n", node->name);
    
    for (int i = 0; i < node->child_count; i++) {
        print_all_nodes(node->children[i]);
    }
}

// 查找节点
Node* find_node(Node* node, const char* name) {
    if (node == NULL) return NULL;
    
    if (strcmp(node->name, name) == 0) {
        return node;
    }
    
    for (int i = 0; i < node->child_count; i++) {
        Node* result = find_node(node->children[i], name);
        if (result != NULL) {
            return result;
        }
    }
    
    return NULL;
}

// 检查移动是否合法
int is_legal_move(Node* from, Node* to) {
    if (from == NULL || to == NULL) return 0;
    
    // 检查to是否是从from的直接子节点
    for (int i = 0; i < from->child_count; i++) {
        if (from->children[i] == to) {
            return 1;
        }
    }
    
    return 0;
}

// 改进的计算机决策函数
Node* computer_move() {
    if (current == NULL || current->child_count == 0) return NULL;
    
    Node* winning_moves[MAX_CHILDREN];
    int winning_count = 0;
    int min_winning_height = 1000;
    
    Node* backup_moves[MAX_CHILDREN];
    int backup_count = 0;
    int max_backup_height = -1;
    
    // 检查所有可能的移动
    for (int i = 0; i < current->child_count; i++) {
        Node* child = current->children[i];
        
        // 如果这个移动能直接获胜
        if (child->is_leaf) {
            winning_moves[winning_count++] = child;
            if (child->height < min_winning_height) {
                min_winning_height = child->height;
            }
            continue;
        }
        
        // 检查这个移动是否能确保胜利
        int can_force_win = 1;
        for (int j = 0; j < child->child_count; j++) {
            Node* grandchild = child->children[j];
            // 如果对手有立即获胜的移动，则这个移动不安全
            if (grandchild->is_leaf) {
                can_force_win = 0;
                break;
            }
            // 检查对手移动后，我们是否还有必胜策略
            int we_have_winning_response = 0;
            for (int k = 0; k < grandchild->child_count; k++) {
                if (grandchild->children[k]->is_leaf) {
                    we_have_winning_response = 1;
                    break;
                }
            }
            if (!we_have_winning_response) {
                can_force_win = 0;
                break;
            }
        }
        
        if (can_force_win) {
            winning_moves[winning_count++] = child;
            if (child->height < min_winning_height) {
                min_winning_height = child->height;
            }
        } else {
            backup_moves[backup_count++] = child;
            if (child->height > max_backup_height) {
                max_backup_height = child->height;
            }
        }
    }
    
    // 选择必胜移动中高度最小的（最左边的）
    if (winning_count > 0) {
        Node* best_win = NULL;
        for (int i = 0; i < winning_count; i++) {
            if (winning_moves[i]->height == min_winning_height) {
                if (best_win == NULL) {
                    best_win = winning_moves[i];
                } else {
                    // 选择最左边的（即数组中靠前的）
                    for (int j = 0; j < current->child_count; j++) {
                        if (current->children[j] == best_win) {
                            break;
                        }
                        if (current->children[j] == winning_moves[i]) {
                            best_win = winning_moves[i];
                            break;
                        }
                    }
                }
            }
        }
        return best_win;
    }
    
    // 没有必胜移动，选择高度最大的（最左边的）
    if (backup_count > 0) {
        Node* best_backup = NULL;
        for (int i = 0; i < backup_count; i++) {
            if (backup_moves[i]->height == max_backup_height) {
                if (best_backup == NULL) {
                    best_backup = backup_moves[i];
                } else {
                    // 选择最左边的
                    for (int j = 0; j < current->child_count; j++) {
                        if (current->children[j] == best_backup) {
                            break;
                        }
                        if (current->children[j] == backup_moves[i]) {
                            best_backup = backup_moves[i];
                            break;
                        }
                    }
                }
            }
        }
        return best_backup;
    }
    
    return NULL;
}

// 释放树内存
void free_tree(Node* node) {
    if (node == NULL) return;
    
    for (int i = 0; i < node->child_count; i++) {
        free_tree(node->children[i]);
    }
    
    free(node);
}

int main() {
    char tree_str[1000];
    char input[100];
    char continue_game;
    fgets(tree_str, sizeof(tree_str), stdin);
    tree_str[strcspn(tree_str, "\n")] = 0;
    
    // 解析博弈树
    int index = 0;
    root = parse_tree(tree_str, &index);
    
    // 计算高度
    calculate_heights(root);
    
    // 按题目要求打印所有节点
    print_all_nodes(root);
    
    do {
        current = root;
        
        int first_player;
        printf("Who play first(0: computer; 1: player )?\n");
        scanf("%d", &first_player);
        getchar();
        
        int game_over = 0;
        
        if (first_player == 1) {
            // 玩家先手
            while (!game_over) {
                printf("player:\n");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = 0;
                
                Node* target = find_node(current, input);
                if (target == NULL || !is_legal_move(current, target)) {
                    printf("illegal move.\n");
                    continue;
                }
                
                current = target;
                
                if (current->is_leaf) {
                    printf("Congratulate, you win.\n");
                    game_over = 1;
                    break;
                }
                
                // 计算机走棋
                Node* computer_choice = computer_move();
                if (computer_choice == NULL) {
                    // 如果没有合法移动，玩家获胜
                    printf("Congratulate, you win.\n");
                    game_over = 1;
                    break;
                }
                
                printf("computer: %s\n", computer_choice->name);
                current = computer_choice;
                
                if (current->is_leaf) {
                    printf("Sorry, you lost.\n");
                    game_over = 1;
                }
            }
        } else {
            // 计算机先手
            while (!game_over) {
                // 计算机走棋
                Node* computer_choice = computer_move();
                if (computer_choice == NULL) {
                    printf("Computer has no valid moves.\n");
                    game_over = 1;
                    break;
                }
                
                printf("computer: %s\n", computer_choice->name);
                current = computer_choice;
                
                if (current->is_leaf) {
                    printf("Sorry, you lost.\n");
                    game_over = 1;
                    break;
                }
                
                // 玩家走棋
                int valid_move = 0;
                while (!valid_move && !game_over) {
                    printf("player:\n");
                    fgets(input, sizeof(input), stdin);
                    input[strcspn(input, "\n")] = 0;
                    
                    Node* target = find_node(current, input);
                    if (target == NULL || !is_legal_move(current, target)) {
                        printf("illegal move.\n");
                        continue;
                    }
                    
                    current = target;
                    valid_move = 1;
                    
                    if (current->is_leaf) {
                        printf("Congratulate, you win.\n");
                        game_over = 1;
                    }
                }
            }
        }
        
        printf("Continue(y/n)?\n");
        scanf(" %c", &continue_game);
        getchar();
        
    } while (continue_game == 'y' || continue_game == 'Y');
    
    free_tree(root);
    return 0;
}