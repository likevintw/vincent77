
FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install -y git python3 python3-pip libjansson4&& \
    rm -rf /var/lib/apt/lists/*
