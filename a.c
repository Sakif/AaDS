int const sonicSensorPinFront = 4;
int const sonicSensorPinBack = 3;
int const LeftMotorE = 1;
int const RightMotorE = 2;
//int const rearLeftMotorE = 3;
//int const rearRightMotorE = 4;
int const frontLeftMotor1 = 5;
int const frontLeftMotor2 = 6;
int const frontRightMotor1 = 7;
int const frontRightMotor2 = 8;
int const rearLeftMotor1 = 9;
int const rearLeftMotor2 = 10;
int const rearRightMotor1 = 12;
int const rearRightMotor2 = 11;
int const switchPin = 0;
int const onLED = 13;

int const colour1 = A0;
int const colour2 = A1;
int const colour3 = A2;
int const colour4 = A3;

bool inititalDelayComplete = false;
float frontRange = 0.0;
float backRange = 0.0;

long readUltrasonicDistance(int pin)
{
	pinMode(pin, OUTPUT); // Clear the trigger
	digitalWrite(pin, LOW);
	delayMicroseconds(2); // Sets the pin on HIGH state for 10 micro seconds
	digitalWrite(pin, HIGH);
	delayMicroseconds(10);
	digitalWrite(pin, LOW);
	pinMode(pin, INPUT); // Reads the pin, and returns the sound wave travel time in microseconds
	return pulseIn(pin, HIGH);
}

void setup()
{
	Serial.begin(9600);
	pinMode(sonicSensorPinFront, INPUT);
	pinMode(sonicSensorPinBack, INPUT);
}

void loop()
{
	if (!inititalDelayComplete)
	{
		delay(5000);
		inititalDelayComplete = !inititalDelayComplete;
	}
	frontRange = 0.01723 * readUltrasonicDistance(sonicSensorPinFront);
	backRange = 0.01723 * readUltrasonicDistance(sonicSensorPinBack);
	Serial.print("Front: ");
	Serial.print(frontRange);
	Serial.print(" Back: ");
	Serial.println(backRange);
}