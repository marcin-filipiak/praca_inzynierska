//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TStringGrid *StringGrid1;
        TGroupBox *GroupBox1;
        TEdit *Edit_haslo;
        TEdit *Edit_przed;
        TEdit *Edit_po;
        TEdit *Edit_efektor;
        TButton *Button_Add;
        TButton *Button_delete;
        TButton *Button_edit;
        TProgressBar *Progress;
        TGroupBox *GroupBox2;
        TListBox *lista_bazy_sampli;
        TButton *Button_zapisz;
        TImage *Image1;
        TMainMenu *MainMenu1;
        TMenuItem *Jezyk1;
        TMenuItem *English1;
        void __fastcall Button_AddClick(TObject *Sender);
        void __fastcall StringGrid1Click(TObject *Sender);
        void __fastcall Button_editClick(TObject *Sender);
        void __fastcall Button_deleteClick(TObject *Sender);
        void __fastcall lista_bazy_sampliClick(TObject *Sender);
        void __fastcall Button_zapiszClick(TObject *Sender);
        void __fastcall Jezyk1Click(TObject *Sender);
        void __fastcall English1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
