#include "pch.h"
#include "Person.h"

// Constructor
CPerson::CPerson(PERSONS oPerson, CPhoneNumbersArray oPhoneNumbersArray)
    : m_oRecPerson(oPerson),
      m_oPhoneNumbersArray(oPhoneNumbersArray)
{
}

// Copy Constructor
CPerson::CPerson(const CPerson& oPerson)
    : m_oRecPerson(oPerson.m_oRecPerson),
      m_oPhoneNumbersArray(oPerson.m_oPhoneNumbersArray)
{
}

// Destructor
CPerson::~CPerson()
{
}

// Methods
CPhoneNumbersArray CPerson::GetPhoneNumbers()
{
    return m_oPhoneNumbersArray;
}

PERSONS CPerson::GetPerson()
{
    return m_oRecPerson;
}
