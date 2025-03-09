import psutil
import GPUtil
import socket
import time
import json

def get_cpu_usage():
    return psutil.cpu_percent(interval=1)

def get_ram_usage():
    memory = psutil.virtual_memory()
    return memory.percent

def get_gpu_load_and_temp():
    gpus = GPUtil.getGPUs()
    if gpus:
        gpu = gpus[0]  # Якщо кілька GPU, береться перший
        return gpu.load * 100, gpu.temperature
    else:
        return None, None  # Якщо GPU немає

def main():
    server_ip = '192.168.31.79'
    server_port = 55555  # Порт, на якому слухає Arduino

    while True:
        cpu_usage = get_cpu_usage()
        ram_usage = get_ram_usage()
        gpu_load, gpu_temp = get_gpu_load_and_temp()

        data = {
            'cpu_usage': cpu_usage,
            'ram_usage': ram_usage,
            'gpu_load': gpu_load,
            'gpu_temp': gpu_temp
        }

        try:
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
                s.connect((server_ip, server_port))
                s.sendall(json.dumps(data).encode('utf-8'))
                print("Data sent!")
        except Exception as e:
            print(f"Failed to send data: {e}")

        time.sleep(0.5)  # Затримка в 0.5 секунд перед наступною відправкою даних

if __name__ == "__main__":
    main()
