mkdir -p bin
g++ -Wall -Wextra -Werror -g -std=c++11 src/* -o bin/a.out && ./bin/a.out < input.txt
