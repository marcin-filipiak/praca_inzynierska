//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <MPlayer.hpp>
#include <CheckLst.hpp>
#include <Dialogs.hpp>
#include "Trayicon.h"
#include <Graphics.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TSyntezator : public TForm
{
__published:	// IDE-managed Components
        TMemo *memo_tekst;
        TTimer *Timer1;
        TPanel *Panel1;
        TGroupBox *GroupBox1;
        TTrackBar *track_predkosc;
        TOpenDialog *OpenDialog;
        TSaveDialog *SaveDialog;
        TGroupBox *GroupBox2;
        TCheckListBox *lista_sampli;
        TPanel *Panel2;
        TTrayIcon *TrayIcon;
        TTimer *test_schowka;
        TPanel *Panel3;
        TCheckBox *Check_struktury;
        TGroupBox *GroupBox3;
        TStringGrid *StringGrid1;
        TProgressBar *Progress;
        TMainMenu *Menu;
        TMenuItem *Plik1;
        TMenuItem *Widok1;
        TMenuItem *Help1;
        TMenuItem *Wczytaj1;
        TMenuItem *Karnacja1;
        TMenuItem *Professional1;
        TMenuItem *Save1;
        TImage *Img_zapisz;
        TImage *Czysc;
        TImage *Image1;
        TImage *Img_usun;
        TImage *Img_test;
        TOpenDialog *Open_czytania;
        TSaveDialog *Save_czytania;
        TMenuItem *Jezyk1;
        TMenuItem *Polski1;
        TMenuItem *English1;
        TProgressBar *Progress_struktur;
        TComboBox *combo_baza;
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall test_schowkaTimer(TObject *Sender);
        void __fastcall Img_zapiszClick(TObject *Sender);
        void __fastcall Img_usunClick(TObject *Sender);
        void __fastcall Img_testClick(TObject *Sender);
        void __fastcall track_predkoscChange(TObject *Sender);
        void __fastcall Karnacja1Click(TObject *Sender);
        void __fastcall Professional1Click(TObject *Sender);
        void __fastcall CzyscClick(TObject *Sender);
        void __fastcall Image1Click(TObject *Sender);
        void __fastcall Help1Click(TObject *Sender);
        void __fastcall Wczytaj1Click(TObject *Sender);
        void __fastcall English1Click(TObject *Sender);
        void __fastcall Polski1Click(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall combo_bazaChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TSyntezator(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSyntezator *Syntezator;
//---------------------------------------------------------------------------
#endif
