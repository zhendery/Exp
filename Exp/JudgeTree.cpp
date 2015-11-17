#include "stdafx.h"
#include "JudgeTree.h"
const char* JudgeTree::name()
{
	return "决策树";
}
void JudgeTree::reset(){
	int i;
	unCalPros.clear();
	for (i = 0; i < 15; ++i)
		unCalPros[i] = 0;
	caledPros.clear();

	for (int j = 0; j <=CHORD_COUNT; ++j){
		for (i = 0; i < PITCH_COUNT << 1; ++i)
			pitchCount[i][j] = 0;

		for (i = 0; i < BASS_COUNT; ++i)
			bassCount[i][j] = 0;

		for (i = 0; i < 5; ++i)
			meterCount[i][j] = 0;
	}

	totalCount = 0;
}
int bass(const char *c){
	for (int i = 0; i < BASS_COUNT; ++i){
		if (c == BASS[i])
			return i;
	}
	return -1;
}
int chord(const char *c){
	for (int i = 0; i < CHORD_COUNT; ++i){
		if (c == CHORD[i])
			return i;
	}
	return -1;
}

JudgeTree::JudgeTree(){
	root = new TreeNode();
	root->firstChild=root->nextBrother = NULL;
	root->index = -1;
}
void JudgeTree::learn(vector<DNode*> *datas)
{
	for each (DNode* data in *datas)
	{
		int ch = chord(data->chord);
		for (int x = 0; x < PITCH_COUNT; ++x){
			if (data->pitch[x]){
				pitchCount[x << 1][ch]++;
				pitchCount[x << 1][CHORD_COUNT]++;//..1
			}
			else{
				pitchCount[(x << 1) + 1][ch]++;
				pitchCount[(x << 1) + 1][CHORD_COUNT]++;//..2
			}
		}
		bassCount[bass(data->bass)][ch]++;
		bassCount[bass(data->bass)][CHORD_COUNT]++;//..3
		meterCount[data->meter][ch]++;
		meterCount[data->meter][CHORD_COUNT]++;//..4
		// .. 1,2,3,4分别是为该属性的某个值不论类计数加一
		totalCount++;
	}
}
void JudgeTree::learn(DNode *data, int from, int end){
	for (int i = from; i < end; ++i)//将要学习的数据地址压入root的vector
		root->datas.push_back(&data[i]);
}

void JudgeTree::calculate(){
	//计算属性gain值

}

const char* JudgeTree::getClass(DNode *record){//参数是一条记录
	float probability[CHORD_COUNT], max = 0;
	int maxID = 0;

	//for (int i = 0; i < CHORD_COUNT; ++i){
	//	probability[i] = 1;//首先置为1，以便计算乘积
	//	for (int x = 0; x < PITCH_COUNT; ++x){
	//		if (record->pitch[x])
	//			probability[i] *= pitchCount[x << 1][i];
	//		else
	//			probability[i] *= pitchCount[(x << 1) + 1][i];
	//	}
	//	probability[i] *= bassCount[bass(record->bass)][i];
	//	probability[i] *= meterCount[record->meter][i];
	//	probability[i] *= chordCount[i];
	//}
	//for (int i = 0; i < CHORD_COUNT; ++i){
	//	if (probability[i]>max){
	//		max = probability[i];
	//		maxID = i;
	//	}
	//}
	//return CHORD[maxID];
}
JudgeTree::~JudgeTree(){

}