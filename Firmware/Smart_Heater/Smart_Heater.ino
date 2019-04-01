#define ESPTX 2
#define ESPRX 8
#define enableA 7
#define enableB 4
#define MB1 3
#define MB2 9
#define MA1 5
#define MA2 6
#define Relay 10
#define Hall 11
#define B 17
#define R 19
#define G 16
#define PTM1 A0
#define PTM2 A1
bool updown = false;
int leds[7][3]={{R,0,0},{G,0,0},{B,0,0},{R,G,0},{R,B,0},{B,G,0},{R,G,B}};
void setup() {
  Serial.begin(9600);
  pinMode(enableA,OUTPUT);
  pinMode(enableB,OUTPUT);
  pinMode(MA1, OUTPUT);
  pinMode(MA2, OUTPUT);
  pinMode(MB1, OUTPUT);
  pinMode(MB2, OUTPUT);
  pinMode(Hall, INPUT);
  pinMode(Relay, OUTPUT);
  digitalWrite(enableA,1);  
  digitalWrite(enableB,1);
 
}

void loop() {
  
  if(get_pot1() < 1023 && updown == false){  
    
    go_up(true);
    turn_on_heater();
    updown = true;
  }  
  
  if(get_pot1() == 1023 && updown == true){    
    
    turn_off_heater();
    go_up(false);
    updown = false;
  }

 
    for(int i=0; i<7;i++){  
      fade_pin(leds[i],true,200);
       if(get_pot1() == 1023 && updown == true){
        break;
       }
       else if(get_pot1() < 1023 && updown == false){
        break;
       }
      fade_pin(leds[i],false,200);
    }
  
  
}

int get_pot1(){
  return analogRead(PTM1);
}

int get_pot2(){
  return analogRead(PTM2);
}

void turn_on_heater(){
//  digitalWrite(Relay,1);
  digitalWrite(MB1,1);  
  digitalWrite(MB2,0);
}

void turn_off_heater(){
//  digitalWrite(Relay,0);
  digitalWrite(MB1,0);
  digitalWrite(MB2,0);  
}

void go_up(bool yesorno){
  
  while(get_hall() == 0){
  
    if(yesorno == false){
      retract();
    }
    else{
      extend();      
    }
  }   

  while(get_hall() == 1){
    
    if(yesorno == false){
      retract();
    }
    else{
      extend();
    }    
  }
  delay(50);
  stop_();
}
void fade_pin(int pin[],bool fade_in,int speed_){
  if(fade_in == true){ 
    for(int val=0;val<=100;val++){
      int wait=0;
      while(wait < speed_){
        for(int idx=0; idx < 3; idx++){
          if(pin[idx] != 0){
            digitalWrite(pin[idx],1);
          }
        }
        delayMicroseconds(val);
        for(int idx=0; idx < 3; idx++){
          if(pin[idx] != 0){
            digitalWrite(pin[idx],0);
          }
        }
        delayMicroseconds(100-val);
        wait ++;
      }
    }
  }
  else{
    for(int val=100;val>=0;val--){
      int wait=0;
      while(wait < speed_){
        for(int idx=0; idx < 3; idx++){
          if(pin[idx] != 0){
            digitalWrite(pin[idx],1);
          }
        }
        delayMicroseconds(val);
        for(int idx=0; idx < 3; idx++){
          if(pin[idx] != 0){
            digitalWrite(pin[idx],0);
          }
        }
        delayMicroseconds(100-val);
      wait ++;
      }
    }
  }
}

int get_hall(){
  return digitalRead(Hall);
}

void retract(){
  digitalWrite(MA1,0);
  digitalWrite(MA2,1);
}

void extend(){
  digitalWrite(MA1,1);
  digitalWrite(MA2,0);
}

void stop_(){
  digitalWrite(MA1,0);
  digitalWrite(MA2,0);
}
