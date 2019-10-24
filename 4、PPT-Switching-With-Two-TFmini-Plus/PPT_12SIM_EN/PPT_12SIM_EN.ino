#include <Keyboard.h>
/****************************************************************
define pin27,29 as control and pin23,25 as display
*****************************************************************/
#define ON 23
#define OFF 25
#define LED_ON 27
#define LED_OFF 29
char left  = KEY_LEFT_ARROW; 
char right  = KEY_RIGHT_ARROW;
const int HEADER=0x59;// frame header of data package
/****************************************************************
Define module function initial state parameters
*****************************************************************/
bool receiveok1=false;
bool receiveok2=false;
bool status_complete1=false;
bool status_complete2=true;
/****************************************************************
The variable DELAY can control the delay time of the module to filter out the misoperation caused by walking.
*****************************************************************/
int DELAY=180;
int distance1=0;
int distance2=0;
int DISTANCE1=1200;
int DISTANCE2=1200;
int threshold=0;
unsigned long tim[2]={0};
int period=0;
/****************************************************************
Declarative function, LiDAR data acquisition function and acquisition environment distance threshold function
*****************************************************************/
int TFminione(void);
int TFminitwo(void);
int lidar_average(void);





/****************************************************************
Pin function definition, initialization;
Serial port initialization;
Collect the surrounding environment and determine the module working threshold;
*****************************************************************/
void setup() 
{
  pinMode(ON,INPUT);
  pinMode(OFF,INPUT);
  pinMode(LED_ON,OUTPUT);
  pinMode(LED_OFF,OUTPUT);
  digitalWrite(ON,HIGH);
  digitalWrite(OFF,HIGH);
  digitalWrite(LED_ON,LOW);
  digitalWrite(LED_OFF,LOW);  
  Serial1.begin(115200);// set bit rate of serial port connecting LiDAR1 with Arduino
  Serial2.begin(115200);// set bit rate of serial port connecting LiDAR2 with Arduino
  Serial3.begin(115200);// set bit rate of serial port connecting Arduino with computer
  int threshold1=lidar_average();
  threshold=threshold1-100;
  Serial3.print("threshold=");
  Serial3.println(threshold);
}
/****************************************************************
First, determine the status of the function switch;
Then, determine the LiDAR ranging state;
If the judgment condition is satisfied, the corresponding operation is performed;
*****************************************************************/
void loop() 
{
       if(digitalRead(ON)==LOW)// Control switch open
       {                          
           digitalWrite(ON,HIGH);
           digitalWrite(LED_OFF,LOW);
           digitalWrite(LED_ON,HIGH);
           Keyboard.begin();
           receiveok1=false;
           receiveok2=false; 
           distance1 =  TFminione();
           distance2 =  TFminitwo(); 
           if(receiveok1 & receiveok2)
           {           
              if(DISTANCE1>threshold  & distance1<=threshold  & distance2>threshold)
              { 
                   tim[0]=millis();
                   DISTANCE1=distance1;
                   DISTANCE2=distance2;
                   while(true)
                   {
                      receiveok1=false;
                      receiveok2=false;
                      distance1 =  TFminione();
                      distance2 =  TFminitwo(); 
                      if(receiveok1 & receiveok2)
                      {
                          tim[1]=millis();
                          period=tim[1]-tim[0];
                          if(DISTANCE2>threshold  & distance2<=threshold )
                          {
                              DISTANCE1=distance1;
                              DISTANCE2=distance2;
                              while(true)
                              {
                                  receiveok1=false;
                                  receiveok2=false;
                                  distance1 =  TFminione();
                                  distance2 =  TFminitwo(); 
                                  if(receiveok1 & receiveok2)
                                  { 
                                      tim[1]=millis();
                                      period=tim[1]-tim[0];
                                      if(distance2>threshold & distance1>threshold )
                                      {
                                         tim[1]=millis();
                                         period=tim[1]-tim[0];
                                         if(period<DELAY)
                                         {
                                             Keyboard.write(right);
                                             status_complete1=true;  
                                             break; 
                                         }
                                         else
                                         {
                                            status_complete1=true;
                                            break;           
                                         }
                                      }
                                      else if(period>DELAY)
                                      {
                                         status_complete1=true;
                                         break;
                                      }
                                      else
                                      {
                                          DISTANCE1=distance1;
                                          DISTANCE2=distance2;
                                      }        
                                  }
                              }                                        
                          }
                          else if(status_complete1)
                          {
                              status_complete1=false;
                              break;   
                          }
                          else if(period>DELAY)
                          {
                              break;
                          }
                          else
                          {
                              DISTANCE1=distance1;
                              DISTANCE2=distance2;
                          }
                      }    
                   }
              }
              else if(DISTANCE2>threshold  & distance2<=threshold  & distance1>threshold)
              { 
                   tim[0]=millis();
                   DISTANCE1=distance1;
                   DISTANCE2=distance2;
                   while(true)
                   {
                      receiveok1=false;
                      receiveok2=false;
                      distance1 =  TFminione();
                      distance2 =  TFminitwo(); 
                      if(receiveok1 & receiveok2)
                      {
                          tim[1]=millis();
                          period=tim[1]-tim[0];
                          if(DISTANCE1>threshold  & distance1<=threshold )
                          {
                              DISTANCE1=distance1;
                              DISTANCE2=distance2;
                              while(true)
                              {
                                  receiveok1=false;
                                  receiveok2=false;
                                  distance1 =  TFminione();
                                  distance2 =  TFminitwo(); 
                                  if(receiveok1 & receiveok2)
                                  { 
                                      tim[1]=millis();
                                      period=tim[1]-tim[0];
                                      if(distance1>threshold & distance2>threshold )
                                      {
                                         tim[1]=millis();
                                         period=tim[1]-tim[0];
                                         if(period<DELAY)
                                         {
                                             Keyboard.write(left);
                                             status_complete2=true;  
                                             break; 
                                         }
                                         else
                                         {
                                            status_complete2=true;
                                            break;           
                                         }
                                      }
                                      else if(period>DELAY)
                                      {
                                         status_complete2=true;
                                         break;
                                      }
                                      else
                                      {
                                          DISTANCE1=distance1;
                                          DISTANCE2=distance2;
                                      }        
                                  }
                              }                                        
                          }
                          else if(status_complete2)
                          {
                              status_complete2=false;
                              break;   
                          }
                          else if(period>DELAY)
                          {
                              break;
                          }
                          else
                          {
                              DISTANCE1=distance1;
                              DISTANCE2=distance2;
                          }
                      }    
                   }
              }
              else
              {
                 DISTANCE1=distance1;
                 DISTANCE2=distance2; 
              }
              Keyboard.end();
           }                 
       }
 
       else if(digitalRead(OFF)==LOW)
       {              
            digitalWrite(OFF,HIGH);
            digitalWrite(LED_OFF,HIGH);
            digitalWrite(LED_ON,LOW);
       }
       else
       {
          delay(1);
       }
}



/****************************************************************
LiDAR 1 acquisition environment distance function
*****************************************************************/
int TFminione(void) 
{
  int dist=0;// actual distance measurements of LiDAR
  int check;// save check value
  int uart[9]={0};// save data measured by LiDAR
  int i=0;
  if (Serial1.available())//check if serial port has data input
  {
    if(Serial1.read()==HEADER)//assess data package frame header 0x59
    {
      uart[0]=HEADER;
      if(Serial1.read()==HEADER)// assess data package frame header 0x59
      {
        uart[1]=HEADER;
        for(i=2;i<9;i++)// save data in array
        {
          uart[i]=Serial1.read();
        } 
        check=uart[0]+uart[1]+uart[2]+uart[3]+uart[4]+uart[5]+uart[6]+uart[7];
        if(uart[8]==(check&0xff))//verify the received data as per protocol
        {
          dist=uart[2]+uart[3]*256;//calculate distance value
          receiveok1=true;
          return(dist);
        }
      }
    }
  }
  else
  {
      delay(1);  
  }
}
/****************************************************************
LiDAR 2 acquisition environment distance function
*****************************************************************/
int TFminitwo(void) 
{
  int dist=0;//actual distance measurements of LiDAR
  int check;// save check value
  int uart[9]={0};//save data measured by LiDAR
  int i=0;
  if (Serial2.available())//check if serial port has data input
  {
    if(Serial2.read()==HEADER)//assess data package frame header 0x59
    {
      uart[0]=HEADER;
      if(Serial2.read()==HEADER)//assess data package frame header 0x59
      {
        uart[1]=HEADER;
        for(i=2;i<9;i++)//save data in array
        {
          uart[i]=Serial2.read();
        } 
        check=uart[0]+uart[1]+uart[2]+uart[3]+uart[4]+uart[5]+uart[6]+uart[7];
        if(uart[8]==(check&0xff))// verify the received data as per protocol
        {
          dist=uart[2]+uart[3]*256;//calculate distance value
          receiveok2=true;
          return(dist);     
        }
      }
    }
  }
  else
  {
      delay(1);  
  }
}
int lidar_average(void)
{
  int i=0;
  int sum=0;
  int average=0;
  int temp[100]={0};
  while(true)
  {
    distance1=TFminione();
    if(receiveok1)
    {
        temp[i]=distance1;
        Serial3.println(distance1);
        i++;
        if(i>=100)
        {
          for(i=0;i<100;i++)
          {
            sum+=temp[i];
          }
          average=sum/100;
          Serial3.print("average=");
          Serial3.print(average);
          Serial3.print('\t');
          i=0;
          sum=0;
          return(average);
          delay(1);
          break;
        }
    }
    receiveok1=false;
  }
}
