//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
int wczytany=0;
AnsiString katalog;
AnsiString interface_jezyk;

#include "struktura_edycyjna.cpp"
//----------------------Wczytaj do edytora-----------------------------------
void Load_Edit(int i)
{
Form1->Edit_przed->Text="";
Form1->Edit_po->Text="";

Form1->Edit_haslo->Text=Strukt[i].haslo;
Form1->Edit_efektor->Text=Strukt[i].efektor;
  if (Strukt[i].przed==true)   Form1->Edit_przed->Text=Strukt[i].maska;
  if (Strukt[i].po==true)   Form1->Edit_po->Text=Strukt[i].maska;
}
//----------------------Wczytaj siatke---------------------------------------
void Load_Grid()
{
//czyszczenie siatki
for(int a =0;a<Form1->StringGrid1->RowCount;a++)
Form1->StringGrid1->Rows[a]->Clear();

if (interface_jezyk=="Pl")
   {
    //opisy siatki Polskie
    Form1->StringGrid1->Cells[0][0] = "haslo";
    Form1->StringGrid1->Cells[1][0] = "maska";
    Form1->StringGrid1->Cells[2][0] = "efekt";
    Form1->StringGrid1->Cells[3][0] = "prefiks";
    Form1->StringGrid1->Cells[4][0] = "sufiks";
   }
if (interface_jezyk=="En")
   {
    //opisy siatki Angielskie
    Form1->StringGrid1->Cells[0][0] = "password";
    Form1->StringGrid1->Cells[1][0] = "mask";
    Form1->StringGrid1->Cells[2][0] = "effect";
    Form1->StringGrid1->Cells[3][0] = "prefix";
    Form1->StringGrid1->Cells[4][0] = "sufix";
   }

 //Wczytywanie do siatki
 for(int i = 0; i < 100; i++)
  {
  Form1->StringGrid1->Cells[0][i + 1] = Strukt[i].haslo;
  Form1->StringGrid1->Cells[1][i + 1] = Strukt[i].maska;
  Form1->StringGrid1->Cells[2][i + 1] = Strukt[i].efektor;
  if (Strukt[i].przed==true)   Form1->StringGrid1->Cells[3][i + 1] = "X";
  if (Strukt[i].po==true)   Form1->StringGrid1->Cells[4][i + 1] = "X";

  Form1->StringGrid1->RowCount++;
  }

 Form1->StringGrid1->RowCount--;
 //koniec siatki

 Form1->Progress->Position=szukaj_wolnego_w_strukturze()-1;
}
//---------------------------zmiana jezyka-----------------------------------
void jezyk(AnsiString ln)
{
if (ln=="En")
    {
     interface_jezyk="En";
     Form1->Button_Add->Caption="Add";
     Form1->Button_edit->Caption="Edit";
     Form1->Button_delete->Caption="Delete";
     Form1->GroupBox1->Caption="Add/Edit/Delete Structure";
     Form1->Button_zapisz->Caption="Save";
     Form1->GroupBox2->Caption="Select data base";
     Form1->English1->Caption="English";
     Form1->Jezyk1->Caption="Polski";
     Form1->Caption="Structure Analizer";
     Load_Grid();
    }
if (ln=="Pl")
    {
     interface_jezyk="Pl";
     Form1->Button_Add->Caption="Dodaj";
     Form1->Button_edit->Caption="Edytuj";
     Form1->Button_delete->Caption="Usun";
     Form1->GroupBox1->Caption="Dodaj/Edytuj/Usun Strukture";
     Form1->Button_zapisz->Caption="Zapisz";
     Form1->GroupBox2->Caption="Wybierz Baze";
     Form1->Jezyk1->Caption="Polski";
     Form1->English1->Caption=" English";
     Form1->Caption="Analizator Struktur";
     Load_Grid();
    }
}
//---------------------------MAIN--------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
//wczytanie baz
Form1->lista_bazy_sampli->Items->LoadFromFile("sample/baza.txt");
}
//-----------------------------Dodanie Nowego---------------------------------
void __fastcall TForm1::Button_AddClick(TObject *Sender)
{
int wolny=szukaj_wolnego_w_strukturze();
ShowMessage("zapisany pod id:"+IntToStr(wolny)+" w strukturze");


sprintf(Strukt[wolny].efektor,"%s",Edit_efektor->Text); //ustawianie efektora
sprintf(Strukt[wolny].haslo,"%s",Edit_haslo->Text); //ustawianie hasla wywolawczego

Strukt[wolny].przed=false;
Strukt[wolny].po=false;

if (Edit_przed->Text.Length()!=0){Strukt[wolny].przed=true; sprintf(Strukt[wolny].maska,"%s",Edit_przed->Text);}
if (Edit_po->Text.Length()!=0){Strukt[wolny].po=true; sprintf(Strukt[wolny].maska,"%s",Edit_po->Text);}


strukturyzacja();
Load_Grid();
}
//----------------------------Klikniecie w grida-----------------------------
void __fastcall TForm1::StringGrid1Click(TObject *Sender)
{
wczytany=(StringGrid1->Row)-1;
Load_Edit(wczytany);
}
//-------------------------------EDYCJA-------------------------------------
void __fastcall TForm1::Button_editClick(TObject *Sender)
{

sprintf(Strukt[wczytany].efektor,"%s",Edit_efektor->Text); //ustawianie efektora
sprintf(Strukt[wczytany].haslo,"%s",Edit_haslo->Text); //ustawianie hasla wywolawczego

Strukt[wczytany].przed=false;
Strukt[wczytany].po=false;

if (Edit_przed->Text.Length()!=0){Strukt[wczytany].przed=true; sprintf(Strukt[wczytany].maska,"%s",Edit_przed->Text);}
if (Edit_po->Text.Length()!=0){Strukt[wczytany].po=true; sprintf(Strukt[wczytany].maska,"%s",Edit_po->Text);}


strukturyzacja();
Load_Grid();
}
//--------------------------------USUWANIE------------------------------------
void __fastcall TForm1::Button_deleteClick(TObject *Sender)
{
sprintf(Strukt[wczytany].maska,"%s","");
sprintf(Strukt[wczytany].haslo,"%s","");
sprintf(Strukt[wczytany].efektor,"%s","");

Strukt[wczytany].przed=false;
Strukt[wczytany].po=false;

strukturyzacja();
Load_Grid();
}
//-----------------------------Wczytanie bazy------------------------------------
void __fastcall TForm1::lista_bazy_sampliClick(TObject *Sender)
{
//zliczanie elementow listy, podaje wartosc od 1 do n
int ilosc=Form1->lista_bazy_sampli->Items->Count;

//poniewaz listbox indeksowany jest od 0 do n odejmujemy 1
int index=ilosc-1;

//Uwaga sprawdzanie zaczynamy od tylu
while (index!=-1)
 {

    //jesli dana baza jest zaznaczona na liscie
    if(Form1->lista_bazy_sampli->Selected[index])
      {
      //Pobranie tekstu jaki jest zanzaczony w listboxie
      katalog=lista_bazy_sampli->Items->Strings[lista_bazy_sampli->ItemIndex];
      odczytaj_strukture("sample//"+katalog+"//Struktury.dat");
      //strukturyzacja();
      Load_Grid();

      }
     //idziemy o pole nizej
   index--;
 }

}
//--------------------------------Zapisz zmiany---------------------------------------
void __fastcall TForm1::Button_zapiszClick(TObject *Sender)
{
 zapisz_strukture("sample//"+katalog+"//Struktury.dat");
}
//----------------------------Jezyk Polski-------------------------------------
void __fastcall TForm1::Jezyk1Click(TObject *Sender)
{
jezyk("Pl");
}
//-----------------------------Jezyk Angielski---------------------------------
void __fastcall TForm1::English1Click(TObject *Sender)
{
jezyk("En");
}
//---------------------------------------------------------------------------


