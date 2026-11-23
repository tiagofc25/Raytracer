FROM ubuntu:24.04

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        build-essential \
        cmake \
        gdb \
        git \
        ca-certificates \
    && rm -rf /var/lib/apt/lists/*
