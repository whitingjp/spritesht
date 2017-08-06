#/usr/bin/bash
set -e
mkdir input
pushd input
curl -O ftp://ftp.simplesystems.org/pub/libpng/png/src/libpng12/libpng-1.2.57.tar.gz
tar -xzf libpng-1.2.57.tar.gz
ln -s libpng-1.2.57 libpng
pushd libpng
make -f scripts/makefile.darwin
popd
git clone --depth=1 git@github.com:madler/zlib
pushd zlib
./configure --static
make
popd
