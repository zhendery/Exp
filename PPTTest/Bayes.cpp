#include "stdafx.h"
#include "Bayes.h"

void Bayes::reset(){
	int i, j;
	for (i = 0; i < 3; ++i)
		for (j = 0; j < 2; ++j)
			ageCount[i][j] = 0;

	for (i = 0; i < 3; ++i)
		for (j = 0; j < 2; ++j)
			incomeCount[i][j] = 0;

	for (i = 0; i < 2; ++i)
		for (j = 0; j < 2; ++j)
			stuCount[i][j] = 0;

	for (i = 0; i < 2; ++i)
		for (j = 0; j < 2; ++j)
			creditCount[i][j] = 0;

	for (i = 0; i < 2; ++i)
		buyCount[i] = 0;
}

void Bayes::learn(DNode *data, int count){
	reset();
	for (int i = 0; i < count; ++i){//读取每一条记录，根据每一个属性与chord，将对应的属性计数加一
		int ch = data[i].buy ? 0 : 1;
		ageCount[data[i].age][ch]++;
		incomeCount[data[i].income][ch]++;
		stuCount[data[i].student ? 0 : 1][ch]++;
		creditCount[data[i].credit][ch]++;
		buyCount[ch]++;
	}

	//计算属性概率
	for (int i = 0; i < 2; ++i){
		if (buyCount[i] == 0)
			continue;
		int j;
		for (j = 0; j < 3; ++j)
			ageCount[j][i] /= buyCount[i];
		for (j = 0; j < 3; ++j)
			incomeCount[j][i] /= buyCount[i];
		for (j = 0; j < 2; ++j)
			stuCount[j][i] /= buyCount[i];
		for (j = 0; j < 2; ++j)
			creditCount[j][i] /= buyCount[i];
		buyCount[i] /= count;
	}
}

bool Bayes::getClass(DNode *record){//参数是一条记录
	float probability[2];

	for (int i = 0; i < 2; ++i){
		probability[i] = 1;//首先置为1，以便计算乘积
		probability[i] *= ageCount[record->age][i];
		probability[i] *= incomeCount[record->income][i];
		probability[i] *= stuCount[record->student ? 0 : 1][i];
		probability[i] *= creditCount[record->credit][i];
		probability[i] *= buyCount[i];
		std::cout << "pro " << i << "=" << probability[i] << "    ";
	}
	return probability[0]>probability[1];
}