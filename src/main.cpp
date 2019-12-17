/*
 * @Date: 2019-12-15 16:08:59
 * @LastEditors: Gavin Chen
 * @Github: https://github.com/Heanden
 * @�γ����ó���: https://eiet.xyz
 * @������Ŀ: https://eiet.xyz/ITEM/
 * @LastEditTime: 2019-12-17 11:27:12
 */
#include <arduino.h>
#include <Wire.h>                   //IIC
#include <LiquidCrystal_I2C.h>      //LCD1602ͷ�ļ�
#include <Servo.h>                  //���ͷ�ļ�
Servo myservo;                      // ����Servo����������,�������
LiquidCrystal_I2C lcd(0x27, 16, 2); //����LCD��ַ������
int pinA = 3;                       //CLK
int pinB = 4;                       //DT
int KEY = 5;                        //SW
int pinA_First;                     //pinA��״̬
int pinA_After;                     //pinA��״̬
int encoderPosCount = 0;
int countstate = 0;
int key_state; //KEY ״̬
int Pw1 = 0;
int Pw2 = 0;
int Pw3 = 0;
int clkcount = 0;
int keycount = 0;
int keycounto = 0;
boolean turndir; //��ת����˳ʱ��Ϊ�棬��ʱ��Ϊ��
boolean backstate = 1;

void setup()
{
  myservo.attach(9); // ��������������9
  pinMode(KEY, INPUT);
  lcd.init();      //��ʼ��LCD
  lcd.backlight(); //�򿪱���
  //��ʼ����ת������
  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);
  pinA_First = digitalRead(pinA); //��ȡpinA�����һ��״̬
  Serial.begin(9600);             //��ʼ������ͨ�ţ���������������Ϊ9600
  lcd.setCursor(3, 0);            //��һ�У�����λ
  lcd.print("XXXXXXX ");          //��ʱ��
  lcd.setCursor(15, 0);           //�ڶ��У���ʮ��λ
  lcd.print(encoderPosCount / 2); //λ��
  lcd.setBacklight(backstate);
  myservo.write(0);
}

void loop()
{
  if ((Pw3 == 1) && (Pw2 == 4) && (Pw1 == 7))
  {
    myservo.write(180);
    keycount = 0;
    keycounto = 0;
    lcd.setCursor(0, 0);
    lcd.print("    Unlocked    ");
    lcd.setCursor(0, 1);
    lcd.print("    Unlocked    ");
    delay(500);
    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("                ");
    delay(500);
    lcd.setCursor(0, 0);
    lcd.print("    Unlocked    ");
    lcd.setCursor(0, 1);
    lcd.print("    Unlocked    ");
    delay(500);
    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("                ");
    delay(500);
    lcd.setCursor(0, 0);
    lcd.print("    Unlocked    ");
    lcd.setCursor(0, 1);
    lcd.print("    Unlocked    ");
    delay(500);
    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("                ");
    delay(500);
    lcd.setCursor(0, 0);
    lcd.print("    Unlocked    ");
    lcd.setCursor(0, 1);
    lcd.print("    Unlocked    ");
    Pw1 = 0;
    Pw2 = 0;
    Pw3 = 0;
    delay(2000);
    lcd.setBacklight(backstate = !backstate);
    lcd.noDisplay();
    myservo.write(0);
    lcd.setCursor(3, 0);   //��һ�У�����λ
    lcd.print("XXXXXXX "); //��ʱ��
    lcd.setCursor(15, 0);  //��һ�У�����λ
    lcd.print((encoderPosCount = 0) / 2);
  }

  if ((Pw3 != 1) && (Pw2 != 4) && (Pw1 != 7))
  {
    lcd.setCursor(0, 1);
    lcd.print("     Locked     ");
  }

  key_state = digitalRead(KEY);

  if (key_state == 0)
  {
    lcd.setCursor(0, 0);
    lcd.print("DN ");
    clkcount = 0;
    lcd.setBacklight(backstate = 1);
    lcd.display();
  }
  else
  {
    lcd.setCursor(0, 0);
    lcd.print("UP ");
  }

  pinA_After = digitalRead(pinA); //��ȡpinA����һ��״̬
  if (pinA_After != pinA_First)   //�Ⱥ�����״̬���ȣ�˵������ת����ȡpinA�ж���ת����
  {
    if (digitalRead(pinB) != pinA_After) //���²���Ϊ˳ʱ��
    {
      encoderPosCount++;
      turndir = true;
    }

    else //�������Ϊ˳ʱ��
    {
      turndir = false;
      encoderPosCount--;
    }

    if (encoderPosCount > 19)
      encoderPosCount = 0;
    if (encoderPosCount < 0)
      encoderPosCount = 19;

    if (key_state == 0)
    {
      delay(10);
      if (key_state == 0)
      {
        encoderPosCount = 10;
        lcd.setCursor(0, 0);            //�ڶ��У���ʮ��λ
        lcd.print(encoderPosCount / 2); //λ��
      }
    }

    if (turndir)
    {
      lcd.setCursor(3, 0);   //��һ�У�����λ
      lcd.print(">>>>>>> "); //˳ʱ��

      lcd.setCursor(15, 0);           //�ڶ��У���ʮ��λ
      lcd.print(encoderPosCount / 2); //λ��
    }

    else
    {
      lcd.setCursor(3, 0);   //��һ�У�����λ
      lcd.print("<<<<<<< "); //��ʱ��

      lcd.setCursor(15, 0);           //�ڶ��У���ʮ��λ
      lcd.print(encoderPosCount / 2); //λ��
    }
  }

  lcd.setCursor(13, 0); //�ڶ��У���ʮ��λ
  lcd.print(Pw1);       //λ��
  lcd.setCursor(11, 0); //�ڶ��У���ʮ��λ
  lcd.print(Pw2);       //λ��

  if (key_state == 0)
  {
    delay(100);
    key_state = digitalRead(KEY);
    if (key_state == 0)
    {
      keycount++;
      keycounto++;
      Pw3 = Pw2;
      Pw2 = Pw1;
      Pw1 = encoderPosCount / 2;
    }
  }

  if ((keycount >= 4) && ((Pw3 != 1) || (Pw2 != 4) || (Pw1 != 7)))
  {
    lcd.setCursor(0, 0);
    lcd.print("UP ");
    keycount = 0;
    lcd.setCursor(0, 1);           //�ڶ��У���ʮ��λ
    lcd.print("     error!     "); //λ��
    delay(200);
    lcd.setCursor(0, 1);           //�ڶ��У���ʮ��λ
    lcd.print("      error!    "); //λ��
    delay(200);
    lcd.setCursor(0, 1);           //�ڶ��У���ʮ��λ
    lcd.print("    error!      "); //λ��
    delay(200);
    lcd.setCursor(0, 1);           //�ڶ��У���ʮ��λ
    lcd.print("      error!    "); //λ��
    delay(200);
    lcd.setCursor(0, 1);           //�ڶ��У���ʮ��λ
    lcd.print("    error!      "); //λ��
    delay(200);
    lcd.setCursor(0, 1);           //�ڶ��У���ʮ��λ
    lcd.print("     error!     "); //λ��
    delay(200);
    lcd.setCursor(0, 1);
    lcd.print("     Locked     ");
  }

  if (keycounto >= 5)
  {
    keycounto = 0;
    myservo.write(180);
    delay(3000);
    myservo.write(0);
  }

  if (clkcount >= 500)
  {
    clkcount = 0;
    lcd.setBacklight(backstate = 0);
    lcd.noDisplay();
  }
  clkcount++;
  pinA_First = pinA_After; //��״̬��Ϊ��״̬
}
