from aes import AES

aes = AES(mode='ecb', input_type='hex')
        
# Test vector 128-bit key
key = '000102030405060708090a0b0c0d0e0f'
    
# Encrypt data with your key
data = '00112233445566778899aabbccddeeff'

ciphertext = aes.encryption(data, key)
    
# Decrypt data with the same key
plaintext = aes.decryption(ciphertext, key) 

print("\n")

if plaintext == data:
    print(True)
