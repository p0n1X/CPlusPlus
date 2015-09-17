//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <dbcgrids.hpp>
#include <DBCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TADOQuery *ADOQuery1;
        TADOConnection *ADOConnection1;
        TStringGrid *StringGrid1;
        TGroupBox *GroupAdd;
        TEdit *editKod;
        TLabel *Label1;
        TEdit *editIme;
        TLabel *Label2;
        TComboBox *ComboAddZvanie;
        TLabel *Label3;
        TComboBox *ComboAddStepen;
        TLabel *Label4;
        TEdit *editStaj;
        TLabel *Label5;
        TComboBox *ComboDlajnost;
        TEdit *eidtDeca;
        TLabel *Label6;
        TBitBtn *BitBtn1;
        TGroupBox *GroupEdit;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label11;
        TLabel *Label12;
        TEdit *editModKod;
        TEdit *editModIme;
        TComboBox *ComboModZvanie;
        TComboBox *ComboModStepen;
        TEdit *editModStaj;
        TComboBox *ComboModDlajnost;
        TEdit *editModDeca;
        TBitBtn *BitBtn2;
        TBitBtn *Add;
        TBitBtn *BitBtn3;
        TBitBtn *BitBtn4;
        TBitBtn *BitBtn5;
        TStringGrid *StringGrid2;
        TLabel *Label13;
        TBitBtn *BitBtn6;
        TBitBtn *BitBtn7;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall ShowOutput();
        void __fastcall AddClick(TObject *Sender);
        void __fastcall BitBtn3Click(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall StringGrid1SelectCell(TObject *Sender, int ACol,
          int ARow, bool &CanSelect);
        void __fastcall BitBtn4Click(TObject *Sender);
        void __fastcall BitBtn5Click(TObject *Sender);
        void __fastcall BitBtn6Click(TObject *Sender);
        void __fastcall BitBtn7Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        int SelectedRow;
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
