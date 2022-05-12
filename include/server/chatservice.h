//
// Created by Cmf on 2022/5/11.
//

#ifndef CLUSTERCHAT_CHATSERVICE_H
#define CLUSTERCHAT_CHATSERVICE_H

#include <unordered_map>
#include <functional>
#include "muduo/net/TcpConnection.h"
#include "json.hpp"
#include "public.h"

using json = nlohmann::json;
using MsgHandler = std::function<void(const muduo::net::TcpConnectionPtr&,json&, muduo::Timestamp)>;

class ChatService
{
public:
    //获取单例对象接口函数
    static ChatService&Instance();
    //处理登录
    void Login(const muduo::net::TcpConnectionPtr&conn,json&js, muduo::Timestamp timestamp);
    //处理注册
    void Reg(const muduo::net::TcpConnectionPtr&conn,json&js, muduo::Timestamp timestamp);
    //获取消息id对应的处理函数
    MsgHandler GetHandler(int msgId);
    ~ChatService();
private:
    ChatService();//单例
private:
    std::unordered_map<int,MsgHandler> msgHandlerMap_;  //一个消息id对应一个处理函数
};

#endif //CLUSTERCHAT_CHATSERVICE_H