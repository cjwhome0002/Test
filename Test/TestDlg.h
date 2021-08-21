
// TestDlg.h: 헤더 파일
//

#pragma once


// CTestDlg 대화 상자
class CTestDlg : public CDialogEx
{
private:
	char m_is_first = 0;//대화상자가 처음 열렸을때가 0
	CString m_prev_str;//현재 열려있는 환자번호정보를 기록
// 생성입니다.
public:
	CTestDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CListBox m_patient_list;
	CListCtrl m_patient_info_list;
	afx_msg void OnBnClickedSaveBtn();
};
