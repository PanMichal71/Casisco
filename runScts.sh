python -m virtualenv venv
source venv/bin/activate
pip install grpcio
pip install grpcio-tools
pip install pytest

PATH=$PATH:$PWD/build/src/server
echo "Generating python source files"
CASISCO_GRPC_DIR="./test/SCT/casisco_grpc"
mkdir -p $CASISCO_GRPC_DIR
touch $CASISCO_GRPC_DIR/__init__.py
python -m grpc_tools.protoc -I./protos --python_out=$CASISCO_GRPC_DIR --grpc_python_out=$CASISCO_GRPC_DIR ./protos/casisco.proto
cd test/SCT
echo "Running test"
python -m pytest -q -v --tb=long
cd -
