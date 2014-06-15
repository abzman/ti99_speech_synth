
int data[] = {
  2,3,4,5,6,7,8,9};
int a = 10;
int b = 11;
int g1 = 12;
int led = 13;
int gb2 = A0;
int rdy = A1;
int speak[] = {
  0,1,0,1,0,0,0,0};
int addr[] = {
  0,1,0,0,0,0,0,0};
int reset_cmd[] = {
  0,1,1,1,0,0,0,0};
void setup() {      
  for (int i = 0;i<8;i++)
  {
    pinMode(data[i], OUTPUT);
  }
  pinMode(g1, OUTPUT);       
  pinMode(a, OUTPUT);       
  pinMode(gb2, OUTPUT);       
  pinMode(led, OUTPUT);       
  pinMode(b, OUTPUT);       
  pinMode(rdy, INPUT);    

  digitalWrite(gb2,LOW); 
  Serial.begin(115200);
  Serial.println("TI speech synth code");
  //write_rst();
  //write_addr(0);
  //Serial.println("reset");
}

void loop() {
  is_ready();
  if(get_rdy())
  {
    Serial.println("speaking");
    write_speak();
  }
  delay(1000);
}

void is_ready()
{
  if(get_rdy())
  {
    Serial.println("ready");
    digitalWrite(led,HIGH);
  }
  else
  {
    Serial.println("not ready");
    digitalWrite(led,LOW);
  }
}

void write_speak()
{
  for (int i = 0;i<8;i++)
  {
    digitalWrite(data[i], speak[i]);
  }
  set_write();
}

void write_rst()
{
  for (int i = 0;i<8;i++)
  {
    digitalWrite(data[i], reset_cmd[i]);
  }
  set_write();
  
}

void write_addr(int addre)
{
  addr[4] = addre % 16;
  addr[5] = addre % 8;
  addr[6] = addre % 4;
  addr[7] = addre % 2;
  for (int i = 0;i<8;i++)
  {
    digitalWrite(data[i], addr[i]);
  }
  set_write();
}

void set_read()
{
  digitalWrite(a,LOW);
  digitalWrite(b,HIGH);
  digitalWrite(g1,HIGH);
    delayMicroseconds(8);
    set_none();
}

void set_write()
{
  digitalWrite(a,HIGH);
  digitalWrite(b,HIGH);
  digitalWrite(g1,HIGH);
    delayMicroseconds(8);
    set_none();
}

void set_something()
{
  digitalWrite(a,LOW);
  digitalWrite(b,LOW);
  digitalWrite(g1,HIGH);
    delayMicroseconds(8);
    set_none();
}

void set_none()
{
  digitalWrite(g1,LOW);
}

boolean get_rdy()
{
  if(digitalRead(rdy))
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

