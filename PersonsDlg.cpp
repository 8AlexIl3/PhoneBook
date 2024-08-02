// PersonsDlg.cpp : implementation file
//

#include "pch.h"
#include "PhoneBook.h"
#include "afxdialogex.h"
#include "PersonsDlg.h"


// CPersonsDlg dialog

IMPLEMENT_DYNAMIC(CPersonsDlg, CDialogEx)

CPersonsDlg::CPersonsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_PERSONS, pParent)
{
}


CPersonsDlg::~CPersonsDlg()
{
}

void CPersonsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDB_ADDRESS, m_EdbAddress);
	DDX_Control(pDX, IDC_EDB_SURNAME, m_EdbSurname);
	DDX_Control(pDX, IDC_EDB_EGN, m_EdbEGN);
	DDX_Control(pDX, IDC_EDB_LAST_NAME, m_EdbLastName);
	DDX_Control(pDX, IDC_EDB_FIRST_NAME, m_EdbFirstName);
}


BEGIN_MESSAGE_MAP(CPersonsDlg, CDialogEx)
END_MESSAGE_MAP()


// CPersonsDlg message handlers
