fndef GOOGLE_PROTOBUF_COMPILER_RPC_GENERATOR_H__
#define GOOGLE_PROTOBUF_COMPILER_RPC_GENERATOR_H__

#include <string>
#include <google/protobuf/compiler/code_generator.h>

namespace google {
namespace protobuf {
namespace compiler {
namespace rpc {

// CodeGenerator implementation which generates a C++ source file and
// header.  If you create your own protocol compiler binary and you want
// it to support C++ output, you can do so by registering an instance of this
// CodeGenerator with the CommandLineInterface in your main() function.
class RpcGenerator : public CodeGenerator {
 public:
  RpcGenerator();
  ~RpcGenerator();

  // implements CodeGenerator ----------------------------------------
  bool Generate(const FileDescriptor* file,
                const string& parameter,
                GeneratorContext* generator_context,
                string* error) const;

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(RpcGenerator);
};

}  // namespace rpc 
}  // namespace compiler
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_Rpc_GENERATOR_H__

