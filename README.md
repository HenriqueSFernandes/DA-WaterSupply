# DA-WaterSupply

### Balance Pseudo-code

function EdmondBalance( source, target):
    curflow= MIN
    result=0
    while (curflow != 0) :
        curflow = bfsEdmond(source, target);
        res += curflow
    return res

function bfsEdmondKarp(source, target):
    ratio=1 // A value that will help in edge selection
    smallValue=0.1 // Can be changed
    queue=[]
    sourceVertex= graph.getSourceVertex()
    queue.push(sourceVertex)
    while(queue is not empty):
        head=queue.front()
        queue.pop()
        if( cur  is the target):
            pathFlow=updateFlowAcrossPath()
            getAverageDifferenceOfFlowToCapacity()
            if(limit is 0 and all edges are selected):
                return pathFlow
            else:
                limit-=div
            limit=average*ratio 
            blackListEdgesWithDifferenceBelowLimit()
        for(edge in neighbors of head):
            if(edge is not in blackListed and edge.dest is not blackListed and edge.dest was not visited before):
                edge.dest.visited=true
                queue.push(edge)
    return 0