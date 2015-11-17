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
#include <vector>
#include <hash_map>

const int BASS_COUNT = 16, CHORD_COUNT = 102, PITCH_COUNT = 12;

static char *BASS[BASS_COUNT] = { "C", "D", "E", "F", "G", "A", "B", "C#", "D#", "F#", "G#", "A#", "Db", "Eb", "Ab", "Bb" };

static char *CHORD[CHORD_COUNT] = { " D_M", " G_M", " C_M", " F_M", " A_M", " BbM", " E_M", " A_m", " E_m", " B_m",
" D_m", " C_M7", " D_m7"," C_M4", " G_m"," G_M7",  " F#d", " AbM", " C#d7", " D_M7", " EbM", " F_M7", " C_m", 
" A_M4", " F#m", " B_M"," D#d", " C#M", " F#m7", " A#d", " E_M7",  " F#M", " F#M7", " B_M7", " A_m6", " C#d",
" A_m7", " A_d", " C_m7", " G_m6", " D_M4", " G_m7", " E_m7", " E_m6", " A_M7", " C#m", " C#M7", " A#d7",
" EbM7", " B_m7", " E_M4", " C#m7", " F_M4", " D_m6", " G#d", " G#d7", " A_m4", " D_M6", " F_d", " B_m6",
" B_M4", " C_m6", " F_m", " G_M4", " F_m7", " C_d6", " F_m6", " G_M6", " A_M6", " F_M6", " F#M4", " B_d7",
" D_d7", " E_d", " Bbm", " Bbm6", " DbM", " C_d7", " F#d7", " Abd", " Ebd", " Dbd7", " Dbd", " Bbd", " Dbm7",
" Abm", " DbM7", " Dbm", " F#m6", " G#m", " B_d", " C_M6", " D#m", " D#M", " BbM7", " F_d7", " C#d6", " G_d",
" G#M", " C#M4", " D#d6", " D#d7" };

struct DNode{
	bool pitch[12];
	const char *bass;
	short meter;
	const char *chord;
};

class Algrithom{
public:
	virtual const char* name(){ return NULL; }
	virtual void reset(){}
	virtual void learn(DNode *data, int from, int end){}//含from，不含end   用来学习所有记录
	virtual void calculate(){}//学习完所有记录后进行概率计算
	virtual const char* getClass(DNode *record){
		return NULL;
	}
	virtual ~Algrithom(){};
};

// TODO:  在此处引用程序需要的其他头文件
