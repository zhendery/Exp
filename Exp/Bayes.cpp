#include "stdafx.h"
#include "Bayes.h"
const char* Bayes::name()
{
	return "朴素贝叶斯";
}
void Bayes::reset(){
	int i;
	for (int j = 0; j < CHORD_COUNT; ++j){
		for (i = 0; i < PITCH_COUNT << 1; ++i)
			pitchCount[i][j] = 0;

		for (i = 0; i < BASS_COUNT; ++i)
			bassCount[i][j] = 0;

		for (i = 0; i < 5; ++i)
			meterCount[i][j] = 0;
	}
	for (i = 0; i < CHORD_COUNT; ++i)
		chordCount[i] = 0;

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

void Bayes::learn(DNode *data, int from, int end){
	int count = end - from;
	for (int i = from; i < end; ++i){//读取每一条记录，根据每一个属性与chord，将对应的属性计数加一
		int ch = chord(data[i].chord);
		for (int x = 0; x < PITCH_COUNT; ++x){
			if (data[i].pitch[x])
				pitchCount[x << 1][ch]++;
			else
				pitchCount[(x << 1) + 1][ch]++;
		}
		bassCount[bass(data[i].bass)][ch]++;
		meterCount[data[i].meter][ch]++;
		chordCount[ch]++;
	}
	totalCount += count;
}

void Bayes::calculate(){
	//计算属性概率
	for (int i = 0; i < CHORD_COUNT; ++i){
		if (chordCount[i] == 0)
			continue;
		int x;
		for (x = 0; x < PITCH_COUNT; ++x){
			pitchCount[x << 1][i] /= chordCount[i];
			pitchCount[(x << 1) + 1][i] /= chordCount[i];
		}
		for (x = 0; x < BASS_COUNT; ++x)
			bassCount[x][i] /= chordCount[i];
		for (x = 0; x < 5; ++x)
			meterCount[x][i] /= chordCount[i];
		chordCount[i] /= totalCount;
	}
}

const char* Bayes::getClass(DNode *record){//参数是一条记录
	float probability[CHORD_COUNT], max = 0;
	int maxID = 0;

	for (int i = 0; i < CHORD_COUNT; ++i){
		probability[i] = 1;//首先置为1，以便计算乘积
		for (int x = 0; x < PITCH_COUNT; ++x){
			if (record->pitch[x])
				probability[i] *= pitchCount[x << 1][i];
			else
				probability[i] *= pitchCount[(x << 1) + 1][i];
		}
		probability[i] *= bassCount[bass(record->bass)][i];
		probability[i] *= meterCount[record->meter][i];
		probability[i] *= chordCount[i];
	}
	for (int i = 0; i < CHORD_COUNT; ++i){
		if (probability[i]>max){
			max = probability[i];
			maxID = i;
		}
	}
	return CHORD[maxID];
}