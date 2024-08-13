
// PhoneBook.h : main header file for the PhoneBook application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CPhoneBookApp:
// See PhoneBook.cpp for the implementation of this class
//

class CPhoneBookApp : public CWinAppEx
{
public:
	CPhoneBookApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();
	
	afx_msg void OnAppAbout();
	afx_msg void OnFileNewPhoneTypes();
	afx_msg void OnFileNewCities();
	afx_msg void OnFileNewPersons();
	DECLARE_MESSAGE_MAP()
//	Members
	CMultiDocTemplate* pPersonsTemplate;
	CMultiDocTemplate* pCitiesTemplate;
	CMultiDocTemplate* pPhoneTypesTemplate;
};

extern CPhoneBookApp theApp;
