import os

file_path= "2025-12-14_16:56:40.png"
def parse():
    with open(file_path,"r") as f:
        line_stripped = [line.strip() for line in f]
        print(line_stripped)

if __name__  == "__main__":
    parse()
