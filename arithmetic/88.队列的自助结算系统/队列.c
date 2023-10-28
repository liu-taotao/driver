
/**
 * @brief 一个队列的自助结算系统
 * 
 */
typedef struct {
    int arr[20000];
    int begin;
    int end;
} Checkout;


Checkout* checkoutCreate() {
    Checkout *tem = (Checkout *)malloc(sizeof(Checkout));
    tem->begin = 0;
    tem->end = 0;
    return tem;
}

int checkoutGet_max(Checkout* obj) {
    int ans = -1;
    for (int i = obj->begin; i < obj->end; i++) {
        ans = fmax(ans, obj->arr[i]);
    }
    return ans;
}

void checkoutAdd(Checkout* obj, int value) {
    obj->arr[obj->end++] = value;
}

int checkoutRemove(Checkout* obj) {
    if (obj->begin == obj->end) {
        return -1;
    } else {
        return obj->arr[obj->begin++];
    }
}

void checkoutFree(Checkout* obj) {
    obj->end = 0;
    obj->begin = 0;
}