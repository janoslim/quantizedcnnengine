# 프로젝트 이름 설정
project(engine)

# 변수 ROOT 설정
set(ROOT ..)
# 변수 MAIN_DIR 설정
set(MAIN_DIR ../main)
# 변수 NETWORK_DIR 설정
set(NETWORK_DIR ../network)
# 변수 LAYER_DIR 설정
set(LAYER_DIR ../layer)
# 변수 MODEL_DIR 설정
set(MODEL_DIR ../model)
# 변수 TYPE_DIR 설정
set(TYPE_DIR ../type)
# 변수 JSONPARSER_DIR 설정
set(JSONPARSER_DIR ../jsonparser)

# 변수 SOURCE 설정
set(SOURCE ${MAIN_DIR}/main.cpp
        ${NETWORK_DIR}/network.cpp
        ${TYPE_DIR}/io.cpp
        ${TYPE_DIR}/iopool.cpp
        ${TYPE_DIR}/param.cpp
        ${JSONPARSER_DIR}/jsonParser.cpp
        ${JSONPARSER_DIR}/jsonValue.cpp
        ${JSONPARSER_DIR}/jsonValue_constr.cpp
        ${JSONPARSER_DIR}/jsonValue_gs.cpp
        ${JSONPARSER_DIR}/jsonValue_print.cpp
        ${MODEL_DIR}/model.cpp
        ${LAYER_DIR}/activation_layer.cpp
        ${LAYER_DIR}/convolutional_layer.cpp
        ${LAYER_DIR}/dense_layer.cpp
        ${LAYER_DIR}/gemm.cpp
        ${LAYER_DIR}/maxpool_layer.cpp
        ${LAYER_DIR}/softmax_layer.cpp
        )

# 변수 OUTPUT 설정
set(OUTPUT ${ROOT}/engine.out)

SET ( CMAKE_C_COMPILER "g++")

# 최소 cmake 요구 버전
cmake_minimum_required(VERSION 2.8)
# 메세지 설정
message(${CMAKE_PROJECT_NAME})
# 컴파일 옵션
set(CMAKE_CXX_FLAGS "-W -Wall -pthread")

# 빌드 설정
ADD_EXECUTABLE(${OUTPUT} ${SOURCE})