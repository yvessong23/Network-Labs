import os
file_path = "/home/yvessong/Network-Labs/BlackFriday/network-automation/network_backups/CoreSW1/2025-12-15_11:05:16.png"

def parse(file_path):
    with open(file_path, "r") as fp:
        lines_stripped = [line.strip() for line in fp]
        interface_dict = dict()
        for line in lines_stripped:
            interface = line
            if "interface" in line:
                interface_dict[interface] = line
                print(interface_dict)

if __name__ == "__main__":
    parse(file_path)
