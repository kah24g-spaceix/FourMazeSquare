#pragma once

// maze.h
const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;
const int SUBMIT = 4;

const int HEIGHT = 43 + 1; // 20 + 48 = 68
const int WIDTH = 62 + 1; // 50 + 48 = 98

class Maze {
private:
    char tempMap[HEIGHT][WIDTH];
    int x, y;
    int key;
    int playing;
    int stageNum;

public:
    Maze();

    void GameLoop(int stageNum);
    int KeyControl();
    void DrawMap();
    void DrawUI();

    void Move(int _x, int _y);
    void StageName();
    void Stage();

    int title();
    void titleDraw(int s);
    int menuDraw();
};
