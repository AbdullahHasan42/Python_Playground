from aes import AES
import os



# Example of AES encryption
aes = AES(mode='ecb', input_type='text')

# Test vector 128-bit key
key = '424c41434b2045594520504952415445' # 'BLACK EYE PIRATE' in Hexadecimal

# Encrypt data with your key
data = 'TREASURE'
ciphertext = aes.encryption(data, key)

# Decrypt data with the same key
plaintext = aes.decryption(ciphertext, key) 

print("\n")

# Verification that the data was encrypted and decrypted correctly
if plaintext == data:
    print('SUCCESS')
    print("\n")

os.system('PAUSE')
