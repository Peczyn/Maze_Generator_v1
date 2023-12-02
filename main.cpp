#include <iostream>
#include <stack>
#include <vector>
#include <bitset>

using namespace std;


class maze{
public:
    int mSize;
    int mVisited;
    vector<vector<int>> mMaze;

    int mWidth;
    int mHeight;
private:

    enum{
        North = 0x01,
        East = 0x02,
        South = 0x04,
        West = 0x08,
        CellVisited = 0x10,
    }; //WSEN


    stack<pair<int, int>> mStack;
    int mPathWidth;

public:
    virtual bool Create()
    {
        mWidth = 15;
        mHeight = 15;
        mMaze =  vector<vector<int>>(mHeight,vector<int>(mWidth,0));
        mSize = mWidth*mHeight;

        int x = 0;
        int y = 0;
        mStack.push(make_pair(x,y));
        mMaze[y][x]= CellVisited;
        mVisited=1;


        return true;
    }

    virtual bool Update()
    {
        auto offsetX = [&](int x)
        {
            return (mStack.top().first + x);
        };
        auto offsetY = [&](int y)
        {
            return (mStack.top().second + y);
        };

        if(mVisited < mWidth*mHeight)
        {
            vector<int> neighbours;

            if(mStack.top().second > 0 && (mMaze[offsetY(-1)][offsetX(0)] & CellVisited) ==0)
            {
                neighbours.push_back(0);
            }
            if(mStack.top().first < mWidth-1  && (mMaze[offsetY(0)][offsetX(1)] & CellVisited) ==0)
            {
                neighbours.push_back(1);
            }
            if(mStack.top().second < mHeight-1  && (mMaze[offsetY(1)][offsetX(0)] & CellVisited) ==0)
            {
                neighbours.push_back(2);
            }
            if(mStack.top().first > 0 && (mMaze[offsetY(0)][offsetX(-1)] & CellVisited) ==0)
            {
                neighbours.push_back(3);
            }


            if(!neighbours.empty())
            {
                int nextCellDir = neighbours[rand() % neighbours.size()];

                switch(nextCellDir)
                {
                    case 0:
                        mMaze[offsetY(-1)][offsetX(0)] |= CellVisited | South;
                        mMaze[offsetY(0)][offsetX(0)]  |= North;
                        mStack.push(make_pair((mStack.top().first+0),(mStack.top().second-1)));
                        break;
                    case 1:
                        mMaze[offsetY(0)][offsetX(1)] |= CellVisited | West;
                        mMaze[offsetY(0)][offsetX(0)]  |= East;
                        mStack.push(make_pair((mStack.top().first+1),(mStack.top().second+0)));
                        break;
                    case 2:
                        mMaze[offsetY(1)][offsetX(0)] |= CellVisited | North;
                        mMaze[offsetY(0)][offsetX(0)]  |= South;
                        mStack.push(make_pair((mStack.top().first+0),(mStack.top().second+1)));
                        break;
                    case 3:
                        mMaze[offsetY(0)][offsetX(-1)] |= CellVisited | East;
                        mMaze[offsetY(0)][offsetX(0)]  |= West;
                        mStack.push(make_pair((mStack.top().first-1),(mStack.top().second+0)));
                        break;
                }
                mVisited++;
            }
            else
            {
                mStack.pop();
            }
        }
        return true;
    }

};

vector<vector<char>> StworzLabirynt()
{
    srand((unsigned) time(NULL));
    maze M;
    M.Create();
    while(M.mVisited!=M.mSize)
    {
        M.Update();
    }


    vector<vector<char>> labirynt;
    for(int i=0; i<M.mHeight*3; i++)
    {
        vector<char> temp;
        for(int j=0; j<M.mWidth*3; j++)
        {
            temp.push_back('@');
        }
        labirynt.push_back(temp);
    }

    for(int row =0; row<M.mHeight; row++)
    {
        for(int collumn=0; collumn<M.mWidth; collumn++) {
            labirynt[row*3+1][collumn*3+1]=' ';
            if ((M.mMaze[row][collumn] & 0x01) == 1) {
                labirynt[row*3][collumn*3 + 1] = ' ';
            }
            if ((M.mMaze[row][collumn] & 0x02) == 2) {
                labirynt[row*3 + 1][collumn*3 + 2] = ' ';
            }
            if ((M.mMaze[row][collumn] & 0x04) == 4) {
                labirynt[row*3 + 2][collumn*3 + 1] = ' ';
            }
            if ((M.mMaze[row][collumn] & 0x08) == 8) {
                labirynt[row*3 + 1][collumn*3] = ' ';
            }
        }
    }



    return labirynt;
}

//int main() {
//    vector<vector<char>> lab = StworzLabirynt();
//    for(auto a : lab)
//    {
//        for (auto b : a)
//        {
//            cout << b;
//        }
//        cout << endl;
//    }
//}
