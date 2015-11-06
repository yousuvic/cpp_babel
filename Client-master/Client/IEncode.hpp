#ifndef IENCODE_HPP
#define	IENCODE_HPP

#include <iostream>
#include <fstream>
#include "AudioOption.h"

class	IEncode
{
public:
	virtual ~IEncode() {}

	virtual unsigned char	*encodeAudio(const SAMPLE *frame, int *retenc) = 0;
	virtual void			decodeAudio(const unsigned char *data, SAMPLE *out, int retenc) = 0;
};

#endif // !IENCODE_HPP

