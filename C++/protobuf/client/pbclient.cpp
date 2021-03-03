#include "../proto/test.grpc.pb.h"
#include <grpcpp/grpcpp.h>

int main(int argc, char* argv[]) {
    std::unique_ptr<Test::Stub> client = Test::NewStub(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));


    grpc::ClientContext ctx;
    TestRequest req;
    req.set_name("hello");
    TestResponse rsp;
    client->TestRpc(&ctx, req, &rsp);
    std::cout << "count:" << rsp.count() << std::endl;

    return 0;
}