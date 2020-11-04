#ifndef IO_H
#define IO_H

#include <string>
#include <mutex>

class IO
{
private:
	int ID;
	std::mutex* key;
public:	
	IO(int ID);
	~IO();
	int get_ID();
	void get_access();
	void ready();
};

#endif
