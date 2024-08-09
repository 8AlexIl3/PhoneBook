// PhoneNumbersDlg.cpp : implementation file
//

#include "pch.h"
#include "PhoneBook.h"
#include "afxdialogex.h"
#include "PhoneNumbersDlg.h"


// CPhoneNumbersDlg dialog

IMPLEMENT_DYNAMIC(CPhoneNumbersDlg, CDialogEx)

CPhoneNumbersDlg::CPhoneNumbersDlg(CPhoneTypesArray* oPhoneTypeArray,PHONE_NUMBERS* oPhoneNumber/*=nullptr*/, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_PHONE_NUMBERS, pParent),
	m_pPhoneNumber(oPhoneNumber),
	m_pPhoneTypeArray(oPhoneTypeArray)
{
	m_bAllocatedNumber = false;
}

CPhoneNumbersDlg::~CPhoneNumbersDlg()
{
	m_pPhoneNumber = nullptr;
	m_pPhoneTypeArray = nullptr;
}

void CPhoneNumbersDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDB_PHONE_NUMBER, m_EdbPhoneNumber);
	DDX_Control(pDX, IDC_CMB_PHONE_TYPE, m_CmbPhoneType);
}

// Macros
// ----------------
BEGIN_MESSAGE_MAP(CPhoneNumbersDlg, CDialogEx)
END_MESSAGE_MAP()


// CPhoneNumbersDlg message handlers

PHONE_NUMBERS CPhoneNumbersDlg::GetNumber()
{
	return *m_pPhoneNumber;
}

BOOL CPhoneNumbersDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_EdbPhoneNumber.SetLimitText(PHONE_NUMBER_LENGTH);
	m_EdbPhoneNumber.SetCueBanner(L"Напр:0987654321",1);

	if (m_pPhoneNumber) {
		m_EdbPhoneNumber.SetWindowTextW(m_pPhoneNumber->szPhone);
	}
	for (INT_PTR nIndexer(0); nIndexer < m_pPhoneTypeArray->GetCount(); nIndexer++) {
		PHONE_TYPES* pPhoneTypes= m_pPhoneTypeArray->GetAt(nIndexer);
		if (!pPhoneTypes)
			continue;
		m_CmbPhoneType.AddString(pPhoneTypes->szPhoneType);
		m_CmbPhoneType.SetItemData((int)nIndexer, pPhoneTypes->lID);

		if (m_pPhoneNumber) {
			if (pPhoneTypes->lID == m_pPhoneNumber->lPhoneTypeID) {
				m_CmbPhoneType.SetCurSel((int)nIndexer);
			}
		}
	}

	return TRUE;
}


void CPhoneNumbersDlg::OnOK()
{
	if(!ValidateData())
		return;
	
	CDialogEx::OnOK();
}

bool CPhoneNumbersDlg::ValidateData()
{
	CString strPhoneNumber;
	m_EdbPhoneNumber.GetWindowTextW(strPhoneNumber);
	if (strPhoneNumber.GetLength()<10) {
		AfxMessageBox(L"Въведете номер от десет цифри");
		return false;
	}
	int nIndexer = m_CmbPhoneType.GetCurSel();

	if (nIndexer == CB_ERR) {
		AfxMessageBox(L"Изберете план");
		return false;
	}

	//in case we are trying to write to null
	//(happens when we call the constructor with nullptr)
	if (!m_pPhoneNumber) {
		m_pPhoneNumber = new PHONE_NUMBERS;
		if (m_pPhoneNumber) {
			m_bAllocatedNumber = true;
		}
		else {
			AfxMessageBox(L"Възникна грешка, опитайте по-късно");
			return false;
		}
	}
	
	_tcscpy_s(m_pPhoneNumber->szPhone, strPhoneNumber);
	if (m_pPhoneNumber->szPhone[0] != L'0') {
		AfxMessageBox(L"Номерът трябва да започва с нула");
		return false;
	}

	m_pPhoneNumber->lPhoneTypeID = (int)m_CmbPhoneType.GetItemData(nIndexer);

	return true;
}

void CPhoneNumbersDlg::OnCancel()
{
	if (m_bAllocatedNumber) {
		delete m_pPhoneNumber;
	}

	CDialogEx::OnCancel();
}
