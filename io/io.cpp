#include "./io.h"

IO::IO(int ID)
{
    this->ID = ID;
    this->key = new std::mutex();
    this->key->lock();
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