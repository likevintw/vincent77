#!/usr/bin/env bash 





func_un_install_serviceA_all(){
 
 service_name=susi_api_server.service
    
 STATUS="$(systemctl is-active $service_name)"
 
 if [ "${STATUS}" = "inactive" ] && [ -f "/etc/systemd/system/$service_name" ]; then
    
    
  # 1
  sudo systemctl stop $service_name
  sudo systemctl disable $service_name
  
  
  # 2

  sudo rm -rf "/etc/systemd/system/$service_name"
  sudo rm -rf "/usr/local/etc/systemd/system/$service_name"
  sudo rm -rf "~/.config/systemd/user/$service_name"
  sudo rm -rf "/usr/lib/systemd/$service_name"
  sudo rm -rf "/usr/local/lib/systemd/$service_name"
  sudo rm -rf "/etc/init.d/$service_name"
  
  # 3
  sudo systemctl daemon-reload
  sudo systemctl reset-failed
  
 # echo "func_un_install_serviceA_all"

 fi
  

}





func_un_install_cJsonLib(){
    

     sudo rm -f "/usr/lib/libcjson_utils.so"
     sudo rm -f "/usr/lib/libcjson_utils.so.1.7.14"
     sudo rm -f "/usr/lib/libcjson_utils.so.1"
     sudo rm -f "/usr/include/cjson/cJSON_Utils.h"
     sudo rm -f "/usr/lib/libcjson.so"
     sudo rm -f "/usr/lib/libcjson.so.1.7.14"
     sudo rm -f "/usr/lib/libcjson.so.1"
     sudo rm -f "/usr/include/cjson/cJSON.h"


     if [ -d "/usr/include/cjson" ]; then
         sudo rmdir "/usr/include/cjson" 
     fi

   
  
}


func_remove_unnecessary_files(){


     dir1=/etc/Advantech/susi/service/
     dir2=/opt/Advantech/susi/service/
 
 
     if [ -d "$dir1" ]; then
     	sudo rm -r "$dir1"
     fi
     
     if [ -d "$dir2" ]; then
     	sudo rm -r "$dir2"
     fi

}



#############################################################



func_un_install_serviceA_all 

func_un_install_cJsonLib

func_remove_unnecessary_files















