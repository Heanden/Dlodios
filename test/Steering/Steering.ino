/*
 * @Author: your name
 * @Date: 2019-12-13 20:55:14
 * @LastEditTime: 2019-12-15 16:46:20
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \Dlodios\test\Steering\Steering.ino
 */
#include <Servo.h>

Servo myservo; // 定义Servo对象来控制
int pos = 0;   // 角度存储变量

void setup()
{
  myservo.attach(9); // 控制线连接数字9
}

void loop()
{
  myservo.write(180);
  delay(1000);
  myservo.write(0);
  delay(1000);
}
