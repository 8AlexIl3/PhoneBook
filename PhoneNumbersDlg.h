#pragma once
#include "afxdialogex.h"
#include "Structures.h"


/////////////////////////////////////////////////////////////////////////////
// CPhoneNumbersDlg

class CPhoneNumbersDlg : public CDialogEx
{
    // Macros
    // ----------------
    DECLARE_DYNAMIC(CPhoneNumbersDlg)
    DECLARE_MESSAGE_MAP()

    // Constructor / Destructor
    // ----------------
public:
    CPhoneNumbersDlg(CPhoneTypesArray& oPhoneTypeArray, PHONE_NUMBERS& oPhoneNumbers, CWnd* pParent = nullptr);
    
    virtual ~CPhoneNumbersDlg();


    // Constants
    // ----------------
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_DLG_PHONE_NUMBERS };
#endif


    // MFC Overrides
    // ----------------
protected:
    void DoDataExchange(CDataExchange* pDX) override;    // DDX/DDV support
    BOOL OnInitDialog() override;
    void OnOK() override;
    void OnCancel() override;

    //Methods
    // ----------------
private:
    bool ValidateData();
public:
    PHONE_NUMBERS& GetNumber();


    //Members
    // ----------------
private:
    CPhoneTypesArray& m_oPhoneTypeArray;
    PHONE_NUMBERS& m_oPhoneNumber;
    CEdit m_EdbPhoneNumber;
    CComboBox m_CmbPhoneType;
};

#define PHONE_NUMBER_LENGTH 10
