#include <string.h>
#include <stdio.h>

#include "fstream.h"//PLIKI


//-----------------------FUNKCJE POMOCNICZE-------------------------------------

//sprawdza dlugosc tekstu char
int dlugosc(char tekst[])
{
 int i=0;
 while (tekst[i]!='\0')
        {
        ++i;
        }
return i;

}    

//wyszukiwanie ciagu; !0 znaleziono w ciagu,0 nie znaleziono
int szukaj(String ciag, String szukana)
{
return ciag.Pos(szukana);
}

//funkcja wycina z tekstu od do podanego miejsca i zwraca wyciety text
String wytnij(int od, int to, String ciag)
{
String bufor;
for (int x=od;x<=to;x++)
    {
    bufor=bufor+ciag[x];
    }
return bufor;
}

//----------------------DEFINICJA STRUKTURY------------------------------------
struct klucz
{
bool przed;
bool po;
char maska[4];
char haslo[20];
char efektor[30];
};

//-------------------------WEKTOR STRUKTURY-------------------------------------
klucz Strukt[99]; //od 0 do 99 = 100
//---------------------PROCEDURY WEKTORA STRUKTURY------------------------------

void zapisz_strukture(String path)
{
/*zapis struktury do pliku*/
/* fstream outfile;
 outfile.open("Test.dat", ios::out | ios::binary);
 outfile.write((char *)&Strukt, sizeof(Strukt));
 outfile.close();*/

 FILE *plik;
 plik = fopen(path.c_str(), "wb");
 fwrite(&Strukt, sizeof(Strukt), 1, plik);
 fclose(plik);
}

void odczytaj_strukture(String path)
{
/*odczyt struktury z pliku*/
 fstream infile;
 infile.open(path.c_str(), ios::in | ios::binary);
 infile.read((char *)&Strukt, sizeof(Strukt));
 infile.close();
}

int szukaj_wolnego_w_strukturze()
{
for (int x=0;x<100;x++)  //od 0 do 99 =100
     {
     if (dlugosc(Strukt[x].haslo)==0)
        {
        return x;
        break;
        }
     }
}

void strukturyzacja()
{
int i = 0;
//ustawianie na poczatek wektora wartosci z dluzsza maska #
for (i=0;i<100;i++)//id struktury do jakiej porownujemy
     {
     for (int y=0;y<100;y++)//id struktury porownywanej
          {
           if (dlugosc(Strukt[i].maska)>dlugosc(Strukt[y].maska) && dlugosc(Strukt[i].haslo)!=0 && dlugosc(Strukt[y].haslo)!=0) //jesli ta do jakiej sie porownuje jest mniejsza od tej drogiej
              {
              //mniejsza do bufora, wieksza do mniejszej, bufor do wiekszej
             // bool z=Strukt[i].przed;
             // Strukt[i].przed=Strukt[y].przed ;
             // Strukt[y].przed=z;


             // bool c=Strukt[i].po;
             // Strukt[i].po=Strukt[y].po;
             // Strukt[y].po=c;


             // char b_maska[4];
             // strcpy(b_maska,Strukt[i].maska);
             // strcpy(Strukt[i].maska,Strukt[y].maska);
             // strcpy(Strukt[y].maska,b_maska);

             // char b_haslo[20];
             // strcpy(b_haslo, Strukt[i].haslo);
             // strcpy(Strukt[i].haslo,Strukt[y].haslo);
             // strcpy(Strukt[y].haslo,b_haslo);

             // char b_efektor[30];
             // strcpy(b_efektor, Strukt[i].efektor);
             // strcpy(Strukt[i].efektor,Strukt[y].efektor);
             // strcpy(Strukt[y].efektor,b_efektor);

              }

           if  (dlugosc(Strukt[i].haslo)==0 && i<99)
                  {
            //  Strukt[i].po=Strukt[i+1].po;
            //  Strukt[i].przed=Strukt[i+1].przed;
            //  strcpy(Strukt[i].maska,Strukt[i+1].maska);
            //  strcpy(Strukt[i].haslo,Strukt[i+1].haslo);
            //  strcpy(Strukt[i].efektor,Strukt[i+1].efektor);

                  }
          }
     }
}
