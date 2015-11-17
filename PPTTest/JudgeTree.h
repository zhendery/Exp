#pragma once
#include "stdafx.h"
#include <vector>
#include <hash_map>
using namespace std;

struct TreeNode{
	int index;//��ʾѡ����һ��ڵ�ʱӦ���ж������Ե�index
	bool finished;//��ʾ���ò��Ѿ�ϸ����ɣ�û����һ��ڵ���
	TreeNode *firstChild, *nextBrother;
	vector<DNode *> datas;//��ʾĿǰ��������һ�ڵ���������ݵĵ�ַ�ļ���

	hash_map<int, float> gain;//int���Ե�index��float���ڴ洢�����gainֵ
};

class JudgeTree :public Algrithom{
private:
	TreeNode *root;

	float ageCount[3][3];//������ʾ���������
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