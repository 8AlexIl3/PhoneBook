#pragma once
#include "Structures.h"

class CPerson
{
    // Constructor / Destructor
    // ----------------
public:
    CPerson();
    CPerson(PERSONS oPerson);
    CPerson(PERSONS oPerson, CPhoneNumbersArray oPhoneNumbersArray);
    CPerson(const CPerson& oPerson);
    virtual ~CPerson();
    // Methods
    // ----------------
public:
    CPerson& operator=(const CPerson& oPerson)
    {   
        m_oRecPerson = oPerson.m_oRecPerson;
        m_oPhoneNumbersArray = m_oPhoneNumbersArray;
        return *this;
    }
    CPhoneNumbersArray GetPhoneNumbers();
    PERSONS GetPerson();
    // Members
    // ----------------
public:
    PERSONS m_oRecPerson;
    CPhoneNumbersArray m_oPhoneNumbersArray;
};

typedef CAutoMemoryArray<CPerson> CPersonArray;
