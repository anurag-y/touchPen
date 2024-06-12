#include <LedControl.h>
#define NUM_DEVICES 4
#define threshold 800
int dataInPin = 11, clkPin = 13, loadPin = 3;
const int ldrPin = A5; 
LedControl lc = LedControl(dataInPin, clkPin, loadPin, NUM_DEVICES);

bool led_pos[8][8];
void dispAll()
  {
    for(int i=0;i<8;i++)
      {
        for(int j=0; j<8; j++)
        {
          if(led_pos[i][j])
           lc.setLed(1,i,j,true);

        }
      }
    delay(500);
  }


int verticalScan()
{
  for(int y=7;y>=0;y--)
    {
          for(int x=0; x<8; x++)
            lc.setLed(1,x,y,true);
          delay(5);
          int ldrValue = analogRead(ldrPin);  
          // Serial.println(ldrValue);
          if(ldrValue<threshold)
          {
            digitalWrite(7,HIGH);
            lc.clearDisplay(1);
            delay(30);
            digitalWrite(7,LOW);
            return y;
          }
          else{
            digitalWrite(7,LOW);
          }
          
          lc.clearDisplay(1);
    }
  return -1;
}

int horizontalScan()
  {
    for(int y=7;y>=0;y--)
      {
            for(int x=0; x<8; x++)
              lc.setLed(1,y,x,true);
              delay(5);
            int ldrValue = analogRead(ldrPin);  
            // Serial.println(ldrValue);
            if(ldrValue<threshold)
            {
              digitalWrite(7,HIGH);
              delay(30);
              digitalWrite(7,LOW);
              lc.clearDisplay(0);
              lc.clearDisplay(1);
              lc.clearDisplay(2);
              lc.clearDisplay(3);
              return y;
            }
            else{
              digitalWrite(7,LOW);
            }
            lc.clearDisplay(0);
            lc.clearDisplay(1);
            lc.clearDisplay(2);
            lc.clearDisplay(3);
      }
      return -1;
  }

void setup() {
  pinMode(7, OUTPUT);
  for (int y = 0; y < NUM_DEVICES; y++) {// Initialize the MAX7219 chips and clear the screen
    lc.shutdown(y, false);
    lc.setIntensity(y, 8);
    lc.clearDisplay(y);
  }
  for(int i=0;i<8;i++)
  {
    for(int j=0;j<8;j++)
    {
       led_pos[i][j]=false;
    }
  }
  Serial.begin(9600);
 }

void loop() {
  int y,x;
  y=verticalScan();
  x=horizontalScan();

  if(x!=-1 && y!=-1)
  led_pos[x][y]=true;
  dispAll();

  // lc.setLed(n,x,y,true);
  // delay(2000);
  // lc.setLed(n,x,y,false);
  // delay(100);

  // Serial.print("x: ");
  // Serial.println(x);
  // Serial.print("y: ");
  // Serial.println(y);


}
