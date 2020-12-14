rm core
cd build
make
if [ $? -ne 0 ]; then
	exit 1
fi
cd ..
./engine reluMnist.json reluMnistFloat.weights mnist0.bin
