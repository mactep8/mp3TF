#include <SoftwareSerial.h>
#include <mp3TF.h>
#define READ_D2 ((PIND>>2) & 1)

mp3TF mp3tf = mp3TF ();
SoftwareSerial SoundSerial(7,8);

void setup()
{
  Serial.begin(9600);
  pinMode(2, INPUT);
  SoundSerial.begin(9600);
  mp3tf.init (&SoundSerial);
  attachInterrupt(0, SoundIRQ, RISING);
}

volatile byte play_id = 1;
void loop()
{
  play_id = 1;
  mp3tf.playTrackPhisical(play_id);
  delay(10000); //wait 10s
  play_id++;
  mp3tf.playTrackPhisical(play_id);
  delay(100); // wait 100us
  while(!READ_D2) ; // wait while play track
  
  delay(9500);
  play_id++;
  mp3tf.setInterCut(play_id); // Interrupt track 3 for playing track 4
  delay(10000);
  play_id++;
  mp3tf.playTrackPhisical(play_id);
  delay(15000);
}

void SoundIRQ()
{
  Serial.println(play_id);
  
  if (play_id == 2)
  {
    play_id++;
    mp3tf.playRepeatSingle(play_id);
  }
}
