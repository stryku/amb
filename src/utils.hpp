#pragma once

#include <Windows.h>

namespace Utils
{
    void closeAndNullHandle( HANDLE &handle )
    {
        CloseHandle( handle );
        handle = NULL;
    }

    void safeCloseAndNullHandle( HANDLE &handle )
    {
        if( handle != NULL )
            closeAndNullHandle( handle );
    }
}