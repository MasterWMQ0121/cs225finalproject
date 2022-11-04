# CS 225 Final Project

## [Presentation Video]()

## Authors

- Mingqi Wang (`mingqiw2`)
- Sihan Cheng (`sihanc6`)
- Kelly Dai (`sihanc6`)
- Teresa Zhang (`sihanc6`)

## Algorithms: BFS, Astar, Dijkstra's

## Data

We are using the [California Road Network and Points of Interest](https://www.cs.utah.edu/~lifeifei/SpatialDataset.htm) data and focusing on the following two files:

- [California Road Network's Nodes (Node ID, Longitude, Latitude)](https://www.cs.utah.edu/~lifeifei/research/tpq/cal.cnode)
- [California Road Network's Edges (Edge ID, Start Node ID, End Node ID, L2 Distance)](https://www.cs.utah.edu/~lifeifei/research/tpq/cal.cedge)

## Repo Structure

- All major files that contain our functions and classes are in the [root directory](https://github-dev.cs.illinois.edu/cs225-sp22/ruoranz2-gracewz2-elliepc2/tree/main). The structure of those files is outlined in [Project Structure](#project-structure).

- Datasets are stored as txt files in [`/data`](https://github-dev.cs.illinois.edu/cs225-sp22/ruoranz2-gracewz2-elliepc2/tree/main/data).

- Tests are in [`/tests`](https://github-dev.cs.illinois.edu/cs225-sp22/ruoranz2-gracewz2-elliepc2/tree/main/data).

- Project report, development log, contract, etc. are in [`/documents`](https://github-dev.cs.illinois.edu/cs225-sp22/ruoranz2-gracewz2-elliepc2/tree/main/documents).

## Running Instructions

Make sure you are running the program in [Docker](https://www.docker.com/). If not, follow [This Guide](https://courses.engr.illinois.edu/cs225/sp2022/resources/own-machine/) to get started.

### Building the application

### Running the application

### Testing the application

To use our Complete California Experience program, run `make` then `./main` in the root directory. Follow the instructions of our program and you are good to go!

We call all the functions in `main.cpp` for you (through a fleshed-out `utils.cpp` that will print clear instructions on what your user input should be). The required inputs for each of the functionality are as follows:

1. GPS (Dijkstra's): 
   - Input: starting node number and ending node number (both should be integer between 0 and 21047)
   - Output: the shortest path (nodes it passes through) and the distance of the shortest path (in km)
   - Image Output: `californiaShortestPath.png` that outlines the shortest path on the California map constructed from our nodes
2. Sporadic Tour (Welsh-Powell Colorability):
   - Input: an integer within the given bounds (currently it's 1-3)
   - Output: the node numbers, based on our colorability algorithm, that correspond to your given input and represent places you should visit
3. Nearest Attraction (KD Tree Nearest Neighbors):
   - Input: longitude (-124.389343 ~ -114.294258) and latitude (32.541302 ~ 42.017231)
   - Output: a latitude - longitude pair that indicates a California attraction that is closest to your current location
4. Lazy/Cluster Travel (BFS): 
   - Input: starting node number (integer between 0 and 21047)
   - Output: a traversal path within your current cluster

In addition to the above overarching functions that are called in `main.cpp`, we also have clear input and output definitions in the comments for each small functions, so you can always refer to those.

### Tests

To run the test cases, run `make test` then `./test` in the root directory.

We constructed several small to medium sized datasets in [`/data`](https://github-dev.cs.illinois.edu/cs225-sp22/ruoranz2-gracewz2-elliepc2/tree/main/data) directory, which are used as test cases to evaluate if the output of our algorithms are as expected. We also tested for edge cases such as when the graph is not fully connected. Our tests focus on testing the functionality of graph construction, Djikstra's algorithm, Welsh-Powell algorithm, and KD Tree construction.

## Building the application

1. Clone the project repository to your local machine
2. `cd` into the cloned repository
3. Enter the command `make` or `make map` into the terminal

## Running the application

1. To run a bfs traversal on a set of airport data enter the command
   `./map bfs` - This outputs the visited airports in the order of the traversal from San Diego International Airport
2. To run the Astar pathfinding algorithm enter the command `./map astar`
   - This finds a path from San Diego International Airport to Coimbatore International Airport
3. To run Dijkstra's algorithm enter the command `./map dijkstra`
   - Since the actual data set is so large the runtime for dijkstra's algorithm is very long
   - We remedied this by instead creating a smaller sample dataset and running the algorithm on that

## Testing the application

1. To build the tests enter the command `make test`
2. To run the tests:
   - To run all tests enter the command `./test`
   - To run all bfs tests enter `./test [part=bfs]`
   - To run all astar tests enter `./test [part=astar]`
   - To run all dijkstra tests enter `./test [part=dijkstra]`
