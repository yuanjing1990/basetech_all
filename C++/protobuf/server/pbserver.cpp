#include "test.grpc.pb.h"
#include "GrpcService.h"
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>

class TestImpl : public Test::Service {
    std::vector<std::string> members;
    ::grpc::Status TestRpc(::grpc::ServerContext* context, const ::TestRequest* request, ::TestResponse* response) {
        members.push_back(request->name());
        std::for_each(members.begin(), members.end(), [](auto e)-> void {std::cout << e << std::endl;});
        response->set_count(members.size());
        return grpc::Status::OK;
    }
};

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  TestImpl service;

  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();
  grpc::ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
}

int main(int argc, char* argv[]) {
    // RunServer();
    TestImpl service;
    GrpcService svr("0.0.0.0:50051", &service);
    char q;
    std::cin >> q;
    return 0;
}