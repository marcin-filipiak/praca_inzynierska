#include "mic.h"


MIC::MIC()
{
  nagrywanie = false;
  numer_buf = 0;
  liczba_nagranych = 0;
  liczba_buf_wkolejce = 0;
  koniec = false;
};

//ta funkcja inicjalizuje nam mikrofon
int MIC::OpenMic(DWORD *funkcja)
{

  //tu beda zapisywane wartosci zwracane przez funkcje
  MMRESULT result;
  int i;
  //OTWARCIE MIKROFONU

  //wypelniamy strukture typu WAVEFORMATEX na potrzeby funkcji waveInOpen
  waveformatex.wFormatTag = WAVE_FORMAT_PCM; //Pulse Code Modulation (PCM),
                                           //an uncompressed format in which
                                          //each sample represents
                                         //the amplitude of the signal
                                        //at the time of sampling.

  waveformatex.nChannels = 1; //liczba kanalow
  waveformatex.nSamplesPerSec = 11025; //liczba sampli na sec.
  waveformatex.nAvgBytesPerSec = 11025; //liczba bajtow na sec.
  waveformatex.nBlockAlign = 1; //equal to the product of nChannels
                                //and wBitsPerSample divided by 8
  waveformatex.wBitsPerSample = 8; //bity na sampel
  waveformatex.cbSize = 0; //brak "extra information"

  // sprawdzenie czy format prawidlowy
  int Res = waveInOpen(&hmic, WAVE_MAPPER, &waveformatex, 0, 0,
                       WAVE_FORMAT_QUERY);
  if (Res == WAVERR_BADFORMAT)
  {
    MessageBox(NULL, "Nieprawidlowy format", "B��d...", MB_OK | MB_ICONERROR);
    return Res;
  }

  //otwiera urzadzenie waveform-audio (mikrofon) do nagrywania
  result = waveInOpen(&hmic,  //globalnie zdefiniowany uchwyt do mikrofonu
                      WAVE_MAPPER, //id urzadzenia, ktore otwieramy
                      &waveformatex, //wypelniona wczesniej struktura WAVEFORMATEX
                      (DWORD)funkcja, //procedura callbackowa
                      NULL,  //nie wykorzystywany
                      CALLBACK_FUNCTION);

  //jezeli wystapil blad...
  if (result != MMSYSERR_NOERROR)
  {
    MessageBox(NULL, "Nie mo�na otworzy� mikrofonu", "B��d...", MB_OK | MB_ICONERROR);

    return result;
  }

  //PRZYGOTOWANIE BUFOROW I USTAWIENIE ICH DO KOLEJKI NAGRYWANIA
  for (int nr_buf=0;nr_buf<2;nr_buf++)
  {
    wavhdr[nr_buf].lpData = bufor[nr_buf];
    wavhdr[nr_buf].dwBufferLength = DLUGOSC_BUFORA;
    wavhdr[nr_buf].dwFlags = 0;

    result = waveInPrepareHeader(hmic, &wavhdr[nr_buf], sizeof(WAVEHDR));

    if (   (result!= MMSYSERR_NOERROR)
        || ( wavhdr[nr_buf].dwFlags != WHDR_PREPARED))
    {
      MessageBox(NULL, "Nag��wek bufora nie zosta� prawid�owo przygotowany do obs�ugi d�wi�ku",
               "B��d...", MB_OK | MB_ICONERROR);

      return result;
    }

    //wysyla bufor do urzadzenia dzwiekowego (wstawia do kolejki)
    result = waveInAddBuffer(hmic, &wavhdr[nr_buf], sizeof(WAVEHDR));

    if (result!= MMSYSERR_NOERROR)
    {
      MessageBox(NULL, "Bufor nie zosta� prawid�owo wys�any do urz�dzenia d�wi�kowego",
                 "B��d...", MB_OK | MB_ICONERROR);

      return result;
    }
    liczba_buf_wkolejce ++;
  }
  //PROCES NAGRYWANIA

  result = waveInStart(hmic); //zaczyna nagrywac

  if (result != MMSYSERR_NOERROR)
  {
    MessageBox(NULL, "B��d przy pr�bie uruchomienia nagrywania",
               "B��d...", MB_OK | MB_ICONERROR);

   return result;
  }
  return 0;
}
//----------------------------------------------------------------------------
void MIC::CloseMic()
{
  //tu beda zapisywane wartosci zwracane przez funkcje
  MMRESULT result;

  koniec = true;

  // czekam na zamkniecie buforow
  while (liczba_buf_wkolejce){};

  //koniec nagrywania
  result = waveInReset(hmic);

  if (result!= MMSYSERR_NOERROR)
  {
    MessageBox(NULL, "Nie mo�na zwolni� bufora z urz�dzenia d�wi�kowego",
               "B��d...", MB_OK | MB_ICONERROR);
    return;
  }
  //plik<<"Po resecie"<<endl;

  result = waveInStop(hmic);
  if (result!= MMSYSERR_NOERROR)
  {
    MessageBox(NULL, "Nie mog� zastopowac urz�dzenia",
               "B��d...", MB_OK | MB_ICONERROR);
    return;
  }
 //plik<<"po zastopowaniu"<<endl;
  //zamyka mikrofon
  result = waveInClose(hmic);

  if (result!= MMSYSERR_NOERROR)
  {
    MessageBox(NULL, "Nie mo�na zamkn�� mikrofonu",
               "B��d...", MB_OK | MB_ICONERROR);
    return;
  }
  //plik<<"po zamknieciu urzadzenia"<<endl;
}

//---------------------------------------------
void MIC::CheckWaveError(DWORD code)
{
  if (code == 0) return;
  char buff[256];
  // Report a wave out error, if one occurred.
  waveInGetErrorText(code, buff, sizeof(buff));
  MessageBox(NULL, buff, "Wave Error", MB_OK);
}

void MIC::CheckMMIOError(DWORD code)
{
  // Report an mmio error, if one occurred.
  if (code == 0) return;
  char buff[256];
  wsprintf(buff,
    "MMIO Error. Error Code: %d", code);
  MessageBox(NULL,buff, "MMIO Error", 0);
}

// Zapis pliku *.wav
void MIC::SaveWaveFile(char nazwa_pliku[])
{
  // Declare the structures we'll need.
  MMCKINFO ChunkInfo;
  MMCKINFO FormatChunkInfo;
  MMCKINFO DataChunkInfo;

  // Open the file.
  HMMIO handle = mmioOpen(
    nazwa_pliku, 0, MMIO_CREATE | MMIO_WRITE);
  if (!handle) {
    MessageBox(0, "Error creating file.", "Error Message", 0);
    return;
  }

  // Create RIFF chunk. First zero out ChunkInfo structure.
  memset(&ChunkInfo, 0, sizeof(MMCKINFO));
  ChunkInfo.fccType = mmioStringToFOURCC("WAVE", 0);
  DWORD Res = mmioCreateChunk(
    handle, &ChunkInfo, MMIO_CREATERIFF);
  CheckMMIOError(Res);

  // Create the format chunk.
  FormatChunkInfo.ckid = mmioStringToFOURCC("fmt ", 0);
  FormatChunkInfo.cksize = sizeof(WAVEFORMATEX);
  Res = mmioCreateChunk(handle, &FormatChunkInfo, 0);
  CheckMMIOError(Res);
  // Write the wave format data.
  mmioWrite(handle, (char*)&waveformatex, sizeof(waveformatex));

  // Create the data chunk.
  Res = mmioAscend(handle, &FormatChunkInfo, 0);
  CheckMMIOError(Res);
  DataChunkInfo.ckid = mmioStringToFOURCC("data", 0);
  //DataSize = WaveHeader.dwBytesRecorded;
  DataChunkInfo.cksize = DLUGOSC_BUFORA*liczba_nagranych;//DataSize;
  Res = mmioCreateChunk(handle, &DataChunkInfo, 0);
  CheckMMIOError(Res);
  // Write the data.
  for (int i=0;i<liczba_nagranych;i++)
    mmioWrite(handle, nagra[i], DLUGOSC_BUFORA);
  // Ascend out of the data chunk.
  mmioAscend(handle, &DataChunkInfo, 0);

  // Ascend out of the RIFF chunk (the main chunk). Failure to do
  // this will result in a file that is unreadable by Windows95
  // Sound Recorder.
  mmioAscend(handle, &ChunkInfo, 0);
  mmioClose(handle, 0);
}

/*-----------------------------------------------------------------------
   Sprawdzenie czy bufor zostal wypelniony (komunikat WIM_DATA)
   jesli tak, to mozna pobrac dane i wstawic go na oniec kolejki
*/
void MIC::sprawdzaj(HWAVEIN hwi, UINT uMsg, DWORD dwInstance,
                         DWORD dwParam1, DWORD dwParam2){
  MMRESULT result;
  int numer_buf2 = (numer_buf == 0 ? 1 : 0);
  //plik<<" numery buf: "<<numer_buf<<" "<<numer_buf2<<endl;
  switch(uMsg)
  {
     case WIM_CLOSE:
        //plik<<"komunikat o zamknieciu mikrofonu"<<endl;
        break;
     case WIM_DATA:
        // PRZETWARZANIE NOWYCH DANYCH
        if (nagrywanie)  // jesli nagrywanie jest wlaczone
        {
          nagra[liczba_nagranych] = new byte[DLUGOSC_BUFORA];
          for (long i=0;i<DLUGOSC_BUFORA;i++)  // przepisanie bufora probka po probce to tablicy nagra
            nagra[liczba_nagranych][i] = bufor[numer_buf][i];
          liczba_nagranych ++;
        }

        // WSTAWIENIE BUFORA NA KONIEC KOLEJKI
        if (!koniec)
        {
          result = waveInAddBuffer(hmic, &wavhdr[numer_buf], sizeof(WAVEHDR));
          numer_buf = numer_buf2;
        }
        else
          liczba_buf_wkolejce --;

        break;

  }
}



