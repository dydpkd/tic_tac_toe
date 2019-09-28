#include <iostream>
#include <random>

using namespace std;

template <typename T>

class dl_list
{
public:
	struct unit
	{
		unit(T obj)
		{
			data = obj;
			next = NULL;
			prev = NULL;
		}
		T data;
		unit* next, * prev;
	};
	dl_list()
	{
		head = NULL;
		tail = NULL;
	}
	~dl_list()
	{
		if (head)
		{
			unit* cur = head;
			while (cur != NULL)
			{
				unit* tmp = cur->next;
				delete cur;
				cur = tmp;
			}
		}
	}
	void add(T obj)
	{
		if (head == NULL)
		{
			head = tail = new unit(obj);
		}
		else
		{
			unit* tmp = new unit(obj);
			tail->next = tmp;
			tmp->prev = tail;
			tail = tmp;
		}
	}
	void remove(unit* obj)
	{
		if (obj->next != NULL)
		{
			obj->next->prev = obj->prev;
		}
		if (obj->prev != NULL)
		{
			obj->prev->next = obj->next;
		}
		delete obj;
	}
	unit* getHead()
	{
		return head;
	}
	unit* getTail()
	{
		return tail;
	}
private:
	unit* head, * tail;
};

struct game
{
	char cell = '_';
	bool occupied = false;
};

class tictac
{
private:
	char win;
	dl_list<game> tmp;
	game cell;
public:
	void start()
	{
		for (int i = 1; i < 10; i++)
		{
			tmp.add(cell);
		}
	}
	void step(int x, int y, char symb, char user)
	{
		dl_list<game>::unit* cur = tmp.getHead();
		if (y == 1)
		{
			for (int i = 0; i < x - 1; i++)
			{
				cur = cur->next;
			}
		}
		else if (y == 2)
		{
			for (int i = 0; i < x + 2; i++)
			{
				cur = cur->next;
			}
		}
		else if (y == 3)
		{
			for (int i = 0; i < x + 5; i++)
			{
				cur = cur->next;
			}
		}
		if (cur->data.occupied)
		{
			if (user == 'c')
			{
				computer();
			}
			else
			{
				cout << "\nCell is occupied\n";
				system("pause");
			}
		}
		else
		{
			cur->data.occupied = true;
			cur->data.cell = symb;
		}
	}
	void show()
	{
		dl_list<game>::unit* cur = tmp.getHead();
		int i = 1;
		int j = 1;
		cout << " ";
		for (int ii = 1; ii < 4; ii++)
		{
			cout << " " << ii;
		}
		cout << "\n" << j << "|";
		j++;
		for (cur; cur != NULL; cur = cur->next)
		{
			if (i != 3)
			{
				cout << cur->data.cell << " ";
			}
			else
			{
				if (j != 4)
				{
					cout << cur->data.cell << "\n" << j << "|";
				}
				else
				{
					cout << cur->data.cell << "\n";
				}
				i = 0;
				j++;
			}
			i++;
		}
	}
	bool result()
	{
		dl_list<game>::unit* x1_y1 = tmp.getHead();
		dl_list<game>::unit* x2_y1 = x1_y1->next;
		dl_list<game>::unit* x3_y1 = x2_y1->next;
		dl_list<game>::unit* x1_y2 = x3_y1->next;
		dl_list<game>::unit* x2_y2 = x1_y2->next;
		dl_list<game>::unit* x3_y2 = x2_y2->next;
		dl_list<game>::unit* x1_y3 = x3_y2->next;
		dl_list<game>::unit* x2_y3 = x1_y3->next;
		dl_list<game>::unit* x3_y3 = tmp.getTail();
		if (x1_y1->data.cell == x2_y1->data.cell && x1_y1->data.cell == x3_y1->data.cell && (x1_y1->data.cell == 'X' || x1_y1->data.cell == 'O'))
		{
			win = x1_y1->data.cell;
			return false;
		}
		else if (x1_y2->data.cell == x2_y2->data.cell && x1_y2->data.cell == x3_y2->data.cell && (x1_y2->data.cell == 'X' || x1_y2->data.cell == 'O'))
		{
			win = x1_y2->data.cell;
			return false;
		}
		else if (x1_y3->data.cell == x2_y3->data.cell && x1_y3->data.cell == x3_y3->data.cell && (x1_y3->data.cell == 'X' || x1_y3->data.cell == 'O'))
		{
			win = x1_y3->data.cell;
			return false;
		}
		else if (x1_y1->data.cell == x2_y2->data.cell && x1_y1->data.cell == x3_y3->data.cell && (x1_y1->data.cell == 'X' || x1_y1->data.cell == 'O'))
		{
			win = x1_y1->data.cell;
			return false;
		}
		else if (x3_y1->data.cell == x2_y2->data.cell && x3_y1->data.cell == x1_y3->data.cell && (x3_y1->data.cell == 'X' || x3_y1->data.cell == 'O'))
		{
			win = x3_y1->data.cell;
			return false;
		}
		else if (x1_y1->data.cell == x1_y2->data.cell && x1_y1->data.cell == x1_y3->data.cell && (x1_y1->data.cell == 'X' || x1_y1->data.cell == 'O'))
		{
			win = x1_y1->data.cell;
			return false;
		}
		else if (x2_y1->data.cell == x2_y2->data.cell && x2_y1->data.cell == x2_y3->data.cell && (x2_y1->data.cell == 'X' || x2_y1->data.cell == 'O'))
		{
			win = x2_y1->data.cell;
			return false;
		}
		else if (x3_y1->data.cell == x3_y2->data.cell && x3_y1->data.cell == x3_y3->data.cell && (x3_y1->data.cell == 'X' || x3_y1->data.cell == 'O'))
		{
			win = x3_y1->data.cell;
			return false;
		}
		return true;
	}
	bool check()
	{
		bool answer = true;
		for (dl_list<game>::unit* cur = tmp.getHead(); cur != NULL; cur = cur->next)
		{
			if (cur->data.occupied == false)
			{
				answer = false;
				break;
			}
		}
		if (answer == false)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	void computer()
	{
		random_device gen;// Объявляем переменную gen типа (Генератор случайных чисел взят из библиотеки <random>)
		uniform_int_distribution<int> uid(1, 3);// Применяется для указания диапазона целых чисел для рандома
		char symb = 'O';
		int x = uid(gen);
		int y = uid(gen);
		step(x, y, symb, 'c');
	}
	char getWinner()
	{
		return win;
	}
};

int main()
{
	tictac user;
	user.start();
	bool winner = true;
	int x, y;
	char symb = 'X';
	do
	{
		if (!user.check())
		{
			do
			{
				system("cls");
				cout << "Your step. Select cell\n\n";
				user.show();
				cout << "\nAxis x = "; cin >> x;
				cout << "Axis y = "; cin >> y;
				if ((x >= 1 && x <= 3) && (y >= 1 && y <= 3))
				{
					user.step(x, y, symb, 'u');
					break;
				}
				else
				{
					cout << "\nWrong coordinates. Try again.\n";
					system("pause");
				}
			} while (true);
		}
		if (!user.check())
		{
			user.computer();
		}
		else
		{
			if (!user.result())
			{
				winner = true;
			}
			else
			{
				winner = false;
			}
			system("cls");
			user.show();
			break;
		}
		if (!user.result())
		{
			winner = true;
			system("cls");
			user.show();
			break;
		}
	} while (true);
	if (winner)
	{
		cout << "\nWon \"" << user.getWinner() << "\"!";
	}
	else
	{
		cout << "\nThe winner is undetermined.";
	}
	cout << endl << endl;
	system("pause");
}