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
	// �ʱ�ȭ �ڵ� �߰�
	this->stageNum = stageNumber;
	this->key = 0;
	this->playing = 1;

	Stage();

	DrawMap(); // �������� ���

	while (playing) {
		int stop = 0;
		DrawUI();
		switch (KeyControl()) // �÷��̾� �̵�
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
			cout << "1.5���� ������ �����մϴ�.";
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

	return -1;  // ��ȿ���� ���� Ű
}
void Maze::DrawMap() {
	system("cls");
	int h, w;

	for (h = 0; h < HEIGHT; h++) {
		for (w = 0; w < WIDTH; w++) {
			char temp = tempMap[h][w];
			if (temp == '0') { // �� ���� (����)
				cout << " ";
			}
			else if (temp == '1') { // ��(#)
				cout << "#";
			}
			else if (temp == 's') { // �÷��̾� (@)
				x = w;
				y = h;
				cout << "@";
			}
			else if (temp == 'q') { // ������ (O)
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
	cout << "���� : " << key << "��";

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
	else if (mapObject == 'K') { // �̵��� ��ġ�� ���谡 ������ ȹ��
		key += 1;
		tempMap[y + _y][x + _x] = '0';
		gotoxy(x + _x, y + _y); // ���谡 �ִ� ��ġ�� ����
		cout << " ";
	}
	else if (mapObject == 'L') {
		if (key > 0) {
			key -= 1; // ���� 1�� �Ҹ�
			tempMap[y + _y][x + _x] = '0'; // ���� �������� L �����͸� 0���� ����

			gotoxy(x + _x, y + _y);
			cout << " ";
		}
	}
	else if (mapObject == '<') { // ��Ż �Ա�
		// ��Ż ���� ����: �ش��ϴ� ��Ż �Ա�("<") ã��
		tempMap[y + _y][x + _x] = '0';
		gotoxy(x + _x, y + _y);
		cout << " ";
		for (int h = 0; h < HEIGHT; h++) {
			for (int w = 0; w < WIDTH; w++) {
				if (tempMap[h][w] == 's') {
					tempMap[h][w] = '0';
				}
				if (tempMap[h][w] == '>') {
					// �÷��̾ ��Ż �Ա� ��ġ�� �̵�
					x = w;
					y = h;
					tempMap[h][w] = 's';
					DrawMap(); // ���� �ٽ� �׷���
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
		cout << " "; // �����

		gotoxy(x + _x, y + _y); // ������ ��ġ�� �̵� �� �÷��̾� ���
		cout << "@";

		x += _x; // ���� ��ǥ �� �ݿ�
		y += _y;
	}
}
void Maze::StageName() {
	// �̱���
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
		cout << "������ �� �� �����ϴ�.";
	}
}