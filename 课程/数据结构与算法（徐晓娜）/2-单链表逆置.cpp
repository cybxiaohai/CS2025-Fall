#include<stdio.h>
#include<malloc.h>

typedef int ElemType;
typedef struct LNode {
	ElemType data;
	struct LNode* next;
} LinkNode;

bool InitList(LinkNode *&L);
bool InsertList(LinkNode *&L,)





bool InitList(LinkNode *&L) {
	L = (*LinkNode)malloc(sizeof(LinkNode));
	L->next = NULL;
}


int main() {
	LinkNode* L;
	InitList(L);
}
