#pragma once
#include "Structures.h"
#include <atldbcli.h>


/////////////////////////////////////////////////////////////////////////////
// CPhoneNumbersAccessor

#define ACCESSOR_COUNT              2

#define ACCESSOR_IDENTITY           0
#define ACCESSOR_DATA               1

#define REC_ID                      1

#define PHONE_NUMBER_UPDATE_COUNTER 2
#define PERSON_ID                   3
#define PHONE_TYPE_ID               4
#define PHONE                       5

class CPhoneNumbersAccessor
{

protected:
    PHONE_NUMBERS m_rec;

    BEGIN_ACCESSOR_MAP(CPhoneNumbersAccessor, ACCESSOR_COUNT)
        BEGIN_ACCESSOR(ACCESSOR_IDENTITY, true)
        COLUMN_ENTRY(REC_ID, m_rec.lID)
        END_ACCESSOR()

        BEGIN_ACCESSOR(ACCESSOR_DATA, true)
        COLUMN_ENTRY(PHONE_NUMBER_UPDATE_COUNTER, m_rec.lUpdateCounter)
        COLUMN_ENTRY(PERSON_ID, m_rec.lPersonID)
        COLUMN_ENTRY(PHONE_TYPE_ID, m_rec.lPhoneTypeID)
        COLUMN_ENTRY(PHONE, m_rec.szPhone)
        END_ACCESSOR()

    END_ACCESSOR_MAP()
};