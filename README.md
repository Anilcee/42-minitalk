# Minitalk

## **Description**
Minitalk is a small communication program between a client and a server using UNIX signals. The client sends a string to the server, which then prints the received message.

## **Features**
- Communication via UNIX signals (**SIGUSR1** and **SIGUSR2**).
- Server can receive and display messages from the client.
- Custom implementation of signal handling in **C**.

## **Installation**

### **1. Clone the repository:**

```bash
git clone git@github.com:Anilcee/42-minitalk.git
```

### **2. Compilation:**
To compile the project, run the following command:

```bash
make
```

### **3. Running the program:**
First, start the server:

```bash
./server
```

The server will display its **Process ID (PID)**. Use this PID to send a message from the client:

```bash
./client <PID> "Your message here"
```

## **Usage Example**

```bash
./server
# Output: Server PID: 12345

./client 12345 "Hello, world!"
# Output on server: Hello, world!
```

## **How It Works**
- The **client** converts each character of the message into binary and sends signals to the **server**.
- The **server** reconstructs the message from the received signals and prints it.

## **Credits**
- Developed in **C** using UNIX signals for interprocess communication.

