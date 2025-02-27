#ifndef ACCEPTORTHREAD_H
#define ACCEPTORTHREAD_H

#include <iostream>

namespace CodeCat
{
    class AcceptorThread
    {
    public:
        bool allowAccept = true;
        int server;

        ~AcceptorThread();

        void operator()();
        void log(const char *);
        void log(std::string);
    };
}

#endif