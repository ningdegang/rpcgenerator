
#ifndef GOOGLE_PROTOBUF_COMPILER_CPP_FILE_H__
#define GOOGLE_PROTOBUF_COMPILER_CPP_FILE_H__

#include <memory>
#ifndef _SHARED_PTR_H
#include <google/protobuf/stubs/shared_ptr.h>
#endif
#include <string>
#include <vector>
#include <google/protobuf/stubs/common.h>

namespace google {
namespace protobuf {
  class FileDescriptor;        // descriptor.h
  namespace io {
    class Printer;             // printer.h
  }
}

namespace protobuf {
namespace compiler {
namespace rpc {

class ServiceGenerator;        // service.h

struct Options {
  Options() : safe_boundary_check(false), proto_h(false) {
  }
  string dllexport_decl;
  bool safe_boundary_check;
  bool proto_h;
};

class FileGenerator {
 public:
  // See generator.cc for the meaning of dllexport_decl.
  explicit FileGenerator(const FileDescriptor* file,
                         const Options& options);
  ~FileGenerator();

  void GenerateServiceImplHeader(io::Printer* printer);
  void GenerateServiceImplSource(io::Printer* printer);

 private:
  // Internal type used by GenerateForwardDeclarations (defined in file.cc).
  class ForwardDeclarations;

  // Generate the BuildDescriptors() procedure, which builds all descriptors
  // for types defined in the file.
  void GenerateBuildDescriptors(io::Printer* printer);

  void GenerateNamespaceOpeners(io::Printer* printer);
  void GenerateNamespaceClosers(io::Printer* printer);

  // For other imports, generates their forward-declarations.
  void GenerateForwardDeclarations(io::Printer* printer);

  // Generates top or bottom of a header file.
  void GenerateTopHeaderGuard(io::Printer* printer,
                              const string& filename_identifier);
  void GenerateBottomHeaderGuard(io::Printer* printer,
                                 const string& filename_identifier);


  // Generates generic service definitions.
  void GenerateServiceDefinitions(io::Printer* printer);

  // Generates inline function defintions.
  void GenerateInlineFunctionDefinitions(io::Printer* printer);

  const FileDescriptor* file_;

  google::protobuf::scoped_array<google::protobuf::scoped_ptr<ServiceGenerator> > service_generators_;

  // E.g. if the package is foo.bar, package_parts_ is {"foo", "bar"}.
  vector<string> package_parts_;
  const Options options_;

  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(FileGenerator);
};



}  // namespace rpc 
}  // namespace compiler
}  // namespace protobuf

}  // namespace google
#endif  // GOOGLE_PROTOBUF_COMPILER_CPP_FILE_H__

