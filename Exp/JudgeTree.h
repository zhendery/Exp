#pragma once
#include "stdafx.h"
using namespace std;

struct TreeNode{
	int index;//��ʾѡ����һ��ڵ�ʱӦ���ж������Ե�index

	TreeNode *firstChild, *nextBrother;
	vector<DNode *> datas;//��ʾĿǰ��������һ�ڵ���������ݵĵ�ַ�ļ���
};

class JudgeTree :public Algrithom{
private:
	hash_map<int, float> unCalPros;//��ʾû�м���gain�����Ե�index��float���ڴ洢�����gainֵ
	vector<int> caledPros;//��ʾ�Ѿ�����gian�����Ե�index��ȫ����������vector��˳����Ǿ��������ɵ�˳��

	TreeNode *root;

	float pitchCount[PITCH_COUNT<<1][CHORD_COUNT+1];//������ʾ12��pitch������
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
	void learn(DNode *data, int from, int end);//��from������end   ����ѧϰ���м�¼
	void calculate();//ѧϰ�����м�¼�����gain�ļ���
	const char* getClass(DNode *record);
	~JudgeTree();
};