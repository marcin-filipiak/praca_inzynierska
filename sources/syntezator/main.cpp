//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <mmsystem.h>

#include <inifiles.hpp>
#include <clipbrd.hpp>

#include "stdio.h"

#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Trayicon"
#pragma resource "*.dfm"

TSyntezator *Syntezator;

#include "../strukturyzator/struktura_analizujaca.cpp"

int total_znakow; //wszystkich znakow w tekscie
int kareta; //do przesuwania sie po tekscie
int czas_spacji; //wartosc przerwy [ms] by zaznaczyc spacje przy odczycie
AnsiString tekst; //zmienna w jakiej bedzie tekst z memo_tekst
AnsiString path_sampli=""; //sciezka do sampli
int speed; //predkosc czytania
bool bledy_odczytu;

AnsiString jezyk_interface;
int szerokosc;//szerokosc okna

TClipboard *pCB = Clipboard();

#include "procedury.cpp"
//------------------------------MAIN-------------------------------------------
__fastcall TSyntezator::TSyntezator(TComponent* Owner)
        : TForm(Owner)
{
 Timer1->Enabled=false; //na poczatku petla czytajaca stoi
 
 odczytaj_konfiguracje_syntezatora();


 combo_baza->Items->LoadFromFile("sample//baza.txt");

}

//-----------------------------TIMER (petla czytajaca)-----------------------
void __fastcall TSyntezator::Timer1Timer(TObject *Sender)
{

//pobieramy predkosc, by potem obliczyc czas odczytu znaku
int o_speed=speed;
//sciezka do sampla
AnsiString sciezka;

//jesli sa wogole jakies znaki
if (total_znakow!=0)
{
//kareta lokalna pojawia sie w miejscu gdzie zakonczono czytanie
int kareta_lokalna=kareta;
//bufor w jakim bedzie tekst do sprawdzenia w bazie sampli
AnsiString bufor="";
//tutaj bedzie najdluzszy znaleziony sampel
AnsiString sampel="";


//jesli teraz nie ma spacji to znaczy, ze mamy wyraz
if (get_znak(kareta_lokalna)!=' ')
{
//zaznaczanie tekstu
memo_tekst->SelLength=kareta;

//petla odczytu wyrazu i szukania jak najdluzszego sampla
while (get_znak(kareta_lokalna)!=' ')
     {
     //jesli nie jestesmy na koncu tekstu
     if (total_znakow!=kareta_lokalna)
          {
          //do bufora ladujemy kolejne znaki wyrazu az do zakonczenia wyrazu
          bufor=bufor+get_znak(kareta_lokalna);
          //jesli bufor zostal rozpoznany to bedziemy miec aktualnie
          //najdluzszy sampel
          if (sprawdz_sampel(bufor))
             {
             //obliczenie czasu w jakim bedzie odczytany sampel
             o_speed=speed+bufor.Length()*20;
             //zapisujemy stan rozpoznanego bufora jako sampel
             sampel=bufor;
             //budujemy sciezke do sampla
             sciezka=path_sampli+sampel+".wav";
             //przesuniecie karety globalnej o ilosc znakow w buforze (karecie lokalnej)
             kareta=kareta_lokalna+1;
             }
          //nastepny znak, kareta lokalna
          kareta_lokalna++;
          }
       }

// jesli sampla nie znaleziono
if ( sampel=="")
                 {
                  kareta=kareta_lokalna;
                  bledy_odczytu=true;
                  //ShowMessage("Nie potrafie odczytac "+bufor);
                 }
                 //jesli sampel znaleziony to go czytamy
                 else
                     {
                     //zamiana sciezki w ansi string na char
                     char *path=new char[ sciezka.Length()+1 ];
                     strcpy( path, sciezka.c_str() );
                     //odgrywa plik wav z podanej sciezki
                     sndPlaySound(path, SND_ASYNC);
                     }
}
//znak jest spacja
else
              {
               //zatrzymanie by zaznaczyc spacje w tekscie
               o_speed=speed+200;
               //przesuniecie do nastepnego znaku w tekscie
               kareta++;
              }



}

 //predkosc odczytu pobrana z pozycji suwaka
Syntezator->Timer1->Interval=o_speed;

 //---jesli to juz koniec zatrzymujemy petle
 if (total_znakow<=kareta+1)
      {
      //odznacz tekst
      memo_tekst->SelLength=0;

      Syntezator->Timer1->Enabled=false;

      if (bledy_odczytu==true)
         {
          String bufor=":SYNT:Nie wszystko odczytane poprawnie";
          pCB->AsText=bufor;
         }

      }


}
//-----------------------------TEST SCHOWKA-----------------------------------
//jesli w schowku bedzie tekst i bedzie zaczynal sie od ":SYNT"
//to go pobierze wyczysci schowek i odczyta to co pobral
void __fastcall TSyntezator::test_schowkaTimer(TObject *Sender)
{


if (pCB->HasFormat(CF_OEMTEXT))
  {
  String bufor= pCB->AsText;
  if (bufor.Pos(":SYNT:"))
     {
     bufor=bufor.Delete(1,6);
     Syntezator->memo_tekst->Clear();
     Syntezator->memo_tekst->Text=bufor+" ";

     start_czytania();
     pCB->Clear();
     }
  }
}
//-----------------------------------ZAPISANIE USTAWIEN----------------------
void __fastcall TSyntezator::Img_zapiszClick(TObject *Sender)
{
//zapisuje ustawienia
zapisz_konfiguracje_sampli();
}
//---------------------------USUWANIE SAMPLA----------------------------------
void __fastcall TSyntezator::Img_usunClick(TObject *Sender)
{
//zliczanie elementow listy, podaje wartosc od 1 do n
int ilosc=Syntezator->lista_sampli->Items->Count;

//poniewaz listbox indeksowany jest od 0 do n odejmujemy 1
int index=ilosc-1;

//Uwaga sprawdzanie zaczynamy od tylu bo nie mozna usuwac od przodu
//poniewaz ilosc po usunieciu by sie nie zgadzala
while (index!=-1)
 {
   //jesli dane pole jest zaznaczone
   if(Syntezator->lista_sampli->Checked[index])
      {
      //usuwamy je
      Syntezator->lista_sampli->Items->Delete(index);
      }
   //idziemy o pole nizej
   index--;
 }        
}
//----------------------------Odsluchanie jednego sampla------------------------

void __fastcall TSyntezator::Img_testClick(TObject *Sender)
{
//Pobranie tekstu jaki jest zanzaczony w listboxie
AnsiString sampl=lista_sampli->Items->Strings[lista_sampli->ItemIndex];

AnsiString a_path=path_sampli+"//"+sampl+".wav";
//zamiana String na char-
char ch_path[20];
sprintf(ch_path, "%s", a_path.c_str());

   sndPlaySound(ch_path, SND_ASYNC);
}
//---------------------Zmiana predkosci odczytu---------------------------------
void __fastcall TSyntezator::track_predkoscChange(TObject *Sender)
{
speed=track_predkosc->Position;
}
//------------------------------Przelaczenie do trybu mini---------------------
void __fastcall TSyntezator::Karnacja1Click(TObject *Sender)
{
 szerokosc=386;
 Syntezator->Width=szerokosc;
 zapisz_konfiguracje_syntezatora();
}
//-----------------------------------------------------------------------------

void __fastcall TSyntezator::Professional1Click(TObject *Sender)
{
szerokosc=860;
Syntezator->Width=szerokosc;
zapisz_konfiguracje_syntezatora();
}
//---------------------------Czysc-------------------------------------------
void __fastcall TSyntezator::CzyscClick(TObject *Sender)
{
 memo_tekst->Lines->Clear();
tekst="";
}
//----------------------------Zacznij czytac-------------------------------------------

void __fastcall TSyntezator::Image1Click(TObject *Sender)
{

memo_tekst->Text=memo_tekst->Text+" ";
//zaznaczanie tekstu
memo_tekst->SelStart=0;

Progress_struktur->Visible=true;
Progress_struktur->Max=szukaj_wolnego_w_strukturze();

//jesli ma analizowac struktury w tekscie
if (Check_struktury->Checked)
    {
     int z=0;
     while(z<szukaj_wolnego_w_strukturze())
          {
          String string_t=memo_tekst->Text;
          Strukt[z].analizuj(string_t);
          Progress_struktur->Position=z;
          z++;
          }
    }

 Progress_struktur->Visible=false;
 start_czytania();
}
//----------------------------------Wyswietla Helpa------------------------------------
void __fastcall TSyntezator::Help1Click(TObject *Sender)
{
 ShowMessage("Testowy Syntezator Mowy\n  (C)Marcin Filipiak \n         2007");
}
//-------------------------------Wczytaj Text----------------------------------------

void __fastcall TSyntezator::Wczytaj1Click(TObject *Sender)
{
if (Syntezator->Open_czytania->Execute())
{
 memo_tekst->Lines->Clear();
 memo_tekst->Lines->LoadFromFile(Open_czytania->FileName);
}
}



//----------------------------Zmiana na angielski-------------------------------
void __fastcall TSyntezator::English1Click(TObject *Sender)
{
 ustaw_interface("En");
 zapisz_konfiguracje_syntezatora();
 Load_Grid();
}
//-----------------------------Zmiana na polski-------------------------------

void __fastcall TSyntezator::Polski1Click(TObject *Sender)
{
 ustaw_interface("Pl");
 zapisz_konfiguracje_syntezatora();
 Load_Grid();
}
//-------------------------------Zmiana rozmiaru formy---------------------------
//blokada rozmiaru by nie maksymalizowac
void __fastcall TSyntezator::FormResize(TObject *Sender)
{
 Syntezator->Width=szerokosc;
 Syntezator->Height=421;
}
//------------------------------------Wybranie bazy-----------------------------------
void __fastcall TSyntezator::combo_bazaChange(TObject *Sender)
{
AnsiString b="sample//"+Syntezator->combo_baza->Items->Strings[Syntezator->combo_baza->ItemIndex]+".synt";

TIniFile *PlikIni=new TIniFile(b);
speed=PlikIni->ReadInteger("Odczyt","predkosc_odczytu",300);
czas_spacji=PlikIni->ReadInteger("Odczyt","czas_spacji",100);
path_sampli="sample//"+PlikIni->ReadString("Sample","sciezka","pl_basic//");
delete PlikIni;

//wczytanie z pliku do list boxa
Syntezator->lista_sampli->Items->LoadFromFile(path_sampli+"index.txt");
//zliczenie elementow w listboxie zwraca wartosc od 1 do n
int liczba_sampli=Syntezator->lista_sampli->Items->Count;
//pokazanie informacji ile elementow w list boxie (ilosc sampli)
//Syntezator->label_liczba_sampli->Caption="Sampli: "+IntToStr(liczba_sampli);
//predkosc odczytu
Syntezator->track_predkosc->Position=speed;

//wczytywanie struktury
odczytaj_strukture(path_sampli+"struktury.dat");
//wpisanie do siatki
Load_Grid();

}
//---------------------------------------------------------------------------

