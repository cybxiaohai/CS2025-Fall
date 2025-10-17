/*
第二章选做作业

1.两个一元n次多项式(anxn+an-1xn-1+an-2xn-2+....+a1x1+a0)的相加。两个单链表节点指数相同时，系数相加。指数1...n可能不全都出现。

注意结点结构和数据类型 如下。

系数coef 指数expn 指针 next


*/
#include<malloc.h>
#include<stdio.h>

typedef struct {
	float coef; // 系数
	int expn;   // 指数
} ElemType;

typedef struct LNode {
	ElemType data;
	struct LNode *next;
} LinkList;

//尾插法建立单链表
void LinkCreatR(LinkList *&L, ElemType a[], int n) {
	LinkList *s,*r;
	L = (LinkList*)malloc(sizeof(LinkList));
	r = L;
	for (int i = 0; i < n; i++) {
		s = (LinkList*)malloc(sizeof(LinkList));
		r->next = s;
		s->data = a[i];
		r = s;
	}
	r->next = NULL;
}

//建立ElemType数组
void ElemCreat(ElemType *a, int n, float *a_coef, int *a_expn) {
	for (int i = 0; i < n; i++) {
		(a + i)->coef = *(a_coef + i);
		(a + i)->expn = *(a_expn + i);
	}
}

//清除链表
void LinkDes(LinkList*&L) {
	LinkList *pre = L,*p = pre->next;
	while (p != NULL) {
		free(pre);
		pre = p;
		p = pre->next;
	}
	free(pre);
}

//展示链表
void LinkDis(LinkList*&L) {
	LinkList *p = L->next;
	while (p != NULL) {
		printf("a%d=%.2f\t\t", p->data.expn, p->data.coef);
		p = p->next;
	}
	printf("\n");
}

//多项式相加（L=L1+L2）
LinkList* LinkAdd(LinkList *&L1, LinkList*&L2) {
	//创建相加新链表头节点
	LinkList*L = (LinkList*)malloc(sizeof(LinkList));
	L->next = NULL;
	LinkList*p = L,*p1 = L1->next,*p2 = L2->next;
	while (p1 != NULL && p2 != NULL) {
		//按级数从小到大编辑新链表，若仅一条链表含该级数，则直接并入节点
		if (p1->data.expn < p2->data.expn) {
			p->next = p1;
			p1 = p1->next;
		} else if (p1->data.expn > p2->data.expn) {
			p->next = p2;
			p2 = p2->next;

		}
		//若两条链表均含该级数，则系数相加
		else {
			p1->data.coef += p2->data.coef;
			p->next = p1;
			LinkList *s = p2;
			p1 = p1->next;
			p2 = p2->next;
			free(s);

		}
		p = p->next;
	}
	//剩余部分相加，清除残余头节点
	p->next = (p1 != NULL) ? p1 : p2;
	free(L1);
	free(L2);

	return L;

}


int main() {
	//创建ElemType数组
	float c1[5] = {1.2, 2.2, 4, 3, 5};
	float c2[3] = {3, 6, 6};
	int e1[5] = {0, 1, 2, 3, 4};
	int e2[3] = {1, 2, 3};
	ElemType *a1,*a2;
	a1 = (ElemType*)malloc(sizeof(ElemType) * 5);
	a2 = (ElemType*)malloc(sizeof(ElemType) * 3);
	ElemCreat(a1, 5, c1, e1);
	ElemCreat(a2, 3, c2, e2);

	//创建单链表并展示
	LinkList *L1,*L2,*L;
	LinkCreatR(L1, a1, 5);
	LinkCreatR(L2, a2, 3);
	printf("创建L1\n");
	LinkDis(L1);
	printf("创建L2\n");
	LinkDis(L2);

	//单链表相加并展示
	L = LinkAdd(L1, L2);
	printf("多项式相加：\n");
	LinkDis(L);
	LinkDes(L);


	return 0;
}
