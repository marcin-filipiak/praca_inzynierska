#include <vcl.h>
#include <mmsystem.h>

#define DLUGOSC_BUFORA 1024 //obowiazkowo potega 2

class MIC
{
    private:
	HWAVEIN hmic; //uchwyt mikrofonu
        //w ponizszej strukturze znajda sie dane nt. dzwieku
        //(np. liczba kanalow, sampli/sec., bitow/sampel itd.)
        WAVEFORMATEX waveformatex;

	//tu znajda sie parametry buforow, do ktorych zapisywany bedzie dzwiek
	WAVEHDR wavhdr[2];

	//tablica wykorzystywana do tworzenia transformaty
	BYTE bufor[2][DLUGOSC_BUFORA];

        void CheckWaveError(DWORD code); // komunikaty o bledach
        void CheckMMIOError(DWORD code);
        

    public:
     	MIC();
        bool nagrywanie;              // czy wlaczone nagrywanie
        int numer_buf;                // numer bufora, do ktorego dodawane sa probki dzwieku z mikrofonu
        int liczba_nagranych;         // liczba nagranych buforow
        int liczba_buf_wkolejce;      // liczba buforow pozostajacych w kolejce
        bool koniec;
        byte *nagra[10000];           // tablica do zapisywania buforow

	//otwarcie mikrofonu, poczatek przechwytywania dzwieku
	int OpenMic(DWORD *funkcja);
        //funkcja pomocnicza przy zamykaniu mikrofonu
	void CloseMic();

        void SaveWaveFile(char nazwa_pliku[]);
        //funkcja wywolywana przez funkcje sprawdzaj
        void sprawdzaj(HWAVEIN hwi, UINT uMsg, DWORD dwInstance,
                         DWORD dwParam1, DWORD dwParam2);
};
