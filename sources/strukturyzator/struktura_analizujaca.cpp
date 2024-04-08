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
//---------------------------------------------------
//wyszukiwanie ciagu; !0 znaleziono w ciagu,0 nie znaleziono
int szukaj(String ciag, String szukana)
{
return ciag.Pos(szukana);
}
//---------------------------------------------------
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
//---------------------------------------------------
bool sprawdz(String tekst,String szukana,int pozycja)
{
int a=0;
 while(a<szukana.Length())
  {
  a++;
  if (szukana[a]!=tekst[pozycja+a-1])
     {
     return false;
     break;
     }
  }
  return true;
}

//----------------------DEFINICJA STRUKTURY------------------------------------
struct klucz
{
bool przed;
bool po;
char maska[4];
char haslo[20];
char efektor[30];
String analizuj(String ciag);
};
//---------------------PROCEDURY STRUKTURY--------------------------------------

String klucz::analizuj(String ciag)
{
//analizuje podany ciag znakowy
//i zamienia znaki hasla na efektory zgodnie z zasadami
//maski jaka sie pojawia przed lub po zdefiniowanym hasle

int int_maska=dlugosc(maska);

int x=1;
while(x<ciag.Length())
    {

    String buf_to_compare=ciag[x];   // == tak mozna porownac tylko dwa stringi wiec przepisanie do stringu
    String buf2=haslo;
      if (sprawdz(ciag,buf2,x)==true) //znaleziono haslo
       {
       buf_to_compare=maska[0];

       //jesli sprawdzenie nie wyjdzie poza dlugosc a trzeba w przod
        if ((x+int_maska+1)<=ciag.Length() && po==true)
            {
            if (buf_to_compare=="#")
               {
               //wyciecie z tekstu od miejsca gdzie znaleziono haslo
               //tyle w przod ile ma maska
               //teraz sprawdzic czy nie ma spacji a  potem czy jest
              if ( szukaj( wytnij(x,(x+int_maska),ciag) ," ")==0 && szukaj( wytnij(x,(x+int_maska+1),ciag) ," ")!=0)
                   {
                    ciag.Delete(x,dlugosc(haslo));
                    ciag.Insert(efektor,x);
                   }
               }
            }

        //jesli sprawdzenie nie wyjdzie poza poczatek a trzeba w tyl
        if (int_maska<x && przed==true)
            {
            if (buf_to_compare=="#")
               {
               //wyciecie z tekstu od miejsca gdzie znaleziono haslo
               //tyle w tyl ile ma maska , jak wycina sie w tyl to trzeba
               // obliczyc poczatek (haslo-maska) i do miejsca gdzie jest haslo
               //teraz sprawdzic czy nie ma spacji
               if ( szukaj( wytnij((x-int_maska),x,ciag) ," ")==0)
                   {
                    ciag.Delete(x,dlugosc(haslo));
                    ciag.Insert(efektor,x);
                   }
               }
            }
            
                   if (po==false && przed==false )
          {
          if (x<ciag.Length()-dlugosc(haslo) && x>ciag.Length()+dlugosc(haslo))
           {
           if(szukaj(wytnij(x,x+dlugosc(haslo),ciag)," ")!=0 && szukaj(wytnij(x-dlugosc(haslo),x,ciag)," ")!=0 )
             {
              ciag.Delete(x,dlugosc(haslo));
              ciag.Insert(efektor,x);
             }
            }
             else
                 {
                 ciag.Delete(x,dlugosc(haslo));
                 ciag.Insert(efektor,x);
                 }
           }

       }
    x++;

//oddanie zmienionego tekstu
        Syntezator->memo_tekst->Clear();
        Syntezator->memo_tekst->Text=ciag;
    }

}

//-------------------------WEKTOR STRUKTURY-------------------------------------
klucz Strukt[99]; //od 0 do 99 = 100
//---------------------PROCEDURY WEKTORA STRUKTURY------------------------------

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
