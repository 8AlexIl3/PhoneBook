#pragma once


/////////////////////////////////////////////////////////////////////////////
// CCitiesDlg

#include "afxdialogex.h"
#include "Structures.h"


class CCitiesDlg : public CDialogEx
{

// Macros
// ----------------
	DECLARE_DYNAMIC(CCitiesDlg)
	DECLARE_MESSAGE_MAP()


// Constants
// ----------------
private:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_CITIES };
#endif


// Constructor / Destructor
// ----------------
public:
	CCitiesDlg(CWnd* pParent = nullptr);
	/// <param name="oCities">City to fill the fields if redaction is needed</param>
	CCitiesDlg(CITIES& oCities, bool bEditPermission = true, CWnd* pParent = nullptr);
	virtual ~CCitiesDlg();


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
	CITIES* GetCity();

// Members
// ----------------
private:
	CEdit m_EdbName;
	CEdit m_EdbResidence;
	CITIES* m_pCities;
	CITIES m_oCities;
	bool m_bEditPermission;

};


#define CITY_FIELD_SIZE NAME_SIZE-1
#define USE_CITY_FIELD_WITH_BULGARIAN_TEXT L"въведете полето на града с бълграски текст"
#define EMPTY_CITY_FIELD L"въведете град"
#define USE_RESIDENCE_FIELD_WITH_BULGARIAN_TEXT L"въведете полето на областта с бълграски текст"
#define EMPTY_RESIDENCE_FIELD L"въведете област"
#define SAME_TEXT_AS_INITIAL L"Сменете текста в някое от полетата"
