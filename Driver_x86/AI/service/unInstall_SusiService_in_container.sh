#!/usr/bin/env bash 





func_un_install_serviceA_all(){
 
 service_name=susi_api_server.service
    
 STATUS="$(systemctl is-active $service_name)"
 
 if [ "${STATUS}" = "inactive" ] && [ -f "/etc/systemd/system/$service_name" ]; then
    
    
  # 1
#   systemctl stop $service_name
#   systemctl disable $service_name
  
  
  # 2

  rm -rf "/etc/systemd/system/$service_name"
  rm -rf "/usr/local/etc/systemd/system/$service_name"
  rm -rf "~/.config/systemd/user/$service_name"
  rm -rf "/usr/lib/systemd/$service_name"
  rm -rf "/usr/local/lib/systemd/$service_name"
  rm -rf "/etc/init.d/$service_name"
  
  # 3
#   systemctl daemon-reload
#   systemctl reset-failed
  
 # echo "func_un_install_serviceA_all"

 fi
  

}





func_un_install_cJsonLib(){
    

     rm -f "/usr/lib/libcjson_utils.so"
     rm -f "/usr/lib/libcjson_utils.so.1.7.14"
     rm -f "/usr/lib/libcjson_utils.so.1"
     rm -f "/usr/include/cjson/cJSON_Utils.h"
     rm -f "/usr/lib/libcjson.so"
     rm -f "/usr/lib/libcjson.so.1.7.14"
     rm -f "/usr/lib/libcjson.so.1"
     rm -f "/usr/include/cjson/cJSON.h"


     if [ -d "/usr/include/cjson" ]; then
         rmdir "/usr/include/cjson" 
     fi

   
  
}


func_remove_unnecessary_files(){


     dir1=/etc/Advantech/susi/service/
     dir2=/opt/Advantech/susi/service/
 
 
     if [ -d "$dir1" ]; then
     	rm -r "$dir1"
     fi
     
     if [ -d "$dir2" ]; then
     	rm -r "$dir2"
     fi

}



#############################################################



func_un_install_serviceA_all 

func_un_install_cJsonLib

func_remove_unnecessary_files















