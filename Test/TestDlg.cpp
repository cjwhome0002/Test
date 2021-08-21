
// TestDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Test.h"
#include "TestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestDlg 대화 상자



CTestDlg::CTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_PATIENT_LIST, m_patient_list);
	DDX_Control(pDX, IDC_PATIENT_INFO_LIST, m_patient_info_list);
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &CTestDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTestDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_SAVE_BTN, &CTestDlg::OnBnClickedSaveBtn)
END_MESSAGE_MAP()


// CTestDlg 메시지 처리기

BOOL CTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	m_patient_info_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	LV_COLUMN add_column;

	add_column.mask = LVCF_TEXT | LVCF_WIDTH;

	add_column.pszText = L"이름";
	add_column.cx = 80;
	m_patient_info_list.InsertColumn(0, &add_column);

	add_column.pszText = L"환자번호";
	add_column.cx = 80;
	m_patient_info_list.InsertColumn(1, &add_column);

	add_column.pszText = L"알림 내용";
	add_column.cx = 200;
	m_patient_info_list.InsertColumn(2, &add_column);

	add_column.pszText = L"알림 시간";
	add_column.cx = 80;
	m_patient_info_list.InsertColumn(3, &add_column);

	add_column.pszText = L"알림 날짜";
	add_column.cx = 150;
	m_patient_info_list.InsertColumn(4, &add_column);


	SetTimer(1, 10000, NULL);
	
    /*
	HWND h_wnd = ::FindWindowEx(NULL, NULL, L"TfmPNameCard", NULL);
	if (h_wnd != NULL) {
		
		int len = ::SendMessage(h_wnd, WM_GETTEXTLENGTH, 0, 0);
		wchar_t* p_name = new wchar_t[len + 1];
		::SendMessage(h_wnd, WM_GETTEXT, len + 1, (LPARAM)p_name);
		
		CString str = p_name;
		delete[] p_name;
			SetDlgItemText(IDC_EDIT1, str);
		}
		else SetDlgItemInt(IDC_EDIT1, 1);
	
	*/

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTestDlg::OnDestroy()
{
	KillTimer(1);
	CDialogEx::OnDestroy();
	
}


LRESULT CTestDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_PAINT) {
		HWND h_wnd = ::FindWindowEx(NULL, NULL, L"TfmMain", NULL);
		if (h_wnd != NULL) {
			int len = ::SendMessage(h_wnd, WM_GETTEXTLENGTH, 0, 0);
			wchar_t* p_name = new wchar_t[len + 1];
			::SendMessage(h_wnd, WM_GETTEXT, len + 1, (LPARAM)p_name);
			//이름만 추출하는 코드
			wchar_t* p = p_name;
			wchar_t* p_start = p_name;
			while (*p) {
				if (*p == '-') {
					p_start = p + 1;
					while (*p != ' ')p++;
					*p = 0;
					CString str = p_start;
					SetDlgItemText(IDC_NAME_EDIT, str);
					break;
				}
				p++;
				
			}
			//CString str;
			delete[] p_name;
			
			h_wnd = ::FindWindowEx(h_wnd, NULL, L"MDIClient", NULL);
			if (h_wnd != NULL) {
				h_wnd = ::FindWindowEx(h_wnd, NULL, L"TfmPNameCard", NULL);
				if (h_wnd != NULL) {
					len = ::SendMessage(h_wnd, WM_GETTEXTLENGTH, 0, 0);
					wchar_t* p_num = new wchar_t[len + 1];
					::SendMessage(h_wnd, WM_GETTEXT, len + 1, (LPARAM)p_num);
					//환자번호만 추출
					wchar_t* p_n = p_num;
					wchar_t* n_start = p_num;
					while (*p_n) {
						if (*p_n == ':') {
							n_start = p_n + 2;
							while (*p_n != ']')p_n++;
							*p_n = 0;
							CString str = n_start;
							SetDlgItemText(IDC_NUM_EDIT, str);
							break;
						}
						p_n++;

					}
					//str = p_num;
					delete[] p_num;
					//SetDlgItemText(IDC_NUM_EDIT, str);

					if (m_is_first == 0) {
						//m_prev_str = str;
						m_is_first = 1;
					}
					//if (m_prev_str != str) {
						//새로운 환자가 호출되면 해야할일을 적는다
					//}
				}
				//else SetDlgItemInt(IDC_EDIT1, 1);

			}
		}
	}
	return CDialogEx::WindowProc(message, wParam, lParam);
}


void CTestDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1) {
		Invalidate();
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CTestDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//CDialogEx::OnOK();
}


void CTestDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}


void CTestDlg::OnBnClickedSaveBtn()
{
	CString str;

	int index = m_patient_info_list.GetItemCount();

	LV_ITEM add_item;
	add_item.mask = LVIF_TEXT;
	add_item.iItem = index;
	m_patient_info_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	GetDlgItemText(IDC_NAME_EDIT, str);
	add_item.pszText = (wchar_t*)(const wchar_t*)str;
	add_item.iSubItem = 0;

	m_patient_info_list.InsertItem(&add_item);

	GetDlgItemText(IDC_NUM_EDIT, str);
	add_item.pszText = (wchar_t*)(const wchar_t*)str;
	add_item.iSubItem = 1;

	m_patient_info_list.SetItem(&add_item);

	GetDlgItemText(IDC_CONTENT_EDIT, str);
	add_item.pszText = (wchar_t*)(const wchar_t*)str;
	add_item.iSubItem = 2;

	m_patient_info_list.SetItem(&add_item);

	GetDlgItemText(IDC_DAY_EDIT, str);
	add_item.pszText = (wchar_t*)(const wchar_t*)str;
	add_item.iSubItem = 3; 

	m_patient_info_list.SetItem(&add_item);

	//이후에는 계산된 날짜를 넣는다
}
