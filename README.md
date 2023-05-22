## Name: Shubham Prasad Singh

### Instruction on how to build and run the application
The codebase contains a `run.sh` file in the root directory of the project. Please change its access mode using `chmod +x run.sh` command so that it can be run as an executable. On running this shell script, it will build a docker image, then build the source code (using `make build` cmd) and then execute the `match_engine` binary. As mentioned in the Runtime Requirements section of the assignment, the run.sh script is capable of accepting piped input. A sample_input.txt file is also present in the root directory of the project.

Sample run:
- virtual-machine:~/gemini/GeminiMatchingEngine$ cat sample_input.txt | ./run.sh

- Please refer https://stackoverflow.com/questions/47854463/docker-got-permission-denied-while-trying-to-connect-to-the-docker-daemon-socke in case you face any docker permission related issue like the following
docker: permission denied while trying to connect to the Docker daemon socket at unix:///var/run/docker.sock: Post "http://%2Fvar%2Frun%2Fdocker.sock/v1.24/containers/create": dial unix /var/run/docker.sock: connect: permission denied.                                                                                                 
See 'docker run --help'.

- The above issue can be fixed by running the following commands:
virtual-machine:~/gemini/GeminiMatchingEngine$ sudo usermod -a -G docker [your_user]
virtual-machine:~/gemini/GeminiMatchingEngine$ newgrp docker

### Instruction on how to build and run the tests
The codebase contains a `test.sh` file in the root directory of the project. Please change its access mode using `chmod +x test.sh` command so that it can be run as an executable. On running this shell script, it will build a docker image, then build the unit tests (using `make test` cmd) and then execute the `match_engine_test` binary which will run all the unit tests.

Sample run:
- virtual-machine:~/gemini/GeminiMatchingEngine$ ./test.sh

### How I approached the problem?
- I divided the entire problem statement into 3 core components, MatchingEngine, OrderBook and PriceBucket.
- The PriceBucket consists of a list of orders at a particular price. It provides APIs to execute/fill the order, access the number of orders and total volume at a particular price in the order book at any given time.
- The OrderBook maintains the buy and sell order books separately. Both the books are a map of price to PriceBucket. The buy order book map is sorted in decreasing order of price and the sell order book is sorted in increasing order of price. Whenever an order is added in the OrderBook it first tries to execute the order by checking the counter book. It iterates over the each price point in the counter book map and if the spread is crossed it tries to fill this order with the list of orders present in the PriceBucket of the counter order book. If after fill any quantity is left, this order is added in its corresponding side order book.
- PLEASE NOTE THAT THE OrderBook ONLY HANDLES LIMIT ORDERS. IT DOES NOT HANDLE MARKET ORDERS (that is the orders with price = 0), AS THERE WAS NOTHING MENTIONED IN THE ASSIGNMENT ABOUT HOW TO HANDLE MARKET ORDERS AND WHAT TO DO IF THE MARKET ORDER EMPTIES THE ENTIRE COUNTER BOOK WITH ITS QUANTITY STILL REMAINING TO BE FILLED. I DID NOT MAKE ANY ASSUMPTIONS AROUND IT AND HENCE LEFT THE PART TO HANDLE MARKET ORDERS.
- MatchingEngine maintains a map of symbol to OrderBook, that is the OrderBook is maintained per symbol. Whenever an order is added in the matching engine it will add the order in the OrderBook of the symbol for which this order was placed. It also exposes API to access all the remaining orders in the order of arrival time.

### Time spent on this project
6 hours