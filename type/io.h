#ifndef IO_H
#define IO_H

#include <string>
#include <mutex>
#include "type.h"

class IO
{
private:
	int ID;
	std::mutex* key;

	int h;
	int w;
	int c;
	Tinfo ty;

	void* io;
	
public:	
	IO(int ID);
	~IO();
	int get_ID();
	void get_access();
	void ready();

	void set_value(int h, int w, int c, int type, void* value);
	int get_h();
	int get_w();
	int get_c();
	int get_ty();
	int* get_value_i();
	int8_t* get_value_i8();
	int16_t* get_value_i16();
	float* get_value_fp();
	//dp* get_value_dp();
	void print_io();
};

#endif
