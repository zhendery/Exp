// Exp.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<windows.h>
#include "Bayes.h"
#include "JudgeTree.h"

using namespace std;

const int DATA_COUNT = 5665;
const int recordLen = 10;

const char* bass(char *c){
	for (int i = 0; i < BASS_COUNT; ++i){
		if (!strcmp(c, BASS[i]))
			return BASS[i];
	}
	return NULL;
}
const char* chord(char *c){
	for (int i = 0; i < CHORD_COUNT; ++i){
		if (!strcmp(c, CHORD[i]))
			return CHORD[i];
	}
	return NULL;
}

DNode data[DATA_COUNT];

void readData(){
	ifstream file;
	file.open("../Data/jsbach_chorals_harmony.data");

	for (int i = 0; i < DATA_COUNT; ++i){
		char record[recordLen];
		file.get(record, recordLen, ',');//Choral ID
		file.read(record, 1);
		file.get(record, recordLen, ',');//Event number
		file.read(record, 1);
		//以上两个属性无用，直接跳过

		for (int x = 0; x < PITCH_COUNT; ++x){
			file.get(record, recordLen, ',');//Pitch class
			data[i].pitch[x] = strcmp(record, " NO");
			file.read(record, 1);
		}
		file.get(record, recordLen, ',');//Bass
		data[i].bass = bass(record);
		file.read(record, 1);
		file.get(record, recordLen, ',');//Meter
		data[i].meter = (short) atoi(record) - 1;
		file.read(record, 1);
		file.get(record, recordLen, '\n');//Chord label
		data[i].chord = chord(record);
		file.read(record, 1);
	}
	file.close();
}

void printData(int count){
	for (int i = 0; i < count; ++i){
		for (int x = 0; x < PITCH_COUNT; ++x)
			cout << data[i].pitch[x] << ",";
		cout << data[i].bass << "," << data[i].meter << "," << data[i].chord << endl;
	}
}

void test(Algrithom *al){
	cout << "采用" << al->name() << "算法的测试：" << endl;
	int times = 5;
	float accuracy = 0, tpr = 0;
	for (int n = 0; n < times; ++n){
		al->reset();
		int from = (int) (DATA_COUNT*n / times), end = (int) (DATA_COUNT*(n + 1) / times);//测试集
		al->learn(data, 0, from);
		al->learn(data, end, DATA_COUNT);//学习其余
		al->calculate();//计算概率

		int tp = 0, tn = 0, fp = 0, fn = 0;
		for (int i = from; i < end; ++i){
			const char *result = al->getClass(&data[i]);
			if (result == data[i].chord)//预测正确
				result==CHORD[0] ? tp++ : tn++;//选取D_M作为正例
			else//预测错误
				result == CHORD[0] ? fp++ : fn++;
		}

		float accuThisTurn = (tp + tn)*1.0f / (end - from);
		float tprThisTurn = tp*1.0f / (tp + fn);
		cout << "第" << n + 1 << "轮测试，结果：准确率=" << accuThisTurn << "    TPR=" << tprThisTurn << endl;
		accuracy = (accuracy*n + accuThisTurn) / (n + 1);
		tpr = (accuracy*n + tprThisTurn) / (n + 1);
	}
	cout << "完成测试，结果：准确率=" << accuracy << "    TPR=" << tpr << endl << endl;
}

int _tmain(int argc, _TCHAR* argv [])
{
	readData();

	//Bayes bayes;
	//test(&bayes);

	JudgeTree judgeTree;
	test(&judgeTree);

	system("PAUSE");
	return 0;
}
