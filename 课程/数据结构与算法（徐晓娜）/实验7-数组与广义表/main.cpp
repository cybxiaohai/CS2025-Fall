/*
实验六  数组 和广义表

（一）实验目的及要求

学会以三元组表和十字链表进行矩阵压缩存储常用算法的实现方法。

学会广义表的相关操作

掌握广义表的操作。

（二）实验内容

1. 已知稀疏矩阵采用三元组表压缩存储，试编写算法求稀疏矩阵中所有数的平均数。

2. 已知稀疏矩阵采用十字链表压缩存储，试编写算法修改稀疏矩阵中下标为i，j的元素的元素值，可能从0到非0，也可能从非0到0，也可能从非0到非0。

3. 试编写算法比较两个广义表是否相等。
*/
// 陈怡冰 学号：24012022

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define M 3         			//矩阵行
#define N 4           			//矩阵列
#define Max ((M)>(N)?(M):(N))   //矩阵行列较大者
#define MaxSize 100

// 三元组顺序表定义
typedef int ElemType;

typedef struct {
	int r;          // 行号
	int c;          // 列号
	ElemType d;     // 元素值
} TupNode;          // 三元组定义

typedef struct {
	int rows;       // 行数
	int cols;       // 列数
	int nums;       // 非零元素个数
	TupNode data[MaxSize];
} TSMatrix;         // 三元组顺序表

// 十字链表定义
typedef struct mtxn {
	int row;                    // 行号
	int col;                    // 列号
	struct mtxn *right, *down;  // 向右和向下的指针
	union {
		ElemType value;
		struct mtxn *link;
	} tag;
} MatNode;          // 十字链表类型

// 广义表类型定义
typedef char ElemType22;

typedef struct lnode {
	int tag;        // 结点类型标识
	union {
		ElemType22 data;          // 原子值
		struct lnode *sublist;  // 指向子表的指针
	} val;
	struct lnode *link;         // 指向下一个元素
} GLNode;           // 广义表类型

// 1. 求稀疏矩阵中所有数的平均数（三元组表存储）
double MatrixAverage(TSMatrix *M22) {
	if (M22 == NULL || M22->rows <= 0 || M22->cols <= 0) {
		printf("错误：无效矩阵22\n");
		return 0.0;
	}

	long total22 = 0;
	int totalElements22 = M22->rows * M22->cols;

	// 先累加所有非零元素
	for (int i = 0; i < M22->nums; i++) {
		total22 += M22->data[i].d;
	}

	// 零元素不存储，但值为0，所以平均数需要计算所有元素
	// 非零元素的和除以总元素个数
	double average22 = (double)total22 / totalElements22;

	printf("矩阵平均值22: %.2f\n", average22);
	return average22;
}

// 2. 修改十字链表中下标为i,j的元素值
void ModifyCrossList(MatNode *h22, int i22, int j22, ElemType newValue22) {
	if (h22 == NULL) {
		printf("错误：空矩阵22\n");
		return;
	}

	MatNode *p22, *q22, *pre22;

	// 查找第i22行
	p22 = h22->tag.link;
	for (int k = 0; k < i22 && p22 != NULL; k++) {
		p22 = p22->down;
	}

	if (p22 == NULL) {
		printf("错误：未找到第%d行22\n", i22);
		return;
	}

	// 在第i22行中查找第j22列
	pre22 = p22;
	q22 = p22->right;
	while (q22 != NULL && q22->col < j22) {
		pre22 = q22;
		q22 = q22->right;
	}

	if (newValue22 == 0) {  // 新值为0，需要删除节点
		if (q22 != NULL && q22->col == j22) {
			// 找到节点，删除它
			pre22->right = q22->right;
			free(q22);
			printf("元素位于(%d,%d)删除成功 22\n", i22, j22);
		} else {
			printf("元素位于(%d,%d)处未找到，无需删除22\n", i22, j22);
		}
	} else {  // 新值非0
		if (q22 != NULL && q22->col == j22) {
			// 找到节点，修改值
			q22->tag.value = newValue22;
			printf("元素位于(%d,%d)处已修改为%d 22\n", i22, j22, newValue22);
		} else {
			// 没找到节点，创建新节点
			MatNode *newNode22 = (MatNode*)malloc(sizeof(MatNode));
			newNode22->row = i22;
			newNode22->col = j22;
			newNode22->tag.value = newValue22;
			newNode22->right = q22;
			pre22->right = newNode22;
			printf("新元素已在(%d,%d)处创建，其值为%d 22\n", i22, j22, newValue22);
		}
	}
}

// 3. 比较两个广义表是否相等
int EqualGL(GLNode *g22, GLNode *h22) {
	if (g22 == NULL && h22 == NULL) {
		return 1;  // 都为空，相等
	}
	if (g22 == NULL || h22 == NULL) {
		return 0;  // 一个空一个不空，不相等
	}

	// 比较当前节点
	if (g22->tag != h22->tag) {
		return 0;  // 节点类型不同
	}

	if (g22->tag == 0) {  // 原子节点
		if (g22->val.data != h22->val.data) {
			return 0;  // 原子值不同
		}
	} else {  // 子表节点
		if (!EqualGL(g22->val.sublist, h22->val.sublist)) {
			return 0;  // 子表不相等
		}
	}

	// 递归比较后续节点
	return EqualGL(g22->link, h22->link);
}
//辅助函数：输出三元组
void DispMat(TSMatrix t) {
	int i;
	if (t.nums <= 0)			//没有非零元素时返回
		return;
	printf("\t%d\t%d\t%d\n", t.rows, t.cols, t.nums);
	printf("\t------------------\n");
	for (i = 0; i < t.nums; i++)
		printf("\t%d\t%d\t%d\n", t.data[i].r, t.data[i].c, t.data[i].d);
}

// 辅助函数：创建广义表
GLNode *CreateGL(char *&s) {			//创建由括号表示法表示s的广义表链式存储结构
	GLNode *g;
	char ch = *s++;						//取一个字符
	if (ch != '\0') {					//串未结束判断
		g = (GLNode *)malloc(sizeof(GLNode)); //创建一个新结点
		if (ch == '(') {				//当前字符为左括号时
			g->tag = 1;					//新结点作为表头结点
			g->val.sublist = CreateGL(s); //递归构造子表并链到表头结点
		} else if (ch == '#')				//遇到'#'字符，表示为空表
			g = NULL;
		else {						//为原子字符
			g->tag = 0;					//新结点作为原子结点
			g->val.data = ch;
		}
	} else								//串结束,g置为空
		g = NULL;
	ch = *s++;                           	//取下一个字符
	if (g != NULL) {                    	//串未结束，继续构造兄递结点
		if (ch == ',')                  	//当前字符为','
			g->link = CreateGL(s);   		//递归构造兄递结点
		else                            //没有兄弟了,将兄弟指针置为NULL
			g->link = NULL;
	}
	return g;                     		//返回广义表g
}

// 辅助函数：输出广义表
void DispGL(GLNode *g) {				//输出广义表g

	if (g != NULL) {               		//表不为空判断
		//先处理g的元素
		if (g->tag == 0)               	//g的元素为原子时
			printf("%c", g->val.data);  //输出原子值
		else {						//g的元素为子表时
			printf("(");                //输出'('
			if (g->val.sublist == NULL)  	//为空表时
				printf("#");
			else						//为非空子表时
				DispGL(g->val.sublist); //递归输出子表
			printf(")");               	//输出')'
		}
		if (g->link != NULL) {
			printf(",");
			DispGL(g->link);            //递归输出后续表的内容
		}
	}
}
//辅助函数：创建a的十字链表
void CreatMat(MatNode *&mh, ElemType a[][N]) {
	int i, j;
	MatNode *h[Max],*p,*q,*r;
	mh = (MatNode *)malloc(sizeof(MatNode)); //创建十字链表的头结点
	mh->row = M;
	mh->col = N;
	r = mh;					//r指向尾结点
	for (i = 0; i < Max; i++) {	//采用尾插法创建头结点h1,h2,…循环链表
		h[i] = (MatNode *)malloc(sizeof(MatNode));
		h[i]->down = h[i]->right = h[i];		//将down和right方向置为循环的
		r->tag.link = h[i];					//将h[i]加到链表中
		r = h[i];
	}
	r->tag.link = mh;							//置为循环链表
	for (i = 0; i < M; i++) {					//处理每一行
		for (j = 0; j < N; j++) {				//处理每一列
			if (a[i][j] != 0) {				//处理非零元素
				p = (MatNode *)malloc(sizeof(MatNode));	//创建一个新结点
				p->row = i;
				p->col = j;
				p->tag.value = a[i][j];
				q = h[i];      					//查找在行表中的插入位置
				while (q->right != h[i] && q->right->col < j)
					q = q->right;
				p->right = q->right;
				q->right = p;	//完成行表的插入
				q = h[j];      					//查找在列表中的插入位置
				while (q->down != h[j] && q->down->row < i)
					q = q->down;
				p->down = q->down;
				q->down = p;  	//完成列表的插入
			}
		}
	}
}
//辅助函数:销毁十字链表
void DestroyMat(MatNode *&mh) {
	MatNode *pre,*p,*mp;
	mp = mh->tag.link;				//mp指向h[i]
	while (mp != mh) {				//释放所有数据结点
		pre = mp->right;				//pre指向h[i]的行首结点
		if (pre != mp) {			//h[i]不空
			p = pre->right;			//p指向结点pre的后继结点
			while (p != mp) {
				free(pre);
				pre = p;
				p = p->right;
			}
		}
		mp = mp->tag.link;			//mp指向下一个头结点
	}
	//释放所有的头结点
	pre = mh->tag.link;				//pre指向h[i]
	p = pre->tag.link;				//p指向h[i+1]
	while (p != mh) {
		free(pre);
		pre = p;
		p = p->tag.link;
	}
	free(mh);
}
//辅助函数：输出十字链表
void DispMat(MatNode *mh) {
	MatNode *p,*q;
	printf("行=%d  列=%d\n", mh->row, mh->col);
	p = mh->tag.link;
	while (p != mh) {
		q = p->right;
		while (p != q) {	//输出一行非零元素
			printf("%d\t%d\t%d\n", q->row, q->col, q->tag.value);
			q = q->right;
		}
		p = p->tag.link;
	}
}


// 测试函数
int main() {
	// 测试1：三元组表求平均数
	printf("1. 三元组表求平均数22:\n");
	TSMatrix M22;
	M22.rows = 3;
	M22.cols = 3;
	M22.nums = 3;
	M22.data[0] = {0, 0, 5};
	M22.data[1] = {1, 1, 8};
	M22.data[2] = {2, 2, 3};
	DispMat(M22);
	double avg22 = MatrixAverage(&M22);
	printf("\n");

	// 测试2：十字链表修改元素
	printf("2. 十字链表修改元素22:\n");
	printf("初始矩阵22:\n");
	ElemType a[M][N] = {{1, 0, 0, 2}, {0, 0, 3, 0}, {0, 0, 0, 4}};
	MatNode* crossMatrix22;
	CreatMat(crossMatrix22, a);
	DispMat(crossMatrix22);

	printf("\n测试修改操作22:\n");

	printf("情况1：插入新元素22\n");
	ModifyCrossList(crossMatrix22, 1, 1, 10);
	DispMat(crossMatrix22);

	printf("情况2：修改现有元素22\n");
	ModifyCrossList(crossMatrix22, 1, 1, 20);
	DispMat(crossMatrix22);

	printf("情况3：删除元素22\n");
	ModifyCrossList(crossMatrix22, 1, 1, 0);
	DispMat(crossMatrix22);

	DestroyMat(crossMatrix22);


	// 测试3：广义表比较
	printf("3.广义表比较22:\n");
	char str1[] = "(a,(b,c),d)";
	char str2[] = "(a,(b,c),d)";
	char str3[] = "(a,(b,x),d)";

	char *s1 = str1;
	char *s2 = str2;
	char *s3 = str3;

	GLNode *g1 = CreateGL(s1);
	GLNode *g2 = CreateGL(s2);
	GLNode *g3 = CreateGL(s3);

	printf("GL1: ");
	DispGL(g1);
	printf(" 22\n");
	printf("GL2: ");
	DispGL(g2);
	printf(" 22\n");
	printf("GL3: ");
	DispGL(g3);
	printf(" 22\n");

	int result122 = EqualGL(g1, g2);
	int result222 = EqualGL(g1, g3);

	if (result122) {
		printf("GL1 == GL2 22\n");
	} else {
		printf("GL1 != GL2 22\n");
	}
	if (result222) {
		printf("GL1 == GL3 22\n");
	} else {
		printf("GL1 != GL3 22\n");
	}


	return 0;
}
