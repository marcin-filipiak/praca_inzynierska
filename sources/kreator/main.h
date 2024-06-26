//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <CheckLst.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TKreator : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TGroupBox *GroupBox1;
        TSpeedButton *dodaj_do_alfabetu;
        TSpeedButton *usun_z_alfabetu;
        TLabel *Label1;
        TEdit *edit_znak;
        TCheckListBox *alfabet;
        TButton *button1;
        TGroupBox *GroupBox2;
        TMemo *memo_tekst;
        TProgressBar *Progress;
        TPanel *Panel2;
        TGroupBox *GroupBox3;
        TLabel *Label2;
        TSpeedButton *dodaj_powiazanie;
        TSpeedButton *usun_powiazanie;
        TCheckListBox *powiazania;
        TEdit *edit_powiazanie;
        TButton *button2;
        TPanel *Panel3;
        TImage *Image1;
        TSpeedButton *SpeedButton1;
        TMemo *Memo1;
        TGroupBox *GroupBox4;
        TLabel *label_powiazan;
        TLabel *label_alfabetu;
        TLabel *label_sampli;
        TStaticText *StaticText1;
        TEdit *edit_nazwa;
        TButton *Button4;
        TPanel *Panel4;
        TGroupBox *GroupBox5;
        TListBox *lista_sampli;
        TButton *Button3;
        TMainMenu *MainMenu;
        TMenuItem *Plik1;
        TMenuItem *Openfromfile1;
        TMenuItem *Savetofile1;
        TOpenDialog *OpenDialog;
        TSaveDialog *SaveDialog;
        TMenuItem *Polski1;
        TMenuItem *English1;
        void __fastcall Openfromfile1Click(TObject *Sender);
        void __fastcall button1Click(TObject *Sender);
        void __fastcall dodaj_do_alfabetuClick(TObject *Sender);
        void __fastcall usun_z_alfabetuClick(TObject *Sender);
        void __fastcall dodaj_powiazanieClick(TObject *Sender);
        void __fastcall usun_powiazanieClick(TObject *Sender);
        void __fastcall button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall Polski1Click(TObject *Sender);
        void __fastcall English1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TKreator(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TKreator *Kreator;
//---------------------------------------------------------------------------
#endif
