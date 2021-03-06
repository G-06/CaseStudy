//*****************************************************************************
//
// xaudio2 sound
//
// Author		: Kenji Kabutomori
//
//*****************************************************************************

//*****************************************************************************
// include guard
//*****************************************************************************
#pragma once
#ifndef _XAUDIO2_SOUND_H_
#define _XAUDIO2_SOUND_H_

//*****************************************************************************
// include
//*****************************************************************************

//*****************************************************************************
// forward declaration
//*****************************************************************************

//*****************************************************************************
// class definition
//*****************************************************************************
class XAudio2Sound : public Basic
{
public:
	// constructor
	XAudio2Sound(IXAudio2* ixaudio2);

	// destructor
	virtual ~XAudio2Sound(void);

	// initialize
	bool Initialize(void);

	// uninitialize
	void Uninitialize(void);

	// load from file
	bool LoadFromFile(const s8* filename);

	// load from resource
	bool LoadFromResource(const s8* resource);

	// play
	bool Play(const u32& loop_count);

	// stop
	void Stop(void);

	// pause
	void Pause(void);

	// set volume
	void SetVolume(const f32& volume);

	// create clone ixaudio2 source voice
	IXAudio2SourceVoice* CreateCloneIXAudio2SourceVoice(void);

	// clone xaudio2 buffer
	void CloneXAudio2Buffer(XAUDIO2_BUFFER* xaudio2_buffer);

	// accesor
	const f32& __volume(void)const { return volume_; }
	bool __is_play(void)const { return is_play_; }
	bool __is_pause(void)const { return is_pause_; }

private:
	IXAudio2* ixaudio2_;
	IXAudio2SourceVoice* ixaudio2_source_voice_;
	XAUDIO2_BUFFER xaudio2_buffer_;
	bool is_pause_;
	bool is_play_;
	f32 volume_;
	WAVEFORMATEX waveformatex_;
	bool ReadWaveData(const s8* data);
};

#endif // _XAUDIO2_SOUND_H_

//---------------------------------- EOF --------------------------------------
