#pragma once
#include "afxdialogex.h"
#include "Structures.h"

/////////////////////////////////////////////////////////////////////////////
// CPhoneNumbersDlg


class CPhoneTypesDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPhoneTypesDlg)
		DECLARE_MESSAGE_MAP()
public:

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_PHONE_TYPES };
#endif

	// Constructor / Destructor
	// ----------------

	CPhoneTypesDlg(PHONE_TYPES& oPhoneTypes,bool editPermission=true, CWnd* pParent = nullptr);
	CPhoneTypesDlg(bool editPermission = true, CWnd* pParent = nullptr);
	virtual ~CPhoneTypesDlg();

	// MFC Overrides
	// ----------------
private:
	void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support
	void OnOK() override;
	BOOL OnInitDialog() override;


	// Methods
	// ----------------
private:
	/// <summary> Determine if fields in dialog are correct</summary>
	/// <returns>True if all data is correct, false otherwise</returns>
	bool ValidateData();
	/// <summary> Reformat the string </summary>
	void Capitalize(CString& oString);
public:
	PHONE_TYPES* GetPhoneType();

protected:

private:
	CEdit m_EdbPhoneType;
	PHONE_TYPES* m_pPhoneType;
	PHONE_TYPES m_oPhoneType;
	bool m_bEditPermission;
};

#define PHONE_TYPE_SIZE PHONE_SIZE-1
#define USE_PHONE_TYPE_FIELD_WITH_BULGARIAN_TEXT L"въведете полето на плана с бълграски текст"
#define EMPTY_PHONE_TYPE_FIELD L"въведете план"
#define SAME_TEXT_AS_INITIAL L"Сменете текста за да се направи корекция"
