// Exp.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<windows.h>
#include "JudgeTree.h"

using namespace std;

#define DATA_COUNT 14
const int recordLen = 10;

DNode data[DATA_COUNT];

void readData(){
	ifstream file;
	file.open("../Data/ppttest.data");

	for (int i = 0; i < DATA_COUNT; ++i){
		char record[recordLen];
		file.get(record, recordLen, ',');//age
		data[i].age = atoi(record);
		file.read(record, 1);

		file.get(record, recordLen, ',');//income
		data[i].income = atoi(record);
		file.read(record, 1);

		file.get(record, recordLen, ',');//student
		data[i].student = !strcmp(record, "y");
		file.read(record, 1);

		file.get(record, recordLen, ',');//credit
		data[i].credit = atoi(record);
		file.read(record, 1);

		file.get(record, recordLen, '\n');//buy
		data[i].buy = !strcmp(record, "y");
		file.read(record, 1);
	}
	file.close();
}

void printData(int count){
	for (int i = 0; i < count; ++i){
		cout << data[i].age << "," << data[i].income << "," << data[i].student << ","
			<< data[i].credit << "," << data[i].buy << endl;
	}
}

void test(JudgeTree *al, float &accuracy, float &tpr){
	int start = (int) (DATA_COUNT *0.9) + 1, testCount = DATA_COUNT - start;
	int tp = 0, tn = 0, fp = 0, fn = 0;
	for (int i = start; i < DATA_COUNT; ++i){
		bool result = al->getClass(&data[i]);
		if (result )//假设正例为buy
			data[i].buy ? tp++ : fp++;
		else
			data[i].buy ? fn++ : tn++;
	}
	accuracy = (tp + tn)*1.0f / testCount;
	tpr = tp*1.0f / (tp + fn);
}


int _tmain(int argc, _TCHAR* argv [])
{
	readData();
	JudgeTree bayes;

	bayes.learn(data,DATA_COUNT);
	//float accu, tpr;

	//DNode node={0,1,0,true};
//	bayes.getClass(&node);
	system("PAUSE");
	return 0;
}
