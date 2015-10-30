#!/bin/bash
 protoc --proto_path=.  --proto_path=/data/common/3rd/protobuf-2.4.1/include --spprpc_out=.  --plugin=protoc-gen-spprpc=/data/shmilychen/protobuf/cppplugin/spp_rpc_plugin  $1
