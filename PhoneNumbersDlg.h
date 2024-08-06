#pragma once
#include "afxdialogex.h"
#include "Structures.h"

// CPhoneNumbersDlg dialog

class CPhoneNumbersDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPhoneNumbersDlg)

public:
	CPhoneNumbersDlg(CPhoneTypesArray* oPhoneTypeArray, PHONE_NUMBERS* oPhoneNumbers=nullptr,CWnd* pParent = nullptr);   // standard constructor
	virtual ~CPhoneNumbersDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_PHONE_NUMBERS };
#endif


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	CPhoneTypesArray* m_pPhoneTypeArray;
	PHONE_NUMBERS* m_pPhoneNumbers;
	CEdit m_EdbPhoneNumber;
	CComboBox m_CmbPhoneType;
public:
	PHONE_NUMBERS& GetNumber();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
};
