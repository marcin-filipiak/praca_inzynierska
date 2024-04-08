//
void ustaw_interface(String ln)
{
if (ln=="Pl")
    {
     jezyk_interface="Pl";
     Syntezator->GroupBox1->Caption="Predkosc odczytu";
     Syntezator->GroupBox2->Caption="Baza Sampli";
     Syntezator->GroupBox3->Caption="Struktury";
     Syntezator->Check_struktury->Caption="Analizuj struktury w tekscie";
     Syntezator->Plik1->Caption="Plik";
     Syntezator->Wczytaj1->Caption="Otworz";
     Syntezator->Save1->Caption="Zapisz";
     Syntezator->Widok1->Caption="Widok";
     Syntezator->Karnacja1->Caption="Prosty";
     Syntezator->Professional1->Caption="Profesionalny";
     Syntezator->Jezyk1->Caption="Jezyk";
     Syntezator->Polski1->Caption=" Polski";
     Syntezator->English1->Caption="  Angielski";
     Syntezator->combo_baza->Text="Wybierz baze";
     //Syntezator->Text_baza->Caption=path_sampli;
     }
if (ln=="En")
     {
     jezyk_interface="En";
     Syntezator->GroupBox1->Caption="Readout speed";
     Syntezator->GroupBox2->Caption="Samples";
     Syntezator->GroupBox3->Caption="Structures";
     Syntezator->Check_struktury->Caption="Analyze structures in the text";
     Syntezator->Plik1->Caption="File";
     Syntezator->Wczytaj1->Caption="Open";
     Syntezator->Save1->Caption="Save";
     Syntezator->Widok1->Caption="View";
     Syntezator->Karnacja1->Caption="Easy";
     Syntezator->Professional1->Caption="Professional";
     Syntezator->Jezyk1->Caption="Language";
     Syntezator->Polski1->Caption="  Polish";
     Syntezator->English1->Caption=" English";
     Syntezator->combo_baza->Text="Select data base";
//     Syntezator->Text_baza->Caption=path_sampli;
     }
}

//----------------------Wczytaj siatke---------------------------------------
void Load_Grid()
{
//czyszczenie siatki
for(int a =0;a<Syntezator->StringGrid1->RowCount;a++)
Syntezator->StringGrid1->Rows[a]->Clear();

if (jezyk_interface=="Pl")
   {
   //opisy siatki Polski
   Syntezator->StringGrid1->Cells[0][0] = "haslo";
   Syntezator->StringGrid1->Cells[1][0] = "maska";
   Syntezator->StringGrid1->Cells[2][0] = "efekt";
   Syntezator->StringGrid1->Cells[3][0] = "prefiks";
   Syntezator->StringGrid1->Cells[4][0] = "sufiks";
   }
if (jezyk_interface=="En")
   {
   //opisy siatki Polski
   Syntezator->StringGrid1->Cells[0][0] = "password";
   Syntezator->StringGrid1->Cells[1][0] = "mask";
   Syntezator->StringGrid1->Cells[2][0] = "effect";
   Syntezator->StringGrid1->Cells[3][0] = "prefix";
   Syntezator->StringGrid1->Cells[4][0] = "sufix";
   }

 //Wczytywanie do siatki
 for(int i = 0; i < 100; i++)
  {
  Syntezator->StringGrid1->Cells[0][i + 1] = Strukt[i].haslo;
  Syntezator->StringGrid1->Cells[1][i + 1] = Strukt[i].maska;
  Syntezator->StringGrid1->Cells[2][i + 1] = Strukt[i].efektor;
  if (Strukt[i].przed==true)   Syntezator->StringGrid1->Cells[3][i + 1] = "X";
  if (Strukt[i].po==true)   Syntezator->StringGrid1->Cells[4][i + 1] = "X";

  Syntezator->StringGrid1->RowCount++;
  }

 Syntezator->StringGrid1->RowCount--;
 //koniec siatki

   Syntezator->Progress->Position=szukaj_wolnego_w_strukturze()-1;
}


//-------------------------wyciaga znak w typie char z tekstu--------------------------
char get_znak(int pozycja)
{
//Trzeba zamienic wszystko jednolicie na male znaki
//i pobrac tylko jeden znak, pobieramy w ascii
int ascii_znak=tolower(tekst[pozycja]);
//zamiana ascii na char
char char_znak=(char)ascii_znak;
return char_znak;
}

//-------------------------Czy jest taki sampel-----------------------------
bool sprawdz_sampel(AnsiString sampel)
{
int index=Syntezator->lista_sampli->Items->IndexOf(sampel);
if (index>-1)
    { return true; }
                    else
                       { return false; }
}

//-------------------------KONFIGURACJA BAZY SAMPLI-------------------------------------
void zapisz_konfiguracje_sampli()
{
AnsiString b="sample//"+Syntezator->combo_baza->Items->Strings[Syntezator->combo_baza->ItemIndex]+".synt";
TIniFile *PlikIni=new TIniFile(b);
PlikIni->WriteInteger("Odczyt","predkosc_odczytu",speed);
PlikIni->WriteInteger("Odczyt","czas_spacji",100);
PlikIni->WriteString("Sample","sciezka",path_sampli);
delete PlikIni;
if (jezyk_interface=="Pl") ShowMessage("Ustawienia zapisane");
if (jezyk_interface=="En") ShowMessage("All changes save");
}



//-----------------------START CZYTANIA--------------------------------------
void start_czytania()
{
if (Syntezator->lista_sampli->Items->Count>0)
   {
   //ustawienie predkosci na suwaku
   speed=Syntezator->track_predkosc->Position;

  //wczytanie tekstu do zmiennej tekst
  tekst=Syntezator->memo_tekst->Text+"  ";

  //wywalanie enterow itp. tworzenie ciagu tekstu
  //zamiana macierzy 2 wymiarowej na 1 wymiarowa
  for(int z=1; z<tekst.Length(); z++)
     {
     if (tekst[z]=='\n' || tekst[z]=='\r')
        {
        tekst[z]=' ';
        }
     }

  //ustawienie sie na poczatek tekstu
  kareta=1;

  bledy_odczytu=false;

  Syntezator->Timer1->Enabled=true; //wlacz petle czytajaca
  total_znakow=tekst.Length(); //ile znakow ma caly tekst
                                 //minus dwa jesli konczy sie enterem
  }
   else
       {
       if (jezyk_interface=="Pl") ShowMessage("Wczytaj najpierw baz� sampli!");
       if (jezyk_interface=="En") ShowMessage("Load first base of samples");
       }
}

//-------------------------KONFIGURACJA SYNTEZATORA-----------------------------
void zapisz_konfiguracje_syntezatora()
{
TIniFile *PlikKonf=new TIniFile("pliki_pomocnicze\syntezator.txt");

if ( Syntezator->Width==386 ) PlikKonf->WriteInteger("Okno","tryb",1);
if (Syntezator->Width!=386 ) PlikKonf->WriteInteger("Okno","tryb",2);

if (jezyk_interface=="Pl") PlikKonf->WriteString("Interface","jezyk","Pl");
if (jezyk_interface=="En") PlikKonf->WriteString("Interface","jezyk","En");

delete PlikKonf;
}


void odczytaj_konfiguracje_syntezatora()
{
TIniFile *PlikKonf=new TIniFile("pliki_pomocnicze\syntezator.txt");

int tryb=PlikKonf->ReadInteger("Okno","tryb",2);
if (tryb==1) { Syntezator->Width=386; szerokosc=386;}
     else  { Syntezator->Width=860; szerokosc=860;}

AnsiString ln=PlikKonf->ReadString("Interface","jezyk","Pl");
ustaw_interface(ln); 

delete PlikKonf;
}



