#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_STOCK 10000
#define MAX_ORDERS 200000

typedef struct Stock {
    int stockid;
    int orderid;
    double price;
    int quantity;
    char side;              /* 'b' for buy, 's' for sell */
    struct Stock *prev;
    struct Stock *next;
} Stock;

static Stock *buy_heads[MAX_STOCK];
static Stock *sell_heads[MAX_STOCK];
static Stock *order_index[MAX_ORDERS];

static void printStockInfo(const Stock *s) {
    printf("orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: %c",
           s->orderid, s->stockid, s->price, s->quantity, s->side);
}

static Stock *createOrder(int stockid, int orderid, double price, int quantity, char side) {
    Stock *node = (Stock *)malloc(sizeof(Stock));
    if (!node) {
        fprintf(stderr, "memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->stockid = stockid;
    node->orderid = orderid;
    node->price = price;
    node->quantity = quantity;
    node->side = side;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

static void detachNode(Stock **head, Stock *node) {
    if (!node) return;
    if (node->prev) {
        node->prev->next = node->next;
    } else {
        *head = node->next;
    }
    if (node->next) {
        node->next->prev = node->prev;
    }
    node->prev = NULL;
    node->next = NULL;
}

static void insertBuyOrder(Stock **head, Stock *node) {
    Stock *cur = *head;
    Stock *prev = NULL;
    while (cur) {
        if (node->price > cur->price) break;
        if (node->price == cur->price && node->orderid < cur->orderid) break;
        prev = cur;
        cur = cur->next;
    }
    node->next = cur;
    node->prev = prev;
    if (cur) cur->prev = node;
    if (prev) prev->next = node;
    else *head = node;
}

static void insertSellOrder(Stock **head, Stock *node) {
    Stock *cur = *head;
    Stock *prev = NULL;
    while (cur) {
        if (node->price < cur->price) break;
        if (node->price == cur->price && node->orderid < cur->orderid) break;
        prev = cur;
        cur = cur->next;
    }
    node->next = cur;
    node->prev = prev;
    if (cur) cur->prev = node;
    if (prev) prev->next = node;
    else *head = node;
}

static void matchOrders(int stockid, char trigger_side) {
    while (buy_heads[stockid] && sell_heads[stockid] &&
           buy_heads[stockid]->price >= sell_heads[stockid]->price) {
        Stock *buy = buy_heads[stockid];
        Stock *sell = sell_heads[stockid];
        int tradeQuantity = buy->quantity < sell->quantity ? buy->quantity : sell->quantity;
        double tradePrice = (buy->price + sell->price) / 2.0;

        if (trigger_side == 'b') {
            printf("deal--price:%6.1f  quantity:%4d  buyorder:%04d  sellorder:%04d\n",
                   tradePrice, tradeQuantity, buy->orderid, sell->orderid);
        } else {
            printf("deal--price:%6.1f  quantity:%4d  sellorder:%04d  buyorder:%04d\n",
                   tradePrice, tradeQuantity, sell->orderid, buy->orderid);
        }

        buy->quantity -= tradeQuantity;
        sell->quantity -= tradeQuantity;

        if (buy->quantity == 0) {
            detachNode(&buy_heads[stockid], buy);
            order_index[buy->orderid] = NULL;
            free(buy);
        }
        if (sell->quantity == 0) {
            detachNode(&sell_heads[stockid], sell);
            order_index[sell->orderid] = NULL;
            free(sell);
        }
    }
}

static void printOrders(int stockid) {
    printf("buy orders:\n");
    for (Stock *cur = buy_heads[stockid]; cur; cur = cur->next) {
        printStockInfo(cur);
        printf("\n");
    }
    printf("sell orders:\n");
    for (Stock *cur = sell_heads[stockid]; cur; cur = cur->next) {
        printStockInfo(cur);
        printf("\n");
    }
}

static void cancelOrder(int orderid) {
    if (orderid <= 0 || orderid >= MAX_ORDERS) {
        printf("not found\n");
        return;
    }
    Stock *node = order_index[orderid];
    if (!node) {
        printf("not found\n");
        return;
    }

    if (node->side == 'b') {
        detachNode(&buy_heads[node->stockid], node);
    } else {
        detachNode(&sell_heads[node->stockid], node);
    }

    printf("deleted order:");
    printStockInfo(node);
    printf("\n");

    order_index[orderid] = NULL;
    free(node);
}

static void cleanupAll(void) {
    for (int i = 0; i < MAX_STOCK; ++i) {
        Stock *cur = buy_heads[i];
        while (cur) {
            Stock *next = cur->next;
            free(cur);
            cur = next;
        }
        buy_heads[i] = NULL;

        cur = sell_heads[i];
        while (cur) {
            Stock *next = cur->next;
            free(cur);
            cur = next;
        }
        sell_heads[i] = NULL;
    }
    for (int i = 0; i < MAX_ORDERS; ++i) {
        order_index[i] = NULL;
    }
}

int main(void) {
    int command = 0;
    int nextOrderId = 1;

    while (scanf("%d", &command) == 1) {
        if (command == 0) {
            cleanupAll();
            return 0;
        } else if (command == 1) {
            int stockid = 0;
            int quantity = 0;
            double price = 0.0;
            char side_char = 0;
            if (scanf("%d %lf %d %c", &stockid, &price, &quantity, &side_char) != 4) {
                cleanupAll();
                return 0;
            }
            side_char = (char)tolower((unsigned char)side_char);
            if (side_char != 'b' && side_char != 's') {
                continue;
            }

            if (nextOrderId >= MAX_ORDERS) {
                cleanupAll();
                return 0;
            }

            if (quantity == 0) {
                printf("orderid: %04d\n", nextOrderId);
                if (side_char == 'b') {
                    Stock *best_sell = sell_heads[stockid];
                    if (best_sell && best_sell->price <= price) {
                        double tradePrice = (price + best_sell->price) / 2.0;
                        int tradeQuantity = best_sell->quantity;
                        printf("deal--price:%6.1f  quantity:%4d  buyorder:%04d  sellorder:%04d\n",
                               tradePrice, tradeQuantity, nextOrderId, best_sell->orderid);
                        detachNode(&sell_heads[stockid], best_sell);
                        if (best_sell->orderid >= 0 && best_sell->orderid < MAX_ORDERS) {
                            order_index[best_sell->orderid] = NULL;
                        }
                        free(best_sell);
                    }
                } else {
                    Stock *best_buy = buy_heads[stockid];
                    if (best_buy && best_buy->price >= price) {
                        double tradePrice = (price + best_buy->price) / 2.0;
                        int tradeQuantity = best_buy->quantity;
                        printf("deal--price:%6.1f  quantity:%4d  sellorder:%04d  buyorder:%04d\n",
                               tradePrice, tradeQuantity, nextOrderId, best_buy->orderid);
                        detachNode(&buy_heads[stockid], best_buy);
                        if (best_buy->orderid >= 0 && best_buy->orderid < MAX_ORDERS) {
                            order_index[best_buy->orderid] = NULL;
                        }
                        free(best_buy);
                    }
                }
                nextOrderId++;
                continue;
            }

            Stock *node = createOrder(stockid, nextOrderId, price, quantity, side_char);
            order_index[nextOrderId] = node;
            printf("orderid: %04d\n", nextOrderId);

            if (side_char == 'b') {
                insertBuyOrder(&buy_heads[stockid], node);
            } else {
                insertSellOrder(&sell_heads[stockid], node);
            }

            matchOrders(stockid, side_char);
            nextOrderId++;
        } else if (command == 2) {
            int stockid = 0;
            if (scanf("%d", &stockid) != 1) {
                cleanupAll();
                return 0;
            }
            printOrders(stockid);
        } else if (command == 3) {
            int orderid = 0;
            if (scanf("%d", &orderid) != 1) {
                cleanupAll();
                return 0;
            }
            cancelOrder(orderid);
        } else {
            cleanupAll();
            return 0;
        }
    }

    cleanupAll();
    return 0;
}
