# This is a configuration file that connects to the Cisco CML server
# and into the lab devices
# 1. IMPORT

import os # OS for file and directory creation. This is how I will be saving my created files 
from datetime import datetime  # Datetime library allows me to log each configuration file based on time created, or modified
from netmiko import ConnectHandler, redispatch # netmiko allows me to connect to external devices
from configConstants.device_config import devices, CML_SERVER # Hidden in a land far far away.. rests the information to access 
import time
# the server and devices (for security of course)

# 2. CREATE CONSTANTS
# At this stage it's its important to create and set the time immediately at the top of the file.
# This is what will be used to mark the time of the configurations within the files you create and
# any update that follows after

current_time = datetime.now()
formatted_time = current_time.strftime("%Y/%m/%d %H:%M:%S")
print(formatted_time)


# 3. CREATE FUNCTIONS FOR CONNECTION ACCESS
# At this point, I could do everything in a try-catch block, but let's
# be a little more organized and modular 

# The first function will allow me to connect to the remote CML server

def connect_to_server():
    try:  
        print(f"Attempting to connect to {CML_SERVER['host']}..")
        conn = ConnectHandler(**CML_SERVER,session_log="cml_log.txt")     # connect to the CML server via the handler we imported
        print(f"Connection to {CML_SERVER['host']} succeeded!..")
        return conn
    except Exception as err:    # Important to 
        print(f"Failed to connect to {CML_SERVER['host']}..")
        return None

# The second function runs BECAUSE I'm now connected to the server,
# Since I know the format, I begin with parsing
# This is where I will be sending commands to the actual CML server

def command_to_server(cml_connect):
    
    # View Device list, 
    # It's important to do this as I may be sending commands to a device thats doesnt exist
    try:
        print("Sending command to CML server.. List")
        response = cml_connect.send_command("list")     
        lines = response.split('\n') 
    
        for index in range(len(lines)): # Run through the lines and search if the device I want exists!
            current_line = lines[index]
            if "Black Friday Scenario" not in current_line: # Skip irrelevant lines and headers
                continue;
            print("Found Black Friday Scenario")
            
            #position_idx = current_line.find(CORESW1) # Loop through device list until found, else return false
             
            #if position_idx >= 0:
            for device in devices:
                node_name = device["node"]
                if node_name in current_line:
                    print("Found CoreSW1..")
                    print("Opening CoreSW1...")
                    cml_connect.send_command_timing(f"open /Black Friday Scenario/{node_name}/0", read_timeout=600) # Once the device exists
                    time.sleep(2)
                    
                    cml_connect.write_channel("en")
                    cml_connect.write_channel("\n")
                    time.sleep(1)

                    redispatch(cml_connect, device_type="cisco_ios", session_prep=False) # This is crucial, connect handler expects a terminal CLI, but since we've switches devices, its important to redispatch to the cisco driver
                
                    cml_connect.send_command("terminal length 0", expect_string=r"[>#]")
                    output = cml_connect.send_command("show running-config", expect_string=r"[>#]", read_timeout=30)
                
                    print(output)
                    return output

                #prompt = cml_connect.find_prompt()
                #print(f"On device prompt: {prompt}")
                #cml_connect.send_command("terminal length 0", expect_string=r"[>#]")
                #cml_connect.find_prompt(delay_factor=1)
    except Exception as err:
        print(f"Failed to write prompt to {CML_SERVER['host']}..")
        return None

    print("Could not find CoreSW1")
    return False

if  __name__ == "__main__":
    conn = connect_to_server()
    if conn is not None:
        command_to_server(conn)

