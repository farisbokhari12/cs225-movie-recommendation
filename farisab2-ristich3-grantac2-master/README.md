# farisab2-ristich3-grantac2


# CS225 Final Project
## Team Members: Grant Chen, Faris Bokhari, Alexander Ristich

### VIDEO LINK FOR OUR PRESENTATION (Also emailed to mentor)
* https://mediaspace.illinois.edu/media/1_0r0hdxb1

### Movie Recommendations - Instructions
1. Open the terminal and type *make clean*, the dataset is humongous so sometimes it'll crash if we don't clean it up regularly
2. Type: make && ./finalproj [filename]
   - Example: make && ./finalproj tests/movies_small.txt
3. Then you will be prompted with 2 choices [PR] = PageRank Movie Recommendation Algorithm, or [DIJK] = Dijkstra's Movie Recommendation Algorithm
   - Type either "PR" or "DIJK" **exactly as shown** (case sensitive)
4. When you are prompted to enter one or multiple product IDs, you can either:
   1. Open a dataset file and *cltr-v* a product ID
   2. OR, you can go to amazon.com, search up a movie, and take the ID from the url in this format - amazon.com/.../dp/**productID**
      1. NOTE: the dataset might not contain the movie ID you want if you search it up because our dataset isn't up to date
5. If you choose to use the PageRank algo, after inputting 2 product ID's, it'll ask you whether or not you want to input more movies that you like. [Y] = Yes, [N] = No.
6. The final step is to wait for the algo to finish running :)

### Running test cases - Instructions
1. *Same as above*
2. Type: make test && ./test