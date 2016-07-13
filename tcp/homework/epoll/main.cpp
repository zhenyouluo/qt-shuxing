#include "epoll_server.h"

#include <iostream>



int main(int /*argc*/, char const **/*argv[]*/)
{
    std::cout << "server" << std::endl;
    Epoll_server s(18090);
    if (s.bind() < 0) {
        return -1;
    }
    return s.listen();
}
