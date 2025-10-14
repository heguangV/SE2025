#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// 链表节点，表示一个区域（可能包含多个合并后的平面）
typedef struct Node {
    int height;          // 区域的高度
    int index;           // 该区域最初对应的平面索引
    int width;           // 区域的总宽度
    struct Node* prev;   // 前一个区域
    struct Node* next;   // 后一个区域
} Node;

// 创建新节点
Node* createNode(int idx, int h, int w) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->height = h;
    node->width = w;
    node->index = idx;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

// 找到最低的区域
Node* findMinNode(Node* head) {
    Node* min_node = head;
    Node* current = head;
    while (current != NULL) {
        if (current->height < min_node->height) {
            min_node = current;
        }
        current = current->next;
    }
    return min_node;
}

int main() {
    int n;
    scanf("%d", &n);
    
    int* widths = (int*)malloc(n * sizeof(int));
    int* heights = (int*)malloc(n * sizeof(int));
    long long* ans = (long long*)malloc(n * sizeof(long long));
    
    // 读入数据
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &widths[i], &heights[i]);
        ans[i] = 0;
    }
    
    // 初始化链表，每个平面对应一个节点
    Node* head = createNode(0, heights[0], widths[0]);
    Node* current = head;
    
    for (int i = 1; i < n; i++) {
        Node* new_node = createNode(i, heights[i], widths[i]);
        current->next = new_node;
        new_node->prev = current;
        current = new_node;
    }
    
    Node* cur = head;
    long long cur_time = 0;     // 当前累计时间  
    int cur_height = 0;         // 当前水位高度
    Node* min_node = findMinNode(head);
    cur = min_node;
    
    // 模拟灌水过程
    while (head != NULL) {
        // 水位再上升1个单位，该平面被覆盖
        ans[cur->index] = cur_time + cur->width;
        
        // 判断相邻平面的情况
        int left_h = (cur->prev != NULL) ? cur->prev->height : INT_MAX;
        int right_h = (cur->next != NULL) ? cur->next->height : INT_MAX;

        // 找到需要合并的相邻区域（选择较低的）
        Node* merge_target = NULL;

        if (cur->prev != NULL && cur->next != NULL) {
            // 两边都有，选择较低的那个
            if (left_h <= right_h) {
                merge_target = cur->prev;
            } else {
                merge_target = cur->next;
            }
        } else if (cur->prev != NULL) {
            // 只有左边
            merge_target = cur->prev;
        } else if (cur->next != NULL) {
            // 只有右边
            merge_target = cur->next;
        } else {
            // 只剩一个区域了，处理完毕
            break;
        }
        if(merge_target->height < cur->height) {
            cur = merge_target;
        }
        else{
        // 合并区域
        merge_target->width += cur->width;
        cur_time += (long long)(merge_target->height - cur->height) * cur->width;
        if (merge_target == cur->prev) {
            // 合并到左边
            merge_target->next = cur->next;
            if (cur->next != NULL) {
                cur->next->prev = merge_target;
            }
        } else {
            // 合并到右边
            merge_target->prev = cur->prev;
            if (cur->prev != NULL) {
                cur->prev->next = merge_target;
            } else {
                head = merge_target;  // 更新头节点
            }
        }
        free(cur);
        cur = merge_target;
    }
    }
    
    // 输出结果
    for (int i = 0; i < n; i++) {
        printf("%lld\n", ans[i]);
    }
    
    // 释放内存
    free(widths);
    free(heights);
    free(ans);
    
    // 释放链表
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
    
    return 0;
}
