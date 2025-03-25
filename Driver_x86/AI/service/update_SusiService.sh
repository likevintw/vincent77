#!/usr/bin/env bash 
 
 
sudo systemctl stop susi_api_server.service


sudo mkdir -p /etc/Advantech/susi/service

sudo mkdir -p /opt/Advantech/susi/service

sudo rm -rf   /opt/Advantech/susi/service/*

 
sudo cp Susi_X86_64_Service exeSusiService.sh   /opt/Advantech/susi/service


sudo cp susi_api_server.service /etc/systemd/system/

 
sudo systemctl daemon-reload
sudo systemctl enable susi_api_server
sudo systemctl start susi_api_server










