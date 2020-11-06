cc -g board.c -o board
lldb board
lldb breakpoint set -f board.c --name findComputerMove

