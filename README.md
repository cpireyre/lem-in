# lem_in
## What this is
This is a school project about graph traversal, flow regulation, ants, and more. By @Tanguyix and @cpireyre.

The program takes as input an anthill, which looks like this:
```
15                <-  Number of ants.
3 100 500         <-  Room name, followed by its x-y coordinates.
##start           <-  Special room "start", the source of our flow.
start 200 300
##end             <-  The other special room, our sink.
end 250 900
4 100 700
1 200 500
2 200 700
5 300 500
6 300 700
start-1           <-  "start" room is connected to the "1" room.
3-4               <-  "3" is connected to "4", and so on.
2-4
1-5
6-5
end-6
1-2
2-end
3-start
```
From there, it computes the most efficient way to move all the ants from *start* to *end*, with the proviso that ants can't step on each other, i.e. you can't have two ants in one room at the same time.
The program will output this solution for the above anthill:
```
L1-1 L2-3
L1-5 L2-4 L3-1 L4-3
L1-6 L2-2 L3-5 L4-4 L5-1 L6-3
L1-end L2-end L3-6 L4-2 L5-5 L6-4 L7-1 L8-3
L3-end L4-end L5-6 L6-2 L7-5 L8-4 L9-1 L10-3
L5-end L6-end L7-6 L8-2 L9-5 L10-4 L11-1 L12-3
L7-end L8-end L9-6 L10-2 L11-5 L12-4 L13-1 L14-3
L9-end L10-end L11-6 L12-2 L13-5 L14-4 L15-1
L11-end L12-end L13-6 L14-2 L15-5
L13-end L14-end L15-6
L15-end
```
`L2-3` means "ant number 2 goes to room number 3." Each line of output corresponds to one "round" of moving ants through the anthill. The goal is to choose paths optimally to minimize this number of lines.

## How to run it
`git clone https://github.com/cpireyre/lem-in.git && cd lem-in && make test`

This will clone the repository, compile the project, and launch our automated tests. These tests work by generating an anthill with the tool provided by @fbouquet42 (`./tools/generator --flow-one > one.lemin`), solving it with `./lem-in < one.lemin`, and finally comparing the number of lines in our output with that expected by the generator using `grep -c L`. We also check our output for validity (making sure every room has at most one ant at all times) using a Python script we made.

## What? tl;dr
If you're a 42 student, you can probably just run `make visutest` for a magnificent, interactive, full-featured, ultraHD cinematic experience, brought to you by @Tanguyix. The visualizer is unlikely to compile on computers outside of 42 unfortunately, since it is made using the school's internal graphics library.
Then again if you're a 42 student you should already know what this is and what it does.

## How it's made and what we learned
We implemented the Edmonds-Karp flow regulation algorithm on a graph structure made from an array of linked lists. Unlike the usual flow regulation problem, lem-in has a finite and usually rather small number of ants, requiring us to put extra constraints on the residual paths uncovered by our algorithm. We had to get crafty, in a word. 

Getting acquainted with graph theory and implementing the various puzzle pieces, such as filling out our graph from an adjacency matrix, running breadth-first searches using queues, updating the residual graph per Edmonds-Karp, finding our own extra constraints to the algorithm to make it relevant to our actual problem, etc. was a challenging and rewarding process. 

This was also our first consequential group project, which meant we had to figure out a team workflow. I am pleased to say we managed this without any major git gaffes. (Plenty of small or medium-sized ones though.)
