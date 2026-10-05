import os
import time
import sys

# While sleep duration is running.. put program to sleep..

while 1:
    captured = time.time() 
    time.sleep(10)
    
    print(f"Slept at {captured}, it is now {time.time()}")
    
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
