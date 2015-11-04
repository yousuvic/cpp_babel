#ifndef IAUDIO_HPP
#define	IAUDIO_HPP

#include <iostream>
#include <fstream>
#include <utility>
#include "IEncode.hpp"

class	IAudio
{
public:
	virtual ~IAudio() {}

	/*	Init	*/
	virtual int						initAudio() = 0;
	virtual void					initInput() = 0;
	virtual void					initOutput() = 0;
	/*	Stream	*/
	virtual int						setupStream() = 0;
	virtual int						start() = 0;
	virtual int						stop() = 0;
	/*	Error*/
	virtual void					errorAudio() = 0;
	/*	Getter	*/
	virtual IEncode *				getEnc() = 0;
	virtual const int				getRetenc() const = 0;
	virtual unsigned char *			getSound() const = 0;
	/*	Setter	*/
	virtual void					setData(unsigned char *) = 0;
	virtual void					setRetenc(int) = 0;
};

#endif // !IAUDIO_HPP
