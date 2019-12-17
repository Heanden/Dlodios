/*
 * @Date: 2019-12-15 16:08:59
 * @LastEditors: Gavin Chen
 * @Github: https://github.com/Heanden
 * @课程所用程序: https://eiet.xyz
 * @个人项目: https://eiet.xyz/ITEM/
 * @LastEditTime: 2019-12-17 11:27:12
 */
#include <arduino.h>
#include <Wire.h>                   //IIC
#include <LiquidCrystal_I2C.h>      //LCD1602头文件
#include <Servo.h>                  //舵机头文件
Servo myservo;                      // 定义Servo对象来控制,舵机驱动
LiquidCrystal_I2C lcd(0x27, 16, 2); //配置LCD地址及行列
int pinA = 3;                       //CLK
int pinB = 4;                       //DT
int KEY = 5;                        //SW
int pinA_First;                     //pinA先状态
int pinA_After;                     //pinA后状态
int encoderPosCount = 0;
int countstate = 0;
int key_state; //KEY 状态
int Pw1 = 0;
int Pw2 = 0;
int Pw3 = 0;
int clkcount = 0;
int keycount = 0;
int keycounto = 0;
boolean turndir; //旋转方向，顺时针为真，逆时针为假
boolean backstate = 1;

void setup()
{
  myservo.attach(9); // 控制线连接数字9
  pinMode(KEY, INPUT);
  lcd.init();      //初始化LCD
  lcd.backlight(); //打开背光
  //初始化旋转编码器
  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);
  pinA_First = digitalRead(pinA); //读取pinA的最后一个状态
  Serial.begin(9600);             //初始化串口通信，并将波特率设置为9600
  lcd.setCursor(3, 0);            //第一行，第五位
  lcd.print("XXXXXXX ");          //逆时针
  lcd.setCursor(15, 0);           //第二行，第十三位
  lcd.print(encoderPosCount / 2); //位置
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
    lcd.setCursor(3, 0);   //第一行，第五位
    lcd.print("XXXXXXX "); //逆时针
    lcd.setCursor(15, 0);  //第一行，第五位
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

  pinA_After = digitalRead(pinA); //读取pinA的下一个状态
  if (pinA_After != pinA_First)   //先后两个状态不等，说明在旋转，读取pinA判断旋转方向
  {
    if (digitalRead(pinB) != pinA_After) //上下不等为顺时针
    {
      encoderPosCount++;
      turndir = true;
    }

    else //上下相等为顺时针
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
        lcd.setCursor(0, 0);            //第二行，第十三位
        lcd.print(encoderPosCount / 2); //位置
      }
    }

    if (turndir)
    {
      lcd.setCursor(3, 0);   //第一行，第五位
      lcd.print(">>>>>>> "); //顺时针

      lcd.setCursor(15, 0);           //第二行，第十三位
      lcd.print(encoderPosCount / 2); //位置
    }

    else
    {
      lcd.setCursor(3, 0);   //第一行，第五位
      lcd.print("<<<<<<< "); //逆时针

      lcd.setCursor(15, 0);           //第二行，第十三位
      lcd.print(encoderPosCount / 2); //位置
    }
  }

  lcd.setCursor(13, 0); //第二行，第十三位
  lcd.print(Pw1);       //位置
  lcd.setCursor(11, 0); //第二行，第十三位
  lcd.print(Pw2);       //位置

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
    lcd.setCursor(0, 1);           //第二行，第十三位
    lcd.print("     error!     "); //位置
    delay(200);
    lcd.setCursor(0, 1);           //第二行，第十三位
    lcd.print("      error!    "); //位置
    delay(200);
    lcd.setCursor(0, 1);           //第二行，第十三位
    lcd.print("    error!      "); //位置
    delay(200);
    lcd.setCursor(0, 1);           //第二行，第十三位
    lcd.print("      error!    "); //位置
    delay(200);
    lcd.setCursor(0, 1);           //第二行，第十三位
    lcd.print("    error!      "); //位置
    delay(200);
    lcd.setCursor(0, 1);           //第二行，第十三位
    lcd.print("     error!     "); //位置
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
  pinA_First = pinA_After; //后状态变为先状态
}
