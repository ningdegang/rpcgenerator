#!/bin/bash
protoc  --rpc_out=. --plugin=protoc-gen-rpc=rpc_generator  $1
