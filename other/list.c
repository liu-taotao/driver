#include <stdio.h>
#include <malloc.h>
struct list {
	int val;
	struct list *next;
};

/**
 * @brief 由于在本地编译必须是英文文件名称，所以注释就写在这里了，这个就是两个链表一个存入后，另一个在从头读取
 * 以下是结果
 * head = 0
 * head = 1
 * head = 2
 * head = 3
 * head = 4
 * head = 5
 * head = 6
 * head = 7
 * head = 8
 * head = 9
 * head = 10
 * 
 * @return int 
 */
int main(void) 
{
	int i = 0;
	struct list * head = NULL, *tail = NULL; 
	head = tail = (struct list *)malloc(sizeof(struct list));;
	while (i < 10) {
		tail->val = i;
		tail->next = (struct list *)malloc(sizeof(struct list));//这个申请空间不同于刷题，必须要先在指向下一个之前就申请
		tail = tail->next;
		tail->next = NULL;
		i++;			
	}
	tail->val = i;//这里是为了让没来得及存储的10，存储在链表中
	while (head != NULL) {
		printf("head = %d\n", head->val);
		head =head->next;		
	}
	return 0;
}