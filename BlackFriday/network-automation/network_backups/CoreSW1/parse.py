import os

file_path= "2025-12-15_11:25:05.png"
def parse():
    with open(file_path,"r") as f:
        line_stripped = [line.strip() for line in f]
    print(line_stripped)

if __name__  == "__main__":
    parse()
