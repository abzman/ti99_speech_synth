
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
  pinMode(rdy, INPUT_PULLUP);    

// OFF
  digitalWrite(g1,LOW); 
  digitalWrite(gb2,LOW); 
  digitalWrite(a,LOW); 
  digitalWrite(b,HIGH);

  Serial.begin(115200);
  Serial.println("TI speech synth code");
  //write_rst();
  //write_addr(0);
  //Serial.println("reset");

  //do_reset_command()
    
  wait_for_ready();


    do_load_address(0);
    do_load_address(0);
    do_load_address(0);
    do_load_address(0);
    do_load_address(0);
}

void loop() {
    print_ready_status();

    //Serial.println("speaking");
    delay(1000);
    do_speak_command();
}

void print_ready_status()
{
  if(is_ready())
  {
    //Serial.println("ready");
    digitalWrite(led,HIGH);
  }
  else
  {
    //Serial.println("not ready");
    digitalWrite(led,LOW);
  }
}

/*
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
*/

void wait_for_ready()
{
  while(!is_ready());
}

void wait_for_not_ready()
{
  while(is_ready());
}

void do_load_address(int addre)
{
  Serial.println("do_load_address()");
  
  addr[4] = (addre>>3)&0x01;
  addr[5] = (addre>>2)&0x01;
  addr[6] = (addre>>1)&0x01;
  addr[7] = (addre>>0)&0x01;
  
  // Enable Write
  digitalWrite(a,HIGH);
  digitalWrite(b,HIGH);
  digitalWrite(g1,HIGH);
  
  wait_for_not_ready();

  for (int i = 0;i<8;i++)
  {
    digitalWrite(data[i], addr[i]);
  }

  // Disable Write
  digitalWrite(g1,LOW);

  wait_for_ready();
}

void do_speak_command()
{
  // Enable Write
  digitalWrite(a,HIGH);
  digitalWrite(b,HIGH);
  digitalWrite(g1,HIGH);
  
  wait_for_not_ready();

  for (int i = 0;i<8;i++)
  {
    digitalWrite(data[i], speak[i]);
  }

  // Disable Write
  digitalWrite(g1,LOW);

  wait_for_ready();
}

void do_reset_command()
{
  // Enable Write
  digitalWrite(a,HIGH);
  digitalWrite(b,HIGH);
  digitalWrite(g1,HIGH);

  Serial.println("a");
  
  wait_for_not_ready();

  Serial.println("b");

  for (int i = 0;i<8;i++)
  {
    digitalWrite(data[i], 1);
  }

  // Disable Write
  digitalWrite(g1,LOW);

  Serial.println("c");

  wait_for_ready();

  Serial.println("d");

}

/*
void read_req()
{
  // Enable Read
  digitalWrite(a,LOW);
  digitalWrite(b,HIGH);
  digitalWrite(g1,HIGH);
  
  wait_for_not_ready();

  
}

void set_read()
{
  // Do Read
  digitalWrite(g1,LOW);
  
  // Wait For Ready
  wait_for_ready();
}

void set_write()
{
  // Do Write
  digitalWrite(a,HIGH);
  digitalWrite(b,HIGH);
  digitalWrite(g1,HIGH);
    delayMicroseconds(8);
    set_none();
  // Wait for Ready
  wait_for_ready();
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
*/

boolean is_ready()
{
  if(digitalRead(rdy))
  {
    return 1;
  }
  else
  {
    return 0;
  }
}
