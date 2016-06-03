// WaveDoc.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "PLS2.h"
#include "WaveDoc.h"


// CWaveDoc

IMPLEMENT_DYNCREATE(CWaveDoc, CDocument)

CWaveDoc::CWaveDoc()
{
}

BOOL CWaveDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	return TRUE;
}

CWaveDoc::~CWaveDoc()
{
}


BEGIN_MESSAGE_MAP(CWaveDoc, CDocument)
END_MESSAGE_MAP()


// CWaveDoc 진단입니다.

#ifdef _DEBUG
void CWaveDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifndef _WIN32_WCE
void CWaveDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

#ifndef _WIN32_WCE
// CWaveDoc serialization입니다.

void CWaveDoc::Serialize(CArchive& ar)
{
	int l = 0;
	int max = 0;
	int gate = -1;
	int direct = 0;
	CPoint pointofpif;
	CPoint wave(5, 3);
	CString name;
	if (ar.IsStoring())//완성
	{
		// TODO: 여기에 저장 코드를 추가합니다.

		if (ls.readylibaray == 0) {
			ar << 1;
			for (int i = 0; i < INDEX; i++)
				for (int j = 0; j < INDEX; j++) {
					gate = ls.pif[i][j].serializegate;
					ar << gate;
					ar << ls.pif[i][j].direct;
					ar << ls.pif[i][j].name;
				}
			ls.line.Serialize(ar);
			ar << ls.count_line;
			if (ls.existlibrary == 0) {
				ar << 0;
			}
			else {
				ar << 1;
				for (int i = 0; i < INDEX; i++)
					for (int j = 0; j < INDEX; j++) {
						gate = library.pif[i][j].serializegate;
						ar << gate;
						ar << library.pif[i][j].direct;
						ar << ls.pif[i][j].name;
					}
				library.line.Serialize(ar);
				ar << library.count_line;
			}
		}
		else {
			ar << 0;
			ar << 1;
			for (int i = 0; i < INDEX; i++)
				for (int j = 0; j < INDEX; j++) {
					gate = ls.pif[i][j].serializegate;
					ar << gate;
					ar << ls.pif[i][j].direct;
					ar << ls.pif[i][j].name;
				}
			ls.line.Serialize(ar);
			ar << ls.count_line;
		}

	}
	else//완성
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
		ar >> l;
		if (l == 1) {
			for (int i = 0; i < INDEX; i++)
				for (int j = 0; j < INDEX; j++) {
					ar >> gate;
					ar >> direct;
					ar >> name;
					ls.pif[i][j].direct = (Direct)direct;
					ls.pif[i][j].serializegate = (WhatGate)gate;
					pointofpif = { i,j };
					switch (ls.pif[i][j].serializegate) {
					case input:
						ls.count_input++;
						ls.pif[i][j].input = ls.count_input;
						ls.create_input(&(ls.in[ls.count_input]), pointofpif);
						ls.rotate_input(&(ls.in[ls.count_input]), (Direct)direct);
						ls.in[ls.count_input].name = name;
						ls2.count_input++;
						ls2.create_input(&(ls2.in[ls2.count_input]), wave);
						wave.y = wave.y + 3;
						break;
					case output:
						ls.count_output++;
						ls.pif[i][j].output = ls.count_output;
						ls.create_output(&ls.out[ls.count_output], pointofpif);
						ls.rotate_output(&ls.out[ls.count_output], (Direct)direct);
						ls.out[ls.count_output].name = name;
						ls2.count_output++;
						ls2.create_output(&(ls2.out[ls2.count_output]), wave);
						wave.y = wave.y + 3;
						break;
					case and:
						ls.count_and++;
						ls.pif[i][j].and = ls.count_and;
						ls.create_and(&ls.and[ls.count_and], pointofpif); // 만드는 함수 호출.
						ls.rotate_and(&ls.and[ls.count_and], (Direct)direct);
						ls.and[ls.count_and].name = name;
						break;
					case xor:
						ls.count_xor++;
						ls.pif[i][j].xor = ls.count_xor;
						ls.create_xor(&ls.xor[ls.count_xor], pointofpif); // 만드는 함수 호출.
						ls.rotate_xor(&ls.xor[ls.count_xor], (Direct)direct);
						ls.xor[ls.count_xor].name = name;
						break;
					case nor:
						ls.count_nor++;
						ls.pif[i][j].nor = ls.count_nor;
						ls.create_nor(&ls.nor[ls.count_nor], pointofpif); // 만드는 함수 호출.
						ls.rotate_nor(&ls.nor[ls.count_nor], (Direct)direct);
						ls.nor[ls.count_nor].name = name;
						break;
					case nand:
						ls.count_nand++;
						ls.pif[i][j].nand = ls.count_nand;
						ls.create_nand(&ls.nand[ls.count_nand], pointofpif); // 만드는 함수 호출.
						ls.rotate_nand(&ls.nand[ls.count_nand], (Direct)direct);
						ls.nand[ls.count_nand].name = name;
						break;
					case or :
						ls.count_or++;
						ls.pif[i][j]. or = ls.count_or;
						ls.create_or(&ls. or [ls.count_or], pointofpif);
						ls.rotate_or(&ls. or [ls.count_or], (Direct)direct);
						ls. or [ls.count_or].name = name;
						break;
					case not:
						ls.count_not++;
						ls.pif[i][j].not = ls.count_not;
						ls.create_not(&ls. not [ls.count_not], pointofpif);
						ls.rotate_not(&ls. not [ls.count_not], (Direct)direct);
						ls. not [ls.count_not].name = name;
						break;
					case tff:
						ls.count_tff++;
						ls.create_tff(&ls.tff[ls.count_tff], pointofpif);
						ls.rotate_tff(&ls.tff[ls.count_tff], (Direct)direct);
						ls.tff[ls.count_tff].name = name;
						break;
					case lsclock:
						ls.count_clock++;
						ls.create_clock(&ls.clock[ls.count_clock], pointofpif);
						ls.rotate_clock(&ls.clock[ls.count_clock], (Direct)direct);
						ls.clock[ls.count_clock].name = name;
						ls2.count_clock++;
						ls2.create_clock(&(ls2.clock[ls2.count_clock]), wave);
						wave.y = wave.y + 3;
						break;
					case dff:
						ls.count_dff++;
						ls.create_dff(&ls.dff[ls.count_dff], pointofpif);
						ls.rotate_dff(&ls.dff[ls.count_dff], (Direct)direct);
						ls.dff[ls.count_dff].name = name;
						break;
					case jkff:
						ls.count_jkff++;
						ls.create_jkff(&ls.jkff[ls.count_jkff], pointofpif);
						ls.rotate_jkff(&ls.jkff[ls.count_jkff], (Direct)direct);
						ls.jkff[ls.count_jkff].name = name;
						break;
					case seg7:
						ls.count_seg7++;
						ls.create_seg7(&ls.seg7[ls.count_seg7], pointofpif);
						ls.rotate_seg7(&ls.seg7[ls.count_seg7], (Direct)direct);
						ls.seg7[ls.count_seg7].name = name;
						break;
					case dcd:
						ls.count_dcd++;
						ls.create_dcd(&ls.dcd[ls.count_dcd], pointofpif);
						//ls.rotate_dcd(&ls.dcd[ls.count_dcd], (Direct)direct);
						ls.dcd[ls.count_dcd].name = name;
						break;
					case lib:
						ls.count_lib++;
						ls.create_lib(&ls.lib[ls.count_lib], pointofpif);
						ls.rotate_lib(&ls.lib[ls.count_lib], (Direct)direct);
						ls.lib[ls.count_lib].name = name;
						break;
					}
				}
			ls.line.Serialize(ar);
			ar >> max;
			for (int i = 0; i <= max; i++) {
				ls.count_line++;
				ls.create_line(ls.line[i].firstPt, ls.line[i].secondPt, i);
			}
		}
		ar >> l;
		if (l == 1) {
			ls.existlibrary = 1;
			for (int i = 0; i < INDEX; i++)
				for (int j = 0; j < INDEX; j++) {
					ar >> gate;
					ar >> direct;
					ar >> name;
					library.pif[i][j].serializegate = (WhatGate)gate;
					pointofpif = { i,j };
					switch (library.pif[i][j].serializegate) {
					case input:
						ls.count_input++;
						ls.pif[i][j].input = ls.count_input;
						ls.create_input(&(ls.in[ls.count_input]), pointofpif);
						ls.rotate_input(&(ls.in[ls.count_input]), (Direct)direct);
						ls.in[ls.count_input].name = name;
						break;
					case output:
						ls.count_output++;
						ls.pif[i][j].output = ls.count_output;
						ls.create_output(&ls.out[ls.count_output], pointofpif);
						ls.rotate_output(&ls.out[ls.count_output], (Direct)direct);
						ls.out[ls.count_output].name = name;
						break;
					case and:
						ls.count_and++;
						ls.pif[i][j].and = ls.count_and;
						ls.create_and(&ls.and[ls.count_and], pointofpif); // 만드는 함수 호출.
						ls.rotate_and(&ls.and[ls.count_and], (Direct)direct);
						ls.and[ls.count_and].name = name;
						break;
					case xor:
						ls.count_xor++;
						ls.pif[i][j].xor = ls.count_xor;
						ls.create_xor(&ls.xor[ls.count_xor], pointofpif); // 만드는 함수 호출.
						ls.rotate_xor(&ls.xor[ls.count_xor], (Direct)direct);
						ls.xor[ls.count_xor].name = name;
						break;
					case nor:
						ls.count_nor++;
						ls.pif[i][j].nor = ls.count_nor;
						ls.create_nor(&ls.nor[ls.count_nor], pointofpif); // 만드는 함수 호출.
						ls.rotate_nor(&ls.nor[ls.count_nor], (Direct)direct);
						ls.nor[ls.count_nor].name = name;
						break;
					case nand:
						ls.count_nand++;
						ls.pif[i][j].nand = ls.count_nand;
						ls.create_nand(&ls.nand[ls.count_nand], pointofpif); // 만드는 함수 호출.
						ls.rotate_nand(&ls.nand[ls.count_nand], (Direct)direct);
						ls.nand[ls.count_nand].name = name;
						break;
					case or :
						ls.count_or++;
						ls.pif[i][j]. or = ls.count_or;
						ls.create_or(&ls. or [ls.count_or], pointofpif);
						ls.rotate_or(&ls. or [ls.count_or], (Direct)direct);
						ls. or [ls.count_or].name = name;
						break;
					case not:
						ls.count_not++;
						ls.pif[i][j].not = ls.count_not;
						ls.create_not(&ls. not [ls.count_not], pointofpif);
						ls.rotate_not(&ls. not [ls.count_not], (Direct)direct);
						ls. not [ls.count_not].name = name;
						break;
					case tff:
						ls.count_tff++;
						ls.create_tff(&ls.tff[ls.count_tff], pointofpif);
						ls.rotate_tff(&ls.tff[ls.count_tff], (Direct)direct);
						ls.tff[ls.count_tff].name = name;
						break;
					case lsclock:
						ls.count_input++;
						ls.pif[i][j].input = ls.count_input;
						ls.create_input(&(ls.in[ls.count_input]), pointofpif);
						ls.rotate_input(&(ls.in[ls.count_input]), (Direct)direct);
						ls.in[ls.count_input].name = name;
						break;
					case dff:
						ls.count_dff++;
						ls.create_dff(&ls.dff[ls.count_dff], pointofpif);
						ls.rotate_dff(&ls.dff[ls.count_dff], (Direct)direct);
						ls.dff[ls.count_dff].name = name;
						break;
					case jkff:
						ls.count_jkff++;
						ls.create_jkff(&ls.jkff[ls.count_jkff], pointofpif);
						ls.rotate_jkff(&ls.jkff[ls.count_jkff], (Direct)direct);
						ls.jkff[ls.count_jkff].name = name;
						break;
					case seg7:
						ls.count_seg7++;
						ls.create_seg7(&ls.seg7[ls.count_seg7], pointofpif);
						ls.rotate_seg7(&ls.seg7[ls.count_seg7], (Direct)direct);
						ls.seg7[ls.count_seg7].name = name;
						break;
					case dcd:
						ls.count_dcd++;
						ls.create_dcd(&ls.dcd[ls.count_dcd], pointofpif);
						//ls.rotate_dcd(&ls.dcd[ls.count_dcd], (Direct)direct);
						ls.dcd[ls.count_dcd].name = name;
						break;
					case lib:
						ls.count_lib++;
						ls.create_lib(&ls.lib[ls.count_lib], pointofpif);
						ls.rotate_lib(&ls.lib[ls.count_lib], (Direct)direct);
						ls.lib[ls.count_lib].name = name;
						break;
					}
				}
			library.line.Serialize(ar);
			ar >> max;
			for (int i = 0; i <= max; i++) {
				library.count_line++;
				library.create_line(library.line[i].firstPt, library.line[i].secondPt, i);
			}
		}
	}
}
#endif


// CWaveDoc 명령입니다.
