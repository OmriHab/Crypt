# Crypt
A C based program that encrypts and decrypts files using a passcode that it acquires during run-time.<br />
Setup: `make` will make a copy of crypt, decrypt and encrypt at ~/bin/bash<br />
Usage: 
```
crypt [-ios] [File to Encrypt/Decrept] [OutFile]
To use stdin as in-file use switch '-i' or '--stdin.
To use stdout as outfile use switch '-o' or '--stdout.
To encrypt on to self use option '-s' or '--self'. File will be overwriten with the encrypted data.
```
Encrypt Usage `Encrypt <file>`. Uses the --self option on crypt with the file<br />
Decrypt Usage `Decrypt <file>`. Uses the --self option on crypt with the file
