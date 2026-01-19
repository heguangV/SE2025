#include <stdio.h>
#include <stdlib.h>

// 定义记录结构体
typedef struct {
    int key;
    int original_index;
} Record;

// qsort所需的比较函数，按关键字升序排序
int compare_records(const void *a, const void *b) {
    Record *rec_a = (Record *)a;
    Record *rec_b = (Record *)b;
    return (rec_a->key - rec_b->key);
}

int main() {
    int n;
    scanf("%d", &n);

    if (n <= 0) {
        return 1;
    }

    Record *records = (Record *)malloc(n * sizeof(Record));
    if (records == NULL) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &records[i].key, &records[i].original_index);
    }

    // 使用qsort对记录按关键字进行排序
    qsort(records, n, sizeof(Record), compare_records);

    // 输出排序后的序列
    for (int i = 0; i < n; i++) {
        printf("(%d %d)", records[i].key, records[i].original_index);
    }
    printf("\n");

    int search_key;
    scanf("%d", &search_key);

    // 折半查找
    int low = 0;
    int high = n - 1;
    int found = 0;
    int found_index = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (records[mid].key == search_key) {
            found = 1;
            found_index = mid;
            break;
        } else if (records[mid].key < search_key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    if (found) {
        printf("(%d %d)\n", records[found_index].key, records[found_index].original_index);
    } else {
        printf("error\n");
    }

    free(records);
    return 0;
}
