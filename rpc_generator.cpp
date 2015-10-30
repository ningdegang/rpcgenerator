// Generates  RPC service interface out of Protobuf IDL.

#include <vector>
#include <memory>
#include <utility>
#include <google/protobuf/io/printer.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/descriptor.pb.h>
#include "log.h"

using namespace google::protobuf::compiler::rpc;
bool RpcGenerator::Generate(const google::protobuf::FileDescriptor *file, const std::string &parameter,
        google::protobuf::compiler::GeneratorContext *context, std::string *error) const
{

    if (file->options().cc_generic_services())
    {
        *error = "rpc google proto compiler plugin does not work with generic "
            "services. To generate rpc google APIs, please set \""
            "cc_generic_service = false\".";
        return false;
    }

    vector<pair<string, string> > options;
    ParseGeneratorParameter(parameter, &options);

    Options file_options;

    for (int i = 0; i < options.size(); i++) 
    {
        if (options[i].first == "dllexport_decl") 
        {
            file_options.dllexport_decl = options[i].second;
        } 
        else if (options[i].first == "safe_boundary_check") 
        {
            file_options.safe_boundary_check = true;
        } 
        else 
        {
            *error = "Unknown generator option: " + options[i].first;
            return false;
        }
    }

    std::string basename = google_generator::StripProto(file->name());
    FileGenerator file_generator(file, file_options);


    basename.append("serviceimpl.pb");
    {
        google::protobuf::scoped_ptr<io::ZeroCopyOutputStream> output(
                generator_context->Open(basename + ".h"));
        io::Printer printer(output.get(), '$');
        file_generator.GeneratePBHeader(&printer);
    }

    {
        google::protobuf::scoped_ptr<io::ZeroCopyOutputStream> output(
                generator_context->Open(basename + ".cc"));
        io::Printer printer(output.get(), '$');
        file_generator.GenerateSource(&printer);
    }

    return true;

}

int main(int argc, char *argv[])
{

    log_init("log/", 60, 1);
    RpcGenerator generator;
    return google::protobuf::compiler::PluginMain(argc, argv, &generator);
}
