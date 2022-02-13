#include "Bmp.h"
using namespace std;

void SearchWay(int** map,int size)
{
	int x = 0;
	int y = 0;
	int x_to = 0; 
	int y_to = 0;
	int*** wave_matrix = new int** [size];
	for (int i = 0; i < size; i++) {
		wave_matrix[i] = new int* [size];
		for (int j = 0; j < size; j++) {
			wave_matrix[i][j] = new int[3];
		}
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (map[i][j] == 9) {
				x = i;
				y = j;
				map[i][j] = 2;
			}
			if (map[i][j] == 10) {
				x_to = i;
				y_to = j;
				map[i][j] = 2;
			}
		}
	}
	int step;
	bool added = true, result = true;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (map[i][j]!= 2)
			{
				wave_matrix[i][j][0] = -2;// занято
			}
			else
			{
				wave_matrix[i][j][0] = -1;// Мы еще нигде не были
			}
		}
	}
	wave_matrix[x_to][y_to][0] = 0;//стартуем от финиша
	step = 0; // Изначально мы сделали ноль шагов

	// Пока вершины добаляются и мы не дошли до старта

	while (added && wave_matrix[x][y][0] == -1)
	{
		added = false;// Пока что ничего не добавили
		step++;// Увеличиваем число шагов

		for (int i = 0; i < size; i++)// Пробегаем по всей карте
		{
			for (int j = 0; j < size; j++)
			{
				// Если (i, j) была добавлена на предыдущем шаге
				// Пробегаем по всем четырем сторонам
				if (wave_matrix[i][j][0] == step - 1)
				{
					int _i, _j;

					_i = i + 1; _j = j;
					// Если не вышли за пределы карты -  обрабатываем
					if (_i >= 0 && _j >= 0 && _i < size && _j < size)
					{
						// Если (_i, _j) уже добавлено или непроходимо, то не обрабатываем 
						if (wave_matrix[_i][_j][0] == -1 && wave_matrix[_i][_j][0] != -2)
						{
							wave_matrix[_i][_j][0] = step; // Добавляем
							wave_matrix[_i][_j][1] = i;  
							wave_matrix[_i][_j][2] = j; 
							added = true; // Что-то добавили
						}
					}
					_i = i - 1; _j = j;
					// Если не вышли за пределы карты -  обрабатываем
					if (_i >= 0 && _j >= 0 && _i < size && _j < size)
					{
						// Если (_i, _j) уже добавлено или непроходимо, то не обрабатываем 
						if (wave_matrix[_i][_j][0] == -1 && wave_matrix[_i][_j][0] != -2)
						{
							wave_matrix[_i][_j][0] = step; // Добавляем
							wave_matrix[_i][_j][1] = i;  
							wave_matrix[_i][_j][2] = j; 
							added = true; // Что-то добавили
						}
					}
					_i = i; _j = j + 1;
					// Если не вышли за пределы карты -  обрабатываем
					if (_i >= 0 && _j >= 0 && _i < size && _j < size)
					{
						// Если (_i, _j) уже добавлено или непроходимо, то не обрабатываем 
						if (wave_matrix[_i][_j][0] == -1 && wave_matrix[_i][_j][0] != -2)
						{
							wave_matrix[_i][_j][0] = step; // Добавляем
							wave_matrix[_i][_j][1] = i;  
							wave_matrix[_i][_j][2] = j;
							added = true; // Что-то добавили
						}
					}
					_i = i; _j = j - 1;
					// Если не вышли за пределы карты -  обрабатываем
					if (_i >= 0 && _j >= 0 && _i < size && _j < size)
					{
						// Если (_i, _j) уже добавлено или непроходимо, то не обрабатываем 
						if (wave_matrix[_i][_j][0] == -1 && wave_matrix[_i][_j][0] != -2)
						{
							wave_matrix[_i][_j][0] = step; // Добавляем
							wave_matrix[_i][_j][1] = i; 
							wave_matrix[_i][_j][2] = j;
							added = true; // Что-то добавили
						}
					}
				}
			}
		}
	}

	if (wave_matrix[x][y][0] == -1)
	{
		result = false; // то пути не существует
	}


	if (result)
	{
		int _i = x, _j = y;

		while (wave_matrix[_i][_j][0] != 0)
		{
			map[_i][_j] = 3;
			// тут записываем в  _i _J значение клеток пути для изначального массива и шагаем дальше к началу
			int li = wave_matrix[_i][_j][1];
			int lj = wave_matrix[_i][_j][2];
			_i = li; _j = lj;
		}
	}
	map[x][y] = 10;
	map[x_to][y_to] = 9;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			delete[] wave_matrix[i][j];
		}
		delete[] wave_matrix[i];
	}
	delete[] wave_matrix;
}
void read_txt(int** map, int size) { //cout << "path to txt file"<<endl;string enter;cin >> enter;string line;
	ifstream f;
	f.open("18.txt");
	if (f.is_open())
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				f >> map[i][j];
			}
		}
		f.close();
	}
	else {
		cout << "eror" << endl;
	}
}
void resize_and_write_BMP(int** map, int size, int b) {
	BMP newBmp(b * size, b * size);
	for (int i = 0; i < b * size; ++i) {
		for (int j = 0; j < b * size; ++j) {
			int x = trunc(i / b);
			int y = trunc(j / b);
			if (map[x][y] == 2) {
				newBmp.set_pixel(i, j, 255, 255, 255, 255);
			}
			if (map[x][y] == 3) {
				newBmp.set_pixel(i, j, 255, 0, 0, 255);
			}
			if (map[x][y] == 4) {
				newBmp.set_pixel(i, j, 128, 128, 128, 255);
			}
			if (map[x][y] == 10) {
				newBmp.set_pixel(i, j, 0, 0, 255, 255);
			}
			if (map[x][y] == 9) {
				newBmp.set_pixel(i, j, 0, 255, 255, 255);
			}
		}
	}
	newBmp.write("labyrinth_with_way2.bmp");
}
int main() {
    int size = 20;
	int b = 16;
    int** map=new int* [size];
	for (int i = 0; i < size; i++) {
		map[i] = new int[size];
	}
   
	read_txt(map, size);
	SearchWay(map,size);
	resize_and_write_BMP(map, size, b);	
	for (int i = 0; i < size; i++) {
		delete[] map[i];
	}
	delete[] map;
    return 0;
}
