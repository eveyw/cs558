- Team information:

Name: Wen Yang
Email: wyang41@binghamton.edu

Name: Jieying Zhou
Email: jzhou86@binghamton.edu


- Whether the code was tested on bingsuns:

Yes.


- How to excute our program:

Part1: 

1) Run command "make";
2) Run command " ./telnetserv 1234 " to active server;
3) Open another shell window and run " ./telnetcli localhost 1234 " to active client and get connected to server;
4) After we active client, our shell will begin to work. Then you can try those commands in the assignments requirements.

Part2: 

1) Run command "make";
2) To avoid some weird characters or blank lines go into the input file, please use this command to create the input file: " echo -n 'abce.....' > input "; (***)
3) Encryption example: " ./mono input output 123 1 " 
4) Decryption example: " ./mono output input 123 0 "


- Notes:

The algorithm we used for part 2:
We choose have a 26-times loop, every time we used 'rand()' to take remainders. Because of the requirement that different plaintext letters should be mapped to different ciphertext letters, so once the rand() result is the same as another one, we would add 1 on it. In some special cases such as adding to the limit, we would take the remainder again.
