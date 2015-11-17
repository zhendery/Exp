#include "stdafx.h"
#include "JudgeTree.h"

const int JudgeTree::propCount[4] = { 3, 3, 2, 2 };

JudgeTree::JudgeTree(){
	props[0] = (float **) ageCount;
	props[1] = (float **) incomeCount;
	props[2] = (float **) stuCount;
	props[3] = (float **) creditCount;
}

void JudgeTree::reset(){
	for (int x = 0; x < 4; ++x){
		for (int i = 0; i < propCount[x]; ++i){
			for (int j = 0; j < BUY_COUNT + 1; ++j){
				*((float *) (props[x] + i*(BUY_COUNT + 1)) + j) = 0;
			}
		}
	}
	totalCount = 0;
}

void JudgeTree::resetTree(TreeNode *root){
	if (!root)
		return;
	resetTree(root->firstChild);
	resetTree(root->nextBrother);
	delete root;
}

void JudgeTree::learn(DNode *data, int count)
{
	resetTree(root);
	root = new TreeNode();
	root->gain[0] = root->gain[1] = root->gain[2] = root->gain[3] = 0;
	root->finished = false;
	root->firstChild = root->nextBrother = NULL;
	root->index = -1;

	for (int i = 0; i < count; ++i)//将要学习的数据地址压入root的vector
		root->datas.push_back(data + i);

	createTree(root);
}

float calI(float x, float y){
	if (x == y || x == 0)
		return 0;
	return -x / y*log2f(x / y);
}
void JudgeTree::createTree(TreeNode *root){
	reset();
	for each (DNode *data in root->datas)//先统计数据个数，然后根据公式计算
	{
		if (data->buy){
			ageCount[data->age][0]++;
			incomeCount[data->income][0]++;
			stuCount[data->student ? 0 : 1][0]++;
			creditCount[data->credit][0]++;
		}
		else{
			ageCount[data->age][1]++;
			incomeCount[data->income][1]++;
			stuCount[data->student ? 0 : 1][1]++;
			creditCount[data->credit][1]++;
		}
		ageCount[data->age][2]++;
		incomeCount[data->income][2]++;
		stuCount[data->student ? 0 : 1][2]++;
		creditCount[data->credit][2]++;
		totalCount++;
	}

	int i = 0;
	//计算属性的"增益"，并选择一个最小的



	root->gain[0] = (ageCount[0][2] / totalCount* (calI(ageCount[0][0], ageCount[0][2]) + calI(ageCount[0][1], ageCount[0][2])) +
		ageCount[1][2] / totalCount*(calI(ageCount[1][0], ageCount[1][2]) + calI(ageCount[1][1], ageCount[1][2])) +
		ageCount[2][2] / totalCount*(calI(ageCount[2][0], ageCount[2][2]) + calI(ageCount[2][1], ageCount[2][2])));
	root->gain[1] = (incomeCount[0][2] / totalCount* (calI(incomeCount[0][0], incomeCount[0][2]) + calI(incomeCount[0][1], incomeCount[0][2])) +
		incomeCount[1][2] / totalCount*(calI(incomeCount[1][0], incomeCount[1][2]) + calI(incomeCount[1][1], incomeCount[1][2])) +
		incomeCount[2][2] / totalCount*(calI(incomeCount[2][0], incomeCount[2][2]) + calI(incomeCount[2][1], incomeCount[2][2])));
	root->gain[2] = (stuCount[0][2] / totalCount*(calI(stuCount[0][0], stuCount[0][2]) + calI(stuCount[0][1], stuCount[0][2])) +
		stuCount[1][2] / totalCount*(calI(stuCount[1][0], stuCount[1][2]) + calI(stuCount[1][1], stuCount[1][2])));
	root->gain[3] = (creditCount[0][2] / totalCount*(calI(creditCount[0][0], creditCount[0][2]) + calI(creditCount[0][1], creditCount[0][2])) +
		creditCount[1][2] / totalCount*(calI(creditCount[1][0], creditCount[1][2]) + calI(creditCount[1][1], creditCount[1][2])));

	float min = 99; int minID = -1;
	for (i = 0; i < 4; ++i){
		if (root->gain[i] < min){
			min = root->gain[i];
			minID = i;
		}
	}
	root->index = minID;
	TreeNode **children = new TreeNode*[propCount[minID]];
	children[0] = root->firstChild = new TreeNode();
	children[0]->firstChild = NULL;
	for (i = 1; i < propCount[minID]; ++i){
		children[i] = children[i - 1]->nextBrother = new TreeNode();
		children[i]->nextBrother = children[i]->firstChild = NULL;
	}
	hash_map <int, float> ::iterator gain_it = root->gain.begin();
	for (i = 0; i < minID; ++i)
		gain_it++;
	root->gain.erase(gain_it);//下一层不需要计算这个属性了
	for (i = 0; i < propCount[minID]; ++i){
		for (gain_it = root->gain.begin(); gain_it != root->gain.end(); gain_it++)
			children[i]->gain[gain_it->first] = 0;
		if (*((float *) (props[minID] + i*(BUY_COUNT + 1))) == 0 || *((float *) (props[minID] + i*(BUY_COUNT + 1)) + 1) == 0)
			children[i]->finished = true;
		else
			children[i]->finished = false;
	}
	vector<DNode*>::iterator data_it;
	for (data_it = root->datas.begin(); data_it != root->datas.end();)
	{
		int value = 0;
		DNode *data = *data_it;
		//将属性index换算为属性,value表示属性值
		switch (minID)
		{
		case 0://age
			value = data->age;
			break;
		case 1://income
			value = data->income;
			break;
		case 2:
			value = data->student ? 0 : 1;
			break;
		case 3:
			value = data->credit;
			break;
		}
		if (!children[value]->finished)
			children[value]->datas.push_back(data);//将要继续计算的记录插入到下一层
		data_it = root->datas.erase(data_it);//从原节点中移除
	}
	delete children;
}

bool JudgeTree::getClass(DNode *record){//参数是一条记录
	return true;
}

JudgeTree::~JudgeTree(){
	reset();

}