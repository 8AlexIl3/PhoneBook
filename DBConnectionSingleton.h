#pragma once

/////////////////////////////////////////////////////////////////////////////
// DBConnectionSingleton

#include "DBConnection.h"

class CDBConnectionSingleton {
public:
    static CDBConnection& GetInstance() {
        static CDBConnection instance;
        return instance;
    }
private:
    CDBConnectionSingleton() = default;
    ~CDBConnectionSingleton() = default;
    CDBConnectionSingleton(const CDBConnectionSingleton&) = delete;
    CDBConnectionSingleton& operator=(const CDBConnectionSingleton&) = delete;
};
