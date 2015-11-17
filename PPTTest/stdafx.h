// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
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

// TODO:  在此处引用程序需要的其他头文件
