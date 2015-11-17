#pragma once
#include "stdafx.h"


class Bayes :public Algrithom{
private:
	float pitchCount[PITCH_COUNT<<1][CHORD_COUNT];//用来表示12个pitch的数量
	/*
							c1  c2  c3  ....
	pitch1:true
	pitch1:false
	pitch2:true
	pitch2:false
	...
	*/
	float bassCount[BASS_COUNT][CHORD_COUNT];
	float meterCount[5][CHORD_COUNT];

	float chordCount[CHORD_COUNT];
	int totalCount;

public:
	const char* name();
	void reset();
	void learn(DNode *data, int from, int end);//含from，不含end   用来学习所有记录
	void calculate();//学习完所有记录后进行概率计算
	const char* getClass(DNode *record);
};