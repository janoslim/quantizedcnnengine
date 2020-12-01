#include "./io.h"
#include <iostream>

IO::IO(int ID)
{
    this->ID = ID;
    this->key = new std::mutex();
    this->key->lock();
    std::cout << ID << std::endl;
}

IO::~IO()
{
    delete this->key;
}

void IO::get_access()
{
    this->key->lock();
    this->key->unlock();
}

void IO::ready()
{
    this->key->unlock();
}

int IO::get_ID()
{
    return this->ID;
}

void IO::set_value(int h, int w, int c, int type, void* value)
{
    this->h = h;
    this->w = w;
    this->c = c;
    this->ty = (Tinfo)type;
    this->io = value;
}

int IO::get_h()
{
    return h;
}

int IO::get_w()
{
    return w;
}

int IO::get_c()
{
    return c;
}

int IO::get_ty()
{
    return ty;
}

int* IO::get_value_i()
{
    return (int *)io;
}

int8_t* IO::get_value_i8()
{
    return (int8_t *)io;
}

int16_t* IO::get_value_i16()
{
    return (int16_t *)io;
}

float* IO::get_value_fp()
{
    return (float *)io;
}