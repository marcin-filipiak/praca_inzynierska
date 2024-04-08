//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "stdio.h"

#include <mmsystem.h>

#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

AnsiString sampl;
int klatka=0;

//------------------------rysuje samo tlo i czysci ekran------------------------
void refresh()
{
   Graphics::TBitmap *pBitmap = new Graphics::TBitmap();
    pBitmap->LoadFromFile("gloski\\budowa.bmp");
    pBitmap->Transparent = false;
    Form1->ekran->Canvas->Draw(0,0,pBitmap);
    delete pBitmap;
}

void rysuj(int _x, int _y)
{
   Graphics::TBitmap *pBitmap = new Graphics::TBitmap();
    if (klatka==1) pBitmap->LoadFromFile("gloski\\1.bmp");
    if (klatka==2) pBitmap->LoadFromFile("gloski\\2.bmp");
    if (klatka==3) pBitmap->LoadFromFile("gloski\\3.bmp");
    pBitmap->Transparent = True;
    _x=_x-20;
    _y=_y-17;
    Form1->ekran->Canvas->Draw(_x,_y,pBitmap);
    delete pBitmap;
}

//----------------------MAIN-------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
// by obraz nie migotal w czasie animacji
 DoubleBuffered = true;
 
ListSamogloski->Items->LoadFromFile("gloski\\samogloski.txt");
ListSpolgloski->Items->LoadFromFile("gloski\\spolgloski.txt");
}
//----------------------LIST SAMOGLOSKI----------------------------------------------------
void __fastcall TForm1::ListSamogloskiClick(TObject *Sender)
{
sampl=ListSamogloski->Items->Strings[ListSamogloski->ItemIndex];


AnsiString a_path="gloski//"+sampl+".wav";
//zamiana String na char-
char ch_path[20];
sprintf(ch_path, "%s", a_path.c_str());

   sndPlaySound(ch_path, SND_ASYNC);

   klatka=0;
   animator->Enabled=true;
}
//-----------------------LIST SPOLGLOSKI----------------------------------------------------
void __fastcall TForm1::ListSpolgloskiClick(TObject *Sender)
{
sampl=ListSpolgloski->Items->Strings[ListSpolgloski->ItemIndex];

AnsiString a_path="gloski//"+sampl+".wav";
//zamiana String na char-
char ch_path[20];
sprintf(ch_path, "%s", a_path.c_str());

   sndPlaySound(ch_path, SND_ASYNC);

   klatka=0;
   animator->Enabled=true;

}
//-------------------------ANIMATOR----------------------------------------------
void __fastcall TForm1::animatorTimer(TObject *Sender)
{
int x,y;

klatka++;

if (klatka<4)
{
//--------------------
//spolgloski dwuwargowe
if (sampl=="p" || sampl=="b")
    {
    rysuj(37,162);
    rysuj(26,256);
    }
//spolgloski przedniojezykowo-dziaslowe
if (sampl=="t" || sampl=="d")
    {
    rysuj(69,165);
    rysuj(56,217);
    }
//spolgloski tylnojezykowopodniebienna
if (sampl=="c" || sampl=="g" || sampl=="k")
    {
    rysuj(192,153);
    }
//spolgloski wargowo-zebowe
if (sampl=="f")
    {
    rysuj(46,167);
    }
//spolgloski nosowo dwuwargowe
if (sampl=="m")
    {
    rysuj(124,57);
    rysuj(37,162);
    rysuj(26,256);
    }
//spolgloski dwuwargowe miekkopodniebienne
if (sampl=="w")
    {
    rysuj(37,162);
    rysuj(26,256);
    rysuj(192,153);
    }
//spolgloski krtaniowe
if (sampl=="h")
    {
    rysuj(234,261);
    }
//spolgloski  drgajaca przedniojezykowo-dziaslowe
if (sampl=="r")
    {
    rysuj(54,219);
    }
//spolgloski tylnojezykowo-podniebienna
if (sampl=="l")
    {
    rysuj(129,216);
    }
//spolgloski przedniojezykowo-dziaslowe
if (sampl=="s" || sampl=="z")
    {
    rysuj(57,185);
    }
//spolgloska nosowo zebowa
if (sampl=="n")
    {
    rysuj(54,179);
    rysuj(124,57);
    }

//samogloski
//samogloski przedniojezykowo
if (sampl=="i" || sampl=="y" || sampl=="a" || sampl=="e")
    {
    rysuj(78,215);
    }
//samogloski tylnojezykowo
if (sampl=="u" || sampl=="o" || sampl=="a")
    {
    rysuj(166,222);
    }
//--------------------

}



if (klatka>4) {refresh(); animator->Enabled=false; }


}
//---------------------------------------------------------------------------

