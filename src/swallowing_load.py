import psutil
import GPUtil
import requests
import time

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
            response = requests.post("http://192.168.31.79/update", json=data)
            print(f"Data sent! Status code: {response.status_code}")
        except requests.exceptions.RequestException as e:
            print(f"Failed to send data: {e}")

        time.sleep(0.5)  # Затримка в 5 секунд перед наступною відправкою даних

if __name__ == "__main__":
    main()
