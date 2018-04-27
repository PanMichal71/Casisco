PATH=$PATH:$PWD/build/src/server
echo $PATH
cd test/SCT
python -m pytest -q -v
cd -
