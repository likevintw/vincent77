#!/usr/bin/env bash 
 


 
 

func_install_serviceA_all(){

#sudo systemctl stop susi_api_server.service


# service output dir : create
sudo mkdir -p /etc/Advantech/susi/service/

# run service dir (at first)
sudo mkdir -p /opt/Advantech/susi/service
sudo cp Susi_Jetson_Service exeSusiService.sh /opt/Advantech/susi/service


sudo cp susi_api_server.service /etc/systemd/system/
sudo systemctl daemon-reload
sudo systemctl enable susi_api_server
sudo systemctl start susi_api_server


}



func_install_serviceA_all

















