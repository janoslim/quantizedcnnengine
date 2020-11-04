#include <iostream>
#include "./iopool.h"
#include <utility>

IOPool::IOPool()
{
}

IOPool::~IOPool()
{

}

void IOPool::get_access(int id)
{
    io_map[id]->get_access();
}

void IOPool::finish_input(int id)
{
    io_map[id]->ready();
}

void IOPool::add_IO(IO* io_obj)
{
    io_map.insert(std::pair<int, IO*>(io_obj->get_ID(), io_obj));
}

