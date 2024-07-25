#pragma once
#include "afxdialogex.h"
#define CITY_FIELD_SIZE 32

// CCitiesDlg dialog

class CCitiesDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCitiesDlg)

public:
	CCitiesDlg(CWnd* pParent = nullptr,
		const CString& cityName = _T(""),
		const CString& townResidence = _T(""));
	virtual ~CCitiesDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_CITIES };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	void OnOK();
	DECLARE_MESSAGE_MAP()
//Members----------------------------------------------------------------------------------------------------
public:
	CEdit m_EdbName;
	CEdit m_EdbResidence;
	CString m_szCityName;
	CString m_szTownResidence;


private:
	CString m_initialCityName;
	CString m_initialTownResidence;
//Member functions-------------------------------------------------------------------------------------------
	BOOL ValidateData();
	BOOL OnInitDialog() override;

};
