Implementation of a basic Cleint-Server Socket in C , that allows a server to communicate with two clients.
## Features
- Mutli-threading
- Mutex
- Condition Variable
## Requirements
### Software
- CodeBlocks or compatible toolchain
- Git Bash 
## Installation
1. Clone this repository:
   ```bash
   git clone https://github.com/Asma-Prog-Eng/Client_Server_Socket
   
2. Import project into STM32CubeIDE:
File → Import... → Existing Projects into Workspace

3. Rebuild project dependenciesFile 

## Usage : 

Three bash terminals are need : 

1. Start the server : ./server <br />

2. Start Client 1 : ./client1 <br />

3. Start Client 2 : ./client2  <br />

4. In client 1 ( shell) , enter a number : 2 for example <br />
This number will be sent to the server, which will decrement it and send it to client 2 <br />

### Output Sample

<img width="1920" height="1028" alt="im" src="https://github.com/user-attachments/assets/1371ee77-bbff-4813-b18d-80be98a989aa" />

## Contributing
Pull requests are welcome. For major changes, open an issue first.

## License
MIT License
Copyright (c) [2025] [Asma Askri]
