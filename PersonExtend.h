#pragma once
#include "Structures.h"


/////////////////////////////////////////////////////////////////////////////
// CBasePersonExtend

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
    // Members
    // ----------------
public:
    PERSONS m_oRecPerson;
    CPhoneNumbersArray m_oPhoneNumbersArray;
};

typedef CAutoMemoryArray<CPersonExtend> CPersonArray;
