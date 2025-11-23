//层次遍历算法
#include "btree.cpp"
#define MaxSize 100
//--------------------------------------------------------
//--循环队列基本运算算法----------------------------------
//--------------------------------------------------------
typedef struct 
{	BTNode *data[MaxSize];				//存放队中元素
	int front,rear;						//队头和队尾指针
} SqQueue;								//顺序队类型
void InitQueue(SqQueue *&q)				//初始化队列
{	q=(SqQueue *)malloc (sizeof(SqQueue));
	q->front=q->rear=0;
}
void DestroyQueue(SqQueue *&q)			//销毁队列
{
	free(q);
}
bool QueueEmpty(SqQueue *q)				//判断队列是否为空
{
	return(q->front==q->rear);
}
bool enQueue(SqQueue *&q,BTNode *e)		//进队列
{	if ((q->rear+1)%MaxSize==q->front)	//队满上溢出
		return false;
	q->rear=(q->rear+1)%MaxSize;
	q->data[q->rear]=e;
	return true;
}
int Count(SqQueue *&q)					//求队列中的元素个数 
{
	return (q->rear-q->front+MaxSize)%MaxSize;
}
bool deQueue(SqQueue *&q,BTNode *&e)	//出队列
{	if (q->front==q->rear)				//队空下溢出
		return false;
	q->front=(q->front+1)%MaxSize;
	e=q->data[q->front];
	return true;
}
//--------------------------------------------------------

//基本层次遍历算法
void LevelOrder(BTNode *b)			//基本层次遍历算法 
{
	BTNode *p;
	SqQueue *qu;
	InitQueue(qu);					//初始化队列
	enQueue(qu,b);					//根结点指针进入队列
	while (!QueueEmpty(qu))			//队不为空循环
	{
		deQueue(qu,p);				//出队结点p
		printf("%c ",p->data);		//访问结点p
		if (p->lchild!=NULL)		//有左孩子时将其进队
			enQueue(qu,p->lchild);
		if (p->rchild!=NULL)		//有右孩子时将其进队
			enQueue(qu,p->rchild);
	} 
}

//分层次的层次遍历算法
void LevelOrder1(BTNode *b)			//分层次的层次遍历算法 
{
	BTNode *p;
	SqQueue *qu;
	InitQueue(qu);					//初始化队列
	int curl=1;						//表示当前层次(初始化为1) 
	enQueue(qu,b);					//根结点指针进入队列
	while (!QueueEmpty(qu))			//队不为空循环
	{
		printf("第%d层: ",curl); 
		int cnt=Count(qu);		//求当前层次的结点个数
		for(int i=0;i<cnt;i++)		//循环cnt次访问当前层的全部结点 
		{ 
			deQueue(qu,p);				//出队结点p
			printf("%c ",p->data);		//访问结点p
			if (p->lchild!=NULL)		//有左孩子时将其进队
				enQueue(qu,p->lchild);
			if (p->rchild!=NULL)		//有右孩子时将其进队
				enQueue(qu,p->rchild);
		}
		curl++;
		printf("\n"); 
	} 
}

int main()
{
	BTNode *b;
	CreateBTree(b,"A(B(D(,G)),C(E,F))");
	printf("b:");DispBTree(b);printf("\n");
	printf("基本层次遍历序列:");LevelOrder(b);printf("\n");
	printf("分层次的层次遍历:\n");LevelOrder1(b);printf("\n");
	DestroyBTree(b);
	return 1;
}
