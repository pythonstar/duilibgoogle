#pragma once
#include <crtdbg.h>
#include <assert.h>
#ifdef _DEBUG
#define DEBUG_CLIENTBLOCK   new( _CLIENT_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_CLIENTBLOCK
#endif

#define _CRTDBG_MAP_ALLOC

#ifdef _DEBUG
#define new DEBUG_CLIENTBLOCK
#endif

void CheckOnExit()
{
    _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); 
    assert( _CrtDumpMemoryLeaks() == 0);
}
