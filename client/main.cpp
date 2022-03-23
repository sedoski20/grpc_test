#include <iostream>
#include "system.grpc.pb.h"

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/security/credentials.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::Status;
using grpc::StatusCode;
using userData::userDataRequest;
using userData::Cpf;
using userData::Data;

std::string getCpfFromUser()
{
    std::cout << "Enter the CPF number or '0' to exit: ";
    std::string cpf;
    std::cin >> cpf;

    if(cpf == "0")
        exit(0);

    return cpf;
}

std::string getAddress()
{
    std::cout << "Enter the addrress to the server or '0' to default: ";
    std::string address;
    std::cin >> address;

    if(address == "0")
        address = "localhost:50051";
    
    return address;
}

void printResponse(Data *response)
{
    std::cout << std::endl;
    std::cout << "-----------------------------------"<< std::endl;
    std::cout << "[name]    : " << response->name()    << std::endl;
    std::cout << "[cpf]     : " << response->cpf()     << std::endl;
    std::cout << "[email]   : " << response->email()   << std::endl;
    std::cout << "[address] : " << response->address() << std::endl;
    std::cout << "-----------------------------------"<< std::endl;
    std::cout << std::endl;
}

void printError(Status &status)
{
    std::string error_string;

    if(status.error_code() == StatusCode::UNAVAILABLE)
        error_string = "Service Unavailable!";
    else
        error_string = status.error_message();

    std::cout << std::endl;
    std::cout << "-----------------------------------"<< std::endl;
    std::cout << error_string << std::endl;
    std::cout << "-----------------------------------"<< std::endl;
    std::cout << std::endl;
}

class userDataRequestClient
{
    public:
        userDataRequestClient(std::shared_ptr<Channel> channel) 
        : stub(userDataRequest::NewStub(channel)){}
        
        Status userDataRequest(const std::string cpf, Data *response)
        {
            Cpf request;
            request.set_cpf(cpf);

            ClientContext context;

            Status status = this->stub->userRequest(&context, request, response);
            return status;
        }

    private:
        std::unique_ptr<userDataRequest::Stub> stub;
};


int main(int, char**) 
{
    const std::string target = getAddress();
    userDataRequestClient request(grpc::CreateChannel(target, grpc::InsecureChannelCredentials()));
    
    while(true)
    {
        std::string cpf = getCpfFromUser();

        //Call the server her and print the response
        Data *response = new Data();
        Status status = request.userDataRequest(cpf, response);

        if(status.ok())
            printResponse(response);
        else
            printError(status);
    }

    return 0;
}


