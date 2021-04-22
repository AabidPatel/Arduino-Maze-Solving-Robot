#define leftFarSensor     A1
#define leftNearSensor    A2
#define CenterSensor      A3
#define rightNearSensor   A4
#define rightFarSensor    A5

#define base 0
#define line 1

int CenterReading;
int leftNearReading;
int leftFarReading;
int rightNearReading;
int rightFarReading;

int leftNudge;
int replaystage;
int rightNudge;

#define leapTime 200

#define leftMotor1  3
#define leftMotor2  5

#define rightMotor1 9
#define rightMotor2 6

#define enableA 10
#define enableB 11

#define botspeed 230

#define led 13

char path[30] = {};
int pathLength;
int readLength;

void setup(){
  
  pinMode(leftNearSensor, INPUT);
  pinMode(leftFarSensor, INPUT);
  pinMode(CenterSensor, INPUT);
  pinMode(rightNearSensor, INPUT);
  pinMode(rightFarSensor, INPUT);
    
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
  pinMode(enableA, OUTPUT);
  pinMode(enableB, OUTPUT);

  analogWrite(enableA, botspeed);
  analogWrite(enableB, botspeed);
  
  pinMode(led, OUTPUT);
  //Serial.begin(115200);
  digitalWrite(led, HIGH);
  delay(1000);
}


void loop(){
  
 readSensors();                                                                                     
 
 if(leftFarReading==base && rightFarReading==base && (leftNearReading==line || CenterReading==line || rightNearReading==line)){ 
    straight();                                                                                      
  }
  else{                                                                                              
    leftHand();                                                                                   
  }

}

void readSensors(){
  
  CenterReading      = digitalRead(CenterSensor);
  leftNearReading    = digitalRead(leftNearSensor);
  leftFarReading     = digitalRead(leftFarSensor);
  rightNearReading   = digitalRead(rightNearSensor);
  rightFarReading    = digitalRead(rightFarSensor);  

// serial printing below for debugging purposes

// Serial.print("CenterReading: ");
// Serial.println(CenterReading);
// Serial.print("leftNearReading: ");
// Serial.println(leftNearReading);
// Serial.print("leftFarReading: ");
// Serial.println(leftFarReading);
  
// Serial.print("rightNearReading: ");
// Serial.println(rightNearReading);
// Serial.print("rightFarReading: ");
// Serial.println(rightFarReading);
// delay(200);
  

}


void leftHand(){
  

  if( leftFarReading==line && rightFarReading==line){
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(leapTime);
    readSensors();
    
    if(leftFarReading==line || rightFarReading==line){
      done();
    }
    if(leftFarReading==base && rightFarReading==base){ 
      turnLeft();
    }
    
  }
  
  if(leftFarReading==line){ // if you can turn left then turn left
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(leapTime);
    readSensors();
      
      if(leftFarReading==base && rightFarReading==base){
        turnLeft();
      }
      else{
        done();
      }
  }
   
  if(rightFarReading==line){
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(30);
    readSensors();
    
    if(leftFarReading==line){
      delay(leapTime-30);
      readSensors();
      
      if(rightFarReading==line && leftFarReading==line){
        done();
      }
      else{
        turnLeft();
        return;
      }
    }
    delay(leapTime-30);
    readSensors();
    if(leftFarReading==base && CenterReading==base && rightFarReading==base){
      turnRight();
      return;
    }
    path[pathLength]='S';
   // Serial.println("s");
    pathLength++;
    //Serial.print("Path length: ");
    //Serial.println(pathLength);
    if(path[pathLength-2]=='B'){
    //Serial.println("shortening path");
    shortPath();
     }
    straight();
  }
  readSensors();
  if(leftFarReading==base && CenterReading==base && rightFarReading==base && leftNearReading==base && rightNearReading==base){
    turnAround();
  }

}
void done(){
  digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
  replaystage=1;
  path[pathLength]='D';
  pathLength++;
 while(digitalRead(leftFarSensor)==line){
   digitalWrite(led, LOW);
   delay(150);
   digitalWrite(led, HIGH);
   delay(150);
 }
 delay(10000);
  replay();
}

void turnLeft(){
  
    
 
  while(digitalRead(CenterSensor)==line){
     digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, HIGH);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(2);
     digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(1);
  }
    
  while(digitalRead(CenterSensor)==base){
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, HIGH);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(2);
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(1);
  }
 
  if(replaystage==0){
    path[pathLength]='L';
    //Serial.println("l");
    pathLength++;
    //Serial.print("Path length: ");
    //Serial.println(pathLength);
      if(path[pathLength-2]=='B'){
        //Serial.println("shortening path");
        shortPath();
      }
  }
}

void turnRight(){

    
  while(digitalRead(CenterSensor)==line){
     digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, HIGH);
    delay(2);
     digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(1);
  }
   while(digitalRead(CenterSensor)==base){
     digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, HIGH);
    delay(2);
     digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(1);
  }
  
  if(replaystage==0){
  path[pathLength]='R';
  //Serial.println("r");
  pathLength++;
  //Serial.print("Path length: ");
  //Serial.println(pathLength);
    if(path[pathLength-2]=='B'){
      //Serial.println("shortening path");
      shortPath();
    }
  }
 
}

void straight(){
  if( digitalRead(rightNearSensor)==line){
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(1);
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(5);
    return;
  }
  if(digitalRead(leftNearSensor)==line){
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(1);
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(5);
    return;
  }
  
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(4);
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(1);
  
}

void turnAround(){
    digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(150);
   while(digitalRead(CenterSensor)==base){
     digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, HIGH);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(2);
     digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
    delay(1);
  }
  path[pathLength]='B';
  pathLength++;
  straight();
  //Serial.println("b");
  //Serial.print("Path length: ");
  //Serial.println(pathLength);
}

void shortPath(){
 int shortDone=0;
  if(path[pathLength-3]=='L' && path[pathLength-1]=='R'){
    pathLength-=3;
    path[pathLength]='B';
    //Serial.println("test1");
    shortDone=1;
  }
   
  if(path[pathLength-3]=='L' && path[pathLength-1]=='S' && shortDone==0){
    pathLength-=3;
    path[pathLength]='R';
    //Serial.println("test2");
    shortDone=1;
  }
   
  if(path[pathLength-3]=='R' && path[pathLength-1]=='L' && shortDone==0){
    pathLength-=3;
    path[pathLength]='B';
    //Serial.println("test3");
    shortDone=1;
  }
  
   
  if(path[pathLength-3]=='S' && path[pathLength-1]=='L' && shortDone==0){
    pathLength-=3;
    path[pathLength]='R';
    //Serial.println("test4");
    shortDone=1;
  }
     
  if(path[pathLength-3]=='S' && path[pathLength-1]=='S' && shortDone==0){
    pathLength-=3;
    path[pathLength]='B';
    //Serial.println("test5");
    shortDone=1;
  }
    if(path[pathLength-3]=='L' && path[pathLength-1]=='L' && shortDone==0){
    pathLength-=3;
    path[pathLength]='S';
    //Serial.println("test6");
    shortDone=1;
  }
  
  path[pathLength+1]='D';
  path[pathLength+2]='D';
  pathLength++;
  //Serial.print("Path length: ");
  //Serial.println(pathLength);
  //printPath();
}




void printPath(){
  Serial.println("+++++++++++++++++");
  int x;
  while(x<=pathLength){
  Serial.println(path[x]);
  x++;
  }
  Serial.println("+++++++++++++++++");
}


void replay(){
   readSensors();
  if(leftFarReading==base && rightFarReading==base){
    straight();
  }
  else{
    if(path[readLength]=='D'){
       digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(100);
    digitalWrite(leftMotor1, LOW);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, LOW);
    digitalWrite(rightMotor2, LOW);
      endMotion();
    }
    if(path[readLength]=='L'){
     digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(leapTime);
      turnLeft();
    }
    if(path[readLength]=='R'){
       digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(leapTime);
    turnRight();
    }
    if(path[readLength]=='S'){
       digitalWrite(leftMotor1, HIGH);
    digitalWrite(leftMotor2, LOW);
    digitalWrite(rightMotor1, HIGH);
    digitalWrite(rightMotor2, LOW);
    delay(leapTime);
    straight();
    }
    
    readLength++;
  }
    
  replay();
  
}

void endMotion(){
    digitalWrite(led, LOW);
    delay(500);
    digitalWrite(led, HIGH);
    delay(200);
      digitalWrite(led, LOW);
    delay(200);
    digitalWrite(led, HIGH);
    delay(500);
  endMotion();
}
