FROM ubuntu:24.04

COPY petalinux_sdk/ /opt/petalinux_sdk/sysroots/

WORKDIR /workspace

RUN export DEBIAN_FRONTEND=noninteractive && \
    apt-get update && \
    apt-get -y install cmake git googletest google-mock python3 python3-venv python3-pip

