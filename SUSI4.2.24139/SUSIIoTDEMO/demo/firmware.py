import os

# 定義 /sys/firmware/efi/efivars 的路徑
efivars_path = '/sys/firmware/efi/efivars'

# 檢查 efivars 目錄是否存在
if os.path.exists(efivars_path) and os.path.isdir(efivars_path):
    # 列出 efivars 目錄中的所有檔案
    for filename in os.listdir(efivars_path):
        file_path = os.path.join(efivars_path, filename)

        # 只讀取檔案，跳過目錄
        if os.path.isfile(file_path):
            try:
                with open(file_path, 'rb') as f:  # 以二進位模式讀取檔案
                    content = f.read()
                    print(f"File: {filename}")
                    print(f"Content: {content.hex()}")  # 以十六進位輸出檔案內容
            except Exception as e:
                print(f"Failed to read {filename}: {e}")
else:
    print(f"{efivars_path} does not exist or is not a directory.")
