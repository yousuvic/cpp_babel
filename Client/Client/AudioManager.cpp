#include "AudioManager.hpp"

AudioManager::AudioManager()
{
	this->_enc = new EncodeManager;
	this->_streamin = NULL;
	this->_streamout = NULL;
	this->_run = true;
}

AudioManager::~AudioManager()
{
	if (this->_enc)
		delete this->_enc;
	if (this->_data)
		delete this->_data;
	if (this->_streamin)
		Pa_CloseStream(this->_streamin);
	if (this->_streamout)
		Pa_CloseStream(this->_streamout);
	Pa_Terminate();
}

int			AudioManager::initAudio()
{
	this->_err = Pa_Initialize();
	if (this->_err != paNoError)
	{
		this->errorAudio();
		return (0);
	}
	this->initInput();
	this->initOutput();
	this->setupStream();
	return (1);
}

void		AudioManager::errorAudio()
{
	if (this->_err != paNoError)
	{
		this->_run = false;
		if (this->_streamin)
		{
			Pa_AbortStream(this->_streamin);
			Pa_CloseStream(this->_streamin);
		}
		if (this->_streamout)
		{
			Pa_AbortStream(this->_streamout);
			Pa_CloseStream(this->_streamout);
		}
		Pa_Terminate();
		std::cerr << "Error !" << std::endl;
		std::cerr << "Error number : " << this->_err << std::endl;
		std::cerr << "Error message : " << Pa_GetErrorText(this->_err) << std::endl;
	}
}

void		AudioManager::initInput()
{
	this->_inputParam.device = Pa_GetDefaultInputDevice();
	this->_inputParam.channelCount = 2;
	this->_inputParam.sampleFormat = PA_TYPE;
	this->_inputParam.suggestedLatency = Pa_GetDeviceInfo(this->_inputParam.device)->defaultLowInputLatency;
	this->_inputParam.hostApiSpecificStreamInfo = NULL;
}

void		AudioManager::initOutput()
{
	this->_outputParam.device = Pa_GetDefaultOutputDevice();
	this->_outputParam.channelCount = 2;
	this->_outputParam.sampleFormat = PA_TYPE;
	this->_outputParam.suggestedLatency = Pa_GetDeviceInfo(this->_outputParam.device)->defaultLowOutputLatency;
	this->_outputParam.hostApiSpecificStreamInfo = NULL;
}

int			recordCallback(const void *input, void *output,
							unsigned long framesPerBuffer,
							const PaStreamCallbackTimeInfo* timeInfo,
							PaStreamCallbackFlags statusFlags,
							void *userData)
{
	AudioManager *dis = (AudioManager*)userData;
	const SAMPLE *in = (const SAMPLE *)input;
	int retenc(0);
	(void)timeInfo;
	(void)statusFlags;
	(void)output;


	dis->setData(dis->getEnc()->encodeAudio(in, &retenc));
	dis->setRetenc(retenc);
	return paContinue;
}

int			playCallback(const void *input, void *output,
						unsigned long framesPerBuffer,
						const PaStreamCallbackTimeInfo* timeInfo,
						PaStreamCallbackFlags statusFlags,
						void *userData)
{
	AudioManager *dis = (AudioManager*)userData;
	SAMPLE	*out = (SAMPLE *)output;
	(void)timeInfo;
	(void)statusFlags;
	(void)input;

	//dis->getEnc()->decodeAudio(dis->getData().first, out, dis->getData().second);
	//dis->getEnc()->decodeAudio(dis->getData(), out, dis->getRetenc());
	dis->getEnc()->decodeAudio(dis->getReceivedData(), out, dis->getReceivedRetenc());
	return paContinue;
}

int			AudioManager::setupStream()
{
	this->_err = Pa_OpenStream(
		&this->_streamin,
		&this->_inputParam,
		NULL,
		SAMPLE_RATE,
		FRAMES_PER_BUFFER,
		paClipOff,
		recordCallback,
		this);
	if (this->_err != paNoError)
	{
		this->errorAudio();
		return (0);
	}
	this->_err = Pa_OpenStream(
		&this->_streamout,
		NULL,
		&this->_outputParam,
		SAMPLE_RATE,
		FRAMES_PER_BUFFER,
		paClipOff,
		playCallback,
		this);
	if (this->_err != paNoError)
	{
		this->errorAudio();
		return (0);
	}
	return (1);
}

int	AudioManager::start()
{
	this->_err = Pa_StartStream(this->_streamin);
	if (this->_err != paNoError)
	{
		this->errorAudio();
		return (0);
	}
	this->_err = Pa_StartStream(this->_streamout);
	if (this->_err != paNoError)
	{
		this->errorAudio();
		return (0);
	}
	std::cout << "Stream started..." << std::endl;
	/*while (this->_run)
	{
		std::cout << "Hit ENTER to quit..." << std::endl;
		if (std::cin.get() == '\n')
			this->_run = false;
	}*/
	return (1);
}

int			AudioManager::stop()
{
	if (this->_streamin)
	{
		this->_err = Pa_StopStream(this->_streamin);
		if (this->_err != paNoError)
		{
			this->errorAudio();
			return (0);
		}
	}
	if (this->_streamout)
	{
		this->_err = Pa_StopStream(this->_streamout);
		if (this->_err != paNoError)
		{
			this->errorAudio();
			return (0);
		}
	}
	return (1);
}

IEncode	*AudioManager::getEnc()
{
	return (this->_enc);
}

void		AudioManager::setData(unsigned char *data)
{
	this->_data = data;
}

const int			AudioManager::getRetenc() const
{
	return (this->_retenc);
}

void		AudioManager::setRetenc(int retenc)
{
	this->_retenc = retenc;
}

unsigned char		*AudioManager::getData() const
{
	return (_data);
}

void				AudioManager::setReceivedData(unsigned char *data)
{
	this->_receivedData = data;
}

unsigned char		*AudioManager::getReceivedData() const
{
	return _receivedData;
}

void					AudioManager::setReceivedRetenc(int retenc)
{
	this->_receivedRetenc = retenc;
}

int						AudioManager::getReceivedRetenc() const
{
	return _receivedRetenc;
}

/*void					AudioManager::initialize()
{
	this->_err = Pa_Initialize();
	if (this->_err != paNoError)
	{
		this->errorAudio();
		return;
	}
}

void					AudioManager::initInputDevice()
{
	this->_inputParam.device = Pa_GetDefaultInputDevice();
	this->_inputParam.channelCount = 2;
	this->_inputParam.sampleFormat = PA_SAMPLE_TYPE;
	this->_inputParam.suggestedLatency = Pa_GetDeviceInfo(this->_inputParam.device)->defaultLowInputLatency;
	this->_inputParam.hostApiSpecificStreamInfo = NULL;
}

void					AudioManager::initOutputDevice()
{
	this->_outputParam.device = Pa_GetDefaultOutputDevice();
	this->_outputParam.channelCount = 2;
	this->_outputParam.sampleFormat = PA_SAMPLE_TYPE;
	this->_outputParam.suggestedLatency = Pa_GetDeviceInfo(this->_outputParam.device)->defaultLowOutputLatency;
	this->_outputParam.hostApiSpecificStreamInfo = NULL;
}

void					AudioManager::openPlayStream()
{
	this->_err = Pa_OpenStream(
		&this->_streamout,
		NULL,
		&this->_outputParam,
		SAMPLE_RATE,
		FRAMES_PER_BUFFER,
		paClipOff,
		playCallback,
		this);
	if (this->_err != paNoError)
	{
		this->errorAudio();
		return;
	}
}

void					AudioManager::openRecordStream()
{
	this->_err = Pa_OpenStream(
		&this->_streamin,
		&this->_inputParam,
		NULL,
		SAMPLE_RATE,
		FRAMES_PER_BUFFER,
		paClipOff,
		recordCallback,
		this);
	if (this->_err != paNoError)
	{
		this->errorAudio();
		return;
	}
}

void					AudioManager::recordSound()
{
	this->_err = Pa_StartStream(this->_streamin);
	if (this->_err != paNoError)
	{
		this->errorAudio();
		return;
	}
}

void					AudioManager::playSound()
{
	this->_err = Pa_StartStream(this->_streamout);
	if (this->_err != paNoError)
	{
		this->errorAudio();
		return;
	}
}*/