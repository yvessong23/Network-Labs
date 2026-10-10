import os
import time
import sys
import datetime as dt

LOG_DIR = "/var/log/jeffG"
LOG_PATH = f"{LOG_DIR}/apt_get_update.log"

# 1. Setup the environment once before the heavy lifting begins
os.system(f"sudo mkdir -p {LOG_DIR}") 

# While sleep duration is running.. put program to sleep..
def snapshot():
    child = os.fork()
    if (child == 0):
        os.setpgid(0,0)
        grandchild = os.fork() # Double fork to create background process (daemon)
        if (grandchild == 0):
            os.setpgid(0,0)
            while 1:
                try:
                    os.system("sudo apt-get update")
                    with open(f"{LOG_PATH}", "w") as log_file:
                        log_file.write(f"Updated apt configs at {dt.datetime.now()}")
                except OSError as system_error:
                    print("There was an error.. now exiting")
                    os._exit(1)
                    null_dev = os.open(os.devnull,os._RDWR) # Open /dev/null 
                    for fd in (0, 1, 2):                    # Point file desc to /dev/null to prevent FD leaks
                        os.dup2(null_dev, fd) 
                    os.close(null_dev)
                #time.sleep(5) # Every 12 hours run and update again
    print("Child exiting")
    os.wait()
    os._exit(0) # Exit from child

snapshot()
