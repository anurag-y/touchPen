#include <LedControl.h>
#define NUM_DEVICES 4
#define threshold 950
int dataInPin = 11, clkPin = 13, loadPin = 3;
const int ldrPin = A5; 
LedControl lc = LedControl(dataInPin, clkPin, loadPin, NUM_DEVICES);

int x_vals[8]={-1,-1,-1,-1,-1,-1,-1,-1}, y_vals[8]={-1,-1,-1,-1,-1,-1,-1,-1}, n_vals[4]={-1,-1,-1,-1};
bool led_pos[4][8][8];
void dispAll()
  {
    for(int n=0;n<4;n++)
    {
      for(int i=0;i<8;i++)
      {
        for(int j=0; j<8; j++)
        {
          if(led_pos[n][i][j])
          {
            lc.setLed(n,i,j,true);
          }

        }
      }
    }
    delay(3000);
  }


int verticalScan()
{
  for(int i=0; i<NUM_DEVICES; i++)
  {
    for(int y=7;y>=0;y--)
    {
          for(int x=0; x<8; x++)
            lc.setLed(i,x,y,true);
          delay(5);
          int ldrValue = analogRead(ldrPin);  
          // Serial.println(ldrValue);
          if(ldrValue<threshold)
          {
            digitalWrite(7,HIGH);
            lc.clearDisplay(i);
            delay(100);
            digitalWrite(7,LOW);
            return i*10+y;
          }
          else{
            digitalWrite(7,LOW);
          }
          
          lc.clearDisplay(i);
    }
  }
  return -1;
}

int horizontalScan()
  {
    for(int y=7;y>=0;y--)
      {
            for(int i=0;i<4;i++)
            {
              for(int x=0; x<8; x++)
              lc.setLed(i,y,x,true);
              delay(5);
            }
            int ldrValue = analogRead(ldrPin);  
            // Serial.println(ldrValue);
            if(ldrValue<threshold)
            {
              digitalWrite(7,HIGH);
              delay(100);
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
  for(int i=0;i<4;i++)
  {
    for(int j=0;j<8;j++)
    {
      for(int k=0;k<8;k++)
       led_pos[i][j][k]=false;
    }
  }
  Serial.begin(9600);
 }

void loop() {
  int y,n,x;
  y=verticalScan();
  n=y/10;
  y=y%10;
  x=horizontalScan();

  if(x!=-1 && y!=-1)
  led_pos[n][x][y]=true;
  dispAll();

  // lc.setLed(n,x,y,true);
  // delay(2000);
  // lc.setLed(n,x,y,false);
  // delay(100);

  Serial.print("n: ");
  Serial.println(n);
  Serial.print("x: ");
  Serial.println(x);
  Serial.print("y: ");
  Serial.println(y);

  
  delay(100);


}
