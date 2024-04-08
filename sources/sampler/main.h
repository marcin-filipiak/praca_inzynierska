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
#include <Graphics.hpp>
#include <MPlayer.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TFSampler : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TGroupBox *GroupBox1;
        TSpeedButton *SpeedMinus;
        TSpeedButton *SpeedPlus;
        TListBox *lista_bazy_sampli;
        TGroupBox *GroupBox2;
        TListBox *lista_sampli;
        TTimer *Timer;
        TPanel *Panel2;
        TGroupBox *GroupBox3;
        TSpeedButton *SpeedNagraj;
        TListBox *lista_sampli_do_nagrania;
        TImage *Image1;
        TImage *swiatlo;
        TGroupBox *GroupBox4;
        TSpeedButton *speed_ok;
        TSpeedButton *speed_no;
        TSpeedButton *speed_cofnij;
        TEdit *edit_sampl;
        TSpeedButton *speed_add_sampl;
        TGroupBox *GroupBox5;
        TEdit *edit_dlugosc;
        TStaticText *StaticText1;
        TSpeedButton *speed_odsluchaj;
        TSpeedButton *speed_del_sampl;
        TMainMenu *MainMenu1;
        TMenuItem *Polski1;
        TMenuItem *English1;
        void __fastcall SpeedMinusClick(TObject *Sender);
        void __fastcall SpeedPlusClick(TObject *Sender);
        void __fastcall lista_bazy_sampliClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall SpeedNagrajClick(TObject *Sender);
        void __fastcall TimerTimer(TObject *Sender);
        void __fastcall speed_okClick(TObject *Sender);
        void __fastcall speed_add_samplClick(TObject *Sender);
        void __fastcall speed_cofnijClick(TObject *Sender);
        void __fastcall speed_noClick(TObject *Sender);
        void __fastcall speed_odsluchajClick(TObject *Sender);
        void __fastcall speed_del_samplClick(TObject *Sender);
        void __fastcall Polski1Click(TObject *Sender);
        void __fastcall English1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFSampler(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFSampler *FSampler;
//---------------------------------------------------------------------------
#endif
