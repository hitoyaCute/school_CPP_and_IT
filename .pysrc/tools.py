

def fnv1a_32(data:bytes):
    fnv_prime = 0x0100_0193
    hash_value = 0x811c_9dc5
    for byte in data:
        hash_value ^= byte
        hash_value *= fnv_prime
        hash_value &= 0xffff_ffff
    return hash_value

def fnv1a_64(data:bytes):
    h = 0xcbf2_9ce4_8422_2325
    for byte in data:
        h ^= byte
        h *= 0x100_0000_01b3
        h &= 0xffff_ffff_ffff_ffff
    
    return h

def int_to_signed(data:int):
    print(f"size: {data.bit_length()}")
    if data.bit_length() > 32:
        raise ValueError("only 64 bit bozo")

    if (data >> 31) & 1:
        data -= (1 << 32)
    return data

dat = b"nice"
print(int_to_signed(fnv1a_32(dat)))
