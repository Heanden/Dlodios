int pinA = 3; //CLK
int pinB = 4; // DT
int encoderPosCount = 0;
int pinA_First; //pinA先状态
int pinA_After; //pinA后状态

int KEY = 5;	 //KEY
int key_state;   //KEY状态
boolean turndir; //旋转方向，顺时针为真，逆时针为假

void setup()
{
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(KEY, INPUT);

	pinMode(pinA, INPUT);
	pinMode(pinB, INPUT);

	pinA_First = digitalRead(pinA); //读取pinA的最后一个状态
	Serial.begin(9600);				//初始化串口通信，并将波特率设置为9600
}

void loop()
{
	key_state = digitalRead(KEY);
	if (key_state == 0)
		digitalWrite(LED_BUILTIN, HIGH);
	else
		digitalWrite(LED_BUILTIN, LOW);

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

		Serial.print("Rotated: ");

		if (turndir)
		{
			Serial.println("clockwise");
		}

		else
		{
			Serial.println("counterclockwise");
		}

		Serial.print("Encoder Position: ");
		Serial.println(encoderPosCount);
	}
	pinA_First = pinA_After; //后状态变为先状态
}
