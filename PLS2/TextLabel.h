#pragma once
#include "afxwin.h"


// TextLabel 대화 상자입니다.

class TextLabel : public CDialog
{
	DECLARE_DYNAMIC(TextLabel)

public:
	TextLabel(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~TextLabel();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_str;
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnBnClickedOk();
	char m_label2;
};
