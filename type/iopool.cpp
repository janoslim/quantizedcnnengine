#include <iostream>
#include "./iopool.h"
#include <utility>
#include <vector>

IOPool::IOPool()
{
    std::fill_n(this->bitmap, 1024, false);
}

IOPool::~IOPool()
{

}

void IOPool::get_access(std::vector<int>& inputVec)
{
    for(int& id : inputVec)
    {
        io_map[id+1]->get_access();
    }
}

void IOPool::finish_input(int id)
{
    io_map[id+1]->ready();
}

void IOPool::add_IO(IO* io_obj)
{
    int id = io_obj->get_ID() + 1;
    if(this->bitmap[id] == false)
    {
        io_map.insert(std::pair<int, IO*>(id, io_obj));
        this->bitmap[id] = true;
    }
}
