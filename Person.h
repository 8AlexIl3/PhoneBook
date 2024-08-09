#pragma once
#include "Structures.h"

class CPersonExtend
{
    // Constructor / Destructor
    // ----------------
public:
    CPersonExtend();

    CPersonExtend(PERSONS oPerson);

    CPersonExtend(PERSONS oPerson, CPhoneNumbersArray oPhoneNumbersArray);

    CPersonExtend(const CPersonExtend& oPerson);

    virtual ~CPersonExtend();
    // Methods
    // ----------------
public:
    CPersonExtend& operator=(const CPersonExtend& oPerson)
    {   
        m_oRecPerson = oPerson.m_oRecPerson;
        m_oPhoneNumbersArray = oPerson.m_oPhoneNumbersArray;
        return *this;
    }
    // Members
    // ----------------
public:
    PERSONS m_oRecPerson;
    CPhoneNumbersArray m_oPhoneNumbersArray;
};

typedef CAutoMemoryArray<CPersonExtend> CPersonArray;
