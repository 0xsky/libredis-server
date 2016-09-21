/*
* ----------------------------------------------------------------------------
* Copyright (c) 2015-2016, xSky <guozhw at gmail dot com>
* All rights reserved.
* Distributed under GPL license.
* ----------------------------------------------------------------------------
*/

#include "../src/xRedisServerLib.h"
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

#include <unistd.h>
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
        _storage_clear();
    }

public:
    bool Init()
    {
        CmdRegister();return true;
    }

private:
    bool CmdRegister()
    {
        if (!SetCmdTable("get", (CmdCallback)&xRedisServer::ProcessCmd_get)) return false;
        if (!SetCmdTable("del", (CmdCallback)&xRedisServer::ProcessCmd_del)) return false;
        if (!SetCmdTable("cls", (CmdCallback)&xRedisServer::ProcessCmd_clear)) return false;
        return SetCmdTable("set", (CmdCallback)&xRedisServer::ProcessCmd_set);
    }

    void ProcessCmd_clear(xRedisConnect *pConnector){
        if (1 != pConnector->argc) {
            SendErrReply(pConnector, "cmd error:", "error arg");
            return;
        }
        _storage_clear();
        SendBulkReply(pConnector, "cleared");
        return;
    }

    void ProcessCmd_del(xRedisConnect *pConnector){
        if (2 != pConnector->argc) {
            SendErrReply(pConnector, "cmd error:", "error arg");
            return;
        }

        _storage_del(pConnector->argv[1]);
        SendBulkReply(pConnector, "deleted");
        return;
    }

    void ProcessCmd_get(xRedisConnect *pConnector)
    {
        if (2 != pConnector->argc) {
            SendErrReply(pConnector, "cmd error:", "error arg");
            return;
        }
        const char* p_data = (const char*)_storage_get(pConnector->argv[1]);
        SendBulkReply(pConnector, p_data);
        return;
    }

    void ProcessCmd_set(xRedisConnect *pConnector){
        if(3 != pConnector->argc){
            SendErrReply(pConnector, "cmd error:", "err arg");
            return;
        }
        _storage_set(pConnector->argv[1], pConnector->argv[2], strlen(pConnector->argv[2]));
        SendBulkReply(pConnector, "OK");
        return;
    }

    void*
    _storage_get(const char* key){
        std::map<string, void*>::iterator iter = _storage.find(key);

        if(iter != _storage.end()){
            return iter->second;
        }

        static char* no_data = (char *) "No data";
        return (void*)no_data;
    }

    void
    _storage_set(const char* key,void *value, size_t val_len){
        if(key == NULL|| value == NULL||val_len == 0)return;

        char *p = (char*)malloc(val_len + 1);
        memcpy(p, value, val_len);
        p[val_len] = '\0';
        _storage_del(key);
        _storage.insert(std::pair<const char* ,void*>(key, p));
    }

    void
    _storage_del(const char* key){
        std::map<string, void*>::iterator iter = _storage.find(key);
        if(iter != _storage.end()){
            free(iter->second);
            _storage.erase(key);
        }
    }

    void
    _storage_clear(){
        for (std::map<string ,void*>::iterator it = _storage.begin(); it != _storage.end() ;++it) {
            free(it->second);
        }
        _storage.clear();
    }

private:
    std::map<string ,void*> _storage;
};

static void
_print_welcome(){
    fprintf(stdout, "                  " "********************kMemServer******************" "\n"
                    "                  " "*                                              *" "\n"
                    "                  " "*                                              *" "\n"
                    "                  " "*                    Welcome                   *" "\n"
                    "                  " "*                                              *" "\n"
                    "                  " "*                                              *" "\n"
                    "                  " "************************************************" "\n\n\n");
    fflush(stdout);
}

int main(int argc, char **argv)
{
    xRedisServer xRedis;
    void *r_val;

    _print_welcome();
    xRedis.Init();
    xRedis.Start("127.0.0.1", 7788);
    pthread_join(xRedis.get_tid(), &r_val);
}

