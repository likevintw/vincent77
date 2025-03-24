#!/usr/bin/env bash 
 

 
 
currentDir=$1
 
 

func_install_serviceA_all(){
 
# service output dir : create
sudo mkdir -p /etc/Advantech/susi/service/

# run service dir (at first)
sudo mkdir -p /opt/Advantech/susi/service
sudo cp "$currentDir/Susi_X86_64_Service" "$currentDir/exeSusiService.sh" "/opt/Advantech/susi/service"


sudo cp "$currentDir/susi_api_server.service" "/etc/systemd/system/"
sudo systemctl daemon-reload
sudo systemctl enable susi_api_server
sudo systemctl start susi_api_server


}



func_install_cJsonLib(){
    
    
 
    cJSON_ZIP=$currentDir/cJSON.zip
    cJSON_dir=$currentDir/cJSON-master

    if [ -f "$cJSON_ZIP" ]; then
    
        # currentDir=${PWD}
  
    	sudo unzip "$cJSON_ZIP"  -d "$currentDir"
 
    	cd "$cJSON_dir"
    	sudo cmake . -DENABLE_CJSON_UTILS=On -DENABLE_CJSON_TEST=Off -DCMAKE_INSTALL_PREFIX=/usr
    	sudo make install                   
 
        cd "$currentDir"

    fi
    
    
    if [ -d "$cJSON_dir" ]; then
     sudo rm -rf "$cJSON_dir"  
    fi
 
      
}




######################################################################################################
######################################################################################################
######################################################################################################
######################################################################################################
######################################################################################################



#echo "$currentDir"
 

func_install_cJsonLib


func_install_serviceA_all


















