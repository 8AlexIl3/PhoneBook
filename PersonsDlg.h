#pragma once
#include "afxdialogex.h"
#include "Person.h"

// CPersonsDlg dialog

class CPersonsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPersonsDlg)

public:
	CPersonsDlg(CWnd* pParent = nullptr);
	/// <param name="oCities">City to fill the fields if redaction is needed</param>
	CPersonsDlg(CPerson& oPerson, CWnd* pParent = nullptr);
	virtual ~CPersonsDlg();
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_PERSONS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	CEdit m_EdbAddress;
	CEdit m_EdbSurname;
	CEdit m_EdbEGN;
	CEdit m_EdbLastName;
	CEdit m_EdbFirstName;
	CListCtrl m_LscPhoneNumbers;
	CComboBox m_CmbCities;

	CPerson m_oPerson;
	CPerson* m_pPerson;
};
