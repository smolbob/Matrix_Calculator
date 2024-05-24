#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>

void matrix_output(int** matrix, int matr_row, int matr_col) {
	for (int i = 0; i < matr_row; i++) {
		for (int j = 0; j < matr_col; j++) {
			std::cout << matrix[i][j] << '\t';
		}
		std::cout << "\n\n";
	}
}

int** create_matrix(int row, int col) {
	int i, j, el = 0;

	int** matrix = new int* [row] {};
	for (i = 0; i < row; i++) {
		matrix[i] = new int[col] {};
	}


	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			system("cls");
			matrix_output(matrix, row, col);

			std::cout << "Введите " << ++el << " элемент матрицы: ";
			std::cin >> matrix[i][j];
		}
	}

	return matrix;
}

void delete_matrix(int **matrix, int row) {
	for (int i = 0; i < row; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}

int matrix_determ(int **matrix, int matr_rang) {
	if (matr_rang == 3)
		return matrix[0][0] * matrix[1][1] * matrix[2][2] + matrix[0][1] * matrix[1][2] * matrix[2][0] + matrix[1][0] * matrix[2][1] * matrix[0][2] - matrix[0][2] * matrix[1][1] * matrix[2][0] - matrix[0][1] * matrix[1][0] * matrix[2][2] - matrix[2][1] * matrix[1][2] * matrix[0][0];
	else {
		int menu, copy_rows, copy_cols, rows, cols, i;
		int determ = 0;

		int** matrix_copy{ new int* [matr_rang -1] {} };	//создаем матрицу для алгебраического дополнения
		for (i = 0; i < matr_rang -1; i++) {
			matrix_copy[i] = new int[matr_rang -1] {};
		}

		system("cls");
		matrix_output(matrix, matr_rang, matr_rang);

		std::cout << "Как будем раскрывать матрицу?" << '\n' << "1.По строке." << '\n' << "2.По столбцу." << '\n';
		do {
			std::cin >> menu;
		} while (menu > 2 || menu < 1);

		switch (menu)
		{
		case 1:
		{

			std::cout << "Введите номер строки: ";
			do {
				std::cin >> menu;
			} while (menu > matr_rang || menu < 1);

			menu--;

			for (int j = 0; j < matr_rang; j++) {

				copy_rows = 0;
				for (rows = 0; copy_rows < matr_rang - 1; rows++) {	//заполняем матрицу алгебраического дополнения
					copy_cols = 0;
					if (rows != menu) {
						for (cols = 0; copy_cols < matr_rang - 1; cols++) {
							if (cols != j) {
								matrix_copy[copy_rows][copy_cols] = matrix[rows][cols];
								copy_cols++;
							}
						}
						copy_rows++;
					}
				}

				determ += pow(-1, (j + menu)) * matrix[menu][j] * matrix_determ(matrix_copy, matr_rang - 1);
			}

			for (i = 0; i < matr_rang - 1; i++) {
				delete[] matrix_copy[i];
			}
			delete[] matrix_copy;

			return determ;
		}
			break;
		case 2:
		{
			std::cout << "Введите номер столбца: ";
			do {
				std::cin >> menu;
			} while (menu > matr_rang || menu < 1);

			menu--;

			for (int j = 0; j < matr_rang; j++) {

				copy_rows = 0;
				for (rows = 0; copy_rows < matr_rang - 1; rows++) {	//заполняем минор
					copy_cols = 0;
					if (rows != j) {
						for (cols = 0; copy_cols < matr_rang - 1; cols++) {
							if (cols != menu) {
								matrix_copy[copy_rows][copy_cols] = matrix[rows][cols];
								copy_cols++;
							}
						}
						copy_rows++;
					}
				}

				determ += pow(-1, (j + menu + 2)) * matrix[j][menu] * matrix_determ(matrix_copy, matr_rang - 1);
			}

			for (i = 0; i < matr_rang - 1; i++) {
				delete[] matrix_copy[i];
			}
			delete[] matrix_copy;

			return determ;
		}
			break;
		default:
			break;
		}
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

    int menu, i = 0, j = 0, el = 0, rang;

	do {
		system("cls");
		std::cout << "1.Умножение матриц.\n";
		std::cout << "2.Найти определитель матрицы.\n";
		std::cout << "3.Выход.\n";

		std::cin >> menu;
		system("cls");
		switch (menu)
		{
		case 1:
		{
			int m1, n1, m2, n2;
			std::cout << "Введите размеры матрицы A:\nm:\n";
			std::cin >> m1;
			std::cout << "n:\n";
			std::cin >> n1;

			std::cout << "Введите размеры матрицы B:\nm:\n";
			std::cin >> m2;
			std::cout << "n:\n";
			std::cin >> n2;

			if (n1 == m2) {		//если матрицы можно перемножить, то создаем новую матрицу AB
				int** matrix_A{};
				matrix_A = create_matrix(m1, n1);
				int** matrix_B{};
				matrix_B = create_matrix(m2, n2);


				int** matrix_AB = new int* [m1] {};
				for (i = 0; i < m1; i++) {
					matrix_AB[i] = new int[n2] {};
				}

				for (i = 0; i < m1; i++) {
					for (j = 0; j < n1; j++) {
						matrix_AB[i][j] = 0;
					}
				}

				for (i = 0; i < m1; i++) {
					for (j = 0; j < n2; j++) {
						for (int k = 0; k < n1; k++) {
							matrix_AB[i][j] += matrix_A[i][k] * matrix_B[k][j];
						}
					}
				}

				matrix_output(matrix_AB, m1, n2);
				delete_matrix(matrix_AB, m1);
				delete_matrix(matrix_A, m1);
				delete_matrix(matrix_B, m2);
			}
			else std::cout << "Неверные размеры матриц.\n";

			std::cout << "Нажмите любую клавишу для выхода.\n";
			_getch();
		}
			break;
		case 2: {
			std::cout << "Введите порядок матрицы: ";
			do {
				std::cin >> rang;
			} while (rang < 2 || rang > 5);

			int** matrix{ new int* [rang] {} };
			for (i = 0; i < rang; i++) {
				matrix[i] = new int[rang] {};
			}

			for (i = 0; i < rang; i++) {
				for (j = 0; j < rang; j++) {
					matrix[i][j] = 0;
				}
			}

			for (i = 0; i < rang; i++) {
				for (j = 0; j < rang; j++) {
					system("cls");
					matrix_output(matrix, rang, rang);

					std::cout << "Введите " << ++el << " элемент матрицы: ";
					std::cin >> matrix[i][j];
				}
			}

			system("cls");
			matrix_output(matrix, rang, rang);
			if (rang == 2)
				std::cout << "Определитель матрицы: " << matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0] << '\n';
			else if(rang == 3)
				std::cout << "Определитель матрицы: " << matrix_determ(matrix, rang) << '\n';
			else {
				std::cout << "Определитель матрицы: " << matrix_determ(matrix, rang) << '\n';
			}

			for (i = 0; i < rang; i++) {
				delete[] matrix[i];
			}
			delete[] matrix;

			std::cout << "Нажмите любую клавишу для выхода.\n";
			_getch();
		}
			break;
		default:
			break;
		}
	} while (menu != 3);

	return 0;
}
