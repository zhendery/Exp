#pragma once
#include "stdafx.h"
using namespace std;

struct TreeNode{
	int index;//表示选择下一层节点时应当判定的属性的index

	TreeNode *firstChild, *nextBrother;
	vector<DNode *> datas;//表示目前从属于这一节点的所有数据的地址的集合
};

class JudgeTree :public Algrithom{
private:
	hash_map<int, float> unCalPros;//表示没有计算gain的属性的index，float用于存储计算的gain值
	vector<int> caledPros;//表示已经计算gian的属性的index，全部计算完后此vector的顺序就是决策树生成的顺序

	TreeNode *root;

	float pitchCount[PITCH_COUNT<<1][CHORD_COUNT+1];//用来表示12个pitch的数量
	/*
							c1  c2  c3  ....  All
	pitch1:true
	pitch1:false
	pitch2:true
	pitch2:false
	...
	*/
	float bassCount[BASS_COUNT][CHORD_COUNT+1];
	float meterCount[5][CHORD_COUNT+1];

	int totalCount;


	void learn(vector<DNode*> *datas);
public:
	JudgeTree();
	const char* name();
	void reset();
	void learn(DNode *data, int from, int end);//含from，不含end   用来学习所有记录
	void calculate();//学习完所有记录后进行gain的计算
	const char* getClass(DNode *record);
	~JudgeTree();
};