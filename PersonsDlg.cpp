#include "pch.h"
#include "PhoneBook.h"
#include "afxdialogex.h"
#include "PersonsDlg.h"
#include <regex>

/////////////////////////////////////////////////////////////////////////////
// CPersonsDlg


IMPLEMENT_DYNAMIC(CPersonsDlg, CDialogEx)
BEGIN_MESSAGE_MAP(CPersonsDlg, CDialogEx)
	ON_COMMAND(IDC_BTN_ADD_NUMBER, &CPersonsDlg::onInsertNumber)
	ON_COMMAND(IDC_BTN_UPDATE_NUMBER, &CPersonsDlg::onUpdateNumber)
	ON_COMMAND(IDC_BTN_DELETE_NUMBER, &CPersonsDlg::onDeleteNumber)
END_MESSAGE_MAP()

// Constructor / Destructor
// ----------------
CPersonsDlg::CPersonsDlg(CPersonsCredentials& oPersonsCredentials, CPersonExtend* pPerson/*=nullptr*/,
	bool bEditPermission/*=true*/, CWnd* pParent /*nullptr*/)
	: CDialogEx(IDD_DLG_PERSONS, pParent),
	m_pPerson(pPerson),
	m_oPersonsCredentials(oPersonsCredentials),
	m_bEditPermitted(bEditPermission)
	
{
	m_bAllocatedPerson = false;
}

CPersonsDlg::~CPersonsDlg()
{
}
// Methods
// ----------------

bool CPersonsDlg::ValidateData()
{
	CArray<CString> oErrors;
	std::wstring oPatternChecker;
	CString strFirstName;
	CString strSurname;
	CString strLastName;
	CString strEGN;
	CString strAdress;
	m_EdbFirstName.GetWindowTextW(strFirstName);
	m_EdbSurname.GetWindowTextW(strSurname);
	m_EdbLastName.GetWindowTextW(strLastName);
	m_EdbEGN.GetWindowTextW(strEGN);
	m_EdbAddress.GetWindowTextW(strAdress);

	std::wregex oSymbolsOnly(L"^[\\u0410-\\u044F\\s]+$");
	std::wregex oNumbersOnly(L"^[\\u0030-\\u0039\\s]+$");
	std::wregex oPatternMixed(L"^[\\u0410-\\u044F\\u0030-\\u0039\\s\\.]+$");

	if (!IsStringValid(oSymbolsOnly, strFirstName))
		oErrors.Add(L"Въведете име на български");

	Capitalize(strFirstName);

	if(!IsStringValid(oSymbolsOnly, strSurname))
		oErrors.Add(L"Въведете презиме на български");

	Capitalize(strSurname);

	if(!IsStringValid(oSymbolsOnly, strLastName))
		oErrors.Add(L"Въведете фамилия на български");

	Capitalize(strLastName);

	if(!IsStringValid(oNumbersOnly, strEGN))
		oErrors.Add(L"Въведете егн");
	if(!IsStringValid(oPatternMixed, strAdress))
		oErrors.Add(L"Въведете адрес на български");


	int nCursel = m_CmbCities.GetCurSel();

	if (nCursel == INDEX_NOT_FOUND)
		oErrors.Add(L"Изберете град");

	if (!oErrors.IsEmpty()) {
		for (long lIndexer(0); (INT_PTR)lIndexer < oErrors.GetCount(); lIndexer++)
			AfxMessageBox(oErrors.GetAt(lIndexer), MB_OK | MB_ICONEXCLAMATION);

		return FALSE;
	}

	//Copy data 
	_tcscpy_s(m_pPerson->m_oRecPerson.szAddress, strAdress);
	_tcscpy_s(m_pPerson->m_oRecPerson.szEGN, strEGN);
	_tcscpy_s(m_pPerson->m_oRecPerson.szLastName, strLastName);
	_tcscpy_s(m_pPerson->m_oRecPerson.szSurname, strSurname);
	_tcscpy_s(m_pPerson->m_oRecPerson.szFirstName, strFirstName);

	long lCityID= (long) m_CmbCities.GetItemData(nCursel);

	m_pPerson->m_oRecPerson.lCityID = lCityID;

	return TRUE;

}

void CPersonsDlg::DisplayData()
{
	for (INT_PTR nIndexer(0); nIndexer < m_pPerson->m_oPhoneNumbersArray.GetCount(); nIndexer++) {

		PHONE_NUMBERS* pPhoneNumbers = m_pPerson->m_oPhoneNumbersArray.GetAt(nIndexer);

		if (!pPhoneNumbers)
			continue;

		m_LscPhoneNumbers.InsertItem((int)nIndexer, pPhoneNumbers->szPhone);

		CString strTypeID;
		m_oPersonsCredentials.GetStringToPhoneTypeMap().Lookup(pPhoneNumbers->lPhoneTypeID, strTypeID);
		m_LscPhoneNumbers.SetItemText((int)nIndexer, PHONE_TYPE_COLUMN, strTypeID);

	}
}

bool CPersonsDlg::IsStringValid(const std::wregex& oPattern, CString& strArg)
{
	strArg.Trim();

	if (strArg.IsEmpty()) 
		return FALSE;

	std::wstring oPatternChecker = strArg.GetString();

	if (!std::regex_match(oPatternChecker, oPattern))
		return FALSE;

	return TRUE;
}

void CPersonsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDB_ADDRESS, m_EdbAddress);
	DDX_Control(pDX, IDC_EDB_SURNAME, m_EdbSurname);
	DDX_Control(pDX, IDC_EDB_EGN, m_EdbEGN);
	DDX_Control(pDX, IDC_EDB_LAST_NAME, m_EdbLastName);
	DDX_Control(pDX, IDC_EDB_FIRST_NAME, m_EdbFirstName);
	DDX_Control(pDX, IDC_LSC_PHONE_NUMBERS, m_LscPhoneNumbers);
	DDX_Control(pDX, IDC_CMB_CITIES, m_CmbCities);
	DDX_Control(pDX, IDC_BTN_ADD_NUMBER, m_BtnAddNumber);
	DDX_Control(pDX, IDC_BTN_UPDATE_NUMBER, m_BtnUpdateNumber);
	DDX_Control(pDX, IDC_BTN_DELETE_NUMBER, m_BtnDeleteNumber);
}

// CPersonsDlg message handlers



void CPersonsDlg::onInsertNumber()
{
	if (!m_bEditPermitted)
		return;

	PHONE_NUMBERS oPhoneNumbers;

	CPhoneNumbersDlg oPhoneNumbersdlg(m_oPersonsCredentials.GetPhoneTypesArray(), oPhoneNumbers);

	if (oPhoneNumbersdlg.DoModal() == IDCANCEL)
		return;

	oPhoneNumbers = oPhoneNumbersdlg.GetNumber();

	int nCount= m_LscPhoneNumbers.GetItemCount();

	m_LscPhoneNumbers.InsertItem(nCount, oPhoneNumbers.szPhone);

	CString strTypeID;
	m_oPersonsCredentials.GetStringToPhoneTypeMap().Lookup(oPhoneNumbers.lPhoneTypeID, strTypeID);
	m_LscPhoneNumbers.SetItemText(nCount, PHONE_TYPE_COLUMN, strTypeID);
	
	PHONE_NUMBERS* pPhoneNumbers = new PHONE_NUMBERS(oPhoneNumbers);

	m_pPerson->m_oPhoneNumbersArray.Add(pPhoneNumbers);

}

void CPersonsDlg::onUpdateNumber()
{
	if (!m_bEditPermitted)
		return;

	int lIndexer = GetRowIndex();

	if (lIndexer == INDEX_NOT_FOUND) {
		AfxMessageBox(L"Изберете телефонен номер");
		return;
	}
	CString strPhoneString= m_LscPhoneNumbers.GetItemText(lIndexer, PHONE_NUMBER_COLUMN);

	PHONE_NUMBERS* pPhoneNumber=nullptr;

	for (INT_PTR nIndexer(0); nIndexer < m_pPerson->m_oPhoneNumbersArray.GetCount(); nIndexer++) {
		PHONE_NUMBERS* pPhoneNumberSearch = m_pPerson->m_oPhoneNumbersArray.GetAt(nIndexer);

		if (!_tcscmp(strPhoneString, pPhoneNumberSearch->szPhone)) {
			pPhoneNumber = pPhoneNumberSearch;
			break;
		}
	}
	if (!pPhoneNumber) {
		return;
	}

	PHONE_NUMBERS& oPhoneNumbers = *pPhoneNumber;

	CPhoneNumbersDlg oPhoneNumbersdlg(m_oPersonsCredentials.GetPhoneTypesArray(), oPhoneNumbers);

	if (oPhoneNumbersdlg.DoModal() == IDCANCEL)
		return;


	m_LscPhoneNumbers.SetItemText(lIndexer, PHONE_NUMBER_COLUMN, oPhoneNumbers.szPhone);

	CString strTypeID;
	m_oPersonsCredentials.GetStringToPhoneTypeMap().Lookup(oPhoneNumbers.lPhoneTypeID, strTypeID);
	m_LscPhoneNumbers.SetItemText(lIndexer, PHONE_TYPE_COLUMN, strTypeID);

	m_LscPhoneNumbers.Update(lIndexer);

}
long CPersonsDlg::GetRowIndex()
{
	POSITION pos = m_LscPhoneNumbers.GetFirstSelectedItemPosition();
	if (!pos)
		return INDEX_NOT_FOUND;

	int lIndexer = m_LscPhoneNumbers.GetNextSelectedItem(pos);
	if (lIndexer == INDEX_NOT_FOUND)
		return INDEX_NOT_FOUND;

	return lIndexer;
}
void CPersonsDlg::onDeleteNumber()
{
	if (!m_bEditPermitted)
		return;

	int nIndexer = GetRowIndex();

	if (nIndexer == INDEX_NOT_FOUND) {
		AfxMessageBox(L"Изберете номер");
		return;
	}

	int nCount = m_LscPhoneNumbers.GetItemCount();

	if (nCount == 1) {
		AfxMessageBox(L"Не може да се изтрие единствения останал номер");
		AfxMessageBox(L"За да се изтрият всички телефонни номера, трябва да бъде изтрит човека",MB_ICONINFORMATION);
		return;
	}

	CString strNumberToDelete = m_LscPhoneNumbers.GetItemText(nIndexer, PHONE_NUMBER_COLUMN);

	for (long lIndexer(0); lIndexer < m_pPerson->m_oPhoneNumbersArray.GetCount(); lIndexer++) {
		PHONE_NUMBERS* pPhoneNumber = m_pPerson->m_oPhoneNumbersArray.GetAt(lIndexer);
		if (!pPhoneNumber)
			continue;
		if (!_tcscmp(pPhoneNumber->szPhone, strNumberToDelete)) {
			_tcscpy_s(pPhoneNumber->szPhone,EMPTY_NUMBER);
			break;
		}
	}
	m_LscPhoneNumbers.DeleteItem(nIndexer);
}

void CPersonsDlg::MapPhoneTypeIDToString()
{
	for (INT_PTR nIndexer(0); nIndexer < m_oPersonsCredentials.GetPhoneTypesArray().GetCount(); nIndexer++) {
		PHONE_TYPES* pPhoneType = m_oPersonsCredentials.GetPhoneTypesArray().GetAt(nIndexer);
		if (!pPhoneType)
			continue;
		m_oPersonsCredentials.GetStringToPhoneTypeMap().SetAt(pPhoneType->lID, pPhoneType->szPhoneType);
	}
}

void CPersonsDlg::OnOK()
{
	if (!ValidateData())
		return;

	if (!m_LscPhoneNumbers.GetItemCount()) {
		AfxMessageBox(L"Абонатът трябва да има поне един номер");
		return;
	}
	CDialogEx::OnOK();
}

void CPersonsDlg::Capitalize(CString& oString)
{
	//Capitilize first letter
	if (oString.GetAt(0) > L'Я')
		oString.SetAt(0, oString.GetAt(0) - 0x20);

	//LowerCase all others
	for (long lIndexer(1); (int)lIndexer < oString.GetLength(); lIndexer++) {
		if (oString.GetAt(lIndexer) < L'а')
			oString.SetAt(lIndexer, oString.GetAt(lIndexer) + 0x20);
	}
}
CPersonExtend& CPersonsDlg::GetPerson()
{
	return *m_pPerson;
}


BOOL CPersonsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	
	m_EdbAddress.SetLimitText(ADDRESS_LENGTH);
	m_EdbSurname.SetLimitText(NAME_LENGTH);
	m_EdbEGN.SetLimitText(EGN_LENGTH);
	m_EdbLastName.SetLimitText(NAME_LENGTH);
	m_EdbFirstName.SetLimitText(NAME_LENGTH);


	m_LscPhoneNumbers.ModifyStyle(0, LVS_REPORT | LVS_SINGLESEL);
	m_LscPhoneNumbers.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_LscPhoneNumbers.InsertColumn(PHONE_NUMBER_COLUMN, _T("Телефон"), LVCFMT_LEFT, PIXEL_WIDTH_250);
	m_LscPhoneNumbers.InsertColumn(PHONE_TYPE_COLUMN, _T("План"), LVCFMT_LEFT, PIXEL_WIDTH_250);

	if (!m_bEditPermitted) {
		m_EdbAddress.EnableWindow(false);
		m_EdbSurname.EnableWindow(false);
		m_EdbEGN.EnableWindow(false);
		m_EdbLastName.EnableWindow(false);
		m_EdbFirstName.EnableWindow(false);
		m_CmbCities.EnableWindow(false);
		m_LscPhoneNumbers.EnableWindow(false);
		m_BtnAddNumber.EnableWindow(false);
		m_BtnUpdateNumber.EnableWindow(false);
		m_BtnDeleteNumber.EnableWindow(false);
		SetWindowTextW(L"Информация за човек (Преглед)");
	}
	if (!m_pPerson) {
		m_bAllocatedPerson = true;
		m_pPerson = new CPersonExtend;
	}
	
	m_EdbAddress.SetWindowTextW(m_pPerson->m_oRecPerson.szAddress);
	m_EdbSurname.SetWindowTextW(m_pPerson->m_oRecPerson.szSurname);
	m_EdbEGN.SetWindowTextW(m_pPerson->m_oRecPerson.szEGN);
	m_EdbLastName.SetWindowTextW(m_pPerson->m_oRecPerson.szLastName);
	m_EdbFirstName.SetWindowTextW(m_pPerson->m_oRecPerson.szFirstName);
	
	SetCityComboboxItems();
	
	DisplayData();

	return TRUE;
}
void CPersonsDlg::SetCityComboboxItems()
{
	for (INT_PTR nIndexer(0); nIndexer < m_oPersonsCredentials.GetCitiesArray().GetCount(); nIndexer++) {

		CITIES oCities = *m_oPersonsCredentials.GetCitiesArray().GetAt(nIndexer);

		CString strCityName = oCities.szCityName;
		CString strResidenceName = oCities.szTownResidence;

		CString strCityOption;
		strCityOption.Format(L"%s (област %s)",
			static_cast<const wchar_t*>(strCityName),
			static_cast<const wchar_t*>(strResidenceName));
		m_CmbCities.AddString(strCityOption);
		m_CmbCities.SetItemData((int)nIndexer, oCities.lID);

		if (oCities.lID == m_pPerson->m_oRecPerson.lCityID)
			m_CmbCities.SetCurSel((int)nIndexer);
	}
}

void CPersonsDlg::OnCancel()
{
	CDialogEx::OnCancel();
}
