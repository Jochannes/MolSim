echo 'loading xerces.'
module load xerces/3.1
module load papi
export CPLUS_INCLUDE_PATH=/lrz/sys/libraries/xerces/3.1/include/:$CPLUS_INCLUDE_PATH
export CPLUS_INCLUDE_PATH=/scratch/t1221/t1221af/log4cxx_build/apache-log4cxx-0.10.0/src/main/include:$CPLUS_INCLUDE_PATH
export CPLUS_INCLUDE_PATH=/scratch/t1221/t1221af/cppunit-1.12.1/include:$CPLUS_INCLUDE_PATH
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/scratch/t1221/t1221af/log4cxx_build/apache-log4cxx-0.10.0/src/main/cpp/.libs/
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/scratch/t1221/t1221af/cppunit-1.12.1/src/cppunit/.libs/
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/lrz/sys/libraries/xerces/3.1/lib/

echo 'copying LD_LIBRARY_PATH into LIBRARY_PATH'
export LIBRARY_PATH=$LIBRARY_PATH:$LD_LIBRARY_PATH
