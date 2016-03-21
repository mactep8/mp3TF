#include <SoftwareSerial.h>
#include <mp3TF.h>
#define READ_D2 ((PIND>>2) & 1)

mp3TF mp3tf = mp3TF ();
SoftwareSerial SoundSerial(7,8);

void setup()
{
  pinMode(2, INPUT);
  SoundSerial.begin(9600);
  mp3tf.init (&SoundSerial);
}

void loop()
{
  mp3tf.playTrackPhisical(1);
  delay(10000); //wait 10s
  mp3tf.playTrackPhisical(2);
  delay(100); // wait 100us
  while(!READ_D2) ; // wait while play track
  mp3tf.playRepeatSingle(3);
  delay(9500);
  mp3tf.setInterCut(4); // Interrupt track 3 for playing track 4
  delay(10000);
  mp3tf.playTrackPhisical(5);
  delay(15000);
}
