#pragma once

#include "IAudio.hpp"
#include "EncodeManager.hpp"
#include "portaudio.h"
#include "AudioOption.h"

class	AudioManager : public IAudio
{
private:
	PaStream							*_streamin;
	PaStream							*_streamout;
	PaError								_err;
	PaStreamParameters					_inputParam;
	PaStreamParameters					_outputParam;
	IEncode								*_enc;
	bool								_run;
	unsigned char						*_data;
	unsigned char						*_receivedData;
	int									_retenc;
	int									_receivedRetenc;

public:
	AudioManager();
	virtual ~AudioManager();

	virtual int						initAudio();
	virtual void					errorAudio();
	virtual void					initInput();
	virtual void					initOutput();
	virtual int						setupStream();
	virtual int						start();
	virtual int						stop();
	virtual IEncode *				getEnc();
	virtual void					setData(unsigned char *);
	virtual const int				getRetenc() const;
	virtual void					setRetenc(int);
	virtual unsigned char*			getData() const;
	virtual	void					setReceivedData(unsigned char *);
	virtual	unsigned char			*getReceivedData() const;
	virtual	void					setReceivedRetenc(int);
	virtual	int						getReceivedRetenc() const;

	/*virtual void					initialize();
	virtual void					initInputDevice();
	virtual void					initOutputDevice();
	virtual void					openPlayStream();
	virtual void					openRecordStream();
	virtual void					recordSound();
	virtual void					playSound();*/
};