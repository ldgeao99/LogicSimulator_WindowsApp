// DlgSelLib.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "PLS2.h"
#include "DlgSelLib.h"
#include "afxdialogex.h"


// DlgSelLib 대화 상자입니다.

IMPLEMENT_DYNAMIC(DlgSelLib, CDialogEx)

DlgSelLib::DlgSelLib(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

DlgSelLib::~DlgSelLib()
{
}

void DlgSelLib::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(DlgSelLib, CDialogEx)
END_MESSAGE_MAP()


// DlgSelLib 메시지 처리기입니다.


BOOL DlgSelLib::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	CFileFind finder;
	CString s;
	BOOL bWorking = finder.FindFile(_T("res\\lib_*.mdi"));

	while (bWorking) {
		bWorking = finder.FindNextFile();
		//TRACE(_T("[%s]\n"), (LPCTSTR)finder.GetFileName()); //디렉토리인경우 [] 로 보여줌.
		m_list.AddString(finder.GetFileTitle());
	}

	m_list.SetCurSel(0); // 첫번째 항목이 디폴트로 선택되어있게 함.
	SetWindowText(_T("라이브러리 선택(lib_*.mdi)")); // 다이어로그 창 이름.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
