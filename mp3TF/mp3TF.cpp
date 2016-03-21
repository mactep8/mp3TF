/*        2014-01-07 by lisper <leyapin@gmail.com>
 *        control mp3 module by seirial
 */

#include <Arduino.h>
#include "mp3TF.h"


//calc checksum (1~6 byte)
uint16_t mp3TF::get_checksum () 
{
	uint16_t sum = 0;
	for (int i=1; i<7; i++) 
	{
		sum += packet[i];
	}
	return -sum;
}

//
void mp3TF::init (SoftwareSerial* theSerial) {
	mySerial = theSerial;
	packet[0] = 0X7E;
	packet[1] = 0xFF;
	packet[2] = 0x06; // 6 bytes w/o checksum
	packet[3] = 0X00; // 0x01: Need feedback--send confirmation back to MCU; 0x00: No need feedback
	packet[4] = 0X00; // command id
	packet[5] = 0X00;
	packet[6] = 0X00;
	packet[7] = 0XFE;
	packet[8] = 0X00;
	packet[9] = 0XEF;
}

// Sending command to player
void mp3TF::sendCmd (uint8_t cmd, uint16_t Value) 
{
	packet[3] = cmd;
	packet[5] = (Value >> 8);
	packet[6] = Value & 0xff;
	uint16_t sum = get_checksum();
	packet[7] = (sum >> 8);
	packet[8] = sum & 0xFF;
	for (int i=0; i<10; i++) //send cmd
	{ 
		(*mySerial).write (packet[i]);
	}
}

// play next track
void mp3TF::playNext()
{
	sendCmd(MP3_PLAY_NEXT, 0);
}

// play prev track
void mp3TF::playPrev()
{
	sendCmd(MP3_PLAY_PREV, 0);
}

// play track by number (phisically ordered)
void mp3TF::playTrackPhisical(uint16_t track_num)
{
	sendCmd(MP3_PLAY_TRACK, track_num);
}

// repeat single track
void mp3TF::playRepeatSingle(uint16_t track_num)
{
	sendCmd(MP3_SINGLE_REPEAT, track_num);
}

// play track in folder; Folders 01-99
void mp3TF::playFolder(uint8_t folder, uint8_t track)
{
	
	sendCmd(MP3_PLAY_FOLDER, (uint16_t)((folder<<8)|(track & 0xff)));
}

// play track in folder;  Supports 15 folders only(01-15)
void mp3TF::playFolder2(uint8_t folder, uint16_t track)
{
	sendCmd(MP3_PLAY_FOLDER2, (uint16_t)((folder<<12)|(track & 0xfff)));
}

void mp3TF::play()
{
	sendCmd(MP3_PLAY, 0);
}

void mp3TF::pause()
{
	sendCmd(MP3_PAUSE, 0);
}

void mp3TF::stop()
{
	sendCmd(MP3_STOP, 0);
}

void mp3TF::playAllRepeat(bool start)
{
	sendCmd(MP3_SET_ALL_REPEAT, (uint16_t)start);
}

void mp3TF::playMP3Folder(uint16_t track)
{
	sendCmd(MP3_PLAY_FOLDER_MP3, track);
}

void mp3TF::volumeInc()
{
	sendCmd(MP3_VOLUME_INC, 0);
}

void mp3TF::volumeDec()
{
	sendCmd(MP3_VOLUME_DEC, 0);
}

void mp3TF::volumeSet(uint8_t val)
{
	sendCmd(MP3_VOLUME_SET, (uint16_t)val);
}

void mp3TF::setEQ(uint8_t val)
{
	sendCmd(MP3_EQ_SET, (uint16_t)val);
}

void mp3TF::setAudioAmplifier(uint8_t val)
{
	sendCmd(MP3_AMPLIFIER, (uint16_t)val);
}

void mp3TF::Sleep()
{
	sendCmd(MP3_SLEEP, 0);
}

void mp3TF::Reset()
{
	sendCmd(MP3_RESET, 0);
}

void mp3TF::setInterCut(uint16_t track)
{
	sendCmd(MP3_INTER_CUT, track);
}

void mp3TF::stopInterCut()
{
	sendCmd(MP3_INTER_CUT_STOP, 0);
}

void mp3TF::playFolderRepeat(uint8_t folder)
{
	sendCmd(MP3_REPEAT_FOLDER, (uint16_t)folder);
}

void mp3TF::playRandom()
{
	sendCmd(MP3_PLAY_RANDOM, 0);
}

void mp3TF::repeatCurrent(bool start)
{
	sendCmd(MP3_REPEAT_CURRENT, (uint16_t)start);
}

void mp3TF::useDAC(bool use)
{
	sendCmd(MP3_SET_DAC, (uint16_t)use);
}
