#ifndef SQLIST_H
#define SQLIST_H
#define MaxSize 10
typedef int ElemType;
typedef struct {
	ElemType data[MaxSize];
	int length;
} SqList;
void CreateList(SqList *&L, ElemType a[], int n);
void InitList(SqList *&L);
void DestroyList(SqList *&L);
int ListLength(SqList *L);

#endif
