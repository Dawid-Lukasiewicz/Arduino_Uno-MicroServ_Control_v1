#include <Servo.h>

Servo Serw;
String Received = "";
uint32_t Position = 0, Change = 5, DelayedTimeMs = 100;
void setup()
{
    pinMode(13, OUTPUT);
    Serial.begin(9600);
    Serw.attach(3);
}

void loop()
{
    if (Serw.read() < 180)
    {
        if (Serial.available() > 0)
        {
            digitalWrite(13, HIGH);
            Received = Serial.readStringUntil('\n');
            while (Received == "stop" || Received == "")
            {
                Received = Serial.readStringUntil('\n');
                if (Received == "start")
                    break;
            }
        }
        DelayedTimeMs += 2 * Change;
        delay(DelayedTimeMs);
        Serw.write(Position);
        Position += Change;
        digitalWrite(13, LOW);
    }
    else
    {
        DelayedTimeMs = 0;
        Position = 0;
        Serw.write(Position);
        delay(500);
    }
}