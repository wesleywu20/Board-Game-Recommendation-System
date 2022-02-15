# Results

## Overall testing methodology
One of our main testing methods was to run graph algorithms on a small graph, which we could manually check all the properties of. The CS225 resources page has a page on Dijkstra's algorithm [here](https://courses.engr.illinois.edu/cs225/fa2021/resources/dijkstra/), which references a graph of locations used to demonstrate Dijkstra's algorithm. Using this graph (represented as small_graph.txt), we made a catch test suite that would check various properties of the graph to make sure all of our methods were working properly. In addition to this example graph, we ran tests on the first 5 elements of the game dataset. We used small datasets so that we could run our tests in a reasonable amount of time. We also tested properties of the larger graphs (including the full dataset) using this method. Running the test suite (as described in the readme) will verify all of our results.

## BFS traversal
Our BFS traversal seems to be working perfectly fine. When performing a BFS from the game Terra Mystica, the first 20 games in the list (in order of the traversal) are as follows.

```
Terra Mystica
Gloomhaven
Pandemic Legacy: Season 1
Through the Ages: A New Story of Civilization
Terraforming Mars
Twilight Struggle
Star Wars: Rebellion
Scythe
The 7th Continent
Gaia Project
The Castles of Burgundy
7 Wonders Duel
War of the Ring (Second Edition)
Caverna: The Cave Farmers
Puerto Rico
Agricola
Mage Knight Board Game
Viticulture Essential Edition
Arkham Horror: The Card Game
Mansions of Madness: Second Edition
```
Upon inspection of the adjacency matrix file, these are all neighbors of Terra Mystica, and are in order of their rank, which makes sense as our BFS on the adjacency matrix gives neighbors by order of their rank. This indicates that our BFS is working perfectly. Additionally, the size of the traversal vector is `4999`, which is exactly the size of the input dataset. This implies that our graph is connected, which is good. In our original project proposal, we indicated that we would like the user to enter in parameters to filter the BFS. However, we did not think this was that useful of a feature to implement in the graph. Since the graph API gives an inorder list of the traversal, it is up to the client to filter this data as they see fit. We believed that only a full BFS traversal was what was necessary for our graph.

## Dijkstra's Algorithm
Our shortest path algorithm of choice was Dijkstra's algorithm. Using the CS225 resource page referenced above, we were able to get our algorithm working perfectly. An example output of our algorithm, for example: 
```
Shortest path between Mice and Mystics and Alhambra
(Mice and Mystics, Case Blue, W1815, Empires in Arms, The 7th Continent, Alhambra)
```
The use case of this is one of the main purposes of our project: to recommend the shortest path between any two board games so that the player plays games that are increasingly similar to a destination. Our algorithm was well-tested, and can be run using the command line. 

# Discoveries
Our main discoveries came  from our centrality measures, which were intended to give us some insight on our dataset. Our discoveries are indicated below.
## Centrality measures
Our development of centrality measures was quite the adventure. In our original proposal, we aimed to create a Floyd-Warshall algorithm for betweenness centrality. After thorough research on this algorithm, we concluded that the runtime would be too immense to use, and so we pivoted to closeness centrality. We did implement this feature, but had to scrap it entirely due to the fact that it as well had a very large runtime. We wrote a degree centrality algorithm, which is likely the simplest centrality measure, to see if we could gain any information, but our results did not seem to indicate very much. After this however, we found out about the algorithm for eigenvector centrality, which was a perfect fit for our project as we were using an adjacency matrix as our underlying data structure.
### Degree Centrality
Our Degree centrality ranking provided the following output:
```
#1: City of Remnants
#2: 504
#3: 1754: Conquest – The French and Indian War
#4: Yashima: Legend of the Kami Masters
#5: Dungeoneer: Vault of the Fiends
#6: Dungeoneer: Tomb of the Lich Lord
#7: Mythic Battles: Pantheon
#8: Illuminati: New World Order
#9: Warhammer Underworlds: Shadespire
#10: Artifacts, Inc.
#11: Bloodborne: The Card Game
#12: Heroes
#13: Panic Station
#14: Covert
#15: Mage Knight Board Game
#16: Dixie: Bull Run
#17: The Thing
#18: Virulence: An Infectious Card Game
#19: Council of Blackthorn
#20: The Hobbit
```
Of course, this is only the first 20 elements in the ranking. This measure was not very good, because it really only provided insight into which games had the most mechanics/categories, since if there were no overlap in either of these, games would not be connected. Therefore the games with the most categories or mechanics would rank the highest. This was not included in our original proposal, nor does it provide much useful information, but it was still a fun and simple method to write. 

### Eigenvector Centrality
Eigenvector centrality was a much more interesting centrality metric. We used the power iteration method to compute the eigenvector of our adjacency matrix, with one key factor being that the reciprocal of the edge weight was used for the repeated matrix multiplications. This would guarantee that nodes closer to others (with lower edge weights) get ranked higher. Over multiple iterations, matrix multiplications of the adjacency matrix and a seed vector converge to a dominant eigenvector, which will represent the relative amount of centrality that each game has. Here are the first 20 games in the ranking on the full dataset:
```
#1: Through the Ages: A New Story of Civilization
#2: Twilight Struggle
#3: Star Wars: Rebellion
#4: Scythe
#5: Great Western Trail
#6: The 7th Continent
#7: Gaia Project
#8: The Castles of Burgundy
#9: 7 Wonders Duel
#10: War of the Ring (Second Edition)
#11: Caverna: The Cave Farmers
#12: Agricola
#13: Mage Knight Board Game
#14: Viticulture Essential Edition
#15: Arkham Horror: The Card Game
#16: Mansions of Madness: Second Edition
#17: Concordia
#18: Blood Rage
#19: Mechs vs. Minions
#20: Star Wars: Imperial Assault
```
This data is really wonderful! Through our testing, we noticed that The 7th Continent was a game that showed up in **several** shortest path inputs. Seeing it rank high in the centrality measure was a very good indication that our ranking had worked. Additionally, other games on this list have good rankings, and also have rather common categories and mechanics. They also seem to have average playing times around 2-3 hours. This data seems to make sense, as popular games would be more "ubiquitous" in a sense, and 2-3 hours seems like the time to play for most of these board games. Having common categories and mechanics would also increase the number of connections any game has, which would make them more central.

# Conclusion
Board games are fun. Coding is fun. Coding about board games is fun! This project was a wonderful way for us to explore the relationships of several board games to each other, as well as to explore the inner workings of graphs.