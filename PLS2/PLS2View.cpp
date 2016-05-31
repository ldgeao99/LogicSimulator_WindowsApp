
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
	ON_COMMAND(ID_32782, &CPLS2View::Create_Clock_BCLK)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_COMMAND(ID_32779, &CPLS2View::Create_DFF_BCLK)
	ON_COMMAND(ID_32780, &CPLS2View::Create_JKFF_BCLK)
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

// CPLS2View 생성/소멸

CPLS2View::CPLS2View()
{
	// TODO: 여기에 생성 코드를 추가합니다.

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
				str.Format(_T("value = %d"), pDoc->ls.in[i].value);
				pDC->TextOutW(pDoc->ls.in[i].min.x * 20, pDoc->ls.in[i].min.y * 20 + 40, str);
			}
		}
	}
	//존재하는 output단자의 개수만큼 그려줌.(Ellipse이므로 min(왼쪽끝)점과 max(오른쪽)점을 가짐)
	for (i = 0; i <= pDoc->ls.count_output; i++) {
		if (pDoc->ls.out[i].clicked.x != 0 && pDoc->ls.out[i].clicked.y != 0)
		{
			pDC->Ellipse(pDoc->ls.out[i].min.x * 20, pDoc->ls.out[i].min.y * 20, pDoc->ls.out[i].max.x * 20, pDoc->ls.out[i].max.y * 20);
			if (pDoc->ls.out[i].min.x * 20 > 0) {
				str.Format(_T("value = %d"), pDoc->ls.out[i].value);
				pDC->TextOutW(pDoc->ls.out[i].min.x * 20, pDoc->ls.out[i].min.y * 20 + 40, str);
			}
		}
	}
	//존재하는 and게이트의 개수만큼 그려줌.(min(왼쪽끝)점과 max(오른쪽)점을 가짐)

	for (i = 0; i <= pDoc->ls.count_and; i++) {
		if (pDoc->ls.and[i].clicked.x != 0 && pDoc->ls.and[i].clicked.y != 0)
		{
			CBitmap bitmap;
			bitmap.LoadBitmapW(IDB_GATE_AND);
			BITMAP bmpinfo;
			bitmap.GetBitmap(&bmpinfo);
			CDC dcmem;
			dcmem.CreateCompatibleDC(pDC);
			dcmem.SelectObject(&bitmap);
			pDC->StretchBlt(pDoc->ls.and[i].min.x * 20, pDoc->ls.and[i].min.y * 20, 80, 80, &dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
			str.Format(_T("value = %d"), pDoc->ls.and[i].value);
			pDC->TextOutW(pDoc->ls.and[i].min.x * 20, pDoc->ls.and[i].min.y * 20 + 80, str);
}
	}

	for (i = 0; i <= pDoc->ls.count_xor; i++) {
		if (pDoc->ls.xor[i].clicked.x != 0 && pDoc->ls.xor[i].clicked.y != 0)
		{
			CBitmap bitmap;
			bitmap.LoadBitmapW(IDB_GATE_XOR);
			BITMAP bmpinfo;
			bitmap.GetBitmap(&bmpinfo);
			CDC dcmem;
			dcmem.CreateCompatibleDC(pDC);
			dcmem.SelectObject(&bitmap);
			pDC->StretchBlt(pDoc->ls.xor[i].min.x * 20, pDoc->ls.xor[i].min.y * 20, 80, 80, &dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
			str.Format(_T("value = %d"), pDoc->ls.xor[i].value);
			pDC->TextOutW(pDoc->ls.xor[i].min.x * 20, pDoc->ls.xor[i].min.y * 20 + 80, str);
		}
	}

	for (i = 0; i <= pDoc->ls.count_nor; i++) {
		if (pDoc->ls.nor[i].clicked.x != 0 && pDoc->ls.nor[i].clicked.y != 0)
		{
			CBitmap bitmap;
			bitmap.LoadBitmapW(IDB_GATE_NOR);
			BITMAP bmpinfo;
			bitmap.GetBitmap(&bmpinfo);
			CDC dcmem;
			dcmem.CreateCompatibleDC(pDC);
			dcmem.SelectObject(&bitmap);
			pDC->StretchBlt(pDoc->ls.nor[i].min.x * 20, pDoc->ls.nor[i].min.y * 20, 80, 80, &dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
			str.Format(_T("value = %d"), pDoc->ls.nor[i].value);
			pDC->TextOutW(pDoc->ls.nor[i].min.x * 20, pDoc->ls.nor[i].min.y * 20 + 80, str);
		}
	}

	for (i = 0; i <= pDoc->ls.count_or; i++) {
		if (pDoc->ls. or [i].clicked.x != 0 && pDoc->ls.xor[i].clicked.y != 0) {
			CBitmap bitmap;
			bitmap.LoadBitmapW(IDB_GATE_OR);
			BITMAP bmpinfo;
			bitmap.GetBitmap(&bmpinfo);
			CDC dcmem;
			dcmem.CreateCompatibleDC(pDC);
			dcmem.SelectObject(&bitmap);
			pDC->StretchBlt(pDoc->ls.or[i].min.x * 20, pDoc->ls.or[i].min.y * 20, 80, 80, &dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
			str.Format(_T("value = %d"), pDoc->ls.or[i].value);
			pDC->TextOutW(pDoc->ls.or[i].min.x * 20, pDoc->ls.or[i].min.y * 20 + 80, str);
		}
	}

	for (i = 0; i <= pDoc->ls.count_not; i++) {
		if (pDoc->ls. not [i].clicked.x != 0 && pDoc->ls.not[i].clicked.y != 0) {
			CBitmap bitmap;
			bitmap.LoadBitmapW(IDB_GATE_NOT);
			BITMAP bmpinfo;
			bitmap.GetBitmap(&bmpinfo);
			CDC dcmem;
			dcmem.CreateCompatibleDC(pDC);
			dcmem.SelectObject(&bitmap);
			pDC->StretchBlt(pDoc->ls. not [i].min.x * 20, pDoc->ls. not [i].min.y * 20, 80, 80, &dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
			str.Format(_T("value = %d"), pDoc->ls. not [i].value);
			pDC->TextOutW(pDoc->ls. not [i].min.x * 20, pDoc->ls. not [i].min.y * 20 + 80, str);
		}
	}


	for (i = 0; i <= pDoc->ls.count_nand; i++) {
		if (pDoc->ls.nand[i].clicked.x != 0 && pDoc->ls.nand[i].clicked.y != 0)
		{
			CBitmap bitmap;
			bitmap.LoadBitmapW(IDB_GATE_NAND);
			BITMAP bmpinfo;
			bitmap.GetBitmap(&bmpinfo);
			CDC dcmem;
			dcmem.CreateCompatibleDC(pDC);
			dcmem.SelectObject(&bitmap);
			pDC->StretchBlt(pDoc->ls.nand[i].min.x * 20, pDoc->ls.nand[i].min.y * 20, 80, 80, &dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
			str.Format(_T("value = %d"), pDoc->ls.nand[i].value);
			pDC->TextOutW(pDoc->ls.nand[i].min.x * 20, pDoc->ls.nand[i].min.y * 20 + 80, str);
		}
	}

	for (i = 0; i <= pDoc->ls.count_clock; i++) {
		if (pDoc->ls.clock[i].clicked.x != 0 && pDoc->ls.clock[i].clicked.y != 0)
		{
			pDC->Rectangle(pDoc->ls.clock[i].min.x * 20, pDoc->ls.clock[i].min.y * 20, pDoc->ls.clock[i].max.x * 20, pDoc->ls.clock[i].max.y * 20);
			pDC->Ellipse(pDoc->ls.clock[i].min.x * 20, pDoc->ls.clock[i].min.y * 20, pDoc->ls.clock[i].max.x * 20, pDoc->ls.clock[i].max.y * 20);
			if (pDoc->ls.clock[i].min.x * 20 > 0) {
				//str.Format(_T("value = %d"), *(pDoc->ls.pif[pDoc->ls.clock[i].clicked.x + 1][pDoc->ls.clock[i].clicked.y].value));
				str.Format(_T("value = %d"), pDoc->ls.clock[pDoc->ls.count_clock].value);
				pDC->TextOutW(pDoc->ls.clock[i].min.x * 20, pDoc->ls.clock[i].min.y * 20 + 40, str);
			}
		}
	}

	for (i = 0; i <= pDoc->ls.count_tff; i++) {
		if (pDoc->ls.tff[i].clicked.x != 0 && pDoc->ls.tff[i].clicked.y != 0)
		{
			CBitmap bitmap;
			bitmap.LoadBitmapW(IDB_FF_T);
			BITMAP bmpinfo;
			bitmap.GetBitmap(&bmpinfo);
			CDC dcmem;
			dcmem.CreateCompatibleDC(pDC);
			dcmem.SelectObject(&bitmap);
			pDC->StretchBlt(pDoc->ls.tff[i].min.x * 20, pDoc->ls.tff[i].min.y * 20, 120, 120, &dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
			str.Format(_T("value = %d"), pDoc->ls.tff[i].value);
			pDC->TextOutW(pDoc->ls.tff[i].min.x * 20, pDoc->ls.tff[i].min.y * 20 + 120, str);
		}
	}

	for (i = 0; i <= pDoc->ls.count_dff; i++) {
		if (pDoc->ls.dff[i].clicked.x != 0 && pDoc->ls.dff[i].clicked.y != 0)
		{
			CBitmap bitmap;
			bitmap.LoadBitmapW(IDB_FF_D);
			BITMAP bmpinfo;
			bitmap.GetBitmap(&bmpinfo);
			CDC dcmem;
			dcmem.CreateCompatibleDC(pDC);
			dcmem.SelectObject(&bitmap);
			pDC->StretchBlt(pDoc->ls.dff[i].min.x * 20, pDoc->ls.dff[i].min.y * 20, 120, 120, &dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
		}
	}
	
	for (i = 0; i <= pDoc->ls.count_jkff; i++) {
		if (pDoc->ls.jkff[i].clicked.x != 0 && pDoc->ls.jkff[i].clicked.y != 0)
		{
			CBitmap bitmap;
			bitmap.LoadBitmapW(IDB_FF_JK);
			BITMAP bmpinfo;
			bitmap.GetBitmap(&bmpinfo);
			CDC dcmem;
			dcmem.CreateCompatibleDC(pDC);
			dcmem.SelectObject(&bitmap);
			pDC->StretchBlt(pDoc->ls.jkff[i].min.x * 20, pDoc->ls.jkff[i].min.y * 20, 120, 120, &dcmem, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
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
void CPLS2View::OnLButtonDown(UINT nFlags, CPoint point)
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
			Invalidate(1);
			break;
		case output:
			pDoc->ls.count_output++;
			pDoc->ls.pif[p1.x / 20 - 1][p1.y / 20].value;
			pDoc->ls.create_output(&pDoc->ls.out[pDoc->ls.count_output], pointofpif);
			pDoc->ls.whatgate = nothing;
			Invalidate(1);
			break;
		case and:
			pDoc->ls.count_and++;
			pDoc->ls.pif[p1.x / 20][p1.y / 20].and = pDoc->ls.count_and;
			pDoc->ls.create_and(&pDoc->ls.and[pDoc->ls.count_and], pointofpif); // 만드는 함수 호출.
			pDoc->ls.whatgate = nothing;
			Invalidate(1);
			break;
		case xor:
			pDoc->ls.count_xor++;
			pDoc->ls.pif[p1.x / 20][p1.y / 20].xor = pDoc->ls.count_xor;
			pDoc->ls.create_xor(&pDoc->ls.xor[pDoc->ls.count_xor], pointofpif); // 만드는 함수 호출.
			pDoc->ls.whatgate = nothing;
			Invalidate(1);
			break;
		case nor:
			pDoc->ls.count_nor++;
			pDoc->ls.pif[p1.x / 20][p1.y / 20].nor = pDoc->ls.count_nor;
			pDoc->ls.create_nor(&pDoc->ls.nor[pDoc->ls.count_nor], pointofpif); // 만드는 함수 호출.
			pDoc->ls.whatgate = nothing;
			Invalidate(1);
			break;
		case nand:
			pDoc->ls.count_nand++;
			pDoc->ls.pif[p1.x / 20][p1.y / 20].nand = pDoc->ls.count_nand;
			pDoc->ls.create_nand(&pDoc->ls.nand[pDoc->ls.count_nand], pointofpif); // 만드는 함수 호출.
			pDoc->ls.whatgate = nothing;
			Invalidate(1);
			break;
		case or :
			pDoc->ls.count_or++;
			pDoc->ls.pif[p1.x / 20][p1.y / 20].or = pDoc->ls.count_or;
			pDoc->ls.create_or(&pDoc->ls. or [pDoc->ls.count_or], pointofpif);
			pDoc->ls.whatgate = nothing;
			Invalidate(1);
			break;
		case not:
			pDoc->ls.count_not++;
			pDoc->ls.pif[p1.x / 20][p1.y / 20].not = pDoc->ls.count_not;
			pDoc->ls.create_not(&pDoc->ls. not [pDoc->ls.count_not], pointofpif);
			pDoc->ls.whatgate = nothing;
			Invalidate(1);
			break;
		case tff:
			pDoc->ls.count_tff++;
			pDoc->ls.create_tff(&pDoc->ls. tff [pDoc->ls.count_tff], pointofpif);
			pDoc->ls.whatgate = nothing;
			Invalidate(1);
			break;
		case lsclock:
			pDoc->ls.count_clock++;
			pDoc->ls.create_clock(&pDoc->ls.clock[pDoc->ls.count_clock], pointofpif);
			SetTimer(pDoc->ls.count_clock,500, NULL);
			pDoc->ls.whatgate = nothing;
			Invalidate(1);
			break;
		case dff:
			pDoc->ls.count_dff++;
			pDoc->ls.create_dff(&pDoc->ls.dff[pDoc->ls.count_dff], pointofpif);
			pDoc->ls.whatgate = nothing;
			Invalidate(1);
			break;
		case jkff:
			pDoc->ls.count_jkff++;
			pDoc->ls.create_jkff(&pDoc->ls.jkff[pDoc->ls.count_jkff], pointofpif);
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
			Invalidate(false);
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

	if (pDoc->ls.pif[pointofpif.x][pointofpif.y].serializegate == dff || pDoc->ls.pif[pointofpif.x][pointofpif.y].serializegate == jkff || pDoc->ls.pif[pointofpif.x][pointofpif.y].serializegate == tff) {
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
		if (pDoc->ls.clock[nIDEvent].value == 0)
			pDoc->ls.clock[nIDEvent].value = 1;
		else
			pDoc->ls.clock[nIDEvent].value = 0;
		//pDoc->ls.calculate_tff(&pDoc->ls.tff[nIDEvent]);
		Invalidate(0);
	//}
	CView::OnTimer(nIDEvent);
}


void CPLS2View::OnDestroy()
{
	CView::OnDestroy();
	KillTimer(0);
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
		if(pDoc->ls.pif[p1.x / 20 - 1][p1.y / 20].value != NULL)
			pDoc->ls.out[pDoc->ls.pif[p1.x / 20][p1.y / 20].output].value = *(pDoc->ls.pif[p1.x / 20 - 1][p1.y / 20].value);
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
	}
	Invalidate();
	CView::OnLButtonDblClk(nFlags, point);
}
