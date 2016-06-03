// TextLabel.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "PLS2.h"
#include "TextLabel.h"
#include "afxdialogex.h"


// TextLabel 대화 상자입니다.

IMPLEMENT_DYNAMIC(TextLabel, CDialog)

TextLabel::TextLabel(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG1, pParent)
	, m_label2(0)
{

}

TextLabel::~TextLabel()
{
}

void TextLabel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_str);
}


BEGIN_MESSAGE_MAP(TextLabel, CDialog)
	ON_BN_CLICKED(IDOK, &TextLabel::OnBnClickedOk)
END_MESSAGE_MAP()


// TextLabel 메시지 처리기입니다.


BOOL TextLabel::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetDlgItemText(IDC_EDIT1, m_str);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void TextLabel::OnOK()
{
	GetDlgItemText(IDC_EDIT1, m_str);
	CDialog::OnOK();
}


void TextLabel::OnBnClickedOk()
{
	EndDialog(IDC_EDIT1);
	CDialog::OnOK();
}
