#ifndef IOPOOL_H
#define IOPOOL_H

#include <map>
#include "./io.h"

class IOPool
{
private:
    std::map<int, IO*> io_map;
public:
    IOPool();
    ~IOPool();
    void finish_input(int id);
    void add_IO(IO* io_obj);
    void get_access(int id);
};

#endif