object Form2: TForm2
  Left = 246
  Top = 222
  Width = 632
  Height = 407
  Caption = #1044#1077#1090#1072#1081#1083#1085#1080' '#1057#1087#1088#1072#1074#1082#1080
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 296
    Top = 208
    Width = 51
    Height = 13
    Caption = #1050#1088#1080#1090#1077#1088#1080#1081':'
  end
  object StringGrid2: TStringGrid
    Left = 0
    Top = 5
    Width = 609
    Height = 148
    ColCount = 7
    FixedCols = 0
    RowCount = 2
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goColSizing, goRowSelect]
    TabOrder = 0
    ColWidths = (
      94
      91
      94
      72
      70
      52
      106)
    RowHeights = (
      24
      24)
  end
  object ComboBox1: TComboBox
    Left = 8
    Top = 176
    Width = 601
    Height = 21
    ItemHeight = 13
    TabOrder = 1
    Text = '-'#1048#1079#1073#1077#1088#1080' '#1047#1072#1103#1074#1082#1072'-'
    Items.Strings = (
      
        '1/ '#1057#1072#1084#1086' '#1085#1072' '#1072#1089#1080#1089#1090#1077#1085#1090#1080' '#1089' '#1073#1088#1091#1090#1085#1072' '#1079#1072#1087#1083#1072#1090#1072' , '#1087#1086'-'#1075#1086#1083#1103#1084#1072' '#1086#1090' '#1074#1098#1074#1077#1078#1076#1072#1085#1072' '#1089 +
        #1091#1084#1072'.'
      
        '2/ '#1057#1072#1084#1086' '#1085#1072' '#1075#1083'. '#1072#1089#1080#1089#1090#1077#1085#1090#1080' '#1089' '#1087#1088#1077#1087#1086#1076#1072#1074#1072#1090#1077#1083#1089#1082#1080' '#1089#1090#1072#1078', '#1087#1086'-'#1075#1086#1083#1103#1084' '#1086#1090' '#1074#1098#1074 +
        #1077#1078#1076#1072#1085' '#1073#1088#1086#1081'.'
      
        '3/ '#1057#1072#1084#1086' '#1085#1072' '#1076#1086#1094#1077#1085#1090#1080' '#1089' '#1085#1072#1091#1095#1085#1072' '#1089#1090#1077#1087#1077#1085' '#1080' '#1089' '#1073#1088#1091#1090#1085#1072' '#1079#1072#1087#1083#1072#1090#1072', '#1087#1086'-'#1084#1072#1083#1082#1072' ' +
        #1086#1090' '#1074#1098#1074#1077#1078#1076#1072#1085#1072' '#1089#1091#1084#1072'.'
      
        '4/ '#1057#1072#1084#1086' '#1085#1072' '#1089#1090#1072#1088#1096#1080' '#1072#1089#1080#1089#1090#1077#1085#1090#1080' '#1089' '#1073#1088#1086#1081' '#1076#1077#1094#1072' , '#1087#1086'-'#1075#1086#1083#1103#1084' '#1086#1090' '#1074#1098#1074#1077#1078#1076#1072#1085#1086' ' +
        #1095#1080#1089#1083#1086'.'
      
        '5/ '#1057#1072#1084#1086' '#1085#1072' '#1087#1088#1086#1092#1077#1089#1086#1088#1080', '#1088#1098#1082#1086#1074#1086#1076#1080#1090#1077#1083#1080' '#1085#1072' '#1082#1072#1090#1077#1076#1088#1080', '#1089' '#1073#1088#1091#1090#1085#1072' '#1079#1072#1087#1083#1072#1090#1072' ' +
        ', '#1087#1086'-'#1075#1086#1083#1103#1084#1072' '#1086#1090' '#1074#1098#1074#1077#1078#1076#1072#1085#1072' '#1089#1091#1084#1072'.'
      
        '6/ '#1057#1072#1084#1086' '#1085#1072' '#1085#1077#1093#1072#1073#1080#1083#1080#1090#1080#1088#1072#1085#1080' '#1087#1088#1077#1087#1086#1076#1072#1074#1072#1090#1077#1083#1080' '#1089' '#1087#1088#1077#1087#1086#1076#1072#1074#1072#1090#1077#1083#1089#1082#1080' '#1089#1090#1072#1078', ' +
        #1087#1086'-'#1084#1072#1083#1098#1082' '#1086#1090' '#1074#1098#1074#1077#1078#1076#1072#1085' '#1073#1088#1086#1081'.'
      
        '7/ '#1057#1072#1084#1086' '#1085#1072' '#1093#1072#1073#1080#1083#1080#1090#1080#1088#1072#1085#1080' '#1087#1088#1077#1087#1086#1076#1072#1074#1072#1090#1077#1083#1080' '#1089' '#1085#1072#1091#1095#1085#1072' '#1089#1090#1077#1087#1077#1085' '#1076#1086#1082#1090#1086#1088' '#1085#1072' ' +
        #1085#1072#1091#1082#1080#1090#1077' '#1080' '#1087#1088#1077#1087#1086#1076#1072#1074#1072#1090#1077#1083#1089#1082#1080' '#1089#1090#1072#1078', '#1087#1086'-'#1075#1086#1083#1103#1084' '#1086#1090' '#1074#1098#1074#1077#1078#1076#1072#1085' '#1073#1088#1086#1081'.'
      
        '8/ '#1057#1072#1084#1086' '#1085#1072' '#1085#1077#1093#1072#1073#1080#1083#1080#1090#1080#1088#1072#1085#1080' '#1087#1088#1077#1087#1086#1076#1072#1074#1072#1090#1077#1083#1080' '#1089' '#1085#1072#1091#1095#1085#1072' '#1089#1090#1077#1087#1077#1085' '#1076#1086#1082#1090#1086#1088' '#1080 +
        ' '#1087#1088#1077#1087#1086#1076#1072#1074#1072#1090#1077#1083#1089#1082#1080' '#1089#1090#1072#1078', '#1087#1086'-'#1075#1086#1083#1103#1084' '#1086#1090' '#1074#1098#1074#1077#1078#1076#1072#1085' '#1073#1088#1086#1081'.'
      
        '9/ '#1057#1072#1084#1086' '#1085#1072' '#1087#1088#1086#1092#1077#1089#1086#1088#1080' '#1089' '#1085#1072#1091#1095#1085#1072' '#1089#1090#1077#1087#1077#1085' '#1076#1086#1082#1090#1086#1088' '#1080' '#1089' '#1087#1088#1077#1087#1086#1076#1072#1074#1072#1090#1077#1083#1089#1082#1080' ' +
        #1089#1090#1072#1078', '#1087#1086'-'#1084#1072#1083#1098#1082' '#1086#1090' '#1074#1098#1074#1077#1078#1076#1072#1085' '#1073#1088#1086#1081'.'
      
        '10/ '#1057#1072#1084#1086' '#1085#1072' '#1087#1088#1086#1092#1077#1089#1086#1088#1080' '#1073#1077#1079' '#1088#1098#1082#1086#1074#1086#1076#1085#1072' '#1076#1083#1098#1078#1085#1086#1089#1090' '#1080' '#1089' '#1087#1088#1077#1087#1086#1076#1072#1074#1072#1090#1077#1083#1089#1082#1080 +
        ' '#1089#1090#1072#1078', '#1087#1086'-'#1075#1086#1083#1103#1084' '#1086#1090' '#1074#1098#1074#1077#1078#1076#1072#1085' '#1073#1088#1086#1081'.'
      
        '11/ '#1057#1072#1084#1086' '#1085#1072' '#1089#1090#1072#1088#1096#1080' '#1072#1089#1080#1089#1090#1077#1085#1090#1080' '#1089' '#1073#1088#1091#1090#1085#1072' '#1079#1072#1087#1083#1072#1090#1072' , '#1087#1086'-'#1075#1086#1083#1103#1084#1072' '#1086#1090' '#1074#1098#1074 +
        #1077#1078#1076#1072#1085#1072' '#1089#1091#1084#1072'.'
      
        '12/ '#1057#1072#1084#1086' '#1085#1072' '#1072#1089#1080#1089#1090#1077#1085#1090#1080' '#1089' '#1087#1088#1077#1087#1086#1076#1072#1074#1072#1090#1077#1083#1089#1082#1080' '#1089#1090#1072#1078', '#1087#1086'-'#1075#1086#1083#1103#1084' '#1086#1090' '#1074#1098#1074#1077#1078#1076 +
        #1072#1085' '#1073#1088#1086#1081'.'
      
        '13/ '#1057#1072#1084#1086' '#1085#1072' '#1087#1088#1086#1092#1077#1089#1086#1088#1080' '#1089' '#1085#1072#1091#1095#1085#1072' '#1089#1090#1077#1087#1077#1085' '#1080' '#1089' '#1073#1088#1091#1090#1085#1072' '#1079#1072#1087#1083#1072#1090#1072', '#1087#1086'-'#1084#1072#1083 +
        #1082#1072' '#1086#1090' '#1074#1098#1074#1077#1078#1076#1072#1085#1072' '#1089#1091#1084#1072'.'
      
        '14/ '#1057#1072#1084#1086' '#1085#1072' '#1075#1083#1072#1074#1085#1080' '#1072#1089#1080#1089#1090#1077#1085#1090#1080' '#1089' '#1073#1088#1086#1081' '#1076#1077#1094#1072' , '#1087#1086'-'#1075#1086#1083#1103#1084' '#1086#1090' '#1074#1098#1074#1077#1078#1076#1072#1085#1086 +
        ' '#1095#1080#1089#1083#1086'.'
      
        '15/ '#1057#1072#1084#1086' '#1085#1072' '#1076#1086#1094#1077#1085#1090#1080', '#1088#1098#1082#1086#1074#1086#1076#1080#1090#1077#1083#1080' '#1085#1072' '#1082#1072#1090#1077#1076#1088#1080', '#1089' '#1073#1088#1091#1090#1085#1072' '#1079#1072#1087#1083#1072#1090#1072' ,' +
        ' '#1087#1086'-'#1075#1086#1083#1103#1084#1072' '#1086#1090' '#1074#1098#1074#1077#1078#1076#1072#1085#1072' '#1089#1091#1084#1072'.'
      
        '16/ '#1057#1072#1084#1086' '#1085#1072' '#1093#1072#1073#1080#1083#1080#1090#1080#1088#1072#1085#1080' '#1087#1088#1077#1087#1086#1076#1072#1074#1072#1090#1077#1083#1080' '#1089' '#1087#1088#1077#1087#1086#1076#1072#1074#1072#1090#1077#1083#1089#1082#1080' '#1089#1090#1072#1078', '#1087 +
        #1086'-'#1084#1072#1083#1098#1082' '#1086#1090' '#1074#1098#1074#1077#1078#1076#1072#1085' '#1073#1088#1086#1081'.'
      
        '17/ '#1057#1072#1084#1086' '#1085#1072' '#1085#1077#1093#1072#1073#1080#1083#1080#1090#1080#1088#1072#1085#1080' '#1087#1088#1077#1087#1086#1076#1072#1074#1072#1090#1077#1083#1080' '#1089' '#1085#1072#1091#1095#1085#1072' '#1089#1090#1077#1087#1077#1085' '#1076#1086#1082#1090#1086#1088' ' +
        #1080' '#1087#1088#1077#1087#1086#1076#1072#1074#1072#1090#1077#1083#1089#1082#1080' '#1089#1090#1072#1078', '#1087#1086'-'#1075#1086#1083#1103#1084' '#1086#1090' '#1074#1098#1074#1077#1078#1076#1072#1085' '#1073#1088#1086#1081'.'
      
        '18/ '#1057#1072#1084#1086' '#1085#1072' '#1093#1072#1073#1080#1083#1080#1090#1080#1088#1072#1085#1080' '#1087#1088#1077#1087#1086#1076#1072#1074#1072#1090#1077#1083#1080' '#1089' '#1085#1072#1091#1095#1085#1072' '#1089#1090#1077#1087#1077#1085' '#1076#1086#1082#1090#1086#1088' '#1085#1072 +
        ' '#1085#1072#1091#1082#1080#1090#1077' '#1080' '#1087#1088#1077#1087#1086#1076#1072#1074#1072#1090#1077#1083#1089#1082#1080' '#1089#1090#1072#1078', '#1087#1086'-'#1075#1086#1083#1103#1084' '#1086#1090' '#1074#1098#1074#1077#1078#1076#1072#1085' '#1073#1088#1086#1081'.'
      
        '19/ '#1057#1072#1084#1086' '#1085#1072' '#1076#1086#1094#1077#1085#1090#1080' '#1089' '#1085#1072#1091#1095#1085#1072' '#1089#1090#1077#1087#1077#1085' '#1076#1086#1082#1090#1086#1088' '#1080' '#1089' '#1087#1088#1077#1087#1086#1076#1072#1074#1072#1090#1077#1083#1089#1082#1080' '#1089 +
        #1090#1072#1078', '#1087#1086'-'#1084#1072#1083#1098#1082' '#1086#1090' '#1074#1098#1074#1077#1078#1076#1072#1085' '#1073#1088#1086#1081'.'
      
        '20/ '#1057#1072#1084#1086' '#1085#1072' '#1087#1088#1086#1092#1077#1089#1086#1088#1080' '#1089' '#1088#1098#1082#1086#1074#1086#1076#1085#1072' '#1076#1083#1098#1078#1085#1086#1089#1090' '#1080' '#1089' '#1087#1088#1077#1087#1086#1076#1072#1074#1072#1090#1077#1083#1089#1082#1080' '#1089 +
        #1090#1072#1078', '#1087#1086'-'#1075#1086#1083#1103#1084' '#1086#1090' '#1074#1098#1074#1077#1078#1076#1072#1085' '#1073#1088#1086#1081'.'
      
        '21/ '#1057#1072#1084#1086' '#1085#1072' '#1075#1083#1072#1074#1085#1080' '#1072#1089#1080#1089#1090#1077#1085#1090#1080' '#1089' '#1073#1088#1091#1090#1085#1072' '#1079#1072#1087#1083#1072#1090#1072' , '#1087#1086'-'#1084#1072#1083#1082#1072' '#1086#1090' '#1074#1098#1074#1077 +
        #1078#1076#1072#1085#1072' '#1089#1091#1084#1072'.'
      
        '22/ '#1057#1072#1084#1086' '#1085#1072' '#1089#1090#1072#1088#1096#1080' '#1080' '#1075#1083#1072#1074#1085#1080' '#1072#1089#1080#1089#1090#1077#1085#1090#1080' '#1089' '#1087#1088#1077#1087#1086#1076#1072#1074#1072#1090#1077#1083#1089#1082#1080' '#1089#1090#1072#1078', '#1087#1086 +
        '-'#1084#1072#1083#1098#1082' '#1086#1090' '#1074#1098#1074#1077#1078#1076#1072#1085' '#1073#1088#1086#1081'.'
      
        '23/ '#1057#1072#1084#1086' '#1085#1072' '#1076#1086#1094#1077#1085#1090#1080' '#1080' '#1087#1088#1086#1092#1077#1089#1086#1088#1080' '#1089' '#1085#1072#1091#1095#1085#1072' '#1089#1090#1077#1087#1077#1085' '#1076#1086#1082#1090#1086#1088' '#1080' '#1089' '#1073#1088#1091#1090#1085 +
        #1072' '#1079#1072#1087#1083#1072#1090#1072', '#1087#1086'-'#1084#1072#1083#1082#1072' '#1086#1090' '#1074#1098#1074#1077#1078#1076#1072#1085#1072' '#1089#1091#1084#1072'.'
      
        '24/ '#1057#1072#1084#1086' '#1085#1072' '#1089#1090#1072#1088#1096#1080' '#1080' '#1075#1083#1072#1074#1085#1080' '#1072#1089#1080#1089#1090#1077#1085#1090#1080' '#1089' '#1073#1088#1086#1081' '#1076#1077#1094#1072', '#1087#1086'-'#1075#1086#1083#1103#1084' '#1086#1090' '#1074 +
        #1098#1074#1077#1078#1076#1072#1085#1086' '#1095#1080#1089#1083#1086'.'
      
        '25/ '#1057#1072#1084#1086' '#1085#1072' '#1076#1086#1094#1077#1085#1090#1080' '#1080' '#1087#1088#1086#1092#1077#1089#1086#1088#1080', '#1088#1098#1082#1086#1074#1086#1076#1080#1090#1077#1083#1080' '#1085#1072' '#1082#1072#1090#1077#1076#1088#1080', '#1089' '#1073#1088#1091#1090 +
        #1085#1072' '#1079#1072#1087#1083#1072#1090#1072' , '#1087#1086'-'#1075#1086#1083#1103#1084#1072' '#1086#1090' '#1074#1098#1074#1077#1078#1076#1072#1085#1072' '#1089#1091#1084#1072'.')
  end
  object Edit1: TEdit
    Left = 261
    Top = 224
    Width = 121
    Height = 21
    TabOrder = 2
  end
  object BitBtn1: TBitBtn
    Left = 269
    Top = 264
    Width = 105
    Height = 25
    Caption = #1048#1079#1074#1077#1076#1080'!'
    Default = True
    ModalResult = 1
    TabOrder = 3
    OnClick = BitBtn1Click
    Glyph.Data = {
      DE010000424DDE01000000000000760000002800000024000000120000000100
      0400000000006801000000000000000000001000000000000000000000000000
      80000080000000808000800000008000800080800000C0C0C000808080000000
      FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF00333333333333
      3333333333333333333333330000333333333333333333333333F33333333333
      00003333344333333333333333388F3333333333000033334224333333333333
      338338F3333333330000333422224333333333333833338F3333333300003342
      222224333333333383333338F3333333000034222A22224333333338F338F333
      8F33333300003222A3A2224333333338F3838F338F33333300003A2A333A2224
      33333338F83338F338F33333000033A33333A222433333338333338F338F3333
      0000333333333A222433333333333338F338F33300003333333333A222433333
      333333338F338F33000033333333333A222433333333333338F338F300003333
      33333333A222433333333333338F338F00003333333333333A22433333333333
      3338F38F000033333333333333A223333333333333338F830000333333333333
      333A333333333333333338330000333333333333333333333333333333333333
      0000}
    NumGlyphs = 2
  end
end
