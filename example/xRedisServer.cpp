/*
* ----------------------------------------------------------------------------
* Copyright (c) 2015-2016, xSky <guozhw@gmail.com>
* All rights reserved.
* Distributed under GPL license.
* ----------------------------------------------------------------------------
*/

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
    string pass = "xsky";
    xRedis.SetAuth(pass);
    xRedis.Start("127.0.0.1", 6479);

    while (1) {
        usleep(1000);
    }
    
    return 0;
}

