#pragma once
#include "Structures.h"
#include <atldbcli.h>
#define ACCESSOR_COUNT              2

#define ACCESSOR_0                  0
#define ACCESSOR_1                  1


#define REC_ID                      1

#define PHONE_NUMBER_UPDATE_COUNTER 2
#define PERSON_ID                   3
#define PHONE_TYPE_ID               4
#define PHONE                       5

class CPhoneNumbersAccessor
{
protected:
    PHONE_NUMBERS m_recPhoneNumber;

    BEGIN_ACCESSOR_MAP(CPhoneNumbersAccessor, ACCESSOR_COUNT)
        BEGIN_ACCESSOR(ACCESSOR_0, true)
        COLUMN_ENTRY(REC_ID, m_recPhoneNumber.lID)
        END_ACCESSOR()

        BEGIN_ACCESSOR(ACCESSOR_1, true)
        COLUMN_ENTRY(PHONE_NUMBER_UPDATE_COUNTER, m_recPhoneNumber.lUpdateCounter)
        COLUMN_ENTRY(PERSON_ID, m_recPhoneNumber.lPersonID)
        COLUMN_ENTRY(PHONE_TYPE_ID, m_recPhoneNumber.lPhoneTypeID)
        COLUMN_ENTRY(PHONE, m_recPhoneNumber.szPhone)
        END_ACCESSOR()

    END_ACCESSOR_MAP()
};