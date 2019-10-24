#include<SoftwareSerial.h>//header file of soft serial port
SoftwareSerial Serial1(2,3); //define the soft serial port name as Serial1, and set pin2 as RX and pin3 as TX.
/* For an arduino board with multiple serial ports, such as the DUE board, comment out the above two pieces of code and use the Serial1 serial port directly. */
int dist;//Range measured by Radar
int strength;// The strength of the radar signal, the strength below 100 is not credible
int IH=230;//radar installation height (to be set), it needs to be corrected for the actual black object
int H;// Height 
int h=0;// Last height 
int check;// Check value storage
int i;
int Number=0;// 
int Height=0;//Maximum height
int up=50;//Height limit (need to be set), the height of the object is valid above this value
int down=40;//Lower limit (to be set) to prevent data fluctuation and wrong data when the height is at the exact height limit
int uart[9];// Store radar measured data
const int HEADER=0x59;// 
void setup() 
{
  Serial.begin(115200);// Set the baud rate of the arduino and computer connected serial port
  Serial1.begin(115200);// Set the baud rate of the serial port connected to the radar and arduino
}
void loop() 
{
  if (Serial1.available())//Check if the serial port has data input
  {
    if(Serial1.read()==HEADER)
    {
      uart[0]=HEADER;
      if(Serial1.read()==HEADER)
      {
        uart[1]=HEADER;
        for(i=2;i<9;i++)// Storing data into an array
        {
          uart[i]=Serial1.read();
        } 
        check=uart[0]+uart[1]+uart[2]+uart[3]+uart[4]+uart[5]+uart[6]+uart[7];
        if(uart[8]==(check&0xff))// Verify the received data according to the protocol
        {
          dist=uart[2]+uart[3]*256;// Calculate the distance
          strength=uart[4]+uart[5]*256;// Calculated signal strength 
          H=IH-dist;// Calculating height
          /* The number of measurements */
          /* Principle: increase the number of people by 1 when the data exceeds the height limit from the lower limit*/
          if(H>=up&h<down)// When people enter the measurement area, add one to the number
          {
            Number=Number+1;
            h=H; 
            Height=H;
            Serial.print("Number = ");
            Serial.print(Number);// 
            Serial.print('\t');
          }
           if(H>=up&h>=down)// When the person is in the measurement area, the maximum value of the period is obtained by comparison
          {
            if(Height<H)
            {
              Height=H;
            }
          }
          if(H<down&h>=up)// When the person walks out of the measurement area, the maximum height is output and the maximum value is reset to zero.
          {
            Serial.print("Height = ");
            Serial.print(Height);// 
            Serial.print('\n');
            h=H;
            Height=0;
          }
//          Serial.print("H = ");
//          Serial.print(H);// 
//          Serial.print('\t');
//          Serial.print("dist = ");
//          Serial.print(dist);// 
//          Serial.print('\t'); 
//          Serial.print("strength = ");
//          Serial.print(strength);// 
//          Serial.print('\n');
        }
      }
    }
  }
}
