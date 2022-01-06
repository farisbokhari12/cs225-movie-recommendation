A one-page summary of the dataset (source location and format) you are using and the specific algorithms you have chosen to implement.

http://snap.stanford.edu/data/web-Movies.html

**Dataset**:
    **Overview** - Movie Reviews  
    **Source Location** - J. McAuley and J. Leskovec. From amateurs to connoisseurs: modeling the evolution of user expertise through online reviews. WWW, 2013.  
    **Format** -    product/productId: B00006HAXW  
                    review/userId: A1RSDE90N6RSZF  
                    review/profileName: Joseph M. Kotow  
                    review/helpfulness: 9/9  
                    review/score: 5.0  
                    review/time: 1042502400  
                    review/summary: Pittsburgh - Home of the OLDIES  
                    review/text: I have all of the doo wop DVD's and this one is as good or better than the  
                    1st ones. Remember once these performers are gone, we'll never get to see them again.  
                    Rhino did an excellent job and if you like or love doo wop and Rock n Roll you'll LOVE  
                    this DVD !!  

                *product/productId: asin, e.g. amazon.com/dp/B00006HAXW
                review/userId: id of the user, e.g. A1RSDE90N6RSZF
                review/profileName: name of the user
                review/helpfulness: fraction of users who found the review helpful
                review/score: rating of the product
                review/time: time of the review (unix time)
                review/summary: review summary
                review/text: text of the review*

**Algorithms**:  
    1. Traversal - DFS - Use DFS to confirm whether or not our graph is bipartite or not.
    2. Complex Algorithm - PageRank - Use PageRank to recommend similar movies based on a given movie by the user.
    3. Covered Algorithm - Shortest Path Algorithm - Dijkstra's Algorithm - Similar to PageRank use case. User would input two movies and would find the path through edges where the movie rating and helpfullness of a reviewer would be above a certain threshold. Would then find  the path through that reviewer and another review's rating and helpfullness that matches that same rating to give the shortest path between the two movies. The path would be the recommendations.  