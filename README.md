[![Author](https://img.shields.io/badge/author-@0xsky-blue.svg?style=flat)](http://www.0xsky.com/)
[![Platform](https://img.shields.io/badge/platform-Linux,%20BSD,%20OS%20X,%20Windows-green.svg?style=flat)](https://github.com/0xsky/xredis-server) 
[![NoSQL](https://img.shields.io/badge/db-NoSQL-pink.svg?tyle=flat)](https://github.com/0xsky/xredis-server) 
[![License](https://img.shields.io/badge/license-MIT-yellow.svg?style=flat)](LICENSE)

###[中文说明](README-cn.md)
xredis-server
======


redis-server is a redis server framework library write by C++, using this library you can develop redis protocol compatible server easily.


### Dependencies
xredis-server requires libevent


###install
```bash
git clone https://github.com/0xsky/xredis-server.git
cd xredis-server
make
```
###build example
```bash
make example
```

###usage:
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
    std::string pass = "123456";
    xRedis.SetPassword(pass);
    xRedis.Start("127.0.0.1", 6479);

    while (1) {
        usleep(1000);
    }
    
    return 0;
}

```
### DOC

<p>example [examples](https://github.com/0xsky/xredis-server/tree/master/example) directory for some examples
<p>QQ Group: 190107312

<p><p>author: xSky        
<p>Blog: <a href="http://www.0xsky.com/">xSky's Blog</a>

