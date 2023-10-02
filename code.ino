int trig,echoPin,ir1,ir2,distance;
int m[4][2]={},e1,e2,e3,e4;

int dist()
{
   digitalWrite(trig, LOW);
    delayMicroseconds(2);  
    digitalWrite(trig,HIGH); 
    delayMicroseconds( 10);
    digitalWrite(trig,LOW);
    int duration = pulseIn(echoPin, HIGH);
    int distance = duration * 0.034 / 2; 
    return distance;
}
void forward()
{
  for(int j=0;j<4;j++)
  {
  for(int i=0;i<2;i++)
  {
    if(i)
    {
      digitalWrite(m[j][i],HIGH);
    }
    else
    {
      digitalWrite(m[j][i],LOW);
    }
  }
  }
}
void backward()
{
  for(int j=0;j<4;j++)
  {
  for(int i=0;i<2;i++)
  {
    if(i==0)
    {
      digitalWrite(m[j][i],HIGH);
    }
    else
    {
      digitalWrite(m[j][i],LOW);
    }
  }
  }
}
void right()
{
  for(int j=0;j<2;j++)
  {
  for(int i=0;i<2;i++)
  {
    if(i)
    {
      digitalWrite(m[j][i],HIGH);
    }
    else
    {
      digitalWrite(m[j][i],LOW);
    }
  }
  }
  digitalWrite(m[3][0],HIGH);
  digitalWrite(m[3][1],LOW);
   digitalWrite(m[2][1],HIGH);
  digitalWrite(m[2][0],LOW);
}
void left()
{
  for(int j=0;j<2;j++)
  {
  for(int i=0;i<2;i++)
  {
    if(i)
    {
      digitalWrite(m[j][i],HIGH);
    }
    else
    {
      digitalWrite(m[j][i],LOW);
    }
  }
  }
  digitalWrite(m[2][0],HIGH);
  digitalWrite(m[2][1],LOW);
   digitalWrite(m[3][1],HIGH);
  digitalWrite(m[3][0],LOW);
}
void stop()
{
  for(int j=0;j<2;j++)
  {
  for(int i=0;i<2;i++)
  {
    digitalWrite(m[j][i],LOW);
  }
  }
}
void speed(int x)
{
  analogWrite(e1,x);
  analogWrite(e2,x);
  analogWrite(e3,x);
  analogWrite(e4,x);
}
void setup() {
for(int j=0;j<2;j++)
  {
  for(int i=0;i<2;i++)
  {
    pinMode(m[j][i],OUTPUT);
  }
  }
  pinMode(trig,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(ir1,INPUT);
  pinMode(ir2,INPUT);
  Serial.begin(9600);

}
void manual()
{
  if(Serial.available()>0)
  {
      String c=Serial.readString();
      c.trim();
      if(c=="s")
      {
        stop();
      
      }
      else if(c=="l")
      {
        left();
      }
      else if(c=="r")
      {
        right();
      }
      else if(c=="f")
      {
        forward();
      }
      else if(c=="b")
      {
        backward();
      }
      else
      {
        int l=Serial.parseInt();
        speed(l);
      }
  }
}
void autom()
{
int c=0;
 distance = dist();
  while (distance < 20 )  {
    forward(); 
    distance = dist();
    int IR_front = digitalRead(ir1);
    int IR_back = digitalRead(ir2);
    if ( IR_front ==0|| IR_back  ==0 ) {c=2; break;}
    delay(10); }
 if (ir1==0 &&c==2)  
   {
   stop();
   delay (50);
   backward();
   
   } 
   
 if (ir2 ==0 &&c==2)  
   {
   stop();
   delay (50);
   forward();

   }
 right(); 
    stop();
   
    
  
}
bool a=1;
void loop() {
 if(Serial.available()>0)
  {
      String c=Serial.readString();
      c.trim();
     if(c=="auto")
     {
       a=1;
     }
     if(c=="manual")
     {a=0;
     }
  }
  if(a)
  {
    autom();
  }
  else
  {
    manual();
  }
  int distance=dist();
  Serial.println(distance);
}