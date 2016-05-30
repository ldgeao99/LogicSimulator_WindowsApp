
// PLS2Doc.cpp : CPLS2Doc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "PLS2.h"
#endif

#include "PLS2Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPLS2Doc

IMPLEMENT_DYNCREATE(CPLS2Doc, CDocument)

BEGIN_MESSAGE_MAP(CPLS2Doc, CDocument)
END_MESSAGE_MAP()


// CPLS2Doc 생성/소멸

CPLS2Doc::CPLS2Doc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CPLS2Doc::~CPLS2Doc()
{
}

BOOL CPLS2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	ls.AllPointClear();
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CPLS2Doc serialization

void CPLS2Doc::Serialize(CArchive& ar)
{
	int gate = -1;
	CPoint pointofpif;
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
		for (int i = 0; i < INDEX; i++)
			for (int j = 0; j < INDEX; j++) {
				gate = ls.pif[i][j].serializegate;
				ar << gate;
			}
		ls.line.Serialize(ar);
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
		for (int i = 0; i < INDEX; i++)
			for (int j = 0; j < INDEX; j++) {
				ar >> gate;
				ls.pif[i][j].serializegate = (WhatGate)gate;
				pointofpif = { i,j };
				switch (ls.pif[i][j].serializegate) {
				case input:
					ls.count_input++;
					ls.create_input(&(ls.in[ls.count_input]), pointofpif);
					break;
				case output:
					ls.count_output++;
					ls.pif[i][j].value;
					ls.create_output(&ls.out[ls.count_output], pointofpif);
					break;
				case and:
					ls.count_and++;
					ls.create_and(&ls.and[ls.count_and], pointofpif); // 만드는 함수 호출.
					break;
				case xor:
					ls.count_xor++;
					ls.pif[i][j].xor = ls.count_xor;
					ls.create_xor(&ls.xor[ls.count_xor], pointofpif); // 만드는 함수 호출.
					break;
				case nor:
					ls.count_nor++;
					ls.create_nor(&ls.nor[ls.count_nor], pointofpif); // 만드는 함수 호출.
					break;
				case nand:
					ls.count_nand++;
					ls.create_nand(&ls.nand[ls.count_nand], pointofpif); // 만드는 함수 호출.
					break;
				case or :
					ls.count_or++;
					ls.pif[i][j]. or = ls.count_or;
					ls.create_or(&ls. or [ls.count_or], pointofpif);
					break;
				case not:
					ls.count_not++;
					ls.pif[i][j].not = ls.count_not;
					ls.create_not(&ls. not [ls.count_not], pointofpif);
					break;
				case tff:
					ls.count_tff++;
					ls.create_tff(&ls.tff[ls.count_tff], pointofpif);
					break;
				case lsclock:
					ls.count_clock++;
					ls.create_clock(&ls.clock[ls.count_clock], pointofpif);
					//SetTimer(ls.count_clock, 500, NULL);
					break;
				case dff:
					ls.count_dff++;
					ls.create_dff(&ls.dff[ls.count_dff], pointofpif);
					break;
				case jkff:
					ls.count_jkff++;
					ls.create_jkff(&ls.jkff[ls.count_jkff], pointofpif);
					break;
				}
			}
		ls.line.Serialize(ar);
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CPLS2Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CPLS2Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CPLS2Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CPLS2Doc 진단

#ifdef _DEBUG
void CPLS2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPLS2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPLS2Doc 명령
