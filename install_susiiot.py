import os
import sys

def usage():
    print("""
    Usage: script.py [u]
      (Null) : install SUSI 5.0
      u      : uninstall SUSI 5.0
      s      : silent install
    """)

def install_ai_service():
    this_dir = os.path.dirname(os.path.abspath(__file__))
    argument = os.path.join(this_dir, "AI/service")
    target_ai_install_file = os.path.join(argument, "install_SusiService.sh")
    os.system(f'"{target_ai_install_file}" "{argument}"')

def remove_ai_service():
    this_dir = os.path.dirname(os.path.abspath(__file__))
    target_ai_remove_file = os.path.join(this_dir, "AI/service/unInstall_SusiService.sh")
    os.system(f'"{target_ai_remove_file}"')

def install_library():
    this_dir = os.path.dirname(os.path.abspath(__file__))
    linux_lib_dir = "/usr/lib"
    linux_adv_dir = "/usr/lib/Advantech"
    linux_susi_ini_dir = os.path.join(linux_adv_dir, "Susi/ini")
    linux_susiiot_module_dir = os.path.join(linux_adv_dir, "iot/modules")
    
    os.makedirs(linux_susi_ini_dir, exist_ok=True)
    os.system(f'cp -af "{this_dir}/ini/*.ini" "{linux_susi_ini_dir}/"')
    os.system(f'cp -a "{this_dir}/lib*.*" "{linux_lib_dir}/"')
    
    os.makedirs(linux_susiiot_module_dir, exist_ok=True)
    modules = ["libSUSIDrv.so", "libDiskInfo.so", "libSUSIDevice.so"]
    for module in modules:
        os.system(f'cp -af "{this_dir}/modules/{module}" "{linux_susiiot_module_dir}/"')
    
    cpu_name = os.popen("cat /proc/cpuinfo | grep 'model name' | uniq").read()
    if "Intel" in cpu_name:
        os.system(f'cp -af "{this_dir}/modules/libSUSIAIIoT.so" "{linux_susiiot_module_dir}/"')
    
    os.system("ldconfig")

def uninstall_library():
    linux_lib_dir = "/usr/lib"
    linux_adv_dir = "/usr/lib/Advantech"
    libraries = [
        "libSUSI-4.00", "libSUSI-3.02", "libEApi", "libJNISUSI-4.00", 
        "libSUSIDevice", "libSUSIAI", "libjansson", "libSusiIoT"
    ]
    
    for lib in libraries:
        os.system(f'rm -f "{linux_lib_dir}/{lib}.*"')
    
    os.system("ldconfig")
    os.system(f'rm -rf "{linux_adv_dir}"')

def main():
    arg = sys.argv[1] if len(sys.argv) > 1 else ""
    cpu_name = os.popen("cat /proc/cpuinfo | grep 'model name' | uniq").read()
    
    if arg == "":
        uninstall_library()
        remove_ai_service()
        print("""
        *****************************************************************
        *                SOFTWARE SUSI LICENSE AGREEMENT                *
        * Please carefully read the terms and conditions in license.rtf.*
        * Do you agree with above patent declaration?                   *
        *****************************************************************
          [Y] Yes, I agree.  [N] No, I don't agree.
        """)
        ans = input().strip()
        if ans.lower() != "y":
            sys.exit(1)
        if "Intel" in cpu_name:
            print("Install SUSI AI service.")
            install_ai_service()
        print("Install SUSI library.")
        install_library()
        os.system("ldconfig -p | grep 'libSUSI-4.00\|libSUSI-3.02\|libEApi\|libJNISUSI-4.00\|libSUSIDevice\|libjansson\|libSusiIoT\|libSUSIAI'")
    elif arg == "s":
        uninstall_library()
        remove_ai_service()
        if "Intel" in cpu_name:
            print("Install SUSI AI service.")
            install_ai_service()
        print("Install SUSI library.")
        install_library()
        os.system("ldconfig -p | grep 'libSUSI-4.00\|libSUSI-3.02\|libEApi\|libJNISUSI-4.00\|libSUSIDevice\|libjansson\|libSusiIoT\|libSUSIAI'")
    elif arg == "u":
        print("Uninstall SUSI AI service.")
        remove_ai_service()
        print("Uninstall SUSI.")
        uninstall_library()
    else:
        print(f'ERROR: "{arg}" is an invalid input parameter!')
        usage()

if __name__ == "__main__":
    main()