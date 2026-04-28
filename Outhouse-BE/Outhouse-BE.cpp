// Outhouse-BE.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "Outhouse-BE.h"


// This is an example of an exported variable
OUTHOUSEBE_API int nOuthouseBE=0;

// This is an example of an exported function.
OUTHOUSEBE_API int fnOuthouseBE(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
COuthouseBE::COuthouseBE()
{
    return;
}
