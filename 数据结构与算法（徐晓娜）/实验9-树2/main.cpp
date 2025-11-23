/*
5.编写一个程序，采用一个二叉树表示一个家谱关系（由若干个家谱记录构成，每个家谱记录由丈夫、妻子的姓名组成），每家最多两个孩子，程序具有以下功能。家庭成员中姓名采用第四章的顺序串SqString类型。

(1) 查找某人(参数为父亲姓名或者母亲姓名)的孩子们。

(2) 查找某人的所有祖先，如苏轼的祖先：祖父母苏序和史氏，伯父母苏涣和杨氏，父母苏洵和程氏。

(3) 查找某人同代的所有兄弟姐妹，如跟苏辙同一代的兄弟姐们包括：堂兄弟苏不欺和苏不疑，兄弟苏轼。

(4) 给某人添加孩子。

(5) 某单身人士结婚后添加妻子姓名。





结点数据结构如下：

typedef struct node
{
SqString Husband;
SqString Wife;
struct node *lchild; //指向左孩子节点
struct node *rchild; //指向右孩子节点
} BTNode;



主函数中输入的数据为： 苏序/史氏(苏涣/杨氏(苏不欺/蒲氏,苏不疑),苏洵/程氏(苏轼/王弗,苏辙/史氏))

形参中关于姓名，采用SqString类型


*/
/*陈怡冰24012022*/
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define MaxSize 100

// 顺序串结构
typedef struct {
	char data[MaxSize];
	int length;
} SqString;

// 二叉树节点结构
typedef struct node {
	SqString Husband;
	SqString Wife;
	struct node *lchild;
	struct node *rchild;
} BTNode;

// 顺序串基本运算
void StrAssign(SqString &s, char cstr[]) {
	int i;
	for (i = 0; cstr[i] != '\0'; i++)
		s.data[i] = cstr[i];
	s.length = i;
}

void DestroyStr(SqString &s) {}

void StrCopy(SqString &s, SqString t) {
	int i;
	for (i = 0; i < t.length; i++)
		s.data[i] = t.data[i];
	s.length = t.length;
}

bool StrEqual(SqString s, SqString t) {
	bool same = true;
	int i;
	if (s.length != t.length)
		same = false;
	else
		for (i = 0; i < s.length; i++)
			if (s.data[i] != t.data[i]) {
				same = false;
				break;
			}
	return same;
}

int StrLength(SqString s) {
	return s.length;
}

void DispStr(SqString s) {
	int i;
	if (s.length > 0) {
		for (i = 0; i < s.length; i++)
			printf("%c", s.data[i]);
	}
}

// 自定义辅助函数
BTNode *CreateFamilyNode(char hus[], char wife[]) {
	BTNode *p = (BTNode *)malloc(sizeof(BTNode));
	StrAssign(p->Husband, hus);
	StrAssign(p->Wife, wife);
	p->lchild = NULL;
	p->rchild = NULL;
	return p;
}

// 功能1：查找某人的孩子们
void FindChildren(BTNode *b, SqString name22) {
	if (b == NULL)
		return;

	if (StrEqual(b->Husband, name22) || StrEqual(b->Wife, name22)) {
		printf("查找结果22：查找对象为");
		DispStr(name22);
		printf("，其孩子信息如下：");
		if (b->lchild != NULL) {
			printf("长子/长女：");
			DispStr(b->lchild->Husband);
			printf(" 和 ");
			DispStr(b->lchild->Wife);
			printf(" ");
		}
		if (b->rchild != NULL) {
			printf("次子/次女：");
			DispStr(b->rchild->Husband);
			printf(" 和 ");
			DispStr(b->rchild->Wife);
		}
		if (b->lchild == NULL && b->rchild == NULL)
			printf("无子女");
		printf("\n");
		return;
	}

	FindChildren(b->lchild, name22);
	FindChildren(b->rchild, name22);
}

// 功能2：查找某人的所有祖先
void FindAncestors(BTNode *b, SqString target22, bool &found22) {
	if (b == NULL || found22)
		return;

	if ((b->lchild != NULL && (StrEqual(b->lchild->Husband, target22) || StrEqual(b->lchild->Wife, target22))) ||
	    (b->rchild != NULL && (StrEqual(b->rchild->Husband, target22) || StrEqual(b->rchild->Wife, target22)))) {
		printf("祖先22：查找对象为");
		DispStr(target22);
		printf("，直系祖先：");
		DispStr(b->Husband);
		printf(" 和 ");
		DispStr(b->Wife);
		printf("\n");
		found22 = true;
		return;
	}

	FindAncestors(b->lchild, target22, found22);
	FindAncestors(b->rchild, target22, found22);

	if (found22 && !(StrEqual(b->Husband, target22) || StrEqual(b->Wife, target22))) {
		printf("祖先22：查找对象为");
		DispStr(target22);
		printf("，更高层祖先：");
		DispStr(b->Husband);
		printf(" 和 ");
		DispStr(b->Wife);
		printf("\n");
	}
}

// 功能3：查找某人同代的所有兄弟姐妹
void FindSiblings(BTNode *b, SqString target22, BTNode *parent22) {
	if (b == NULL)
		return;

	if (StrEqual(b->Husband, target22) || StrEqual(b->Wife, target22)) {
		printf("同代兄弟姐妹22：查找对象为");
		DispStr(target22);
		printf("，其兄弟姐妹信息如下：");
		if (parent22 != NULL) {
			bool hasSibling = false;
			if (parent22->lchild != NULL && !StrEqual(parent22->lchild->Husband, target22) && !StrEqual(parent22->lchild->Wife, target22)) {
				DispStr(parent22->lchild->Husband);
				hasSibling = true;
			}
			if (parent22->rchild != NULL && !StrEqual(parent22->rchild->Husband, target22) && !StrEqual(parent22->rchild->Wife, target22)) {
				if (hasSibling) printf("、");
				DispStr(parent22->rchild->Husband);
				hasSibling = true;
			}
			if (!hasSibling)
				printf("无同代兄弟姐妹");
		} else
			printf("无父节点，无法查询兄弟姐妹");
		printf("\n");
		return;
	}

	FindSiblings(b->lchild, target22, b);
	FindSiblings(b->rchild, target22, b);
}

// 功能4：给某人添加孩子
bool AddChild(BTNode *b, SqString parent22, char childHus22[], char childWife22[]) {
	if (b == NULL)
		return false;

	if (StrEqual(b->Husband, parent22) || StrEqual(b->Wife, parent22)) {
		BTNode *child22 = CreateFamilyNode(childHus22, childWife22);
		if (b->lchild == NULL) {
			b->lchild = child22;
			printf("添加孩子成功22：父母为");
			DispStr(parent22);
			printf("，新增孩子：");
			printf("%s 和 %s\n", childHus22, childWife22);
		} else if (b->rchild == NULL) {
			b->rchild = child22;
			printf("添加孩子成功22：父母为");
			DispStr(parent22);
			printf("，新增孩子：");
			printf("%s 和 %s\n", childHus22, childWife22);
		} else {
			printf("添加失败22：父母为");
			DispStr(parent22);
			printf("，该家庭已达最多2个孩子，无法新增\n");
			return false;
		}
		return true;
	}

	return AddChild(b->lchild, parent22, childHus22, childWife22) ||
	       AddChild(b->rchild, parent22, childHus22, childWife22);
}

// 功能5：单身人士结婚添加妻子
bool AddSpouse(BTNode *b, SqString single22, char spouse22[]) {
	if (b == NULL)
		return false;

	if (StrEqual(b->Husband, single22) && b->Wife.length == 0) {
		StrAssign(b->Wife, spouse22);
		printf("添加妻子成功22：单身人士为");
		DispStr(single22);
		printf("，新增妻子：%s\n", spouse22);
		return true;
	} else if (StrEqual(b->Husband, single22) && b->Wife.length > 0) {
		printf("添加失败22：人士为");
		DispStr(single22);
		printf("，已有配偶，无需重复添加\n");
		return false;
	}

	return AddSpouse(b->lchild, single22, spouse22) ||
	       AddSpouse(b->rchild, single22, spouse22);
}

// 构建示例家谱
BTNode *BuildFamilyTree() {
	BTNode *root = CreateFamilyNode("苏序", "史氏");
	root->lchild = CreateFamilyNode("苏涣", "杨氏");
	root->rchild = CreateFamilyNode("苏洵", "程氏");
	root->lchild->lchild = CreateFamilyNode("苏不欺", "蒲氏");
	root->lchild->rchild = CreateFamilyNode("苏不疑", "");
	root->rchild->lchild = CreateFamilyNode("苏轼", "王弗");
	root->rchild->rchild = CreateFamilyNode("苏辙", "史氏");
	return root;
}

// 主函数测试
int main() {
	BTNode *familyTree = BuildFamilyTree();
	SqString name22, target22, single22;
	bool found22;

	// 测试功能1：查找苏洵的孩子
	StrAssign(name22, "苏洵");
	printf("=== 功能1测试22：查找苏洵的孩子 ===\n");
	FindChildren(familyTree, name22);

	// 测试功能2：查找苏轼的祖先
	StrAssign(target22, "苏轼");
	found22 = false;
	printf("\n=== 功能2测试22：查找苏轼的所有祖先 ===\n");
	FindAncestors(familyTree, target22, found22);

	// 测试功能3：查找苏辙的兄弟姐妹
	StrAssign(target22, "苏辙");
	printf("\n=== 功能3测试22：查找苏辙的同代兄弟姐妹 ===\n");
	FindSiblings(familyTree, target22, NULL);

	// 测试功能4：给苏不疑添加孩子
	StrAssign(name22, "苏不疑");
	printf("\n=== 功能4测试22：给苏不疑添加孩子 ===\n");
	AddChild(familyTree, name22, "苏某", "某氏");

	// 测试功能5：给苏不疑添加妻子
	StrAssign(single22, "苏不疑");
	printf("\n=== 功能5测试22：给苏不疑添加妻子 ===\n");
	AddSpouse(familyTree, single22, "林氏");

	// 释放内存
	free(familyTree->lchild->lchild);
	free(familyTree->lchild->rchild);
	free(familyTree->rchild->lchild);
	free(familyTree->rchild->rchild);
	free(familyTree->lchild);
	free(familyTree->rchild);
	free(familyTree);

	return 0;
}
