RO=`pwd`
LIBDIR=${RO}/thirdparty
OPENSSL_DIR=${LIBDIR}/openssl-3.0.5
PROTOBUF_DIR=${LIBDIR}/protobuf-3.21.9
INSTALL_DIR=${RO}/lib
# SHDIR=./thirdparty
echo ${LIBDIR}


cd ${LIBDIR}
if [ -d ${PROTOBUF_DIR} ];
then 
    echo "protobuf compile";
else
    unzip protobuf-cpp-3.21.9.zip
    cd ${PROTOBUF_DIR}/cmake && mkdir build && cd build
    cmake .. -DCMAKE_CXX_FLAGS="-fPIC" -DCMAKE_INSTALL_PREFIX=${INSTALL_DIR}
    make -j 10 && make install -j 5
   # make install -j 5
fi;

cd ${LIBDIR}
if [ -d ${OPENSSL_DIR} ];
then 
    echo "openssl compile";
else
    tar -xvf openssl-3.0.5.tar.gz
    cd ${OPENSSL_DIR}
    ./Configure --prefix=${INSTALL_DIR}
    make -j 10 && make install -j 5
   # make install -j 5
fi;




# tar -xvf openssl-3.0.5.tar.gz 
# unzip protobuf-cpp-3.21.9.zip 

# cd ${LIBDIR}/thirdparty/openssl-3.0.5
# ./Configure --prefix=${LIBDIR}/lib
# cd ${LIBDIR}/thirdparty/protobuf-3.21.9/cmake
# mkdir build
# cd build