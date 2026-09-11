import os
file_path = "/home/yvessong/Network-Labs/BlackFriday/network-automation/network_backups/CoreSW1/2025-12-15_11:25:05.png"

def parse(file_path):
    with open(file_path, "r") as fp:
        lines_stripped = [line.strip() for line in fp]
        interface_dict = dict()
        interface = None
        
        for line in lines_stripped:
            if "interface" in line:
                interface = line
                interface_dict[interface] = []
            elif "!" in line:
                interface = None
            elif interface != None: 
                interface_dict[interface].append(line)
        print(f"{interface_dict}\n")
if __name__ == "__main__":
    parse(file_path)
