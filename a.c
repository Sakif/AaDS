int const sonicSensorPinFront = 4;
int const sonicSensorPinBack = 3;
int const leftMotorE = 1;
int const rightMotorE = 2;
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

int const irSensorFL = A0;
int const irSensorFR = A1;
int const irSensorRL = A2;
int const irSensorRR = A3;

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

	pinMode(irSensorFL, INPUT);
	pinMode(irSensorFR, INPUT);
	pinMode(irSensorRL, INPUT);
	pinMode(irSensorRR, INPUT);

	pinMode(rightMotorE, OUTPUT);
	pinMode(frontRightMotor1, OUTPUT);
	pinMode(frontRightMotor2, OUTPUT);
	pinMode(rearRightMotor1, OUTPUT);
	pinMode(rearRightMotor2, OUTPUT);

	pinMode(leftMotorE, OUTPUT);
	pinMode(frontLeftMotor1, OUTPUT);
	pinMode(frontLeftMotor2, OUTPUT);
	pinMode(rearLeftMotor1, OUTPUT);
	pinMode(rearLeftMotor2, OUTPUT);
}

void forward()
{
	digitalWrite(rightMotorE, HIGH);
	digitalWrite(frontRightMotor1, LOW);
	digitalWrite(frontRightMotor2, HIGH);
	digitalWrite(rearRightMotor1, HIGH);
	digitalWrite(rearRightMotor2, LOW);

	digitalWrite(leftMotorE, HIGH);
	digitalWrite(frontLeftMotor1, LOW);
	digitalWrite(frontLeftMotor2, HIGH);
	digitalWrite(rearLeftMotor1, LOW);
	digitalWrite(rearLeftMotor2, HIGH);
}

void back()
{
	digitalWrite(rightMotorE, HIGH);
	digitalWrite(frontRightMotor1, HIGH);
	digitalWrite(frontRightMotor2, LOW);
	digitalWrite(rearRightMotor1, LOW);
	digitalWrite(rearRightMotor2, HIGH);

	digitalWrite(leftMotorE, HIGH);
	digitalWrite(frontLeftMotor1, HIGH);
	digitalWrite(frontLeftMotor2, LOW);
	digitalWrite(rearLeftMotor1, HIGH);
	digitalWrite(rearLeftMotor2, LOW);
}

void right()
{
	digitalWrite(rightMotorE, HIGH);
	digitalWrite(frontRightMotor1, LOW);
	digitalWrite(frontRightMotor2, HIGH);
	digitalWrite(rearRightMotor1, HIGH);
	digitalWrite(rearRightMotor2, LOW);

	digitalWrite(leftMotorE, HIGH);
	digitalWrite(frontLeftMotor1, HIGH);
	digitalWrite(frontLeftMotor2, LOW);
	digitalWrite(rearLeftMotor1, HIGH);
	digitalWrite(rearLeftMotor2, LOW);
}

void left()
{
	digitalWrite(rightMotorE, HIGH);
	digitalWrite(frontRightMotor1, HIGH);
	digitalWrite(frontRightMotor2, LOW);
	digitalWrite(rearRightMotor1, LOW);
	digitalWrite(rearRightMotor2, HIGH);

	digitalWrite(leftMotorE, HIGH);
	digitalWrite(frontLeftMotor1, LOW);
	digitalWrite(frontLeftMotor2, HIGH);
	digitalWrite(rearLeftMotor1, LOW);
	digitalWrite(rearLeftMotor2, HIGH);
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

	digitalWrite(rightMotorE, HIGH);
	digitalWrite(frontRightMotor1, HIGH);
	digitalWrite(frontRightMotor2, LOW);
	digitalWrite(rearRightMotor1, HIGH);
	digitalWrite(rearRightMotor2, LOW);

	digitalWrite(leftMotorE, HIGH);
	digitalWrite(frontLeftMotor1, HIGH);
	digitalWrite(frontLeftMotor2, LOW);
	digitalWrite(rearLeftMotor1, HIGH);
	digitalWrite(rearLeftMotor2, LOW);
}