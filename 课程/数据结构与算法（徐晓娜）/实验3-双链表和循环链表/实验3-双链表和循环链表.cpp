/*
typedef  int ElemType;

typedef struct Dnode

{   Elemtype data;                          //数据元素

struct Dnode  * prior, * next;     //指针

int freq;

} DlinkList;

注意：

将题目要求定义为子函数，子函数中只能写基本语句完成功能。

main()函数中可以调用dlinklist.cpp和clinklist.cpp中的函数。

在main（）函数中调用子函数进行测试。



1、设有一个双链表h,每个结点中除了有prior、data和next几个域以外,还有一个访问频度域freq,
在链表被启用之前,其值均初始化为零。每当进行 Locatenode(h,x)运算时,令元素值为x的结点中freq域的值加1,
并调整表中结点的次序,使其按访问频度的递减次序排列,以便使频繁访问的结点总是靠近表头。
试写一个符合上述要求的 Locatenode运算的算法。链表中元素值无重复。

2、有序循环单链表rear中,  中位数的元素值。


*/
#include<stdio.h>
#include<malloc.h>
typedef int ElemType;
typedef struct DNode {
	ElemType data;
	struct DNode *prior,*next;
	int freq;
} DLinkNode;

void ListCreateF(DLinkNode *&L, ElemType a[], int n);		//头插法建立双链表
void ListCreateR(DLinkNode *&L, ElemType a[], int n);		//尾插法建立双链表
void ListDestory(DLinkNode *&L);							//删除链表
void ListDisplay(DLinkNode *&L);							//展示双链表及freq值
bool Locatenode(DLinkNode *&h, ElemType x);					//访问双链表并按频度排序


void ListLinkCreate(DLinkNode *&L, ElemType a[], int n);	//尾插法建立循环单链表
void ListLinkMedian(DLinkNode *&L);							//求循环单链表中位数
void  ListLinkMedian(DLinkNode *&L);						//展示循环单链表

//头插法建立双链表
void ListCreateF(DLinkNode *&L, ElemType a[], int n) {
	DLinkNode *s;
	L = (DLinkNode*)malloc(sizeof(DLinkNode));                //头结点
	L->next = L->prior = NULL;
	for (int i = 0; i < n; i++) {
		s = (DLinkNode*)malloc(sizeof(DLinkNode));            //创建新结点
		s->data = a[i];
		s->next = L->next;
		if (L->next != NULL)L->next->prior = s;
		s->prior = L;
		L->next = s;
		s->freq = 0;
	}
}
//尾插法建立双链表
void ListCreateR(DLinkNode *&L, ElemType a[], int n) {
	DLinkNode *s,*p;
	L = (DLinkNode*)malloc(sizeof(DLinkNode));
	L->next = L->prior = NULL;
	p = L;
	for (int i = 0; i < n; i++) {
		s = (DLinkNode*)malloc(sizeof(DLinkNode));
		s->data = a[i];
		s->freq = 0;
		s->prior = p;
		p->next = s;
		s->next = NULL;
		p = s;
	}
}


//删除链表
void ListDestory(DLinkNode *&L) {
	DLinkNode *pre = L,*p = pre->next;
	while (p != NULL) {
		free(pre);
		pre = p;
		p = pre->next;
	}
	free(pre);
}

//展示双链表及freq值
void ListDisplay(DLinkNode *&L) {
	DLinkNode *p = L;
	printf("List:(data,freq)");
	while (p->next != NULL) {
		p = p->next;
		printf("(%d,%d) ", p->data, p->freq);
	}
	printf("\n");
}


//访问双链表并按频度排序
bool Locatenode(DLinkNode *&h, ElemType x) {
	//若找到x则排序并返回true，否则返回false
	DLinkNode *p = h;
	bool flag = false;
	//找到x并将对应freq+1，若找不到则返回false
	while (p->next != NULL) {
		p = p->next;
		if (p->data == x) {
			p->freq++;
			flag = true;
			break;
		}
	}
	//若成功找到，判断x对应freq是否比前一个节点大，若比前一个节点大则前移一个节点，直到不大于前一个节点
	if (flag) {

		DLinkNode *pre = p->prior;
		if (pre == NULL) {
		} else {
			while (pre->prior != NULL && pre->freq < p->freq) {
				pre->prior->next = p;
				p->prior = pre->prior;
				pre->next = p->next;
				p->next->prior = pre;
				pre->prior = p;
				p->next = pre;
				pre = p->prior;
			}

		}
	}

	return flag;

}
//尾插法建立循环单链表
void ListLinkCreate(DLinkNode *&L, ElemType a[], int n) {
	DLinkNode*s,*p;
	L = (DLinkNode*)malloc(sizeof(DLinkNode));
	L->prior = NULL;
	L->next = L;
	p = L;
	for (int i = 0; i < n; i++) {
		s = (DLinkNode*)malloc(sizeof(DLinkNode));
		s->data = a[i];
		s->prior = NULL;
		s->next = NULL;
		p->next = s;
		p = s;
	}
	p->next = L;
}
//展示循环单链表
void ListLinkDisplay(DLinkNode *&L) {
	DLinkNode *p = L->next;
	printf("\nList:");
	while (p != L) {
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}
//求循环单链表中位数
void ListLinkMedian(DLinkNode *&L) {
	DLinkNode *p;
	float m;
	int n = 0;
	p = L;
	//确定链表节点个数n，不包括头节点
	while (p->next != L) {
		p = p->next;
		n++;
	}
	//找中位数
	p = L;
	for (int i = 0; i < n / 2; i++) {
		p = p->next;

	}
	if (n % 2 == 0) {
		m = float((p->data + p->next->data) ) / 2;
	} else {
		m = p->next->data;
	}
	printf("中位数为%f", m);
}
int main() {
	//创建双链表h，验证Locatenode算法
	DLinkNode *h;
	ElemType a[6] = {1, 2, 3, 4, 5, 6};
	ListCreateF(h, a, 6);
	ListDisplay(h);

	//调用Locatenode
	for (int i = 0; i <= 3; i++) {
		Locatenode(h, 3);
		Locatenode(h, 5);
	}
	for (int i = 0; i <= 4; i++) {
		Locatenode(h, 6);
	}
	Locatenode(h, 4);
	printf("分别访问4次元素3 ，4次元素5 ，6次元素6 ，1次元素4 \n");
	ListDisplay(h);
	ListDestory(h);

	//创建循环单链表并求中位数
	DLinkNode *rear;
	ElemType b[6] = {1, 2, 3, 4, 5, 6};
	ListLinkCreate(rear, b, 6);
	ListLinkDisplay(rear);
	ListLinkMedian(rear);
	ListDestory(rear);

	return 0;
}

