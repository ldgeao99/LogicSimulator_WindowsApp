#pragma once
#include "stdafx.h"

#define INDEX 200

//enum변수입니다.
enum WhatGate { nothing, input, output, line, and, or, xor, nand, nor, nxor, not ,lsclock, dff, jkff, tff, seg7, lib, dcd};
enum WhereFixed { DEFAULT, SERO, GARO }; // 그림그릴 때 가로가 고정되었나 세로가 고정되었나?
enum Direct { RIGHT, LEFT, BOTTOM, TOP };

class LogicSimulator
{

public:
	//구조체입니다.
public:

	struct PointInfo {

		//각각 몇번인가
		int input = -1; //입력
		int output = -1; //출력
		int and = -1;
		int or = -1;
		int xor = -1;
		int not = -1;
		int line = -1;
		int nand = -1;
		int nor = -1;
		int dff = -1;
		int jkff = -1;
		int tff = -1;
		int seg7 = -1;
		int lib = -1;
		int clock = -1;
		int dcd = -1;


		BOOL gatein = FALSE; //게이트의 입력값으로 사용되는가
		BOOL gateout = FALSE; //게이트의 출력값으로 사용되는가

		BOOL lineok = FALSE;
		WhatGate gate = nothing;
		WhatGate serializegate = nothing;
		BOOL usingpoint = FALSE;

		int direct = 0;

		int* value = NULL;
	}pinfo;

	struct Input {//완성
		int value = 0; // 가지는 값.
		CString name = _T("IN");
		CPoint clicked{ -1, -1 }; // 사각형의 중점.
		CPoint min; // 사각형의 왼쪽 끝점
		CPoint max; // 사각형의 오른쪽 끝점
		CPoint output;  // 값을 내보낼 수 있는 점.
		BOOL serial = FALSE;
		Direct direct = ::RIGHT;
	};

	struct Output {//완성
		int value = 0;
		CString name = _T("OUT");
		CPoint clicked{ -1, -1 };
		CPoint min;
		CPoint max;
		CPoint input;
		BOOL serial = FALSE;
		Direct direct = ::RIGHT;

	};

	struct OneLinePoint {
		CPoint firstPt;
		CPoint secondPt;
		OneLinePoint() {}
		OneLinePoint(CPoint a, CPoint b) {
			firstPt = a;
			secondPt = b;
		}
	};

	struct AndGate { // 입력값은 pif[input[0].x][input[0].y].value * 뭐 이런식으로 얻을 수 있음.
		int value = 0;  // 값을 내보내는 변수
		CString name = _T("AND");
		CPoint clicked{ -1, -1 };
		CPoint min;
		CPoint max;
		CPoint output;
		CPoint input[2];
		BOOL serial = FALSE;
		Direct direct = ::RIGHT;
	};

	struct XorGate {
		int value = 0;
		CString name = _T("XOR"); // caption
		CPoint clicked{ -1, -1 }; // 사각형의 중점.
		CPoint min; // 사각형의 왼쪽 끝점
		CPoint max; // 사각형의 오른쪽 끝점
		CPoint output;  // 값을 내보낼 수 있는 점.
		CPoint input[2];
		BOOL serial = FALSE;
		Direct direct = ::RIGHT;
	};

	struct NorGate {
		int value = 0;
		CString name = _T("NOR"); // caption
		CPoint clicked{ -1, -1 }; // 사각형의 중점.
		CPoint min; // 사각형의 왼쪽 끝점
		CPoint max; // 사각형의 오른쪽 끝점
		CPoint output;  // 값을 내보낼 수 있는 점.
		CPoint input[2];
		BOOL serial = FALSE;
		Direct direct = ::RIGHT;
	};

	struct NAndGate {
		int value = 0;
		CString name = _T("NAND");
		CPoint clicked{ -1, -1 }; // 사각형의 중점.
		CPoint min; // 사각형의 왼쪽 끝점
		CPoint max; // 사각형의 오른쪽 끝점
		CPoint output;  // 값을 내보낼 수 있는 점.
		CPoint input[2];
		BOOL serial = FALSE;
		Direct direct = ::RIGHT;
	};

	struct OrGate {
		int value = 0;
		CString name = _T("OR");
		CPoint clicked{ -1, -1 };
		CPoint min;
		CPoint max;
		CPoint output;
		CPoint input[2];
		BOOL serial = FALSE;
		Direct direct = ::RIGHT;
	};

	struct NotGate {
		int value = 0;
		CString name = _T("NOT");
		CPoint clicked{ -1. - 1 };
		CPoint min;
		CPoint max;
		CPoint output;
		CPoint input;
		BOOL serial = FALSE;
		Direct direct = ::RIGHT;
	};

	struct TFF{
		int value = 0;
		int value2 = 1;
		CString name = _T("TFF");
		CPoint clicked{ -1. - 1 };
		CPoint min;
		CPoint max;
		CPoint output[2];
		CPoint input;
		CPoint clock;
		BOOL trigger = TRUE; //true->상승 false->하강
		int newclock = 0;
		int oldclock = 0;
		BOOL serial = FALSE;
		Direct direct = ::RIGHT;
	};

	struct Clock {
		int value = 0;
		CString name = _T("CLK");
		CPoint clicked{ -1. - 1 };
		CPoint min;
		CPoint max;
		CPoint output;
		BOOL serial = FALSE;
		Direct direct = ::RIGHT;
	};

	struct DFF {
		int value = 0;
		int value2 = 1;
		CString name = _T("DFF");
		CPoint clicked{ -1. - 1 };
		CPoint min;
		CPoint max;
		CPoint output[2];
		CPoint input;
		CPoint clock;
		BOOL trigger = TRUE; //true->상승 false->하강
		int newclock = 0;
		int oldclock = 0;
		BOOL serial = FALSE;
		Direct direct = ::RIGHT;
	};

	struct JKFF {
		int value = 0;
		int value2 = 1;
		CString name = _T("JKFF");
		CPoint clicked{ -1. - 1 };
		CPoint min;
		CPoint max;
		CPoint output[2];
		CPoint input[2];
		CPoint clock;
		BOOL trigger = TRUE; //true->상승 false->하강
		int newclock = 0;
		int oldclock = 0;
		BOOL serial = FALSE;
		Direct direct = ::RIGHT;
	};

	struct SEG7 {
		int value[7] = { 0, };
		CString name = _T("7SEG");
		CPoint clicked{ -1. - 1 };
		CPoint min;
		CPoint max;
		CPoint input[7];
		BOOL serial = FALSE;
		Direct direct = ::RIGHT;
	};

	struct serialize {
		WhatGate gate;
		int count;
	};

	struct Library {
		int value[7] = { 0,0,0,0,0,0,0 };
		CString name = _T("LIB");
		CPoint clicked{ -1. - 1 };
		CPoint min;
		CPoint max;
		CPoint input[7];
		CPoint output[7];
		BOOL serial = FALSE;
		Direct direct = ::RIGHT;
	};

	struct Decoder {
		int value[7] = { 0,0,0,0,0,0,0 };
		CString name = _T("DCD");
		CPoint clicked{ -1. - 1 };
		CPoint min;
		CPoint max;
		CPoint input[4];
		CPoint output[7];
		BOOL serial = FALSE;
		Direct direct = ::RIGHT;
	};

	//변수입니다.
public:
	PointInfo pif[INDEX][INDEX];
	CArray<OneLinePoint, OneLinePoint&> line; // 각 원소가 한 라인
	Input in[INDEX];
	Output out[INDEX];
	AndGate and[INDEX];
	XorGate xor[INDEX];
	NorGate nor[INDEX];
	NAndGate nand[INDEX];
	OrGate or [INDEX];
	NotGate not[INDEX];
	TFF tff[INDEX];
	Clock clock[INDEX];
	DFF dff[INDEX];
	JKFF jkff[INDEX];
	SEG7 seg7[INDEX];
	Library lib[INDEX];
	Decoder dcd[INDEX];

	CPoint downPoint;
	CPoint upPoint;



	WhereFixed wherefixed = DEFAULT;
	WhatGate whatgate = nothing;

	bool canDrawState = false;
	int count_input = -1;
	int count_output = -1;
	int count_and = -1;
	int count_xor = -1;
	int count_nor = -1;
	int count_nand = -1;
	int count_or = -1;
	int count_not = -1;
	int count_clock = -1;
	int count_tff = -1;
	int count_dff = -1;
	int count_jkff = -1;
	int count_line = -1;
	int count_seg7 = -1;
	int count_lib = -1;
	int count_dcd = -1;

	int create = -1; // 이 숫자에 따라 무엇을 생성할 지가 정해짐.

	serialize serial[300];
	int count_serial = -1;

	int existlibrary = 0;
	int readylibaray = 0;
//함수입니다.
public:
	LogicSimulator::LogicSimulator();
	void OnePointClear(PointInfo *pif);
	void AllPointClear();
	void print(LogicSimulator ls);
	void create_input(Input* in, CPoint clicked);
	void create_output(Output* out, CPoint clicked);
	void create_and(AndGate *and, CPoint clicked);
	void SavePointOnTheLine(CPoint old_start, CPoint old_end, WhereFixed old_wherefixed);
	void create_xor(XorGate *xor, CPoint clicked);
	void create_nor(NorGate *nor, CPoint clicked);
	void create_nand(NAndGate *nand, CPoint clicked);
	void create_or(OrGate * or , CPoint clicked);
	void create_not(NotGate * not, CPoint clicked);
	void create_tff(TFF * not, CPoint clicked);
	void create_clock(Clock * not, CPoint clicked);
	void create_dff(DFF * dff, CPoint clicked);
	void create_jkff(JKFF * jkff, CPoint clicked);
	void create_line(CPoint firstPt, CPoint secondPt, int index);
	void create_lib(Library *lib, CPoint clicked);
	void create_seg7(SEG7 * seg7, CPoint clicked);
	void create_dcd(Decoder *dcd, CPoint clicked);
	void calculate_output(Output *out);
	void calculate_xor(XorGate *xor);
	void calculate_nor(NorGate *nor);
	void calculate_or(OrGate * or );
	void calculate_not(NotGate * not);
	void calculate_tff(TFF *tff);
	void calculate_jkff(JKFF *jkff);
	void calculate_and(AndGate *and);
	void calculate_nand(NAndGate *nand);
	void calculate_seg7(SEG7 * seg7);
	void calculate_dff(DFF *dff);
	void calculate_lib(Library *lib, LogicSimulator *ls);
	void calculate_dcd(Decoder *dcd);
	int serialize_gate(int x, int y);
	void run(int repeat, int se[10], LogicSimulator *lib);
	void rotate_and(AndGate *and, Direct dir);
	void rotate_input(Input *in, Direct dir);
	void rotate_output(Output *out, Direct dir);
	void rotate_or(OrGate *or, Direct dir);
	void rotate_not(NotGate * not , Direct dir);
	void rotate_nand(NAndGate * nand , Direct dir);
	void rotate_nor(NorGate * nor , Direct dir);
	void rotate_xor(XorGate * xor , Direct dir);
	void rotate_dff(DFF *dff, Direct dir);
	void rotate_jkff(JKFF *jkff, Direct dir);
	void rotate_tff(TFF *tff, Direct dir);
	void rotate_clock(Clock *clock, Direct dir);
	void rotate_seg7(SEG7 *seg7, Direct dir);
	void rotate_lib(Library *lib, Direct dir);
	void lsdelete(WhatGate gate, CPoint clicked, int num);
};