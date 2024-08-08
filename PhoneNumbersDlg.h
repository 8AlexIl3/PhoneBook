#pragma once

#include "afxdialogex.h"
#include "Structures.h"

// CPhoneNumbersDlg dialog
class CPhoneNumbersDlg : public CDialogEx
{
    // Macros
    // ----------------
    DECLARE_DYNAMIC(CPhoneNumbersDlg)
    DECLARE_MESSAGE_MAP()

    // Constructor / Destructor
    // ----------------
public:
    CPhoneNumbersDlg(CPhoneTypesArray* oPhoneTypeArray, PHONE_NUMBERS* oPhoneNumbers = nullptr, CWnd* pParent = nullptr);
    
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
    CPhoneTypesArray* m_pPhoneTypeArray;
    PHONE_NUMBERS* m_pPhoneNumbers;
    CEdit m_EdbPhoneNumber;
    CComboBox m_CmbPhoneType;
    bool m_bAllocatedNumber;
   
};

#define PHONE_NUMBER_LENGTH 10
