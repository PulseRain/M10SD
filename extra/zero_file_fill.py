#! python3

import sys, getopt
import struct
    
def main():
    
    file_name = sys.argv[1]
    total_bytes_size = int(sys.argv[2])
    num_of_1k = total_bytes_size // 1024
    bytes_remain = total_bytes_size % 1024
    byte_array_fill = bytes([65] * 1024)
    one_byte = bytes([65])
    with open(file_name, 'wb') as f:
        for i in range (num_of_1k):
            f.write(num_of_1k)
        
        for i in range(bytes_remain):
            f.write(one_byte)
        f.close()
    
if __name__ == "__main__":
    main()        


