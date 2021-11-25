#include <Servo.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd (12,11,5,4,3,2);

float Vout = 0.0;
int lectura1 = 0;
int lectura2 = 0;
int lectura3 = 0; 
int lectura4 = 0;
int abajo = 0;
int arriba = 0;

Servo servoMotorAbajo;
Servo servoMotorArriba;


float Sensibilidad=0.100; //sensibilidad en Voltios/Amperio para sensor de 20A


void setup() 
{  
  pinMode (A0,INPUT);
  pinMode (A1,INPUT);
  pinMode (A2,INPUT);
  pinMode (A3,INPUT);
  pinMode (A4,INPUT);
  servoMotorAbajo.attach(9);
  servoMotorArriba.attach(7);

  servoMotorAbajo.write(abajo);
  servoMotorArriba.write(arriba);

  Serial.begin(9600);

}

void loop() 
{
  lectura1 = analogRead(A0);
  lectura2 = analogRead(A1);
  lectura3 = analogRead(A2);
  lectura4 = analogRead(A3);

  float voltajeSensor= analogRead(A4)*(5.0 / 1023.0); //lectura del sensor   
  float I=(voltajeSensor-2.5)/Sensibilidad; //Ecuación  para obtener la corriente
  lcd.setCursor(0,0);
  lcd.print("Corriente:");
  Serial.print("Corriente: ");
  Serial.print(-I);
  lcd.setCursor(8,1);
  lcd.print(-I);
  lcd.print("A");    
  delay(2000);
  //lcd.clear();


  if(A0 == A1)
  {
    Serial.print("Igual en los lados \n");
    delay(2000);
  }
  else
  {
    if(A0 == A2)
    {
      Serial.print("Igual en extremos \n");
      delay(2000);
    }

    else
    {
      if(A0 < A1 && arriba < 170)
      {
        arriba = arriba + 5;
        servoMotorArriba.write(arriba);
        Serial.print("Estabiizando en los lados \n");
        delay(2000);  
      }
      else
      {
        if(A0 > A1 && arriba >= 0)
        {
          arriba = arriba - 5;
          servoMotorArriba.write(arriba);
          Serial.print("Estabiizando en los lados \n");
          delay(2000);  
        }
        else
        {
          if(A0 < A2 && abajo < 170) 
          {
            abajo = abajo + 5;
            servoMotorAbajo.write(abajo);
            Serial.print("Estabiizando en los extremos \n");
            delay(2000);  
          }
          else
          {
            if(A0 > A2 && abajo >= 170) 
            {
              abajo = abajo - 5;
              servoMotorAbajo.write(abajo);
              Serial.print("Estabiizando en los extremos \n");
              delay(2000);  
            }
            else
            {
              Serial.print("Sin movimiento\n");
            }
          }
        }
      }
      
    }
  }

  //delay(2000);
}






   
