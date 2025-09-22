/*
实验  单链表
注意：本次作业，main（）中可以调用linklist.cpp中的初始化、创建和释放函数;
自己定义的子函数中必须写基本语句，不能调用linklist.cpp中的函数，可以调用自己写的子函数
参考单链表的基本运算，设计有序单链表的基本运算，主要功能函数如下，
1）初始化有序单链表L，L为空表。
2）main（）中存放一组有序数建立有序单链表，或产生一组随机数建立单链表并对单链表排序。
3）求有序单链表L的长度。
4）有序单链表L中取出第i个元素。
5）定位函数，确定有序单链表L值为e元素的位置。
6）在有序单链表L插入一个值为e的元素，使其仍有序。
7）假设值为e的元素有多个，删除有序单链表L中所有值为e的元素。
8）假设值为e的元素仅一个，将有序单链表L中值为e元素修改值为e1，使其仍有序。
9）将有序单链表L中属于区间[low,high]的数据取出存入新的有序单链表L1，原链表L不修改。
10）有序单链表LA和有序单链表LB，求出两个集合的并集，并存入LC中。单个集合中不能有重复元素，但LA和LB中可能有重复值。
11）有序单链表LA和有序单链表LB，求出两个集合的交集，并存入LC中。单个集合中不能有重复元素，但LA和LB中可能有重复值。
12）有序单链表LA和有序单链表LB，求出LA与LB的差集，并存入LC中。单个集合中不能有重复元素，但LA和LB中可能有重复值。

*/
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
typedef int ElemType;
typedef struct LNode {
	ElemType data;
	struct LNode *next;		//指向后继结点
} LinkNode;					//声明单链表结点类型



// 1）初始化有序单链表L,L为空表
void InitList(LinkNode *&L) {
	L = (LinkNode *)malloc(sizeof(LinkNode));  	//创建头结点
	L->next = NULL;
}
void DestroyList(LinkNode *&L) {
	LinkNode *pre = L,*p = pre->next;
	while (p != NULL) {
		free(pre);
		pre = p;
		p = pre->next;
	}
	free(pre);
}

int LengthList(LinkNode *&L) {
	LinkNode *p = L;
	int n = 0;
	while (p->next != NULL) {
		n++;
		p = p->next;
	}
	return n;
}

void DisList(LinkNode *&L) {		//打印单链表
	LinkNode *p = L->next;
	printf("List: ");
	while (p != NULL) {
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}


// 4）有序单链表L中取出第i个元素（i从1开始）
int GetElem(LinkNode *L, int i, ElemType &e) {
	int j = 1;
	LinkNode *p = L->next;
	while (p != NULL && j < i) {
		j++;
		p = p->next;
	}
	if (p == NULL) return 0; // 不存在第i个结点
	e = p->data;
	return 1;
}

// 5）定位函数，确定有序单链表L值为e元素的位置（返回位置，从1开始）
int LocateElem(LinkNode *L, ElemType e) {
	int i = 1;
	LinkNode *p = L->next;
	while (p != NULL && p->data < e) {
		i++;
		p = p->next;
	}
	if (p != NULL && p->data == e)
		return i;
	else
		return 0; // 未找到
}

// 6）在有序单链表L插入一个值为e的元素，使其仍有序
void InsertElem(LinkNode *L, ElemType e) {
	LinkNode *p = L;
	while (p->next != NULL && p->next->data < e) {
		p = p->next;
	}
	// 如果值已存在，可选择不插入（保持集合无重复），这里按集合处理，不插入重复值
	if (p->next != NULL && p->next->data == e)
		return;

	LinkNode *s = (LinkNode *)malloc(sizeof(LinkNode));
	s->data = e;
	s->next = p->next;
	p->next = s;
}

// 7）删除有序单链表L中所有值为e的元素
void DeleteElemAll(LinkNode *L, ElemType e) {
	LinkNode *p = L;
	while (p->next != NULL) {
		if (p->next->data == e) {
			LinkNode *q = p->next;
			p->next = q->next;
			free(q);
		} else if (p->next->data > e) {
			break; // 后面不可能再有e
		} else {
			p = p->next;
		}
	}
}

// 8）将有序单链表L中值为e的元素修改为e1，使其仍有序
void ModifyElem(LinkNode *L, ElemType e, ElemType e1) {
	// 先删除所有e
	DeleteElemAll(L, e);
	// 再插入e1（保持有序）
	InsertElem(L, e1);
}

// 9）将有序单链表L中属于区间[low,high]的数据取出存入新的有序单链表L1，原链表L不修改
void RangeExtract(LinkNode *L, LinkNode *&L1, ElemType low, ElemType high) {
	InitList(L1);
	LinkNode *p = L->next;
	while (p != NULL) {
		if (p->data >= low && p->data <= high) {
			InsertElem(L1, p->data);
		}
		p = p->next;
	}
}

// 10）求两个有序单链表LA和LB的并集，存入LC（无重复）
void UnionList(LinkNode *LA, LinkNode *LB, LinkNode *&LC) {
	InitList(LC);
	LinkNode *pa = LA->next, *pb = LB->next;

	while (pa != NULL && pb != NULL) {
		if (pa->data < pb->data) {
			InsertElem(LC, pa->data);
			pa = pa->next;
		} else if (pa->data > pb->data) {
			InsertElem(LC, pb->data);
			pb = pb->next;
		} else {
			InsertElem(LC, pa->data);
			pa = pa->next;
			pb = pb->next;
		}
	}
	// 处理剩余部分
	while (pa != NULL) {
		InsertElem(LC, pa->data);
		pa = pa->next;
	}
	while (pb != NULL) {
		InsertElem(LC, pb->data);
		pb = pb->next;
	}
}

// 11）求两个有序单链表LA和LB的交集，存入LC
void IntersectList(LinkNode *LA, LinkNode *LB, LinkNode *&LC) {
	InitList(LC);
	LinkNode *pa = LA->next, *pb = LB->next;

	while (pa != NULL && pb != NULL) {
		if (pa->data < pb->data) {
			pa = pa->next;
		} else if (pa->data > pb->data) {
			pb = pb->next;
		} else {
			InsertElem(LC, pa->data); // 相等才插入
			pa = pa->next;
			pb = pb->next;
		}
	}
}

// 12）求LA与LB的差集（LA - LB），即属于LA但不属于LB的元素
void DiffList(LinkNode *LA, LinkNode *LB, LinkNode *&LC) {
	InitList(LC);
	LinkNode *pa = LA->next, *pb = LB->next;

	while (pa != NULL && pb != NULL) {
		if (pa->data < pb->data) {
			InsertElem(LC, pa->data);
			pa = pa->next;
		} else if (pa->data > pb->data) {
			pb = pb->next;
		} else {
			// 相等，都不插入（差集排除公共部分）
			pa = pa->next;
			pb = pb->next;
		}
	}
	// LA剩余部分都属于差集
	while (pa != NULL) {
		InsertElem(LC, pa->data);
		pa = pa->next;
	}
}

// 尾插法创建有序单链表
void CreateSortedList(LinkNode *&L, ElemType a[], int n) {
	InitList(L);
	for (int i = 0; i < n; i++) {
		InsertElem(L, a[i]);
	}
}

int main() {
	LinkNode *L, *L1, *LA, *LB, *LC;
	ElemType a[] = {1, 3, 5, 6, 7, 8, 9};
	ElemType b[] = {2, 3, 5, 7, 10, 12};
	int len;
	ElemType e;

	// 1）初始化
	InitList(L);

	// 2）建立有序单链表
	for (int i = 0; i < 7; i++) {
		InsertElem(L, a[i]);
	}
	printf("初始化并插入元素后: ");
	DisList(L);

	// 3）求长度
	len = LengthList(L);
	printf("链表长度: %d\n", len);

	// 4）取第3个元素
	if (GetElem(L, 3, e)) {
		printf("第3个元素是: %d\n", e);
	}

	// 5）查找值为5的元素位置
	int pos = LocateElem(L, 5);
	printf("值为5的元素位置: %d\n", pos);

	// 6）插入元素4
	InsertElem(L, 4);
	printf("插入4后: ");
	DisList(L);

	// 7）删除所有值为5的元素
	DeleteElemAll(L, 5);
	printf("删除所有5后: ");
	DisList(L);

	// 8）将值为6的元素改为10
	ModifyElem(L, 6, 10);
	printf("将6改为10后: ");
	DisList(L);

	// 9）提取区间[3,8]的元素到L1
	RangeExtract(L, L1, 3, 8);
	printf("区间[3,8]的元素: ");
	DisList(L1);

	//创建LA和LB用于集合运算
	CreateSortedList(LA, a, 7);
	CreateSortedList(LB, b, 6);

	// 10)并集
	UnionList(LA, LB, LC);
	printf("LA和LB的并集: ");
	DisList(LC);
	DestroyList(LC);

	// 11)交集
	IntersectList(LA, LB, LC);
	printf("LA和LB的交集: ");
	DisList(LC);
	DestroyList(LC);

	// 12)差集 LA - LB
	DiffList(LA, LB, LC);
	printf("LA - LB 的差集: ");
	DisList(LC);

	// 释放内存
	DestroyList(L);
	DestroyList(L1);
	DestroyList(LA);
	DestroyList(LB);
	DestroyList(LC);

	return 0;
}

