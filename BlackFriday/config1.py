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
formatted_time = current_time.strftime("%Y-%m-%d_%H:%M:%S")
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
            
            #if position_idx >= 0:
            for device in devices:
                node_name = device["node"]
                if node_name in current_line:
                    print("Found CoreSW1..")
                    print("Opening CoreSW1...")
                    cml_connect.send_command_timing(f"open /Black Friday Scenario/{node_name}/0", read_timeout=600) # Once the device exists
                    print(f"Connected to {node_name}")
                    return node_name 
    except Exception as err:
        print(f"Failed to write prompt to {CML_SERVER['host']}..")
        return None

    print("Could not find {node_name}")
    return False

def get_running_config(cml_connect):
    cml_connect.write_channel("\r")
    cml_connect.write_channel("en")
    redispatch(cml_connect, device_type="cisco_ios", session_prep=False) # Redispatching allows us to change Netmiko class to Cisco CLI
    cml_connect.send_command("terminal length 0")
    output = cml_connect.send_command("show running-config", expect_string=r"[>#]") 
    return output

def save_config(output, node):
    # check if filePath exists, find filePath for device
    network_path = f"network-automation/network_backups/{node}"
    #for root, dirs, files in os.walk("."):
    #for direct in dirs:
    if os.path.isdir(network_path):
        print(f"The directory {network_path} exists!")
        working_dir = os.chdir(network_path) # Change directory
        print(f"Current directory {os.getcwd()}")
        try:
            file_path = formatted_time+".png" # Files named by most recent time
            with open(file_path, 'w') as fp:  # write config
                fp.write(output)
                print("File created successfully")
        except FileExistsError:
            print("This {file_path} exists!")
    else: 
        print(f"The directory {network_path} does not exist")
    return file_path

def parse_config(file_path):
    try: 
        with open(file_path, "r") as fp:
            interface_dict = dict()
            content = fp.read()
            if content == "interface":
                interface = content
                return print(interface)
               # for line in content:
                #    interface_dict[interface] = line

                    

    except FileNotFoundError:
        print("{file_path} not found!")
        return

if  __name__ == "__main__":
    conn = connect_to_server()
    if conn is not None:
        node = command_to_server(conn)
        #time.sleep(2)
        output = get_running_config(conn)
        file_path = save_config(output, node)
        parse_config(file_path)
        
