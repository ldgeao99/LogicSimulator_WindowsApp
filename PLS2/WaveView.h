#pragma once



// CWaveView 뷰입니다.

class CWaveView : public CScrollView
{
	DECLARE_DYNCREATE(CWaveView)

protected:
	CWaveView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CWaveView();

	//로직시뮬레이터 변수
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

	//wave변수
	BOOL drawing = FALSE;
	CArray <CPoint, CPoint&> *inoldpoint;
	int inold[300];
	CArray <CPoint, CPoint&> *clockoldpoint;
	int clockold[300];
	CArray <CPoint, CPoint&> *outoldpoint;
	int outold[300];
	CPoint indexpoint;
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void OnDraw(CDC* pDC);      // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual void OnInitialUpdate();     // 생성된 후 처음입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void Onwaveserial();
	afx_msg void Onwaverunning();
	afx_msg void On32840();
	afx_msg void Onwavehz2();
	afx_msg void Onwavehz3();
	afx_msg void Onwavehz4();
	afx_msg void Onready();
	afx_msg void Onstart();
	afx_msg void Onpause();
	afx_msg void Ondelete();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CPoint DividedByTwenty(CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void Onwavehzstop();
	afx_msg void Onupedge();
	afx_msg void Ondownedge();
	afx_msg void OnUpdate32840(CCmdUI *pCmdUI);
	afx_msg void OnUpdatewavehz2(CCmdUI *pCmdUI);
	afx_msg void OnUpdatewavehz3(CCmdUI *pCmdUI);
	afx_msg void OnUpdatewavehz4(CCmdUI *pCmdUI);
	afx_msg void OnUpdateupedge(CCmdUI *pCmdUI);
	afx_msg void OnUpdatedownedge(CCmdUI *pCmdUI);
};


