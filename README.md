xredis-server
======


xredis-server 是一个C++开发的redis服务器框架库，使用这个库可以很容易的开发自己的redis协议兼容服务器.


### 依赖
xredis-server 依赖 libevent 做为网络层.


xredis-server源码安装
```bash
git clone https://github.com/0xsky/xredis-server.git
cd xredis-server.git
make
```
使用示例:
```cpp
#include "../src/xRedisServerLib.h"

class xRedisConnect :public xRedisConnectorBase
{
public:
    xRedisConnect();
    ~xRedisConnect();
private:
};

class xRedisServer :public xRedisServerBase
{
public:
    xRedisServer() {

    }
    ~xRedisServer() {

    }

public:
    bool Init()
    {
        CmdRegister();
    }

private:
    bool CmdRegister()
    {
        if (!SetCmdTable("get", (CmdCallback)&xRedisServer::ProcessCmd_get)) return false;
        return true;
    }

    void ProcessCmd_get(xRedisConnect *pConnector)
    {
        if (2 != pConnector->argc) {
            SendErrReply(pConnector, "cmd error:", "error arg");
            return;
        }
        SendBulkReply(pConnector, pConnector->argv[1]);
        return;
    }

private:

};

int main(int argc, char **argv)
{
    xRedisServer xRedis;
    xRedis.Init();
    xRedis.Start("127.0.0.1", 6379);

    while (1) {
        usleep(1000);
    }
    
    return 0;
}

```
### 相关文档

<p>使用示例 [examples](https://github.com/0xsky/xredis-server/tree/master/example) directory for some examples
<p>QQ群: 190107312

<p><p>作者: xSky        
<p>博客: <a href="http://www.0xsky.com/">xSky's Blog</a>

