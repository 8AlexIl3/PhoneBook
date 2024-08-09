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
	m_pCities = &m_oCities;
}

CCitiesDlg::CCitiesDlg(CITIES & oCities, CWnd * pParent)
	: CDialogEx(IDD_DLG_CITIES, pParent),
	m_pCities(&oCities),
	m_oCities(oCities)
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
	m_EdbName.SetWindowTextW(m_oCities.szCityName);
	m_EdbResidence.SetWindowTextW(m_oCities.szTownResidence);

	return TRUE;
}


//Methods
// ----------------

bool CCitiesDlg::ValidateData() {
	CArray<CString> oErrors;
	std::wstring oPatternChecker;
	CString strNameGetter;
	CString strResidenceGetter;
	m_EdbName.GetWindowTextW(strNameGetter);
	//oPattern that allows only bulgarian and whitespaces
	std::wregex oPattern(L"^[\\u0410-\\u044F\\s]+$");

	strNameGetter.Trim();

	oPatternChecker = strNameGetter.GetString();
	if (strNameGetter.IsEmpty()) {
		oErrors.Add(EMPTY_CITY_FIELD);
	}
	else if (!std::regex_match(oPatternChecker, oPattern)) {
		oErrors.Add(USE_CITY_FIELD_WITH_BULGARIAN_TEXT);
	}

	Capitalize(strNameGetter);

	m_EdbResidence.GetWindowTextW(strResidenceGetter);

	strResidenceGetter.Trim();

	oPatternChecker = strResidenceGetter.GetString();

	if (strResidenceGetter.IsEmpty()) {
		oErrors.Add(EMPTY_RESIDENCE_FIELD);
	}
	else if (!std::regex_match(oPatternChecker, oPattern)) {
		oErrors.Add(USE_RESIDENCE_FIELD_WITH_BULGARIAN_TEXT);
	}
	else if (!(_tcscmp(strNameGetter, m_oCities.szCityName)||
		_tcscmp(strResidenceGetter, m_oCities.szTownResidence)
		)) {
		oErrors.Add(SAME_TEXT_AS_INITIAL);
	}

	Capitalize(strResidenceGetter);

	if (!oErrors.IsEmpty()) {
		for (long lIndexer(0); (INT_PTR)lIndexer < oErrors.GetCount(); lIndexer++) {
			AfxMessageBox(oErrors.GetAt(lIndexer), MB_OK | MB_ICONEXCLAMATION);
		}

		return FALSE;
	}
	_tcscpy_s(m_pCities->szCityName, strNameGetter);
	_tcscpy_s(m_pCities->szTownResidence, strResidenceGetter);

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

 CITIES* CCitiesDlg::GetCity()
{
	return m_pCities;
}



	