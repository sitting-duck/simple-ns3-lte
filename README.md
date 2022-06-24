### Building the Docker Image
Use

```bash
docker build -t simple-lte . 
```
### Running the Containers Interactive Terminal to Play Around In It
Check your work by running to get into the interactive terminal if you need to. Interactive terminal is just how we enter a container and use it just like a normal command line. 

```bash
docker run --name simple-lte-container -it --rm simple-lte /bin/bash
```

