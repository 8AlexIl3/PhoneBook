#include "pch.h"
#include "Person.h"

CPersonExtend::CPersonExtend()
{
}

CPersonExtend::CPersonExtend(PERSONS oPerson):m_oRecPerson(oPerson)
{
    
}

// Constructor
CPersonExtend::CPersonExtend(PERSONS oPerson, CPhoneNumbersArray oPhoneNumbersArray)
    : m_oRecPerson(oPerson),
      m_oPhoneNumbersArray(oPhoneNumbersArray)
{
}

// Copy Constructor
CPersonExtend::CPersonExtend(const CPersonExtend& oPerson)
    : m_oRecPerson(oPerson.m_oRecPerson),
      m_oPhoneNumbersArray(oPerson.m_oPhoneNumbersArray)
{
}

// Destructor
CPersonExtend::~CPersonExtend()
{
}

