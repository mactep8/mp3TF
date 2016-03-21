/*        2014-01-07 by lisper <leyapin@gmail.com>
 *        control mp3 module by seirial
 */

#include <Arduino.h>
#include "SoftwareSerial.h"

// EQ VALUES
#define MP3_EQ_NORMAL 0
#define MP3_EQ_POP 1
#define MP3_EQ_ROCK 2
#define MP3_EQ_JAZZ 3
#define MP3_EQ_CLASSIC 4
#define MP3_EQ_BASS 5

// playback device
#define MP3_DEV_USB 0
#define MP3_DEV_SD 1

// Commands
#define MP3_PLAY_NEXT 0x01
#define MP3_PLAY_PREV 0x02
#define MP3_PLAY_TRACK 0x03
#define MP3_VOLUME_INC 0x04
#define MP3_VOLUME_DEC 0x05
#define MP3_VOLUME_SET 0x06
#define MP3_EQ_SET 0x07
#define MP3_SINGLE_REPEAT 0x08
#define MP3_SET_DEVICE 0x09
#define MP3_SLEEP 0x0A
#define MP3_RESET 0x0C
#define MP3_PLAY 0x0D
#define MP3_PAUSE 0x0E
#define MP3_PLAY_FOLDER 0x0F
#define MP3_AMPLIFIER 0x10
#define MP3_SET_ALL_REPEAT 0x11
#define MP3_PLAY_FOLDER_MP3 0x12
#define MP3_INTER_CUT 0x13
#define MP3_PLAY_FOLDER2 0x14
#define MP3_INTER_CUT_STOP 0x15
#define MP3_STOP 0x16
#define MP3_REPEAT_FOLDER 0x17
#define MP3_PLAY_RANDOM 0x18
#define MP3_REPEAT_CURRENT 0x19
#define MP3_SET_DAC 0x1A

class mp3TF{
private:
        SoftwareSerial* mySerial;
	byte packet[10];
	void sendCmd (uint8_t cmd, uint16_t Value); 
	uint16_t get_checksum ();
public :
	void init (SoftwareSerial*);
	void playNext();
	void playPrev();
	void playTrackPhisical(uint16_t track_num);
	void playRepeatSingle(uint16_t track_num);
	void playFolder(uint8_t folder, uint8_t track);
    void playFolder2(uint8_t folder, uint16_t track);
	void play();
	void pause();
	void stop();
	void playAllRepeat(bool start);
	void playMP3Folder(uint16_t track);
	void playFolderRepeat(uint8_t folder);
	void playRandom();
	void repeatCurrent(bool start);

	void volumeInc();
	void volumeDec();
	void volumeSet(uint8_t val);

	void setEQ(uint8_t val);
	void setAudioAmplifier(uint8_t val);

	void Sleep();
	void Reset();
	void setInterCut(uint16_t track);
	void stopInterCut();
	void useDAC(bool use);
};

