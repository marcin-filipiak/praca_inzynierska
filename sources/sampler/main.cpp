//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"

#include "mic.cpp"

#include "stdio.h"

#include <inifiles.hpp>

#include <mmsystem.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFSampler *FSampler;
int stoper=1; //uruchamia swiatla i kontroluje czas nagrania
AnsiString interface_jezyk;

//---------------------------zmiana jezyka-----------------------------------
void jezyk(AnsiString ln)
{
if (ln=="En")
    {
     interface_jezyk="En";
     FSampler->GroupBox1->Caption="Select data base";
     FSampler->GroupBox2->Caption="Samples recorded in the language base";
     FSampler->GroupBox3->Caption="Samples to record";
     FSampler->GroupBox4->Caption="Is the sample recorded correctly?";
     FSampler->GroupBox5->Caption="Suggested sample time";
     FSampler->English1->Caption="English";
     FSampler->Polski1->Caption="Polski";
     FSampler->Caption=".:: Sampler ::.";
    }
if (ln=="Pl")
    {
     interface_jezyk="Pl";
     FSampler->GroupBox1->Caption="Bazy Jezykowe";
     FSampler->GroupBox2->Caption="Nagrane sample w Bazie Jezykowej";
     FSampler->GroupBox3->Caption="Lista sampli do nagrania";
     FSampler->GroupBox4->Caption="Czy sampl jest nagrany poprawnie?";
     FSampler->GroupBox5->Caption="Sugerowany czas sampla";
     FSampler->Polski1->Caption="Polski";
     FSampler->English1->Caption=" English";
     FSampler->Caption=".:: Sampler ::.";
    }
}
//-------------------------tworzy plik konfiguracyjny bazy jezykowej----------------
 void zapisz_dla_syntezatora()
{
AnsiString path=FSampler->lista_bazy_sampli->Items->Strings[FSampler->lista_bazy_sampli->ItemIndex];

TIniFile *PlikIni=new TIniFile("sample//"+path+".synt");
PlikIni->WriteString("Sample","sciezka",path+"//");
delete PlikIni;
}
//-----------------------Obsluga obrazkow--------------------------------------
void rysuj(AnsiString plik)
{
    Graphics::TBitmap *pBitmap = new Graphics::TBitmap();
    pBitmap->LoadFromFile("pliki_pomocnicze//"+plik);
    FSampler->swiatlo->Canvas->Draw(0,0,pBitmap);
    FSampler->swiatlo->Picture->Bitmap->PixelFormat = pf32bit;
    pBitmap->Transparent = True;
    delete pBitmap;
}
//----------------------OBSLUGA MIKROFONU--------------------------------------
//stworzenie mikrofonu
MIC *mic = new MIC();

//--------sprawdzenie wypelnienia bufora-------------
void CALLBACK sprawdzaj(HWAVEIN hwi, UINT uMsg, DWORD dwInstance,
                         DWORD dwParam1, DWORD dwParam2)
{
/*
   Sprawdzenie czy bufor zostal wypelniony (komunikat WIM_DATA)
   jesli tak, to mozna pobrac dane i wstawic go na oniec kolejki
*/
  mic->sprawdzaj(hwi, uMsg, dwInstance, dwParam1, dwParam2);
}

//----stop nagrywania----
void stop()
{
  mic->nagrywanie = false;
}

//----nagrywaj----
void record()
{
 mic->nagrywanie = true;
  for (int i=0;i<mic->liczba_nagranych;i++)
    delete []mic->nagra[i];
  mic->liczba_nagranych = 0;
}

//----zapisz---
void save(AnsiString plik)
{
//zamiana String na char-
char ch_plik[20];
sprintf(ch_plik, "%s", plik.c_str());

  mic->SaveWaveFile(ch_plik);
}





//----------------------------OPERACJE NA FOLDERACH I PLIKACH----------------------------
//tworzenie katalogu
bool CreateFolder(const AnsiString folder)
{
CreateDir(folder);
//Zapisanie wszystkich zmian
FSampler->lista_bazy_sampli->Items->SaveToFile("sample/baza.txt");
}

//usuwanie plikow
void DeleteFiles(String DirName, String prefix)
{
 TSearchRec sr;
 int result;
 AnsiString FileName;
 result = FindFirst(DirName + "*.*", faAnyFile, sr);
 while(result == 0)
 {
  if((sr.Name != ".") && (sr.Name != "..") && (!(sr.Attr & faDirectory) > 0))
  {
   if(ExtractFileExt(sr.Name).SubString(2, 5) == prefix)
   {
    FileName = DirName + sr.Name;
   }
   if(prefix == "*")
   {
    FileName = DirName + sr.Name;
   }
   DeleteFile(FileName); // lub DeleteFile(FileName.c_str()).
  }
  result = FindNext(sr);
 }
 FindClose(sr);
}


//---usuwanie foldera-----
bool DeleteFolder(AnsiString folder)
{
//wszystkie pliki z foldera usunac
DeleteFiles(folder+"//","*");
//usunac tez i folder
RemoveDir(folder);

//Zapisanie wszystkich zmian
FSampler->lista_bazy_sampli->Items->SaveToFile("sample/baza.txt");
}

//------------------------zapisuje aktualny stan list--------------------------
void zapisz_listy()
{
//Pobranie tekstu jaki jest zanzaczony w listboxie
AnsiString katalog=FSampler->lista_bazy_sampli->Items->Strings[FSampler->lista_bazy_sampli->ItemIndex];

FSampler->lista_sampli_do_nagrania->Items->SaveToFile("sample//"+katalog+"//do_nagrania.txt");
FSampler->lista_sampli->Items->SaveToFile("sample//"+katalog+"//index.txt");

//poniewaz sa juz jakies sample to mozna stworzyc plik do otwierania
//bazy syntezatorem
if ((FSampler->lista_sampli->Items->Count)!=0)
   {
   zapisz_dla_syntezatora();
   }



}

//--------------------------------------MAIN-------------------------------
__fastcall TFSampler::TFSampler(TComponent* Owner)
        : TForm(Owner)
{
//wczytanie baz
FSampler->lista_bazy_sampli->Items->LoadFromFile("sample/baza.txt");

//sprawdzenie mikrofonu
mic->OpenMic((DWORD*)sprawdzaj);
}
//-------------------------------Usuwanie z bazy----------------------------------------

void __fastcall TFSampler::SpeedMinusClick(TObject *Sender)
{
//zliczanie elementow listy, podaje wartosc od 1 do n
int ilosc=FSampler->lista_bazy_sampli->Items->Count;

//poniewaz listbox indeksowany jest od 0 do n odejmujemy 1
int index=ilosc-1;

//Uwaga sprawdzanie zaczynamy od tylu bo nie mozna usuwac od przodu
//poniewaz ilosc po usunieciu by sie nie zgadzala
while (index!=-1)
 {
 //jesli baza jest zaznaczona na liscie
    if(FSampler->lista_bazy_sampli->Selected[index])
      {
      //Pobranie tekstu jaki jest zanzaczony w listboxie
      AnsiString katalog=lista_bazy_sampli->Items->Strings[lista_bazy_sampli->ItemIndex];

      //usuwamy je
      FSampler->lista_bazy_sampli->Items->Delete(index);


      DeleteFolder("sample\\"+katalog);
      DeleteFile("sample\\"+katalog+".synt");


      }
     //idziemy o pole nizej
   index--;
 }

//Zapisanie wszystkich zmian
FSampler->lista_bazy_sampli->Items->SaveToFile("sample/baza.txt");

}
//--------------------------Dodawanie do bazy-----------------------------

void __fastcall TFSampler::SpeedPlusClick(TObject *Sender)
{
WinExec("budowacz.exe", SW_SHOW);
Close();
}
//---------------------------Po kliknieciu na bazie pokazywane jej sample-----

void __fastcall TFSampler::lista_bazy_sampliClick(TObject *Sender)
{

lista_sampli->Items->Clear();
lista_sampli_do_nagrania->Items->Clear();

 //zliczanie elementow listy, podaje wartosc od 1 do n
int ilosc=FSampler->lista_bazy_sampli->Items->Count;

//poniewaz listbox indeksowany jest od 0 do n odejmujemy 1
int index=ilosc-1;

//Uwaga sprawdzanie zaczynamy od tylu
while (index!=-1)
 {

    //jesli dana baza jest zaznaczona na liscie
    if(FSampler->lista_bazy_sampli->Selected[index])
      {
      //Pobranie tekstu jaki jest zanzaczony w listboxie
      AnsiString katalog=lista_bazy_sampli->Items->Strings[lista_bazy_sampli->ItemIndex];

         //ta baza ma jakies sample
         if ( FileExists("sample//"+katalog+"//index.txt"))
            {
             lista_sampli->Items->LoadFromFile("sample//"+katalog+"//index.txt");
             }

        //to baza dopiero do nagrania sampli
         if ( FileExists("sample//"+katalog+"//do_nagrania.txt"))
            {
            //wczytanie do listy
            lista_sampli_do_nagrania->Items->LoadFromFile("sample//"+katalog+"//do_nagrania.txt");
            }

         //brak pliku index.txt i do_nagrania.txt zatem to pusty katalog
         if (FileExists("sample//"+katalog+"//do_nagrania.txt")==false && FileExists("sample//"+katalog+"//index.txt")==false)
           {
           ShowMessage("Wyglada na to ze baza jest zupelnie pusta \n zostaje wykasowana!");
           //usuwanie jej z dysku
           DeleteFolder("sample//"+katalog);
           //usuwamy ja z listy
           FSampler->lista_bazy_sampli->Items->Delete(index);
           }



      }
     //idziemy o pole nizej
   index--;
 }


}
//----------------------------Gdy okno zostanie zamkniete-----------------------------------------

void __fastcall TFSampler::FormClose(TObject *Sender, TCloseAction &Action)
{
//wylaczenie mikrofonu
  mic->CloseMic();
}
//---------------------------Wlaczenie timera-----------------------------------------

void __fastcall TFSampler::SpeedNagrajClick(TObject *Sender)
{
FSampler->Timer->Enabled=true;
}
//-------------------------------Timer-----------------------------------------

void __fastcall TFSampler::TimerTimer(TObject *Sender)
{
if (stoper==StrToInt(edit_dlugosc->Text)+2)
   {
   //zatrzymaj nagrywanie
   stop();
   save("pliki_pomocnicze//bufor.wav");

   //odgrywa plik wav z podanej sciezki
   sndPlaySound("pliki_pomocnicze//bufor.wav", SND_ASYNC);

   stoper=1;
   Timer->Enabled=false;
   }

if (stoper<3)
   {
   rysuj(IntToStr(stoper)+".bmp");
   }

if (stoper==3)
      {
      rysuj("3.bmp");

      
      //nagrywaj
      record();
      }

stoper++;
}
//-------------------------Nagrany sampl jest ok----------------------------------------------
void __fastcall TFSampler::speed_okClick(TObject *Sender)
{

//Pobranie tekstu jaki jest zanzaczony w listboxie
AnsiString katalog=lista_bazy_sampli->Items->Strings[lista_bazy_sampli->ItemIndex];

//Pobranie tekstu jaki jest zanzaczony w listboxie
AnsiString sampl=lista_sampli_do_nagrania->Items->Strings[lista_sampli_do_nagrania->ItemIndex];

AnsiString s_path="sample//"+katalog+"//"+sampl+".wav";

//zamiana String na char-
char c_path[40];
sprintf(c_path, "%s", s_path.c_str());

//zapisanie sampla w bazie
CopyFile("pliki_pomocnicze//bufor.wav",c_path, false);

//dodanie do listy nagranych
lista_sampli->Items->Add(sampl);

//usuniecie z listy do nagrania
lista_sampli_do_nagrania->Items->Delete(lista_sampli_do_nagrania->ItemIndex);

zapisz_listy();
}
//--------------------------Nagrany Sampl jest zly---------------------------------------------

void __fastcall TFSampler::speed_noClick(TObject *Sender)
{
FSampler->Timer->Enabled=true;
}
//----------------------DODANIA SAMPLA DO BAZY SAMPLI DO NAGRANIA-----------------------

void __fastcall TFSampler::speed_add_samplClick(TObject *Sender)
{
lista_sampli_do_nagrania->Items->Add(edit_sampl->Text);
zapisz_listy();
edit_sampl->Text="";
}
//------------USUWANIE NAGRANEGO SAMPLA COFNIECIE DO SAMPLI DO NAGRANIA---------------------------------

void __fastcall TFSampler::speed_cofnijClick(TObject *Sender)
{
//Pobranie tekstu jaki jest zanzaczony w listboxie
AnsiString katalog=lista_bazy_sampli->Items->Strings[lista_bazy_sampli->ItemIndex];

//Pobranie tekstu jaki jest zanzaczony w listboxie
AnsiString sampl=lista_sampli->Items->Strings[lista_sampli->ItemIndex];
//usuniecie z listy sampli
lista_sampli->Items->Delete(lista_sampli->ItemIndex);
//dodanie do listy sampli do nagrania
lista_sampli_do_nagrania->Items->Add(sampl);

DeleteFile("sample//"+katalog+"//"+sampl+".wav");

zapisz_listy();
}

//--------------------------------Odsluchanie sampla z bazy---------------------

void __fastcall TFSampler::speed_odsluchajClick(TObject *Sender)
{
//Pobranie tekstu jaki jest zanzaczony w listboxie
AnsiString katalog=lista_bazy_sampli->Items->Strings[lista_bazy_sampli->ItemIndex];

//Pobranie tekstu jaki jest zanzaczony w listboxie
AnsiString sampl=lista_sampli->Items->Strings[lista_sampli->ItemIndex];

AnsiString a_path="sample//"+katalog+"//"+sampl+".wav";
//zamiana String na char-
char ch_path[20];
sprintf(ch_path, "%s", a_path.c_str());

   sndPlaySound(ch_path, SND_ASYNC);
}
//---------------------------------------------------------------------------

void __fastcall TFSampler::speed_del_samplClick(TObject *Sender)
{
    //zliczanie elementow listy, podaje wartosc od 1 do n
int ilosc=FSampler->lista_sampli_do_nagrania->Items->Count;

//poniewaz listbox indeksowany jest od 0 do n odejmujemy 1
int index=ilosc-1;

//Uwaga sprawdzanie zaczynamy od tylu bo nie mozna usuwac od przodu
//poniewaz ilosc po usunieciu by sie nie zgadzala
while (index!=-1)
 {
 //jesli sampl jest zaznaczony na liscie
    if(FSampler->lista_sampli_do_nagrania->Selected[index])
      {
      //Pobranie tekstu jaki jest zanzaczony w listboxie
      AnsiString katalog=lista_sampli_do_nagrania->Items->Strings[lista_sampli_do_nagrania->ItemIndex];

      //usuwamy je
      FSampler->lista_sampli_do_nagrania->Items->Delete(index);

      }
     //idziemy o pole nizej
   index--;
 }

//Zapisanie wszystkich zmian
zapisz_listy();

}
//-------------------------------Jezyk polski---------------------------------
void __fastcall TFSampler::Polski1Click(TObject *Sender)
{
 jezyk("Pl");
}
//--------------------------------Jezyk angielski-----------------------------

void __fastcall TFSampler::English1Click(TObject *Sender)
{
 jezyk("En");
}
//---------------------------------------------------------------------------

