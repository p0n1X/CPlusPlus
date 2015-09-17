//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ShowOutput()
{
        int br = ADOQuery1->RecordCount;
        StringGrid1->RowCount = br+1;
        AnsiString Zvanie = "";
        AnsiString Stepen = "";
        AnsiString Dlajnost = "";
        for (int i = 1; i<=br; i++)
        {
                StringGrid1->Cells [0][i] = ADOQuery1->FieldByName("Kod")->AsString;
                StringGrid1->Cells [1][i] = ADOQuery1->FieldByName("Ime")->AsString;
                switch (ADOQuery1->FieldByName("KodZvanie")->AsInteger)
                {
                        case 1:
                                Zvanie = "Асистент";break;
                        case 2:
                                Zvanie = "Старши Асистент";break;
                        case 3:
                                Zvanie = "Главен Асистент";break;
                        case 4:
                                Zvanie = "Доцент";break;
                        case 5:
                                Zvanie = "Професор";break;
                        default:
                                Zvanie = "Грешен Код за Звание";
                }
                StringGrid1->Cells [2][i] = Zvanie;
                switch (ADOQuery1->FieldByName("KodStepen")->AsInteger)
                {
                        case 0:
                                Stepen = "Без Степен";break;
                        case 1:
                                Stepen = "Доктор";break;
                        case 2:
                                Stepen = "Доктор на Науките";break;
                        default:
                                Stepen = "Грешен Код за Степен";
                }
                StringGrid1->Cells [3][i] = Stepen;
                StringGrid1->Cells [4][i] = ADOQuery1->FieldByName("Staj")->AsString;
                switch (ADOQuery1->FieldByName("KodDlajnost")->AsInteger)
                {
                        case 0:
                                Dlajnost = "Без Длъжност";break;
                        case 1:
                                Dlajnost = "Ръководител на Катедра";break;
                        case 2:
                                Dlajnost = "Научен Секретар";break;
                        case 3:
                                Dlajnost = "Заместник-Декан";break;
                        case 4:
                                Dlajnost = "Декан";break;
                        default:
                                Dlajnost = "Грешен Код за Длъжност";
                }
                StringGrid1->Cells [5][i] = Dlajnost;
                StringGrid1->Cells [6][i] = ADOQuery1->FieldByName("BroiDeca")->AsString;
                if(!ADOQuery1->Eof)
                        ADOQuery1->Next();
        }
        ADOQuery1->First();
        StringGrid1->Repaint();
}


void __fastcall TForm1::FormCreate(TObject *Sender)
{
        //StringGrid1->RowCount = ADOQuery1->RecordCount+1;
        StringGrid1->Cells [0][0] = "Код";
        StringGrid1->Cells [1][0] = "Име";
        StringGrid1->Cells [2][0] = "Звание";
        StringGrid1->Cells [3][0] = "Степен";
        StringGrid1->Cells [4][0] = "Стаж";
        StringGrid1->Cells [5][0] = "Длъжност";
        StringGrid1->Cells [6][0] = "Брой Деца";
        ShowOutput();
        //ADOQuery1->SQL->Clear();
        //ADOQuery1->SQL->Add("SELECT * FROM Prepodavateli WHERE BroiDeca = 0;");
        StringGrid2->Cells [0][0] = "Име";
        StringGrid2->Cells [1][0] = "Звание";
        StringGrid2->Cells [2][0] = "Степен";
        StringGrid2->Cells [3][0] = "Длъжност";
        StringGrid2->Cells [4][0] = "Брутна Заплата";
        StringGrid2->Cells [5][0] = "Удръжки";
        StringGrid2->Cells [6][0] = "Сума за Получаване";
}
//---------------------------------------------------------------------------



void __fastcall TForm1::BitBtn1Click(TObject *Sender)
{
        AnsiString Kod = editKod->Text;
        AnsiString Ime = editIme->Text;
        int Zvanie = ComboAddZvanie->ItemIndex + 1;
        int Stepen = ComboAddStepen->ItemIndex;
        int Dlajnost = ComboDlajnost->ItemIndex;
        AnsiString Staj = editStaj->Text;
        AnsiString Deca = eidtDeca->Text;

        AnsiString query = "INSERT INTO Prepodavateli(Kod, Ime, KodZvanie, KodStepen, Staj, KodDlajnost, BroiDeca) VALUES (\'" +
        Kod + "\', \'" + Ime + "\'," + Zvanie + "," + Stepen + ",\'" +
        Staj + "\'," + Dlajnost + ",\'" + Deca + "\');";
        ADOQuery1->Close();
        ADOQuery1->SQL->Clear();
        ADOQuery1->SQL->Add(query);
        ADOQuery1->ExecSQL();

        GroupAdd->Visible = false;
        Add->Enabled = true;
        BitBtn3->Enabled = true;
        BitBtn4->Enabled = true;
        StringGrid1->Enabled = true;
        ADOQuery1->Close();
        ADOQuery1->SQL->Clear();
        ADOQuery1->SQL->Add("SELECT * FROM Prepodavateli;");
        ADOQuery1->Open();
        ShowOutput();
}


//---------------------------------------------------------------------------


void __fastcall TForm1::AddClick(TObject *Sender)
{
        StringGrid1->Enabled = false;
        GroupAdd->Visible = true;
        Add->Enabled = false;
        BitBtn3->Enabled = false;
        BitBtn4->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BitBtn3Click(TObject *Sender)
{
        ADOQuery1->Close();
        ADOQuery1->SQL->Clear();
        AnsiString query = "SELECT * FROM Prepodavateli WHERE Kod = ";
        query += StringGrid1->Cells[0][SelectedRow];
        query += ";";
        //editModIme->Text = query;
        ADOQuery1->SQL->Add(query);
        ADOQuery1->Open();
        ADOQuery1->First();

        editModKod->Text = ADOQuery1->FieldByName("Kod")->AsString;
        editModIme->Text = ADOQuery1->FieldByName("Ime")->AsString;
        ComboModZvanie->ItemIndex = ADOQuery1->FieldByName("KodZvanie")->AsInteger-1;
        ComboModStepen->ItemIndex = ADOQuery1->FieldByName("KodStepen")->AsInteger;
        editModStaj->Text = ADOQuery1->FieldByName("Staj")->AsString;
        editModDeca->Text = ADOQuery1->FieldByName("BroiDeca")->AsString;
        ComboModDlajnost->ItemIndex = ADOQuery1->FieldByName("KodDlajnost")->AsInteger;

        GroupEdit->Visible = true;
        BitBtn3->Enabled = false;
        BitBtn4->Enabled = false;
        Add->Enabled = false;
        StringGrid1->Enabled = false;
        ADOQuery1->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BitBtn2Click(TObject *Sender)
{
        AnsiString Kod = editModKod->Text;
        AnsiString Ime = editModIme->Text;
        int Zvanie = ComboModZvanie->ItemIndex + 1;
        int Stepen = ComboModStepen->ItemIndex;
        int Dlajnost = ComboModDlajnost->ItemIndex;
        AnsiString Staj = editModStaj->Text;
        AnsiString Deca = editModDeca->Text;

        AnsiString query = "UPDATE Prepodavateli SET Kod = " + Kod + ", Ime = \'" + Ime + "\', KodZvanie = " + Zvanie + ", KodStepen = " + Stepen + ", Staj = \'" + Staj + "\', KodDlajnost = " +Dlajnost+ ", BroiDeca = \'" + Deca + "\' WHERE Kod = " + StringGrid1->Cells[0][SelectedRow] + ";";
        ADOQuery1->Close();
        ADOQuery1->SQL->Clear();
        ADOQuery1->SQL->Add(query);
        ADOQuery1->ExecSQL();
        
        GroupEdit->Visible = false;
        BitBtn3->Enabled = true;
        BitBtn4->Enabled = true;
        Add->Enabled = true;
        StringGrid1->Enabled = true;
        ADOQuery1->Close();
        ADOQuery1->SQL->Clear();
        ADOQuery1->SQL->Add("SELECT * FROM Prepodavateli;");
        ADOQuery1->Open();
        ShowOutput();
}
//---------------------------------------------------------------------------




void __fastcall TForm1::StringGrid1SelectCell(TObject *Sender, int ACol,
      int ARow, bool &CanSelect)
{
        SelectedRow = ARow;        
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BitBtn4Click(TObject *Sender)
{
        ADOQuery1->Close();
        ADOQuery1->SQL->Clear();
        AnsiString query = "DELETE FROM Prepodavateli WHERE Kod = ";
        query += StringGrid1->Cells[0][SelectedRow];
        query += ";";
        Form1->ADOQuery1->SQL->Add(query);
        ADOQuery1->ExecSQL();

        ADOQuery1->Close();
        ADOQuery1->SQL->Clear();
        ADOQuery1->SQL->Add("SELECT * FROM Prepodavateli;");
        ADOQuery1->Open();
        ShowOutput();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BitBtn5Click(TObject *Sender)
{
        ADOQuery1->Close();
        ADOQuery1->SQL->Clear();
        ADOQuery1->SQL->Add("SELECT * FROM Prepodavateli ORDER BY Ime ASC;");
        ADOQuery1->Open();
        ShowOutput();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::BitBtn6Click(TObject *Sender)
{
        ADOQuery1->Close();
        ADOQuery1->SQL->Clear();
        AnsiString query = "SELECT * FROM Prepodavateli WHERE Kod = ";
        query += StringGrid1->Cells[0][SelectedRow];
        query += ";";
        //editModIme->Text = query;
        ADOQuery1->SQL->Add(query);
        ADOQuery1->Open();
        ADOQuery1->First();

        int KodZvanie = ADOQuery1->FieldByName("KodZvanie")->AsInteger;
        int KodStepen = ADOQuery1->FieldByName("KodStepen")->AsInteger;
        int Staj = ADOQuery1->FieldByName("Staj")->AsInteger;
        int Deca = ADOQuery1->FieldByName("BroiDeca")->AsInteger;
        int KodDlajnost = ADOQuery1->FieldByName("KodDlajnost")->AsInteger;
        int Nadbavka = 0;
        int Shtatna = 0;
        int udrajki = 5;
        int brutna = 0;
        int zapoluchavane = 0;

        switch (KodZvanie)
        {
                case 1:
                        Shtatna = 400;break;
                case 2:
                        Shtatna = 480;break;
                case 3:
                        Shtatna = 590;break;
                case 4:
                        Shtatna = 700;break;
                case 5:
                        Shtatna = 900;break;
                default: Shtatna = 0;
        }

        Nadbavka += (Staj * Shtatna)/100; //nadbavka za klas
        if (KodStepen == 1) Nadbavka += 200;     //nadbavka za stepen
        if (KodStepen == 2) Nadbavka += 500;

        switch (KodDlajnost)               //nadbavka za dlajnost
        {
                case 1:
                        Nadbavka += 150;break;
                case 2:
                        Nadbavka += 200;break;
                case 3:
                        Nadbavka += 320;break;
                case 4:
                        Nadbavka += 450;break;
                default: Nadbavka += 0;
        }

        Nadbavka += Deca*50; //nadbavka za deca
        brutna = Shtatna + Nadbavka;
        if (brutna > 360)
                udrajki = 7;
        if (brutna > 420)
                udrajki = 10;
        if (brutna > 520)
                udrajki = 14;
        if (brutna > 660)
                udrajki = 19;
        if (brutna > 900)
                udrajki = 25;
        zapoluchavane = (brutna*(100-udrajki))/100;

        StringGrid2->Cells [0][1] = StringGrid1->Cells [1][SelectedRow];
        StringGrid2->Cells [1][1] = StringGrid1->Cells [2][SelectedRow];
        StringGrid2->Cells [2][1] = StringGrid1->Cells [3][SelectedRow];
        StringGrid2->Cells [3][1] = StringGrid1->Cells [5][SelectedRow];
        StringGrid2->Cells [4][1] = IntToStr(brutna);
        StringGrid2->Cells [5][1] = IntToStr((udrajki*brutna)/100);
        StringGrid2->Cells [6][1] = IntToStr(zapoluchavane);
        ADOQuery1->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::BitBtn7Click(TObject *Sender)
{
        Form2->Show();
}
//---------------------------------------------------------------------------




