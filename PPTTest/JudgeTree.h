#pragma once
#include "stdafx.h"
#include <vector>
#include <hash_map>
using namespace std;

struct TreeNode{
	int index;//表示选择下一层节点时应当判定的属性的index
	bool finished;//表示到该层已经细分完成，没有下一层节点了
	TreeNode *firstChild, *nextBrother;
	vector<DNode *> datas;//表示目前从属于这一节点的所有数据的地址的集合

	hash_map<int, float> gain;//int属性的index，float用于存储计算的gain值
};

class JudgeTree :public Algrithom{
private:
	TreeNode *root;

	float ageCount[3][3];//用来表示年龄的数量
	/*
					y    n	All
		<=30
		30..40
		>40
					*/
	float incomeCount[3][3];
	float stuCount[2][3];
	float creditCount[2][3];

	float totalCount;
	static const int propCount[4] ;
	const int BUY_COUNT = 2;
	float  **props[4];

	void resetTree(TreeNode *root);
	void createTree(TreeNode *root);
public:
	JudgeTree();
	void reset();
	void learn(DNode *data, int count);
	bool getClass(DNode *record);
	~JudgeTree();
};