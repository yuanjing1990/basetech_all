#include "GrpcService.h"

#define log(format, ...) printf(format, __VA_ARGS__)

GrpcService::GrpcService(std::string addr, grpc::Service* service) : m_server_address(addr), m_service(service)
{
    grpc::ServerBuilder build;
    build.AddListeningPort(addr, grpc::InsecureServerCredentials());
    build.RegisterService(service);
    m_server = build.BuildAndStart();
    if (m_server == NULL)
    {
        log("Create service on [%s] failed, please check if the address is available.", addr.c_str());
    }
}

GrpcService::~GrpcService()
{
    stopService();
    m_server.reset();
}

bool GrpcService::isServiceStart()
{
    return m_server != NULL;
}

void GrpcService::stopService()
{
    if (isServiceStart())
    {
        m_server->Shutdown();
    }
}