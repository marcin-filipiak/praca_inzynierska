//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"

#include "../strukturyzator/struktura_edycyjna.cpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

AnsiString tekst;

TKreator *Kreator;

AnsiString interface_jezyk;


//---------------------------zmiana jezyka-----------------------------------
void jezyk(AnsiString ln)
{
if (ln=="En")
    {
     interface_jezyk="En";
     Kreator->English1->Caption="English";
     Kreator->Polski1->Caption="Polski";
     Kreator->Caption=".::Creator::.";
     Kreator->GroupBox1->Caption="Alphabet";
     Kreator->GroupBox2->Caption="Text for analysis";
     Kreator->GroupBox3->Caption="Powiazania";
     Kreator->GroupBox4->Caption="Informations";
     Kreator->GroupBox5->Caption="Samples";
     Kreator->button1->Caption="(1)Build alphabet";
     Kreator->button2->Caption="(2)Connections analysis";
     Kreator->Button3->Caption="(3)Samples";
     Kreator->Button4->Caption="(4)Sampling";
     Kreator->Label1->Caption="New:";
     Kreator->Label2->Caption="New:";
     Kreator->label_alfabetu->Caption="Alphabet: ??";
     Kreator->label_powiazan->Caption="Connections: ??";
     Kreator->label_sampli->Caption="Samples: ??";
     Kreator->StaticText1->Caption="Base name:";
     Kreator->Memo1->Text="The program builds alphabet, creates a diphones base for a given language. Please read in from a file or write in by hand a possibly longest text in any language, and next clicking on the buttons marked from (1) to (3) will cause the text analysis. Next, please give the name of created base and click on the diskette icon to write in data. Next step is assignment of sound equivalents to character patterns. To do it, click the (4).";
    }
if (ln=="Pl")
    {
     interface_jezyk="Pl";
     Kreator->Polski1->Caption="Polski";
     Kreator->English1->Caption=" English";
     Kreator->Caption=".::Kretor::.";
     Kreator->GroupBox1->Caption="Alfabet";
     Kreator->GroupBox2->Caption="Tekst do analizy";
     Kreator->GroupBox3->Caption="Powiazania";
     Kreator->GroupBox4->Caption="Informacje";
     Kreator->GroupBox5->Caption="Sample";
     Kreator->button1->Caption="(1)Buduj alfabet";
     Kreator->button2->Caption="(2)Analiza powiazan";
     Kreator->Button3->Caption="(3)Sample";
     Kreator->Button4->Caption="(3)Samplowanie";
     Kreator->Label1->Caption="Nowy:";
     Kreator->Label2->Caption="Nowy:";
     Kreator->label_alfabetu->Caption="Alfabet: ??";
     Kreator->label_powiazan->Caption="Powiazania: ??";
     Kreator->label_sampli->Caption="Sampli: ??";
     Kreator->StaticText1->Caption="Nazwa bazy:";
     Kreator->Memo1->Text="Program buduje alfabet, tworzy baz� difon�w, oraz s�u�y dla danego j�zyka. Prosz�  wczyta� z pliku lub wpisa� r�cznie  mo�liwie najd�uzszy tekst w dowolnym j�zyku a nastepnie klikaj�c w przyciski  oznaczone od (1) do (3) zostanie przeprowadzona analiza tekstu. Nastepnie prosz� poda� nazw� tworzonej bazy i klikn�� ikon� dyskietki, by zapisac dane. Kolejnym  etapem jest przypisywanie odpowiednik�w d�wi�kowych wzorcom znakowym. By tego dokona� kliknij (4).";
    }
}
//-------------------------Aktualizuje napisy statystyczne---------------------------
void aktualizuj_napisy()
{
//zliczenie elementow w listboxie zwraca wartosc od 1 do n
int liczba_w_alfabecie=Kreator->alfabet->Items->Count;
//Wyswietlenie informacji ile znakow ma alfabet
Kreator->label_alfabetu->Caption="Alfabet: "+IntToStr(liczba_w_alfabecie);

//zliczenie elementow w listboxie zwraca wartosc od 1 do n
int liczba_powiazan=Kreator->powiazania->Items->Count;
//Wyswietlenie informacji ile powiazan liter znaleziono w tekscie
Kreator->label_powiazan->Caption="Powiazania: "+IntToStr(liczba_powiazan);

Kreator->label_sampli->Caption="Sampli: "+IntToStr(liczba_powiazan+liczba_w_alfabecie);

}
//-------------------------Czy znak juz jest w alfabecie-----------------------------
bool czy_jest_w_alfabecie(AnsiString sampel)
{
int index=Kreator->alfabet->Items->IndexOf(sampel);
if (index>-1)
    { return true; }
                    else
                       { return false; }
}
//-------------------------Czy znak juz jest w bazie powiazan-------------------------
bool czy_jest_w_bazie_powiazan(AnsiString sampel)
{
int index=Kreator->powiazania->Items->IndexOf(sampel);
if (index>-1)
    { return true; }
                    else
                       { return false; }
}
//-------------------------wyciaga znak w typie char z tekstu--------------------------
AnsiString get_znak(int pozycja)
{
//Trzeba zamienic wszystko jednolicie na male znaki
//i pobrac tylko jeden znak, pobieramy w ascii
int ascii_znak=tolower(tekst[pozycja]);
//zamiana ascii na char
AnsiString znak=(char)ascii_znak;
return znak;
}
//-----------------------------------MAIN-------------------------------------
__fastcall TKreator::TKreator(TComponent* Owner)
        : TForm(Owner)
{
}
//--------------------------Recznie Dopisz znak do alfabetu--------------------------------------------

void __fastcall TKreator::dodaj_do_alfabetuClick(TObject *Sender)
{
Kreator->alfabet->Items->Add(Kreator->edit_znak->Text);
aktualizuj_napisy();
}
//-----------------------Usuwanie znaku z alfabetu------------------------------------------------
void __fastcall TKreator::usun_z_alfabetuClick(TObject *Sender)
{
//zliczanie elementow listy, podaje wartosc od 1 do n
int ilosc=Kreator->alfabet->Items->Count;

//poniewaz listbox indeksowany jest od 0 do n odejmujemy 1
int index=ilosc-1;

//Uwaga sprawdzanie zaczynamy od tylu bo nie mozna usuwac od przodu
//poniewaz ilosc po usunieciu by sie nie zgadzala
while (index!=-1)
 {
   //jesli dane pole jest zaznaczone
   if(Kreator->alfabet->Checked[index])
      {
      //usuwamy je
      Kreator->alfabet->Items->Delete(index);
      }
   //idziemy o pole nizej
   index--;
 }

aktualizuj_napisy();


}
//--------------------------Recznie Dopisz powiazanie--------------------------------------------

void __fastcall TKreator::dodaj_powiazanieClick(TObject *Sender)
{
Kreator->powiazania->Items->Add(Kreator->edit_powiazanie->Text);

aktualizuj_napisy();

}
//-----------------------Usuwanie powiazania------------------------------------------------
void __fastcall TKreator::usun_powiazanieClick(TObject *Sender)
{
//zliczanie elementow listy, podaje wartosc od 1 do n
int ilosc=Kreator->powiazania->Items->Count;

//poniewaz listbox indeksowany jest od 0 do n odejmujemy 1
int index=ilosc-1;

//Uwaga sprawdzanie zaczynamy od tylu bo nie mozna usuwac od przodu
//poniewaz ilosc po usunieciu by sie nie zgadzala
while (index!=-1)
 {
   //jesli dane pole jest zaznaczone
   if(Kreator->powiazania->Checked[index])
      {
      //usuwamy je
      Kreator->powiazania->Items->Delete(index);
      }
   //idziemy o pole nizej
   index--;
 }

aktualizuj_napisy();



}
//----------------------------Alfabet z tekstu-------------------------------------------
void __fastcall TKreator::button1Click(TObject *Sender)
{
//pobranie tekstu
tekst=Kreator->memo_tekst->Text;

//kursor w tekscie na poczatek
int kareta=1;

//ile znakow ma caly tekst
int total_znakow=tekst.Length(); //minus dwa jesli konczy sie enterem

//ustalenie konca na pasku postepu
Kreator->Progress->Max=total_znakow;
//ustawienie na poczatku
Kreator->Progress->Position=0;

while (kareta<total_znakow)
 {
 //jesli znaku nie ma w alfabecie i jesli znak nie jest spacja
 if (czy_jest_w_alfabecie(get_znak(kareta))==false && get_znak(kareta)!=' ')
     {
     //dodaj znak to spisu alfabetu
     Kreator->alfabet->Items->Add(get_znak(kareta));
     }

 //nastepny znak
 kareta++;

  //krok do przodu paska progresu
 Kreator->Progress->Position=kareta;
 }

aktualizuj_napisy();

Kreator->Progress->Position=0;

}
//------------------------------Otwiera tekst z pliku------------------------------------void __fastcall TKreator::Openfromfile1Click(TObject *Sender)
void __fastcall TKreator::Openfromfile1Click(TObject *Sender)
{
if (Kreator->OpenDialog->Execute())
Kreator->memo_tekst->Lines->LoadFromFile(Kreator->OpenDialog->FileName);

}
//-------------------------------Analiza powiazan----------------------------------------

void __fastcall TKreator::button2Click(TObject *Sender)
{

if (Kreator->alfabet->Items->Count>0)
{
//pobranie tekstu
tekst=Kreator->memo_tekst->Text;

//kursor w tekscie na poczatek
int kareta=1;

//ile znakow ma caly tekst
int total_znakow=tekst.Length(); //minus dwa jesli konczy sie enterem

//ustalenie konca na pasku postepu
Kreator->Progress->Max=total_znakow;
//ustawienie na poczatku
Kreator->Progress->Position=0;

while (kareta<total_znakow)
 {
 //jesli znak nie jest spacja i jego towarzysz tez to mozemy analizowac
 if (get_znak(kareta)!=' ' && get_znak(kareta+1)!=' ')
    {

     if (czy_jest_w_alfabecie(get_znak(kareta)) && czy_jest_w_alfabecie(get_znak(kareta+1)))
        {
         //pobranie znaku i jego towarzysza
         AnsiString dwuznak=get_znak(kareta)+get_znak(kareta+1);

         kareta++;

         //jesli znakow nie ma w bazie powiazan
         if (czy_jest_w_bazie_powiazan(dwuznak)==false)
            {
            //dodaj znak te dwa znaki
            Kreator->powiazania->Items->Add(dwuznak);
            }
         }

    }


 //nastepny znak
 kareta++;

  //krok do przodu paska progresu
 Kreator->Progress->Position=kareta;
 }

aktualizuj_napisy();
Kreator->Progress->Position=0;
}
 else
     {
     ShowMessage("Najpierw dokonaj analizy wyciagajacej alfabet z tekstu \n Nastepnie go przeanalizuj usuwajac niepotrzebne znaki \n potem mozna opracowac powiazania");
     }

}

//----------Zapisanie stworzonej bazy sampli do nagrania do pliku--------------
void __fastcall TKreator::SpeedButton1Click(TObject *Sender)
{
AnsiString katalog=Kreator->edit_nazwa->Text;
CreateDir("sample//"+katalog);
Kreator->lista_sampli->Items->SaveToFile("sample//"+katalog+"//do_nagrania.txt");



//wiertualny stringlist
TStringList* List = new TStringList();
List->LoadFromFile("sample//baza.txt");
List->Add(katalog);
List->SaveToFile("sample//baza.txt");
delete List;

zapisz_strukture("sample//"+katalog+"//Struktury.dat");

ShowMessage("Baza zapisana!");
}
//---------------------------------------------------------------------------

void __fastcall TKreator::Button3Click(TObject *Sender)
{

//zliczanie elementow listy, podaje wartosc od 1 do n
int ilosc=Kreator->alfabet->Items->Count;
//poniewaz listbox indeksowany jest od 0 do n odejmujemy 1
int index=0;

while (index<ilosc)
 {
    AnsiString sampl=alfabet->Items->Strings[index];
    Kreator->lista_sampli->Items->Add(sampl);
   index++;
 }

//zliczanie elementow listy, podaje wartosc od 1 do n
ilosc=Kreator->powiazania->Items->Count;
//poniewaz listbox indeksowany jest od 0 do n odejmujemy 1
index=0;

while (index<ilosc)
 {
    AnsiString sampl=Kreator->powiazania->Items->Strings[index];
    Kreator->lista_sampli->Items->Add(sampl);
   index++;
 }

}
//------------------------------NAGRYWAJ SAMPLE--------------------------------

void __fastcall TKreator::Button4Click(TObject *Sender)
{
WinExec("sampler.exe", SW_SHOW);
Close();
}



//----------------------------na jezyk polski---------------------------------
void __fastcall TKreator::Polski1Click(TObject *Sender)
{
jezyk("Pl");
}
//---------------------------na jezyk angielski-------------------------------

void __fastcall TKreator::English1Click(TObject *Sender)
{
jezyk("En");
}
//---------------------------------------------------------------------------
