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

（2）画出队列的初始状态，并给出判断队空和队满的条件。

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

bool check(ElemType *s22) {
	int i = 0;
	SqStack*
}



int main() {
	//两栈共享存储空间测试
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




	return 0;


}






