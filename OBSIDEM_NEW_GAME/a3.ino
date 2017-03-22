#include "Mfrc522.h"
#include <SPI.h>


//r1 pins
#define r1_shield_pin 6
#define r1_bust_pin 2
#define r1_motor_relay_pin 18
#define r1_motor_mosfet_pin 40
#define r1_large_frame_pin 39
#define r1_pedestal_pin 38

//r2 pins
#define r2_houselight_pin 37
#define r2_uv_pin 36
#define r2_entry_door_pin 24
#define r2_exit_door_pin 11
#define r2_laserrx1_pin 28
#define r2_laserrx2_pin 27
#define r2_laserrx3_pin 26
#define r2_laserrx4_pin 25
#define r2_door_lights_pin 19

//r3 pins
#define r3_picture_pin 13
#define r3_g1_pin 34
#define r3_g2_pin 33
#define r3_g3_pin 32
#define r3_g4_pin 31
#define r3_shield_pin 23
#define r3_statue_orientation_pin 8


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
class Room1
{
public:
bool sliding_frame;
bool pedestal;
bool large_frame;

int off_state;

  Room1()
{
 pinMode(r1_shield_pin,INPUT_PULLDOWN);
 pinMode(r1_bust_pin,INPUT_PULLDOWN);
 pinMode(r1_motor_relay_pin,OUTPUT);
 pinMode(r1_motor_mosfet_pin,OUTPUT);
 pinMode(r1_large_frame_pin,OUTPUT);
 pinMode(r1_pedestal_pin,OUTPUT);
 calibrate_bust();
}

//r1 functions
bool check_shield()
{
  return (digitalRead(r1_shield_pin));
}

void calibrate_bust()
{
  off_state = analogRead(r1_bust_pin);
}

bool check_bust()
{
  return digitalRead(r1_bust_pin);
}

void set_pedestal(bool state)
{
  digitalWrite(r1_pedestal_pin,state);
}

void set_frame(bool state)
{
  digitalWrite(r1_large_frame_pin,state);
}

void activate_slider(bool direction)
{
  digitalWrite(r1_motor_relay_pin,direction);
  digitalWrite(r1_motor_mosfet_pin,true);
  delay (5000);
  digitalWrite(r1_motor_mosfet_pin,false);
}
};
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
class Room2
{
public:
bool exit_door;


Room2()
{
pinMode(r2_houselight_pin,OUTPUT);
pinMode(r2_uv_pin,OUTPUT);
pinMode(r2_entry_door_pin,INPUT_PULLDOWN);
pinMode(r2_exit_door_pin,OUTPUT);
pinMode(r2_laserrx1_pin,INPUT);
pinMode(r2_laserrx2_pin,INPUT);
pinMode(r2_laserrx3_pin,INPUT);
pinMode(r2_laserrx4_pin,INPUT);
pinMode(r2_door_lights_pin, OUTPUT);
calibrate_laserrx();
}
//room2 objects
const int code[4] =  {1,1,1,1};
int puzzle_state = 0;
int avg_base_value = 200;
bool r2_door;
//

//
//r2_functions
void set_houselights (bool status)
{
  digitalWrite(r2_houselight_pin, status);
}

void set_uv (bool status)
{
  digitalWrite(r2_uv_pin, status);
}

void set_door_lights(int intensity)
{
  analogWrite(r2_door_lights_pin,intensity);
}

bool get_entry_door_status()
{
  return (digitalRead(r2_entry_door_pin));
}

void set_exit_door(bool status)
{
  digitalWrite(r2_exit_door_pin,status);
}

int calibrate_laserrx()
{
  int avg = 0;
  avg = analogRead(r2_laserrx1_pin) + analogRead(r2_laserrx2_pin) + analogRead(r2_laserrx3_pin) + analogRead(r2_laserrx4_pin);
  avg /= 4;
  return avg;
}


bool check_laser_rx (int laser_number)
{
  bool rx_value;
  switch(laser_number)
  {
  case 1: {rx_value = digitalRead(r2_laserrx1_pin);
  break;}
  case 2: {rx_value = digitalRead(r2_laserrx2_pin);
  break;}
  case 3: {rx_value = digitalRead(r2_laserrx3_pin);
  break;}
  case 4: {rx_value = digitalRead(r2_laserrx4_pin);
  break;}
  }
  Serial.println(!rx_value);
  return !rx_value;
}

int check_laser_puzzle()
{
  Serial.println(puzzle_state);
  if ((puzzle_state == 0) && (check_laser_rx(code[0])))
    {
    puzzle_state = 1;
    set_door_lights(63);
    delay (500);
    }

  if ((puzzle_state == 1) && (check_laser_rx(code[1])))
    {
    puzzle_state = 2;
    set_door_lights(126);
    delay(500);
    }
 /* else
  {
    puzzle_state = 0;
    set_door_lights(0);
  }*/

  if ((puzzle_state == 2) && (check_laser_rx(code[2])))
    {
      puzzle_state = 3;
      set_door_lights(189);
      delay(500);
    }
  /*else
  {
    puzzle_state = 0;
    set_door_lights(0);
  }*/
  
  if ((puzzle_state == 3) && (check_laser_rx(code[3])))
    {
      puzzle_state = 4;
      set_door_lights(255);
      set_exit_door(false);
      r2_door = true;
      
      delay(500);
    }
  /*else
    {
    puzzle_state = 0;
    set_door_lights(0);
    }*/



  return puzzle_state;
}

};
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
class Room3
{
public:
  bool pictures;
  bool magnetic_busts;
  bool shield;

Room3()
{
pinMode(r3_picture_pin,INPUT_PULLUP);
pinMode(r3_g1_pin, OUTPUT);
pinMode(r3_g2_pin,OUTPUT);
pinMode(r3_g3_pin,OUTPUT);
pinMode(r3_g4_pin,OUTPUT);
pinMode(r3_shield_pin,INPUT_PULLDOWN);
pinMode(r3_statue_orientation_pin,INPUT_PULLDOWN);
}



bool check_pictures()
{
  return (digitalRead(r3_picture_pin));
}

void set_glyph(int glyph, bool status)
{
  if(glyph == 1)
    digitalWrite(r3_g1_pin,status);
  if(glyph == 2)
    digitalWrite(r3_g2_pin,status);
  if(glyph == 3)
    digitalWrite(r3_g3_pin,status);
  if(glyph == 1)
    digitalWrite(r3_g4_pin,status);
 
}

bool check_shield()
{
  return(digitalRead(r3_shield_pin));
}

bool check_statue_orientation()
{
  return(digitalRead(r3_statue_orientation_pin));
}
};

class RFID_EFFECTS {
  public:
    Mfrc522 * rfid1;
    Mfrc522 * rfid2;
    Mfrc522 * rfid3;
    Mfrc522 * rfid4;
    Mfrc522 * rfid5;
    Mfrc522 * rfid6;  
  RFID_EFFECTS ()
  {
  SPI.begin();
    rfid1 = new Mfrc522(0);
    rfid2 = new Mfrc522(1);
    rfid3 = new Mfrc522(2);
    rfid4 = new Mfrc522(3);
    rfid5 = new Mfrc522(4);
    rfid6 = new Mfrc522(5);
/*
    rfid1->Init();
    rfid2->Init();
    rfid3->Init();
    rfid4->Init();
    rfid5->Init();
    rfid6->Init(); */  
  }

  
void  print_code (Mfrc522*  rfid )
  {
    unsigned char temp[16];
    
    if (rfid->Request(PICC_REQIDL, temp) == '0')
      {
        if (rfid->Anticoll(temp) == '0')
        {
          Serial.println("code reading: ");
          for (int i = 0 ; i < 6 ; i++)
          {
            Serial.print(temp[i]);
          }
          
        }
      }
      else
      Serial.println("no code");
  }
  
};



Room1 room1;
Room2 room2;
Room3 room3;
RFID_EFFECTS rfid_effect;

void setup_room()
{
  
//  room1.sliding_frame      =false;
  room1.pedestal           =false;
  room1.large_frame        =false;
  room2.r2_door            =false;
  room3.magnetic_busts     =false;
  room3.pictures           =false;
  room3.shield             =false;
//  rfid.room1               =false;
//  rfid.room3               =false;

  room1.set_frame(true);
  room1.set_pedestal(true);
//  room1.activate_slider(false);
//  room1.calibrate_bust();

  room2.set_uv(false);
  room2.set_houselights(true);
  room2.set_exit_door(true);
  room2.set_door_lights(0);
//  room2.calibrate_laserrx();

  room3.set_glyph(1,false);
  room3.set_glyph(2,false);
  room3.set_glyph(3,false);
  room3.set_glyph(4,false);

  
  Serial.println("setup completed");
  delay(1000);
}




void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
 // Serial.setTimeout (100);
  Serial.println("booting up");
  
setup_room();

}



void loop() {
   Serial.println(room3.check_pictures());

    //rfid_effect.print_code(rfid_effect.rfid1);
    //rfid_effect.print_code(rfid_effect.rfid2);
    //rfid_effect.print_code(rfid_effect.rfid3);
    //rfid_effect.print_code(rfid_effect.rfid4);
    //rfid_effect.print_code(rfid_effect.rfid5);
    //rfid_effect.print_code(rfid_effect.rfid6);
   
   
    if(room1.check_shield())
      {
        room1.set_frame(false);
        if(!room1.large_frame)
          room1.large_frame = true;
      }
      

    if(room1.check_bust())
    {
      room1.set_pedestal(false);
      if(!room1.pedestal)
        room1.pedestal = true;
    }

     

    
    room2.set_uv(!room2.get_entry_door_status());
    
    room2.set_houselights(room2.get_entry_door_status()||room2.r2_door);
    
    int foo = room2.check_laser_puzzle();    
 
    if(room3.check_shield())
    {
      room3.set_glyph(3,true);
      if (!room3.shield)
        room3.shield = true;
    }

   
    if(room3.check_pictures())
     {
      room3.set_glyph(1,true);
      if(!room3.pictures)
        room3.pictures = true;
     }

    if(room3.check_statue_orientation())
      {
      room3.set_glyph(2,true);
      if(!room3.magnetic_busts)
        room3.magnetic_busts = true;
      }
 
}
