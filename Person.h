#pragma once
#include "Structures.h"

class CPerson
{
    // Constructor / Destructor
    // ----------------
public:
    CPerson(PERSONS oPerson, CPhoneNumbersArray oPhoneNumbersArray);
    CPerson(const CPerson& oPerson);
    virtual ~CPerson();
    // Methods
    // ----------------
public:
    CPhoneNumbersArray GetPhoneNumbers();
    PERSONS GetPerson();
    // Members
    // ----------------
private:
    PERSONS m_oRecPerson;
    CPhoneNumbersArray m_oPhoneNumbersArray;
};

typedef CAutoMemoryArray<CPerson> CPersonArray;
