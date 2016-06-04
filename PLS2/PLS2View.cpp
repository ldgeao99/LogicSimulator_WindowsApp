
// PLS2View.cpp : CPLS2View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "PLS2.h"
#endif

#include "PLS2Doc.h"
#include "PLS2View.h"
#include "TextLabel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPLS2View

IMPLEMENT_DYNCREATE(CPLS2View, CView)

BEGIN_MESSAGE_MAP(CPLS2View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_32771, &CPLS2View::Create_Input_BCLK)
	ON_COMMAND(ID_32772, &CPLS2View::Create_Output_BCLK)
	ON_COMMAND(ID_32773, &CPLS2View::Create_AndGate_BCLK)
	ON_COMMAND(ID_32775, &CPLS2View::Create_XorGate_BCLK)
	ON_COMMAND(ID_32778, &CPLS2View::Create_NorGate_BCLK)
	ON_COMMAND(ID_32777, &CPLS2View::Create_NAndGate_BCLK)
	ON_COMMAND(ID_32774, &CPLS2View::Create_OrGate_BCLK)
	ON_COMMAND(ID_32776, &CPLS2View::Create_NotGate_BCLK)
	ON_COMMAND(ID_32781, &CPLS2View::Create_TFF_BCLK)
	ON_COMMAND(ID_32798, &CPLS2View::Create_Clock_BCLK)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_COMMAND(ID_32779, &CPLS2View::Create_DFF_BCLK)
	ON_COMMAND(ID_32780, &CPLS2View::Create_JKFF_BCLK)
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_serialize, &CPLS2View::OnSerialize)
	ON_COMMAND(ID_run, &CPLS2View::Onrun)
	ON_COMMAND(ID_7_Segment, &CPLS2View::Create_7Segment_BCLK)
	ON_COMMAND(ID_1second, &CPLS2View::On1second)
	ON_COMMAND(ID_point5second, &CPLS2View::Onpoint5second)
	ON_COMMAND(ID_point25second, &CPLS2View::Onpoint25second)
	ON_COMMAND(ID_point1second, &CPLS2View::Onpoint1second)
	ON_COMMAND(ID_clockstop, &CPLS2View::Onclockstop)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_32810, &CPLS2View::On_TurnToRight)
	ON_COMMAND(ID_32811, &CPLS2View::On_TurnToLeft)
	ON_COMMAND(ID_32812, &CPLS2View::On_TurnToTop)
	ON_COMMAND(ID_32813, &CPLS2View::On_TurnToBottom)
	ON_COMMAND(ID_lib_ready, &CPLS2View::Onlibready)
	ON_COMMAND(ID_create_lib, &CPLS2View::Oncreatelib)
	ON_COMMAND(ID_decoder, &CPLS2View::Ondecoder)
	ON_COMMAND(ID_autorun, &CPLS2View::Onautorun)
	ON_COMMAND(ID_runstop, &CPLS2View::Onrunstop)
	ON_COMMAND(ID_32825, &CPLS2View::On32825)
	ON_COMMAND(ID_32826, &CPLS2View::On32826)
//	ON_WM_RBUTTONDBLCLK()
	ON_WM_MBUTTONDOWN()
	ON_COMMAND(ID_TextLabel, &CPLS2View::OnTextlabel)
	ON_COMMAND(ID_delete, &CPLS2View::Ondelete)
	ON_COMMAND(ID_del, &CPLS2View::Ondel)
	ON_COMMAND(ID_Copy, &CPLS2View::OnCopy)
	ON_COMMAND(ID_Paste, &CPLS2View::OnPaste)
	ON_COMMAND(ID_cut, &CPLS2View::Oncut)
	ON_COMMAND(ID_DO_UNDO, &CPLS2View::OnDoUndo)
	ON_COMMAND(ID_DO_REDO, &CPLS2View::OnDoRedo)
	ON_UPDATE_COMMAND_UI(ID_DO_UNDO, &CPLS2View::OnUpdateDoUndo)
	ON_UPDATE_COMMAND_UI(ID_DO_REDO, &CPLS2View::OnUpdateDoRedo)
	ON_UPDATE_COMMAND_UI(ID_1second, &CPLS2View::OnUpdate1second)
	ON_UPDATE_COMMAND_UI(ID_point5second, &CPLS2View::OnUpdatepoint5second)
	ON_UPDATE_COMMAND_UI(ID_point25second, &CPLS2View::OnUpdatepoint25second)
	ON_UPDATE_COMMAND_UI(ID_point1second, &CPLS2View::OnUpdatepoint1second)
	ON_UPDATE_COMMAND_UI(ID_32825, &CPLS2View::OnUpdate32825)
	ON_UPDATE_COMMAND_UI(ID_32826, &CPLS2View::OnUpdate32826)
	ON_UPDATE_COMMAND_UI(ID_lib_ready, &CPLS2View::OnUpdatelibready)
	ON_UPDATE_COMMAND_UI(ID_create_lib, &CPLS2View::OnUpdatecreatelib)
	ON_UPDATE_COMMAND_UI(ID_32810, &CPLS2View::OnUpdate32810)
	ON_UPDATE_COMMAND_UI(ID_32811, &CPLS2View::OnUpdate32811)
	ON_UPDATE_COMMAND_UI(ID_32812, &CPLS2View::OnUpdate32812)
	ON_UPDATE_COMMAND_UI(ID_32813, &CPLS2View::OnUpdate32813)
	ON_UPDATE_COMMAND_UI(ID_cut, &CPLS2View::OnUpdatecut)
	ON_UPDATE_COMMAND_UI(ID_32850, &CPLS2View::OnUpdate32850)
END_MESSAGE_MAP()

// CPLS2View 생성/소멸

CPLS2View::CPLS2View()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_str = _T("");
}

CPLS2View::~CPLS2View()
{
}

BOOL CPLS2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CPLS2View 그리기

CPoint CPLS2View::DividedByTwenty(CPoint point)
{
	CPoint currentPoint;
	if (point.x % 20 <= 10)
		currentPoint.x = point.x - point.x % 20;
	else
		currentPoint.x = point.x + (20 - (point.x % 20));

	if (point.y % 20 <= 10)
		currentPoint.y = point.y - point.y % 20;
	else
		currentPoint.y = point.y + (20 - (point.y % 20));

	return currentPoint;
}

void CPLS2View::OnDraw(CDC* pDC)
{
	CPLS2Doc* pDoc = GetDocument();
	CString str;
	CPen black3pen(PS_SOLID, 3, RGB(0, 0, 0));
	pDC->SetTextColor(RGB(0, 0, 255));
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	int i = 0;

	//격자를 그림
	//for (int i = 0; i < 200; i++)
	//	for (int j = 0; j < 100; j++)
	//		pDC->SetPixel(i * 20, j * 20, RGB(0, 0, 0));

	//그려진 선을 그림
	for (int i = 0; i < pDoc->ls.line.GetSize(); i++) {
		pDC->MoveTo(pDoc->ls.line[i].firstPt);
		pDC->LineTo(pDoc->ls.line[i].secondPt);
	}

	//존재하는 input단자의 개수만큼 그려줌.(Rectangle이므로 min(왼쪽끝)점과 max(오른쪽)점을 가짐)
	for (i = 0; i <= pDoc->ls.count_input; i++) {
		if (pDoc->ls.in[i].clicked.x != 0 && pDoc->ls.in[i].clicked.y != 0)
		{
			pDC->Rectangle(pDoc->ls.in[i].min.x*20, pDoc->ls.in[i].min.y*20, pDoc->ls.in[i].max.x*20, pDoc->ls.in[i].max.y*20);
			if (pDoc->ls.in[i].min.x * 20 > 0 ) {
				//str.Format(_T("value = %d"), *(pDoc->ls.pif[pDoc->ls.in[i].clicked.x + 1][pDoc->ls.in[i].clicked.y].value));
				str.Format(_T("%s(%d)"), pDoc->ls.in[i].name, pDoc->ls.in[i].value);
				pDC->SetBkMode(TRANSPARENT);
				pDC->TextOutW(pDoc->ls.in[i].min.x * 20, pDoc->ls.in[i].min.y * 20, str);
				pDC->SetBkMode(OPAQUE);
			}
		}
	}
	//존재하는 output단자의 개수만큼 그려줌.(Ellipse이므로 min(왼쪽끝)점과 max(오른쪽)점을 가짐)
	for (i = 0; i <= pDoc->ls.count_output; i++) {
		if (pDoc->ls.out[i].clicked.x != 0 && pDoc->ls.out[i].clicked.y != 0)
		{
			pDC->Ellipse(pDoc->ls.out[i].min.x * 20, pDoc->ls.out[i].min.y * 20, pDoc->ls.out[i].max.x * 20, pDoc->ls.out[i].max.y * 20);
			if (pDoc->ls.out[i].min.x * 20 > 0) {
				str.Format(_T("%s(%d)"), pDoc->ls.out[i].name, pDoc->ls.out[i].value);
				pDC->SetBkMode(TRANSPARENT);
				pDC->TextOutW(pDoc->ls.out[i].min.x * 20, pDoc->ls.out[i].min.y * 20, str);
				pDC->SetBkMode(OPAQUE);
			}
		}
	}
	//존재하는 and게이트의 개수만큼 그려줌.(min(왼쪽끝)점과 max(오른쪽)점을 가짐)

	for (i = 0; i <= pDoc->ls.count_and; i++) {
		if (pDoc->ls.and[i].clicked.x != 0 && pDoc->ls.and[i].clicked.y != 0)
		{
			CBitmap bitmap;
			
			if (pDoc->ls.and[i].direct == RIGHT)
				bitmap.LoadBitmapW(IDB_GATE_AND);

			else if (pDoc->ls.and[i].direct == BOTTOM)
				bitmap.LoadBitmapW(IDB_GATE_AND_BOTTOM);

			else if (pDoc->ls.and[i].direct == TOP)
				bitmap.LoadBitmapW(IDB_GATE_AND_TOP);

			else if (pDoc->ls.and[i].direct == LEFT)
				bitmap.LoadBitmapW(IDB_GATE_AND_LEFT);

			BITMAP bmpinfo;
			bitmap.GetBitmap(&bmpinfo);
			CDC dcmem;
			dcmem.CreateCompatibleDC(pDC);
			dcmem.SelectObject(&bitmap);
			pDC->StretchBlt(pDoc->ls.and[i].min.x * 20, pDoc->ls.and[i].min.y * 20, 80, 80, &dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);

			pDC->SetBkMode(TRANSPARENT);
			str.Format(_T("%s(%d)"), pDoc->ls.and[i].name, pDoc->ls.and[i].value);
			pDC->TextOutW(pDoc->ls.and[i].min.x * 20 + 5, pDoc->ls.and[i].min.y * 20 + 30, str);
			pDC->SetBkMode(OPAQUE);

		}
	}

	for (i = 0; i <= pDoc->ls.count_xor; i++) {
		if (pDoc->ls.xor[i].clicked.x != 0 && pDoc->ls.xor[i].clicked.y != 0)
		{
			CBitmap bitmap;

			if (pDoc->ls.xor[i].direct == RIGHT)
				bitmap.LoadBitmapW(IDB_GATE_XOR);

			else if (pDoc->ls.xor[i].direct == BOTTOM)
				bitmap.LoadBitmapW(IDB_GATE_XOR_BOTTOM);

			else if (pDoc->ls.xor[i].direct == TOP) 
				bitmap.LoadBitmapW(IDB_GATE_XOR_TOP);

			else if (pDoc->ls.xor[i].direct == LEFT)
				bitmap.LoadBitmapW(IDB_GATE_XOR_LEFT);

			BITMAP bmpinfo;
			bitmap.GetBitmap(&bmpinfo);
			CDC dcmem;
			dcmem.CreateCompatibleDC(pDC);
			dcmem.SelectObject(&bitmap);
			pDC->StretchBlt(pDoc->ls.xor[i].min.x * 20, pDoc->ls.xor[i].min.y * 20, 80, 80, &dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);

			pDC->SetBkMode(TRANSPARENT);
			str.Format(_T("%s(%d)"), pDoc->ls.xor[i].name, pDoc->ls.xor[i].value);
			pDC->TextOutW(pDoc->ls.xor[i].min.x * 20 + 5, pDoc->ls.xor[i].min.y * 20 + 30, str);
			pDC->SetBkMode(OPAQUE);
		}
	}

	for (i = 0; i <= pDoc->ls.count_nor; i++) {
		if (pDoc->ls.nor[i].clicked.x != 0 && pDoc->ls.nor[i].clicked.y != 0)
		{
			CBitmap bitmap;

			if (pDoc->ls.nor[i].direct == RIGHT)
				bitmap.LoadBitmapW(IDB_GATE_NOR);

			else if (pDoc->ls.nor[i].direct == BOTTOM)
				bitmap.LoadBitmapW(IDB_GATE_NOR_BOTTOM);

			else if (pDoc->ls.nor[i].direct == TOP)
				bitmap.LoadBitmapW(IDB_GATE_NOR_TOP);

			else if (pDoc->ls.nor[i].direct == LEFT)
				bitmap.LoadBitmapW(IDB_GATE_NOR_LEFT);

			BITMAP bmpinfo;
			bitmap.GetBitmap(&bmpinfo);
			CDC dcmem;
			dcmem.CreateCompatibleDC(pDC);
			dcmem.SelectObject(&bitmap);
			pDC->StretchBlt(pDoc->ls.nor[i].min.x * 20, pDoc->ls.nor[i].min.y * 20, 80, 80, &dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);

			pDC->SetBkMode(TRANSPARENT);
			str.Format(_T("%s(%d)"), pDoc->ls.nor[i].name, pDoc->ls.nor[i].value);
			pDC->TextOutW(pDoc->ls.nor[i].min.x * 20 + 5, pDoc->ls.nor[i].min.y * 20 + 30, str);
			pDC->SetBkMode(OPAQUE);
		}
	}

	for (i = 0; i <= pDoc->ls.count_or; i++) {
		if (pDoc->ls. or [i].clicked.x != 0 && pDoc->ls.xor[i].clicked.y != 0) 
		{
			CBitmap bitmap;

			if (pDoc->ls.or[i].direct == RIGHT)
				bitmap.LoadBitmapW(IDB_GATE_OR);

			else if (pDoc->ls.or[i].direct == BOTTOM)
				bitmap.LoadBitmapW(IDB_GATE_OR_BOTTOM);

			else if (pDoc->ls. or [i].direct == TOP)
				bitmap.LoadBitmapW(IDB_GATE_OR_TOP);

			else if (pDoc->ls. or [i].direct == LEFT)
				bitmap.LoadBitmapW(IDB_GATE_OR_LEFT);

			BITMAP bmpinfo;
			bitmap.GetBitmap(&bmpinfo);
			CDC dcmem;
			dcmem.CreateCompatibleDC(pDC);
			dcmem.SelectObject(&bitmap);
			pDC->StretchBlt(pDoc->ls. or [i].min.x * 20, pDoc->ls. or [i].min.y * 20, 80, 80, &dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);

			pDC->SetBkMode(TRANSPARENT);
			str.Format(_T("%s(%d)"), pDoc->ls.or[i].name, pDoc->ls. or [i].value);
			pDC->TextOutW(pDoc->ls.or[i].min.x * 20 + 5, pDoc->ls.or[i].min.y * 20 + 30, str);
			pDC->SetBkMode(OPAQUE);
		}
	}

	for (i = 0; i <= pDoc->ls.count_not; i++) {
		if (pDoc->ls. not [i].clicked.x != 0 && pDoc->ls.not[i].clicked.y != 0) 
		{
			CBitmap bitmap;

			if (pDoc->ls.not[i].direct == RIGHT)
				bitmap.LoadBitmapW(IDB_GATE_NOT);

			else if (pDoc->ls.not[i].direct == BOTTOM) 
				bitmap.LoadBitmapW(IDB_GATE_NOT_BOTTOM);

			else if (pDoc->ls.not[i].direct == TOP)
				bitmap.LoadBitmapW(IDB_GATE_NOT_TOP);

			else if (pDoc->ls.not[i].direct == LEFT) 
				bitmap.LoadBitmapW(IDB_GATE_NOT_LEFT);


			BITMAP bmpinfo;
			bitmap.GetBitmap(&bmpinfo);
			CDC dcmem;
			dcmem.CreateCompatibleDC(pDC);
			dcmem.SelectObject(&bitmap);
			pDC->StretchBlt(pDoc->ls. not [i].min.x * 20, pDoc->ls. not [i].min.y * 20, 80, 80, &dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);

			pDC->SetBkMode(TRANSPARENT);
			str.Format(_T("%s(%d)"), pDoc->ls.not[i].name, pDoc->ls.not[i].value);
			pDC->TextOutW(pDoc->ls. not [i].min.x * 20 + 5, pDoc->ls. not [i].min.y * 20 + 30, str);
			pDC->SetBkMode(OPAQUE);
		}
	}


	for (i = 0; i <= pDoc->ls.count_nand; i++) {
		if (pDoc->ls.nand[i].clicked.x != 0 && pDoc->ls.nand[i].clicked.y != 0)
		{
			CBitmap bitmap;

			if (pDoc->ls.nand[i].direct == RIGHT)
				bitmap.LoadBitmapW(IDB_GATE_NAND);

			else if (pDoc->ls.nand[i].direct == BOTTOM)
				bitmap.LoadBitmapW(IDB_GATE_NAND_BOTTOM);

			else if (pDoc->ls.nand[i].direct == TOP)
				bitmap.LoadBitmapW(IDB_GATE_NAND_TOP);

			else if (pDoc->ls.nand[i].direct == LEFT)
				bitmap.LoadBitmapW(IDB_GATE_NAND_LEFT);

			BITMAP bmpinfo;
			bitmap.GetBitmap(&bmpinfo);
			CDC dcmem;
			dcmem.CreateCompatibleDC(pDC);
			dcmem.SelectObject(&bitmap);
			pDC->StretchBlt(pDoc->ls.nand[i].min.x * 20, pDoc->ls.nand[i].min.y * 20, 80, 80, &dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);

			pDC->SetBkMode(TRANSPARENT);
			str.Format(_T("%s(%d)"), pDoc->ls.nand[i].name, pDoc->ls.nand[i].value);
			pDC->TextOutW(pDoc->ls.nand[i].min.x * 20 + 5, pDoc->ls.nand[i].min.y * 20 + 30, str);
			pDC->SetBkMode(OPAQUE);
		}
	}

	for (i = 0; i <= pDoc->ls.count_clock; i++) {
		if (pDoc->ls.clock[i].clicked.x != 0 && pDoc->ls.clock[i].clicked.y != 0)
		{
			pDC->Rectangle(pDoc->ls.clock[i].min.x * 20, pDoc->ls.clock[i].min.y * 20, pDoc->ls.clock[i].max.x * 20, pDoc->ls.clock[i].max.y * 20);
			pDC->Ellipse(pDoc->ls.clock[i].min.x * 20, pDoc->ls.clock[i].min.y * 20, pDoc->ls.clock[i].max.x * 20, pDoc->ls.clock[i].max.y * 20);
			if (pDoc->ls.clock[i].min.x * 20 > 0) {
				//str.Format(_T("value = %d"), *(pDoc->ls.pif[pDoc->ls.clock[i].clicked.x + 1][pDoc->ls.clock[i].clicked.y].value));
				pDC->SetBkMode(TRANSPARENT);
				str.Format(_T("%s(%d)"), pDoc->ls.clock[i].name, pDoc->ls.clock[i].value);
				pDC->TextOutW(pDoc->ls.clock[i].min.x * 20, pDoc->ls.clock[i].min.y * 20, str);
				pDC->SetBkMode(OPAQUE);
			}
		}
	}

	for (i = 0; i <= pDoc->ls.count_tff; i++) {
		if (pDoc->ls.tff[i].clicked.x != 0 && pDoc->ls.tff[i].clicked.y != 0)
		{
			CBitmap bitmap;

			if (pDoc->ls. tff [i].direct == RIGHT)
				bitmap.LoadBitmapW(IDB_FF_T);

			else if (pDoc->ls.tff[i].direct == BOTTOM)
				bitmap.LoadBitmapW(IDB_FF_T_BOTTOM);

			else if (pDoc->ls.tff[i].direct == TOP)
				bitmap.LoadBitmapW(IDB_FF_T_TOP);

			else if (pDoc->ls.tff[i].direct == LEFT)
				bitmap.LoadBitmapW(IDB_FF_T_LEFT);

			BITMAP bmpinfo;
			bitmap.GetBitmap(&bmpinfo);
			CDC dcmem;
			dcmem.CreateCompatibleDC(pDC);
			dcmem.SelectObject(&bitmap);
			pDC->StretchBlt(pDoc->ls.tff[i].min.x * 20, pDoc->ls.tff[i].min.y * 20, 120, 120, &dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);

			pDC->SetBkMode(TRANSPARENT);
			str.Format(_T("%s(%d)"), pDoc->ls.tff[i].name, pDoc->ls.tff[i].value);
			pDC->TextOutW(pDoc->ls.tff[i].min.x * 20 + 5, pDoc->ls.tff[i].min.y * 20 + 20, str);
			pDC->SetBkMode(OPAQUE);
		}
	}

	for (i = 0; i <= pDoc->ls.count_dff; i++) {
		if (pDoc->ls.dff[i].clicked.x != 0 && pDoc->ls.dff[i].clicked.y != 0)
		{
			CBitmap bitmap;

			if (pDoc->ls.dff[i].direct == RIGHT)
				bitmap.LoadBitmapW(IDB_FF_D);

			else if (pDoc->ls.dff[i].direct == BOTTOM)
				bitmap.LoadBitmapW(IDB_FF_D_BOTTOM);

			else if (pDoc->ls.dff[i].direct == TOP)
				bitmap.LoadBitmapW(IDB_FF_D_TOP);

			else if (pDoc->ls.dff[i].direct == LEFT)
				bitmap.LoadBitmapW(IDB_FF_D_LEFT);

			BITMAP bmpinfo;
			bitmap.GetBitmap(&bmpinfo);
			CDC dcmem;
			dcmem.CreateCompatibleDC(pDC);
			dcmem.SelectObject(&bitmap);
			pDC->StretchBlt(pDoc->ls.dff[i].min.x * 20, pDoc->ls.dff[i].min.y * 20, 120, 120, &dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);

			pDC->SetBkMode(TRANSPARENT);
			str.Format(_T("%s(%d)"), pDoc->ls.dff[i].name, pDoc->ls.dff[i].value);
			pDC->TextOutW(pDoc->ls.dff[i].min.x * 20 + 5, pDoc->ls.dff[i].min.y * 20 + 20, str);
			pDC->SetBkMode(OPAQUE);
		}
	}
	
	for (i = 0; i <= pDoc->ls.count_jkff; i++) {
		if (pDoc->ls.jkff[i].clicked.x != 0 && pDoc->ls.jkff[i].clicked.y != 0)
		{
			CBitmap bitmap;

			if (pDoc->ls.jkff[i].direct == RIGHT)
				bitmap.LoadBitmapW(IDB_FF_JK);

			else if (pDoc->ls.jkff[i].direct == BOTTOM)
				bitmap.LoadBitmapW(IDB_FF_JK_BOTTOM);

			else if (pDoc->ls.jkff[i].direct == TOP)
				bitmap.LoadBitmapW(IDB_FF_JK_TOP);

			else if (pDoc->ls.jkff[i].direct == LEFT)
				bitmap.LoadBitmapW(IDB_FF_JK_LEFT);

			BITMAP bmpinfo;
			bitmap.GetBitmap(&bmpinfo);
			CDC dcmem;
			dcmem.CreateCompatibleDC(pDC);
			dcmem.SelectObject(&bitmap);
			pDC->StretchBlt(pDoc->ls.jkff[i].min.x * 20, pDoc->ls.jkff[i].min.y * 20, 120, 120, &dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);

			pDC->SetBkMode(TRANSPARENT);
			str.Format(_T("%s(%d)"), pDoc->ls.jkff[i].name, pDoc->ls.jkff[i].value);
			pDC->TextOutW(pDoc->ls.jkff[i].min.x * 20 + 5, pDoc->ls.jkff[i].min.y * 20 + 20, str);
			pDC->SetBkMode(OPAQUE);
		}
	}

	for (i = 0; i <= pDoc->ls.count_seg7; i++) {
		if (pDoc->ls.seg7[i].clicked.x != 0 && pDoc->ls.seg7[i].clicked.y != 0)
		{
			CBitmap bitmap;
			bitmap.LoadBitmapW(IDB_GATE_SEG7);
			BITMAP bmpinfo;
			bitmap.GetBitmap(&bmpinfo);
			CDC dcmem;
			dcmem.CreateCompatibleDC(pDC);
			dcmem.SelectObject(&bitmap);
			pDC->SelectObject(&black3pen);
			pDC->StretchBlt(pDoc->ls.seg7[i].min.x * 20, pDoc->ls.seg7[i].min.y * 20, 120, 120, &dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
			pDC->SetBkMode(TRANSPARENT);
			str.Format(_T("%s"), pDoc->ls.seg7[i].name);
			pDC->TextOutW(pDoc->ls.seg7[i].min.x * 20 + 5, pDoc->ls.seg7[i].min.y * 20 + 20, str);
			pDC->SetBkMode(OPAQUE);
			if (pDoc->ls.seg7[i].value[0] == 1)
			{
				pDC->MoveTo((pDoc->ls.seg7[i].min.x + 2) * 20, (pDoc->ls.seg7[i].min.y + 1) * 20);
				pDC->LineTo((pDoc->ls.seg7[i].min.x + 4) * 20, (pDoc->ls.seg7[i].min.y + 1) * 20);
			}
			if (pDoc->ls.seg7[i].value[1] == 1)
			{
				pDC->MoveTo((pDoc->ls.seg7[i].min.x + 4) * 20, (pDoc->ls.seg7[i].min.y + 1) * 20);
				pDC->LineTo((pDoc->ls.seg7[i].min.x + 4) * 20, (pDoc->ls.seg7[i].min.y + 3) * 20);
			}
			if (pDoc->ls.seg7[i].value[2] == 1)
			{
				pDC->MoveTo((pDoc->ls.seg7[i].min.x + 4) * 20, (pDoc->ls.seg7[i].min.y + 3) * 20);
				pDC->LineTo((pDoc->ls.seg7[i].min.x + 4) * 20, (pDoc->ls.seg7[i].min.y + 5) * 20);
			}
			if (pDoc->ls.seg7[i].value[3] == 1)
			{
				pDC->MoveTo((pDoc->ls.seg7[i].min.x + 4) * 20, (pDoc->ls.seg7[i].min.y + 5) * 20);
				pDC->LineTo((pDoc->ls.seg7[i].min.x + 2) * 20, (pDoc->ls.seg7[i].min.y + 5) * 20);
			}
			if (pDoc->ls.seg7[i].value[4] == 1)
			{
				pDC->MoveTo((pDoc->ls.seg7[i].min.x + 2) * 20, (pDoc->ls.seg7[i].min.y + 5) * 20);
				pDC->LineTo((pDoc->ls.seg7[i].min.x + 2) * 20, (pDoc->ls.seg7[i].min.y + 3) * 20);
			}
			if (pDoc->ls.seg7[i].value[5] == 1)
			{
				pDC->MoveTo((pDoc->ls.seg7[i].min.x + 2) * 20, (pDoc->ls.seg7[i].min.y + 3) * 20);
				pDC->LineTo((pDoc->ls.seg7[i].min.x + 2) * 20, (pDoc->ls.seg7[i].min.y + 1) * 20);
			}
			if (pDoc->ls.seg7[i].value[6] == 1)
			{
				pDC->MoveTo((pDoc->ls.seg7[i].min.x + 2) * 20, (pDoc->ls.seg7[i].min.y + 3) * 20);
				pDC->LineTo((pDoc->ls.seg7[i].min.x + 4) * 20, (pDoc->ls.seg7[i].min.y + 3) * 20);
			}
		}
	}

	for (i = 0; i <= pDoc->ls.count_lib; i++) {
		if (pDoc->ls.lib[i].clicked.x != 0 && pDoc->ls.lib[i].clicked.y != 0)
		{
			CBitmap bitmap;
			bitmap.LoadBitmapW(IDB_LIB);
			BITMAP bmpinfo;
			bitmap.GetBitmap(&bmpinfo);
			CDC dcmem;
			dcmem.CreateCompatibleDC(pDC);
			dcmem.SelectObject(&bitmap);
			pDC->SelectObject(&black3pen);
			pDC->StretchBlt(pDoc->ls.lib[i].min.x * 20, pDoc->ls.lib[i].min.y * 20, 120, 120, &dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
			pDC->SetBkMode(TRANSPARENT);
			str.Format(_T("%s"), pDoc->ls.lib[i].name);
			pDC->TextOutW(pDoc->ls.lib[i].min.x * 20 + 5, pDoc->ls.lib[i].min.y * 20 + 20, str);
			str.Format(_T("%d %d %d %d %d %d %d"), pDoc->ls.lib[i].value[0], pDoc->ls.lib[i].value[1],pDoc->ls.lib[i].value[2],pDoc->ls.lib[i].value[3]
				,pDoc->ls.lib[i].value[4],pDoc->ls.lib[i].value[5],pDoc->ls.lib[i].value[6]);
			pDC->TextOutW(pDoc->ls.lib[i].min.x * 20 + 5, pDoc->ls.lib[i].min.y * 20 + 40, str);
			pDC->SetBkMode(OPAQUE);
		}
	}

	for (i = 0; i <= pDoc->ls.count_dcd; i++) {
		if (pDoc->ls.dcd[i].clicked.x != 0 && pDoc->ls.dcd[i].clicked.y != 0)
		{
			CBitmap bitmap;
			bitmap.LoadBitmapW(IDB_LIB);
			BITMAP bmpinfo;
			bitmap.GetBitmap(&bmpinfo);
			CDC dcmem;
			dcmem.CreateCompatibleDC(pDC);
			dcmem.SelectObject(&bitmap);
			pDC->SelectObject(&black3pen);
			pDC->StretchBlt(pDoc->ls.dcd[i].min.x * 20, pDoc->ls.dcd[i].min.y * 20, 120, 120, &dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
			pDC->SetBkMode(TRANSPARENT);
			str.Format(_T("%s"), pDoc->ls.dcd[i].name);
			pDC->TextOutW(pDoc->ls.dcd[i].min.x * 20 + 5, pDoc->ls.dcd[i].min.y * 20 + 20, str);
			str.Format(_T("%d %d %d %d %d %d %d"), pDoc->ls.dcd[i].value[0], pDoc->ls.dcd[i].value[1], pDoc->ls.dcd[i].value[2], pDoc->ls.dcd[i].value[3]
				, pDoc->ls.dcd[i].value[4], pDoc->ls.dcd[i].value[5], pDoc->ls.dcd[i].value[6]);
			pDC->TextOutW(pDoc->ls.dcd[i].min.x * 20 + 5, pDoc->ls.dcd[i].min.y * 20 + 40, str);
			pDC->SetBkMode(OPAQUE);
		}
	}
	CString s;

	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			s.Format(_T("%d"), *(&pDoc->ls.pif[i][j].value));
			//pDC->TextOutW(i*20, j*20, s);
		}
	}

	ReleaseDC(pDC);
}


// CPLS2View 인쇄

BOOL CPLS2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	CPLS2Doc* pDoc = GetDocument();
	pDoc->ls.AllPointClear();
	return DoPreparePrinting(pInfo);
}

void CPLS2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CPLS2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CPLS2View 진단

#ifdef _DEBUG
void CPLS2View::AssertValid() const
{
	CView::AssertValid();
}

void CPLS2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPLS2Doc* CPLS2View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPLS2Doc)));
	return (CPLS2Doc*)m_pDocument;
}
#endif //_DEBUG


// CPLS2View 메시지 처리기
void CPLS2View::OnLButtonDown(UINT nFlags, CPoint point)//완성
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CPLS2Doc* pDoc = GetDocument();
	CClientDC dc(this);
	CPoint p1 = DividedByTwenty(point);
	CPoint pointofpif{ p1.x / 20, p1.y / 20 };
	pDoc->ls.downPoint = DividedByTwenty(point); //마우스를 누르기 시작한 지점의 좌표를 받을 수 있음.

	// 단자 또는 게이트를 생성한다고 할고있을 때.
	if (pDoc->ls.whatgate != nothing) {
		switch (pDoc->ls.whatgate) {
		case input:
			pDoc->ls.count_input++;
			pDoc->ls.create_input(&(pDoc->ls.in[pDoc->ls.count_input]), pointofpif);
			pDoc->ls.whatgate = nothing; // 마우스를 누르는 순간 그 위치에 그려지게 되므로 초기값으로 돌려줌.
			pDoc->ls.savetomem(pointofpif, input, pDoc->ls.count_input, create, pDoc->ls.in[pDoc->ls.count_input].name, pDoc->ls.in[pDoc->ls.count_input].direct);
			Invalidate(1);
			break;
		case output:
			pDoc->ls.count_output++;
			pDoc->ls.pif[p1.x / 20 - 1][p1.y / 20].value;
			pDoc->ls.create_output(&pDoc->ls.out[pDoc->ls.count_output], pointofpif);
			pDoc->ls.whatgate = nothing;
			pDoc->ls.savetomem(pointofpif, output, pDoc->ls.count_output, create, pDoc->ls.out[pDoc->ls.count_output].name, pDoc->ls.out[pDoc->ls.count_output].direct);
			Invalidate(1);
			break;
		case and:
			pDoc->ls.count_and++;
			pDoc->ls.pif[p1.x / 20][p1.y / 20].and = pDoc->ls.count_and;
			pDoc->ls.create_and(&pDoc->ls.and[pDoc->ls.count_and], pointofpif); // 만드는 함수 호출.
			pDoc->ls.savetomem(pointofpif, and, pDoc->ls.count_and, create, pDoc->ls.and[pDoc->ls.count_and].name, pDoc->ls.and[pDoc->ls.count_and].direct);
			pDoc->ls.whatgate = nothing;
			Invalidate(1);
			break;
		case xor:
			pDoc->ls.count_xor++;
			pDoc->ls.pif[p1.x / 20][p1.y / 20].xor = pDoc->ls.count_xor;
			pDoc->ls.create_xor(&pDoc->ls.xor[pDoc->ls.count_xor], pointofpif); // 만드는 함수 호출.
			pDoc->ls.savetomem(pointofpif, xor, pDoc->ls.count_xor, create, pDoc->ls.xor[pDoc->ls.count_xor].name, pDoc->ls.xor[pDoc->ls.count_xor].direct);
			pDoc->ls.whatgate = nothing;
			Invalidate(1);
			break;
		case nor:
			pDoc->ls.count_nor++;
			pDoc->ls.pif[p1.x / 20][p1.y / 20].nor = pDoc->ls.count_nor;
			pDoc->ls.create_nor(&pDoc->ls.nor[pDoc->ls.count_nor], pointofpif); // 만드는 함수 호출.
			pDoc->ls.savetomem(pointofpif, nor, pDoc->ls.count_nor, create, pDoc->ls.nor[pDoc->ls.count_nor].name, pDoc->ls.nor[pDoc->ls.count_nor].direct);
			pDoc->ls.whatgate = nothing;
			Invalidate(1);
			break;
		case nand:
			pDoc->ls.count_nand++;
			pDoc->ls.pif[p1.x / 20][p1.y / 20].nand = pDoc->ls.count_nand;
			pDoc->ls.create_nand(&pDoc->ls.nand[pDoc->ls.count_nand], pointofpif); // 만드는 함수 호출.
			pDoc->ls.savetomem(pointofpif, nand, pDoc->ls.count_nand, create, pDoc->ls.nand[pDoc->ls.count_nand].name, pDoc->ls.nand[pDoc->ls.count_nand].direct);
			pDoc->ls.whatgate = nothing;
			Invalidate(1);
			break;
		case or :
			pDoc->ls.count_or++;
			pDoc->ls.pif[p1.x / 20][p1.y / 20].or = pDoc->ls.count_or;
			pDoc->ls.create_or(&pDoc->ls. or [pDoc->ls.count_or], pointofpif);
			pDoc->ls.savetomem(pointofpif, or , pDoc->ls.count_or, create, pDoc->ls. or [pDoc->ls.count_or].name, pDoc->ls. or [pDoc->ls.count_or].direct);
			pDoc->ls.whatgate = nothing;
			Invalidate(1);
			break;
		case not:
			pDoc->ls.count_not++;
			pDoc->ls.pif[p1.x / 20][p1.y / 20].not = pDoc->ls.count_not;
			pDoc->ls.create_not(&pDoc->ls. not [pDoc->ls.count_not], pointofpif);
			pDoc->ls.savetomem(pointofpif, not, pDoc->ls.count_not, create, pDoc->ls.not[pDoc->ls.count_not].name, pDoc->ls.not[pDoc->ls.count_not].direct);
			pDoc->ls.whatgate = nothing;
			Invalidate(1);
			break;
		case tff:
			pDoc->ls.count_tff++;
			pDoc->ls.create_tff(&pDoc->ls. tff [pDoc->ls.count_tff], pointofpif);
			pDoc->ls.savetomem(pointofpif, tff, pDoc->ls.count_tff, create, pDoc->ls.tff[pDoc->ls.count_tff].name, pDoc->ls.tff[pDoc->ls.count_tff].direct);
			pDoc->ls.whatgate = nothing;
			Invalidate(1);
			break;
		case lsclock:
			pDoc->ls.count_clock++;
			pDoc->ls.create_clock(&pDoc->ls.clock[pDoc->ls.count_clock], pointofpif);
			pDoc->ls.savetomem(pointofpif, lsclock, pDoc->ls.count_clock, create, pDoc->ls.clock[pDoc->ls.count_clock].name, pDoc->ls.clock[pDoc->ls.count_clock].direct);
			pDoc->ls.whatgate = nothing;
			Invalidate(1);
			break;
		case dff:
			pDoc->ls.count_dff++;
			pDoc->ls.create_dff(&pDoc->ls.dff[pDoc->ls.count_dff], pointofpif);
			pDoc->ls.savetomem(pointofpif, dff, pDoc->ls.count_dff, create, pDoc->ls.dff[pDoc->ls.count_dff].name, pDoc->ls.dff[pDoc->ls.count_dff].direct);
			pDoc->ls.whatgate = nothing;
			Invalidate(1);
			break;
		case jkff:
			pDoc->ls.count_jkff++;
			pDoc->ls.create_jkff(&pDoc->ls.jkff[pDoc->ls.count_jkff], pointofpif);
			pDoc->ls.savetomem(pointofpif, jkff, pDoc->ls.count_jkff, create, pDoc->ls.jkff[pDoc->ls.count_jkff].name, pDoc->ls.jkff[pDoc->ls.count_jkff].direct);
			pDoc->ls.whatgate = nothing;
			Invalidate(1);
			break;
		case seg7:
			pDoc->ls.count_seg7++;
			pDoc->ls.create_seg7(&pDoc->ls.seg7[pDoc->ls.count_seg7], pointofpif);
			pDoc->ls.savetomem(pointofpif, seg7, pDoc->ls.count_seg7, create, pDoc->ls.seg7[pDoc->ls.count_seg7].name, pDoc->ls.seg7[pDoc->ls.count_seg7].direct);
			pDoc->ls.whatgate = nothing;
			Invalidate(1);
			break;
		case lib:
			pDoc->ls.count_lib++;
			pDoc->ls.create_lib(&pDoc->ls.lib[pDoc->ls.count_lib], pointofpif);
			pDoc->ls.savetomem(pointofpif, lib, pDoc->ls.count_lib, create, pDoc->ls.lib[pDoc->ls.count_lib].name, pDoc->ls.lib[pDoc->ls.count_lib].direct);
			pDoc->ls.whatgate = nothing;
			Invalidate(1);
			break;
		case ::dcd:
			pDoc->ls.count_dcd++;
			pDoc->ls.create_dcd(&pDoc->ls.dcd[pDoc->ls.count_dcd], pointofpif);
			pDoc->ls.savetomem(pointofpif, dcd, pDoc->ls.count_dcd, create, pDoc->ls.dcd[pDoc->ls.count_dcd].name, pDoc->ls.dcd[pDoc->ls.count_dcd].direct);
			pDoc->ls.whatgate = nothing;
			Invalidate(1);
			break;
		}
	}
	


	else {
		if (pDoc->ls.pif[p1.x / 20][p1.y / 20].lineok == TRUE)
			pDoc->ls.canDrawState = TRUE;
	}


	/* //여기서 선을 그릴 수 있는 곳인지 판단.
	else { // 그밖에 선을 그린다고 알고있을 때.
		if (pDoc->ls.pif[p1.x / 10][p1.y / 10].gate == input) {
			pDoc->ls.pif[p1.x / 10][p1.y / 10].value = pDoc->ls.in[pDoc->ls.pif[p1.x / 10][p1.y / 10].input].value;
			startline = p1;
			drawline = TRUE;
		}
		else if (pDoc->ls.pif[p1.x / 10][p1.y / 10].gate == output) {
			pDoc->ls.pif[p1.x / 10][p1.y / 10].value = pDoc->ls.out[pDoc->ls.pif[p1.x / 10][p1.y / 10].output].value;
			startline = p1;
			drawline = TRUE;
		}
		else if (pDoc->ls.pif[p1.x / 10][p1.y / 10].gate == line) {
			pDoc->ls.pif[p1.x / 10][p1.y / 10].value = pDoc->ls.out[pDoc->ls.pif[p1.x / 10][p1.y / 10].output].value;
			startline = p1;
			drawline = TRUE;
		}
	}
	*/

	CView::OnLButtonDown(nFlags, point);
}


void CPLS2View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CPLS2Doc* pDoc = GetDocument();
	CClientDC dc(this);
	CDC* pDC = GetDC();
	CPoint p1 = DividedByTwenty(point);
	pDoc->ls.upPoint = DividedByTwenty(point); //마우스를 누르기 시작한 지점의 좌표를 받을 수 있음.

	if(pDoc->ls.canDrawState == TRUE){
		pDoc->ls.SavePointOnTheLine(old_start, old_end, old_wherefixed); // 선에대한 점을 저장.
	}

	Invalidate(0);

	//이게 있어야 이전에 그렸던게 안없어짐.
	old_start.x = 0;
	old_start.y = 0;
	old_end.x = 0;
	old_end.y = 0;
	pDoc->ls.canDrawState = FALSE;
	CView::OnLButtonUp(nFlags, point);
}



void CPLS2View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CPLS2Doc* pDoc = GetDocument();
	CPoint p1 = DividedByTwenty(point);
	CPoint pointofpif{ p1.x / 20, p1.y / 20 };
	CPoint movedFirstPoint = DividedByTwenty(p1); // 마우스를 처음 누른 뒤 움직인 첫 위치
	CPoint startPoint = DividedByTwenty(pDoc->ls.downPoint);
	CPen blackpen(PS_SOLID, 1, RGB(0, 0, 0)); // 검정펜
	CPen whitepen(PS_SOLID, 1, RGB(255, 255, 255)); //흰펜
	CPen white3pen(PS_SOLID, 3, RGB(255, 255, 255)); //흰 두꺼운 펜
	CPen gree3npen(PS_SOLID, 3, RGB(0, 255, 0)); //초록 두꺼운 펜
	CBrush whitebrush(RGB(255, 255, 255));
	CDC* pDC = GetDC();
	CBitmap bitmap;
	BITMAP bmpinfo;
	CDC dcmem;
	CRect elrect, eloldrect, elinoutrect, elgaterect, elffrect, elinoutoldrect, elgateoldrect, elffoldrect;
	elrect = {p1.x - 10, p1.y - 10, p1.x + 10, p1.y + 10};
	eloldrect = { oldpoint.x - 10, oldpoint.y - 10, oldpoint.x + 10, oldpoint.y + 10 };

	elinoutrect = { p1.x - 25, p1.y - 25, p1.x + 25, p1.y + 25 };
	elinoutoldrect = { oldpoint.x - 25, oldpoint.y - 25, oldpoint.x + 25, oldpoint.y + 25 };

	elgaterect = { p1.x - 45, p1.y - 45, p1.x + 45, p1.y + 45 };
	elgateoldrect = { oldpoint.x - 45, oldpoint.y - 45, oldpoint.x + 45, oldpoint.y + 45 };

	elffrect = { p1.x - 65, p1.y - 65, p1.x + 65, p1.y + 65 };
	elffoldrect = { oldpoint.x - 65, oldpoint.y - 65, oldpoint.x + 65, oldpoint.y + 65 };

	CRect bitrect;
	bitrect = { oldpoint.x - 40, oldpoint.y - 40, oldpoint.x + 40, oldpoint.y + 40 };
	CRect ffrect;
	ffrect = { oldpoint.x - 60, oldpoint.y - 60, oldpoint.x + 60, oldpoint.y + 60 };
	//"pDoc->ls.create >= 0" 이 상태는 단자 또는 게이트를 메뉴에서 클릭하여 그리려고 하는 상태임.

	if (pDoc->ls.whatgate != nothing) {
		switch (pDoc->ls.whatgate) {
		case input:
			if (oldpoint != p1) {
				Invalidate(0);
			}
			pDC->SelectObject(&whitepen);
			pDC->Rectangle(oldpoint.x - 20, oldpoint.y - 20, oldpoint.x + 20, oldpoint.y + 20);
			pDC->SelectObject(&blackpen);
			pDC->Rectangle(p1.x - 20, p1.y - 20, p1.x + 20, p1.y + 20);
			break;
		case output:
			if (oldpoint != p1) {
				Invalidate(0);
			}
			pDC->SelectObject(&whitepen);
			pDC->Ellipse(oldpoint.x - 20, oldpoint.y - 20, oldpoint.x + 20, oldpoint.y + 20);
			pDC->SelectObject(&blackpen);
			pDC->Ellipse(p1.x - 20, p1.y - 20, p1.x + 20, p1.y + 20);
			break;
		case and:
			if (oldpoint != p1) {
				Invalidate(0);
			}
			bitmap.LoadBitmapW(IDB_GATE_AND);
			bitmap.GetBitmap(&bmpinfo);

			dcmem.CreateCompatibleDC(pDC);
			dcmem.SelectObject(&bitmap);

			pDC->SelectObject(&whitepen);
			pDC->SelectObject(&whitebrush);
			pDC->Rectangle(&bitrect);
			pDC->SelectObject(&blackpen);
			pDC->StretchBlt(p1.x - 40, p1.y - 40, 80, 80, &dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
			break;
		case xor:
			if (oldpoint != p1) {
				Invalidate(0);
			}

			bitmap.LoadBitmapW(IDB_GATE_XOR);
			bitmap.GetBitmap(&bmpinfo);

			dcmem.CreateCompatibleDC(pDC);
			dcmem.SelectObject(&bitmap);

			pDC->SelectObject(&whitepen);
			pDC->SelectObject(&whitebrush);
			pDC->Rectangle(bitrect);
			pDC->SelectObject(&blackpen);
			pDC->StretchBlt(p1.x-40, p1.y-40, 80, 80, &dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
			break;
		case nor:
			if (oldpoint != p1) {
				Invalidate(0);
			}
			bitmap.LoadBitmapW(IDB_GATE_NOR);
			bitmap.GetBitmap(&bmpinfo);

			dcmem.CreateCompatibleDC(pDC);
			dcmem.SelectObject(&bitmap);

			pDC->SelectObject(&whitepen);
			pDC->SelectObject(&whitebrush);
			pDC->Rectangle(bitrect);
			pDC->SelectObject(&blackpen);
			pDC->StretchBlt(p1.x - 40, p1.y - 40, 80, 80, &dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
			break;
		case nand:
			if (oldpoint != p1) {
				Invalidate(0);
			}

			bitmap.LoadBitmapW(IDB_GATE_NAND);
			bitmap.GetBitmap(&bmpinfo);

			dcmem.CreateCompatibleDC(pDC);
			dcmem.SelectObject(&bitmap);

			pDC->SelectObject(&whitepen);
			pDC->SelectObject(&whitebrush);
			pDC->Rectangle(bitrect);
			pDC->SelectObject(&blackpen);
			pDC->StretchBlt(p1.x - 40, p1.y - 40, 80, 80, &dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
			break;
		case or:
			if (oldpoint != p1) {
				Invalidate(0);
			}
			bitmap.LoadBitmapW(IDB_GATE_OR);
			bitmap.GetBitmap(&bmpinfo);

			dcmem.CreateCompatibleDC(pDC);
			dcmem.SelectObject(&bitmap);

			pDC->SelectObject(&whitepen);
			pDC->SelectObject(&whitebrush);
			pDC->Rectangle(bitrect);
			pDC->SelectObject(&blackpen);
			pDC->StretchBlt(p1.x - 40, p1.y - 40, 80, 80, &dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
			break;
		case not:
			if (oldpoint != p1) {
				Invalidate(0);
			}
			bitmap.LoadBitmapW(IDB_GATE_NOT);
			bitmap.GetBitmap(&bmpinfo);

			dcmem.CreateCompatibleDC(pDC);
			dcmem.SelectObject(&bitmap);

			pDC->SelectObject(&whitepen);
			pDC->SelectObject(&whitebrush);
			pDC->Rectangle(bitrect);
			pDC->SelectObject(&blackpen);
			pDC->StretchBlt(p1.x - 40, p1.y - 40, 80, 80, &dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
			break;
		case tff:
			if (oldpoint != p1) {
				Invalidate(0);
			}
			bitmap.LoadBitmapW(IDB_FF_T);
			bitmap.GetBitmap(&bmpinfo);

			dcmem.CreateCompatibleDC(pDC);
			dcmem.SelectObject(&bitmap);

			pDC->SelectObject(&whitepen);
			pDC->SelectObject(&whitebrush);
			pDC->Rectangle(ffrect);
			pDC->SelectObject(&blackpen);
			pDC->StretchBlt(p1.x - 60, p1.y - 60, 120, 120, &dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
			break;
		case lsclock:
			if (oldpoint != p1) {
				Invalidate(0);
			}
			pDC->SelectObject(&whitepen);
			pDC->Rectangle(oldpoint.x - 20, oldpoint.y - 20, oldpoint.x + 20, oldpoint.y + 20);
			pDC->Ellipse(oldpoint.x - 20, oldpoint.y - 20, oldpoint.x + 20, oldpoint.y + 20);
			pDC->SelectObject(&blackpen);
			pDC->Rectangle(p1.x - 20, p1.y - 20, p1.x + 20, p1.y + 20);
			pDC->Ellipse(p1.x - 20, p1.y - 20, p1.x + 20, p1.y + 20);
			break;
		case dff:
			if (oldpoint != p1) {
				Invalidate(0);
			}
			bitmap.LoadBitmapW(IDB_FF_D);
			bitmap.GetBitmap(&bmpinfo);

			dcmem.CreateCompatibleDC(pDC);
			dcmem.SelectObject(&bitmap);

			pDC->SelectObject(&whitepen);
			pDC->SelectObject(&whitebrush);
			pDC->Rectangle(ffrect);
			pDC->SelectObject(&blackpen);
			pDC->StretchBlt(p1.x - 60, p1.y - 60, 120, 120, &dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
			break;
		case jkff:
			if (oldpoint != p1) {
				Invalidate(0);
			}
			bitmap.LoadBitmapW(IDB_FF_JK);
			bitmap.GetBitmap(&bmpinfo);

			dcmem.CreateCompatibleDC(pDC);
			dcmem.SelectObject(&bitmap);

			pDC->SelectObject(&whitepen);
			pDC->SelectObject(&whitebrush);
			pDC->Rectangle(ffrect);
			pDC->SelectObject(&blackpen);
			pDC->StretchBlt(p1.x - 60, p1.y - 60, 120, 120, &dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
			break;
		case seg7:
			if (oldpoint != p1) {
				Invalidate(0);
			}
			bitmap.LoadBitmapW(IDB_GATE_SEG7);
			bitmap.GetBitmap(&bmpinfo);

			dcmem.CreateCompatibleDC(pDC);
			dcmem.SelectObject(&bitmap);

			pDC->SelectObject(&whitepen);
			pDC->SelectObject(&whitebrush);
			pDC->Rectangle(ffrect);
			pDC->SelectObject(&blackpen);
			pDC->StretchBlt(p1.x - 60, p1.y - 60, 120, 120, &dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
			break;
		case lib:
			if (oldpoint != p1) {
				Invalidate(0);
			}
			bitmap.LoadBitmapW(IDB_LIB);
			bitmap.GetBitmap(&bmpinfo);

			dcmem.CreateCompatibleDC(pDC);
			dcmem.SelectObject(&bitmap);

			pDC->SelectObject(&whitepen);
			pDC->SelectObject(&whitebrush);
			pDC->Rectangle(ffrect);
			pDC->SelectObject(&blackpen);
			pDC->StretchBlt(p1.x - 60, p1.y - 60, 120, 120, &dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
			break;
		case ::dcd:
			if (oldpoint != p1) {
				Invalidate(0);
			}
			bitmap.LoadBitmapW(IDB_LIB);
			bitmap.GetBitmap(&bmpinfo);

			dcmem.CreateCompatibleDC(pDC);
			dcmem.SelectObject(&bitmap);

			pDC->SelectObject(&whitepen);
			pDC->SelectObject(&whitebrush);
			pDC->Rectangle(ffrect);
			pDC->SelectObject(&blackpen);
			pDC->StretchBlt(p1.x - 60, p1.y - 60, 120, 120, &dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
			break;
		}
		
	}
	//"pDoc->ls.create < 0 && nFlags & MK_LBUTTON" 이 상태는 메뉴의 게이트 또는 단자를 클릭하지 않은 상태이며 마우스가 눌린상태,, 선을 그릴 수 있음. 
	if (pDoc->ls.create < 0 && nFlags & MK_LBUTTON && pDoc->ls.canDrawState == TRUE) {
		//pDoc->ls.pif[p1.x / 10][p1.y / 10]->linevalue = pDoc->ls.pif[startline.x / 10][startline.y / 10]->linevalue;
		//pDoc->ls.pif[p1.x / 10][p1.y / 10].gate = pDoc->ls.  /*->ls->isline*/;

		//(초기상태)그림을 그릴때 어디가(가로,세로) 고정되는지 정해져 있지 않고 마우스를 누른위치와 현재마우스의 위치가 다르다면 가로 세로 중에서 한쪽으로 고정을 시켜줌.
		if (pDoc->ls.wherefixed == DEFAULT &&  startPoint != p1) {

			if (startPoint.y == p1.y) // 가로로 고정되어서 그려지는 경우
				pDoc->ls.wherefixed = GARO;

			else if (startPoint.x == p1.x) // 세로로 고정되어서 그려지는 경우
				pDoc->ls.wherefixed = SERO;
		}

		//선을 저장하지는 않고 움진인 위치로 그리기만 함.
		if (oldpoint != p1) {
			Invalidate(0);
		}
		drawingline(startPoint, p1, pDoc->ls.wherefixed);

		//고정된 것을 초기상태로 돌려줘야 할 때 (초기상태)로 돌려줌.
		if (pDoc->ls.wherefixed == GARO && startPoint.x == p1.x || startPoint == p1) 
			pDoc->ls.wherefixed = DEFAULT;

		else if (pDoc->ls.wherefixed == SERO && startPoint.y == p1.y || startPoint == p1)
			pDoc->ls.wherefixed = DEFAULT;
	}

	if (pDoc->ls.pif[pointofpif.x][pointofpif.y].gatein == TRUE || pDoc->ls.pif[pointofpif.x][pointofpif.y].gateout == TRUE) {
			line = 1;
			pDC->SelectObject(&white3pen);
			pDC->Ellipse(eloldrect);
			pDC->SelectObject(&gree3npen);
			pDC->Ellipse(elrect);
			Invalidate(0);
	}
	else {
		if (line == 1) {
			line = 0;
			pDC->SelectObject(&white3pen);
			pDC->Ellipse(eloldrect);
			Invalidate(0);
		}
	}

	if (pDoc->ls.pif[pointofpif.x][pointofpif.y].serializegate == input || pDoc->ls.pif[pointofpif.x][pointofpif.y].serializegate == output || pDoc->ls.pif[pointofpif.x][pointofpif.y].serializegate == lsclock) {
		inout = 1;
		pDC->SelectObject(&white3pen);
		pDC->Rectangle(elinoutoldrect);
		pDC->SelectObject(&gree3npen);
		pDC->Rectangle(elinoutrect);
		Invalidate(0);
	}
	else {
		if (inout == 1) {
			inout = 0;
			pDC->SelectObject(&white3pen);
			pDC->Rectangle(elinoutoldrect);
			Invalidate(0);
		}
	}

	if (   pDoc->ls.pif[pointofpif.x][pointofpif.y].serializegate == and || pDoc->ls.pif[pointofpif.x][pointofpif.y].serializegate == or
		|| pDoc->ls.pif[pointofpif.x][pointofpif.y].serializegate == xor || pDoc->ls.pif[pointofpif.x][pointofpif.y].serializegate == not
		|| pDoc->ls.pif[pointofpif.x][pointofpif.y].serializegate == nand || pDoc->ls.pif[pointofpif.x][pointofpif.y].serializegate == nor) {
		gate = 1;
		pDC->SelectObject(&white3pen);
		pDC->Rectangle(elgateoldrect);
		pDC->SelectObject(&gree3npen);
		pDC->Rectangle(elgaterect);
		Invalidate(0);
	}
	else {
		if (gate == 1) {
			gate = 0;
			pDC->SelectObject(&white3pen);
			pDC->Rectangle(elgateoldrect);
			Invalidate(0);
		}
	}

	if (pDoc->ls.pif[pointofpif.x][pointofpif.y].serializegate == dff || pDoc->ls.pif[pointofpif.x][pointofpif.y].serializegate == jkff 
		|| pDoc->ls.pif[pointofpif.x][pointofpif.y].serializegate == tff || pDoc->ls.pif[pointofpif.x][pointofpif.y].serializegate == seg7
		|| pDoc->ls.pif[pointofpif.x][pointofpif.y].serializegate == lib || pDoc->ls.pif[pointofpif.x][pointofpif.y].serializegate == dcd) {
		ff = 1;
		pDC->SelectObject(&white3pen);
		pDC->Rectangle(elffoldrect);
		pDC->SelectObject(&gree3npen);
		pDC->Rectangle(elffrect);
		Invalidate(0);
	}
	else {
		if (ff == 1) {
			ff = 0;
			pDC->SelectObject(&white3pen);
			pDC->Rectangle(elffoldrect);
			Invalidate(0);
		}
	}


	ReleaseDC(pDC);
	oldpoint = p1;
	CView::OnMouseMove(nFlags, point);
}


void CPLS2View::drawingline(CPoint start, CPoint end, WhereFixed wherefixed) {
	CPLS2Doc* pDoc = GetDocument();

	CDC* pDC = GetDC();

	CPen blackpen(PS_SOLID, 1, RGB(0, 0, 0)); // 검정펜
	CPen whitepen(PS_SOLID, 1, RGB(255, 255, 255)); //흰펜

	pDC->SelectObject(whitepen);

	if (old_wherefixed == GARO)
		if (old_start.y == old_end.y) { // 1줄만 그리는경우.
			pDC->MoveTo(old_start);
			pDC->LineTo(old_end);
		}

		else {//두줄을 그려줘야 하는 경우.
			pDC->MoveTo(old_start);
			pDC->LineTo(old_end.x, old_start.y);

			pDC->MoveTo(old_end.x, old_start.y);
			pDC->LineTo(old_end);
		}
	else if (old_wherefixed == SERO) {
		if (old_start.x == old_end.x) { // 1줄만 그리는경우.
			pDC->MoveTo(old_start);
			pDC->LineTo(old_end);
		}
		else {//두줄을 그려줘야 하는 경우.
			pDC->MoveTo(old_start);
			pDC->LineTo(old_start.x, old_end.y);

			pDC->MoveTo(old_start.x, old_end.y);
			pDC->LineTo(old_end);
		}
	}

	pDC->SelectObject(blackpen);

	if (wherefixed == GARO)
		if (start.y == end.y) { // 1줄만 그리는경우.
			pDC->MoveTo(start);
			pDC->LineTo(end);
		}

		else {//두줄을 그려줘야 하는 경우.
			pDC->MoveTo(start);
			pDC->LineTo(end.x, start.y);

			pDC->MoveTo(end.x, start.y);
			pDC->LineTo(end);
		}
	else if (wherefixed == SERO){
		if (start.x == end.x) { // 1줄만 그리는경우.
			pDC->MoveTo(start);
			pDC->LineTo(end);
		}
		else {//두줄을 그려줘야 하는 경우.
			pDC->MoveTo(start);
			pDC->LineTo(start.x, end.y);

			pDC->MoveTo(start.x, end.y);
			pDC->LineTo(end);
		}
	}

	old_start = start;
	old_end = end;
	old_wherefixed = wherefixed;
}


void CPLS2View::Create_Input_BCLK()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CPLS2Doc* pDoc = GetDocument();
	pDoc->ls.whatgate = input; //  create를 LSINPUT(0)으로 만들어 input단자를 만들겠다고 알림.
}


void CPLS2View::Create_Output_BCLK()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CPLS2Doc* pDoc = GetDocument();
	pDoc->ls.whatgate = output; //  create를 LSOUTPUT(1)으로 만들어 output단자를 만들겠다고 알림.
}


void CPLS2View::Create_AndGate_BCLK()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CPLS2Doc* pDoc = GetDocument();
	pDoc->ls.whatgate = and; //  create를 LSOUTPUT(1)으로 만들어 output단자를 만들겠다고 알림.
}


void CPLS2View::Create_XorGate_BCLK()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CPLS2Doc* pDoc = GetDocument();
	pDoc->ls.whatgate = xor;
}


void CPLS2View::Create_NorGate_BCLK()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CPLS2Doc* pDoc = GetDocument();
	pDoc->ls.whatgate = nor;
}


void CPLS2View::Create_NAndGate_BCLK()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CPLS2Doc* pDoc = GetDocument();
	pDoc->ls.whatgate = nand;
}


void CPLS2View::Create_OrGate_BCLK()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CPLS2Doc* pDoc = GetDocument();
	pDoc->ls.whatgate = or;
}


void CPLS2View::Create_NotGate_BCLK()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CPLS2Doc* pDoc = GetDocument();
	pDoc->ls.whatgate = not;
}


void CPLS2View::Create_TFF_BCLK()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CPLS2Doc* pDoc = GetDocument();
	pDoc->ls.whatgate = tff;
}


void CPLS2View::Create_Clock_BCLK()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CPLS2Doc* pDoc = GetDocument();
	pDoc->ls.whatgate = lsclock;
}


int CPLS2View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	return 0;
}


void CPLS2View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CPLS2Doc* pDoc = GetDocument();
	//for (int i = 0; i < pDoc->ls.count_clock; i++) {
	//pDoc->ls.calculate_tff(&pDoc->ls.tff[nIDEvent]);
	switch(nIDEvent) {
	case 999:
		pDoc->ls.run(repeat, se, &pDoc->library);
		break;
	}
	if (pDoc->ls.clock[nIDEvent].value == 0) {
		pDoc->ls.clock[nIDEvent].value = 1;
		Invalidate(1);
	}
	else {
		pDoc->ls.clock[nIDEvent].value = 0;
		Invalidate(1);
	}
		
		//pDoc->ls.calculate_tff(&pDoc->ls.tff[nIDEvent]);
	//}
	CView::OnTimer(nIDEvent);
}


void CPLS2View::OnDestroy()
{
	CView::OnDestroy();
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CPLS2View::Create_DFF_BCLK()
{
	CPLS2Doc* pDoc = GetDocument();
	pDoc->ls.whatgate = dff;
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CPLS2View::Create_JKFF_BCLK()
{
	CPLS2Doc* pDoc = GetDocument();
	pDoc->ls.whatgate = jkff;
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CPLS2View::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	CPLS2Doc* pDoc = GetDocument();
	CPoint p1 = DividedByTwenty(point);
	switch(pDoc->ls.pif[p1.x/20][p1.y/20].gate)
	{
	case input:
		if (pDoc->ls.in[pDoc->ls.pif[p1.x / 20][p1.y / 20].input].value == 1)
			pDoc->ls.in[pDoc->ls.pif[p1.x / 20][p1.y / 20].input].value = 0;
		else
			pDoc->ls.in[pDoc->ls.pif[p1.x / 20][p1.y / 20].input].value = 1;
		break;
	case output:
		pDoc->ls.calculate_output(&pDoc->ls.out[pDoc->ls.pif[p1.x / 20][p1.y / 20].output]);
		break;
	case and:
		pDoc->ls.calculate_and(&pDoc->ls.and[pDoc->ls.pif[p1.x / 20][p1.y / 20].and]);
		break;
	case nand:
		pDoc->ls.calculate_nand(&pDoc->ls.nand[pDoc->ls.pif[p1.x / 20][p1.y / 20].nand]);
		break;
	case xor:
		pDoc->ls.calculate_xor(&pDoc->ls.xor[pDoc->ls.pif[p1.x / 20][p1.y / 20].xor]);
		break;
	case nor:
		pDoc->ls.calculate_nor(&pDoc->ls.nor[pDoc->ls.pif[p1.x / 20][p1.y / 20].nor]);
		break;
	case or:
		pDoc->ls.calculate_or(&pDoc->ls.or[pDoc->ls.pif[p1.x / 20][p1.y / 20].or]);
		break;
	case not:
		pDoc->ls.calculate_not(&pDoc->ls.not[pDoc->ls.pif[p1.x / 20][p1.y / 20].not]);
		break;
	case tff:
		pDoc->ls.calculate_tff(&pDoc->ls.tff[pDoc->ls.pif[p1.x / 20][p1.y / 20].tff]);
		break;
	case seg7:
		pDoc->ls.calculate_seg7(&pDoc->ls.seg7[pDoc->ls.pif[p1.x / 20][p1.y / 20].seg7]);
		break;
	case dff:
		pDoc->ls.calculate_dff(&pDoc->ls.dff[pDoc->ls.pif[p1.x / 20][p1.y / 20].dff]);
		break;
	case jkff:
		pDoc->ls.calculate_jkff(&pDoc->ls.jkff[pDoc->ls.pif[p1.x / 20][p1.y / 20].jkff]);
		break;
	case lsclock:
		SetTimer(pDoc->ls.pif[p1.x / 20][p1.y / 20].clock, hz / (pDoc->ls.pif[p1.x / 20][p1.y / 20].clock + 1), NULL);
		break;
	case lib:
		pDoc->ls.calculate_lib(&pDoc->ls.lib[pDoc->ls.pif[p1.x / 20][p1.y / 20].lib], &pDoc->library);
		break;
	case dcd:
		pDoc->ls.calculate_dcd(&pDoc->ls.dcd[pDoc->ls.pif[p1.x / 20][p1.y / 20].dcd]);
		break;
	}
	Invalidate();
	CView::OnLButtonDblClk(nFlags, point);
}


void CPLS2View::OnSerialize()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	repeat = 0;
	se[0] = 0;
	CPLS2Doc* pDoc = GetDocument();
	pDoc->ls.count_serial = -1;
	for (int i = 0; i <= pDoc->ls.count_output; i++) {
		pDoc->ls.serialize_gate(pDoc->ls.out[i].input.x, pDoc->ls.out[i].input.y);
		repeat++;
		se[repeat] = pDoc->ls.count_serial;
	}
	for (int i = 0; i <= pDoc->ls.count_seg7; i++) {
		pDoc->ls.serialize_gate(pDoc->ls.seg7[i].input[0].x, pDoc->ls.seg7[i].input[0].y);
		repeat++;
		se[repeat] = pDoc->ls.count_serial;
	}
}


void CPLS2View::Onrun()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CPLS2Doc* pDoc = GetDocument();
	pDoc->ls.run(repeat, se, &pDoc->library);
	Invalidate();
}


void CPLS2View::Create_7Segment_BCLK()
{
	CPLS2Doc* pDoc = GetDocument();
	pDoc->ls.whatgate = seg7;
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

//주기설정 완성
void CPLS2View::On1second()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	hz = 1000;

}


void CPLS2View::Onpoint5second()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	hz = 500;
}


void CPLS2View::Onpoint25second()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	hz = 200;
}


void CPLS2View::Onpoint1second()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	hz = 100;
}


void CPLS2View::Onclockstop()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CPLS2Doc* pDoc = GetDocument();
	for (int i = 0; i <= pDoc->ls.count_clock; i++) {
		KillTimer(i);
	}
}


void CPLS2View::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CPLS2Doc* pDoc = GetDocument();
	CPoint p1 = DividedByTwenty(rbuttonClickedPoint);
	CMenu menu, menu2;
	menu.LoadMenuW(IDR_MENU1);
	menu2.LoadMenuW(IDR_MENU2);
	CMenu* pMenu = menu.GetSubMenu(0);
	CMenu* pMenu2 = menu2.GetSubMenu(0);
	pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, AfxGetMainWnd());
}


void CPLS2View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	rbuttonClickedPoint = point; // 그냥 눌린 위치를 파악하기 위해서.
	CView::OnRButtonDown(nFlags, point);
}


void CPLS2View::On_TurnToRight()
{
	CPLS2Doc* pDoc = GetDocument();
	CPoint p1 = DividedByTwenty(rbuttonClickedPoint);
	pDoc->ls.pif[p1.x / 20][p1.y / 20].direct = RIGHT;
	switch (pDoc->ls.pif[p1.x / 20][p1.y / 20].serializegate)
	{
	case input:
		pDoc->ls.in[pDoc->ls.pif[p1.x / 20][p1.y / 20].input].direct = RIGHT;
		pDoc->ls.rotate_input(&pDoc->ls.in[pDoc->ls.pif[p1.x / 20][p1.y / 20].input], RIGHT);
		break;
	case output:
		pDoc->ls.out[pDoc->ls.pif[p1.x / 20][p1.y / 20].output].direct = RIGHT;
		pDoc->ls.rotate_output(&pDoc->ls.out[pDoc->ls.pif[p1.x / 20][p1.y / 20].output], RIGHT);
		break;
	case and:
		pDoc->ls.and[pDoc->ls.pif[p1.x / 20][p1.y / 20].and].direct = RIGHT;
		pDoc->ls.rotate_and(&pDoc->ls.and[pDoc->ls.pif[p1.x / 20][p1.y / 20].and], RIGHT);
		break;
	case or :
		pDoc->ls.or [pDoc->ls.pif[p1.x / 20][p1.y / 20]. or ].direct = RIGHT;
		pDoc->ls.rotate_or(&pDoc->ls.or[pDoc->ls.pif[p1.x / 20][p1.y / 20].or], RIGHT);
		break;
	case not:
		pDoc->ls.not[pDoc->ls.pif[p1.x / 20][p1.y / 20].not].direct = RIGHT;
		pDoc->ls.rotate_not(&pDoc->ls.not[pDoc->ls.pif[p1.x / 20][p1.y / 20].not], RIGHT);
		break;
	case nand:
		pDoc->ls.nand[pDoc->ls.pif[p1.x / 20][p1.y / 20].nand].direct = RIGHT;
		pDoc->ls.rotate_nand(&pDoc->ls.nand[pDoc->ls.pif[p1.x / 20][p1.y / 20].nand], RIGHT);
		break;
	case nor:
		pDoc->ls.nor[pDoc->ls.pif[p1.x / 20][p1.y / 20].nor].direct = RIGHT;
		pDoc->ls.rotate_nor(&pDoc->ls.nor[pDoc->ls.pif[p1.x / 20][p1.y / 20].nor], RIGHT);
		break;
	case xor:
		pDoc->ls.xor[pDoc->ls.pif[p1.x / 20][p1.y / 20].xor].direct = RIGHT;
		pDoc->ls.rotate_xor(&pDoc->ls.xor[pDoc->ls.pif[p1.x / 20][p1.y / 20].xor], RIGHT);
		break;
	case dff:
		pDoc->ls.dff[pDoc->ls.pif[p1.x / 20][p1.y / 20].dff].direct = RIGHT;
		pDoc->ls.rotate_dff(&pDoc->ls.dff[pDoc->ls.pif[p1.x / 20][p1.y / 20].dff], RIGHT);
		break;
	case jkff:
		pDoc->ls.jkff[pDoc->ls.pif[p1.x / 20][p1.y / 20].jkff].direct = RIGHT;
		pDoc->ls.rotate_jkff(&pDoc->ls.jkff[pDoc->ls.pif[p1.x / 20][p1.y / 20].jkff], RIGHT);
		break;
	case tff:
		pDoc->ls.tff[pDoc->ls.pif[p1.x / 20][p1.y / 20].tff].direct = RIGHT;
		pDoc->ls.rotate_tff(&pDoc->ls.tff[pDoc->ls.pif[p1.x / 20][p1.y / 20].tff], RIGHT);
		break;
	case lsclock:
		pDoc->ls.clock[pDoc->ls.pif[p1.x / 20][p1.y / 20].clock].direct = RIGHT;
		pDoc->ls.rotate_clock(&pDoc->ls.clock[pDoc->ls.pif[p1.x / 20][p1.y / 20].clock], RIGHT);
		break;
	case seg7:
		pDoc->ls.seg7[pDoc->ls.pif[p1.x / 20][p1.y / 20].seg7].direct = RIGHT;
		pDoc->ls.rotate_seg7(&pDoc->ls.seg7[pDoc->ls.pif[p1.x / 20][p1.y / 20].seg7], RIGHT);
		break;
	case lib:
		pDoc->ls.lib[pDoc->ls.pif[p1.x / 20][p1.y / 20].lib].direct = RIGHT;
		pDoc->ls.rotate_lib(&pDoc->ls.lib[pDoc->ls.pif[p1.x / 20][p1.y / 20].lib], RIGHT);
		break;
	}
	int max = pDoc->ls.count_line;
	pDoc->ls.count_line = -1;
	for (int i = 0; i <= max; i++) {
		pDoc->ls.count_line++;
		pDoc->ls.create_line(pDoc->ls.line[i].firstPt, pDoc->ls.line[i].secondPt, i);
	}
	Invalidate();
}


void CPLS2View::On_TurnToLeft()
{
	CPLS2Doc* pDoc = GetDocument();
	CPoint p1 = DividedByTwenty(rbuttonClickedPoint);
	pDoc->ls.pif[p1.x / 20][p1.y / 20].direct = LEFT;
	switch (pDoc->ls.pif[p1.x / 20][p1.y / 20].serializegate)
	{
	case input:
		pDoc->ls.in[pDoc->ls.pif[p1.x / 20][p1.y / 20].input].direct = LEFT;
		pDoc->ls.rotate_input(&pDoc->ls.in[pDoc->ls.pif[p1.x / 20][p1.y / 20].input], LEFT);
		break;
	case output:
		pDoc->ls.out[pDoc->ls.pif[p1.x / 20][p1.y / 20].output].direct = LEFT;
		pDoc->ls.rotate_output(&pDoc->ls.out[pDoc->ls.pif[p1.x / 20][p1.y / 20].output], LEFT);
		break;
	case and:
		pDoc->ls.and[pDoc->ls.pif[p1.x / 20][p1.y / 20].and].direct = LEFT;
		pDoc->ls.rotate_and(&pDoc->ls.and[pDoc->ls.pif[p1.x / 20][p1.y / 20].and], LEFT);
		break;
	case or:
		pDoc->ls. or [pDoc->ls.pif[p1.x / 20][p1.y / 20]. or ].direct = LEFT;
		pDoc->ls.rotate_or(&pDoc->ls. or [pDoc->ls.pif[p1.x / 20][p1.y / 20]. or ], LEFT);
		break;
	case not:
		pDoc->ls.not[pDoc->ls.pif[p1.x / 20][p1.y / 20].not].direct = LEFT;
		pDoc->ls.rotate_not(&pDoc->ls.not[pDoc->ls.pif[p1.x / 20][p1.y / 20].not], LEFT);
		break;
	case nand:
		pDoc->ls.nand[pDoc->ls.pif[p1.x / 20][p1.y / 20].nand].direct = LEFT;
		pDoc->ls.rotate_nand(&pDoc->ls.nand[pDoc->ls.pif[p1.x / 20][p1.y / 20].nand], LEFT);
		break;
	case nor:
		pDoc->ls.nor[pDoc->ls.pif[p1.x / 20][p1.y / 20].nor].direct = LEFT;
		pDoc->ls.rotate_nor(&pDoc->ls.nor[pDoc->ls.pif[p1.x / 20][p1.y / 20].nor], LEFT);
		break;
	case xor:
		pDoc->ls.xor[pDoc->ls.pif[p1.x / 20][p1.y / 20].xor].direct = LEFT;
		pDoc->ls.rotate_xor(&pDoc->ls.xor[pDoc->ls.pif[p1.x / 20][p1.y / 20].xor], LEFT);
		break;
	case dff:
		pDoc->ls.dff[pDoc->ls.pif[p1.x / 20][p1.y / 20].dff].direct = LEFT;
		pDoc->ls.rotate_dff(&pDoc->ls.dff[pDoc->ls.pif[p1.x / 20][p1.y / 20].dff], LEFT);
		break;
	case jkff:
		pDoc->ls.jkff[pDoc->ls.pif[p1.x / 20][p1.y / 20].jkff].direct = LEFT;
		pDoc->ls.rotate_jkff(&pDoc->ls.jkff[pDoc->ls.pif[p1.x / 20][p1.y / 20].jkff], LEFT);
		break;
	case tff:
		pDoc->ls.tff[pDoc->ls.pif[p1.x / 20][p1.y / 20].tff].direct = LEFT;
		pDoc->ls.rotate_tff(&pDoc->ls.tff[pDoc->ls.pif[p1.x / 20][p1.y / 20].tff], LEFT);
		break;
	case lsclock:
		pDoc->ls.clock[pDoc->ls.pif[p1.x / 20][p1.y / 20].clock].direct = LEFT;
		pDoc->ls.rotate_clock(&pDoc->ls.clock[pDoc->ls.pif[p1.x / 20][p1.y / 20].clock], LEFT);
		break;
	case seg7:
		pDoc->ls.seg7[pDoc->ls.pif[p1.x / 20][p1.y / 20].seg7].direct = LEFT;
		pDoc->ls.rotate_seg7(&pDoc->ls.seg7[pDoc->ls.pif[p1.x / 20][p1.y / 20].seg7], LEFT);
		break;
	case lib:
		pDoc->ls.lib[pDoc->ls.pif[p1.x / 20][p1.y / 20].lib].direct = LEFT;
		pDoc->ls.rotate_lib(&pDoc->ls.lib[pDoc->ls.pif[p1.x / 20][p1.y / 20].lib], LEFT);
		break;
	}
	int max = pDoc->ls.count_line;
	pDoc->ls.count_line = -1;
	for (int i = 0; i <= max; i++) {
		pDoc->ls.count_line++;
		pDoc->ls.create_line(pDoc->ls.line[i].firstPt, pDoc->ls.line[i].secondPt, i);
	}
	Invalidate();
}


void CPLS2View::On_TurnToTop()
{
	CPLS2Doc* pDoc = GetDocument();
	CPoint p1 = DividedByTwenty(rbuttonClickedPoint);
	pDoc->ls.pif[p1.x / 20][p1.y / 20].direct = TOP;
	switch (pDoc->ls.pif[p1.x / 20][p1.y / 20].serializegate)
	{
	case input:
		pDoc->ls.in[pDoc->ls.pif[p1.x / 20][p1.y / 20].input].direct = TOP;
		pDoc->ls.rotate_input(&pDoc->ls.in[pDoc->ls.pif[p1.x / 20][p1.y / 20].input], TOP);
		break;
	case output:
		pDoc->ls.out[pDoc->ls.pif[p1.x / 20][p1.y / 20].output].direct = TOP;
		pDoc->ls.rotate_output(&pDoc->ls.out[pDoc->ls.pif[p1.x / 20][p1.y / 20].output], TOP);
		break;
	case and:
		pDoc->ls.and[pDoc->ls.pif[p1.x / 20][p1.y / 20].and].direct = TOP;
		pDoc->ls.rotate_and(&pDoc->ls.and[pDoc->ls.pif[p1.x / 20][p1.y / 20].and], TOP);
		break;
	case or:
		pDoc->ls. or [pDoc->ls.pif[p1.x / 20][p1.y / 20]. or ].direct = TOP;
		pDoc->ls.rotate_or(&pDoc->ls. or [pDoc->ls.pif[p1.x / 20][p1.y / 20]. or ], TOP);
		break;
	case not:
		pDoc->ls.not[pDoc->ls.pif[p1.x / 20][p1.y / 20].not].direct = TOP;
		pDoc->ls.rotate_not(&pDoc->ls.not[pDoc->ls.pif[p1.x / 20][p1.y / 20].not], TOP);
		break;
	case nand:
		pDoc->ls.nand[pDoc->ls.pif[p1.x / 20][p1.y / 20].nand].direct = TOP;
		pDoc->ls.rotate_nand(&pDoc->ls.nand[pDoc->ls.pif[p1.x / 20][p1.y / 20].nand], TOP);
		break;
	case nor:
		pDoc->ls.nor[pDoc->ls.pif[p1.x / 20][p1.y / 20].nor].direct = TOP;
		pDoc->ls.rotate_nor(&pDoc->ls.nor[pDoc->ls.pif[p1.x / 20][p1.y / 20].nor], TOP);
		break;
	case xor:
		pDoc->ls.xor[pDoc->ls.pif[p1.x / 20][p1.y / 20].xor].direct = TOP;
		pDoc->ls.rotate_xor(&pDoc->ls.xor[pDoc->ls.pif[p1.x / 20][p1.y / 20].xor], TOP);
		break;
	case dff:
		pDoc->ls.dff[pDoc->ls.pif[p1.x / 20][p1.y / 20].dff].direct = TOP;
		pDoc->ls.rotate_dff(&pDoc->ls.dff[pDoc->ls.pif[p1.x / 20][p1.y / 20].dff], TOP);
		break;
	case jkff:
		pDoc->ls.jkff[pDoc->ls.pif[p1.x / 20][p1.y / 20].jkff].direct = TOP;
		pDoc->ls.rotate_jkff(&pDoc->ls.jkff[pDoc->ls.pif[p1.x / 20][p1.y / 20].jkff], TOP);
		break;
	case tff:
		pDoc->ls.tff[pDoc->ls.pif[p1.x / 20][p1.y / 20].tff].direct = TOP;
		pDoc->ls.rotate_tff(&pDoc->ls.tff[pDoc->ls.pif[p1.x / 20][p1.y / 20].tff], TOP);
		break;
	case lsclock:
		pDoc->ls.clock[pDoc->ls.pif[p1.x / 20][p1.y / 20].clock].direct = TOP;
		pDoc->ls.rotate_clock(&pDoc->ls.clock[pDoc->ls.pif[p1.x / 20][p1.y / 20].clock], TOP);
		break;
	case seg7:
		pDoc->ls.seg7[pDoc->ls.pif[p1.x / 20][p1.y / 20].seg7].direct = TOP;
		pDoc->ls.rotate_seg7(&pDoc->ls.seg7[pDoc->ls.pif[p1.x / 20][p1.y / 20].seg7], TOP);
		break;
	case lib:
		pDoc->ls.lib[pDoc->ls.pif[p1.x / 20][p1.y / 20].lib].direct = TOP;
		pDoc->ls.rotate_lib(&pDoc->ls.lib[pDoc->ls.pif[p1.x / 20][p1.y / 20].lib], TOP);
		break;
	}
	int max = pDoc->ls.count_line;
	pDoc->ls.count_line = -1;
	for (int i = 0; i <= max; i++) {
		pDoc->ls.count_line++;
		pDoc->ls.create_line(pDoc->ls.line[i].firstPt, pDoc->ls.line[i].secondPt, i);
	}
	Invalidate();
}


void CPLS2View::On_TurnToBottom()
{
	CPLS2Doc* pDoc = GetDocument();
	CPoint p1 = DividedByTwenty(rbuttonClickedPoint);
	pDoc->ls.pif[p1.x / 20][p1.y / 20].direct = BOTTOM;
	switch (pDoc->ls.pif[p1.x / 20][p1.y / 20].serializegate)
	{
	case input:
		pDoc->ls.in[pDoc->ls.pif[p1.x / 20][p1.y / 20].input].direct = BOTTOM;
		pDoc->ls.rotate_input(&pDoc->ls.in[pDoc->ls.pif[p1.x / 20][p1.y / 20].input], BOTTOM);
		break;
	case output:
		pDoc->ls.out[pDoc->ls.pif[p1.x / 20][p1.y / 20].output].direct = BOTTOM;
		pDoc->ls.rotate_output(&pDoc->ls.out[pDoc->ls.pif[p1.x / 20][p1.y / 20].output], BOTTOM);
		break;
	case and:
		pDoc->ls.and[pDoc->ls.pif[p1.x / 20][p1.y / 20].and].direct = BOTTOM;
		pDoc->ls.rotate_and(&pDoc->ls.and[pDoc->ls.pif[p1.x / 20][p1.y / 20].and], BOTTOM);
		break;
	case or :
		pDoc->ls. or [pDoc->ls.pif[p1.x / 20][p1.y / 20]. or ].direct = BOTTOM;
		pDoc->ls.rotate_or(&pDoc->ls. or [pDoc->ls.pif[p1.x / 20][p1.y / 20]. or ], BOTTOM);
		break;
	case not:
		pDoc->ls.not[pDoc->ls.pif[p1.x / 20][p1.y / 20].not].direct = BOTTOM;
		pDoc->ls.rotate_not(&pDoc->ls.not[pDoc->ls.pif[p1.x / 20][p1.y / 20].not], BOTTOM);
		break;
	case nand:
		pDoc->ls.nand[pDoc->ls.pif[p1.x / 20][p1.y / 20].nand].direct = BOTTOM;
		pDoc->ls.rotate_nand(&pDoc->ls.nand[pDoc->ls.pif[p1.x / 20][p1.y / 20].nand], BOTTOM);
		break;
	case nor:
		pDoc->ls.nor[pDoc->ls.pif[p1.x / 20][p1.y / 20].nor].direct = BOTTOM;
		pDoc->ls.rotate_nor(&pDoc->ls.nor[pDoc->ls.pif[p1.x / 20][p1.y / 20].nor], BOTTOM);
		break;
	case xor:
		pDoc->ls.xor[pDoc->ls.pif[p1.x / 20][p1.y / 20].xor].direct = BOTTOM;
		pDoc->ls.rotate_xor(&pDoc->ls.xor[pDoc->ls.pif[p1.x / 20][p1.y / 20].xor], BOTTOM);
		break;
	case dff:
		pDoc->ls.dff[pDoc->ls.pif[p1.x / 20][p1.y / 20].dff].direct = BOTTOM;
		pDoc->ls.rotate_dff(&pDoc->ls.dff[pDoc->ls.pif[p1.x / 20][p1.y / 20].dff], BOTTOM);
		break;
	case jkff:
		pDoc->ls.jkff[pDoc->ls.pif[p1.x / 20][p1.y / 20].jkff].direct = BOTTOM;
		pDoc->ls.rotate_jkff(&pDoc->ls.jkff[pDoc->ls.pif[p1.x / 20][p1.y / 20].jkff], BOTTOM);
		break;
	case tff:
		pDoc->ls.tff[pDoc->ls.pif[p1.x / 20][p1.y / 20].tff].direct = BOTTOM;
		pDoc->ls.rotate_tff(&pDoc->ls.tff[pDoc->ls.pif[p1.x / 20][p1.y / 20].tff], BOTTOM);
		break;
	case lsclock:
		pDoc->ls.clock[pDoc->ls.pif[p1.x / 20][p1.y / 20].clock].direct = BOTTOM;
		pDoc->ls.rotate_clock(&pDoc->ls.clock[pDoc->ls.pif[p1.x / 20][p1.y / 20].clock], BOTTOM);
		break;
	case seg7:
		pDoc->ls.seg7[pDoc->ls.pif[p1.x / 20][p1.y / 20].seg7].direct = BOTTOM;
		pDoc->ls.rotate_seg7(&pDoc->ls.seg7[pDoc->ls.pif[p1.x / 20][p1.y / 20].seg7], BOTTOM);
		break;
	case lib:
		pDoc->ls.lib[pDoc->ls.pif[p1.x / 20][p1.y / 20].lib].direct = BOTTOM;
		pDoc->ls.rotate_lib(&pDoc->ls.lib[pDoc->ls.pif[p1.x / 20][p1.y / 20].lib], BOTTOM);
		break;
	}
	int max = pDoc->ls.count_line;
	pDoc->ls.count_line = -1;
	for (int i = 0; i <= max; i++) {
		pDoc->ls.count_line++;
		pDoc->ls.create_line(pDoc->ls.line[i].firstPt, pDoc->ls.line[i].secondPt, i);
	}
	Invalidate();
}


void CPLS2View::Onlibready()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CPLS2Doc* pDoc = GetDocument();
	if (pDoc->ls.readylibaray == 0)
		pDoc->ls.readylibaray = 1;
	else
		pDoc->ls.readylibaray = 0;
}


void CPLS2View::Oncreatelib()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CPLS2Doc* pDoc = GetDocument();
	pDoc->ls.whatgate = lib;
}


void CPLS2View::Ondecoder()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CPLS2Doc* pDoc = GetDocument();
	pDoc->ls.whatgate = dcd;
}


void CPLS2View::Onautorun()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	SetTimer(999, 90, NULL);
}


void CPLS2View::Onrunstop()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	KillTimer(999);
}


void CPLS2View::On32825() 
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CPLS2Doc* pDoc = GetDocument();
	for (int i = 0; i < INDEX; i++) {
		pDoc->ls.dff[i].trigger = TRUE;
		pDoc->ls.jkff[i].trigger = TRUE;
		pDoc->ls.tff[i].trigger = TRUE;
	}
}


void CPLS2View::On32826() 
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CPLS2Doc* pDoc = GetDocument();
	for (int i = 0; i < INDEX; i++) {
		pDoc->ls.dff[i].trigger = FALSE;
		pDoc->ls.jkff[i].trigger = FALSE;
		pDoc->ls.tff[i].trigger = FALSE;
	}
}


void CPLS2View::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CPLS2Doc* pDoc = GetDocument();
	CPoint p1 = DividedByTwenty(point);
	CPoint pointofpif{ p1.x / 20, p1.y / 20 };
	CClientDC dc(this);
	CString str;
	if (pDoc->ls.pif[pointofpif.x][pointofpif.y].value != NULL) {
		str.Format(_T("%d"), *(pDoc->ls.pif[pointofpif.x][pointofpif.y].value));
		MessageBox(str, str, MB_OK);
	}
	else {
		str = _T("NULL");
		MessageBox(str, str, MB_OK);
	}
	CView::OnMButtonDown(nFlags, point);
}


void CPLS2View::OnTextlabel()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CPLS2Doc* pDoc = GetDocument();
	CPoint p1 = DividedByTwenty(rbuttonClickedPoint);
	TextLabel dlg;
	dlg.m_str = m_str;

	int result = dlg.DoModal();
	if (result == IDOK)
	{
		m_str = dlg.m_str; // edit 편집장에서 입력한 값을 뷰 객체 변수로 전달
		switch (pDoc->ls.pif[p1.x / 20][p1.y / 20].serializegate)
		{
		case input:
			pDoc->ls.in[pDoc->ls.pif[p1.x / 20][p1.y / 20].input].name = m_str;
			pDoc->ls.pif[p1.x / 20][p1.y / 20].name = m_str;
			break;
		case output:
			pDoc->ls.out[pDoc->ls.pif[p1.x / 20][p1.y / 20].output].name = m_str;
			pDoc->ls.pif[p1.x / 20][p1.y / 20].name = m_str;
			break;
		case and:
			pDoc->ls.and[pDoc->ls.pif[p1.x / 20][p1.y / 20].and].name = m_str;
			pDoc->ls.pif[p1.x / 20][p1.y / 20].name = m_str;
			break;
		case or:
			pDoc->ls.or[pDoc->ls.pif[p1.x / 20][p1.y / 20].or].name = m_str;
			pDoc->ls.pif[p1.x / 20][p1.y / 20].name = m_str;
			break;
		case not:
			pDoc->ls.not[pDoc->ls.pif[p1.x / 20][p1.y / 20].not].name = m_str;
			pDoc->ls.pif[p1.x / 20][p1.y / 20].name = m_str;
			break;
		case nand:
			pDoc->ls.nand[pDoc->ls.pif[p1.x / 20][p1.y / 20].nand].name = m_str;
			pDoc->ls.pif[p1.x / 20][p1.y / 20].name = m_str;
			break;
		case nor:
			pDoc->ls.nor[pDoc->ls.pif[p1.x / 20][p1.y / 20].nor].name = m_str;
			pDoc->ls.pif[p1.x / 20][p1.y / 20].name = m_str;
			break;
		case xor:
			pDoc->ls.xor[pDoc->ls.pif[p1.x / 20][p1.y / 20].xor].name = m_str;
			pDoc->ls.pif[p1.x / 20][p1.y / 20].name = m_str;
			break;
		case dff:
			pDoc->ls.dff[pDoc->ls.pif[p1.x / 20][p1.y / 20].dff].name = m_str;
			pDoc->ls.pif[p1.x / 20][p1.y / 20].name = m_str;
			break;
		case jkff:
			pDoc->ls.jkff[pDoc->ls.pif[p1.x / 20][p1.y / 20].jkff].name = m_str;
			pDoc->ls.pif[p1.x / 20][p1.y / 20].name = m_str;
			break;
		case tff:
			pDoc->ls.tff[pDoc->ls.pif[p1.x / 20][p1.y / 20].tff].name = m_str;
			pDoc->ls.pif[p1.x / 20][p1.y / 20].name = m_str;
			break;
		case lib:
			pDoc->ls.lib[pDoc->ls.pif[p1.x / 20][p1.y / 20].lib].name = m_str;
			pDoc->ls.pif[p1.x / 20][p1.y / 20].name = m_str;
			break;
		}
		Invalidate(1);
	}
}


void CPLS2View::Ondelete()
{
	
}


void CPLS2View::Ondel()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CPLS2Doc* pDoc = GetDocument();
	CPoint p1 = DividedByTwenty(rbuttonClickedPoint);
	
	pDoc->ls.lsdelete(p1 , 1);
	Invalidate(1);
}


void CPLS2View::OnCopy()
{
	CPLS2Doc* pDoc = GetDocument();
	CPoint p1 = DividedByTwenty(rbuttonClickedPoint);
	 
	switch (pDoc->ls.pif[p1.x / 20][p1.y / 20].gate)
	{
	case input:
		pDoc->ls.temp_logic.direct = pDoc->ls.in[pDoc->ls.pif[p1.x / 20][p1.y / 20].input].direct;
		pDoc->ls.temp_logic.name = pDoc->ls.in[pDoc->ls.pif[p1.x / 20][p1.y / 20].input].name;
		pDoc->ls.temp_logic.gate = input;
		break;
	case output:
		pDoc->ls.temp_logic.direct = pDoc->ls.out[pDoc->ls.pif[p1.x / 20][p1.y / 20].output].direct;
		pDoc->ls.temp_logic.name = pDoc->ls.out[pDoc->ls.pif[p1.x / 20][p1.y / 20].output].name;
		pDoc->ls.temp_logic.gate = output;
		break;
	case and:
		pDoc->ls.temp_logic.direct = pDoc->ls.and[pDoc->ls.pif[p1.x / 20][p1.y / 20].and].direct;
		pDoc->ls.temp_logic.name = pDoc->ls.and[pDoc->ls.pif[p1.x / 20][p1.y / 20].and].name;
		pDoc->ls.temp_logic.gate = and;
		break;
	case or:
		pDoc->ls.temp_logic.direct = pDoc->ls.or[pDoc->ls.pif[p1.x / 20][p1.y / 20].or].direct;
		pDoc->ls.temp_logic.name = pDoc->ls.or[pDoc->ls.pif[p1.x / 20][p1.y / 20].or].name;
		pDoc->ls.temp_logic.gate = or;
		break;
	case not:
		pDoc->ls.temp_logic.direct = pDoc->ls.not[pDoc->ls.pif[p1.x / 20][p1.y / 20].not].direct;
		pDoc->ls.temp_logic.name = pDoc->ls.not[pDoc->ls.pif[p1.x / 20][p1.y / 20].not].name;
		pDoc->ls.temp_logic.gate = not;
		break;
	case nand:
		pDoc->ls.temp_logic.direct = pDoc->ls.nand[pDoc->ls.pif[p1.x / 20][p1.y / 20].nand].direct;
		pDoc->ls.temp_logic.name = pDoc->ls.nand[pDoc->ls.pif[p1.x / 20][p1.y / 20].nand].name;
		pDoc->ls.temp_logic.gate = nand;
		break;
	case nor:
		pDoc->ls.temp_logic.direct = pDoc->ls.nor[pDoc->ls.pif[p1.x / 20][p1.y / 20].nor].direct;
		pDoc->ls.temp_logic.name = pDoc->ls.nor[pDoc->ls.pif[p1.x / 20][p1.y / 20].nor].name;
		pDoc->ls.temp_logic.gate = nor;
		break;
	case xor:
		pDoc->ls.temp_logic.direct = pDoc->ls.xor[pDoc->ls.pif[p1.x / 20][p1.y / 20].xor].direct;
		pDoc->ls.temp_logic.name = pDoc->ls.xor[pDoc->ls.pif[p1.x / 20][p1.y / 20].xor].name;
		pDoc->ls.temp_logic.gate = xor;
		break;
	case dff:
		pDoc->ls.temp_logic.direct = pDoc->ls.dff[pDoc->ls.pif[p1.x / 20][p1.y / 20].dff].direct;
		pDoc->ls.temp_logic.name = pDoc->ls.dff[pDoc->ls.pif[p1.x / 20][p1.y / 20].dff].name;
		pDoc->ls.temp_logic.gate = dff;
		break;
	case jkff:
		pDoc->ls.temp_logic.direct = pDoc->ls.jkff[pDoc->ls.pif[p1.x / 20][p1.y / 20].jkff].direct;
		pDoc->ls.temp_logic.name = pDoc->ls.jkff[pDoc->ls.pif[p1.x / 20][p1.y / 20].jkff].name;
		pDoc->ls.temp_logic.gate = jkff;
		break;
	case tff:
		pDoc->ls.temp_logic.direct = pDoc->ls.tff[pDoc->ls.pif[p1.x / 20][p1.y / 20].tff].direct;
		pDoc->ls.temp_logic.name = pDoc->ls.tff[pDoc->ls.pif[p1.x / 20][p1.y / 20].tff].name;
		pDoc->ls.temp_logic.gate = tff;
		break;
	case seg7:
		pDoc->ls.temp_logic.direct = pDoc->ls.seg7[pDoc->ls.pif[p1.x / 20][p1.y / 20].seg7].direct;
		pDoc->ls.temp_logic.name = pDoc->ls.seg7[pDoc->ls.pif[p1.x / 20][p1.y / 20].seg7].name;
		pDoc->ls.temp_logic.gate = seg7;
		break;
	case lib:
		pDoc->ls.temp_logic.direct = pDoc->ls.lib[pDoc->ls.pif[p1.x / 20][p1.y / 20].lib].direct;
		pDoc->ls.temp_logic.name = pDoc->ls.lib[pDoc->ls.pif[p1.x / 20][p1.y / 20].lib].name;
		pDoc->ls.temp_logic.gate = lib;
		break;
	case dcd:
		pDoc->ls.temp_logic.direct = pDoc->ls.dcd[pDoc->ls.pif[p1.x / 20][p1.y / 20].dcd].direct;
		pDoc->ls.temp_logic.name = pDoc->ls.dcd[pDoc->ls.pif[p1.x / 20][p1.y / 20].dcd].name;
		pDoc->ls.temp_logic.gate = dcd;
		break;
	case lsclock:
		pDoc->ls.temp_logic.direct = pDoc->ls.clock[pDoc->ls.pif[p1.x / 20][p1.y / 20].clock].direct;
		pDoc->ls.temp_logic.name = pDoc->ls.clock[pDoc->ls.pif[p1.x / 20][p1.y / 20].clock].name;
		pDoc->ls.temp_logic.gate = lsclock;
		break;
	}
}


void CPLS2View::OnPaste()
{
	CPLS2Doc* pDoc = GetDocument();
	CPoint p1 = DividedByTwenty(rbuttonClickedPoint);
	pDoc->ls.pif[p1.x / 20][p1.y / 20].gate = pDoc->ls.temp_logic.gate;
	CPoint pointofpif{ p1.x / 20, p1.y / 20 };
	
	switch (pDoc->ls.pif[p1.x / 20][p1.y / 20].gate)
	{
		case input:
			pDoc->ls.count_input++;
			pDoc->ls.create_input(&(pDoc->ls.in[pDoc->ls.count_input]), pointofpif);
			pDoc->ls.rotate_input(&pDoc->ls.in[pDoc->ls.count_input], pDoc->ls.temp_logic.direct);
			pDoc->ls.pif[p1.x / 20][p1.y / 20].input = pDoc->ls.count_input;
			pDoc->ls.in[pDoc->ls.count_input].name = pDoc->ls.temp_logic.name;
			pDoc->ls.in[pDoc->ls.count_input].direct = pDoc->ls.temp_logic.direct;
			pDoc->ls.savetomem(pointofpif, ::input, pDoc->ls.pif[p1.x / 20][p1.y / 20].input, ::paste, pDoc->ls.pif[p1.x / 20][p1.y / 20].name, (Direct)pDoc->ls.pif[p1.x / 20][p1.y / 20].direct);
			pDoc->ls.whatgate = nothing; // 마우스를 누르는 순간 그 위치에 그려지게 되므로 초기값으로 돌려줌.
			Invalidate(1);
			break;
		case output:
			pDoc->ls.count_output++;
			pDoc->ls.create_output(&pDoc->ls.out[pDoc->ls.count_output], pointofpif);
			pDoc->ls.out[pDoc->ls.count_output].direct = pDoc->ls.temp_logic.direct;
			pDoc->ls.rotate_output(&pDoc->ls.out[pDoc->ls.count_output], pDoc->ls.temp_logic.direct);
			pDoc->ls.pif[p1.x / 20][p1.y / 20].input = pDoc->ls.count_output;
			pDoc->ls.out[pDoc->ls.count_output].name = pDoc->ls.temp_logic.name;
			pDoc->ls.pif[p1.x / 20 - 1][p1.y / 20].value;
			pDoc->ls.savetomem(pointofpif, ::input, pDoc->ls.pif[p1.x / 20][p1.y / 20].input, ::paste, pDoc->ls.pif[p1.x / 20][p1.y / 20].name, (Direct)pDoc->ls.pif[p1.x / 20][p1.y / 20].direct);
			pDoc->ls.whatgate = nothing;
			Invalidate(1);
			break;
		case and:
			pDoc->ls.count_and++;
			pDoc->ls.pif[p1.x / 20][p1.y / 20].and = pDoc->ls.count_and;
			pDoc->ls.create_and(&pDoc->ls.and[pDoc->ls.count_and], pointofpif); // 만드는 함수 호출.
			pDoc->ls.and[pDoc->ls.count_and].name = pDoc->ls.temp_logic.name;
			pDoc->ls.and[pDoc->ls.count_and].direct = pDoc->ls.temp_logic.direct;
			pDoc->ls.rotate_and(&pDoc->ls.and[pDoc->ls.count_and], pDoc->ls.temp_logic.direct);
			pDoc->ls.savetomem(pointofpif, ::input, pDoc->ls.pif[p1.x / 20][p1.y / 20].input, ::paste, pDoc->ls.pif[p1.x / 20][p1.y / 20].name, (Direct)pDoc->ls.pif[p1.x / 20][p1.y / 20].direct);
			pDoc->ls.whatgate = nothing;
			Invalidate(1);
			break;
		case xor:
			pDoc->ls.count_xor++;
			pDoc->ls.pif[p1.x / 20][p1.y / 20].xor = pDoc->ls.count_xor;
			pDoc->ls.create_xor(&pDoc->ls.xor[pDoc->ls.count_xor], pointofpif); // 만드는 함수 호출.
			pDoc->ls.xor[pDoc->ls.count_xor].name = pDoc->ls.temp_logic.name;
			pDoc->ls.xor[pDoc->ls.count_xor].direct = pDoc->ls.temp_logic.direct;
			pDoc->ls.rotate_xor(&pDoc->ls.xor[pDoc->ls.count_xor], pDoc->ls.temp_logic.direct);
			pDoc->ls.savetomem(pointofpif, ::input, pDoc->ls.pif[p1.x / 20][p1.y / 20].input, ::paste, pDoc->ls.pif[p1.x / 20][p1.y / 20].name, (Direct)pDoc->ls.pif[p1.x / 20][p1.y / 20].direct);
			pDoc->ls.whatgate = nothing;
			Invalidate(1);
			break;
		case nor:
			pDoc->ls.count_nor++;
			pDoc->ls.pif[p1.x / 20][p1.y / 20].nor = pDoc->ls.count_nor;
			pDoc->ls.create_nor(&pDoc->ls.nor[pDoc->ls.count_nor], pointofpif); // 만드는 함수 호출.
			pDoc->ls.nor[pDoc->ls.count_nor].name = pDoc->ls.temp_logic.name;
			pDoc->ls.nor[pDoc->ls.count_nor].direct = pDoc->ls.temp_logic.direct;
			pDoc->ls.rotate_nor(&pDoc->ls.nor[pDoc->ls.count_nor], pDoc->ls.temp_logic.direct);
			pDoc->ls.savetomem(pointofpif, ::input, pDoc->ls.pif[p1.x / 20][p1.y / 20].input, ::paste, pDoc->ls.pif[p1.x / 20][p1.y / 20].name, (Direct)pDoc->ls.pif[p1.x / 20][p1.y / 20].direct);
			pDoc->ls.whatgate = nothing;
			Invalidate(1);
			break;
		case nand:
			pDoc->ls.count_nand++;
			pDoc->ls.pif[p1.x / 20][p1.y / 20].nand = pDoc->ls.count_nand;
			pDoc->ls.create_nand(&pDoc->ls.nand[pDoc->ls.count_nand], pointofpif); // 만드는 함수 호출.
			pDoc->ls.nand[pDoc->ls.count_nand].name = pDoc->ls.temp_logic.name;
			pDoc->ls.nand[pDoc->ls.count_nand].direct = pDoc->ls.temp_logic.direct;
			pDoc->ls.rotate_nand(&pDoc->ls.nand[pDoc->ls.count_nand], pDoc->ls.temp_logic.direct);
			pDoc->ls.savetomem(pointofpif, ::input, pDoc->ls.pif[p1.x / 20][p1.y / 20].input, ::paste, pDoc->ls.pif[p1.x / 20][p1.y / 20].name, (Direct)pDoc->ls.pif[p1.x / 20][p1.y / 20].direct);
			pDoc->ls.whatgate = nothing;
			Invalidate(1);
			break;
		case or :
			pDoc->ls.count_or++;
			pDoc->ls.pif[p1.x / 20][p1.y / 20]. or = pDoc->ls.count_or;
			pDoc->ls.create_or(&pDoc->ls. or [pDoc->ls.count_or], pointofpif);
			pDoc->ls.or[pDoc->ls.count_or].name = pDoc->ls.temp_logic.name;
			pDoc->ls.or[pDoc->ls.count_or].direct = pDoc->ls.temp_logic.direct;
			pDoc->ls.rotate_or(&pDoc->ls. or [pDoc->ls.count_or], pDoc->ls.temp_logic.direct);
			pDoc->ls.savetomem(pointofpif, ::input, pDoc->ls.pif[p1.x / 20][p1.y / 20].input, ::paste, pDoc->ls.pif[p1.x / 20][p1.y / 20].name, (Direct)pDoc->ls.pif[p1.x / 20][p1.y / 20].direct);
			pDoc->ls.whatgate = nothing;
			Invalidate(1);
			break;
		case not:
			pDoc->ls.count_not++;
			pDoc->ls.pif[p1.x / 20][p1.y / 20].not = pDoc->ls.count_not;
			pDoc->ls.create_not(&pDoc->ls. not [pDoc->ls.count_not], pointofpif);
			pDoc->ls.not[pDoc->ls.count_not].name = pDoc->ls.temp_logic.name;
			pDoc->ls.not[pDoc->ls.count_not].direct = pDoc->ls.temp_logic.direct;
			pDoc->ls.rotate_not(&pDoc->ls. not [pDoc->ls.count_not], pDoc->ls.temp_logic.direct);
			pDoc->ls.savetomem(pointofpif, ::input, pDoc->ls.pif[p1.x / 20][p1.y / 20].input, ::paste, pDoc->ls.pif[p1.x / 20][p1.y / 20].name, (Direct)pDoc->ls.pif[p1.x / 20][p1.y / 20].direct);
			pDoc->ls.whatgate = nothing;
			Invalidate(1);
			break;
		case tff:
			pDoc->ls.count_tff++;
			pDoc->ls.create_tff(&pDoc->ls.tff[pDoc->ls.count_tff], pointofpif);
			pDoc->ls.tff[pDoc->ls.count_tff].name = pDoc->ls.temp_logic.name;
			pDoc->ls.tff[pDoc->ls.count_tff].direct = pDoc->ls.temp_logic.direct;
			pDoc->ls.rotate_tff(&pDoc->ls.tff[pDoc->ls.count_tff], pDoc->ls.temp_logic.direct);
			pDoc->ls.savetomem(pointofpif, ::input, pDoc->ls.pif[p1.x / 20][p1.y / 20].input, ::paste, pDoc->ls.pif[p1.x / 20][p1.y / 20].name, (Direct)pDoc->ls.pif[p1.x / 20][p1.y / 20].direct);
			pDoc->ls.whatgate = nothing;
			Invalidate(1);
			break;
		case lsclock:
			pDoc->ls.count_clock++;
			pDoc->ls.create_clock(&pDoc->ls.clock[pDoc->ls.count_clock], pointofpif);
			pDoc->ls.clock[pDoc->ls.count_clock].name = pDoc->ls.temp_logic.name;
			pDoc->ls.clock[pDoc->ls.count_clock].direct = pDoc->ls.temp_logic.direct;
			pDoc->ls.rotate_clock(&pDoc->ls.clock[pDoc->ls.count_clock], pDoc->ls.temp_logic.direct);
			pDoc->ls.savetomem(pointofpif, ::input, pDoc->ls.pif[p1.x / 20][p1.y / 20].input, ::paste, pDoc->ls.pif[p1.x / 20][p1.y / 20].name, (Direct)pDoc->ls.pif[p1.x / 20][p1.y / 20].direct);
			pDoc->ls.whatgate = nothing;
			Invalidate(1);
			break;
		case dff:
			pDoc->ls.count_dff++;
			pDoc->ls.create_dff(&pDoc->ls.dff[pDoc->ls.count_dff], pointofpif);
			pDoc->ls.dff[pDoc->ls.count_dff].name = pDoc->ls.temp_logic.name;
			pDoc->ls.dff[pDoc->ls.count_dff].direct = pDoc->ls.temp_logic.direct;
			pDoc->ls.rotate_dff(&pDoc->ls.dff[pDoc->ls.count_dff], pDoc->ls.temp_logic.direct);
			pDoc->ls.savetomem(pointofpif, ::input, pDoc->ls.pif[p1.x / 20][p1.y / 20].input, ::paste, pDoc->ls.pif[p1.x / 20][p1.y / 20].name, (Direct)pDoc->ls.pif[p1.x / 20][p1.y / 20].direct);
			pDoc->ls.whatgate = nothing;
			Invalidate(1);
			break;
		case jkff:
			pDoc->ls.count_jkff++;
			pDoc->ls.create_jkff(&pDoc->ls.jkff[pDoc->ls.count_jkff], pointofpif);
			pDoc->ls.jkff[pDoc->ls.count_jkff].name = pDoc->ls.temp_logic.name;
			pDoc->ls.jkff[pDoc->ls.count_jkff].direct = pDoc->ls.temp_logic.direct;
			pDoc->ls.rotate_jkff(&pDoc->ls.jkff[pDoc->ls.count_jkff], pDoc->ls.temp_logic.direct);
			pDoc->ls.savetomem(pointofpif, ::input, pDoc->ls.pif[p1.x / 20][p1.y / 20].input, ::paste, pDoc->ls.pif[p1.x / 20][p1.y / 20].name, (Direct)pDoc->ls.pif[p1.x / 20][p1.y / 20].direct);
			pDoc->ls.whatgate = nothing;
			Invalidate(1);
			break;
		case seg7:
			pDoc->ls.count_seg7++;
			pDoc->ls.create_seg7(&pDoc->ls.seg7[pDoc->ls.count_seg7], pointofpif);
			pDoc->ls.seg7[pDoc->ls.count_seg7].name = pDoc->ls.temp_logic.name;
			pDoc->ls.seg7[pDoc->ls.count_seg7].direct = pDoc->ls.temp_logic.direct;
			pDoc->ls.rotate_seg7(&pDoc->ls.seg7[pDoc->ls.count_seg7], pDoc->ls.temp_logic.direct);
			pDoc->ls.savetomem(pointofpif, ::input, pDoc->ls.pif[p1.x / 20][p1.y / 20].input, ::paste, pDoc->ls.pif[p1.x / 20][p1.y / 20].name, (Direct)pDoc->ls.pif[p1.x / 20][p1.y / 20].direct);
			pDoc->ls.whatgate = nothing;
			Invalidate(1);
			break;
		case lib:
			pDoc->ls.count_lib++;
			pDoc->ls.create_lib(&pDoc->ls.lib[pDoc->ls.count_lib], pointofpif);
			pDoc->ls.lib[pDoc->ls.count_lib].name = pDoc->ls.temp_logic.name;
			pDoc->ls.lib[pDoc->ls.count_lib].direct = pDoc->ls.temp_logic.direct;
			pDoc->ls.rotate_lib(&pDoc->ls.lib[pDoc->ls.count_lib], pDoc->ls.temp_logic.direct);
			pDoc->ls.savetomem(pointofpif, ::input, pDoc->ls.pif[p1.x / 20][p1.y / 20].input, ::paste, pDoc->ls.pif[p1.x / 20][p1.y / 20].name, (Direct)pDoc->ls.pif[p1.x / 20][p1.y / 20].direct);
			pDoc->ls.whatgate = nothing;
			Invalidate(1);
			break;
		case ::dcd:
			pDoc->ls.count_dcd++;
			pDoc->ls.create_dcd(&pDoc->ls.dcd[pDoc->ls.count_dcd], pointofpif);
			pDoc->ls.dcd[pDoc->ls.count_dcd].name = pDoc->ls.temp_logic.name;
			pDoc->ls.dcd[pDoc->ls.count_dcd].direct = pDoc->ls.temp_logic.direct;
			pDoc->ls.savetomem(pointofpif, ::input, pDoc->ls.pif[p1.x / 20][p1.y / 20].input, ::paste, pDoc->ls.pif[p1.x / 20][p1.y / 20].name, (Direct)pDoc->ls.pif[p1.x / 20][p1.y / 20].direct);
			pDoc->ls.whatgate = nothing;
			Invalidate(1);
			break;
		}
}



void CPLS2View::Oncut()
{
	CPLS2Doc* pDoc = GetDocument();
	CPoint p1 = DividedByTwenty(rbuttonClickedPoint);


	switch (pDoc->ls.pif[p1.x / 20][p1.y / 20].gate)
	{
	case input:
		pDoc->ls.temp_logic.direct = pDoc->ls.in[pDoc->ls.pif[p1.x / 20][p1.y / 20].input].direct;
		pDoc->ls.temp_logic.name = pDoc->ls.in[pDoc->ls.pif[p1.x / 20][p1.y / 20].input].name;
		pDoc->ls.temp_logic.gate = input;
		break;
	case output:
		pDoc->ls.temp_logic.direct = pDoc->ls.out[pDoc->ls.pif[p1.x / 20][p1.y / 20].output].direct;
		pDoc->ls.temp_logic.name = pDoc->ls.out[pDoc->ls.pif[p1.x / 20][p1.y / 20].output].name;
		pDoc->ls.temp_logic.gate = output;
		break;
	case and:
		pDoc->ls.temp_logic.direct = pDoc->ls.and[pDoc->ls.pif[p1.x / 20][p1.y / 20].and].direct;
		pDoc->ls.temp_logic.name = pDoc->ls.and[pDoc->ls.pif[p1.x / 20][p1.y / 20].and].name;
		pDoc->ls.temp_logic.gate = and;
		break;
	case or :
		pDoc->ls.temp_logic.direct = pDoc->ls. or [pDoc->ls.pif[p1.x / 20][p1.y / 20]. or ].direct;
		pDoc->ls.temp_logic.name = pDoc->ls. or [pDoc->ls.pif[p1.x / 20][p1.y / 20]. or ].name;
		pDoc->ls.temp_logic.gate = or ;
		break;
	case not:
		pDoc->ls.temp_logic.direct = pDoc->ls.not[pDoc->ls.pif[p1.x / 20][p1.y / 20].not].direct;
		pDoc->ls.temp_logic.name = pDoc->ls.not[pDoc->ls.pif[p1.x / 20][p1.y / 20].not].name;
		pDoc->ls.temp_logic.gate = not;
		break;
	case nand:
		pDoc->ls.temp_logic.direct = pDoc->ls.nand[pDoc->ls.pif[p1.x / 20][p1.y / 20].nand].direct;
		pDoc->ls.temp_logic.name = pDoc->ls.nand[pDoc->ls.pif[p1.x / 20][p1.y / 20].nand].name;
		pDoc->ls.temp_logic.gate = nand;
		break;
	case nor:
		pDoc->ls.temp_logic.direct = pDoc->ls.nor[pDoc->ls.pif[p1.x / 20][p1.y / 20].nor].direct;
		pDoc->ls.temp_logic.name = pDoc->ls.nor[pDoc->ls.pif[p1.x / 20][p1.y / 20].nor].name;
		pDoc->ls.temp_logic.gate = nor;
		break;
	case xor:
		pDoc->ls.temp_logic.direct = pDoc->ls.xor[pDoc->ls.pif[p1.x / 20][p1.y / 20].xor].direct;
		pDoc->ls.temp_logic.name = pDoc->ls.xor[pDoc->ls.pif[p1.x / 20][p1.y / 20].xor].name;
		pDoc->ls.temp_logic.gate = xor;
		break;
	case dff:
		pDoc->ls.temp_logic.direct = pDoc->ls.dff[pDoc->ls.pif[p1.x / 20][p1.y / 20].dff].direct;
		pDoc->ls.temp_logic.name = pDoc->ls.dff[pDoc->ls.pif[p1.x / 20][p1.y / 20].dff].name;
		pDoc->ls.temp_logic.gate = dff;
		break;
	case jkff:
		pDoc->ls.temp_logic.direct = pDoc->ls.jkff[pDoc->ls.pif[p1.x / 20][p1.y / 20].jkff].direct;
		pDoc->ls.temp_logic.name = pDoc->ls.jkff[pDoc->ls.pif[p1.x / 20][p1.y / 20].jkff].name;
		pDoc->ls.temp_logic.gate = jkff;
		break;
	case tff:
		pDoc->ls.temp_logic.direct = pDoc->ls.tff[pDoc->ls.pif[p1.x / 20][p1.y / 20].tff].direct;
		pDoc->ls.temp_logic.name = pDoc->ls.tff[pDoc->ls.pif[p1.x / 20][p1.y / 20].tff].name;
		pDoc->ls.temp_logic.gate = tff;
		break;
	case seg7:
		pDoc->ls.temp_logic.direct = pDoc->ls.seg7[pDoc->ls.pif[p1.x / 20][p1.y / 20].seg7].direct;
		pDoc->ls.temp_logic.name = pDoc->ls.seg7[pDoc->ls.pif[p1.x / 20][p1.y / 20].seg7].name;
		pDoc->ls.temp_logic.gate = seg7;
		break;
	case lib:
		pDoc->ls.temp_logic.direct = pDoc->ls.lib[pDoc->ls.pif[p1.x / 20][p1.y / 20].lib].direct;
		pDoc->ls.temp_logic.name = pDoc->ls.lib[pDoc->ls.pif[p1.x / 20][p1.y / 20].lib].name;
		pDoc->ls.temp_logic.gate = lib;
		break;
	case dcd:
		pDoc->ls.temp_logic.direct = pDoc->ls.dcd[pDoc->ls.pif[p1.x / 20][p1.y / 20].dcd].direct;
		pDoc->ls.temp_logic.name = pDoc->ls.dcd[pDoc->ls.pif[p1.x / 20][p1.y / 20].dcd].name;
		pDoc->ls.temp_logic.gate = dcd;
		break;
	case lsclock:
		pDoc->ls.temp_logic.direct = pDoc->ls.clock[pDoc->ls.pif[p1.x / 20][p1.y / 20].clock].direct;
		pDoc->ls.temp_logic.name = pDoc->ls.clock[pDoc->ls.pif[p1.x / 20][p1.y / 20].clock].name;
		pDoc->ls.temp_logic.gate = lsclock;
		break;
	}

	pDoc->ls.lsdelete(p1 , 1);
}


void CPLS2View::OnDoUndo()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CPLS2Doc* pDoc = GetDocument();
	pDoc->ls.undo();
	Invalidate(1);
}


void CPLS2View::OnDoRedo()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CPLS2Doc* pDoc = GetDocument();
	pDoc->ls.redo();
	Invalidate(1);
}


void CPLS2View::OnUpdateDoUndo(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	CPLS2Doc* pDoc = GetDocument();
	pCmdUI->Enable(pDoc->ls.memindex != -1);
}


void CPLS2View::OnUpdateDoRedo(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	CPLS2Doc* pDoc = GetDocument();
	pCmdUI->Enable(pDoc->ls.memindex != pDoc->ls.maxmemindex);
}


void CPLS2View::OnUpdate1second(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	CPLS2Doc* pDoc = GetDocument();
	pCmdUI->SetCheck(hz == 1000);
}


void CPLS2View::OnUpdatepoint5second(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	CPLS2Doc* pDoc = GetDocument();
	pCmdUI->SetCheck(hz == 500);
}


void CPLS2View::OnUpdatepoint25second(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	CPLS2Doc* pDoc = GetDocument();
	pCmdUI->SetCheck(hz == 200);
}


void CPLS2View::OnUpdatepoint1second(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	CPLS2Doc* pDoc = GetDocument();
	pCmdUI->SetCheck(hz == 100);
}


void CPLS2View::OnUpdate32825(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	CPLS2Doc* pDoc = GetDocument();
	pCmdUI->SetCheck(pDoc->ls.dff[0].trigger == TRUE);
}


void CPLS2View::OnUpdate32826(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	CPLS2Doc* pDoc = GetDocument();
	pCmdUI->SetCheck(pDoc->ls.dff[0].trigger == FALSE);
}


void CPLS2View::OnUpdatelibready(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	CPLS2Doc* pDoc = GetDocument();
	if(pDoc->ls.existlibrary == 1)
		pCmdUI->Enable(pDoc->ls.existlibrary != 1);
	else
		pCmdUI->SetCheck(pDoc->ls.readylibaray == 1);
}


void CPLS2View::OnUpdatecreatelib(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	CPLS2Doc* pDoc = GetDocument();
	pCmdUI->Enable(pDoc->ls.existlibrary == 1);
}


void CPLS2View::OnUpdate32810(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	CPLS2Doc* pDoc = GetDocument();
	CPoint p1 = DividedByTwenty(rbuttonClickedPoint);
	pCmdUI->Enable(pDoc->ls.pif[p1.x/20][p1.y/20].serializegate != nothing);
}


void CPLS2View::OnUpdate32811(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	CPLS2Doc* pDoc = GetDocument();
	CPoint p1 = DividedByTwenty(rbuttonClickedPoint);
	pCmdUI->Enable(pDoc->ls.pif[p1.x / 20][p1.y / 20].serializegate != nothing);
}


void CPLS2View::OnUpdate32812(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	CPLS2Doc* pDoc = GetDocument();
	CPoint p1 = DividedByTwenty(rbuttonClickedPoint);
	pCmdUI->Enable(pDoc->ls.pif[p1.x / 20][p1.y / 20].serializegate != nothing);
}


void CPLS2View::OnUpdate32813(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	CPLS2Doc* pDoc = GetDocument();
	CPoint p1 = DividedByTwenty(rbuttonClickedPoint);
	pCmdUI->Enable(pDoc->ls.pif[p1.x / 20][p1.y / 20].serializegate != nothing);
}


void CPLS2View::OnUpdatecut(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	CPLS2Doc* pDoc = GetDocument();
	CPoint p1 = DividedByTwenty(rbuttonClickedPoint);
	pCmdUI->Enable(pDoc->ls.pif[p1.x / 20][p1.y / 20].serializegate != nothing);
}


void CPLS2View::OnUpdate32850(CCmdUI *pCmdUI)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
	CPLS2Doc* pDoc = GetDocument();
	CPoint p1 = DividedByTwenty(rbuttonClickedPoint);
	pCmdUI->Enable(pDoc->ls.pif[p1.x / 20][p1.y / 20].serializegate != nothing);
}
