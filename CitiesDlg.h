#pragma once
#include "afxdialogex.h"
#include "Structures.h"
#define CITY_FIELD_SIZE 32

// CCitiesDlg dialog
#define CITY_BULGARIAN_TEXT_ERROR L"Грешка: въведете полето на града с бълграски текст"
class CCitiesDlg : public CDialogEx
{

	//Macros---------------------------------------------------------------------------------------------------------
	DECLARE_DYNAMIC(CCitiesDlg)
	DECLARE_MESSAGE_MAP()

private:
	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_CITIES };
#endif
//Constructors and destructors
public:
	CCitiesDlg(CWnd* pParent = nullptr);
	CCitiesDlg(const CITIES& oCity, CWnd* pParent = nullptr);
	virtual ~CCitiesDlg();

	//Overrides--------------------------------------------------------------------------------------------------
protected:
	void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support
	void OnOK() override;
	BOOL OnInitDialog() override;


	//Member functions-------------------------------------------------------------------------------------------
private:
	BOOL ValidateData();
	void Capitalize(CString& oString);

public:
	const CString& GetCityName();
	const CString& GetTownResidence();
	//Members----------------------------------------------------------------------------------------------------
private:
	CEdit m_EdbName;
	CEdit m_EdbResidence;
	CString m_szCityName;
	CString m_szTownResidence;
	CString m_initialCityName;
	CString m_initialTownResidence;
};
