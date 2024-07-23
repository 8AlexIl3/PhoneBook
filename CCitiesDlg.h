#pragma once
#include "afxdialogex.h"
#define CITY_FIELD_SIZE 32

// CCitiesDlg dialog

class CCitiesDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCitiesDlg)

public:
	CCitiesDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CCitiesDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_CITIES };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void OnOK();
	DECLARE_MESSAGE_MAP()
public:
	// City name to be entered
	CEdit m_EdbName;
	CEdit m_EdbResidence;
	CString m_szCityName;
	CString m_szTownResidence;
	CListCtrl m_ListControl;
	virtual BOOL OnInitDialog();
};
