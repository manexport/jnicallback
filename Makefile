## asr Makefile ##
WORK_DIR=/home/appadmin/AsrBridge
JDK_PATH=/opt/cui/jdk1.8.0_162
CC=g++
#AR=ar

#FILE_NAME=$(src)
FILE_NAME=src/AsrBridge.cpp
INC_PATH= -I$(WORK_DIR)/include\
          -I$(WORK_DIR)/include/ASR\
          -I$(JDK_PATH)/include \
	  -I$(JDK_PATH)/include/linux \
          -I$(WORK_DIR)/src/include \


SRC_PATH=$(WORK_DIR)/src
OBJ_PATH=.
TARGET=$(basename $(FILE_NAME)).so
LIB_PATH=$(WORK_DIR)/lib
EXTERN_PATH=$(WORK_DIR)/extern/lib
TARGET_PATH=./

CPPFLAGS1=-Wall -O0 -fPIC -g -D__LINUX__ -Wno-unknown-pragmas -D_GLIBCXX_USE_CXX11_ABI=0  -std=c++11
CPPFLAGS= $(CPPFLAGS1) $(LIB_PATH)/libBDSpeechSDK.a $(EXTERN_PATH)/libcurl.a $(EXTERN_PATH)/libiconv.a $(EXTERN_PATH)/libz.a $(EXTERN_PATH)/libssl.a $(EXTERN_PATH)/libcrypto.a $(EXTERN_PATH)/libuuid.a  /opt/cui/jdk1.8.0_162/jre/lib/amd64/server/libjvm.so  -lrt -ldl -lpthread
SRC_FILE=$(shell cd $(SRC_PATH)&&echo *.cpp)
SRC:=$(foreach n,$(SRC_FILE),$(SRC_PATH)/$(n))

OBJ_FILE=$(SRC_FILE:.cpp=.o)
OBJ:=$(foreach n,$(OBJ_FILE),$(OBJ_PATH)/$(n))
	          
DEP_FILE=$(SRC_FILE:.cpp=.d)
DEP:=$(foreach n,$(DEP_FILE),$(OBJ_PATH)/$(n))

$(TARGET):$(SRC)
	$(CC) -shared -o $(TARGET)  ./$(FILE_NAME) $(INC_PATH) $(CPPFLAGS) 
	-mv $@ $(TARGET_PATH)/deploy/libAsrBridge.so
clean:
	-rm -f $(OBJ)
	-rm -f $(TARGET)
	-rm -f $(WORK_DIR)/deploy/*.so

cleanall:
	-rm -f $(OBJ)
	-rm -f $(TARGET)


