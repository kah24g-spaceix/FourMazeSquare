// title.cpp
#include <iostream>
#include <conio.h>
#include <windows.h>
#include "maze.h"
#include "util.h"
using namespace std;

int Maze::title() {
	init();
	titleDraw(100);
	while (1) {
		int manuCode = menuDraw();
		if (manuCode == 0) {
			system("cls");
			return 0;
		}
		else if (manuCode == 1) {
			return 1;
		}
	}
}
void Maze::titleDraw(int s) {
	int tx = 20, ty = 18;
	int mainT = 12;
	int subT = 22;
	gotoxy(tx + mainT, ty);
	cout << "::::::::::  ::::::::  :::    ::: ::::::::: "; cout << " ::::     ::::     :::     ::::::::: ::::::::::\n";
	Sleep(s);
	gotoxy(tx + mainT, ty + 1);
	cout << ":+:        :+:    :+: :+:    :+: :+:    :+:"; cout << " +:+:+: :+:+:+   :+: :+:        :+:  :+:       \n";
	Sleep(s);
	gotoxy(tx + mainT, ty + 2);
	cout << "+:+        +:+    +:+ +:+    +:+ +:+    +:+"; cout << " +:+ +:+:+ +:+  +:+   +:+      +:+   +:+       \n";
	Sleep(s);
	gotoxy(tx + mainT, ty + 3);
	cout << ":#::+::#   +#+    +:+ +#+    +:+ +#++:++#: "; cout << " +#+  +:+  +#+ +#++:++#++:    +#+    +#++:++#  \n";
	Sleep(s);
	gotoxy(tx + mainT, ty + 4);
	cout << "+#+        +#+    +#+ +#+    +#+ +#+    +#+"; cout << " +#+       +#+ +#+     +#+   +#+     +#+       \n";
	Sleep(s);
	gotoxy(tx + mainT, ty + 5);
	cout << "#+#        #+#    #+# #+#    #+# #+#    #+#"; cout << " #+#       #+# #+#     #+#  #+#      #+#       \n";
	Sleep(s);
	gotoxy(tx + mainT, ty + 6);
	cout << "###         ########   ########  ###    ###"; cout << " ###       ### ###     ### ######### ##########\n";

	Sleep(s);
	gotoxy(tx + subT, ty + 8);
	cout << " ::::::::   ::::::::   :::    :::     :::     :::::::::  :::::::::: \n";
	Sleep(s);
	gotoxy(tx + subT, ty + 9);
	cout << ":+:    :+: :+:    :+:  :+:    :+:   :+: :+:   :+:    :+: :+:        \n";
	Sleep(s);
	gotoxy(tx + subT, ty + 10);
	cout << "+:+        +:+    +:+  +:+    +:+  +:+   +:+  +:+    +:+ +:+        \n";
	Sleep(s);
	gotoxy(tx + subT, ty + 11);
	cout << "+#++:++#++ +#+    +:+  +#+    +:+ +#++:++#++: +#++:++#:  +#++:++#   \n";
	Sleep(s);
	gotoxy(tx + subT, ty + 12);
	cout << "       +#+ +#+  # +#+  +#+    +#+ +#+     +#+ +#+    +#+ +#+        \n";
	Sleep(s);
	gotoxy(tx + subT, ty + 13);
	cout << "#+#    #+# #+#   +#+   #+#    #+# #+#     #+# #+#    #+# #+#        \n";
	Sleep(s);
	gotoxy(tx + subT, ty + 14);
	cout << " ########   ###### ###  ########  ###     ### ###    ### ########## \n";
	Sleep(s);
}
int Maze::menuDraw() {
	//gotoxy(75, 34);
	//cout << "||";
	int x = 73;
	int y = 37;
	int sY = y;
	gotoxy(x - 2, y);
	cout << ">";
	gotoxy(x, y);
	cout << "Game";
	gotoxy(x, y + 1);
	cout << "Over";
	while (1) {
		int n = KeyControl();
		switch (n)
		{
		case UP: {
			if (y > sY) {
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, --y);
				cout << ">";
			}
			break;
		}
		case DOWN: {
			if (y < sY + 1) {
				gotoxy(x - 2, y);
				cout << " ";
				gotoxy(x - 2, ++y);
				cout << ">";
			}
			break;
		}
		case SUBMIT:
			return y - sY;
		}
	}
}