#include "pch.h"
#include "PhoneBook.h"
#include "afxdialogex.h"
#include "CitiesDlg.h"
#include "CitiesData.h"
#include <regex> 

/////////////////////////////////////////////////////////////////////////////
// CCitiesDlg

IMPLEMENT_DYNAMIC(CCitiesDlg, CDialogEx)

BEGIN_MESSAGE_MAP(CCitiesDlg, CDialogEx)
END_MESSAGE_MAP()


// Constructor / Destructor
// ----------------

CCitiesDlg::CCitiesDlg(CWnd* pParent)
	: CDialogEx(IDD_DLG_CITIES, pParent)
{
}

CCitiesDlg::CCitiesDlg(const CITIES & oCities, CWnd * pParent)
	: CDialogEx(IDD_DLG_CITIES, pParent),
	m_initialCityName(oCities.szCityName),
	m_initialTownResidence(oCities.szTownResidence)
{
}

CCitiesDlg::~CCitiesDlg()
{
}


//MFC Overrides
// ----------------

void CCitiesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDB_CITIES_NAME, m_EdbName);
	DDX_Control(pDX, IDC_EDB_CITIES_RESIDENCE, m_EdbResidence);
}

void CCitiesDlg::OnOK()
{
	UpdateData(TRUE);

	m_EdbName.GetWindowTextW(m_szCityName);
	m_EdbResidence.GetWindowTextW(m_szTownResidence);
	if (!ValidateData()) {
		return;
	}

	CDialogEx::OnOK();
}

BOOL CCitiesDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_EdbResidence.SetLimitText(CITY_FIELD_SIZE);
	m_EdbName.SetLimitText(CITY_FIELD_SIZE);
	m_EdbName.SetWindowTextW(m_initialCityName);
	m_EdbResidence.SetWindowTextW(m_initialTownResidence);
	UpdateData(TRUE);

	return TRUE;
}


//Methods
// ----------------

bool CCitiesDlg::ValidateData() {
	CArray<CString> oErrors;
	std::wstring oPatternChecker;

	//oPattern that allows only bulgarian and whitespaces
	std::wregex oPattern(L"^[\\u0410-\\u044F\\s]+$");

	m_szCityName.Trim();

	oPatternChecker = m_szCityName.GetString();
	if (m_szCityName.IsEmpty()) {
		EMPTY_CITY_FIELD;
	}
	else if (!std::regex_match(oPatternChecker, oPattern)) {
		USE_CITY_FIELD_WITH_BULGARIAN_TEXT;
	}
	Capitalize(m_szCityName);

	m_szTownResidence.Trim();

	oPatternChecker = m_szTownResidence.GetString();

	if (m_szTownResidence.IsEmpty()) {
		EMPTY_RESIDENCE_FIELD;
	}
	else if (!std::regex_match(oPatternChecker, oPattern)) {
		USE_RESIDENCE_FIELD_WITH_BULGARIAN_TEXT;
	}
	else if (m_szCityName == m_initialCityName &&
		m_szTownResidence == m_initialTownResidence) {
		SAME_TEXT_AS_INITIAL;
	}

	Capitalize(m_szTownResidence);

	if (!oErrors.IsEmpty()) {
		for (long lIndexer(0); (INT_PTR)lIndexer < oErrors.GetCount(); lIndexer++) {
			AfxMessageBox(oErrors.GetAt(lIndexer), MB_OK | MB_ICONEXCLAMATION);
		}

		return FALSE;
	}

	return TRUE;

}

void CCitiesDlg::Capitalize(CString& oString)
{
	//Capitilize first letter
	if (oString.GetAt(0) > L'ß') {
		oString.SetAt(0, oString.GetAt(0) - 0x20);
	}
	//LowerCase all others
	for (long lIndexer(1);(int) lIndexer < oString.GetLength(); lIndexer++) {
		if (oString.GetAt(lIndexer) < L'à') {
			oString.SetAt(lIndexer, oString.GetAt(lIndexer) + 0x20);
		}
	}
}

const CString& CCitiesDlg::GetCityName()
{
	return m_szCityName;
}

const CString& CCitiesDlg::GetTownResidence()
{
	return m_szTownResidence;
}

	