# include <iostream>
# include <windows.h>
# include <time.h>
# include <conio.h>
# include <direct.h>
# include <io.h> // здесь находятся функции для поиска файлов
using namespace std;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); // получение дескриптора окна
//ширина и высота игрового поля
const int width = 70;
const int height = 30;
//уровни сложности игры,1 активирован уровень 0 неактивирован уровень
int level1 = 1;
int level2 = 0;
int level3 = 0;
/////
int PlayMap[height][width];// игровое поле
int loose = 0; //1 проиграли 2 выиграли 3 скушали себя
int points = 0;// количество собрных очков
int needtowin = 0; // с помощью функции Win считаем сколько на карте яблочек и соответственно для победы надо собрать все яблочки
int ln = 4; // длина змеи 
int a = 0;
COORD* l; // массив координат змеи 
COORD* l2; // резервный массив координат змеи
COORD apples[] = { {72,10},{88,10} };//текст ,кол-во яблочек
COORD control[] = { {72,2},{76,4},{74,5},{76,6},{72,12},{88,12} }; // текст , стрелочка вверх, стрелочки влево вправо , вниз , текст для общего колва яблок ,
COORD c; // переменная, отвечающая за координаты в консоли		
char** load_map = new char* [100];
int Logo() {
	COORD log = { 21,4 };
	SetConsoleCursorPosition(h, log);
	cout << (char)201 << (char)205 << (char)205 << (char)205 << (char)205 << (char)187 << "  " << (char)201 << (char)205 << (char)187 << "  " << (char)201 << (char)205 << (char)187 << "  " << (char)201 << (char)205 << (char)205 << (char)205 << (char)205 << (char)187 << "  " << (char)201 << (char)205 << (char)187 << (char)207 << (char)201 << (char)205 << (char)187 << "  " << (char)201 << (char)205 << (char)187 << (char)201 << (char)205 << (char)205 << (char)205 << (char)187 << "  " << (char)201 << (char)205 << (char)205 << (char)205 << (char)205 << (char)187 << endl;
	log.Y++;
	SetConsoleCursorPosition(h, log);
	cout << (char)200 << (char)205 << (char)205 << (char)187 << " " << (char)186 << "  " << (char)186 << " " << (char)186 << "  " << (char)186 << " " << (char)186 << "  " << (char)186 << " " << (char)201 << (char)205 << (char)205 << (char)188 << "  " << (char)186 << " " << (char)186 << " " << (char)186 << " " << (char)186 << "  " << (char)186 << " " << (char)186 << (char)186 << " " << (char)201 << (char)205 << (char)188 << "  " << (char)186 << " " << (char)201 << (char)187 << " " << (char)186 << endl;
	log.Y++;
	SetConsoleCursorPosition(h, log);
	cout << " " << (char)201 << (char)205 << (char)188 << " " << (char)186 << "  " << (char)186 << " " << (char)200 << (char)187 << (char)201 << (char)188 << " " << (char)186 << "  " << (char)186 << " " << (char)200 << (char)205 << (char)205 << (char)187 << "  " << (char)186 << " " << (char)186 << " " << (char)186 << " " << (char)186 << "  " << (char)186 << " " << (char)200 << (char)188 << " " << (char)186 << "    " << (char)186 << " " << (char)200 << (char)188 << " " << (char)186 << endl;
	log.Y++;
	SetConsoleCursorPosition(h, log);
	cout << " " << (char)200 << (char)205 << (char)187 << " " << (char)186 << "  " << (char)186 << " " << (char)201 << (char)187 << (char)201 << (char)187 << " " << (char)186 << "  " << (char)186 << " " << (char)201 << (char)205 << (char)205 << (char)188 << "  " << (char)186 << " " << (char)186 << " " << (char)186 << " " << (char)186 << "  " << (char)186 << " " << (char)201 << (char)187 << " " << (char)186 << "    " << (char)186 << " " << (char)201 << (char)187 << " " << (char)186 << endl;
	log.Y++;
	SetConsoleCursorPosition(h, log);
	cout << (char)201 << (char)205 << (char)205 << (char)188 << " " << (char)186 << "  " << (char)186 << " " << (char)186 << (char)200 << (char)188 << (char)186 << " " << (char)186 << "  " << (char)186 << " " << (char)200 << (char)205 << (char)205 << (char)187 << "  " << (char)186 << " " << (char)200 << (char)205 << (char)188 << " " << (char)186 << "  " << (char)186 << " " << (char)186 << (char)186 << " " << (char)200 << (char)205 << (char)187 << "  " << (char)186 << " " << (char)186 << (char)186 << " " << (char)186 << endl;
	log.Y++;
	SetConsoleCursorPosition(h, log);
	cout << (char)200 << (char)205 << (char)205 << (char)205 << (char)205 << (char)188 << "  " << (char)200 << (char)205 << (char)188 << "  " << (char)200 << (char)205 << (char)188 << "  " << (char)200 << (char)205 << (char)205 << (char)205 << (char)205 << (char)188 << "  " << (char)200 << (char)205 << (char)205 << (char)205 << (char)205 << (char)205 << (char)188 << "  " << (char)200 << (char)205 << (char)188 << (char)200 << (char)205 << (char)205 << (char)205 << (char)188 << "  " << (char)200 << (char)205 << (char)188 << (char)200 << (char)205 << (char)188 << endl;
	return 0;
}
int Serch() {
	a = 0;
	char path[256]; // адресс
	strcpy_s(path, 255, "Maps\\*.map");
	setlocale(0, "");
	_finddata_t* fileinfo = new _finddata_t; // структура информации о файле
	int first_serch = _findfirst(path, fileinfo); //  занимается поиском группи объектов
	int serch = first_serch;

	setlocale(0, "");

	SetConsoleTextAttribute(h, 1);

	c.X = 20;
	c.Y = 15;
	while (serch != -1) {
		load_map[a] = new char[100];
		strcpy_s(load_map[a], 99, fileinfo->name);
		SetConsoleCursorPosition(h, c);
		cout << a + 1 << " ) " << load_map[a] << endl;
		serch = _findnext(first_serch, fileinfo);
		c.Y += 2;
		a++;
	}
	return 0;
}
int OpenMap() {
	Serch();
	int b = a + 41;
	char* window = new char[256];
	strcpy_s(window, 255, "mode con cols=95 lines=");
	char* num = new char[10];
	_itoa_s(b, num, 9, 10);
	strcat_s(window, 255, num);
	strcat_s(window, 255, "\0");
	cout << window;
	system(window);
	///////////////////////////////
	c.X = 29;
	c.Y = 11;
	SetConsoleCursorPosition(h, c);
	SetConsoleTextAttribute(h, 11);
	cout << "Найденые карты для игры в  \"Змейку\"\n\n";
	SetConsoleTextAttribute(h, 1);

	Serch();

	setlocale(0, "C");
	SetConsoleTextAttribute(h, 12);
	Logo();
	SetConsoleTextAttribute(h, 1);

	COORD ret = { 70,14 };
	SetConsoleCursorPosition(h, ret);
	setlocale(0, "");
	cout << "Назад";/////
	setlocale(0, "C");

	int num_save;
	HANDLE h_in = GetStdHandle(STD_INPUT_HANDLE); // дескриптор окна для работы с мышкой
	INPUT_RECORD all_events[256]; // массив событий, произошедших в консоли
	DWORD read_event; // переменная, в которую запишется количество произошедших событий

	SetConsoleMode(h_in, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	int op = true;
	setlocale(0, "");
	while (op) {
		ReadConsoleInput(h_in, all_events, 256, &read_event); // получить все события, произошедшие в консоли

		for (int i = 0; i < read_event; i++) { // пройтись по всем событиям

			c.X = all_events[i].Event.MouseEvent.dwMousePosition.X; // запомнить координаты мышки
			c.Y = all_events[i].Event.MouseEvent.dwMousePosition.Y;
			setlocale(0, "");
			if (c.X >= ret.X && c.X <= ret.X + 4 && c.Y == ret.Y) {
				SetConsoleTextAttribute(h, 1);
				SetConsoleCursorPosition(h, ret);

				cout << "Назад";
			}
			else {
				SetConsoleTextAttribute(h, 7);
				SetConsoleCursorPosition(h, ret);
				cout << "Назад";
			}
			if (all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
				if (c.X >= ret.X && c.X <= ret.X + 4 && c.Y == ret.Y) {
					SetConsoleMode(h_in, ENABLE_INSERT_MODE);
					loose = 4;
					SetConsoleMode(h_in, ENABLE_MOUSE_INPUT);

					op = false;
					break;
				}

			}
			for (int j = 0; j < a; j++) { // перебор всех пунктов меню

				if (c.X >= 0 && c.X <= 80 && c.Y == 15 + j * 2) {

					COORD t;
					t.X = 20;
					t.Y = c.Y;
					SetConsoleCursorPosition(h, t); // установка координат в то место, где курсор
					SetConsoleTextAttribute(h, 9); // установка цвета
					cout << j + 1 << " ) " << load_map[j];

					for (int r = 0; r < a; r++) {
						if (r != j) {
							COORD w;
							w.X = 20;
							w.Y = 15 + r * 2;
							SetConsoleCursorPosition(h, w); // установка координат в то место, где курсор
							SetConsoleTextAttribute(h, 1); // установка цвета
							cout << r + 1 << " ) " << load_map[r];
						}
					}

					if (all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
						SetConsoleMode(h_in, ENABLE_INSERT_MODE);
						num_save = j;
						op = false;
						SetConsoleMode(h_in, ENABLE_MOUSE_INPUT);
					}

				}
			}
		}
	}
	setlocale(0, "C");
	if (loose != 4) { // если не выбрали пункт НАЗАД выпонялется

		char* load_file_map = new char[256];
		strcpy_s(load_file_map, 255, "Maps\\");
		strcat_s(load_file_map, 255, load_map[num_save]);
		FILE* map;
		fopen_s(&map, load_file_map, "r");

		system("cls");

		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				PlayMap[height][width] = fgetc(map) - 48;
				int atoi(PlayMap[height][width]);
				if (PlayMap[height][width] == 1) {
					SetConsoleTextAttribute(h, 2);
					cout << (char)178;
					PlayMap[y][x] = 1;
				}
				else if (PlayMap[height][width] == 2) {
					SetConsoleTextAttribute(h, 12);
					cout << (char)1;
					PlayMap[y][x] = 2;
				}
				else if (PlayMap[height][width] == 3) {
					SetConsoleTextAttribute(h, 11);
					cout << (char)1;
					PlayMap[y][x] = 3;
				}
				else { cout << " "; PlayMap[y][x] = 0; }

			}
			cout << "\n";
			fgetc(map);

		}
		setlocale(0, "");
		SetConsoleTextAttribute(h, 12);
		SetConsoleCursorPosition(h, apples[0]);
		cout << "Собрано яблок : ";
		SetConsoleCursorPosition(h, apples[1]);
		cout << "0";
		SetConsoleCursorPosition(h, control[0]);
		SetConsoleTextAttribute(h, 10);
		cout << "Управление";

		setlocale(0, "C");

		SetConsoleCursorPosition(h, control[1]);
		cout << (char)24;
		SetConsoleCursorPosition(h, control[2]);
		cout << (char)27 << "   " << (char)26;
		SetConsoleCursorPosition(h, control[3]);
		cout << (char)25;

		setlocale(0, "");
		SetConsoleCursorPosition(h, control[4]);
		cout << "Нужно собрать :";
		SetConsoleCursorPosition(h, control[5]);
		cout << needtowin;
		setlocale(0, "C");
	}
	return 0;
}
int Win() {
	// определяет сколько на карте яблок которых нужно собрать для победы
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (PlayMap[y][x] == 2) { needtowin++; }
		}
	}
	return 0;
}

int Menu(int height, int width, int x, int y) {
	COORD menu = { x,y };
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (menu.X == x && menu.Y == y) { SetConsoleCursorPosition(h, menu); cout << (char)201; }
			else if (menu.X == width - 1 && menu.Y == y) { SetConsoleCursorPosition(h, menu); cout << (char)187; }
			else if (menu.X < width - 1 && menu.Y == y) { SetConsoleCursorPosition(h, menu); cout << (char)205; }
			else if (menu.X == x && menu.Y == height - 1) { SetConsoleCursorPosition(h, menu); cout << (char)200; }
			else if (menu.X == width - 1 && menu.Y == height - 1) { SetConsoleCursorPosition(h, menu); cout << (char)188; }
			else if (menu.X == x && menu.Y < height - 1) { SetConsoleCursorPosition(h, menu); cout << (char)186; }
			else if (menu.X == width - 1 && menu.Y < height - 1) { SetConsoleCursorPosition(h, menu); cout << (char)186; }
			else if (menu.X == x && menu.Y == height - 1) { SetConsoleCursorPosition(h, menu); cout << (char)200; }
			else if (menu.X < width - 1 && menu.Y == height - 1) { SetConsoleCursorPosition(h, menu); cout << (char)205; }
			menu.X++;
		}
		menu.X = x;
		menu.Y++;
	}
	return 0;
}

int Snake() {
	SetConsoleCursorPosition(h, control[5]);
	cout << needtowin;
	int apl = 0;
	l = new COORD[ln]; // выдиление памяти под lm-нное количество координат
	COORD c = { 1,1 }; // координаты головы змеи

	SetConsoleCursorPosition(h, c);
	SetConsoleTextAttribute(h, 10);
	cout << (char)1;

	int b = -1; // направление змеи
	int m = 0; // для прохода и заполнения массива координат змеи (l)
	int move = 0; // показывает сколько раз мы нажали на стрелочки управления,также нужна для проверки не скушала змея себя или нет
	COORD* l = new COORD[ln];
	int des = 0;// для дезарентатора
	int des2 = 0;// для дезарентатора,точнее для конца его работы
	int wi = 1; // переменная нужна просто для выхода из цыкла в определнный момент

	while (wi) {
		if (_kbhit()) {
			int a = _getch(); // получаем код нажатой клавиши			
			if (a == 27) {      //нажатие escap-выход в меню 
				wi = 0;
				loose = 4;
				break;
			}
			if (a == 0 || a == 224) {
				a = _getch();
				move++;
			}
			if (des == 0) {
				if (a == 75 && b != 2) { b = 1; }		// налево
				else if (a == 77 && b != 1) { b = 2; }	// напрво
				else if (a == 72 && b != 4) { b = 3; }	// вниз
				else if (a == 80 && b != 3) { b = 4; }	// вверх
			}

			else if (des == 1) {
				if (a == 75 && b != 1) { b = 2; }		// направо
				else if (a == 77 && b != 2) { b = 1; }	// налево
				else if (a == 72 && b != 3) { b = 4; }	// вверх
				else if (a == 80 && b != 4) { b = 3; }	// вниз

			}


		}

		//// движение 

		if (b == 1)c.X--;
		else if (b == 2)c.X++;
		else if (b == 3)c.Y--;
		else if (b == 4)c.Y++;

		des2++;

		if (des2 == 30) {
			des = 0;
			des2 = 0;
		}

		l[m] = c;
		m++;

		/// проверка не съела ли себя змея

		if (move > 1) {
			for (int i = 0; i < ln - 1; i++) {
				if (c.X == l[i].X && c.Y == l[i].Y) {
					wi = 0;
					loose = 3;
					break;
				}
			}
		}

		/// столкнулись со стенкой

		if (PlayMap[c.Y][c.X] == 1) {
			loose = 1;
			wi = 0;
			break;
		}
		/// наступили на дезарентатор
		else if (PlayMap[c.Y][c.X] == 3) {
			des = 1;
		}
		/// наступили на яблочко 
		else if (PlayMap[c.Y][c.X] == 2) {

			PlayMap[c.Y][c.X] = 0;
			points++;
			ln++;
			/// записываем в резервный массив координаты змеи из основного массива
			l2 = new COORD[ln];
			for (int i = 0; i < ln - 1; i++) {
				l2[i] = l[i];
			}
			delete[] l; // очищаем основной массив координат
			/// пересоздаем основной массив координат змейки с новым выдилением памяти для координат на 1 элемент больше
			l = new COORD[ln];
			for (int i = 0; i < ln - 1; i++) {
				l[i] = l2[i];
			}
			delete[] l2; // очищаем резервный массив координат
			SetConsoleTextAttribute(h, 12);
			SetConsoleCursorPosition(h, apples[1]);
			apl++;
			cout << apl;
		}

		// показываем змейку
		for (int i = 0; i < m; i++) {
			SetConsoleCursorPosition(h, l[i]);
			if (i < m - 1) { SetConsoleTextAttribute(h, 3); cout << "*"; } // хвостик
			else if (i == m - 1) { SetConsoleTextAttribute(h, 10); cout << (char)1; } // голова змейки
		}

		/// проверка на то что собрали мы достаточное количество яблочек или нет
		if (points == needtowin) {
			wi = 0;
			loose = 2;
			b = -1;
			Sleep(2000);
			break;
		}
		/// проверка на уровень сложности,точнее на его активность,если активен первый уровень то змейка медленная
		if (level1 == 1) { // если активен легкий уровень сложности
			Sleep(130);
		}
		else if (level2 == 1) {// если активирован средний уровень сложности
			Sleep(100);
		}
		else if (level3 == 1) {// если активирован тяжелый уровен ьсложности
			Sleep(50);
		}

		/// проверка на то что заполнился массив координат или нет змейки,если да то перезаписывает все елементы и оставляет ln-й элемент пустым для дальнейшей записи и ставит пробел для зарисовки

		if (m == ln) {
			SetConsoleCursorPosition(h, l[0]); cout << " ";
			for (int a = 0; a < ln; a++) {
				l[a] = l[a + 1]; // перехапись элементов
			}
			m--;

		}
	}
	delete[] l;
	b = -1;
	system("cls");
	return 0;
}

int Button(int color1, int color2, int xx, int yy, int height, int width) {
	COORD but = { xx,yy };
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			SetConsoleCursorPosition(h, but);
			SetConsoleTextAttribute(h, color1);
			cout << (char)219;
			but.X++;
		}
		but.Y++;
		but.X = xx;
	}
	/////////////////// кнопочка
	return 0;
}

int ChooseLvl(int choose = 1, int a = 0, int b = 0, int lvl = 0) {
	COORD box = { a,b };
	SetConsoleCursorPosition(h, box);
	for (int y = 0; y < 2; y++) {
		for (int x = 0; x < 3; x++) {
			if (choose == 1 && lvl == 2) { SetConsoleTextAttribute(h, 12); }
			else if (choose == 1 && lvl == 1) { SetConsoleTextAttribute(h, 14); }
			else if (choose == 1 && lvl == 0) { SetConsoleTextAttribute(h, 2); }
			else SetConsoleTextAttribute(h, 7);
			SetConsoleCursorPosition(h, box);
			cout << (char)219;
			box.X++;
		}
		cout << endl;
		box.X = a;
		box.Y++;
	}
	box.X = a + 6;
	box.Y = b + 1;
	setlocale(0, "");
	SetConsoleCursorPosition(h, box);
	if (choose == 1 && lvl == 0) { SetConsoleTextAttribute(h, 2); cout << "Вы выбрали легкий уровень"; }
	else if (choose == 1 && lvl == 1) { SetConsoleTextAttribute(h, 14); cout << "Вы выбрали средний уровень"; }
	else if (choose == 1 && lvl == 2) { SetConsoleTextAttribute(h, 12); cout << "Вы выбрали тяжелый уровень"; }
	setlocale(0, "C");
	return 0;
}

int main() {
	system("title Змейка");
	SetConsoleTextAttribute(h, 12);
	system("mode con cols=95 lines=41");
	CONSOLE_CURSOR_INFO x;
	x.bVisible = false;//сделать невидимым
	x.dwSize = 100;
	SetConsoleCursorInfo(h, &x);

	Logo();

	Menu(40, 95, 0, 0);
	Button(15, 240, 4, 15, 3, 15);
	Button(15, 240, 4, 19, 3, 15);
	setlocale(0, "");

	COORD text[] = { {9,16},{5,20},{35,16} }; // текс : играть ,редактор карт , уровень сложности 
	SetConsoleCursorPosition(h, text[2]);
	SetConsoleTextAttribute(h, 10);
	cout << "Выберите уровень сложности";
	SetConsoleTextAttribute(h, 240);
	SetConsoleCursorPosition(h, text[0]);
	cout << "Играть";
	SetConsoleCursorPosition(h, text[1]);
	cout << "Редактор карт";
	setlocale(0, "C");


	ChooseLvl(level1, 27, 18, 0);
	ChooseLvl(level2, 27, 22, 1);
	ChooseLvl(level3, 27, 26, 2);

	HANDLE h2 = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleMode(h2, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	INPUT_RECORD all_events[256];// все события
	DWORD e;
	COORD a = { 0,0 };
	// для кнопок,для их отрисовки только когда на них наводишь
	int forbuttton1 = 0;
	int forbuttton2 = 0;
	// для кнопок уровня сложности,для их отрисовки только когда на них наводишь
	int forbox1 = 0;
	int forbox2 = 0;
	int forbox3 = 0;

	int hg = 1;// для входи и выхода из массива
	while (hg) {
		ReadConsoleInput(h2, all_events, 256, &e);

		for (int i = 0; i < e; i++) {
			a.X = all_events[i].Event.MouseEvent.dwMousePosition.X;
			a.Y = all_events[i].Event.MouseEvent.dwMousePosition.Y;
			if (a.X >= 4 && a.X <= 18 && a.Y >= 15 && a.Y <= 17) {

				if (forbuttton1 == 0) {
					forbuttton1++;
					Button(7, 240, 4, 15, 3, 15);
					SetConsoleCursorPosition(h, text[0]);
					SetConsoleTextAttribute(h, 127);
					setlocale(0, "");
					cout << "Играть";
					setlocale(0, "C");
				}
			}
			else {
				if (forbuttton1 == 1) {
					forbuttton1 = 0;
					Button(15, 240, 4, 15, 3, 15);
					SetConsoleCursorPosition(h, text[0]);
					SetConsoleTextAttribute(h, 240);
					setlocale(0, "");
					cout << "Играть";
					setlocale(0, "C");
				}
			}
			if (a.X >= 4 && a.X <= 18 && a.Y >= 19 && a.Y <= 21) {
				if (forbuttton2 == 0) {
					forbuttton2++;
					Button(7, 240, 4, 19, 3, 15);
					SetConsoleCursorPosition(h, text[1]);
					SetConsoleTextAttribute(h, 127);
					setlocale(0, "");
					cout << "Редактор карт";
					setlocale(0, "C");
				}
			}
			else {
				if (forbuttton2 == 1) {
					forbuttton2 = 0;
					Button(15, 240, 4, 19, 3, 15);
					SetConsoleCursorPosition(h, text[1]);
					SetConsoleTextAttribute(h, 240);
					setlocale(0, "");
					cout << "Редактор карт";
					setlocale(0, "C");
				}
			}
			if (a.X >= 27 && a.X <= 29 && a.Y >= 18 && a.Y <= 19) {
				if (level1 != 1 && forbox1 == 0) {
					forbox1++;
					ChooseLvl(1, 27, 18, 0);
				}
			}
			else {
				if (forbox1 == 1 && level1 != 1) {
					forbox1 = 0;
					ChooseLvl(0, 27, 18, 0);
					cout << "                                  ";
				}
			}
			if (a.X >= 27 && a.X <= 29 && a.Y >= 22 && a.Y <= 23) {
				if (level2 != 1 && forbox2 == 0) {
					forbox2++;
					ChooseLvl(1, 27, 22, 1);
				}
			}
			else {
				if (forbox2 == 1 && level2 != 1) {
					forbox2 = 0;
					ChooseLvl(0, 27, 22, 1);
					cout << "                                  ";
				}
			}
			if (a.X >= 27 && a.X <= 29 && a.Y >= 26 && a.Y <= 27) {
				if (level3 != 1 && forbox3 == 0) {
					forbox3++;
					ChooseLvl(1, 27, 26, 2);
				}
			}
			else {
				if (forbox3 == 1 && level3 != 1) {
					forbox3 = 0;
					ChooseLvl(0, 27, 26, 2);
					cout << "                                  ";
				}
			}
			//////////////////////////////////////// теперь отлавливание на нажитие
			if (all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
				SetConsoleCursorPosition(h, a);

				if (a.X >= 27 && a.X <= 29 && a.Y >= 18 && a.Y <= 19) {
					level1 = 1;
					level2 = 0;
					level3 = 0;
					ChooseLvl(level1, 27, 18, 0);

				}
				if (a.X >= 27 && a.X <= 29 && a.Y >= 22 && a.Y <= 23) {
					level1 = 0;
					level2 = 1;
					level3 = 0;
					ChooseLvl(level2, 27, 22, 1);
					ChooseLvl(level1, 27, 18, 0);
					a.X = 30;
					a.Y = 19;
					SetConsoleCursorPosition(h, a);
					cout << "                                       ";

				}

				if (a.X >= 27 && a.X <= 29 && a.Y >= 26 && a.Y <= 27) {
					level1 = 0;
					level2 = 0;
					level3 = 1;
					ChooseLvl(level3, 27, 26, 2);
					ChooseLvl(level1, 27, 18, 0);
					a.X = 30;
					a.Y = 19;
					SetConsoleCursorPosition(h, a);
					cout << "                                       ";
				}
				if (a.X >= 4 && a.X <= 18 && a.Y >= 15 && a.Y <= 17) {
					SetConsoleTextAttribute(h, 7);
					system("cls");
					OpenMap();
					if (loose != 4) {
						Win();
						Snake();
					}
					hg = 0;
				}
				if (a.X >= 4 && a.X <= 18 && a.Y >= 19 && a.Y <= 21) {
					system("color 7");
					SetConsoleCursorPosition(h, text[1]);
					SetConsoleTextAttribute(h, 127);
					setlocale(0, "");
					cout << "Редактор карт";
					setlocale(0, "C");
					SetConsoleCursorPosition(h, text[0]);
					SetConsoleTextAttribute(h, 127);
					setlocale(0, "");
					cout << "Играть";
					setlocale(0, "C");
					COORD load = { 35,38 };
					SetConsoleCursorPosition(h, load);
					SetConsoleTextAttribute(h, 15);
					cout << "Loading";
					for (int i = 0; i < 6; i++) {
						cout << " .";
						Sleep(1000);
					}
					system("start redaktor_snake(2008).exe");
					system("taskkill -im Snake.exe -f");
				}
			}
		}
	}
	setlocale(0, "");
	if (loose == 1) { cout << "Вы проиграли!"; }
	else if (loose == 2) { cout << "Вы выиграли!"; }
	else if (loose == 3) { cout << "Вы скушали сами себя :("; }
	cout << endl << endl;
	SetConsoleTextAttribute(h, 12);
	if (loose != 4) {
		cout << "Вы набрали : " << points;
		if (points % 10 == 1 && points % 100 != 11) cout << " очко\n";
		else if ((points % 10 == 2 || points % 10 == 3 || points % 10 == 4) && points % 100 != 12 && points % 100 != 13 && points % 100 != 14) cout << " очка\n";
		else cout << " очков\n\n\n";
		cout << "Нажмите клавишу Enter для возврата в меню";

		while (true) {// проверка на нажатие Enter-а
			int y = _getch();
			if (y == 13) break;
		}
	}
	setlocale(0, "C");
	level1 = 1;
	level2 = 0;
	level3 = 0;
	loose = 0;
	points = 0;
	needtowin = 0;
	ln = 4;
	main();
}