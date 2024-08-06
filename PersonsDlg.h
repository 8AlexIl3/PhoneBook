#pragma once
#include "afxdialogex.h"
#include "Person.h"
#include "PhoneNumbersDlg.h"
#include <regex>
// CPersonsDlg dialog

class CPersonsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPersonsDlg)
	DECLARE_MESSAGE_MAP()

public:
	/// <param name="oCities">City to fill the fields if redaction is needed</param>
	CPersonsDlg(CCitiesArray& oCitiesArray, CPhoneTypesArray* pPhoneTypes, CPerson* pPerson = nullptr, CWnd* pParent = nullptr);
	virtual ~CPersonsDlg();

	
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_PERSONS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog() override;

private:
	CEdit m_EdbAddress;
	CEdit m_EdbSurname;
	CEdit m_EdbEGN;
	CEdit m_EdbLastName;
	CEdit m_EdbFirstName;
	CListCtrl m_LscPhoneNumbers;
	CComboBox m_CmbCities;

	CPhoneTypesArray* m_pPhoneTypes;
	CPerson* m_pPerson;
	CCitiesArray* m_pCitiesArray;

	bool bAllocatedCity;

	void onInsertNumber();
	void onUpdateNumber();
	void onDeleteNumber();
	bool ValidateData();
	void DisplayData();
	bool IsStringValid(const std::wregex& oPattern, CString& strArg);
public:
	virtual void OnOK();
	CPerson& GetPerson();
	virtual void OnCancel();
};
