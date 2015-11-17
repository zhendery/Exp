#pragma once
#include "stdafx.h"


class Bayes{// :public Algrithom{
private:
	float ageCount[3][2];//用来表示年龄的数量
	/*
								y    n
	<=30
	30..40
	>40
	*/
	float incomeCount[3][2];
	float stuCount[2][2];
	float creditCount[2][2];

	float buyCount[2];

public:
	void reset();
	void learn(DNode *data, int count);
	bool getClass(DNode *record);
};