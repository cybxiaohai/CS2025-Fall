/*
（一）实验目的及要求

1、掌握二叉树的递归遍历和非递归遍历设计方法。

2、学会灵活运用二叉树的遍历思想解决实际问题。

（二）实验内容

1.假设二叉树中每个结点值为单个字符，采用二叉链存储结构存储。编写算法,  统计二叉树中度为2的结点的个数。

2.假设二叉树中每个结点值为单个字符，采用二叉链存储结构存储。给定一棵非空二叉树，请在该二叉树中查找给定值的结点（唯一），并输出其双亲。

3.假设二叉树中每个结点值为单个字符，采用二叉链存储结构存储。设计一个算法，求二叉树b的中序遍历序列中第k（1≤k≤二叉树中结点个数）个结点的值。

4.已知二叉树中序遍历序列和后序遍历序列，编写算法建立二叉树，并输出其先序序列。

5.假设二叉树中每个结点值为单个字符，采用二叉链存储结构存储。编写算法求出二叉树中每层结点的个数。（深度遍历和层次遍历两种方法实现）


*/
/*
陈怡冰24012022
*/


//二叉树的基本运算算法
#include <stdio.h>
#include <malloc.h>
#define MaxSize 100
typedef char ElemType;
typedef struct node {
	ElemType data;			//数据元素
	struct node *lchild;	//指向左孩子节点
	struct node *rchild;	//指向右孩子节点
} BTNode;
void CreateBTree(BTNode * &b, char *str) {	//创建二叉树
	BTNode *St[MaxSize],*p = NULL;
	int top = -1, k, j = 0;
	char ch;
	b = NULL;				//建立的二叉树初始时为空
	ch = str[j];
	while (ch != '\0') {	//str未扫描完时循环
		switch (ch) {
			case '(':
				top++;
				St[top] = p;
				k = 1;
				break;		//为左孩子节点
			case ')':
				top--;
				break;
			case ',':
				k = 2;
				break;                      		//为孩子节点右节点
			default:
				p = (BTNode *)malloc(sizeof(BTNode));
				p->data = ch;
				p->lchild = p->rchild = NULL;
				if (b == NULL)                    	 	//*p为二叉树的根节点
					b = p;
				else {								//已建立二叉树根节点
					switch (k) {
						case 1:
							St[top]->lchild = p;
							break;
						case 2:
							St[top]->rchild = p;
							break;
					}
				}
		}
		j++;
		ch = str[j];
	}
}
void DestroyBTree(BTNode *&b) {
	if (b != NULL) {
		DestroyBTree(b->lchild);
		DestroyBTree(b->rchild);
		free(b);
	}
}
BTNode *FindNode(BTNode *b, ElemType x) {
	BTNode *p;
	if (b == NULL)
		return NULL;
	else if (b->data == x)
		return b;
	else {
		p = FindNode(b->lchild, x);
		if (p != NULL)
			return p;
		else
			return FindNode(b->rchild, x);
	}
}
BTNode *LchildNode(BTNode *p) {
	return p->lchild;
}
BTNode *RchildNode(BTNode *p) {
	return p->rchild;
}
int BTHeight(BTNode *b) {
	int lchildh, rchildh;
	if (b == NULL) return (0); 				//空树的高度为0
	else {
		lchildh = BTHeight(b->lchild);	//求左子树的高度为lchildh
		rchildh = BTHeight(b->rchild);	//求右子树的高度为rchildh
		return (lchildh > rchildh) ? (lchildh + 1) : (rchildh + 1);
	}
}
void DispBTree(BTNode *b) {
	if (b != NULL) {
		printf("%c", b->data);
		if (b->lchild != NULL || b->rchild != NULL) {
			printf("(");						//有孩子节点时才输出(
			DispBTree(b->lchild);				//递归处理左子树
			if (b->rchild != NULL) printf(",");	//有右孩子节点时才输出,
			DispBTree(b->rchild);				//递归处理右子树
			printf(")");						//有孩子节点时才输出)
		}
	}
}
/*********************队列基本算法（实验五用到）**************************/
typedef BTNode* ElemType2;
typedef struct {
	ElemType2 data[MaxSize];
	int front, rear;		//队首和队尾指针
} SqQueue;
void InitQueue(SqQueue *&q) {
	q = (SqQueue *)malloc (sizeof(SqQueue));
	q->front = q->rear = 0;
}
void DestroyQueue(SqQueue *&q) {
	free(q);
}
bool QueueEmpty(SqQueue *q) {
	return (q->front == q->rear);
}
bool enQueue(SqQueue *&q, ElemType2 e) {
	if ((q->rear + 1) % MaxSize == q->front)	//队满上溢出
		return false;
	q->rear = (q->rear + 1) % MaxSize;
	q->data[q->rear] = e;
	return true;
}
bool deQueue(SqQueue *&q, ElemType2 &e) {
	if (q->front == q->rear)		//队空下溢出
		return false;
	q->front = (q->front + 1) % MaxSize;
	e = q->data[q->front];
	return true;
}

/**********************************实验所写子函数****************************************/

//1.假设二叉树中每个结点值为单个字符，采用二叉链存储结构存储。编写算法,  统计二叉树中度为2的结点的个数。
int Fuc1(BTNode *b22) {
	//每个子树度为2节点=根（若度为2）+左子树度为2个数+右子树度为2个数
	int n = 0;
	if (b22 != NULL) {
		if (b22->lchild != NULL && b22->rchild != NULL) {
			n++;
		}
		if (b22->lchild != NULL || b22->rchild != NULL) {
			n += Fuc1(b22->lchild);				//递归处理左子树
			n += Fuc1(b22->rchild);				//递归处理右子树
		}
	}
	return n;
}

//2.假设二叉树中每个结点值为单个字符，采用二叉链存储结构存储。给定一棵非空二叉树，请在该二叉树中查找给定值的结点（唯一），并输出其双亲。
BTNode *Fuc2(BTNode *b22, ElemType x22) {
	//以一个双亲节点和其两个孩子节点为单位。
	BTNode *p;
	if (b22 == NULL)
		return NULL;
	else if (b22->lchild != NULL && b22->lchild->data == x22)
		return b22;
	else if (b22->rchild != NULL && b22->rchild->data == x22)
		return b22;
	else {
		p = Fuc2(b22->lchild, x22);
		if (p != NULL)
			return p;
		else
			return Fuc2(b22->rchild, x22);
	}
}

//3.假设二叉树中每个结点值为单个字符，采用二叉链存储结构存储。设计一个算法，求二叉树b的中序遍历序列中第k（1≤k≤二叉树中结点个数）个结点的值。
int Fuc3(BTNode *b22, int k) {
	BTNode *p;
	if (k == 0) {
		return 0;
	}
	if (b22 == NULL) {
		return k;
	} else {
		if (b22->lchild != NULL) {
			k = Fuc3(b22->lchild, k);
		}
		k--;
		if (k == 0) {
			printf("%c\t22\n",  b22->data);
		} else if (b22->rchild != NULL) {}
		k = Fuc3(b22->rchild, k);
	}
	return k;

}

//4.已知二叉树中序遍历序列和后序遍历序列，编写算法建立二叉树，并输出其先序序列。
BTNode* CreateBT2(ElemType *post22, ElemType* in22, int n22) {
	BTNode *b;
	ElemType r,*p;
	int k;
	if (n22 <= 0) {
		return NULL;
	}
	r = *(post22 + n22 - 1);						//根节点值
	b = (BTNode*)malloc(sizeof(BTNode));		//创建二叉树节点b
	b->data = r;
	//在in中找根节点
	for (p = in22; p < in22 + n22; p++) {
		if (*p == r) {
			break;
		}
	}
	k = p - in22;									//k为根节点在in中的下标
	b->lchild = CreateBT2(post22, in22, k);
	b->rchild = CreateBT2(post22 + k, p + 1, n22 - k - 1);
	return b;
}

void DispBTpre(BTNode *b22) {
	BTNode *p;
	if (b22 != NULL) {
		if (b22->lchild != NULL) {
			DispBTpre(b22->lchild);
		}
		printf("%c", b22->data);
		if (b22->rchild != NULL) {
			DispBTpre(b22->rchild);
		}
	}

}


//5.假设二叉树中每个结点值为单个字符，采用二叉链存储结构存储。编写算法求出二叉树中每层结点的个数。（深度遍历和层次遍历两种方法实现）
//深度遍历
void Fuc5d(BTNode *b22, int *c22, int t22) {
	BTNode *p;
	if (b22 != NULL) {
		c22[t22]++;
		if (b22->lchild != NULL) {
			Fuc5d(b22->lchild, c22, t22 + 1);
		}

		if (b22->rchild != NULL) {
			Fuc5d(b22->rchild, c22, t22 + 1);
		}
	}

}

void Fuc5l(BTNode *b22, int *c22) {
	BTNode *p;
	SqQueue *Q;
	InitQueue(Q);

	int t = 0, k = 0, k_next = 0;						//t记录层数-1，k记录本层节点数，k_next记录下层节点数
	enQueue(Q, b22);
	c22[t]++;
	k++;								//根节点处理完毕，第1层1个节点
	while (!QueueEmpty(Q)) {
		deQueue(Q, p);
		k--;
		if (p->lchild != NULL) {
			enQueue(Q, p->lchild);
			c22[t + 1]++;
			k_next++;
		}
		if (p->rchild != NULL) {
			enQueue(Q, p->rchild);
			c22[t + 1]++;
			k_next++;
		}
		if (k == 0) {//当前层数节点处理完毕，下次循环进入下一层
			k = k_next;
			k_next = 0;
			t++;
		}
	}
	DestroyQueue(Q);

}

void Disp5(int *c22) {
	int t = 0;

	printf("节点数：");
	while (*(c22 + t) != 0 && t < 10) {
		printf("第%d层%d个节点,", t + 1, *(c22 + t));
		t++;
	}
	printf("\t22\n");
}






int main() {
	//创建二叉树b
	BTNode *b,*p;
	CreateBTree(b, "A(B(D(K,G)),C(E,F))");
	printf("b: ");
	DispBTree(b);
	printf("\t22\n");

	//1
	printf("1) 树b度为2节点个数为：%d\t22\n", Fuc1(b));

	//2
	ElemType a = 'F';
	p = Fuc2(b, a);
	if (b->data == a) {
		printf("2) b中存在%c节点,无双亲，为根节点。\t22\n", a);
	} else if (p != NULL)
		printf("2) b中存在%c结点,该节点的双亲节点为%c\t22\n", a, p->data);
	else
		printf("2) b中不存在%c结点\t22\n", a);


	//3
	int k = 3;
	printf("3) 第%d个节点值为", k);
	Fuc3(b, k);

	//4
	ElemType* post = "GDBEFCA";
	ElemType* in = "DGBAECF";
	int n = 7;
	printf("4) 后序：%s\t中序：%s\t22\n", post, in);
	BTNode *b2 = CreateBT2(post, in, n);
	printf("b2:");
	DispBTree(b2);
	printf("\t22\n");
	printf("b2前序：");
	DispBTpre(b2);
	printf("\t22\n");

	//5
	printf("5) 22\n");
	int c1[10] = {0};
	int c2[10] = {0};
	Fuc5d(b, c1, 0);
	printf("深度遍历二叉树b:");
	Disp5(c1);
	Fuc5l(b, c2);
	printf("层次遍历二叉树b:");
	Disp5(c2);



	DestroyBTree(b);
}
