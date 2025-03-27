#!/usr/bin/env bash 
 

 
 
currentDir=$1
 
 

func_install_serviceA_all(){
 
# service output dir : create
mkdir -p /etc/Advantech/susi/service/

# run service dir (at first)
mkdir -p /opt/Advantech/susi/service
cp "$currentDir/Susi_X86_64_Service" "$currentDir/exeSusiService_in_container.sh" "/opt/Advantech/susi/service"


cp "$currentDir/susi_api_server.service" "/etc/systemd/system/"
cd /opt/Advantech/susi/service
# ./exeSusiService_in_container.sh
# systemctl daemon-reload
# systemctl enable susi_api_server
# systemctl start susi_api_server


}



func_install_cJsonLib(){
    
    
 
    cJSON_ZIP=$currentDir/cJSON.zip
    cJSON_dir=$currentDir/cJSON-master

    if [ -f "$cJSON_ZIP" ]; then
    
        # currentDir=${PWD}
  
    	unzip "$cJSON_ZIP"  -d "$currentDir"
 
    	cd "$cJSON_dir"
    	cmake . -DENABLE_CJSON_UTILS=On -DENABLE_CJSON_TEST=Off -DCMAKE_INSTALL_PREFIX=/usr
    	make install                   
 
        cd "$currentDir"

    fi
    
    
    if [ -d "$cJSON_dir" ]; then
     rm -rf "$cJSON_dir"  
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


















