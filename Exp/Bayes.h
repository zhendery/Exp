#pragma once
#include "stdafx.h"


class Bayes :public Algrithom{
private:
	float pitchCount[PITCH_COUNT<<1][CHORD_COUNT];//������ʾ12��pitch������
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
	void learn(DNode *data, int from, int end);//��from������end   ����ѧϰ���м�¼
	void calculate();//ѧϰ�����м�¼����и��ʼ���
	const char* getClass(DNode *record);
};