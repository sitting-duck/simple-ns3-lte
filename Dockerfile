# syntax=docker/dockerfile:1
FROM ubuntu:18.04
RUN apt-get update

RUN echo "set nu\nset tabstop=4\nset shiftwidth=4\nset expandtab\nset hlsearch" >> ~/.vimrc

RUN echo 'alias ls="ls -halp"' >> ~/.bashrc
RUN echo 'alias dir="ls -halp"' >> ~/.bashrc
RUN echo 'alias gcc="gcc-8"' >> ~/.bashrc
RUN echo 'alias g++="g++-8"' >> ~/.bashrc

RUN apt-get -y install git gcc-8 g++-8 python3 python3-pip cmake make patch unrar
RUN apt-get -y install python3-dev pkg-config autoconf cvs bzr vim
RUN python3 -m pip install distro requests
RUN git clone https://gitlab.com/nsnam/bake

RUN export BAKE_HOME=`pwd`/bake 
RUN export PATH=$PATH:$BAKE_HOME
RUN export PYTHONPATH=$PYTHONPATH:$BAKE_HOME

COPY / .
RUN python3 /bake/bake.py configure -e "ns-3.34"
RUN python3 /bake/bake.py deploy

#move our simulation(s) into scratch dir in ns3
RUN mv /scratch/** /source/ns-3.34/scratch/

WORKDIR /source/ns-3.34/
./waf -d debug --enable-examples --enable-tests configure