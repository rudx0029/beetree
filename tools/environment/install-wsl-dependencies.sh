#!/bin/bash -xe


if ! cat /etc/issue | grep "Ubuntu 18.04"; then
    echo "Ubuntu 18.04 required for BeeTree."
    exit 1
fi

# download and install apps from debian
sudo apt-get update && apt-get install -y \
  apt-transport-https \
  nodejs \
  npm \
  wget \
  build-essential \
  python3 \
  python3-pip \
  git \
  ninja-build \
  erlang \
  rabbitmq-server

# Python Modules
pip3 install    \
  pyserial      \ # serial communication library for BeeView.
  crcmod        \ # crc generator for BeeTree token generation.
  pika          \ # general purpose messaging protocol for BeeView
  cmake_format    # formats CMake scripting files

# Node JS modules 
sudo npm install --global \
  clang-format    # c/c++ source formatter

mkdir -p ${TOOLS_DIR}
pushd ${TOOLS_DIR}

# install gcc arm toolchain for cortex m series processors
GCC_ARM_URL=https://developer.arm.com/-/media/Files/downloads/gnu-rm/8-2018q4/gcc-arm-none-eabi-8-2018-q4-major-linux.tar.bz2
wget -O gcc-arm-none-eabi.tar.bz2  ${GCC_ARM_URL}
mkdir -p gcc-arm-none-eabi
tar -xvf gcc-arm-none-eabi.tar.bz2 -C gcc-arm-none-eabi --strip-components 1 

# install cmake
CMAKE_URL https://github.com/Kitware/CMake/releases/download/v3.15.4/cmake-3.15.4-Linux-x86_64.sh
wget -O cmake.sh  ${CMAKE_URL}
mkdir -p cmake && chmod +x cmake.sh
./cmake.sh --skip-license --prefix=cmake

# update Paths
echo "PATH=$(pwd)/gcc-arm-none-eabi/bin:${PATH}" >> ~/.bashrc
echo "PATH=$(pwd)/cmake/bin:${PATH}" >> ~/.bashrc

popd