/*
 * Control Stepper 28BYJ-48_3_buttons_Angle
 * This is Arduino code to control 28BYj-48 wiht ULN2003 board using
  as many push button as you want.
  For each push button you can have sepearate:
  -Speed
  -Direction
  -Angle
  
 Watch Video for instruciton.
 you can add as many push button as you want and assign different angle, speed and direciton

This is video: STPB-5
 * Written by Ahmad Shamshiri for Robojax Robojax.com
 * on Jun 09, 2020 at in Ajax, Ontario, Canada
 * 
 * 
 Watch the video instruction for this sketch: https://youtu.be/4LOpXFkWzD4
 
Related videos:
Introduction to using 28BYJ-48 stepper motor motor: https://youtu.be/Sl2mzXfTwCs
Contorl speed of this motor using Potentiometer: https://youtu.be/lrEW8xlSnuY
Control 28BYJ-48 Stepper motor with hand gesture: https://youtu.be/KfAnUgaSDmI
STPB-1 Control 28BYJ-48 Stepper motor with 3 push button for CW, CCW and STOP: https://youtu.be/q-H7GbyX5ho
STPB-2 Control 28BYJ-48 Stepper motor with 2 push button keep pressed: https://youtu.be/y-F-jjTOYyQ
STPB-3 ONE revolution CW CCW: https://youtu.be/MEEKvjj7vbY
STPB-4 Any (one) Angle push button: https://youtu.be/P_O-0_aOXuA
STPB-5 Any Angle (multiple) push buttons:  https://youtu.be/4LOpXFkWzD4
ESP8266 NodeMCU D1 Mini over WiFi: https://youtu.be/CzvGR0WTllI
ESP32 CW CCW Over WiFi : https://youtu.be/n2oeT6RcU5Q
 
 
 * Code is available at http://robojax.com/learn/arduino

pinout button

pin--d3
pin--d4
pin--d5

*/


const int CW =1; // sentido horario
const int CCW =2; // sentido anti-horario
const int STOP =3;

int Pin1 = 10;//IN1 is connected to 8 
int Pin2 = 11;//IN2 is connected to 9  
int Pin3 = 12;//IN3 is connected to 10 
int Pin4 = 13;//IN4 is connected to 11
int switchSTOP =2;//define input pin for STOP push button
int stopType=1;//1=normal stop, 2=hold stop (consumes power)

int speedFactor =1;//1=fastest, 2=slower or 3 more slower

long angles[] = {360, 270, 7655};//angles of each push button
int pushButtons[] ={3, 4, 5};//digial pin for each push button
int directions[] ={CW, CCW, CW};//direction of eacch push button
int speedFactors[] = {1, 1, 3};//speed for each push button


int correction_CW = 150;//watch video for details
int correction_CCW = 150;//watch video for details


int poleStep = 0; 
long stepVale =0;
const int SPR=64*64;
long goToAngle=0;
int activeButton=0;
int pole1[] ={0,0,0,0, 0,1,1,1, 0};//pole1, 8 step values
int pole2[] ={0,0,0,1, 1,1,0,0, 0};//pole2, 8 step values
int pole3[] ={0,1,1,1, 0,0,0,0, 0};//pole3, 8 step values
int pole4[] ={1,1,0,0, 0,0,0,1, 0};//pole4, 8 step values





int count=0;
int  dirStatus = STOP;// stores direction status 3= stop (do not change)

void setup() 
{ 
  //Robojax.com Stepper Push button Any Angle STPB-5
  Serial.begin(9600);
  Serial.begin("Robojax Video for Stepper Motor STPB-2");  
 pinMode(Pin1, OUTPUT);//define pin for ULN2003 in1 
 pinMode(Pin2, OUTPUT);//define pin for ULN2003 in2   
 pinMode(Pin3, OUTPUT);//define pin for ULN2003 in3   
 pinMode(Pin4, OUTPUT);//define pin for ULN2003 in4   

 pinMode(switchSTOP,INPUT_PULLUP); 
 attachInterrupt(digitalPinToInterrupt(switchSTOP), stopMotor, FALLING );
 // see this https://www.arduino.cc/reference/en/language/variables/utilities/sizeof/
 for (byte i = 0; i < (sizeof(pushButtons) / sizeof(pushButtons[0])); i++) {
   pinMode(i,INPUT_PULLUP);
  }


 
} //setup
 void loop() 
{ 
    stepVale = (SPR * goToAngle)/360 ;
  //Robojax.com Stepper Push button Any Angle STPB-5

  //see this https://www.arduino.cc/reference/en/language/variables/utilities/sizeof/
 for (byte i = 0; i < (sizeof(angles) / sizeof(angles[0])); i++) {
    if(digitalRead(pushButtons[i]) == LOW) 
    {
      goToAngle =angles[i];
      dirStatus =directions[i];
      count =0;
      activeButton =i;
    }// if ends
 }//for loop ends
  
  
 if(dirStatus ==CCW){ 
  
   poleStep++; 
   count++;   
   if(count+correction_CCW <= stepVale)
   {
    driveStepper(poleStep);      
   }else{
      stopMotor();  
   }
  //full explannation at Arduino Course on Udemy.com see link above
 }else if(dirStatus ==CW){ 
   poleStep--; 
   count++;   
   if(count+correction_CW <=stepVale)
   {
    driveStepper(poleStep);      
   }else{
      stopMotor();  
   }   
 }else{
  stopMotor();   
 }
 if(poleStep>7){ 
   poleStep=0;
 } 
 if(poleStep<0){ 
   poleStep=7; 
 } 
  delay(speedFactors[activeButton]);
  
  //Robojax.com Stepper Push button Any Angle STPB-5

}// loop


/*
 * @brief moves motor to specific angle 
 * @param "angle" is integer representing the angle
 * @return does not return anything
 * 
 * www.Robojax.com code Ap1il 19 2020 at 01:22 in Ajax, Ontario, Canada
 */
void driveStepper(int c)
{
    //Robojax.com Stepper Push button Any Angle STPB-5
     digitalWrite(Pin1, pole1[c]);  
     digitalWrite(Pin2, pole2[c]); 
     digitalWrite(Pin3, pole3[c]); 
     digitalWrite(Pin4, pole4[c]);

}//driveStepper ends here

/*
 * @brief stops the motor immediately
 * @param none
 * @return does not return anything
 * 
 * www.Robojax.com code June 09, 2020 at 11:09 in Ajax, Ontario, Canada
 */
void stopMotor()
{
  //see this https://www.arduino.cc/reference/en/language/variables/utilities/sizeof/
 for (byte i = 0; i < (sizeof(angles) / sizeof(angles[0])); i++) {
    digitalWrite(pushButtons[i], HIGH); 

 }//for loop ends
 dirStatus = STOP;
 if( stopType ==2)
 {
  driveStepper(8);
 }
}//stopMotor()
