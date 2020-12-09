rm core
cd build
make
cd ..
./engine reluMnist.json reluMnistFloat.weights mnist0.bin
