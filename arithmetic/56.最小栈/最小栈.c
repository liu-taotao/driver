

/**
 * @brief 最小栈 使用这个，具体看题目
 * 
 */
typedef struct MinStack{
    int val;
    int min;
    struct MinStack *next;
} MinStack;


MinStack* minStackCreate() {
    MinStack * stack = (MinStack *)malloc(sizeof(MinStack));
    stack->next = NULL;
    return stack;
}

void minStackPush(MinStack* obj, int val) {
    MinStack *temp = malloc(sizeof(MinStack));
    temp->val = val;
    if (obj->next == NULL) {
        temp->min = val;
        obj->min = 0;
    } else {
        temp->min = ((temp->val) > (obj->next->min)) ? (obj->next->min) : (temp->val);
    }
    temp->next = obj->next;
    obj->next = temp;
}

void minStackPop(MinStack* obj) {
    MinStack *temp = obj->next;
    obj->next = obj->next->next;
    free(temp);
    temp = NULL;
}

int minStackTop(MinStack* obj) {
    return obj->next->val;
}

int minStackGetMin(MinStack* obj) {
    return obj->next->min;
}

void minStackFree(MinStack* obj) {
    free(obj);
    obj = NULL;
}

/**
 * Your MinStack struct will be instantiated and called as such:
 * MinStack* obj = minStackCreate();
 * minStackPush(obj, val);
 
 * minStackPop(obj);
 
 * int param_3 = minStackTop(obj);
 
 * int param_4 = minStackGetMin(obj);
 
 * minStackFree(obj);
*/