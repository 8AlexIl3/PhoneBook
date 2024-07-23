#pragma once
#include "pch.h"
#include <atldbcli.h>
#include <atlstr.h> 
#include <iostream>
#include "Structures.h"
using namespace std;



class CCitiesAccessor
{
protected:
    CITIES m_recCity;

    BEGIN_ACCESSOR_MAP(CCitiesAccessor, 2)
        BEGIN_ACCESSOR(0, true)
        COLUMN_ENTRY(1, m_recCity.lID)
        END_ACCESSOR()

        BEGIN_ACCESSOR(1, true)
        COLUMN_ENTRY(2, m_recCity.lUpdateCounter)
        COLUMN_ENTRY(3, m_recCity.szCityName)
        COLUMN_ENTRY(4, m_recCity.szTownResidence)

        END_ACCESSOR()
    END_ACCESSOR_MAP()
};

class CCitiesTable : private CCommand<CAccessor<CCitiesAccessor>>
{
public:
   BOOL LoadCities();
   BOOL UpdateCity();
};

void Message(const TCHAR* format, ...)
{
    va_list args;
    va_start(args, format);
    _vtprintf(format, args);
    va_end(args);
}

