#ifndef FRONTENDTHREAD_H
#define FRONTENDTHREAD_H

#include <iostream>

namespace CodeCat
{
    class FrontEndThread
    {
    public:
        void operator()();
        void log(const char*);
    };
}

#endif