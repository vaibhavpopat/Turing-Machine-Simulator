# Turing-Machine-Simulator
This repository takes as input a turing machine representation and an input string. The turing machine is simulated by running the given program on the input string to check if it is accepted or not.

Files :

1.  ip1.txt and ip2.txt - They contain deterministic turing machines.
2.  op1.txt and op2.txt - The corresponding final tape configurations on simulating turing machines from ip1.txt and ip2.txt.
3.  ip3.txt and op3.txt - The file ip3.txt contains non-deterministic turing machine with the output tape in op3.txt.
4.  tm.cpp - This file contains the code which runs the given program on the input string and checks if it gets accepted.The Turing Machine can also be Non-Deterministic - in which case backtracking technique is used for covering all the possible solution paths.
