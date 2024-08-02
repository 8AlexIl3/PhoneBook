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
	CCitiesDlg(CITIES& oCities, CWnd* pParent = nullptr);
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
	/// <summary> Edit box for cityName </summary>
	CEdit m_EdbName;
	/// <summary> Edit box for TownResidence </summary>
	CEdit m_EdbResidence;
	/// <summary> String for cityName </summary>
	CITIES* m_pCities;
	/// <summary> Checks to see if info is updated </summary>
	CITIES m_oCities;
};


#define CITY_FIELD_SIZE 32
#define USE_CITY_FIELD_WITH_BULGARIAN_TEXT L"�������� ������ �� ����� � ��������� �����"
#define EMPTY_CITY_FIELD L"�������� ����"
#define USE_RESIDENCE_FIELD_WITH_BULGARIAN_TEXT L"�������� ������ �� �������� � ��������� �����"
#define EMPTY_RESIDENCE_FIELD L"�������� ������"
#define SAME_TEXT_AS_INITIAL L"������� ������ � ����� �� ��������"
