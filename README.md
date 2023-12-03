# BotnetDefenseCPP

## Overview 
This repository contains C++ implementations of algorithms and data structures designed for the analysis of server logs in order to identify and combat botnet attacks. The included code leverages various techniques to process and analyze failed login attempts, aiding in the detection and mitigation of potential security threats. This GitHub repository serves as a comprehensive resource for a school project focused on strengthening server security through intelligent log analysis in C++.

## Folder structure 

The project comprises five folders, each hosting a different application tailored for specific log analysis scenarios.

### Analysis-Using-Vectors-And-Algorithms
This application reads log files, utilizing vectors, merge sort, and binary search to order logs based on the registered date. It also features the capability to filter data within specified date ranges.

### Analysis-using-BST-and-DLinkedLists
The application reads log files and allows users to store logs in either a Binary Search Tree or a Doubly Linked List based on their preference. The stored logs can be ordered and filtered based on the IP addresses associated with each log.

### Analysis-using-AVL-Trees
This application reads log files and employs AVL Trees to store logs. It identifies the top 5 IPs responsible for the most failed requests, enabling the flagging and banning of these IPs to mitigate botnet attacks.

### Analysis-using-graphs
The application reads log files, creating an adjacency matrix to correlate the network octet of each IP with devices making requests from the same network. Through graph creation and analysis, the application identifies potential botnet structures, highlighting the network with the most adjacencies and listing devices making requests from that network.

## Usage

Follow these steps to get the project up and running on your local machine.

### Prerequisites

Make sure you have the following installed on your machine:

- [Git](https://git-scm.com/)
- [C++ Compiler](https://gcc.gnu.org/)

### Installation

- Clone the repository:

    ```bash
    git clone https://github.com/HumbertoBM2/BotnetDefenseCPP
    ```

- Navigate to the project directory:

    ```bash
    cd BotnetDefenseCPP
    ```

## Compilation

For each folder, you can compile the main source file to generate the executable application based on the data structure you want to test.

```bash
g++ main.cpp -o main.exe
```
Run the compiled executable
```bash
./main.exe
```

Each application will display an interactive menu guiding you through each step of the log analysis. Follow the instructions of each menu and enjoy. 
