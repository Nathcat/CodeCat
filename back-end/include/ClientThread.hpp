#ifndef CLIENTTHREAD_HPP
#define CLIENTTHREAD_HPP

#include <string>

namespace CodeCat {
    class ClientThread {
        public:
        int socket;

        ClientThread(int);
        ~ClientThread();

        void operator()();
        void log(const char*);
        void log(std::string);
    };
};

#endif