//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm2::FormCreate(TObject *Sender)
{
        StringGrid2->Cells [0][0] = "Име";
        StringGrid2->Cells [1][0] = "Звание";
        StringGrid2->Cells [2][0] = "Степен";
        StringGrid2->Cells [3][0] = "Длъжност";
        StringGrid2->Cells [4][0] = "Брутна Заплата";
        StringGrid2->Cells [5][0] = "Удръжки";
        StringGrid2->Cells [6][0] = "Сума за Получаване";
}
//---------------------------------------------------------------------------
void __fastcall TForm2::BitBtn1Click(TObject *Sender)
{
try
{
        AnsiString query = "";
        AnsiString criteria = Edit1->Text;
        AnsiString Zvanie = "";
        AnsiString Stepen = "";
        AnsiString Dlajnost = "";
        int br = 1;
        StringGrid2->RowCount = br;
        switch(ComboBox1->ItemIndex)
        {
                case 0:
                        query = "SELECT * FROM Prepodavateli WHERE KodZvanie = 1";
                        Form1->ADOQuery1->Close();
                        Form1->ADOQuery1->SQL->Clear();
                        Form1->ADOQuery1->SQL->Add(query);
                        Form1->ADOQuery1->Open();
                        if (Form1->ADOQuery1->RecordCount <= 0)
                                break;
                        Form1->ADOQuery1->First();
                        for (int i=1; i<=Form1->ADOQuery1->RecordCount; i++)
                        {
                                int KodZvanie = Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger;
                                int KodStepen = Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger;
                                int Staj = Form1->ADOQuery1->FieldByName("Staj")->AsInteger;
                                int Deca = Form1->ADOQuery1->FieldByName("BroiDeca")->AsInteger;
                                int KodDlajnost = Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger;
                                int Nadbavka = 0;
                                int Shtatna = 0;
                                int brutna = 0;
                                int udrajki = 5;
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
                                if (brutna > StrToInt(criteria))
                                {
                                        br++;
                                        StringGrid2->Cells [0][br-1] = Form1->ADOQuery1->FieldByName("Ime")->AsString;
                                        switch (Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger)
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

                                        StringGrid2->Cells [1][br-1] = Zvanie;
                                        StringGrid2->Cells [2][br-1] = Stepen;
                                        StringGrid2->Cells [3][br-1] = Dlajnost;
                                        StringGrid2->Cells [4][br-1] = IntToStr(brutna);
                                        StringGrid2->Cells [5][br-1] = IntToStr((udrajki*brutna)/100);
                                        StringGrid2->Cells [6][br-1] = IntToStr(zapoluchavane);
                                }
                                if (!Form1->ADOQuery1->Eof)
                                        Form1->ADOQuery1->Next();
                                StringGrid2->RowCount= br;
                        }
                        break;
                case 1:
                        query = "SELECT * FROM Prepodavateli WHERE KodZvanie = 3 AND Staj > " + criteria;
                        Form1->ADOQuery1->Close();
                        Form1->ADOQuery1->SQL->Clear();
                        Form1->ADOQuery1->SQL->Add(query);
                        Form1->ADOQuery1->Open();
                        if (Form1->ADOQuery1->RecordCount <= 0)
                                break;
                        Form1->ADOQuery1->First();
                        for (int i=1; i<=Form1->ADOQuery1->RecordCount; i++)
                        {
                                int KodZvanie = Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger;
                                int KodStepen = Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger;
                                int Staj = Form1->ADOQuery1->FieldByName("Staj")->AsInteger;
                                int Deca = Form1->ADOQuery1->FieldByName("BroiDeca")->AsInteger;
                                int KodDlajnost = Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger;
                                int Nadbavka = 0;
                                int Shtatna = 0;
                                int brutna = 0;
                                int udrajki = 5;
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
//                                if (brutna > StrToInt(criteria))
//                                {
                                        br++;
                                        StringGrid2->Cells [0][br-1] = Form1->ADOQuery1->FieldByName("Ime")->AsString;
                                        switch (Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger)
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

                                        StringGrid2->Cells [1][br-1] = Zvanie;
                                        StringGrid2->Cells [2][br-1] = Stepen;
                                        StringGrid2->Cells [3][br-1] = Dlajnost;
                                        StringGrid2->Cells [4][br-1] = IntToStr(brutna);
                                        StringGrid2->Cells [5][br-1] = IntToStr((udrajki*brutna)/100);
                                        StringGrid2->Cells [6][br-1] = IntToStr(zapoluchavane);
//                                }
                                if (!Form1->ADOQuery1->Eof)
                                        Form1->ADOQuery1->Next();
                                StringGrid2->RowCount= br;
                        }
                        break;
                case 2:
                        query = "SELECT * FROM Prepodavateli WHERE KodZvanie = 4 AND KodStepen <> 0";
                        Form1->ADOQuery1->Close();
                        Form1->ADOQuery1->SQL->Clear();
                        Form1->ADOQuery1->SQL->Add(query);
                        Form1->ADOQuery1->Open();
                        if (Form1->ADOQuery1->RecordCount <= 0)
                                break;
                        Form1->ADOQuery1->First();
                        for (int i=1; i<=Form1->ADOQuery1->RecordCount; i++)
                        {
                                int KodZvanie = Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger;
                                int KodStepen = Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger;
                                int Staj = Form1->ADOQuery1->FieldByName("Staj")->AsInteger;
                                int Deca = Form1->ADOQuery1->FieldByName("BroiDeca")->AsInteger;
                                int KodDlajnost = Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger;
                                int Nadbavka = 0;
                                int Shtatna = 0;
                                int brutna = 0;
                                int udrajki = 5;
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
                                if (brutna < StrToInt(criteria))
                                {
                                        br++;
                                        StringGrid2->Cells [0][br-1] = Form1->ADOQuery1->FieldByName("Ime")->AsString;
                                        switch (Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger)
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

                                        StringGrid2->Cells [1][br-1] = Zvanie;
                                        StringGrid2->Cells [2][br-1] = Stepen;
                                        StringGrid2->Cells [3][br-1] = Dlajnost;
                                        StringGrid2->Cells [4][br-1] = IntToStr(brutna);
                                        StringGrid2->Cells [5][br-1] = IntToStr((udrajki*brutna)/100);
                                        StringGrid2->Cells [6][br-1] = IntToStr(zapoluchavane);
                                }
                                if (!Form1->ADOQuery1->Eof)
                                        Form1->ADOQuery1->Next();
                                StringGrid2->RowCount= br;
                        }
                        break;
                case 3:
                        query = "SELECT * FROM Prepodavateli WHERE KodZvanie = 2 AND BroiDeca > " + criteria;
                        Form1->ADOQuery1->Close();
                        Form1->ADOQuery1->SQL->Clear();
                        Form1->ADOQuery1->SQL->Add(query);
                        Form1->ADOQuery1->Open();
                        if (Form1->ADOQuery1->RecordCount <= 0)
                                break;
                        Form1->ADOQuery1->First();
                        for (int i=1; i<=Form1->ADOQuery1->RecordCount; i++)
                        {
                                int KodZvanie = Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger;
                                int KodStepen = Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger;
                                int Staj = Form1->ADOQuery1->FieldByName("Staj")->AsInteger;
                                int Deca = Form1->ADOQuery1->FieldByName("BroiDeca")->AsInteger;
                                int KodDlajnost = Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger;
                                int Nadbavka = 0;
                                int Shtatna = 0;
                                int brutna = 0;
                                int udrajki = 5;
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
//                                if (brutna < StrToInt(criteria))
//                                {
                                        br++;
                                        StringGrid2->Cells [0][br-1] = Form1->ADOQuery1->FieldByName("Ime")->AsString;
                                        switch (Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger)
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

                                        StringGrid2->Cells [1][br-1] = Zvanie;
                                        StringGrid2->Cells [2][br-1] = Stepen;
                                        StringGrid2->Cells [3][br-1] = Dlajnost;
                                        StringGrid2->Cells [4][br-1] = IntToStr(brutna);
                                        StringGrid2->Cells [5][br-1] = IntToStr((udrajki*brutna)/100);
                                        StringGrid2->Cells [6][br-1] = IntToStr(zapoluchavane);
//                                }
                                if (!Form1->ADOQuery1->Eof)
                                        Form1->ADOQuery1->Next();
                                StringGrid2->RowCount= br;
                        }
                        break;
                case 4:
                        query = "SELECT * FROM Prepodavateli WHERE KodZvanie = 5 AND KodDlajnost = 1";
                        Form1->ADOQuery1->Close();
                        Form1->ADOQuery1->SQL->Clear();
                        Form1->ADOQuery1->SQL->Add(query);
                        Form1->ADOQuery1->Open();
                        if (Form1->ADOQuery1->RecordCount <= 0)
                                break;
                        Form1->ADOQuery1->First();
                        for (int i=1; i<=Form1->ADOQuery1->RecordCount; i++)
                        {
                                int KodZvanie = Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger;
                                int KodStepen = Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger;
                                int Staj = Form1->ADOQuery1->FieldByName("Staj")->AsInteger;
                                int Deca = Form1->ADOQuery1->FieldByName("BroiDeca")->AsInteger;
                                int KodDlajnost = Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger;
                                int Nadbavka = 0;
                                int Shtatna = 0;
                                int brutna = 0;
                                int udrajki = 5;
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
                                if (brutna > StrToInt(criteria))
                                {
                                        br++;
                                        StringGrid2->Cells [0][br-1] = Form1->ADOQuery1->FieldByName("Ime")->AsString;
                                        switch (Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger)
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

                                        StringGrid2->Cells [1][br-1] = Zvanie;
                                        StringGrid2->Cells [2][br-1] = Stepen;
                                        StringGrid2->Cells [3][br-1] = Dlajnost;
                                        StringGrid2->Cells [4][br-1] = IntToStr(brutna);
                                        StringGrid2->Cells [5][br-1] = IntToStr((udrajki*brutna)/100);
                                        StringGrid2->Cells [6][br-1] = IntToStr(zapoluchavane);
                                }
                                if (!Form1->ADOQuery1->Eof)
                                        Form1->ADOQuery1->Next();
                                StringGrid2->RowCount= br;
                        }
                        break;
                case 5:
                        query = "SELECT * FROM Prepodavateli WHERE KodZvanie < 4 AND Staj < " + criteria;
                        Form1->ADOQuery1->Close();
                        Form1->ADOQuery1->SQL->Clear();
                        Form1->ADOQuery1->SQL->Add(query);
                        Form1->ADOQuery1->Open();
                        if (Form1->ADOQuery1->RecordCount <= 0)
                                break;
                        Form1->ADOQuery1->First();
                        for (int i=1; i<=Form1->ADOQuery1->RecordCount; i++)
                        {
                                int KodZvanie = Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger;
                                int KodStepen = Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger;
                                int Staj = Form1->ADOQuery1->FieldByName("Staj")->AsInteger;
                                int Deca = Form1->ADOQuery1->FieldByName("BroiDeca")->AsInteger;
                                int KodDlajnost = Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger;
                                int Nadbavka = 0;
                                int Shtatna = 0;
                                int brutna = 0;
                                int udrajki = 5;
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
//                                if (brutna > StrToInt(criteria))
//                                {
                                        br++;
                                        StringGrid2->Cells [0][br-1] = Form1->ADOQuery1->FieldByName("Ime")->AsString;
                                        switch (Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger)
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

                                        StringGrid2->Cells [1][br-1] = Zvanie;
                                        StringGrid2->Cells [2][br-1] = Stepen;
                                        StringGrid2->Cells [3][br-1] = Dlajnost;
                                        StringGrid2->Cells [4][br-1] = IntToStr(brutna);
                                        StringGrid2->Cells [5][br-1] = IntToStr((udrajki*brutna)/100);
                                        StringGrid2->Cells [6][br-1] = IntToStr(zapoluchavane);
//                                }
                                if (!Form1->ADOQuery1->Eof)
                                        Form1->ADOQuery1->Next();
                                StringGrid2->RowCount= br;
                        }                        break;
                case 6:
                        query = "SELECT * FROM Prepodavateli WHERE KodStepen = 2 AND KodZvanie > 3 AND Staj > " + criteria;
                        Form1->ADOQuery1->Close();
                        Form1->ADOQuery1->SQL->Clear();
                        Form1->ADOQuery1->SQL->Add(query);
                        Form1->ADOQuery1->Open();
                        if (Form1->ADOQuery1->RecordCount <= 0)
                                break;
                        Form1->ADOQuery1->First();
                        for (int i=1; i<=Form1->ADOQuery1->RecordCount; i++)
                        {
                                int KodZvanie = Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger;
                                int KodStepen = Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger;
                                int Staj = Form1->ADOQuery1->FieldByName("Staj")->AsInteger;
                                int Deca = Form1->ADOQuery1->FieldByName("BroiDeca")->AsInteger;
                                int KodDlajnost = Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger;
                                int Nadbavka = 0;
                                int Shtatna = 0;
                                int brutna = 0;
                                int udrajki = 5;
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
//                                if (brutna > StrToInt(criteria))
//                                {
                                        br++;
                                        StringGrid2->Cells [0][br-1] = Form1->ADOQuery1->FieldByName("Ime")->AsString;
                                        switch (Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger)
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

                                        StringGrid2->Cells [1][br-1] = Zvanie;
                                        StringGrid2->Cells [2][br-1] = Stepen;
                                        StringGrid2->Cells [3][br-1] = Dlajnost;
                                        StringGrid2->Cells [4][br-1] = IntToStr(brutna);
                                        StringGrid2->Cells [5][br-1] = IntToStr((udrajki*brutna)/100);
                                        StringGrid2->Cells [6][br-1] = IntToStr(zapoluchavane);
//                                }
                                if (!Form1->ADOQuery1->Eof)
                                        Form1->ADOQuery1->Next();
                                StringGrid2->RowCount= br;
                        }
                        break;
                case 7:
                        query = "SELECT * FROM Prepodavateli WHERE KodStepen = 1 AND KodZvanie < 4 AND Staj > " + criteria;
                        Form1->ADOQuery1->Close();
                        Form1->ADOQuery1->SQL->Clear();
                        Form1->ADOQuery1->SQL->Add(query);
                        Form1->ADOQuery1->Open();
                        if (Form1->ADOQuery1->RecordCount <= 0)
                                break;
                        Form1->ADOQuery1->First();
                        for (int i=1; i<=Form1->ADOQuery1->RecordCount; i++)
                        {
                                int KodZvanie = Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger;
                                int KodStepen = Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger;
                                int Staj = Form1->ADOQuery1->FieldByName("Staj")->AsInteger;
                                int Deca = Form1->ADOQuery1->FieldByName("BroiDeca")->AsInteger;
                                int KodDlajnost = Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger;
                                int Nadbavka = 0;
                                int Shtatna = 0;
                                int brutna = 0;
                                int udrajki = 5;
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
//                                if (brutna > StrToInt(criteria))
//                                {
                                        br++;
                                        StringGrid2->Cells [0][br-1] = Form1->ADOQuery1->FieldByName("Ime")->AsString;
                                        switch (Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger)
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

                                        StringGrid2->Cells [1][br-1] = Zvanie;
                                        StringGrid2->Cells [2][br-1] = Stepen;
                                        StringGrid2->Cells [3][br-1] = Dlajnost;
                                        StringGrid2->Cells [4][br-1] = IntToStr(brutna);
                                        StringGrid2->Cells [5][br-1] = IntToStr((udrajki*brutna)/100);
                                        StringGrid2->Cells [6][br-1] = IntToStr(zapoluchavane);
//                                }
                                if (!Form1->ADOQuery1->Eof)
                                        Form1->ADOQuery1->Next();
                                StringGrid2->RowCount= br;
                        }
                        break;
                case 8:
                        query = "SELECT * FROM Prepodavateli WHERE KodStepen = 1 AND KodZvanie = 5 AND Staj < " + criteria;
                        Form1->ADOQuery1->Close();
                        Form1->ADOQuery1->SQL->Clear();
                        Form1->ADOQuery1->SQL->Add(query);
                        Form1->ADOQuery1->Open();
                        if (Form1->ADOQuery1->RecordCount <= 0)
                                break;
                        Form1->ADOQuery1->First();
                        for (int i=1; i<=Form1->ADOQuery1->RecordCount; i++)
                        {
                                int KodZvanie = Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger;
                                int KodStepen = Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger;
                                int Staj = Form1->ADOQuery1->FieldByName("Staj")->AsInteger;
                                int Deca = Form1->ADOQuery1->FieldByName("BroiDeca")->AsInteger;
                                int KodDlajnost = Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger;
                                int Nadbavka = 0;
                                int Shtatna = 0;
                                int brutna = 0;
                                int udrajki = 5;
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
//                                if (brutna > StrToInt(criteria))
//                                {
                                        br++;
                                        StringGrid2->Cells [0][br-1] = Form1->ADOQuery1->FieldByName("Ime")->AsString;
                                        switch (Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger)
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

                                        StringGrid2->Cells [1][br-1] = Zvanie;
                                        StringGrid2->Cells [2][br-1] = Stepen;
                                        StringGrid2->Cells [3][br-1] = Dlajnost;
                                        StringGrid2->Cells [4][br-1] = IntToStr(brutna);
                                        StringGrid2->Cells [5][br-1] = IntToStr((udrajki*brutna)/100);
                                        StringGrid2->Cells [6][br-1] = IntToStr(zapoluchavane);
//                                }
                                if (!Form1->ADOQuery1->Eof)
                                        Form1->ADOQuery1->Next();
                                StringGrid2->RowCount= br;
                        }
                        break;
                case 9:
                        query = "SELECT * FROM Prepodavateli WHERE KodZvanie = 5 AND KodDlajnost = 0 AND Staj > " + criteria;
                        Form1->ADOQuery1->Close();
                        Form1->ADOQuery1->SQL->Clear();
                        Form1->ADOQuery1->SQL->Add(query);
                        Form1->ADOQuery1->Open();
                        if (Form1->ADOQuery1->RecordCount <= 0)
                                break;
                        Form1->ADOQuery1->First();
                        for (int i=1; i<=Form1->ADOQuery1->RecordCount; i++)
                        {
                                int KodZvanie = Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger;
                                int KodStepen = Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger;
                                int Staj = Form1->ADOQuery1->FieldByName("Staj")->AsInteger;
                                int Deca = Form1->ADOQuery1->FieldByName("BroiDeca")->AsInteger;
                                int KodDlajnost = Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger;
                                int Nadbavka = 0;
                                int Shtatna = 0;
                                int brutna = 0;
                                int udrajki = 5;
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
//                                if (brutna > StrToInt(criteria))
//                                {
                                        br++;
                                        StringGrid2->Cells [0][br-1] = Form1->ADOQuery1->FieldByName("Ime")->AsString;
                                        switch (Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger)
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

                                        StringGrid2->Cells [1][br-1] = Zvanie;
                                        StringGrid2->Cells [2][br-1] = Stepen;
                                        StringGrid2->Cells [3][br-1] = Dlajnost;
                                        StringGrid2->Cells [4][br-1] = IntToStr(brutna);
                                        StringGrid2->Cells [5][br-1] = IntToStr((udrajki*brutna)/100);
                                        StringGrid2->Cells [6][br-1] = IntToStr(zapoluchavane);
//                                }
                                if (!Form1->ADOQuery1->Eof)
                                        Form1->ADOQuery1->Next();
                                StringGrid2->RowCount= br;
                        }                        break;
                case 10:
                        query = "SELECT * FROM Prepodavateli WHERE KodZvanie = 2";
                        Form1->ADOQuery1->Close();
                        Form1->ADOQuery1->SQL->Clear();
                        Form1->ADOQuery1->SQL->Add(query);
                        Form1->ADOQuery1->Open();
                        if (Form1->ADOQuery1->RecordCount <= 0)
                                break;
                        Form1->ADOQuery1->First();
                        for (int i=1; i<=Form1->ADOQuery1->RecordCount; i++)
                        {
                                int KodZvanie = Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger;
                                int KodStepen = Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger;
                                int Staj = Form1->ADOQuery1->FieldByName("Staj")->AsInteger;
                                int Deca = Form1->ADOQuery1->FieldByName("BroiDeca")->AsInteger;
                                int KodDlajnost = Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger;
                                int Nadbavka = 0;
                                int Shtatna = 0;
                                int brutna = 0;
                                int udrajki = 5;
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
                                if (brutna > StrToInt(criteria))
                                {
                                        br++;
                                        StringGrid2->Cells [0][br-1] = Form1->ADOQuery1->FieldByName("Ime")->AsString;
                                        switch (Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger)
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

                                        StringGrid2->Cells [1][br-1] = Zvanie;
                                        StringGrid2->Cells [2][br-1] = Stepen;
                                        StringGrid2->Cells [3][br-1] = Dlajnost;
                                        StringGrid2->Cells [4][br-1] = IntToStr(brutna);
                                        StringGrid2->Cells [5][br-1] = IntToStr((udrajki*brutna)/100);
                                        StringGrid2->Cells [6][br-1] = IntToStr(zapoluchavane);
                                }
                                if (!Form1->ADOQuery1->Eof)
                                        Form1->ADOQuery1->Next();
                                StringGrid2->RowCount= br;
                        }                        break;
                case 11:
                        query = "SELECT * FROM Prepodavateli WHERE AND KodZvanie = 1 AND Staj > " + criteria;
                        Form1->ADOQuery1->Close();
                        Form1->ADOQuery1->SQL->Clear();
                        Form1->ADOQuery1->SQL->Add(query);
                        Form1->ADOQuery1->Open();
                        if (Form1->ADOQuery1->RecordCount <= 0)
                                break;
                        Form1->ADOQuery1->First();
                        for (int i=1; i<=Form1->ADOQuery1->RecordCount; i++)
                        {
                                int KodZvanie = Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger;
                                int KodStepen = Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger;
                                int Staj = Form1->ADOQuery1->FieldByName("Staj")->AsInteger;
                                int Deca = Form1->ADOQuery1->FieldByName("BroiDeca")->AsInteger;
                                int KodDlajnost = Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger;
                                int Nadbavka = 0;
                                int Shtatna = 0;
                                int brutna = 0;
                                int udrajki = 5;
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
//                                if (brutna > StrToInt(criteria))
//                                {
                                        br++;
                                        StringGrid2->Cells [0][br-1] = Form1->ADOQuery1->FieldByName("Ime")->AsString;
                                        switch (Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger)
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

                                        StringGrid2->Cells [1][br-1] = Zvanie;
                                        StringGrid2->Cells [2][br-1] = Stepen;
                                        StringGrid2->Cells [3][br-1] = Dlajnost;
                                        StringGrid2->Cells [4][br-1] = IntToStr(brutna);
                                        StringGrid2->Cells [5][br-1] = IntToStr((udrajki*brutna)/100);
                                        StringGrid2->Cells [6][br-1] = IntToStr(zapoluchavane);
//                                }
                                if (!Form1->ADOQuery1->Eof)
                                        Form1->ADOQuery1->Next();
                                StringGrid2->RowCount= br;
                        }                        break;
                case 12:
                        query = "SELECT * FROM Prepodavateli WHERE KodStepen > 0 AND KodZvanie = 5";
                        Form1->ADOQuery1->Close();
                        Form1->ADOQuery1->SQL->Clear();
                        Form1->ADOQuery1->SQL->Add(query);
                        Form1->ADOQuery1->Open();
                        if (Form1->ADOQuery1->RecordCount <= 0)
                                break;
                        Form1->ADOQuery1->First();
                        for (int i=1; i<=Form1->ADOQuery1->RecordCount; i++)
                        {
                                int KodZvanie = Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger;
                                int KodStepen = Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger;
                                int Staj = Form1->ADOQuery1->FieldByName("Staj")->AsInteger;
                                int Deca = Form1->ADOQuery1->FieldByName("BroiDeca")->AsInteger;
                                int KodDlajnost = Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger;
                                int Nadbavka = 0;
                                int Shtatna = 0;
                                int brutna = 0;
                                int udrajki = 5;
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
                                if (brutna < StrToInt(criteria))
                                {
                                        br++;
                                        StringGrid2->Cells [0][br-1] = Form1->ADOQuery1->FieldByName("Ime")->AsString;
                                        switch (Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger)
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

                                        StringGrid2->Cells [1][br-1] = Zvanie;
                                        StringGrid2->Cells [2][br-1] = Stepen;
                                        StringGrid2->Cells [3][br-1] = Dlajnost;
                                        StringGrid2->Cells [4][br-1] = IntToStr(brutna);
                                        StringGrid2->Cells [5][br-1] = IntToStr((udrajki*brutna)/100);
                                        StringGrid2->Cells [6][br-1] = IntToStr(zapoluchavane);
                                }
                                if (!Form1->ADOQuery1->Eof)
                                        Form1->ADOQuery1->Next();
                                StringGrid2->RowCount= br;
                        }                        break;
                case 13:
                        query = "SELECT * FROM Prepodavateli WHERE KodZvanie = 3 AND BroiDeca > " + criteria;
                        Form1->ADOQuery1->Close();
                        Form1->ADOQuery1->SQL->Clear();
                        Form1->ADOQuery1->SQL->Add(query);
                        Form1->ADOQuery1->Open();
                        if (Form1->ADOQuery1->RecordCount <= 0)
                                break;
                        Form1->ADOQuery1->First();
                        for (int i=1; i<=Form1->ADOQuery1->RecordCount; i++)
                        {
                                int KodZvanie = Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger;
                                int KodStepen = Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger;
                                int Staj = Form1->ADOQuery1->FieldByName("Staj")->AsInteger;
                                int Deca = Form1->ADOQuery1->FieldByName("BroiDeca")->AsInteger;
                                int KodDlajnost = Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger;
                                int Nadbavka = 0;
                                int Shtatna = 0;
                                int brutna = 0;
                                int udrajki = 5;
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
//                                if (brutna > StrToInt(criteria))
//                                {
                                        br++;
                                        StringGrid2->Cells [0][br-1] = Form1->ADOQuery1->FieldByName("Ime")->AsString;
                                        switch (Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger)
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

                                        StringGrid2->Cells [1][br-1] = Zvanie;
                                        StringGrid2->Cells [2][br-1] = Stepen;
                                        StringGrid2->Cells [3][br-1] = Dlajnost;
                                        StringGrid2->Cells [4][br-1] = IntToStr(brutna);
                                        StringGrid2->Cells [5][br-1] = IntToStr((udrajki*brutna)/100);
                                        StringGrid2->Cells [6][br-1] = IntToStr(zapoluchavane);
//                                }
                                if (!Form1->ADOQuery1->Eof)
                                        Form1->ADOQuery1->Next();
                                StringGrid2->RowCount= br;
                        }                        break;
                case 14:
                        query = "SELECT * FROM Prepodavateli WHERE KodZvanie = 4 AND KodDlajnost = 1";
                        Form1->ADOQuery1->Close();
                        Form1->ADOQuery1->SQL->Clear();
                        Form1->ADOQuery1->SQL->Add(query);
                        Form1->ADOQuery1->Open();
                        if (Form1->ADOQuery1->RecordCount <= 0)
                                break;
                        Form1->ADOQuery1->First();
                        for (int i=1; i<=Form1->ADOQuery1->RecordCount; i++)
                        {
                                int KodZvanie = Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger;
                                int KodStepen = Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger;
                                int Staj = Form1->ADOQuery1->FieldByName("Staj")->AsInteger;
                                int Deca = Form1->ADOQuery1->FieldByName("BroiDeca")->AsInteger;
                                int KodDlajnost = Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger;
                                int Nadbavka = 0;
                                int Shtatna = 0;
                                int brutna = 0;
                                int udrajki = 5;
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
                                if (brutna > StrToInt(criteria))
                                {
                                        br++;
                                        StringGrid2->Cells [0][br-1] = Form1->ADOQuery1->FieldByName("Ime")->AsString;
                                        switch (Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger)
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

                                        StringGrid2->Cells [1][br-1] = Zvanie;
                                        StringGrid2->Cells [2][br-1] = Stepen;
                                        StringGrid2->Cells [3][br-1] = Dlajnost;
                                        StringGrid2->Cells [4][br-1] = IntToStr(brutna);
                                        StringGrid2->Cells [5][br-1] = IntToStr((udrajki*brutna)/100);
                                        StringGrid2->Cells [6][br-1] = IntToStr(zapoluchavane);
                                }
                                if (!Form1->ADOQuery1->Eof)
                                        Form1->ADOQuery1->Next();
                                StringGrid2->RowCount= br;
                        }                        break;
                case 15:
                        query = "SELECT * FROM Prepodavateli WHERE KodZvanie > 3 AND Staj < " + criteria;
                        Form1->ADOQuery1->Close();
                        Form1->ADOQuery1->SQL->Clear();
                        Form1->ADOQuery1->SQL->Add(query);
                        Form1->ADOQuery1->Open();
                        if (Form1->ADOQuery1->RecordCount <= 0)
                                break;
                        Form1->ADOQuery1->First();
                        for (int i=1; i<=Form1->ADOQuery1->RecordCount; i++)
                        {
                                int KodZvanie = Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger;
                                int KodStepen = Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger;
                                int Staj = Form1->ADOQuery1->FieldByName("Staj")->AsInteger;
                                int Deca = Form1->ADOQuery1->FieldByName("BroiDeca")->AsInteger;
                                int KodDlajnost = Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger;
                                int Nadbavka = 0;
                                int Shtatna = 0;
                                int brutna = 0;
                                int udrajki = 5;
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
//                                if (brutna > StrToInt(criteria))
//                                {
                                        br++;
                                        StringGrid2->Cells [0][br-1] = Form1->ADOQuery1->FieldByName("Ime")->AsString;
                                        switch (Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger)
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

                                        StringGrid2->Cells [1][br-1] = Zvanie;
                                        StringGrid2->Cells [2][br-1] = Stepen;
                                        StringGrid2->Cells [3][br-1] = Dlajnost;
                                        StringGrid2->Cells [4][br-1] = IntToStr(brutna);
                                        StringGrid2->Cells [5][br-1] = IntToStr((udrajki*brutna)/100);
                                        StringGrid2->Cells [6][br-1] = IntToStr(zapoluchavane);
//                                }
                                if (!Form1->ADOQuery1->Eof)
                                        Form1->ADOQuery1->Next();
                                StringGrid2->RowCount= br;
                        }                        break;
                case 16:
                        query = "SELECT * FROM Prepodavateli WHERE KodStepen = 1 AND KodZvanie < 4 AND Staj > " + criteria;
                        Form1->ADOQuery1->Close();
                        Form1->ADOQuery1->SQL->Clear();
                        Form1->ADOQuery1->SQL->Add(query);
                        Form1->ADOQuery1->Open();
                        if (Form1->ADOQuery1->RecordCount <= 0)
                                break;
                        Form1->ADOQuery1->First();
                        for (int i=1; i<=Form1->ADOQuery1->RecordCount; i++)
                        {
                                int KodZvanie = Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger;
                                int KodStepen = Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger;
                                int Staj = Form1->ADOQuery1->FieldByName("Staj")->AsInteger;
                                int Deca = Form1->ADOQuery1->FieldByName("BroiDeca")->AsInteger;
                                int KodDlajnost = Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger;
                                int Nadbavka = 0;
                                int Shtatna = 0;
                                int brutna = 0;
                                int udrajki = 5;
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
//                                if (brutna > StrToInt(criteria))
//                                {
                                        br++;
                                        StringGrid2->Cells [0][br-1] = Form1->ADOQuery1->FieldByName("Ime")->AsString;
                                        switch (Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger)
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

                                        StringGrid2->Cells [1][br-1] = Zvanie;
                                        StringGrid2->Cells [2][br-1] = Stepen;
                                        StringGrid2->Cells [3][br-1] = Dlajnost;
                                        StringGrid2->Cells [4][br-1] = IntToStr(brutna);
                                        StringGrid2->Cells [5][br-1] = IntToStr((udrajki*brutna)/100);
                                        StringGrid2->Cells [6][br-1] = IntToStr(zapoluchavane);
//                                }
                                if (!Form1->ADOQuery1->Eof)
                                        Form1->ADOQuery1->Next();
                                StringGrid2->RowCount= br;
                        }                        break;
                case 17:
                        query = "SELECT * FROM Prepodavateli WHERE KodStepen = 2 AND KodZvanie > 3 AND Staj > " + criteria;
                        Form1->ADOQuery1->Close();
                        Form1->ADOQuery1->SQL->Clear();
                        Form1->ADOQuery1->SQL->Add(query);
                        Form1->ADOQuery1->Open();
                        if (Form1->ADOQuery1->RecordCount <= 0)
                                break;
                        Form1->ADOQuery1->First();
                        for (int i=1; i<=Form1->ADOQuery1->RecordCount; i++)
                        {
                                int KodZvanie = Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger;
                                int KodStepen = Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger;
                                int Staj = Form1->ADOQuery1->FieldByName("Staj")->AsInteger;
                                int Deca = Form1->ADOQuery1->FieldByName("BroiDeca")->AsInteger;
                                int KodDlajnost = Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger;
                                int Nadbavka = 0;
                                int Shtatna = 0;
                                int brutna = 0;
                                int udrajki = 5;
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
//                                if (brutna > StrToInt(criteria))
//                                {
                                        br++;
                                        StringGrid2->Cells [0][br-1] = Form1->ADOQuery1->FieldByName("Ime")->AsString;
                                        switch (Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger)
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

                                        StringGrid2->Cells [1][br-1] = Zvanie;
                                        StringGrid2->Cells [2][br-1] = Stepen;
                                        StringGrid2->Cells [3][br-1] = Dlajnost;
                                        StringGrid2->Cells [4][br-1] = IntToStr(brutna);
                                        StringGrid2->Cells [5][br-1] = IntToStr((udrajki*brutna)/100);
                                        StringGrid2->Cells [6][br-1] = IntToStr(zapoluchavane);
//                                }
                                if (!Form1->ADOQuery1->Eof)
                                        Form1->ADOQuery1->Next();
                                StringGrid2->RowCount= br;
                        }                        break;
                case 18:
                        query = "SELECT * FROM Prepodavateli WHERE KodStepen = 1 AND KodZvanie = 4 AND Staj < " + criteria;
                        Form1->ADOQuery1->Close();
                        Form1->ADOQuery1->SQL->Clear();
                        Form1->ADOQuery1->SQL->Add(query);
                        Form1->ADOQuery1->Open();
                        if (Form1->ADOQuery1->RecordCount <= 0)
                                break;
                        Form1->ADOQuery1->First();
                        for (int i=1; i<=Form1->ADOQuery1->RecordCount; i++)
                        {
                                int KodZvanie = Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger;
                                int KodStepen = Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger;
                                int Staj = Form1->ADOQuery1->FieldByName("Staj")->AsInteger;
                                int Deca = Form1->ADOQuery1->FieldByName("BroiDeca")->AsInteger;
                                int KodDlajnost = Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger;
                                int Nadbavka = 0;
                                int Shtatna = 0;
                                int brutna = 0;
                                int udrajki = 5;
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
//                                if (brutna > StrToInt(criteria))
//                                {
                                        br++;
                                        StringGrid2->Cells [0][br-1] = Form1->ADOQuery1->FieldByName("Ime")->AsString;
                                        switch (Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger)
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

                                        StringGrid2->Cells [1][br-1] = Zvanie;
                                        StringGrid2->Cells [2][br-1] = Stepen;
                                        StringGrid2->Cells [3][br-1] = Dlajnost;
                                        StringGrid2->Cells [4][br-1] = IntToStr(brutna);
                                        StringGrid2->Cells [5][br-1] = IntToStr((udrajki*brutna)/100);
                                        StringGrid2->Cells [6][br-1] = IntToStr(zapoluchavane);
//                                }
                                if (!Form1->ADOQuery1->Eof)
                                        Form1->ADOQuery1->Next();
                                StringGrid2->RowCount= br;
                        }                        break;
                case 19:
                        query = "SELECT * FROM Prepodavateli WHERE KodDlajnost > 0 AND KodZvanie = 5 AND Staj > " + criteria;
                        Form1->ADOQuery1->Close();
                        Form1->ADOQuery1->SQL->Clear();
                        Form1->ADOQuery1->SQL->Add(query);
                        Form1->ADOQuery1->Open();
                        if (Form1->ADOQuery1->RecordCount <= 0)
                                break;
                        Form1->ADOQuery1->First();
                        for (int i=1; i<=Form1->ADOQuery1->RecordCount; i++)
                        {
                                int KodZvanie = Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger;
                                int KodStepen = Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger;
                                int Staj = Form1->ADOQuery1->FieldByName("Staj")->AsInteger;
                                int Deca = Form1->ADOQuery1->FieldByName("BroiDeca")->AsInteger;
                                int KodDlajnost = Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger;
                                int Nadbavka = 0;
                                int Shtatna = 0;
                                int brutna = 0;
                                int udrajki = 5;
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
//                                if (brutna > StrToInt(criteria))
//                                {
                                        br++;
                                        StringGrid2->Cells [0][br-1] = Form1->ADOQuery1->FieldByName("Ime")->AsString;
                                        switch (Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger)
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

                                        StringGrid2->Cells [1][br-1] = Zvanie;
                                        StringGrid2->Cells [2][br-1] = Stepen;
                                        StringGrid2->Cells [3][br-1] = Dlajnost;
                                        StringGrid2->Cells [4][br-1] = IntToStr(brutna);
                                        StringGrid2->Cells [5][br-1] = IntToStr((udrajki*brutna)/100);
                                        StringGrid2->Cells [6][br-1] = IntToStr(zapoluchavane);
//                                }
                                if (!Form1->ADOQuery1->Eof)
                                        Form1->ADOQuery1->Next();
                                StringGrid2->RowCount= br;
                        }                        break;
                case 20:
                        query = "SELECT * FROM Prepodavateli WHERE KodZvanie = 3";
                        Form1->ADOQuery1->Close();
                        Form1->ADOQuery1->SQL->Clear();
                        Form1->ADOQuery1->SQL->Add(query);
                        Form1->ADOQuery1->Open();
                        if (Form1->ADOQuery1->RecordCount <= 0)
                                break;
                        Form1->ADOQuery1->First();
                        for (int i=1; i<=Form1->ADOQuery1->RecordCount; i++)
                        {
                                int KodZvanie = Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger;
                                int KodStepen = Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger;
                                int Staj = Form1->ADOQuery1->FieldByName("Staj")->AsInteger;
                                int Deca = Form1->ADOQuery1->FieldByName("BroiDeca")->AsInteger;
                                int KodDlajnost = Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger;
                                int Nadbavka = 0;
                                int Shtatna = 0;
                                int brutna = 0;
                                int udrajki = 5;
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
                                if (brutna > StrToInt(criteria))
                                {
                                        br++;
                                        StringGrid2->Cells [0][br-1] = Form1->ADOQuery1->FieldByName("Ime")->AsString;
                                        switch (Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger)
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

                                        StringGrid2->Cells [1][br-1] = Zvanie;
                                        StringGrid2->Cells [2][br-1] = Stepen;
                                        StringGrid2->Cells [3][br-1] = Dlajnost;
                                        StringGrid2->Cells [4][br-1] = IntToStr(brutna);
                                        StringGrid2->Cells [5][br-1] = IntToStr((udrajki*brutna)/100);
                                        StringGrid2->Cells [6][br-1] = IntToStr(zapoluchavane);
                                }
                                if (!Form1->ADOQuery1->Eof)
                                        Form1->ADOQuery1->Next();
                                StringGrid2->RowCount= br;
                        }                        break;
                case 21:
                        query = "SELECT * FROM Prepodavateli WHERE KodZvanie > 1 AND KodZvanie < 4 AND Staj < " + criteria;
                        Form1->ADOQuery1->Close();
                        Form1->ADOQuery1->SQL->Clear();
                        Form1->ADOQuery1->SQL->Add(query);
                        Form1->ADOQuery1->Open();
                        if (Form1->ADOQuery1->RecordCount <= 0)
                                break;
                        Form1->ADOQuery1->First();
                        for (int i=1; i<=Form1->ADOQuery1->RecordCount; i++)
                        {
                                int KodZvanie = Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger;
                                int KodStepen = Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger;
                                int Staj = Form1->ADOQuery1->FieldByName("Staj")->AsInteger;
                                int Deca = Form1->ADOQuery1->FieldByName("BroiDeca")->AsInteger;
                                int KodDlajnost = Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger;
                                int Nadbavka = 0;
                                int Shtatna = 0;
                                int brutna = 0;
                                int udrajki = 5;
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
//                                if (brutna > StrToInt(criteria))
//                                {
                                        br++;
                                        StringGrid2->Cells [0][br-1] = Form1->ADOQuery1->FieldByName("Ime")->AsString;
                                        switch (Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger)
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

                                        StringGrid2->Cells [1][br-1] = Zvanie;
                                        StringGrid2->Cells [2][br-1] = Stepen;
                                        StringGrid2->Cells [3][br-1] = Dlajnost;
                                        StringGrid2->Cells [4][br-1] = IntToStr(brutna);
                                        StringGrid2->Cells [5][br-1] = IntToStr((udrajki*brutna)/100);
                                        StringGrid2->Cells [6][br-1] = IntToStr(zapoluchavane);
//                                }
                                if (!Form1->ADOQuery1->Eof)
                                        Form1->ADOQuery1->Next();
                                StringGrid2->RowCount= br;
                        }                        break;
                case 22:
                        query = "SELECT * FROM Prepodavateli WHERE KodZvanie > 3 AND KodZvanie < 6 AND KodStepen = 1";
                        Form1->ADOQuery1->Close();
                        Form1->ADOQuery1->SQL->Clear();
                        Form1->ADOQuery1->SQL->Add(query);
                        Form1->ADOQuery1->Open();
                        if (Form1->ADOQuery1->RecordCount <= 0)
                                break;
                        Form1->ADOQuery1->First();
                        for (int i=1; i<=Form1->ADOQuery1->RecordCount; i++)
                        {
                                int KodZvanie = Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger;
                                int KodStepen = Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger;
                                int Staj = Form1->ADOQuery1->FieldByName("Staj")->AsInteger;
                                int Deca = Form1->ADOQuery1->FieldByName("BroiDeca")->AsInteger;
                                int KodDlajnost = Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger;
                                int Nadbavka = 0;
                                int Shtatna = 0;
                                int brutna = 0;
                                int udrajki = 5;
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
                                if (brutna < StrToInt(criteria))
                                {
                                        br++;
                                        StringGrid2->Cells [0][br-1] = Form1->ADOQuery1->FieldByName("Ime")->AsString;
                                        switch (Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger)
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

                                        StringGrid2->Cells [1][br-1] = Zvanie;
                                        StringGrid2->Cells [2][br-1] = Stepen;
                                        StringGrid2->Cells [3][br-1] = Dlajnost;
                                        StringGrid2->Cells [4][br-1] = IntToStr(brutna);
                                        StringGrid2->Cells [5][br-1] = IntToStr((udrajki*brutna)/100);
                                        StringGrid2->Cells [6][br-1] = IntToStr(zapoluchavane);
                                }
                                if (!Form1->ADOQuery1->Eof)
                                        Form1->ADOQuery1->Next();
                                StringGrid2->RowCount= br;
                        }                        break;
                case 23:
                        query = "SELECT * FROM Prepodavateli WHERE KodZvanie > 1 AND KodZvanie < 4 AND BroiDeca > " + criteria;
                        Form1->ADOQuery1->Close();
                        Form1->ADOQuery1->SQL->Clear();
                        Form1->ADOQuery1->SQL->Add(query);
                        Form1->ADOQuery1->Open();
                        if (Form1->ADOQuery1->RecordCount <= 0)
                                break;
                        Form1->ADOQuery1->First();
                        for (int i=1; i<=Form1->ADOQuery1->RecordCount; i++)
                        {
                                int KodZvanie = Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger;
                                int KodStepen = Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger;
                                int Staj = Form1->ADOQuery1->FieldByName("Staj")->AsInteger;
                                int Deca = Form1->ADOQuery1->FieldByName("BroiDeca")->AsInteger;
                                int KodDlajnost = Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger;
                                int Nadbavka = 0;
                                int Shtatna = 0;
                                int brutna = 0;
                                int udrajki = 5;
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
//                                if (brutna > StrToInt(criteria))
//                                {
                                        br++;
                                        StringGrid2->Cells [0][br-1] = Form1->ADOQuery1->FieldByName("Ime")->AsString;
                                        switch (Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger)
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

                                        StringGrid2->Cells [1][br-1] = Zvanie;
                                        StringGrid2->Cells [2][br-1] = Stepen;
                                        StringGrid2->Cells [3][br-1] = Dlajnost;
                                        StringGrid2->Cells [4][br-1] = IntToStr(brutna);
                                        StringGrid2->Cells [5][br-1] = IntToStr((udrajki*brutna)/100);
                                        StringGrid2->Cells [6][br-1] = IntToStr(zapoluchavane);
//                                }
                                if (!Form1->ADOQuery1->Eof)
                                        Form1->ADOQuery1->Next();
                                StringGrid2->RowCount= br;
                        }                        break;
                case 24:
                        query = "SELECT * FROM Prepodavateli WHERE KodZvanie > 3 AND KodZvanie < 6 AND KodDlajnost = 1";
                        Form1->ADOQuery1->Close();
                        Form1->ADOQuery1->SQL->Clear();
                        Form1->ADOQuery1->SQL->Add(query);
                        Form1->ADOQuery1->Open();
                        if (Form1->ADOQuery1->RecordCount <= 0)
                                break;
                        Form1->ADOQuery1->First();
                        for (int i=1; i<=Form1->ADOQuery1->RecordCount; i++)
                        {
                                int KodZvanie = Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger;
                                int KodStepen = Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger;
                                int Staj = Form1->ADOQuery1->FieldByName("Staj")->AsInteger;
                                int Deca = Form1->ADOQuery1->FieldByName("BroiDeca")->AsInteger;
                                int KodDlajnost = Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger;
                                int Nadbavka = 0;
                                int Shtatna = 0;
                                int brutna = 0;
                                int udrajki = 5;
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
                                if (brutna > StrToInt(criteria))
                                {
                                        br++;
                                        StringGrid2->Cells [0][br-1] = Form1->ADOQuery1->FieldByName("Ime")->AsString;
                                        switch (Form1->ADOQuery1->FieldByName("KodZvanie")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodStepen")->AsInteger)
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
                                        switch (Form1->ADOQuery1->FieldByName("KodDlajnost")->AsInteger)
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

                                        StringGrid2->Cells [1][br-1] = Zvanie;
                                        StringGrid2->Cells [2][br-1] = Stepen;
                                        StringGrid2->Cells [3][br-1] = Dlajnost;
                                        StringGrid2->Cells [4][br-1] = IntToStr(brutna);
                                        StringGrid2->Cells [5][br-1] = IntToStr((udrajki*brutna)/100);
                                        StringGrid2->Cells [6][br-1] = IntToStr(zapoluchavane);
                                }
                                if (!Form1->ADOQuery1->Eof)
                                        Form1->ADOQuery1->Next();
                                StringGrid2->RowCount= br;
                        }                        break;
                default:
                        break;
        }
        Form1->ADOQuery1->Close();
}
catch(int &rangeErr)
{
        MessageBox(0,"GSDFSDFSDF","XXXXXXXXX",0);
}
}
//---------------------------------------------------------------------------
