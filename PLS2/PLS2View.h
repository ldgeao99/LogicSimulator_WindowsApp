
// PLS2View.h : CPLS2View 클래스의 인터페이스
//

#pragma once

class CPLS2View : public CView
{
protected: // serialization에서만 만들어집니다.
	CPLS2View();
	DECLARE_DYNCREATE(CPLS2View)

// 특성입니다.
public:
	CPLS2Doc* GetDocument() const;

//로직 시뮬레이터 변수입니다.
public:
	BOOL drawline = FALSE;
	CPoint startline;
	CPoint rbuttonClickedPoint;

	CPoint oldpoint = { 0,0 };
	int garo = 0, sero = 0;
	int line = 0, inout = 0, gate = 0, ff = 0;
	int zero = 0;
	int se[10];
	int repeat = 0;
	int hz = 1000;
	CString m_str;
//로직 시뮬레이터 함수입니다.
	CPoint DividedByTwenty(CPoint point);

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	void drawingline(CPoint start, CPoint end, WhereFixed wherefixed);
	CPoint old_start; //drawingline에서 이전에 그려진걸 지워주기 위한것.
	CPoint old_end; //drawingline에서 이전에 그려진걸 지워주기 위한것.
	WhereFixed old_wherefixed; //drawingline에서 이전에 그려진걸 지워주기 위한것.
// 구현입니다.
public:
	virtual ~CPLS2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void Create_Input_BCLK();
	afx_msg void Create_Output_BCLK();
	afx_msg void Create_AndGate_BCLK();
	afx_msg void Create_XorGate_BCLK();
	afx_msg void Create_NorGate_BCLK();
	afx_msg void Create_NAndGate_BCLK();
	afx_msg void Create_OrGate_BCLK();
	afx_msg void Create_NotGate_BCLK();
	afx_msg void Create_TFF_BCLK();
	afx_msg void Create_Clock_BCLK();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void Create_DFF_BCLK();
	afx_msg void Create_JKFF_BCLK();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnSerialize();
	afx_msg void Onrun();
	afx_msg void Create_7Segment_BCLK();
	afx_msg void On1second();
	afx_msg void Onpoint5second();
	afx_msg void Onpoint25second();
	afx_msg void Onpoint1second();
	afx_msg void Onclockstop();
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void On_TurnToRight();
	afx_msg void On_TurnToLeft();
	afx_msg void On_TurnToTop();
	afx_msg void On_TurnToBottom();
	afx_msg void Onlibready();
	afx_msg void Oncreatelib();
	afx_msg void Ondecoder();
	afx_msg void Onautorun();
	afx_msg void Onrunstop();
	afx_msg void On32825();
	afx_msg void On32826();
//	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTextlabel();
};

#ifndef _DEBUG  // PLS2View.cpp의 디버그 버전
inline CPLS2Doc* CPLS2View::GetDocument() const
   { return reinterpret_cast<CPLS2Doc*>(m_pDocument); }
#endif

