/*#include <Mouse.h>
#include <TimerOne.h>



#define X_AXIS_PIN A0
#define Y_AXIS_PIN A1
#define BUTTON_PIN 6
#define SENSOR_PIN 3
#define PULS_ARC 8

#define TIMER_OVERRUN_USEC 100000
#define AXIS_SENSITIVITY 100

int xAxisSensitivity = AXIS_SENSITIVITY;

int A = 2;
int B = 4;
int ANTERIOR = 50;
volatile int POSICION = 50;
int vertZero, horzZero;
int vertValue, horzValue;
volatile int clickLeft = 0;
bool canClick = true;
unsigned long lastClickTime = 0;
int buttonPressCount = 0;
unsigned long lastButtonPressTime = 0;

void timerIrq()
{
  clickLeft = 0;
  Timer1.stop();
}

void sensorIrq()
{
  TCNT1 = 1;
  if (!clickLeft && canClick)
  {
    Timer1.start();
    clickLeft = 1;
    Mouse.press(MOUSE_LEFT);
    delay(50);
    Mouse.release(MOUSE_LEFT);
    canClick = false;
    lastClickTime = millis();
  }
}

void setup()
{
  pinMode(A, INPUT);
  pinMode(B, INPUT);
  pinMode(PULS_ARC, INPUT_PULLUP);
  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(A), encoder, LOW);

  pinMode(X_AXIS_PIN, INPUT);
  pinMode(Y_AXIS_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(SENSOR_PIN, INPUT);
  digitalWrite(BUTTON_PIN, HIGH);

  Timer1.initialize(TIMER_OVERRUN_USEC);
  Timer1.attachInterrupt(timerIrq);
  attachInterrupt(0, sensorIrq, RISING);

  delay(1000);
  vertZero = analogRead(Y_AXIS_PIN);
  horzZero = analogRead(X_AXIS_PIN);
}

void loop()
{
  if (POSICION != ANTERIOR)
  {
    Serial.println(POSICION);
    ANTERIOR = POSICION;
  }

  static int mouseClickFlagLeft = 0;

  vertValue = analogRead(Y_AXIS_PIN) - vertZero;
  horzValue = analogRead(X_AXIS_PIN) - horzZero;

  int cursorX = -horzValue / xAxisSensitivity;
  int cursorY = -vertValue / AXIS_SENSITIVITY;

  Mouse.move(cursorX, cursorY, 0);

  if (!canClick && (millis() - lastClickTime >= 1000))
  {
    canClick = true;
  }

  if (digitalRead(PULS_ARC) == LOW)
  {
    Mouse.press(MOUSE_RIGHT);
    delay(500);
    Mouse.release(MOUSE_RIGHT);
  }

  // Verificar si el botón está presionado
  if (digitalRead(BUTTON_PIN) == LOW)
  {
    unsigned long currentMillis = millis();
    if (currentMillis - lastButtonPressTime > 500)
    {
      // Ha pasado suficiente tiempo desde la última vez que se presionó el botón
      buttonPressCount++;

      if (buttonPressCount == 1)
      {
        // Cambiar la sensibilidad a 250
        xAxisSensitivity = 25000000;
      }
      else if (buttonPressCount == 2)
      {
        // Cambiar la sensibilidad a 50
        xAxisSensitivity = 5;
      }
      else if (buttonPressCount == 3)
      {
        // Cambiar la sensibilidad a 100
        xAxisSensitivity = 1000;
        // Reiniciar el contador
        buttonPressCount = 0;
      }

      lastButtonPressTime = currentMillis;
    }
  }

  xAxisSensitivity = AXIS_SENSITIVITY;
}

void encoder()
{
  static unsigned long ultimaInterrupcion = 0;
  unsigned long tiempoInterrupcion = millis();

  if (tiempoInterrupcion - ultimaInterrupcion > 5)
  {
    if (digitalRead(B) == HIGH)
    {
      char xdir = 0;
      char ydir = 0;
      char wheel = 1;

      Mouse.move(xdir, ydir, wheel);
    }
    else
    {
      char xdir = 0;
      char ydir = 0;
      char wheel = -1;
      Mouse.move(xdir, ydir, wheel);
    }

    ultimaInterrupcion = tiempoInterrupcion;
  }
}*/
#include <Mouse.h>
#include <TimerOne.h>

#define X_AXIS_PIN A0
#define Y_AXIS_PIN A1
#define BUTTON_PIN 6
#define SENSOR_PIN 3
#define PULS_ARC 8

#define TIMER_OVERRUN_USEC 100000
#define AXIS_SENSITIVITY 100

int xAxisSensitivity = AXIS_SENSITIVITY;
int yAxisSensitivity = AXIS_SENSITIVITY;  // Agregamos la sensibilidad del eje Y

int A = 2;
int B = 4;
int ANTERIOR = 50;
volatile int POSICION = 50;
int vertZero, horzZero;
int vertValue, horzValue;
volatile int clickLeft = 0;
bool canClick = true;
unsigned long lastClickTime = 0;
int buttonPressCount = 0;
unsigned long lastButtonPressTime = 0;

void timerIrq()
{
  clickLeft = 0;
  Timer1.stop();
}

void sensorIrq()
{
  TCNT1 = 1;
  if (!clickLeft && canClick)
  {
    Timer1.start();
    clickLeft = 1;
    Mouse.press(MOUSE_LEFT);
    delay(50);
    Mouse.release(MOUSE_LEFT);
    canClick = false;
    lastClickTime = millis();
  }
}

void setup()
{
  pinMode(A, INPUT);
  pinMode(B, INPUT);
  pinMode(PULS_ARC, INPUT_PULLUP);
  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(A), encoder, LOW);

  pinMode(X_AXIS_PIN, INPUT);
  pinMode(Y_AXIS_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(SENSOR_PIN, INPUT);
  digitalWrite(BUTTON_PIN, HIGH);

  Timer1.initialize(TIMER_OVERRUN_USEC);
  Timer1.attachInterrupt(timerIrq);
  attachInterrupt(0, sensorIrq, RISING);

  delay(1000);
  vertZero = analogRead(Y_AXIS_PIN);
  horzZero = analogRead(X_AXIS_PIN);
}

void loop()
{
  if (POSICION != ANTERIOR)
  {
    Serial.println(POSICION);
    ANTERIOR = POSICION;
  }

  static int mouseClickFlagLeft = 0;

  vertValue = analogRead(Y_AXIS_PIN) - vertZero;
  horzValue = analogRead(X_AXIS_PIN) - horzZero;

  int cursorX = -horzValue / xAxisSensitivity;
  int cursorY = -vertValue / yAxisSensitivity;  // Usamos la sensibilidad del eje Y

  Mouse.move(cursorX, cursorY, 0);

  if (!canClick && (millis() - lastClickTime >= 1000))
  {
    canClick = true;
  }

  if (digitalRead(PULS_ARC) == LOW)
  {
    Mouse.press(MOUSE_RIGHT);
    delay(500);
    Mouse.release(MOUSE_RIGHT);
  }

  // Verificar si el botón está presionado
  if (digitalRead(BUTTON_PIN) == LOW)
  {
    unsigned long currentMillis = millis();
    if (currentMillis - lastButtonPressTime > 500)
    {
      // Ha pasado suficiente tiempo desde la última vez que se presionó el botón
      buttonPressCount++;

      if (buttonPressCount == 1)
      {
        // Cambiar la sensibilidad de ambos ejes a 250
        xAxisSensitivity = 250;
        yAxisSensitivity = 250;
      }
      else if (buttonPressCount == 2)
      {
        // Cambiar la sensibilidad de ambos ejes a 50
        xAxisSensitivity = 50;
        yAxisSensitivity = 50;
      }
      else if (buttonPressCount == 3)
      {
        // Cambiar la sensibilidad de ambos ejes a 100
        xAxisSensitivity = 100;
        yAxisSensitivity = 100;
        // Reiniciar el contador
        buttonPressCount = 0;
      }

      lastButtonPressTime = currentMillis;
    }
  }
}

void encoder()
{
  static unsigned long ultimaInterrupcion = 0;
  unsigned long tiempoInterrupcion = millis();

  if (tiempoInterrupcion - ultimaInterrupcion > 5)
  {
    if (digitalRead(B) == HIGH)
    {
      char xdir = 0;
      char ydir = 0;
      char wheel = 1;

      Mouse.move(xdir, ydir, wheel);
    }
    else
    {
      char xdir = 0;
      char ydir = 0;
      char wheel = -1;

      Mouse.move(xdir, ydir, wheel);
    }

    ultimaInterrupcion = tiempoInterrupcion;
  }
}
