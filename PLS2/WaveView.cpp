// WaveView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "PLS2.h"
#include "WaveView.h"
#include "WaveDoc.h"

// CWaveView

IMPLEMENT_DYNCREATE(CWaveView, CScrollView)

CWaveView::CWaveView()
{

}

CWaveView::~CWaveView()
{
}


BEGIN_MESSAGE_MAP(CWaveView, CScrollView)
	ON_COMMAND(ID_wave_serial, &CWaveView::Onwaveserial)
	ON_COMMAND(ID_wave_running, &CWaveView::Onwaverunning)
	ON_COMMAND(32840, &CWaveView::On32840)
	ON_COMMAND(ID_wavehz2, &CWaveView::Onwavehz2)
	ON_COMMAND(ID_wavehz3, &CWaveView::Onwavehz3)
	ON_COMMAND(ID_wavehz4, &CWaveView::Onwavehz4)
	ON_COMMAND(ID_ready, &CWaveView::Onready)
	ON_COMMAND(ID_start, &CWaveView::Onstart)
	ON_COMMAND(ID_pause, &CWaveView::Onpause)
	ON_COMMAND(ID_delete, &CWaveView::Ondelete)
	ON_WM_TIMER()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND(ID_wavehzstop, &CWaveView::Onwavehzstop)
END_MESSAGE_MAP()


// CWaveView 그리기입니다.

void CWaveView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

void CWaveView::OnDraw(CDC* pDC)
{
	// TODO: 여기에 그리기 코드를 추가합니다.
	CWaveDoc* pDoc = (CWaveDoc*)GetDocument();
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

	if (drawing == FALSE) {
		//그려진 선을 그림
		for (int i = 0; i < pDoc->ls.line.GetSize(); i++) {
			pDC->MoveTo(pDoc->ls.line[i].firstPt);
			pDC->LineTo(pDoc->ls.line[i].secondPt);
		}

		//존재하는 input단자의 개수만큼 그려줌.(Rectangle이므로 min(왼쪽끝)점과 max(오른쪽)점을 가짐)
		for (i = 0; i <= pDoc->ls.count_input; i++) {
			if (pDoc->ls.in[i].clicked.x != 0 && pDoc->ls.in[i].clicked.y != 0)
			{
				pDC->Rectangle(pDoc->ls.in[i].min.x * 20, pDoc->ls.in[i].min.y * 20, pDoc->ls.in[i].max.x * 20, pDoc->ls.in[i].max.y * 20);
				if (pDoc->ls.in[i].min.x * 20 > 0) {
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

				if (pDoc->ls. or [i].direct == RIGHT)
					bitmap.LoadBitmapW(IDB_GATE_OR);

				else if (pDoc->ls. or [i].direct == BOTTOM)
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
				str.Format(_T("%s(%d)"), pDoc->ls. or [i].name, pDoc->ls. or [i].value);
				pDC->TextOutW(pDoc->ls. or [i].min.x * 20 + 5, pDoc->ls. or [i].min.y * 20 + 30, str);
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

				if (pDoc->ls.tff[i].direct == RIGHT)
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
				str.Format(_T("%d %d %d %d %d %d %d"), pDoc->ls.lib[i].value[0], pDoc->ls.lib[i].value[1], pDoc->ls.lib[i].value[2], pDoc->ls.lib[i].value[3]
					, pDoc->ls.lib[i].value[4], pDoc->ls.lib[i].value[5], pDoc->ls.lib[i].value[6]);
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
	}
	else {
		for (i = 0; i <= pDoc->ls2.count_input; i++) {
			if (pDoc->ls2.in[i].clicked.x != 0 && pDoc->ls2.in[i].clicked.y != 0)
			{
				pDC->Rectangle(pDoc->ls2.in[i].min.x * 20, pDoc->ls2.in[i].min.y * 20, pDoc->ls2.in[i].max.x * 20, pDoc->ls2.in[i].max.y * 20);
				if (pDoc->ls2.in[i].min.x * 20 > 0) {
					//str.Format(_T("value = %d"), *(pDoc->ls2.pif[pDoc->ls2.in[i].clicked.x + 1][pDoc->ls2.in[i].clicked.y].value));
					str.Format(_T("%s(%d)"), pDoc->ls.in[i].name, pDoc->ls.in[i].value);
					pDC->SetBkMode(TRANSPARENT);
					pDC->TextOutW(pDoc->ls2.in[i].min.x * 20, pDoc->ls2.in[i].min.y * 20, str);
					pDC->SetBkMode(OPAQUE);
				}
				pDC->Polyline(inoldpoint[i].GetData(), inoldpoint[i].GetSize());
			}
		}
		//존재하는 output단자의 개수만큼 그려줌.(Ellipse이므로 min(왼쪽끝)점과 max(오른쪽)점을 가짐)
		for (i = 0; i <= pDoc->ls2.count_output; i++) {
			if (pDoc->ls2.out[i].clicked.x != 0 && pDoc->ls2.out[i].clicked.y != 0)
			{
				pDC->Ellipse(pDoc->ls2.out[i].min.x * 20, pDoc->ls2.out[i].min.y * 20, pDoc->ls2.out[i].max.x * 20, pDoc->ls2.out[i].max.y * 20);
				if (pDoc->ls2.out[i].min.x * 20 > 0) {
					str.Format(_T("%s(%d)"), pDoc->ls.out[i].name, pDoc->ls.out[i].value);
					pDC->SetBkMode(TRANSPARENT);
					pDC->TextOutW(pDoc->ls2.out[i].min.x * 20, pDoc->ls2.out[i].min.y * 20, str);
					pDC->SetBkMode(OPAQUE);
				}
				pDC->Polyline(outoldpoint[i].GetData(), outoldpoint[i].GetSize());
			}
		}
		for (i = 0; i <= pDoc->ls2.count_clock; i++) {
			if (pDoc->ls2.clock[i].clicked.x != 0 && pDoc->ls2.clock[i].clicked.y != 0)
			{
				pDC->Rectangle(pDoc->ls2.clock[i].min.x * 20, pDoc->ls2.clock[i].min.y * 20, pDoc->ls2.clock[i].max.x * 20, pDoc->ls2.clock[i].max.y * 20);
				pDC->Ellipse(pDoc->ls2.clock[i].min.x * 20, pDoc->ls2.clock[i].min.y * 20, pDoc->ls2.clock[i].max.x * 20, pDoc->ls2.clock[i].max.y * 20);
				if (pDoc->ls2.clock[i].min.x * 20 > 0) {
					//str.Format(_T("value = %d"), *(pDoc->ls2.pif[pDoc->ls2.clock[i].clicked.x + 1][pDoc->ls2.clock[i].clicked.y].value));
					pDC->SetBkMode(TRANSPARENT);
					str.Format(_T("%s(%d)"), pDoc->ls.clock[i].name, pDoc->ls.clock[i].value);
					pDC->TextOutW(pDoc->ls2.clock[i].min.x * 20, pDoc->ls2.clock[i].min.y * 20, str);
					pDC->SetBkMode(OPAQUE);
				}
				pDC->Polyline(clockoldpoint[i].GetData(), clockoldpoint[i].GetSize());
			}
		}
	}
	ReleaseDC(pDC);
}


// CWaveView 진단입니다.

#ifdef _DEBUG
void CWaveView::AssertValid() const
{
	CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void CWaveView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif
#endif //_DEBUG


// CWaveView 메시지 처리기입니다.


void CWaveView::Onwaveserial()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	repeat = 0;
	se[0] = 0;
	CWaveDoc* pDoc = (CWaveDoc*)GetDocument();
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




void CWaveView::Onwaverunning()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CWaveView::On32840()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	hz = 1000;
}


void CWaveView::Onwavehz2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	hz = 500;
}


void CWaveView::Onwavehz3()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	hz = 200;
}


void CWaveView::Onwavehz4()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	hz = 100;
}


void CWaveView::Onready()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	drawing = TRUE;
	repeat = 0;
	se[0] = 0;
	CWaveDoc* pDoc = (CWaveDoc*)GetDocument();
	pDoc->ls.count_serial = -1;
	for (int i = 0; i <= pDoc->ls.count_output; i++) {
		pDoc->ls.serialize_gate(pDoc->ls.out[i].input.x, pDoc->ls.out[i].input.y);
		repeat++;
		se[repeat] = pDoc->ls.count_serial;
	}
	for (int i = 0; i <= pDoc->ls.count_seg7; i++) {
		pDoc->ls.serialize_gate(pDoc->ls.seg7[0].clicked.x, pDoc->ls.seg7[0].clicked.y);
		repeat++;
		se[repeat] = pDoc->ls.count_serial;
	}
	inoldpoint = new CArray<CPoint, CPoint&>[INDEX];
	for (int i = 0; i <= pDoc->ls.count_input; i++) {
		pDoc->ls2.in[i].value = pDoc->ls.in[i].value;
		inold[i] = pDoc->ls.in[i].value;
		if (pDoc->ls.in[i].value == 0)
			inoldpoint[i].Add(CPoint(pDoc->ls2.in[i].clicked.x * 20 + 40, pDoc->ls2.in[i].clicked.y * 20 + 10));
		else
			inoldpoint[i].Add(CPoint(pDoc->ls2.in[i].clicked.x * 20 + 40, pDoc->ls2.in[i].clicked.y * 20 - 10));  
	}
	clockoldpoint = new CArray<CPoint, CPoint&>[INDEX];
	for (int i = 0; i <= pDoc->ls.count_clock; i++) {
		pDoc->ls2.in[i].value = pDoc->ls.in[i].value;
		clockold[i] = pDoc->ls.clock[i].value;
		if (pDoc->ls.clock[i].value == 0)
			clockoldpoint[i].Add(CPoint(pDoc->ls2.clock[i].clicked.x * 20 + 40, pDoc->ls2.clock[i].clicked.y * 20 + 10));
		else
			clockoldpoint[i].Add(CPoint(pDoc->ls2.clock[i].clicked.x * 20 + 40, pDoc->ls2.clock[i].clicked.y * 20 - 10));
	}
	outoldpoint = new CArray<CPoint, CPoint&>[INDEX];
	for (int i = 0; i <= pDoc->ls.count_output; i++) {
		pDoc->ls2.out[i].value = pDoc->ls.out[i].value;
		outold[i] = pDoc->ls.out[i].value;
		if (pDoc->ls2.out[i].value == 0)
			outoldpoint[i].Add(CPoint(pDoc->ls2.out[i].clicked.x * 20 + 40, pDoc->ls2.out[i].clicked.y * 20 + 10));
		else
			outoldpoint[i].Add(CPoint(pDoc->ls2.out[i].clicked.x * 20 + 40, pDoc->ls2.out[i].clicked.y * 20 - 10));
	}
	SetTimer(999, 25, NULL);
	Invalidate(1);
}


void CWaveView::Onstart()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.	
	SetTimer(888, 50, NULL);
}


void CWaveView::Onpause()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	KillTimer(999);
	KillTimer(888);
}


void CWaveView::Ondelete()
{
	CWaveDoc* pDoc = (CWaveDoc*)GetDocument();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	drawing = FALSE;
	KillTimer(999);
	KillTimer(888);
	for (int i = 0; i <= pDoc->ls.count_input; i++) {
		inoldpoint[i].RemoveAll();
	}
	for (int i = 0; i <= pDoc->ls.count_output; i++) {
		outoldpoint[i].RemoveAll();
	}
	for (int i = 0; i <= pDoc->ls.count_clock; i++) {
		clockoldpoint[i].RemoveAll();
	}
	Invalidate(1);
}


void CWaveView::OnTimer(UINT_PTR nIDEvent)
{
	CWaveDoc* pDoc = (CWaveDoc*)GetDocument();
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int index = 0;
	switch (nIDEvent) {
	case 999:
		pDoc->ls.run(repeat, se, &pDoc->library);
		Invalidate(1);
		break;
	case 888:
		for (int i = 0; i <= pDoc->ls.count_input; i++) {
			if (pDoc->ls.in[i].value == inold[i]) {
				index = inoldpoint[i].GetSize() - 1;
				indexpoint = inoldpoint[i].GetAt(index);
				indexpoint.x = indexpoint.x + 2;
				inoldpoint[i].Add(indexpoint);
			}
			else if (pDoc->ls.in[i].value == 1 || inold[i] == 0) {
				index = inoldpoint[i].GetSize() - 1;
				indexpoint = inoldpoint[i].GetAt(index);
				indexpoint.y = indexpoint.y - 20;
				inoldpoint[i].Add(indexpoint);
				indexpoint.x = indexpoint.x + 2;
				inoldpoint[i].Add(indexpoint);
				inold[i] = 1;
			}
			else if (pDoc->ls.in[i].value == 0 || inold[i] == 1) {
				index = inoldpoint[i].GetSize() - 1;
				indexpoint = inoldpoint[i].GetAt(index);
				indexpoint.y = indexpoint.y + 20;
				inoldpoint[i].Add(indexpoint);
				indexpoint.x = indexpoint.x + 2;
				inoldpoint[i].Add(indexpoint);
				inold[i] = 0;
			}
		}
		for (int i = 0; i <= pDoc->ls.count_output; i++) {
			if (pDoc->ls.out[i].value == outold[i]) {
				index = outoldpoint[i].GetSize() - 1;
				indexpoint = outoldpoint[i].GetAt(index);
				indexpoint.x = indexpoint.x + 2;
				outoldpoint[i].Add(indexpoint);
			}
			else if (pDoc->ls.out[i].value == 1 || outold[i] == 0) {
				index = outoldpoint[i].GetSize() - 1;
				indexpoint = outoldpoint[i].GetAt(index);
				indexpoint.y = indexpoint.y - 20;
				outoldpoint[i].Add(indexpoint);
				indexpoint.x = indexpoint.x + 2;
				outoldpoint[i].Add(indexpoint);
				outold[i] = 1;
			}
			else if (pDoc->ls.out[i].value == 0 || outold[i] == 1) {
				index = outoldpoint[i].GetSize() - 1;
				indexpoint = outoldpoint[i].GetAt(index);
				indexpoint.y = indexpoint.y + 20;
				outoldpoint[i].Add(indexpoint);
				indexpoint.x = indexpoint.x + 2;
				outoldpoint[i].Add(indexpoint);
				outold[i] = 0;
			}
		}
		for (int i = 0; i <= pDoc->ls.count_clock; i++) {
			if (pDoc->ls.clock[i].value == clockold[i]) {
				index = clockoldpoint[i].GetSize() - 1;
				indexpoint = clockoldpoint[i].GetAt(index);
				indexpoint.x = indexpoint.x + 2;
				clockoldpoint[i].Add(indexpoint);
			}
			else if (pDoc->ls.clock[i].value == 1 || clockold[i] == 0) {
				index = clockoldpoint[i].GetSize() - 1;
				indexpoint = clockoldpoint[i].GetAt(index);
				indexpoint.y = indexpoint.y - 20;
				clockoldpoint[i].Add(indexpoint);
				indexpoint.x = indexpoint.x + 2;
				clockoldpoint[i].Add(indexpoint);
				clockold[i] = 1;
			}
			else if (pDoc->ls.clock[i].value == 0 || clockold[i] == 1) {
				index = clockoldpoint[i].GetSize() - 1;
				indexpoint = clockoldpoint[i].GetAt(index);
				indexpoint.y = indexpoint.y + 20;
				clockoldpoint[i].Add(indexpoint);
				indexpoint.x = indexpoint.x + 2;
				clockoldpoint[i].Add(indexpoint);
				clockold[i] = 0;
			}
		}
		Invalidate(0);
		break;
	default:
		if (pDoc->ls.clock[nIDEvent].value == 0)
			pDoc->ls.clock[nIDEvent].value = 1;
		else
			pDoc->ls.clock[nIDEvent].value = 0;
		Invalidate();
		break;
	}
	CScrollView::OnTimer(nIDEvent);
}

CPoint CWaveView::DividedByTwenty(CPoint point)
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


void CWaveView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CWaveDoc* pDoc = (CWaveDoc*)GetDocument();
	CPoint p1 = DividedByTwenty(point);
	switch (pDoc->ls2.pif[p1.x / 20][p1.y / 20].gate)
	{
	case input:
		if (pDoc->ls2.in[pDoc->ls2.pif[p1.x / 20][p1.y / 20].input].value == 1) {
			pDoc->ls2.in[pDoc->ls2.pif[p1.x / 20][p1.y / 20].input].value = 0;
			pDoc->ls.in[pDoc->ls2.pif[p1.x / 20][p1.y / 20].input].value = 0;
		}
		else {
			pDoc->ls2.in[pDoc->ls2.pif[p1.x / 20][p1.y / 20].input].value = 1;
			pDoc->ls.in[pDoc->ls2.pif[p1.x / 20][p1.y / 20].input].value = 1;
		}
		break;
	case lsclock:
		SetTimer(pDoc->ls2.pif[p1.x / 20][p1.y / 20].clock, hz, NULL);
		break;
	}
	Invalidate(0);
	CScrollView::OnLButtonDblClk(nFlags, point);
}


void CWaveView::Onwavehzstop()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CWaveDoc* pDoc = (CWaveDoc*)GetDocument();
	for (int i = 0; i < pDoc->ls.count_clock; i++) {
		KillTimer(i);
	}
}
