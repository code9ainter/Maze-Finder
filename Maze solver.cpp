 #include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

class Points {//Class to represent Point in maze 
public:
    int x, y;
    Points(int x, int y) : x(x), y(y) {}   //Constructor to initialize x and y coordinates
};

class MazeSolver {// class to solve the maze using BFS
private:
    vector<vector<int>> maze;  // The maze 
    vector<vector<bool>> visited;  // To track visited points
    vector<vector<Points>> parent;  // To track the parent

    int dx[4] = {-1, 1, 0, 0};// Directions: Up, Down, Left, Right
    int dy[4] = {0, 0, -1, 1};

public:
    MazeSolver(vector<vector<int>>& m) {     // Constructor to initialize the maze and its size
        maze = m;
        int n = maze.size();
        int mSize = maze[0].size();
        visited.resize(n, vector<bool>(mSize, false));//also intializing everything to false
        parent.resize(n, vector<Points>(mSize, Points(-1, -1)));//initializing parents of all points to (-1,-1)
    }

    //Function to check if a point is valid (inside the maze, not a wall, and not visited)
    bool isValid(int x, int y, int n, int m) {
        return (x >= 0 && x < n && y >= 0 && y < m && maze[x][y] == 0 && !visited[x][y]);
    }

    //BFS to solve the maze
    bool bfsSolveMaze(Points start, Points end, int n, int m) {
        queue<Points> q;  //Queue for BFS
        q.push(start); // Start with start point
        visited[start.x][start.y] = true; //Mark start point as visited

        while (!q.empty()) {  
            Points curr = q.front(); //Get the point at the front of queue
            q.pop(); //Remove it from queue

            //If we have reached end, reconstruct the path
            if (curr.x == end.x && curr.y == end.y) {
                vector<Points> path;
                Points p = end;
                while (p.x != -1 && p.y != -1) {//as parent of starting point is (-1,-1)  
                    path.push_back(p);// Backtrack to reconstruct path
                    p = parent[p.x][p.y]; //Move to parent point
                }

                //Print the path from start to end
                cout << "Shortest Path: ";
                for (int i = path.size() - 1; i >= 0; i--) { //Print path in reverse order
                    cout << "(" << path[i].x << ", " << path[i].y << ")";
                    if (i != 0) cout << " -> "; 
                }
                cout << endl;
                return true;  // We found the path, so return true
            }

            for (int i = 0; i < 4; i++) {//go to 4 adjacent cells (Up, Down, Left, Right)
                int newX = curr.x + dx[i];
                int newY = curr.y + dy[i];

                //If new point is valid, mark as visited and add it to queue
                if (isValid(newX, newY, n, m)) {
                    visited[newX][newY] = true;
                    q.push(Points(newX, newY));
                    parent[newX][newY] = curr; //Set current point as parent for new
                }
            }
        }

        cout << "No path found.\n";  
        return false;
    }
};

int main() {
    int n, m;
    cout << "Enter the number of rows and columns of the maze: ";
    cin>>n>>m;

    vector<vector<int>> maze(n, vector<int>(m));

    cout << "Enter the maze (0 for open space, 1 for wall):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> maze[i][j];
        }
    }

    int startX, startY, endX, endY;
    cout<<"Enter the starting point (x y): ";
    cin>>startX>>startY;
    cout<<"Enter the ending point (x y): ";
    cin>>endX>>endY;

    if (startX < 0 || startX >= n || startY < 0 || startY >= m ||
        endX < 0 || endX >= n || endY < 0 || endY >= m ||
        maze[startX][startY] == 1 || maze[endX][endY] == 1) {
        cout<<"Invalid start or end points. Make sure they are within bounds and not walls.\n";
        return 0; 
    }

    MazeSolver solver(maze);

    Points start(startX, startY);
    Points end(endX, endY);
    solver.bfsSolveMaze(start, end, n, m);

    return 0;
}