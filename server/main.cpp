#include <iostream>
#include "database.h"
#include "system.pb.h"
#include "system.grpc.pb.h"

#include <grpc/grpc.h>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using grpc::StatusCode;
using userData::userDataRequest;
using userData::Cpf;
using userData::Data;

class UserDataRequestImplementation : public userDataRequest::Service
{
    public:
        Status userRequest(ServerContext* context, const Cpf* request, Data* response)
        {
            bool found = getUser(request, response);

            if(!found)
                return Status(StatusCode::NOT_FOUND, std::string("User not found for CPF: ") + request->cpf());

            return Status::OK;
        } 

    private:
        bool getUser(const Cpf* cpf, Data *data)
        {
            for(User user : users)
            {
                if(user.cpf == cpf->cpf())
                {
                    data->set_name(user.name);
                    data->set_cpf(user.cpf);
                    data->set_email(user.email);
                    data->set_address(user.address);
                    return true;
                }
            }

            return false;
        }
};

void runServer()
{
    std::string server_address = "0.0.0.0:50051";

    UserDataRequestImplementation service;
    ServerBuilder builder;

    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    auto server = builder.BuildAndStart();
    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
}

int main(int, char**) 
{
    runServer();
}
