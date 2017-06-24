#! python3

import sys, getopt
import struct
    
def main():
    
    file_name = sys.argv[1]
    total_bytes_size = int(sys.argv[2])
    trunk_size = 65536
    num_of_trunk = total_bytes_size // trunk_size
    bytes_remain = total_bytes_size % trunk_size
    
    byte_array_fill = bytes([65] * trunk_size)
    one_byte_fill = bytes([65])
    
    with open(file_name, 'wb') as f:
        for i in range (num_of_trunk):
            f.write(byte_array_fill)
        
        for i in range(bytes_remain):
            f.write(one_byte_fill)
        f.close()
    
if __name__ == "__main__":
    main()        


