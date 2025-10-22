/*
本次作业起，增加如下规定：

1. 自己写的函数的所有形参都必须包含学号的最后两位，假如学号为24010012，则定义为fun1（int a12mn,char bk12[10],……）,形参中要包含该同学的学号最后两位12

2. 假如运行结果中有输出字符串的语句，也要包含学号的最后两位，printf（“hello12”）;


实验  栈和队列的应用

（一）实验目的及要求

掌握栈和队列的基本运算，分析二者的相同点和不同点。

（二）实验内容


将题目1.3要求定义为子函数，子函数中不能调用第三章资料中给的函数，可以调用自己定义的函数。

main()函数中可以调用第三章资料中给的函数。

在main（）函数中调用子函数进行测试。




1、设计算法实现两个栈共享存储空间的基本运算，初始化initstack_d(&S)，入栈push(&S,i,e)，出栈pop(&S,i,&e)操作。注意两个不同栈顶指针的设置。

2、判断用户输入的中缀表达式是否合法（第一要求是各类括号是否匹配; 第二要求是小点的括号中不能包含大点的括号; 第三要求是整个表达式是否合法，根据自己能力选做），如果合法，计算结果并显示出来。表达式中的符号为+、-、*、/、（、）、[、]、{、}。表达式中数字为整数。

3、请设计一个队列，要求满足：①初始时队列为空；②入队时，允许增加队列占用空间；③出队后，出队元素所占用的空间可重复使用，即整个队列所占用的空间只增不减；④入队操作和出队操作的时间复杂度始终保持为O(1)。请回答下列问题：

（1）该队列是应选择链式存储结构，还是应选择顺序存储结构？
	答：链式
（2）画出队列的初始状态，并给出判断队空和队满的条件。
	答：循环链表构成队列

（3）试编写算法分别实现队列初始化、入队列和出队列操作。
*/
/*陈怡冰 24012022*/

#include<stdio.h>
#include<malloc.h>
#define MaxSize 100
typedef char ElemType;
typedef struct {
	ElemType data[MaxSize];				//数据域
	int top1;							//栈顶1
	int top2;							//栈顶2

} SqStack;								//顺序栈类型

typedef struct DataNode {
	ElemType data;
	struct DataNode *next;
} DataNode;								//链队数据结点类型

typedef struct {
	DataNode *front;
	DataNode *rear;
} LinkQuNode;							//链队类型

void initstack_d(SqStack &S22) {
	S22.top1 = -1;
	S22.top2 = MaxSize;
}

bool push(SqStack &S22, int i22, ElemType e22) {
	//i22==1	入栈1
	//i22==2	入栈2
	if (S22.top1 == S22.top2 - 1) {
		return false;
	}
	if (i22 == 1) {
		S22.top1++;
		S22.data[S22.top1] = e22;
	} else if (i22 == 2) {
		S22.top2--;
		S22.data[S22.top2] = e22;
	} else {
		return false;
	}
	return true;
}

bool pop(SqStack &S22, int i22, ElemType &e22) {
	//i22==1	入栈1
	//i22==2	入栈2
	if (i22 == 1) {
		if (S22.top1 == -1) {
			return false;
		}
		e22 = S22.data[S22.top1];
		S22.top1--;
		return true;
	} else if (i22 == 2) {
		if (S22.top2 == MaxSize) {
			return false;
		}
		e22 = S22.data[S22.top2];
		S22.top2++;
		return true;
	} else {
		return false;
	}
}

bool check(ElemType *exp22) {
	int i = 0;
	int level = 0;						//当前括号层级 3-（）	2-[]	1-{}
	int prel = 0;						//之前括号层级
	SqStack Optr;						//左括号栈
	initstack_d(Optr);
	ElemType ch;
	ElemType next;
	ElemType e;
	while (exp22[i] != '\0') {
		ch = exp22[i];
		next = exp22[i + 1];
		if (ch >= '0' && ch <= '9') {
			if (next == '(' || next == '[' || next == '{') {
				printf("表达式不合法22\n");
				return false;
			}

		} else if (ch == '(' || ch == '[' || ch == '{') {
			if (next == '+' || next == '-' || next == '*' || next == '/' || next == ')' || next == ']' || next == '}') {
				printf("表达式不合法22\n");
				return false;
			}
			switch (ch) {
				case '(':
					level = 3;
					break;
				case '[':
					level = 2;
					break;
				case '{':
					level = 1;
					break;
			}
			if (level <= prel) {
				printf("小括号不可包含大括号22\n");
				return false;
			}
			prel = level;
			push(Optr, 1, ch);
		} else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
			if (next == ')' || next == ']' || next == '}' || next == '+' || next == '-' || next == '*' || next == '/' ) {
				printf("表达式不合法22\n");
				return false;

			}

		} else if (ch == ')' || ch == ']' || ch == '}') {
			if (next == '(' || next == '{' || next == '[') {
				printf("表达式不合法22\n");
				return false;
			}
			if (Optr.top1 == -1) {
				printf("右括号多余22\n");
				return false;
			}
			pop(Optr, 1, e);
			bool flag = false;
			if ((e == '(' && ch != ')') || (e == '[' && ch != ']') || (e == '{' && ch != '}')) {
				printf("括号不匹配22\n");
				return false;
			}
		}


		i++;
	}
	printf("式子正确22\n");
	return true;
}

void InitQueue(LinkQuNode *&q22) {
	q22 = (LinkQuNode *)malloc(sizeof(LinkQuNode));
	DataNode *p = (DataNode*)malloc(sizeof(DataNode));
	p->next = p;
	q22->front = q22->rear = p;
}

void DestroyQueue(LinkQuNode *&q22) {
	DataNode *p = q22->front->next;
	DataNode *r;
	while (p != q22->front) {
		r = p->next;
		free(p);
		p = r;
	}
	free(q22->front);
	free(q22);
}

void enQueue(LinkQuNode *&q22, ElemType e22) {
	DataNode *p;
	if ( q22->rear->next == q22->front) {	//若队满（存储空间不够）
		p = (DataNode *)malloc(sizeof(DataNode));

		p->next = q22->front;

	} else {
		p = q22->rear->next;




	}
	p->data = e22;
	q22->rear->next = p;
	q22->rear = p;

}

bool deQueue(LinkQuNode *&q22, ElemType &e22) {
	DataNode *t;
	if (q22->rear == q22->front)		//队列为空
		return false;
	t = q22->front->next;				//t指向第一个数据结点
	e22 = t->data;
	q22->front->next = t->next;
	return true;
}

void disQueue(LinkQuNode *&q22) {
	if (q22->front->next == q22->front) {
		printf("队列为空22\n");
		return;
	}
	printf("队列22: ");
	DataNode *p = q22->front->next;
	while (p != q22->rear) {
		printf("%c ", p->data);
		p = p->next;
	}
	if (p == q22->rear) {
		printf("%c ", p->data);
	}
	printf("\n");
}

int main() {
	//1.两栈共享存储空间测试
	SqStack S;
	initstack_d(S);
	ElemType a1[5] = {'h', 'e', 'l', 'l', 'o'};			//a1元素依次入栈1
	ElemType a2[5] = {'w', 'o', 'r', 'l', 'd'};			//a2元素依次入栈2
	ElemType e;
	printf("1.  两栈共享存储空间测试22\n");
	printf("入栈1元素：a1={'h','e','l','l','o'}22\n");
	printf("入栈2元素：a2={'w','o','r','l','d'}22\n");
	for (int i = 0; i < 5; i++) {
		push(S, 1, a1[i]);
		push(S, 2, a2[i]);
	}
	printf("栈1依次出栈22：\n");
	while (pop(S, 1, e)) {
		printf("%c ", e);
	}
	printf("\n");
	printf("栈2依次出栈22：\n");
	while (pop(S, 2, e)) {
		printf("%c ", e);
	}

	//2.检查中缀表达式
	printf("\n\n2.  检查中缀表达式22\n");
	ElemType s1[20] = "1+(3/2-6)";
	ElemType s2[20] = "1+(3/2-6))";
	ElemType s3[20] = "1+({3/2}-6)";
	ElemType s4[20] = "1+(3/2--6)";
	printf("检查1：%s\t\t", s1);
	check(s1);
	printf("检查2：%s\t\t", s2);
	check(s2);
	printf("检查3：%s\t\t", s3);
	check(s3);
	printf("检查4：%s\t\t", s4);
	check(s4);

	//3.队列测试
	printf("\n\n3.  队列测试22\n");
	LinkQuNode *L;
	InitQueue(L);
	ElemType e1 = 'a', e2 = 'b', e3;
	printf("入队22：%c\n", e1);
	enQueue(L, e1);
	printf("入队22：%c\n", e2);
	enQueue(L, e2);
	disQueue(L);

	deQueue(L, e3);
	printf("出队22:e=%c\n", e3);
	disQueue(L);

	deQueue(L, e3);
	printf("出队22:e=%c\n", e3);
	disQueue(L);


	DestroyQueue(L);
	return 0;

}






