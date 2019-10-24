#include "voice.h"//include the self-defined head file, voice and oled.
#include "oled.h"
#include<SoftwareSerial.h>//incorporate the SoftwareSerial head file
SoftwareSerial Serial2(4,5); //define a SoftwareSerial named Serial2,regarding pin4 as RX, pin5 as TX.
/*If there are multiple serial port more than one, such as DUE board，you could use the serial port directly.*/
/*define the basic data of TFmini Plus*/
int check;//store the checksum of TFmini Plus
int uart[9];//store the standard data of TFmini Plus
int k;
const int HEADER=0x59;//data packet's frame head
/*define some essential parameters of Auto-measuring Instrument for Body Flexion*/
int D;//the distance measured by the TFmini Plus
int d=0;//the last distance
int result=0;//the result of calculation
const int zero=34;//the zero position calibrated after installation and before test.
int VAR[23]={0};
int var;
int num=0;
const int start=50;//the start position calibrated after installation and before test.
int CHA[15]={0};
int cha=0;
int count=0;
boolean init_stat=false;//define the initiating status of position.

void setup() 
{
  Serial.begin(115200);//configure the baud rate as 115200 bps between Arduino UNO and PC.
  Serial2.begin(115200);//configure the baud rate as 115200 bps between Arduino UNO and TFmini Plus.
  oled_begin();//initialization of OLED module.
  voice_begin();//initializing the voice module.
  voice_setvolume(18);//set the volume of the voice module as an integer between 0 and 20.
}
void loop() 
{
  Serial2.listen();
  if (Serial2.available())//monitor whether there is data input from the lIDAR.
  {
    if(Serial2.read()==HEADER)//check if the first data is the data packet's frame head 0x59 defined in the cummunication protocol. 
    {
      uart[0]=HEADER;
      if(Serial2.read()==HEADER)//check if the second data is the data packet's frame head 0x59 defined in the cummunication protocol.
      {
        uart[1]=HEADER;
        for(k=2;k<9;k++)//store the remaining data into the uart.
        {
          uart[k]=Serial2.read();
        } 
        check=uart[0]+uart[1]+uart[2]+uart[3]+uart[4]+uart[5]+uart[6]+uart[7];
        if(uart[8]==(check&0xff))//verify the checksum according to the cummunication protocol.
        {
          D=uart[2]+uart[3]*256;//compute the actual distance
          if(!init_stat && D==start)//judge the position's initialized status and the relationship of distance measured by the TFmini Plus and start.
          {
            cha=D-start;
            for(k=15;k>=1;k--)//only getting fifteen datas steady and uninterrupted can satisfy the need in case of data fluctuation.
            {
              CHA[k]=CHA[k-1];
            }
            CHA[0] = cha;
            for(k=0;k<15;k++)
            {
              if(CHA[k]==0)
              {
                count++;
              }        
            } 
            oled_measuring();
            if(count>=15)
            {
              voice_ready();
              init_stat=true;//set tht status as true after completing the position initialization.  
            }
          } 
          if(D!=0 && D!=start && init_stat)//judge the position's initialized status and the relationship of distance measured by the TFmini Plus and start.
          {
            var=abs(D-d);
            for(k=23;k>=1;k--)//only getting twenty-three datas steady and uninterrupted can satisfy the need in case of data fluctuation.
            {    
              VAR[k]=VAR[k-1];
            }
            VAR[0] = var;
            for(k=0;k<23;k++)
            {
              if(VAR[k]==0)
              {
                num++;      
              } 
            } 
            if(num>=23)
            {
              result=zero-D;
              oled_result(result);
              voice_num(result);
              Serial2.listen(); 
              init_stat=false;//set tht status as false after completing the test and waiting for the next initialization.
            }
            d=D;
            num=0;
          }
        }
      }
    }
  }
}
