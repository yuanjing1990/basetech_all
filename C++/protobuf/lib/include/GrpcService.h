#ifndef GRPC_SERVICE_H_
#define GRPC_SERVICE_H_

#include <string>
#include <grpcpp/grpcpp.h>

class GrpcService
{
public:
    GrpcService(std::string addr, grpc::Service* service);
    ~GrpcService();

    bool isServiceStart();
    void stopService();

private:
    std::string m_server_address;
    std::unique_ptr<grpc::Server> m_server;
    grpc::Service* m_service;
};

#endif // GRPC_SERVICE_H_