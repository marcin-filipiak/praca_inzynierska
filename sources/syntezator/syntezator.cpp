//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("syntezator.res");
USEFORM("main.cpp", Syntezator);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TSyntezator), &Syntezator);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
