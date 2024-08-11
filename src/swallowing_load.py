import psutil
import GPUtil

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
    cpu_usage = get_cpu_usage()
    ram_usage = get_ram_usage()
    gpu_load, gpu_temp = get_gpu_load_and_temp()

    print(f"{cpu_usage}")
    print(f"{ram_usage}")

    if gpu_load is not None and gpu_temp is not None:
        print(f"{gpu_load:.2f}")
        print(f"{gpu_temp}")
    else:
        print("GPU information not available")

if __name__ == "__main__":
    main()
