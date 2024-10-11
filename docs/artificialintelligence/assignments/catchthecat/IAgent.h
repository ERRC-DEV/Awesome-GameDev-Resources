#ifndef IAgent_h
#define IAgent_h
#include <string>
#include <utility>
#include <vector>
struct ASNode {
  std::pair<int,int> point;
  int accDist;
  int heuristicDist;

  //operator < is overloaded to me used in a priority queue
  bool operator<(const ASNode &rhs) const {
    return accDist + heuristicDist > rhs.accDist + rhs.heuristicDist;
  }
};



struct IAgent {
public:
  /**
     * @brief the agent implementation. the center of the world is {0,0}, top left is {-sideSize/2, -sideSize/2} and the bottom right is {sideSize/2, sideSize/2}.
     *
     * @param world the world as a vector of booleans. true means there is a wall, false means there is no wall. The vector is the linearization of the matrix of the world.
     * @param catPos the position of the cat in the world {x,y} relative to the center of the world.
     * @param sideSize the side size of the world. it will be always a square that follows the sequence of 4*i+1: 5, 9, 13, 17, 21, 25, 29, 33, 37, 41, ...
     *
     * @return the position to move to {x,y}. relative to the center of the world.
   */
  virtual std::pair<int,int> move(const std::vector<bool>& world, std::pair<int,int> catPos, int sideSize ) = 0;

  std::vector<std::pair<int,int>> getNeighbors(const std::vector<bool>& world, std::pair<int,int> currentPoint, int sideSize ) {
    std::vector <std::pair<int,int>> pointsToCheck;
    std::vector <std::pair<int,int>> neighbors;

    if ((currentPoint.second%2) == 1) {
      //If it is on an odd numbered (right leaning) row

      //If not on any edges, add all points
      if (currentPoint.first != sideSize/2 && currentPoint.first != -sideSize/2 && currentPoint.second != sideSize/2 && currentPoint.second != -sideSize/2) {
        pointsToCheck.push_back(std::pair<int,int>(currentPoint.first, currentPoint.second+1));
        pointsToCheck.push_back(std::pair<int,int>(currentPoint.first+1, currentPoint.second+1));
        pointsToCheck.push_back(std::pair<int,int>(currentPoint.first, currentPoint.second-1));
        pointsToCheck.push_back(std::pair<int,int>(currentPoint.first+1, currentPoint.second-1));
        pointsToCheck.push_back(std::pair<int,int>(currentPoint.first-1, currentPoint.second));
        pointsToCheck.push_back(std::pair<int,int>(currentPoint.first+1, currentPoint.second));
      }
      else {
        //Then check to see which edges it is on if we are still running
        bool leftSide, rightSide, upSide, downSide = false;
        if (currentPoint.first == sideSize/2) {
          rightSide = true;
        }
        if (currentPoint.first == -sideSize/2) {
          leftSide = true;
        }
        if (currentPoint.second == sideSize/2) {
          upSide = true;
        }
        if (currentPoint.second == -sideSize/2) {
          downSide = true;
        }

        if (leftSide && upSide) {
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first, currentPoint.second-1));
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first+1, currentPoint.second-1));
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first+1, currentPoint.second));
        }
        else if (rightSide && upSide) {
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first, currentPoint.second-1));
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first-1, currentPoint.second));
        }
        else if (leftSide && downSide) {
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first, currentPoint.second+1));
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first+1, currentPoint.second+1));
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first+1, currentPoint.second));
        }
        else if (rightSide && downSide) {
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first, currentPoint.second+1));
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first-1, currentPoint.second));
        }
        else if (leftSide) {
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first, currentPoint.second+1));
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first+1, currentPoint.second+1));
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first, currentPoint.second-1));
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first+1, currentPoint.second-1));
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first+1, currentPoint.second));
        }
        else if (rightSide) {
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first, currentPoint.second+1));
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first, currentPoint.second-1));
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first-1, currentPoint.second));
        }
        else if (upSide) {
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first, currentPoint.second-1));
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first+1, currentPoint.second-1));
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first-1, currentPoint.second));
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first+1, currentPoint.second));
        }
        else if (downSide) {
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first, currentPoint.second+1));
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first+1, currentPoint.second+1));
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first-1, currentPoint.second));
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first+1, currentPoint.second));
        }
      }



    }
    else {
      //If it is on an even numbered (left leaning) row

      //If not on any edges, add all points
      if (currentPoint.first != sideSize/2 && currentPoint.first != -sideSize/2 && currentPoint.second != sideSize/2 && currentPoint.second != -sideSize/2) {
        pointsToCheck.push_back(std::pair<int,int>(currentPoint.first, currentPoint.second+1));
        pointsToCheck.push_back(std::pair<int,int>(currentPoint.first-1, currentPoint.second+1));
        pointsToCheck.push_back(std::pair<int,int>(currentPoint.first, currentPoint.second-1));
        pointsToCheck.push_back(std::pair<int,int>(currentPoint.first-1, currentPoint.second-1));
        pointsToCheck.push_back(std::pair<int,int>(currentPoint.first-1, currentPoint.second));
        pointsToCheck.push_back(std::pair<int,int>(currentPoint.first+1, currentPoint.second));
      }
      else {
        //Then check to see which edges it is on if we are still running
        bool leftSide, rightSide, upSide, downSide = false;
        if (currentPoint.first == sideSize/2) {
          rightSide = true;
        }
        if (currentPoint.first == -sideSize/2) {
          leftSide = true;
        }
        if (currentPoint.second == sideSize/2) {
          upSide = true;
        }
        if (currentPoint.second == -sideSize/2) {
          downSide = true;
        }

        if (leftSide && upSide) {
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first+1, currentPoint.second));
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first, currentPoint.second-1));
        }
        else if (rightSide && upSide) {
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first, currentPoint.second-1));
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first-1, currentPoint.second-1));
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first-1, currentPoint.second));
        }
        else if (leftSide && downSide) {
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first, currentPoint.second+1));
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first+1, currentPoint.second));
        }
        else if (rightSide && downSide) {
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first, currentPoint.second+1));
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first-1, currentPoint.second+1));
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first-1, currentPoint.second));
        }
        else if (leftSide) {
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first+1, currentPoint.second));
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first, currentPoint.second+1));
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first, currentPoint.second-1));
        }
        else if (rightSide) {
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first, currentPoint.second+1));
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first-1, currentPoint.second+1));
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first, currentPoint.second-1));
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first-1, currentPoint.second-1));
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first-1, currentPoint.second));
        }
        else if (upSide) {
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first, currentPoint.second-1));
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first-1, currentPoint.second-1));
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first-1, currentPoint.second));
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first+1, currentPoint.second));
        }
        else if (downSide) {
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first, currentPoint.second+1));
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first-1, currentPoint.second+1));
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first-1, currentPoint.second));
          pointsToCheck.push_back(std::pair<int,int>(currentPoint.first+1, currentPoint.second));
        }
      }

      //Then check to see which edges it is on if we are still running
    }

    for (std::pair<int, int> point : pointsToCheck) {
      if (!world[getIndexOf(point, sideSize)]) {
        neighbors.push_back(point);
      }
    }

    return neighbors;
  }

  std::vector<std::pair<int,int>> locateEscape(const std::vector<bool>& world, std::pair<int,int> catPos, int sideSize ) {


  }

  int getIndexOf(std::pair<int,int> point, int sideSize) {
    int yComponent = abs(point.second-sideSize/2);
    yComponent *= sideSize;
    int xComponent = abs(point.first-sideSize/2);
    return yComponent + xComponent - 1;
  }
};
#endif