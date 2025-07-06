// game.cpp
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <conio.h>
#include <windows.h>
#include <vector>

#include "maze.h"
#include "util.h"

using namespace std;

Maze::Maze() : x(0), y(0), key(0), playing(1), stageNum(0) {}

void Maze::GameLoop(int stageNumber) {
	// 초기화 코드 추가
	this->stageNum = stageNumber;
	this->key = 0;
	this->playing = 1;

	Stage();

	DrawMap(); // 스테이지 출력

	while (playing) {
		int stop = 0;
		DrawUI();
		switch (KeyControl()) // 플레이어 이동
		{
		case UP:
			Move(0, -1);
			break;
		case DOWN:
			Move(0, 1);
			break;
		case RIGHT:
			Move(1, 0);
			break;
		case LEFT:
			Move(-1, 0);
			break;
		case SUBMIT:
			stop = 1;
		}
		if (stop == 1) {
			gotoxy(22, 8);
			cout << "1.5초후 게임을 종료합니다.";
			break;
		}
	}
	gotoxy(44 + (stageNum * 2), 18 + (stageNum * 2));
	if (playing == 0)
		cout << "Clear!";
	Sleep(1500);
}
int Maze::KeyControl() {
	char temp = _getch();

	if (temp == 'w' || temp == 'W')
		return UP;
	else if (temp == 's' || temp == 'S')
		return DOWN;
	else if (temp == 'a' || temp == 'A')
		return LEFT;
	else if (temp == 'd' || temp == 'D')
		return RIGHT;
	else if (temp == ' ')
		return SUBMIT;

	return -1;  // 유효하지 않은 키
}
void Maze::DrawMap() {
	system("cls");
	int h, w;

	for (h = 0; h < HEIGHT; h++) {
		for (w = 0; w < WIDTH; w++) {
			char temp = tempMap[h][w];
			if (temp == '0') { // 빈 공간 (공백)
				cout << " ";
			}
			else if (temp == '1') { // 벽(#)
				cout << "#";
			}
			else if (temp == 's') { // 플레이어 (@)
				x = w;
				y = h;
				cout << "@";
			}
			else if (temp == 'q') { // 목적지 (O)
				cout << "O";
			}
			else if (temp == 'K') { // key (*)
				cout << "*";
			}
			else if (temp == 'L') { // locked door (+)
				cout << "+";
			}
			else if (temp == '<') { // portal 1 '('
				cout << "(";
			}
			else if (temp == '>') { // portal 2 ')'
				cout << ")";
			}
			else
				break;
		}
		cout << '\n';
	}
}
void Maze::DrawUI() {
	gotoxy(34 + (stageNum * 2), 15 + (stageNum * 2));
	cout << "열쇠 : " << key << "개";

	int numX = 22, numY = 16;
	gotoxy(numX, numY);
	StageName();
}

void Maze::Move(int _x, int _y) {
	char mapObject = tempMap[y + _y][x + _x];
	srand(time(NULL));
	int ouch = 0;
	if (mapObject == '1') {
		ouch = (rand() % 15) + 1;
		gotoxy(x, y);
		if (ouch == 1) {
			cout << "a";
		}
		else {
			cout << "X";
		}

		gotoxy(x, y);
		cout << "@";
	}
	else if (mapObject == 'K') { // 이동할 위치에 열쇠가 있으면 획득
		key += 1;
		tempMap[y + _y][x + _x] = '0';
		gotoxy(x + _x, y + _y); // 열쇠가 있는 위치를 지움
		cout << " ";
	}
	else if (mapObject == 'L') {
		if (key > 0) {
			key -= 1; // 열쇠 1개 소모
			tempMap[y + _y][x + _x] = '0'; // 문이 열렸으니 L 데이터를 0으로 설정

			gotoxy(x + _x, y + _y);
			cout << " ";
		}
	}
	else if (mapObject == '<') { // 포탈 입구
		// 포탈 로직 구현: 해당하는 포탈 입구("<") 찾기
		tempMap[y + _y][x + _x] = '0';
		gotoxy(x + _x, y + _y);
		cout << " ";
		for (int h = 0; h < HEIGHT; h++) {
			for (int w = 0; w < WIDTH; w++) {
				if (tempMap[h][w] == 's') {
					tempMap[h][w] = '0';
				}
				if (tempMap[h][w] == '>') {
					// 플레이어를 포탈 입구 위치로 이동
					x = w;
					y = h;
					tempMap[h][w] = 's';
					DrawMap(); // 맵을 다시 그려줌
					return;
				}
			}
		}

	}
	else {
		if (mapObject == 'q') {
			playing = 0;
		}
		gotoxy(x, y);
		cout << " "; // 지우기

		gotoxy(x + _x, y + _y); // 증감한 위치로 이동 후 플레이어 출력
		cout << "@";

		x += _x; // 실제 좌표 값 반영
		y += _y;
	}
}
void Maze::StageName() {
	// 미구현
}

void Maze::Stage() {
	stringstream ss;
	ss << "Maps\\map" << stageNum << ".txt";
	string fileName = ss.str();

	ifstream file(fileName);
	if (file.is_open()) {
		int lineCount = 0;
		string strLine;
		while (getline(file, strLine) && lineCount < HEIGHT) {
			strncpy_s(tempMap[lineCount], strLine.c_str(), WIDTH - 1);
			tempMap[lineCount][WIDTH - 1] = '\0';
			lineCount++;
		}
		file.close();
	}
	else {
		cout << "파일을 열 수 없습니다.";
	}
}