export LD_LIBRARY_PATH=$(pwd):$LD_LIBRARY_PATH

cp libSUSI-4.00.so ../../ &&\
cp libSUSI-4.00.so.1 ../../ &&\
cp libjansson.so ../../ &&\
cp libjansson.so.4 ../../ &&\
cp libSusiIoT.so ../../ &&\
cp libSUSIAI.so ../../ 

file SUSI4.2.23737/Driver/libSusiIoT.so.1.0.0 &&\
file SUSI4.2.24139/Driver/libSusiIoT.so.1.0.0 &&\
file SUSI5.0.23985/Driver/libSusiIoT.so.1.0.0 &&\
file SUSI5.0.24139/Driver/libSusiIoT.so.1.0.0

cp SUSI5.0.23985/Driver/libSusiIoT.so.1.0.0