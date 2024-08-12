#pragma once
#include "CitiesData.h"
#include "PhoneTypesData.h"
#include "CitiesData.h"
#include <afxtempl.h>

class CPersonsCredentials {
	
	// Constructor & Destructor
	// ----------------
public:
	CPersonsCredentials();

	virtual ~CPersonsCredentials();

	// Methods
	// ----------------
public:
	CPhoneTypesArray& GetPhoneTypesArray();

	CCitiesArray& GetCitiesArray();

	CMap<long, long, CString, CString>& GetStringtoCityMap();

	CMap<long, long, CString, CString>& GetStringToPhoneTypeMap();

	void RefreshData();

private:
	void LoadCities();

	void LoadPhoneTypes();


	// Members
	// ----------------
private:
	CPhoneTypesArray m_oPhoneTypesArray;

	CCitiesArray m_oCitiesArray;

	CMap<long, long, CString, CString> m_oCityIDtoString;

	CMap<long, long, CString, CString> m_oPhoneTypeIDtoString;
};