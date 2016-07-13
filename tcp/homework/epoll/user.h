/********************************************************************
* author 周翔
* e-mail 604487178@qq.com
* blog http://blog.csdn.net/zhx6044
**********************************************************************/

#ifndef USER_H
#define USER_H

#include <string>

#include "socketheads.h"


/**
 * @brief The User class 连接到服务器的用户
 */
class User
{
public:
    User(int _s_fd, in_addr _ip);
private:

    /**
      支持私聊和群聊
      */
    typedef enum {PRIVATE, ChANNEL} TALKMODEL;

    /**
     * @brief user_name 用户名
     */
    std::string user_name;
    /**
     * @brief ip
     */
    in_addr ip;
    /**
     * @brief s_fd socket描述符
     */
    int s_fd;

    /**
     * @brief talk_s_fd 私聊的对方socket描述符
     */
    int talk_s_fd;
};

#endif // USER_H
