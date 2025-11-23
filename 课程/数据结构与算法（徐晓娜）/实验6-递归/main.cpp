/*陈怡冰24012022*/

#include <stdio.h>
#include <stdlib.h>
typedef int ElemType;
// ====================  listring.cpp ====================
typedef struct snode {
	char data;
	struct snode *next;
} LinkStrNode;

// 串赋值：将字符数组赋给链式串
void StrAssign(LinkStrNode *&s, char cstr[]) {	//字符串常量cstr赋给串s
	int i;
	LinkStrNode *r,*p;
	s = (LinkStrNode *)malloc(sizeof(LinkStrNode));
	r = s;						//r始终指向尾结点
	for (i = 0; cstr[i] != '\0'; i++) {
		p = (LinkStrNode *)malloc(sizeof(LinkStrNode));
		p->data = cstr[i];
		r->next = p;
		r = p;
	}
	r->next = NULL;
}

// 销毁串
void DestroyStr(LinkStrNode *&s) {
	LinkStrNode *pre = s,*p = s->next;	//pre指向结点p的前驱结点
	while (p != NULL) {				//扫描链串s
		free(pre);					//释放pre结点
		pre = p;						//pre、p同步后移一个结点
		p = pre->next;
	}
	free(pre);						//循环结束时,p为NULL,pre指向尾结点,释放它
}
// 串复制
void StrCopy(LinkStrNode *&s, LinkStrNode *t) {	//串t复制给串s
	LinkStrNode *p = t->next,*q,*r;
	s = (LinkStrNode *)malloc(sizeof(LinkStrNode));
	r = s;						//r始终指向尾结点
	while (p != NULL) {			//将t的所有结点复制到s
		q = (LinkStrNode *)malloc(sizeof(LinkStrNode));
		q->data = p->data;
		r->next = q;
		r = q;
		p = p->next;
	}
	r->next = NULL;
}

// 串相等比较
bool StrEqual(LinkStrNode *s, LinkStrNode *t) {	//判串相等
	LinkStrNode *p = s->next,*q = t->next;
	while (p != NULL && q != NULL && p->data == q->data) {
		p = p->next;
		q = q->next;
	}
	if (p == NULL && q == NULL)
		return true;
	else
		return false;
}


// 串长度
int StrLength(LinkStrNode *s) {	//求串长
	int i = 0;
	LinkStrNode *p = s->next;
	while (p != NULL) {
		i++;
		p = p->next;
	}
	return i;
}

// 串连接
LinkStrNode *Concat(LinkStrNode *s, LinkStrNode *t) {	//串连接
	LinkStrNode *str,*p = s->next,*q,*r;
	str = (LinkStrNode *)malloc(sizeof(LinkStrNode));
	r = str;
	while (p != NULL) {			//将s的所有结点复制到str
		q = (LinkStrNode *)malloc(sizeof(LinkStrNode));
		q->data = p->data;
		r->next = q;
		r = q;
		p = p->next;
	}
	p = t->next;
	while (p != NULL) {			//将t的所有结点复制到str
		q = (LinkStrNode *)malloc(sizeof(LinkStrNode));
		q->data = p->data;
		r->next = q;
		r = q;
		p = p->next;
	}
	r->next = NULL;
	return str;
}
// 取子串：从第 i 个字符起取 j 个字符（i 从 1 开始）
LinkStrNode *SubStr(LinkStrNode *s, int i, int j) {	//求子串
	int k;
	LinkStrNode *str,*p = s->next,*q,*r;
	str = (LinkStrNode *)malloc(sizeof(LinkStrNode));
	str->next = NULL;
	r = str;						//r指向新建链表的尾结点
	if (i <= 0 || i > StrLength(s) || j < 0 || i + j - 1 > StrLength(s))
		return str;				//参数不正确时返回空串
	for (k = 0; k < i - 1; k++)
		p = p->next;
	for (k = 1; k <= j; k++) {		//将s的第i个结点开始的j个结点复制到str
		q = (LinkStrNode *)malloc(sizeof(LinkStrNode));
		q->data = p->data;
		r->next = q;
		r = q;
		p = p->next;
	}
	r->next = NULL;
	return str;
}
// 插入串
LinkStrNode *InsStr(LinkStrNode *s, int i, LinkStrNode *t) {	//串插入
	int k;
	LinkStrNode *str,*p = s->next,*p1 = t->next,*q,*r;
	str = (LinkStrNode *)malloc(sizeof(LinkStrNode));
	str->next = NULL;
	r = str;								//r指向新建链表的尾结点
	if (i <= 0 || i > StrLength(s) + 1)		//参数不正确时返回空串
		return str;
	for (k = 1; k < i; k++) {				//将s的前i个结点复制到str
		q = (LinkStrNode *)malloc(sizeof(LinkStrNode));
		q->data = p->data;
		r->next = q;
		r = q;
		p = p->next;
	}
	while (p1 != NULL) {				//将t的所有结点复制到str
		q = (LinkStrNode *)malloc(sizeof(LinkStrNode));
		q->data = p1->data;
		r->next = q;
		r = q;
		p1 = p1->next;
	}
	while (p != NULL) {					//将结点p及其后的结点复制到str
		q = (LinkStrNode *)malloc(sizeof(LinkStrNode));
		q->data = p->data;
		r->next = q;
		r = q;
		p = p->next;
	}
	r->next = NULL;
	return str;
}
// 删除子串
LinkStrNode *DelStr(LinkStrNode *s, int i, int j) {	//串删去
	int k;
	LinkStrNode *str,*p = s->next,*q,*r;
	str = (LinkStrNode *)malloc(sizeof(LinkStrNode));
	str->next = NULL;
	r = str;						//r指向新建链表的尾结点
	if (i <= 0 || i > StrLength(s) || j < 0 || i + j - 1 > StrLength(s))
		return str;				//参数不正确时返回空串
	for (k = 0; k < i - 1; k++) {		//将s的前i-1个结点复制到str
		q = (LinkStrNode *)malloc(sizeof(LinkStrNode));
		q->data = p->data;
		r->next = q;
		r = q;
		p = p->next;
	}
	for (k = 0; k < j; k++)				//让p沿next跳j个结点
		p = p->next;
	while (p != NULL) {				//将结点p及其后的结点复制到str
		q = (LinkStrNode *)malloc(sizeof(LinkStrNode));
		q->data = p->data;
		r->next = q;
		r = q;
		p = p->next;
	}
	r->next = NULL;
	return str;
}

// 显示串
void DispStr(LinkStrNode *s) {	//输出串
	LinkStrNode *p = s->next;
	while (p != NULL) {
		printf("%c", p->data);
		p = p->next;
	}
	printf("\n");
}
//======================================================================
// ==================== 任务1：递归计算 x 的 n 次方 ====================
double power(double x22, int n22) {
	if (n22 == 0)
		return 1;
	else if (n22 > 0)
		return x22 * power(x22, n22 - 1);
	else
		return 1.0 / power(x22, -n22);
}

// ==================== 任务2：删除单链表中值为x的所有节点 ====================
typedef struct LNode {
	int data;
	struct LNode* next;
} LinkNode;

// ======================linklist.cpp===================================
void InitList(LinkNode *&L) {
	L = (LinkNode *)malloc(sizeof(LinkNode));  	//创建头结点
	L->next = NULL;
}
bool ListInsert(LinkNode *&L, int i, ElemType e) {
	int j = 0;
	LinkNode *p = L,*s;
	if (i <= 0) return false;			//i错误返回假
	while (j < i - 1 && p != NULL) {	//查找第i-1个结点p
		j++;
		p = p->next;
	}
	if (p == NULL)					//未找到位序为i-1的结点
		return false;
	else {						//找到位序为i-1的结点*p
		s = (LinkNode *)malloc(sizeof(LinkNode)); //创建新结点*s
		s->data = e;
		s->next = p->next;			//将s结点插入到结点p之后
		p->next = s;
		return true;
	}
}
void DispList(LinkNode *L) {
	LinkNode *p = L->next;
	while (p != NULL) {
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
}
//================================================================
// 删除所有值为x的节点
void ListDeleteAll(LinkNode*& L22, int x22) {
	if (L22 == NULL) return;
	if (L22->data == x22) {
		LinkNode* temp22 = L22;
		L22 = L22->next;
		free(temp22);
		ListDeleteAll(L22, x22);
	} else {
		ListDeleteAll(L22->next, x22);
	}
}

// ==================== 任务3：递归实现串的替换 Replace(S, T, R) ====================
void Replace(LinkStrNode*&S22, LinkStrNode* T22, LinkStrNode* R22, LinkStrNode*&result22, int start22) {
	// 递归出口：超出范围
	if (start22 > StrLength(S22)) {
		result22 = (LinkStrNode*)malloc(sizeof(LinkStrNode));
		result22->next = NULL;
		return;
	}

	// 查找 T 在 S 中从 start22 开始的第一次出现位置（字符位置，从1开始）
	int pos22 = -1;
	for (int i22 = start22; i22 <= StrLength(S22) - StrLength(T22) + 1; i22++) {
		LinkStrNode *p = S22->next, *q = T22->next;
		int offset22 = 0;
		while (offset22 < i22 - 1 && p != NULL) {
			p = p->next;
			offset22++;
		}
		int match22 = 1;
		LinkStrNode *temp_p = p;
		while (q != NULL && temp_p != NULL) {
			if (temp_p->data != q->data) {
				match22 = 0;
				break;
			}
			temp_p = temp_p->next;
			q = q->next;
		}
		if (match22 && q == NULL) {
			pos22 = i22;
			break;
		}
	}

	if (pos22 == -1) {
		// 未找到，返回剩余部分
		result22 = SubStr(S22, start22, StrLength(S22) - start22 + 1);
		return;
	}


	LinkStrNode *left22, *rightResult22, *temp1_22, *temp2_22;

	// 左边部分
	left22 = SubStr(S22, start22, pos22 - start22);

	// 递归处理右边
	Replace(S22, T22, R22, rightResult22, pos22 + StrLength(T22));

	// 拼接：left + R
	temp1_22 = Concat(left22, R22);
	// 拼接：temp1 + rightResult
	temp2_22 = Concat(temp1_22, rightResult22);

	// 返回结果
	StrCopy(result22, temp2_22);

	// 释放临时空间（可选）
	DestroyStr(*&left22);
	DestroyStr(*&rightResult22);
	DestroyStr(*&temp1_22);
	DestroyStr(*&temp2_22);
}

// =================== 主函数 ===================
int main() {
	printf("=== 实验6：递归算法 (by22) ===\n");

	// ----- 任务1：x^n -----
	double res1 = power(2.0, 4); // x22=2.0, n22=4
	printf("Task1: 2^4 = %.2f (result22)\n", res1);

	// ----- 任务2：链表删除 -----
	LinkNode* list = NULL;
	InitList(list);
	ListInsert(list, 1, 3);
	ListInsert(list, 2, 2);
	ListInsert(list, 3, 3);
	ListInsert(list, 4, 4);
	ListInsert(list, 5, 3);

	printf("Task2: 删除前 list22: ");
	DispList(list);

	ListDeleteAll(list, 3); // x22=3

	printf("删除所有3后 list22: ");
	DispList(list);

	// ----- 任务3：串替换 -----
	LinkStrNode *S, *T, *R, *result;

	StrAssign(S, "hello22world22test22");
	StrAssign(T, "22");
	StrAssign(R, "XX");

	printf("Task3: Replace(S, T, R) by22\n");
	printf("S: ");
	DispStr(S);
	printf("T: ");
	DispStr(T);
	printf("R: ");
	DispStr(R);

	Replace(S, T, R, result, 1); // start22=1（位置从1开始）

	printf("Replace result22: ");
	DispStr(result);

	printf("End of program by22.\n");

	// 清理内存
	DestroyStr(S);
	DestroyStr(T);
	DestroyStr(R);
	DestroyStr(result);

	return 0;
}
