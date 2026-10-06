import os
import time
import sys

# While sleep duration is running.. put program to sleep..
def snapshot():
    child = os.fork()
    if (child == 0):
        os.setsid()
        grandchild = os.fork() # Double fork to create background process (daemon)
        if (grandchild == 0):
            while 1:
                os.system("sudo apt-get update")
                with open():
                time.sleep(5)
        exit(1) # Exit from chilimport os
snapshot()

'''
left = deadline time.time() 
if time.time() > deadline:
    time.sleep(1);
print("It has been 1 second")
    pid = os.fork()
except OSError as e:
    sys.exit(f"Fork failed: {e}")

if pid == 0:
'''
