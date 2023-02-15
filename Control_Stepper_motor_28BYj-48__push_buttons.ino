
 /*
  * Control Stepper motor 28BYj-48 with Arduino and 3 push buttons
  * https://robojax.com/learn/arduino/?vid=robojax_stepper_28BYJ-48_STPB-2
  * 
 * This is Arduino code to control 28BYj-48 wiht ULN2003 board using
 2 push buttons.   CW and CCW must be kept pressed to make the motor move
 
 * Written by Ahmad Shamshiri for Robojax Robojax.com
 * on April 18, 2020 at 19:59 in Ajax, Ontario, Canada
 * 
 Watch the video instruction for this sketch:https://youtu.be/y-F-jjTOYyQ

 
You can get the wiring diagram and full explanition from my Arduino Course at Udemy.com
Learn Arduino step by step with all library, codes, wiring diagram all in one place
visit my course now http://robojax.com/L/?id=62

If you found this tutorial helpful, please support me so I can continue creating 
content like this. You can support me on Patreon http://robojax.com/L/?id=63
or make donation using PayPal http://robojax.com/L/?id=64

* 
 * Code is available at http://robojax.com/learn/arduino

 * This code is "AS IS" without warranty or liability. Free to be used as long as you keep this note intact.* 
 * This code has been download from Robojax.com
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>. 

*/

int Pin1 = 10;//IN1 is connected to 10 
int Pin2 = 11;//IN2 is connected to 11  
int Pin3 = 12;//IN3 is connected to 12  
int Pin4 = 13;//IN4 is connected to 13 
int switchCW  =2;//define input pin for CW push button
int switchCCW =3;//define input pin for CCW push button

 
int pole1[] ={0,0,0,0, 0,1,1,1, 0};//pole1, 8 step values
int pole2[] ={0,0,0,1, 1,1,0,0, 0};//pole2, 8 step values
int pole3[] ={0,1,1,1, 0,0,0,0, 0};//pole3, 8 step values
int pole4[] ={1,1,0,0, 0,0,0,1, 0};//pole4, 8 step values


int poleStep = 0; 
int  dirStatus = 3;// stores direction status 3= stop (do not change)

void setup() 
{ 
  //Robojax Stepper Motor Code STPB-2
 pinMode(Pin1, OUTPUT);//define pin for ULN2003 in1 
 pinMode(Pin2, OUTPUT);//define pin for ULN2003 in2   
 pinMode(Pin3, OUTPUT);//define pin for ULN2003 in3   
 pinMode(Pin4, OUTPUT);//define pin for ULN2003 in4   

 pinMode(switchCW,INPUT_PULLUP);
 pinMode(switchCCW,INPUT_PULLUP);  
 
} 
 void loop() 
{ 
  //Robojax Stepper Motor Code STPB-2
  if(digitalRead(switchCCW) == LOW) 
  {
    dirStatus =1;
  }else if(digitalRead(switchCW) == LOW)
  {
   dirStatus  = 2;  
  }else
  {
    dirStatus =3; 
  }
 if(dirStatus ==1){ 
   poleStep++; 
    driveStepper(poleStep);    
 }else if(dirStatus ==2){ 
   poleStep--; 
    driveStepper(poleStep);    
 }else{
  driveStepper(8);   
 }
 if(poleStep>7){ 
   poleStep=0; 
 } 
 if(poleStep<0){ 
   poleStep=7; 
 } 
 delay(1); 
//Robojax Stepper Motor Code STPB-2
}// loop



/*
 * @brief sends signal to the motor
 * @param "c" is integer representing the pol of motor
 * @return does not return anything
 * 
 * www.Robojax.com code June 2019
 */
void driveStepper(int c)
{
  //Robojax Stepper Motor Code STPB-2
     digitalWrite(Pin1, pole1[c]);  
     digitalWrite(Pin2, pole2[c]); 
     digitalWrite(Pin3, pole3[c]); 
     digitalWrite(Pin4, pole4[c]);   
}//driveStepper end here
