// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <string>

struct DNode{
	short age,income,credit;
	bool student,buy;
};

class Algrithom{
public:
	virtual void reset(){}
	virtual void learn(DNode *data, int count){}
	virtual bool getClass(DNode *record){ return NULL; }
};

// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
