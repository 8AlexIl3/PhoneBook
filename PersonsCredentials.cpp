#include "pch.h"
#include "PersonsCredentials.h"

CPersonsCredentials::CPersonsCredentials()
{
}

CPersonsCredentials::~CPersonsCredentials()
{
    m_oPhoneTypesArray.RemoveAll();
    m_oCitiesArray.RemoveAll();
}
CPhoneTypesArray& CPersonsCredentials::GetPhoneTypesArray()
{
    return m_oPhoneTypesArray;
}

CCitiesArray& CPersonsCredentials::GetCitiesArray()
{
    return m_oCitiesArray;
}

void CPersonsCredentials::LoadCities()
{
    CCitiesData oCitiesData;

    for (long lIndexer = 0; (INT_PTR)lIndexer < m_oCitiesArray.GetCount(); lIndexer++) {
        CITIES* pCity = m_oCitiesArray.GetAt(lIndexer);
        if (!pCity)
            continue;
        delete pCity;
    }
    m_oCitiesArray.RemoveAll();

    oCitiesData.SelectAll(m_oCitiesArray);

    for (long lIndexer = 0; (INT_PTR)lIndexer < m_oCitiesArray.GetCount(); lIndexer++) {
        CITIES* pCity = m_oCitiesArray.GetAt(lIndexer);
        if (!pCity)
            continue;
        m_oCityIDtoString.SetAt(pCity->lID, pCity->szCityName);
    }


}
void CPersonsCredentials::LoadPhoneTypes()
{
    CPhoneTypesData oPhoneTypesData;

    for (long lIndexer = 0; (INT_PTR)lIndexer < m_oPhoneTypesArray.GetCount(); lIndexer++) {
        PHONE_TYPES* pPhoneType = m_oPhoneTypesArray.GetAt(lIndexer);
        if (!pPhoneType)
            continue;
        delete pPhoneType;
    }
    m_oPhoneTypesArray.RemoveAll();

    oPhoneTypesData.SelectAll(m_oPhoneTypesArray);

    for (long lIndexer = 0; (INT_PTR)lIndexer < m_oPhoneTypesArray.GetCount(); lIndexer++) {
        PHONE_TYPES* pPhoneTypes = m_oPhoneTypesArray.GetAt(lIndexer);
        if (!pPhoneTypes)
            continue;
        m_oPhoneTypeIDtoString.SetAt(pPhoneTypes->lID, pPhoneTypes->szPhoneType);
    }

}

CMap<long, long, CString, CString>& CPersonsCredentials::GetStringToPhoneTypeMap()
{
    return m_oPhoneTypeIDtoString;
}
CMap<long, long, CString, CString>& CPersonsCredentials::GetStringtoCityMap()
{
    return m_oCityIDtoString;
}

void CPersonsCredentials::RefreshData()
{
    LoadCities();
    LoadPhoneTypes();
}
