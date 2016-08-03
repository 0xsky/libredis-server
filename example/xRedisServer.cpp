/*
* ----------------------------------------------------------------------------
* Copyright (c) 2015-2016, xSky <guozhw at gmail dot com>
* All rights reserved.
* Distributed under GPL license.
* ----------------------------------------------------------------------------
*/

#include "../src/xRedisServerLib.h"

class xRedisClient :public xRedisConnectorBase
{
public:
    xRedisClient();
    ~xRedisClient();
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

    void ProcessCmd_get(xRedisClient *pConnector)
    {
        if (2 != pConnector->argc) {
            SendErrReply(pConnector, "cmd error:", "error arg");
            return;
        }
        SendBulkReply(pConnector, "hello world");
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

