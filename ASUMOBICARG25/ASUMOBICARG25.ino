#include <NewPing.h>
#include <Servo.h>

// LINE FOLLOWER
const int R_pin = 13;
const int L_pin = 11;
const int M_pin = 12;

const int line = 0;
const int no_line = 1;

// L298N MOTOR DRIVE
const int right_motor_forward = 6;
const int right_motor_backward = 7;

const int left_motor_forward = 8;
const int left_motor_backward = 9;

const int enable_right_motor = 5;
const int enable_left_motor = 10;

int car_speed = 150;

// ULTRASONIC SENSOR
const int trigger = 2;
const int echo = 4;
const int max_distance = 50;
int distance;
NewPing ultrasonic(trigger, echo);

// SERVO MOTOR
Servo bracket;
int initial_pos = 100;

// BLUETOOTH MODULE
char input = 'S';

// RC CAR
const int horn = 30;
const int lights_left = 22;
const int lights_right = 26;
const int lights_forward = 24;

void setup() {
  Serial.begin(9600);
  Serial3.begin(9600);

  pinMode(right_motor_forward, OUTPUT);
  pinMode(right_motor_backward, OUTPUT);
  pinMode(left_motor_forward, OUTPUT);
  pinMode(left_motor_backward, OUTPUT);
  pinMode(enable_right_motor, OUTPUT);
  pinMode(enable_left_motor, OUTPUT);

  bracket.attach(3);
  bracket.write(initial_pos);
  
  pinMode(horn, OUTPUT);
  pinMode(lights_forward, OUTPUT);
  pinMode(lights_right, OUTPUT);
  pinMode(lights_left, OUTPUT);

  pinMode(R_pin, INPUT);
  pinMode(M_pin, INPUT);
  pinMode(L_pin, INPUT);
}

void stop_car(){
  digitalWrite(lights_forward, LOW);
  digitalWrite(lights_right, LOW);
  digitalWrite(lights_left, LOW);

  digitalWrite(right_motor_forward, LOW);
  digitalWrite(right_motor_backward, LOW);
 
  digitalWrite(left_motor_forward, LOW);
  digitalWrite(left_motor_backward, LOW);
  }

void forward(int car_speed){
  digitalWrite(lights_forward, HIGH);

  analogWrite(enable_right_motor, car_speed);
  digitalWrite(right_motor_forward, HIGH);
  digitalWrite(right_motor_backward, LOW);

  analogWrite(enable_left_motor, car_speed);
  digitalWrite(left_motor_forward, HIGH);
  digitalWrite(left_motor_backward, LOW);
  }
  
void backward(int car_speed){
  analogWrite(enable_right_motor, car_speed);
  digitalWrite(right_motor_forward, LOW);
  digitalWrite(right_motor_backward, HIGH);

  analogWrite(enable_left_motor, car_speed);
  digitalWrite(left_motor_forward, LOW);
  digitalWrite(left_motor_backward, HIGH);
  }
  
void right(int car_speed){
  digitalWrite(lights_right, HIGH);
  
  analogWrite(enable_right_motor, car_speed);
  digitalWrite(right_motor_forward, HIGH);
  digitalWrite(right_motor_backward, LOW);
 
  analogWrite(enable_left_motor, car_speed);
  digitalWrite(left_motor_forward, LOW);
  digitalWrite(left_motor_backward, HIGH);
  }

void right_p2(int car_speed){
  digitalWrite(lights_right, HIGH);
  
  analogWrite(enable_right_motor, car_speed);
  digitalWrite(right_motor_forward, HIGH);
  digitalWrite(right_motor_backward, LOW);
 
  analogWrite(enable_left_motor, car_speed);
  digitalWrite(left_motor_forward, LOW);
  digitalWrite(left_motor_backward, LOW);
  }

void left(int car_speed){
  digitalWrite(lights_left, HIGH);

  analogWrite(enable_right_motor, car_speed);
  digitalWrite(right_motor_forward, LOW);
  digitalWrite(right_motor_backward, HIGH);
 
  analogWrite(enable_left_motor, car_speed);
  digitalWrite(left_motor_forward, HIGH);
  digitalWrite(left_motor_backward, LOW);
  }

void horn_fn(char state){
  if(state == '1'){
    digitalWrite(horn, HIGH);
  }
  else {
    digitalWrite(horn, LOW);
  }
}
/*
void lights_fn(char state){
  if(state == '1'){
    digitalWrite(lights, HIGH);
  }
  else {
    digitalWrite(lights, LOW);
  }
}
  */

int get_distance(){
  return ultrasonic.ping_cm();
}

void loop() {
/*  
  distance = get_distance();
  Serial.println(distance);
  if(distance > 0 && distance < 25){
    stop_car();
    bracket.write(0);
    delay(750);
    int distance_a = get_distance();
    delay(50);
    bracket.write(180);
    delay(750);
    int distance_b = get_distance();
    delay(50);
    bracket.write(initial_pos);
       
    if (distance_a < distance_b){
      left(255);
      delay(250);
      stop_car();
      delay(50);    
    }
    else {
      right(255);
      delay(250);
      stop_car();
      delay(50);
    }
  }
*/
  if(Serial3.available()){
    input = Serial3.read();
  }

    if(input == 'X'){
      digitalWrite(lights_forward, HIGH);
      digitalWrite(lights_right, HIGH);
      digitalWrite(lights_left, HIGH);

      car_speed = 255;
      while(true){

        int R = digitalRead(R_pin);
        int M = digitalRead(M_pin);
        int L = digitalRead(L_pin);

        Serial.print("R: ");        
        Serial.print(R);
        Serial.print("   ");
        Serial.print("M: ");
        Serial.print(M);
        Serial.print("   ");
        Serial.print("L: ");
        Serial.println(L);
        


        
        if((R == line && M == line && L == line) || (R == no_line && M == line && L == no_line)){forward(car_speed);}
        else if((R == line && M == no_line && L == no_line) || (R == line && M == line && L == no_line)){right_p2(car_speed);}
        else if((R == no_line && M == no_line && L == line) || (R == no_line && M == line && L == line)){left(car_speed);}      


    if(Serial3.available()){
      input = Serial3.read();
      if(input == 'x'){
        break;
      }      
    }
      }
    }
      
    switch (input){
      case 'S': {stop_car();                 break;}
      case 'F': {forward(car_speed);         break;}
      case 'B': {backward(car_speed);        break;}
      case 'R': {right(car_speed);           break;}
      case 'L': {left(car_speed);            break;}

      case '0': {car_speed = 80;     break;}
      case '1': {car_speed = 120;     break;}
      case '2': {car_speed = 140;     break;}
      case '3': {car_speed = 160;     break;}
      case '4': {car_speed = 180;     break;}
      case '5': {car_speed = 200;     break;}
      case '6': {car_speed = 210;     break;}
      case '7': {car_speed = 220;     break;}
      case '8': {car_speed = 230;     break;}
      case '9': {car_speed = 240;     break;}
      case 'q': {car_speed = 255;     break;}

      case 'V': {horn_fn('1');       break;}
      case 'v': {horn_fn('0');       break;}
      //case 'W': {lights_fn('1');     break;}
    //  case 'w': {lights_fn('0');     break;}
  //    case 'U': {lights_fn('1');     break;}
//      case 'u': {lights_fn('0');     break;}      
    }
    
  }
  
