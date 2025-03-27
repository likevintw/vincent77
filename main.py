import importlib.util

# 指定 .pyc 檔案的路徑
pyc_path = "susiiot.cpython-38.pyc"

# 載入 .pyc 模組
spec = importlib.util.spec_from_file_location("susiiot", pyc_path)
susiiot = importlib.util.module_from_spec(spec)
spec.loader.exec_module(susiiot)

# 呼叫 susiiot 中的函式 (假設 susiiot.py 內有 `init` 函式)
handler = susiiot.SusiIot()
print(handler.get_susi_information_string())
