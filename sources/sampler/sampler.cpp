//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("sampler.res");
USEFORM("main.cpp", FSampler);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TFSampler), &FSampler);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        return 0;
}
//---------------------------------------------------------------------------
