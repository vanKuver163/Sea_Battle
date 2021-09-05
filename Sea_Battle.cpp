#include <iostream>
#include <algorithm>
#include <vector>
#include <time.h>
#include <windows.h>
using namespace std;

const int xPolePlayer = 2;
const int xPoleComp = 25;


//функция управления курсором 
void Cursor(int x, int y)
{
	COORD position = { x, y }; //позиция x и y
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsole, position);
}
//рисуем окантовку игрового поля 
void Edging()
{
	cout << "%" << "|" << "А " << "Б " << "В " << "Г " << "Д " <<
		"Е " << "Ж " << "З " << "И " << "К " << "|";
	cout << "%" << "|" << "А " << "Б " << "В " << "Г " << "Д " <<
		"Е " << "Ж " << "З " << "И " << "К " << "|" << endl;
	for (int i = 0; i < 46; i++) cout << "=";
	for (int i = 0; i < 10; i++)
	{
		Cursor(0, i + 2);	cout << i << "|";
		Cursor(22, i + 2); cout << "|" << i << "|" << endl;
		Cursor(45, i + 2); cout << "|" << endl;
	}
	for (int i = 0; i < 46; i++) cout << "=";
	cout << endl;
}
//переводим буквы в цифры
int letters(char a)
{
	switch (a)
	{
	case 'А': return 0;
		break;
	case 'Б': return 1;
		break;
	case 'В': return 2;
		break;
	case 'Г': return 3;
		break;
	case 'Д': return 4;
		break;
	case 'Е': return 5;
		break;
	case 'Ж': return 6;
		break;
	case 'З': return 7;
		break;
	case 'И': return 8;
		break;
	case 'К': return 9;
		break;
	}
}
//переводим цифры в буквы
char numbers(int a)
{
	switch (a)
	{
	case 0: return 'А';
		break;
	case 1: return 'Б';
		break;
	case 2: return 'В';
		break;
	case 3: return 'Г';
		break;
	case 4: return 'Д';
		break;
	case 5: return 'Е';
		break;
	case 6: return 'Ж';
		break;
	case 7: return 'З';
		break;
	case 8: return 'И';
		break;
	case 9: return 'К';
		break;
	}
}
// рисуем корабли в поле
void PoleShip(int a, int c, int p, vector<char>& Pole, const int xPole, bool comp)
{
	if (c == 0)													// "р"-палубный корабль рисуется вверх
	{
		for (int i = a - ((p - 1) * 10); i <= a; i += 10)
			Pole[i] = '@';
	}
	else if (c == 1)											// "р"-палубный корабль рисуется вниз
	{
		for (int i = a; i <= a + ((p - 1) * 10); i += 10)
			Pole[i] = '@';
	}
	else if (c == 2)											// "р"-палубный корабль рисуется влево
	{
		for (int i = a - (p - 1); i <= a; i++)
			Pole[i] = '@';
	}
	else if (c == 3)											// "р"-палубный корабль рисуется вправо								
	{
		for (int i = a; i <= a + (p - 1); i++)
			Pole[i] = '@';
	}
	if (comp == true) return;
	for (int i = 0; i < Pole.size(); i += 10)					// рисуем корабль в поле
	{
		Cursor(xPole, (2 + (i / 10)));
		for (int j = 0; j < Pole.size() / 10; j++)
		{
			cout << Pole[i + j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
//убираем одно значение из вектора
void decreaseOne(int a, vector<int>& range)
{
	vector<int>rangeNew;
	for (int i = 0; i < range.size(); i++)		//заполняем новый вектор без значения "а"
	{
		int temp = range[i];
		if (temp == a)
		{
			continue;
		}
		rangeNew.push_back(temp);
	}
	range.clear();								//очищаем старый вектор
	for (int i = 0; i < rangeNew.size(); i++)	//переписываем новый вектор в старый
	{
		int temp = rangeNew[i];
		range.push_back(temp);
	}
	rangeNew.clear();							//очищаем новый вектор
}
//убираем несколько значение из вектора
void decreaseSome(vector<int>& range, vector<int>& star)
{
	vector<int>rangeNew;
	for (int i = 0; i < 100; i++)				//заполняем новый вектор без значений вектора "star"
	{
		int temp = 0;
		for (int j = 0; j < star.size(); j++)
		{
			if (i == star[j])
			{
				temp = 1;
				break;
			}
		}
		if (temp == 1) continue;
		else rangeNew.push_back(i);
	}
	range.clear();								//очищаем старый вектор
	for (int i = 0; i < rangeNew.size(); i++)   //переписываем новый вектор в старый
	{
		int temp = rangeNew[i];
		range.push_back(temp);
	}
	rangeNew.clear();							//очищаем новый вектор
}
// проверка игрового поля
int Check(int a, int p, vector<char>& temp)
{
	vector<int>Route;													//вектор с возможными направлениями расположения корабля
	int up = a - ((p - 1) * 10);
	int down = a + ((p - 1) * 10);
	int left = (a % 10) - (p - 1);
	int right = (a % 10) + (p - 1);
	int left1 = a - (p - 1);
	int right1 = a + (p - 1);
	if (temp[a] == '*')return 7;										//если переменная "а" уже занята, выдаем ошибку, ищем новую переменную "а"
	if (up >= 0 && temp[up] != '*') Route.push_back(0);					//вверх
	if (down < 100 && temp[down] != '*') Route.push_back(1);			//вниз
	if (left >= 0 && temp[left1] != '*') Route.push_back(2);			//влево
	if (right < 10 && temp[right1] != '*') Route.push_back(3);			//вправо
	if (Route.size() == 0) return 7;									//если вектор не заполнен выдаем ошибку, ищем новую переменную "а"
	int c = rand() % Route.size();										//рандомно находим значения направления расположения корабля
	return Route[c];													//возвращам направление "с"
}
//находим зоны кораблей
void Zona(int c, int a, int p, vector<int>& star)
{
	switch (c)
	{
	case 0:
		if (a % 10 == 0)
		{
			for (int i = (a - (p * 10)); i <= (a + 10); i += 10)
			{
				for (int j = -1; j <= 1; j++)
				{
					if (i + j < 0 || j < 0 || i + j > 99) continue;
					else star.push_back(i + j);
				}
			}
		}
		else if (a % 10 == 9)
		{
			for (int i = (a - (p * 10)); i <= (a + 10); i += 10)
			{
				for (int j = -1; j <= 1; j++)
				{
					if (i + j < 0 || j > 0 || i + j > 99) continue;
					else star.push_back(i + j);
				}
			}
		}
		else
		{
			for (int i = (a - (p * 10)); i <= (a + 10); i += 10)
			{
				for (int j = -1; j <= 1; j++)
				{
					if (i + j < 0 || i + j > 99) continue;
					else star.push_back(i + j);
				}
			}
		}
		break;
	case 1:
		if (a % 10 == 0)
		{
			for (int i = (a - 10); i <= (a + (p * 10)); i += 10)
			{
				for (int j = -1; j <= 1; j++)
				{
					if (i + j < 0 || j < 0 || i + j > 99) continue;
					else star.push_back(i + j);
				}
			}
		}
		else if (a % 10 == 9)
		{
			for (int i = (a - 10); i <= (a + (p * 10)); i += 10)
			{
				for (int j = -1; j <= 1; j++)
				{
					if (i + j <= 0 || j > 0 || i + j > 99) continue;
					else star.push_back(i + j);
				}
			}
		}
		else
		{
			for (int i = (a - 10); i <= (a + (p * 10)); i += 10)
			{
				for (int j = -1; j <= 1; j++)
				{
					if (i + j < 0 || i + j > 99) continue;
					else star.push_back(i + j);
				}
			}
		}
		break;
	case 2:
		if (a % 10 == 9)
		{
			for (int i = ((a - 10) / 10) * 10; i <= ((a + 10) / 10) * 10; i += 10)
			{
				for (int j = (a % 10) - p; j <= (a % 10) + 1; j++)
				{
					if (i + j < 0 || j > 9 || i + j > 99) continue;
					else star.push_back(i + j);
				}
			}
		}
		else if (a % 10 == (p - 1))
		{
			for (int i = ((a - 10) / 10) * 10; i <= ((a + 10) / 10) * 10; i += 10)
			{
				for (int j = (a % 10) - p; j <= (a % 10) + 1; j++)
				{
					if (i + j < 0 || j < 0 || i + j > 99) continue;
					else star.push_back(i + j);
				}
			}
		}
		else
		{
			for (int i = ((a - 10) / 10) * 10; i <= ((a + 10) / 10) * 10; i += 10)
			{
				for (int j = (a % 10) - p; j <= (a % 10) + 1; j++)
				{
					if (i + j < 0 || i + j > 99) continue;
					else star.push_back(i + j);
				}
			}
		}
		break;
	case 3:
		if (a % 10 == 0)
		{
			for (int i = ((a - 10) / 10) * 10; i <= ((a + 10) / 10) * 10; i += 10)
			{
				for (int j = (a % 10) - 1; j <= (a % 10) + p; j++)
				{
					if (i + j < 0 || j < 0 || i + j > 99) continue;
					else star.push_back(i + j);
				}
			}
		}
		else if (a % 10 == (10 - p))
		{
			for (int i = ((a - 10) / 10) * 10; i <= ((a + 10) / 10) * 10; i += 10)
			{
				for (int j = (a % 10) - 1; j <= (a % 10) + p; j++)
				{
					if (i + j < 0 || j > 9 || i + j > 99) continue;
					else star.push_back(i + j);
				}
			}
		}
		else
		{
			for (int i = ((a - 10) / 10) * 10; i <= ((a + 10) / 10) * 10; i += 10)
			{
				for (int j = (a % 10) - 1; j <= (a % 10) + p; j++)
				{
					if (i + j < 0 || i + j > 99) continue;
					else star.push_back(i + j);
				}
			}
		}
		break;
	}
}
//заполняем зоны кораблей
void fillingStars(vector<int>& star, vector<char>& tempPlayer)
{
	for (int i = 0; i < 100; i++)
	{
		int temp = 0;
		for (int j = 0; j < star.size(); j++)
		{
			if (i == star[j])
			{
				temp = 1;
				break;
			}
		}
		if (temp == 1)  tempPlayer.push_back('*');
		else tempPlayer.push_back('_');
	}
}
//ставим корабли
void placingShip(vector<char>& Pole, const int xPole, bool comp)
{
	//ставим корабли в поле игрока
	vector<char>temp;						//мнимое поле игрока 10х10 заполняем '_'
	for (int i = 0; i < 100; i++)
	{
		temp.push_back('_');
	}
	vector<int>range;						//вектор значений из которых будем ставить корабли 10х10=100 
	for (int i = 0; i < 100; i++)
	{
		range.push_back(i);
	}
	vector<int>star;						//зоны кораблей
	static int a = 0;						//точка установки корабля
	static int c = 0;						//направление установки корабля
	if (comp == true)
	{
		for (int i = 0; i < Pole.size(); i += 10)					// рисуем поле
		{
			Cursor(xPole, (2 + (i / 10)));
			for (int j = 0; j < Pole.size() / 10; j++)
			{
				cout << Pole[i + j] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
	for (int i = 1; i <= 4; i++)			//ставим корабли
	{
		for (int j = 1; j <= i; j++)
		{
			while (true)
			{
				int b = rand() % range.size();		//рандомим значение из вектора "range"
				a = range[b];						//получаем точку установки корабля
				decreaseOne(a, range);				//удаляем точку установки корабля из вектора "range"
				c = Check(a, (5 - i), temp);			//проверяем точку установки корабля	и находим направлене установки 
				if (c != 7)break;					//если напрвление найдено выходим из цикла, если нет повторяем
			}
			Zona(c, a, (5 - i), star);				//вектор "star" заполняем зоной корабля
			decreaseSome(range, star);				//удаляем зону корабля из вектора "range"
			PoleShip(a, c, (5 - i), Pole, xPole, comp);	//рисуем корабль
			temp.clear();							// очищаем мнимое поле
			fillingStars(star, temp);				//заполняем мнимое поле заного с учетом зоны корабля (зона корабля "*")
		}
	}
	star.clear();
}
//заполнение зоны убитого корабля
void ZonaNew(int c, int a, int p, vector<char>& Pole)
{
	if (c == 0)
	{
		if (a % 10 == 0)
		{
			for (int i = (a - 10); i <= (a + (p * 10)); i += 10)
			{
				for (int j = -1; j <= 1; j++)
				{
					if (i + j < 0 || j < 0 || i + j > 99) continue;
					else if (Pole[i + j] == 'X') continue;
					else Pole[i + j] = 'O';
				}
			}
		}
		else if (a % 10 == 9)
		{
			for (int i = (a - 10); i <= (a + (p * 10)); i += 10)
			{
				for (int j = -1; j <= 1; j++)
				{
					if (i + j <= 0 || j > 0 || i + j > 99) continue;
					else if (Pole[i + j] == 'X') continue;
					else Pole[i + j] = 'O';
				}
			}
		}
		else
		{
			for (int i = (a - 10); i <= (a + (p * 10)); i += 10)
			{
				for (int j = -1; j <= 1; j++)
				{
					if (i + j < 0 || i + j > 99) continue;
					else if (Pole[i + j] == 'X') continue;
					else Pole[i + j] = 'O';
				}
			}
		}
	}
	else if (c == 1)
	{
		if (a % 10 == 0)
		{
			for (int i = ((a - 10) / 10) * 10; i <= ((a + 10) / 10) * 10; i += 10)
			{
				for (int j = (a % 10) - 1; j <= (a % 10) + p; j++)
				{
					if (i + j < 0 || j < 0 || i + j > 99) continue;
					else if (Pole[i + j] == 'X') continue;
					else Pole[i + j] = 'O';
				}
			}
		}
		else if (a % 10 == (10 - p))
		{
			for (int i = ((a - 10) / 10) * 10; i <= ((a + 10) / 10) * 10; i += 10)
			{
				for (int j = (a % 10) - 1; j <= (a % 10) + p; j++)
				{
					if (i + j < 0 || j > 9 || i + j > 99) continue;
					else if (Pole[i + j] == 'X') continue;
					else Pole[i + j] = 'O';
				}
			}
		}
		else
		{
			for (int i = ((a - 10) / 10) * 10; i <= ((a + 10) / 10) * 10; i += 10)
			{
				for (int j = (a % 10) - 1; j <= (a % 10) + p; j++)
				{
					if (i + j < 0 || i + j > 99) continue;
					else if (Pole[i + j] == 'X') continue;
					else Pole[i + j] = 'O';
				}
			}
		}
	}
}
// проверка выстрела игрока
int checkShot(int shot, vector<char>& Opponent, bool Comp)
{
	if (Opponent[shot] == '_')										//если промах	
	{
		Opponent[shot] = 'O';
		return 0;
	}
	if (Opponent[shot] == '@')										//если попал
	{
		Opponent[shot] = 'X';
		for (int i = (shot - 10); i >= (shot - 30); i -= 10)
		{
			if (i < 0) break;
			else if (Opponent[i] == '@') return 1;
			else if (Opponent[i] == 'X') continue;
			else break;
		}
		for (int i = (shot + 10); i <= (shot + 30); i += 10)
		{
			if (i > 99) break;
			else if (Opponent[i] == '@') return 1;
			else if (Opponent[i] == 'X') continue;
			else break;
		}
		for (int i = (shot - 1); i >= (shot - 3); i--)
		{
			if (i < 0) break;
			else if (i % 10 == 9) break;
			else if (Opponent[i] == '@') return 1;
			else if (Opponent[i] == 'X') continue;
			else break;
		}
		for (int i = (shot + 1); i <= (shot + 3); i++)
		{
			if (i % 10 == 0) break;
			else if (Opponent[i] == '@') return 1;
			else if (Opponent[i] == 'X') continue;
			else break;
		}
		vector<int>Shot;										//если убил 
		Shot.push_back(shot);									//заполняем вектор попаданиями
		for (int i = (shot - 10); i >= (shot - 30); i -= 10)
		{
			if (i < 0) continue;
			else if (Opponent[i] == 'X')Shot.push_back(i);
			else break;
		}
		for (int i = (shot + 10); i <= (shot + 30); i += 10)
		{
			if (i > 99) continue;
			else if (Opponent[i] == 'X')Shot.push_back(i);
			else break;
		}
		for (int i = (shot - 1); i >= (shot - 3); i--)
		{
			if (i < 0) continue;
			else if (i % 10 == 9) continue;
			else if (Opponent[i] == 'X')Shot.push_back(i);
			else break;
		}
		for (int i = (shot + 1); i <= (shot + 3); i++)
		{
			if (i % 10 == 0) continue;
			else if (Opponent[i] == 'X')Shot.push_back(i);
			else break;
		}
		sort(Shot.begin(), Shot.end());
		int a = Shot[0];
		int p = Shot.size();									 //кол-во палуб корабля
		int c = 0;												 //положение корабля
		if (Shot.size() == 1) c = 0;							 // вертикаль
		else if ((Shot[1] - Shot[0]) == 1) c = 1;                // горизонт		
		ZonaNew(c, a, p, Opponent);								 //рисуем зону убитого корабля
		if (Comp == true) Cursor(0, 19);
		else Cursor(0, 16);
		return 2;
	}
}
//рисуем поле компьютера
void PoleCompBattle(vector<char>& Comp)
{
	for (int i = 0; i < Comp.size(); i += 10)
	{
		Cursor(25, (2 + (i / 10)));
		for (int j = 0; j < Comp.size() / 10; j++)
		{	
			if (Comp[i + j]=='@')cout << "_ ";
			else cout << Comp[i + j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
//проверка ввода букв
bool chekRow(char a)
{
	char arr[] = { 'А', 'Б', 'В', 'Г', 'Д', 'Е', 'Ж', 'З', 'И', 'К' };
	for (int i = 0; i < strlen(arr); i++)
	{
		if (a == arr[i]) return 0;
	}
	return 1;
}
//проверка ввода цифр
bool chekCol(char b)
{
	char arr[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
	for (int i = 0; i < strlen(arr); i++)
	{
		if (b == arr[i]) return 0;
	}
	return 1;
}
//ход игрока
int movePlayer(vector<char>& Comp)
{
	int col;                                                 //строка
	char row;												 //столбец	
	char ch;
	while (true)
	{
		while (true)
		{
			Cursor(0, 13);
			cout << "                                           ";
			Cursor(0, 13);
			cout << "Ваш выстрел (введите строку): ";
			ch = getchar();
			bool flag = chekCol(ch);
			if (flag == false)
			{
				col = (int)ch - 48;
				cout << col << endl;
				break;
			}
		}
		while (true)
		{
			Cursor(0, 14);
			cout << "                                           ";
			Cursor(0, 14);
			cout << "Ваш выстрел (введите столбец): ";
			row = getchar();
			bool flag = chekRow(row);
			if (flag == false)break;
		}
		int shot = (col * 10) + letters(row);					 //высчитываем выстрел	
		int temp = checkShot(shot, Comp, false);						 //проверка выстрела игрока
		PoleCompBattle(Comp);									 //рисуем поле компьютера					
		Cursor(0, 15);
		cout << "                                           ";
		Cursor(0, 15);
		if (temp == 0)											 //если промах
		{
			cout << "Промах " << endl;
			break;
		}
		else if (temp == 1)											 //если попал
		{
			cout << "Попадание " << endl;
			//return 1;
		}
		else if (temp == 2)											 //если убил
		{
			cout << "Убил " << endl;
			int ship = 0;
			for (int i = 0; i < 100; i++)						 //проверка на наличее кораблей в поле компьютера
			{
				if (Comp[i] == 'X')
				{					
					ship++;
				}				
			}
			if (ship == 20)
			{
				cout << "Вы победили!!!" << endl;
				return 0;
			}
		}			
	}
}
//рисуем поле игрока
void PolePlayerBattle(vector<char>& Player)
{
	for (int i = 0; i < Player.size(); i += 10)
	{
		Cursor(2, (2 + (i / 10)));
		for (int j = 0; j < Player.size() / 10; j++)
		{
			cout << Player[i + j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
//проверка всех ходов компьютера
void fillingStarsComp(vector<int>& star, vector<char>& Player)
{
	for (int i = 0; i < Player.size(); i += 10)
	{
		for (int j = 0; j < Player.size() / 10; j++)
		{
			if ((Player[i + j] == 'X') || (Player[i + j] == 'O')) star.push_back(i + j);
		}
	}
}

int firstStepComp(vector<int>& rangeComp, vector<char>& Player, int shot)
{
	Cursor(0, 22);
	int col = shot / 10;
	char row = numbers(shot % 10);
	Cursor(0, 17);
	cout << "                                           ";
	Cursor(0, 17);
	cout << "Выстрел компьютера (строка): " << col;
	Cursor(0, 18);
	cout << "                                           ";
	Cursor(0, 18);
	cout << "Выстрел компьютера (столбец): " << row;
	int temp = checkShot(shot, Player, true);
	PolePlayerBattle(Player);
	Cursor(0, 19);
	cout << "                                           ";
	Cursor(0, 19);
	return temp;
}

void killShip(vector<int>& rangeComp, vector<char>& Player, vector<int>& tempShotComp)
{
	vector<int>StarComp;
	fillingStarsComp(StarComp, Player);
	decreaseSome(rangeComp, StarComp);
	tempShotComp.clear();
	cout << "Убил " << endl;
}

int moveComp(vector<int>& rangeComp, vector<char>& Player, vector<char>& Comp, vector<int>& tempShotComp, vector<int>& hit)
{
	int temp;
	int shot;
	int b;	
	static int hitComp = 0;	
	while (true)
	{
		if (hitComp == 0)
		{
			b = rand() % rangeComp.size();
			shot = rangeComp[b];
			decreaseOne(shot, rangeComp);
			temp = firstStepComp(rangeComp, Player, shot);
			if (temp == 0)
			{
				cout << "Промах " << endl;
				system("pause");
				break;
			}
			if (temp == 1)
			{
				cout << "Попадание " << endl;
				hit.push_back(shot);				
				for (int i = shot - 10; i <= shot + 10; i += 20)
				{
					if (i < 0) continue;
					else if (i > 99)continue;
					else if (Player[i] == 'O') continue;
					else tempShotComp.push_back(i);
				}
				for (int i = shot - 1; i <= shot + 1; i += 2)
				{
					if (i < 0) continue;
					else if ((i / 10) != (shot / 10)) continue;
					else if (Player[i] == 'O') continue;
					else tempShotComp.push_back(i);
				}				
				hitComp++;
				system("pause");
			}
			if (temp == 2)
			{
				killShip(rangeComp, Player, tempShotComp);
				hitComp = 0;
				system("pause");				
			}
		}
		else if (hitComp == 1)
		{
			if (tempShotComp.size() == 1)	shot = tempShotComp[0];
			else
			{
				b = rand() % tempShotComp.size();
				shot = tempShotComp[b];
			}
			decreaseOne(shot, tempShotComp);

			temp = firstStepComp(rangeComp, Player, shot);
			if (temp == 0)
			{
				cout << "Промах " << endl;			
				system("pause");
				break;
			}
			if (temp == 1)
			{
				cout << "Попадание " << endl;
				tempShotComp.clear();
				hit.push_back(shot);				
				sort(hit.begin(), hit.end());
				if ((hit[1] - hit[0]) == 10)
				{
					int a = hit[0] - 10;
					if (a > 0 && Player[a] != 'O' && Player[a] != 'X')
					{
						tempShotComp.push_back(a);
					}
					a = hit[1] + 10;
					if (a < 99 && Player[a] != 'O' && Player[a] != 'X')
					{
						tempShotComp.push_back(a);
					}
				}
				else if ((hit[1] - hit[0]) == 1)
				{
					int a = hit[0] - 1;
					if (a > 0 && a % 10 != 9 && Player[a] != 'O' && Player[a] != 'X')
					{

						tempShotComp.push_back(a);
					}
					a = hit[1] + 1;
					if (a % 10 != 0 && Player[a] != 'O' && Player[a] != 'X')
					{
						tempShotComp.push_back(a);
					}
				}				
				hitComp++;
				system("pause");
			}
			if (temp == 2)
			{
				killShip(rangeComp, Player, tempShotComp);
				hit.clear();
				hitComp = 0;
				system("pause");				
			}
		}
		else if (hitComp == 2)
		{
			if (tempShotComp.size() == 1)	shot = tempShotComp[0];
			else
			{
				b = rand() % tempShotComp.size();
				shot = tempShotComp[b];
			}
			decreaseOne(shot, tempShotComp);
			temp = firstStepComp(rangeComp, Player, shot);
			if (temp == 0)
			{
				cout << "Промах " << endl;			
				system("pause");
				break;
			}
			if (temp == 1)
			{
				cout << "Попадание " << endl;
				tempShotComp.clear();
				hit.push_back(shot);
				sort(hit.begin(), hit.end());
				if ((hit[1] - hit[0]) == 10)
				{
					int a = hit[0] - 10;
					if (a > 0 && Player[a] != 'O' && Player[a] != 'X')
					{

						tempShotComp.push_back(a);
					}
					a = hit[0] + 30;
					if (a < 99 && Player[a] != 'O' && Player[a] != 'X')
					{

						tempShotComp.push_back(a);
					}
				}
				else if ((hit[1] - hit[0]) == 1)
				{
					int a = hit[0] - 1;
					if (a > 0 && a % 10 != 9 && Player[a] != 'O' && Player[a] != 'X')
					{
						tempShotComp.push_back(a);
					}
					a = hit[0] + 3;
					if (a % 10 != 0 && Player[a] != 'O' && Player[a] != 'X')
					{

						tempShotComp.push_back(a);
					}
				}				
				hitComp++;
				system("pause");
			}
			if (temp == 2)
			{
				killShip(rangeComp, Player, tempShotComp);
				hit.clear();
				hitComp = 0;
				system("pause");				
			}
		}
		else if (hitComp == 3)
		{
			if (tempShotComp.size() == 1)	shot = tempShotComp[0];
			else
			{
				b = rand() % tempShotComp.size();
				shot = tempShotComp[b];
			}
			decreaseOne(shot, tempShotComp);
			temp = firstStepComp(rangeComp, Player, shot);
			if (temp == 0)
			{
				cout << "Промах " << endl;
				system("pause");
				break;
			}
			if (temp == 2)
			{
				killShip(rangeComp, Player, tempShotComp);
				hit.clear();
				hitComp = 0;
				system("pause");				
			}
		}	
		int ship = 0;
		for (int i = 0; i < 100; i++)						 //проверка на наличее кораблей в поле компьютера
		{
			if (Player[i] == 'X')
			{
				ship++;
			}
		}
		if (ship == 20)
		{
			cout << "Компьютер победил!!!" << endl;
			return 0;
		}
	}	
	return 1;
}
//тупой комп
int moveCompStuped(vector<int>& rangeComp, vector<char>& Player, vector<char>& Comp, vector<int>& tempShotComp)
{
	int temp;
	int shot;
	int b;		
	while (true)
	{
		b = rand() % rangeComp.size();
		shot = rangeComp[b];
		decreaseOne(shot, rangeComp);
		temp = firstStepComp(rangeComp, Player, shot);
		if (temp == 0)
		{
			cout << "Промах " << endl;
			system("pause");
			break;
		}
		if (temp == 1)
		{
			cout << "Попадание " << endl;		
			system("pause");
		}
		if (temp == 2)
		{
			killShip(rangeComp, Player, tempShotComp);			
			system("pause");
		}
		int ship = 0;
		for (int i = 0; i < 100; i++)						 //проверка на наличее кораблей в поле компьютера
		{
			if (Player[i] == 'X')
			{
				ship++;
			}
		}
		if (ship == 20)
		{
			cout << "Компьютер победил!!!" << endl;
			return 0;
		}
	}
	return 1;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));
	vector<char>Player;
	for (int i = 0; i < 100; i++)
		Player.push_back('_');
	vector<char>Comp;
	for (int i = 0; i < 100; i++)
		Comp.push_back('_');
	vector<int>rangeComp;
	vector<int>tempShotComp;
	vector<int> hit;
	for (int i = 0; i < 100; i++)
	{
		rangeComp.push_back(i);
	}	
	int victory;	
	bool complexity;
	bool start = rand() % 2;	
	cout << "Выбор сложности компьютера (0-слабый / 1-сильный): ";	
	cin >> complexity;
	system("cls");
	Edging();
	placingShip(Player, xPolePlayer, false);
	placingShip(Comp, xPoleComp, true);
	while (true)
	{		
		if (start && !movePlayer(Comp)) break;
		if (complexity && !moveComp(rangeComp, Player, Comp, tempShotComp, hit)) break;
		if (!complexity && !moveCompStuped(rangeComp, Player, Comp, tempShotComp)) break;
		if (!start && !movePlayer(Comp)) break;
	}
}