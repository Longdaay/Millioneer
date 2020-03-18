//Курсовая работа - "Кто хочет стать миллионером"


#include <iostream> //нужен для вывода строк "cout<<"
#include <fstream>
#include <string>
#include "windows.h" //библиотека audiere её требует
#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <conio.h> // для меню (считывание символов напрямую из консоли без использования буфера и echo-вывода (getch(void))
#include <iomanip>

#include "audiere.h" //сама библиотека
#pragma comment(lib, "audiere.lib")

using namespace std;
using namespace audiere; //определяем пространства имён для более короткой записи кода

bool fl_life = FALSE; // право на ошибку
bool fl_half = FALSE; // 50 на 50
bool fl_phone = FALSE; // помощь друга
bool fl_friends = FALSE; // помощь зала
int cur_prize = 0;
AudioDevicePtr device = OpenDevice(); //Для начала нужно открыть AudioDevice
OutputStreamPtr sound = OpenSound(device, "intro.mp3", false); //открываем наш звук

void print_dib(const vector<string>& prizes);

void SetColor(int text, int bg) //Функция смены цвета, взятая из Интернета
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

struct Question
{
	string question;
	vector<string> answer{ 4 };
	string key;
};

struct Phase
{
	vector<Question> question;
};

void set_question(ifstream& fout, Phase& easy)
{
	if (fout.is_open())
	{
		int count = 1;
		int i = 0;
		string temp;
		while (!fout.eof())
		{
			easy.question.resize(count);
			getline(fout, easy.question[i].question, ';');
			for (int j = 0; j <= 3; j++)
			{
				getline(fout, easy.question[i].answer[j], ';');
			}
			getline(fout,easy.question[i].key, '\n');
			i++;
			count++;
		}
	}
}



void print_one_question(const Phase& ques, int list)
{
	cout << " -------------------------------------------------------------------------------------------------------" << endl;
	cout << "\t" << ques.question[list].question << "" << endl;
	cout << " -------------------------------------------------------------------------------------------------------" << endl;
	cout << "\t -------------------------" << "               " << "------------------------ " << endl;
	if (ques.question[list].answer[0].length() <= 5)
		cout << "\t A" << ": " << ques.question[list].answer[0] << "     \t\t\t\t" << " B" << ": " << ques.question[list].answer[1] << endl;
	if (ques.question[list].answer[0].length() > 5 and ques.question[list].answer[0].length() <= 10)
		cout << "\t A" << ": " << ques.question[list].answer[0] << "        \t\t\t" << " B" << ": " << ques.question[list].answer[1] << endl;
	if (ques.question[list].answer[0].length() > 10 and ques.question[list].answer[0].length() != 14 and ques.question[list].answer[0].length() < 15)
		cout << "\t A" << ": " << ques.question[list].answer[0] << "      \t\t\t" << " B" << ": " << ques.question[list].answer[1] << endl;
	if (ques.question[list].answer[0].length() == 14)
		cout << "\t A" << ": " << ques.question[list].answer[0] << "      \t\t" << " B" << ": " << ques.question[list].answer[1] << endl;
	if (ques.question[list].answer[0].length() >= 15 and ques.question[list].answer[0].length() < 20)
		cout << "\t A" << ": " << ques.question[list].answer[0] << "        \t\t" << " B" << ": " << ques.question[list].answer[1] << endl;
	if (ques.question[list].answer[0].length() >= 20)
		cout << "\t A" << ": " << ques.question[list].answer[0] << "        \t" << " B" << ": " << ques.question[list].answer[1] << endl;
	cout << "\t -------------------------" << "               " << "------------------------ " << endl << endl;
	cout << "\t -------------------------" << "               " << "------------------------ " << endl;
	if (ques.question[list].answer[2].length() <= 5)
		cout << "\t C" << ": " << ques.question[list].answer[2] << "     \t\t\t\t" << " D" << ": " << ques.question[list].answer[3] << endl;
	if (ques.question[list].answer[2].length() > 5 and ques.question[list].answer[2].length() <= 10)
		cout << "\t C" << ": " << ques.question[list].answer[2] << "        \t\t\t" << " D" << ": " << ques.question[list].answer[3] << endl;
	if (ques.question[list].answer[2].length() > 10 and ques.question[list].answer[2].length() != 14 and ques.question[list].answer[2].length() < 15)
		cout << "\t C" << ": " << ques.question[list].answer[2] << "      \t\t\t" << " D" << ": " << ques.question[list].answer[3] << endl;
	if (ques.question[list].answer[2].length() == 14)
		cout << "\t C" << ": " << ques.question[list].answer[2] << "      \t\t" << " D" << ": " << ques.question[list].answer[3] << endl;
	if (ques.question[list].answer[2].length() >= 15 and ques.question[list].answer[2].length() < 20)
		cout << "\t C" << ": " << ques.question[list].answer[2] << "        \t\t" << " D" << ": " << ques.question[list].answer[3] << endl;
	if (ques.question[list].answer[2].length() >= 20)
		cout << "\t C" << ": " << ques.question[list].answer[2] << "        \t" << " D" << ": " << ques.question[list].answer[3] << endl;
	cout << "\t -------------------------" << "               " << "------------------------ " << endl << endl;

	//cout << "Ключ: " << ques.question[list].key << endl;
	cout << endl;
}

void half_answers(const Phase& ques, string key, int temp, int cur_ans, int list)
{
	SetColor(0, 0);
	if (ques.question[list].answer[cur_ans] == ques.question[list].answer[temp])
		SetColor(7, 0);
	if (ques.question[list].answer[cur_ans] == key)
		SetColor(7, 0);


}

string check_key(const Phase& ques, int list)
{
	for (int i = 0; i <= ques.question[list].answer.size() - 1; i++)
	{
		if (ques.question[list].key == ques.question[list].answer[i])
			return ques.question[list].answer[i];
	}
}

void print_half_answer(const Phase& ques, int list)
{
	
	bool fl = TRUE;
	string key = check_key(ques, list);
	int temp = 0;
	while (fl)
	{
		temp = rand() % ques.question[list].answer.size();
		if (ques.question[list].answer[temp] != key)
			fl = FALSE;
	}

	cout << " -------------------------------------------------------------------------------------------------------" << endl;
	cout << "\t" << ques.question[list].question << "" << endl;
	cout << " -------------------------------------------------------------------------------------------------------" << endl;
	cout << "\t -------------------------" << "               " << "------------------------ " << endl;
	
	if (ques.question[list].answer[0].length() <= 5)
	{half_answers(ques, key, temp, 0, list); cout << "\t A" << ": " << ques.question[list].answer[0]; SetColor(7, 0); cout << "     \t\t\t\t"; half_answers(ques, key, temp, 1, list); cout << " B" << ": " << ques.question[list].answer[1]; SetColor(7, 0); cout << endl;}
	if (ques.question[list].answer[0].length() > 5 and ques.question[list].answer[0].length() <= 10)
	{half_answers(ques, key, temp, 0, list); cout << "\t A" << ": " << ques.question[list].answer[0]; SetColor(7, 0); cout << "        \t\t\t"; half_answers(ques, key, temp, 1, list); cout << " B" << ": " << ques.question[list].answer[1]; SetColor(7, 0); cout << endl;}
	if (ques.question[list].answer[0].length() > 10 and ques.question[list].answer[0].length() != 14 and ques.question[list].answer[0].length() < 15)
	{half_answers(ques, key, temp, 0, list); cout << "\t A" << ": " << ques.question[list].answer[0]; SetColor(7, 0); cout << "      \t\t\t"; half_answers(ques, key, temp, 1, list); cout << " B" << ": " << ques.question[list].answer[1]; SetColor(7, 0); cout << endl;}
	if (ques.question[list].answer[0].length() == 14)
	{half_answers(ques, key, temp, 0, list); cout << "\t A" << ": " << ques.question[list].answer[0]; SetColor(7, 0); cout << "      \t\t"; half_answers(ques, key, temp, 1, list); cout << " B" << ": " << ques.question[list].answer[1]; SetColor(7, 0); cout << endl;}
	if (ques.question[list].answer[0].length() >= 15 and ques.question[list].answer[0].length() < 20)
	{half_answers(ques, key, temp, 0, list); cout << "\t A" << ": " << ques.question[list].answer[0]; SetColor(7, 0); cout << "        \t\t"; half_answers(ques, key, temp, 1, list); cout << " B" << ": " << ques.question[list].answer[1]; SetColor(7, 0); cout << endl;}
	if (ques.question[list].answer[0].length() >= 20)
	{half_answers(ques, key, temp, 0, list); cout << "\t A" << ": " << ques.question[list].answer[0]; SetColor(7, 0); cout << "        \t"; half_answers(ques, key, temp, 1, list); cout << " B" << ": " << ques.question[list].answer[1]; SetColor(7, 0); cout << endl;}
	cout << "\t -------------------------" << "               " << "------------------------ " << endl << endl;
	cout << "\t -------------------------" << "               " << "------------------------ " << endl;
	if (ques.question[list].answer[2].length() <= 5)
	{half_answers(ques, key, temp, 2, list); cout << "\t C" << ": " << ques.question[list].answer[2]; SetColor(7, 0); cout << "     \t\t\t\t"; half_answers(ques, key, temp, 3, list); cout << " D" << ": " << ques.question[list].answer[3]; SetColor(7, 0); cout << endl;}
	if (ques.question[list].answer[2].length() > 5 and ques.question[list].answer[2].length() <= 10)
	{half_answers(ques, key, temp, 2, list); cout << "\t C" << ": " << ques.question[list].answer[2]; SetColor(7, 0); cout << "        \t\t\t"; half_answers(ques, key, temp, 3, list); cout << " D" << ": " << ques.question[list].answer[3]; SetColor(7, 0); cout << endl;}
	if (ques.question[list].answer[2].length() > 10 and ques.question[list].answer[2].length() != 14 and ques.question[list].answer[2].length() < 15)
	{half_answers(ques, key, temp, 2, list); cout << "\t C" << ": " << ques.question[list].answer[2]; SetColor(7, 0); cout << "      \t\t\t"; half_answers(ques, key, temp, 3, list); cout << " D" << ": " << ques.question[list].answer[3]; SetColor(7, 0); cout << endl;}
	if (ques.question[list].answer[2].length() == 14)
	{half_answers(ques, key, temp, 2, list); cout << "\t C" << ": " << ques.question[list].answer[2]; SetColor(7, 0); cout << "      \t\t"; half_answers(ques, key, temp, 3, list); cout << " D" << ": " << ques.question[list].answer[3]; SetColor(7, 0); cout << endl;}
	if (ques.question[list].answer[2].length() >= 15 and ques.question[list].answer[2].length() < 20)
	{half_answers(ques, key, temp, 2, list); cout << "\t C" << ": " << ques.question[list].answer[2]; SetColor(7, 0); cout << "        \t\t"; half_answers(ques, key, temp, 3, list); cout << " D" << ": " << ques.question[list].answer[3]; SetColor(7, 0); cout << endl;}
	if (ques.question[list].answer[2].length() >= 20)
	{half_answers(ques, key, temp, 2, list); cout << "\t C" << ": " << ques.question[list].answer[2]; SetColor(7, 0); cout << "        \t"; half_answers(ques, key, temp, 3, list); cout << " D" << ": " << ques.question[list].answer[3]; SetColor(7, 0); cout << endl;}
	cout << "\t -------------------------" << "               " << "------------------------ " << endl;
}

void print_conf_color(const Phase& ques, int list, int current_conf, int current_value, bool flag)
{
	if (flag)
	{
		if (ques.question[list].answer[current_value] == ques.question[list].key)
			SetColor(10, 0);
	}
	else
	{
		if (current_value == current_conf)
			SetColor(6, 0);
	}
}

void print_conf_question(const Phase& ques, const vector <string>& prizes, int list, int current_conf, bool flag)
{

	system("cls");
	print_dib(prizes);
	cout << " -------------------------------------------------------------------------------------------------------" << endl;
	cout << "\t" << ques.question[list].question << "" << endl;
	cout << " -------------------------------------------------------------------------------------------------------" << endl;
	print_conf_color(ques, list, current_conf, 0, flag); cout << "\t -------------------------"; SetColor(7, 0); cout << "               "; print_conf_color(ques, list, current_conf, 1, flag); cout << "------------------------ "; SetColor(7, 0); cout << endl;

	if (ques.question[list].answer[0].length() <= 5)
	{print_conf_color(ques, list, current_conf, 0, flag); cout << "\t A" << ": " << ques.question[list].answer[0];  SetColor(7, 0); cout << "     \t\t\t\t"; print_conf_color(ques, list, current_conf, 1, flag); cout << " B" << ": " << ques.question[list].answer[1]; SetColor(7, 0); cout << endl;}
	if (ques.question[list].answer[0].length() > 5 and ques.question[list].answer[0].length() <= 10)
	{print_conf_color(ques, list, current_conf, 0, flag); cout << "\t A" << ": " << ques.question[list].answer[0]; SetColor(7, 0); cout << "        \t\t\t"; print_conf_color(ques, list, current_conf, 1, flag); cout << " B" << ": " << ques.question[list].answer[1]; SetColor(7, 0); cout << endl;}
	if (ques.question[list].answer[0].length() > 10 and ques.question[list].answer[0].length() != 14 and ques.question[list].answer[0].length() < 15)
	{print_conf_color(ques, list, current_conf, 0, flag); cout << "\t A" << ": " << ques.question[list].answer[0]; SetColor(7, 0); cout << "      \t\t\t"; print_conf_color(ques, list, current_conf, 1, flag); cout << " B" << ": " << ques.question[list].answer[1]; SetColor(7, 0); cout << endl;}
	if (ques.question[list].answer[0].length() == 14)
	{print_conf_color(ques, list, current_conf, 0, flag); cout << "\t A" << ": " << ques.question[list].answer[0]; SetColor(7, 0); cout << "      \t\t"; print_conf_color(ques, list, current_conf, 1, flag); cout << " B" << ": " << ques.question[list].answer[1]; SetColor(7, 0); cout << endl;}
	if (ques.question[list].answer[0].length() >= 15 and ques.question[list].answer[0].length() < 20)
	{print_conf_color(ques, list, current_conf, 0, flag); cout << "\t A" << ": " << ques.question[list].answer[0]; cout << "        \t\t"; print_conf_color(ques, list, current_conf, 1, flag); cout << " B" << ": " << ques.question[list].answer[1]; SetColor(7, 0); cout << endl;}
	if (ques.question[list].answer[0].length() >= 20)
	{print_conf_color(ques, list, current_conf, 0, flag); cout << "\t A" << ": " << ques.question[list].answer[0]; SetColor(7, 0); cout << "        \t"; print_conf_color(ques, list, current_conf, 1, flag); cout << " B" << ": " << ques.question[list].answer[1]; SetColor(7, 0); cout << endl;}
	print_conf_color(ques, list, current_conf, 0, flag); cout << "\t -------------------------"; SetColor(7, 0); cout << "               "; print_conf_color(ques, list, current_conf, 1, flag); cout << "------------------------ "; SetColor(7, 0); cout << endl << endl;
	print_conf_color(ques, list, current_conf, 2, flag); cout << "\t -------------------------"; SetColor(7, 0); cout << "               "; print_conf_color(ques, list, current_conf, 3, flag); cout << "------------------------ "; SetColor(7, 0); cout << endl;
	if (ques.question[list].answer[2].length() <= 5)
	{print_conf_color(ques, list, current_conf, 2, flag); cout << "\t C" << ": " << ques.question[list].answer[2]; SetColor(7, 0); cout << "     \t\t\t\t"; print_conf_color(ques, list, current_conf, 3, flag); cout << " D" << ": " << ques.question[list].answer[3]; SetColor(7, 0); cout << endl;}
	if (ques.question[list].answer[2].length() > 5 and ques.question[list].answer[2].length() <= 10)
	{print_conf_color(ques, list, current_conf, 2, flag); cout << "\t C" << ": " << ques.question[list].answer[2]; SetColor(7, 0); cout << "        \t\t\t"; print_conf_color(ques, list, current_conf, 3, flag); cout << " D" << ": " << ques.question[list].answer[3]; SetColor(7, 0); cout << endl;}
	if (ques.question[list].answer[2].length() > 10 and ques.question[list].answer[2].length() != 14 and ques.question[list].answer[2].length() < 15)
	{print_conf_color(ques, list, current_conf, 2, flag); cout << "\t C" << ": " << ques.question[list].answer[2]; SetColor(7, 0); cout << "      \t\t\t"; print_conf_color(ques, list, current_conf, 3, flag); cout << " D" << ": " << ques.question[list].answer[3]; SetColor(7, 0); cout << endl;}
	if (ques.question[list].answer[2].length() == 14)
	{print_conf_color(ques, list, current_conf, 2, flag); cout << "\t C" << ": " << ques.question[list].answer[2]; SetColor(7, 0); cout << "      \t\t"; print_conf_color(ques, list, current_conf, 3, flag); cout << " D" << ": " << ques.question[list].answer[3]; SetColor(7, 0); cout << endl;}
	if (ques.question[list].answer[2].length() >= 15 and ques.question[list].answer[2].length() < 20)
	{print_conf_color(ques, list, current_conf, 2, flag); cout << "\t C" << ": " << ques.question[list].answer[2]; SetColor(7, 0); cout << "        \t\t"; print_conf_color(ques, list, current_conf, 3, flag); cout << " D" << ": " << ques.question[list].answer[3]; SetColor(7, 0); cout << endl;}
	if (ques.question[list].answer[2].length() >= 20)
	{print_conf_color(ques, list, current_conf, 2, flag); cout << "\t C" << ": " << ques.question[list].answer[2]; SetColor(7, 0); cout << "        \t"; print_conf_color(ques, list, current_conf, 3, flag); cout << " D" << ": " << ques.question[list].answer[3]; SetColor(7, 0); cout << endl;}
	print_conf_color(ques, list, current_conf, 2, flag); cout << "\t -------------------------"; SetColor(7, 0); cout << "               "; print_conf_color(ques, list, current_conf, 3, flag); cout << "------------------------ "; SetColor(7, 0); cout << endl;

}

void print_questions(const Phase& easy)
{
	int i = 0;
	while (i <= easy.question.size() - 1)
	{
		print_one_question(easy, i);
		i++;
	}
}

void end_game()
{
	sound->stop();
	sound = OpenSound(device, "wrong.mp3", false); //открываем наш звук
	sound->play();
	cout << endl << endl << setw(30) << "\t\t Вы проиграли!" << endl;
	system("pause");
	exit(0);
}

bool conf(int confi)
{
	int value;
	value = _getch();
	switch (value)
	{
	case 65:
		if (confi == value)
			return 1;
		else
			return 0;
		break;
	case 66:
		if (confi == value)
			return 1;
		else
			return 0;
		break;
	case 67:
		if (confi == value)
			return 1;
		else
			return 0;
		break;
	case 68:
		if (confi == value)
			return 1;
		else
			return 0;
		break;
	default:
		return 0;
	}
}

void winner()
{
	sound->stop();
	sound = OpenSound(device, "winn.mp3", false); //открываем наш звук
	sound->play();
}

void choice(Phase ques, int list, const vector <string> &prizes) // 
{
	int k1;
	k1 = _getch(); // получаем символ без вывода знака
	switch (k1)
	{
	case 65: // A
		print_conf_question(ques,prizes,list, 0, 0);
		if (conf(k1))
		{
			print_conf_question(ques, prizes, list, 0, 1);
			if (ques.question[list].key == ques.question[list].answer[0])
			{
				winner();
				cout << "right" << endl;
			}
			else
				end_game();
		}
		else
			choice(ques, list, prizes);
		break;
	case 66: // B
		print_conf_question(ques, prizes, list, 1, 0);
		if (conf(k1))
		{
			print_conf_question(ques, prizes, list, 1, 1);
			if (ques.question[list].key == ques.question[list].answer[1])
			{
				winner();
				cout << "right" << endl;
			}
			else
				end_game();
		}
		else
			choice(ques, list, prizes);
		break;
	case 67: // C
		print_conf_question(ques, prizes, list, 2, 0);
		if (conf(k1))
		{
			print_conf_question(ques, prizes, list, 2, 1);
			if (ques.question[list].key == ques.question[list].answer[2])
			{
				winner();
				cout << "right" << endl;
			}
			else
				end_game();
		}
		else
			choice(ques, list, prizes);
		break;
	case 68: // D
		print_conf_question(ques, prizes, list, 3, 0);
		if (conf(k1))
		{
			print_conf_question(ques, prizes, list, 3, 1);
			if (ques.question[list].key == ques.question[list].answer[3])
			{
				winner();
				cout << "right" << endl;
			}
			else
				end_game();
		}
		else
			choice(ques, list, prizes);
		break;
	case 72: // H
		if (!fl_half)
		{
			fl_half = TRUE;
			print_dib(prizes);
			print_half_answer(ques, list);
			choice(ques, list, prizes);
		}
		else
			choice(ques, list, prizes);
		break;
	case 70: // F
		fl_friends = TRUE;
		print_dib(prizes);
		print_one_question(ques, list);
		choice(ques, list, prizes);
		break;
	case 80: // P
		fl_phone = TRUE;
		print_dib(prizes);
		print_one_question(ques, list);
		choice(ques, list, prizes);
		break;
	case 76: // L
		fl_life = TRUE;
		print_dib(prizes);
		print_one_question(ques, list);
		choice(ques, list, prizes);
		break;
	default:
		choice(ques, list, prizes);
	}
}

void print_prize(int list)
{
	if (cur_prize == list)
		SetColor(6, 0);
}

void print_half()
{
	if (fl_half)
		SetColor(0, 0);
	else
		SetColor(6, 0);
}

void print_phone()
{
	if (fl_phone)
		SetColor(0, 0);
	else
		SetColor(6, 0);
}

void print_friends()
{
	if (fl_friends)
		SetColor(0, 0);
	else
		SetColor(6, 0);
}

void print_life()
{
	if (fl_life)
		SetColor(0, 0);
	else
		SetColor(6, 0);
}

void print_dib(const vector<string>& prizes)
{
	system("cls");
	cout << endl << endl;
	cout << "......................:=@######@#@@@%@@@##################@%%%@#####%####@+-............-.-.-------------" << "   "; print_half();  cout << " ----------"; SetColor(7, 0); cout << "    "; print_phone(); cout << " ----------"; SetColor(7, 0); cout << "    "; print_friends(); cout << " ----------"; SetColor(7, 0); cout << "    "; print_life(); cout << " ----------"; SetColor(7, 0); cout << endl;
	cout << ".....................-**%@####@##@@@%=%@#####@%@#@@#@@@#@@@=++@##########@=--..........--...-------------" << "   "; print_half(); cout << "|   50:50  |"; SetColor(7, 0); cout << "   "; print_phone(); cout << "|   CALL   |"; SetColor(7, 0); cout << "   "; print_friends(); cout << "|   HELP   |"; SetColor(7, 0); cout << "   "; print_life(); cout << "|    x2    |"; SetColor(7, 0); cout << endl;
	cout << "....................:=+*@#######@@%%%=%@###@%++*+=%%@##%@%%%+=@##########@=+-.............---------------" << "   "; print_half(); cout << " ----------"; SetColor(7, 0); cout << "    "; print_phone(); cout << " ----------"; SetColor(7, 0); cout << "    "; print_friends(); cout << " ----------"; SetColor(7, 0); cout << "    "; print_life(); cout << " ----------"; SetColor(7, 0); cout << endl;
	cout << "....................-*%*@#####@%==+===%==%@%*+::::::*++++==%%%%@@@@@@@@#@@==:...........-----------------" << " " << endl;
	cout << "...................--*==%####@%=++++++=*:+=%%%==+*:---:::****++++@@##%=%%%%=:.........-----..------------" << " " << endl;
	cout << "...................--=@%@####@==+++***:***:*****:::---:::********=@####@@@=%+..........-----.------------" << "         " << setw(10) << left << "Призовой фонд:" << endl;
	cout << "...................--+@%@###@%==+++***:::::::::-:-:::::::********+=#######%%=:........-------------------" << "         " << "15 " << setw(13) << right; print_prize(14); cout << prizes[0]; SetColor(7, 0); cout << endl;
	cout << "....................:%@@####@%==+++***::::::::::::---::::::::***+++%#######@%+........-------------------" << "         " << "14 " << setw(13) << right; print_prize(13); cout << prizes[1]; SetColor(7, 0); cout << endl;
	cout << "....................*@@#####@@=+++****:::::---::::-:::::****+***++++%######@@%-.......----------.--------" << "         " << "13 " << setw(13) << right; print_prize(12); cout << prizes[2]; SetColor(7, 0); cout << endl;
	cout << "....................:#######@%=++*******:::::::::::**=%@#@@%=====++*+%########-.......-..----------------" << "         " << "12 " << setw(13) << right; print_prize(11); cout << prizes[3]; SetColor(7, 0); cout << endl;
	cout << ".....................@#######@%=%%@@@@@%=+*********=%#@=+*:**+=%%+**++@##@####=-......-------------------" << "         " << "11 " << setw(13) << right; print_prize(10); cout << prizes[4]; SetColor(7, 0); cout << endl;
	cout << "....................-=#######@@@%%=++=%@@#@%+++**+=@@%@%#####@=+*+**+=%#######=.......-------------------" << "         " << "10 " << setw(13) << right; print_prize(9); cout << prizes[5]; SetColor(7, 0); cout << endl;
	cout << "....................:@#######@@#@==+=@###@%@@%*::*==+**********::***+=@#######-.......-------------------" << "         " << "9  " << setw(13) << right; print_prize(8); cout << prizes[6]; SetColor(7, 0); cout << endl;
	cout << ".....................*######@%%%%%@@===*::::*+*::**::::*++=++*:::***+=@####@#=......-.-------------------" << "         " << "8  " << setw(13) << right; print_prize(7); cout << prizes[7]; SetColor(7, 0); cout << endl;
	cout << "....-.................:#@####%+++++++****::**+*:-:**:::::::::::::***+=%@###===-....----------------------" << "         " << "7  " << setw(13) << right; print_prize(6); cout << prizes[8]; SetColor(7, 0); cout << endl;
	cout << "....--..................-=####++****++++*:***++:::*****::::::::::***++=%#@%=--.....----------------------" << "         " << "6  " << setw(13) << right; print_prize(5); cout << prizes[9]; SetColor(7, 0); cout << endl;
	cout << "..-...--.-................:###=++***::::::*++=*:::***:*+=+**:::****++++%@#+:--....-----------------------" << "         " << "5  " << setw(13) << right; print_prize(4); cout << prizes[10]; SetColor(7, 0); cout << endl;
	cout << "-...------.-..-...........-%##%++***:*:**+++*+*::-:****+*+==+****++==+=+%#%:-......----------------------" << "         " << "4  " << setw(13) << right; print_prize(3); cout << prizes[11]; SetColor(7, 0); cout << endl;
	cout << ".---------.-.-..........--:-*@@==++****+===%==+*****+@@+****==+++===++==@#=.......-----------------------" << "         " << "3  " << setw(13) << right; print_prize(2); cout << prizes[12]; SetColor(7, 0); cout << endl;
	cout << "-----------..-..............--:@%%%====%++=%@@@%%@@@@+*******+++++++++=%##*.......-.---------------------" << "         " << "2  " << setw(13) << right; print_prize(1); cout << prizes[13]; SetColor(7, 0); cout << endl;
	cout << "--------.----...--..-.-.......-=@@@@%%=+====%%%@@@%=****++++++****++++%%=-........-----------------------" << "         " << "1  " << setw(13) << right; print_prize(0); cout << prizes[14]; SetColor(7, 0); cout << endl;
	cout << "------------.---------.........-%%%=+*=%%@##@@@%%%@@@%%@%=+*******+*+=%+%@-.........---------------------" << " " << endl;
	cout << "----------.....------...........:%%%=*:****+=%=++**+*************+*+%@==+###-.............-.-------------" << " " << endl;
	cout << "--.---.-.-.---------.............-=%%%=+*+**++++++++***:::::***++*=@@@%%+=####+.................---------" << " " << endl;
	cout << "--.---------------.................+@%=%%=****+*****::::::::*+=+=@@@@@%%*+#######%-......................" << " " << endl;
	cout << "....----------.-..................%#=%@@%@=+****:::::::::::*+%%@@@@@@%%=**############%+:-..............." << " " << endl;
	cout << "----------...-..................+###%#@@@@@=+******:::::***=@@##@@@@%%%**:####################@%+*-......" << " " << endl;
	cout << "------......................:%######+####@@@%=+******++++=@@@###@@@%%==**:###############################" << " " << endl;
	cout << "........................*@##########==@#####@@@%%====%%@@@@@@@@@%%====+**:@##############################" << " " << endl;
	cout << endl << endl << endl;
}

int main()
{
	ifstream out;
	string str;

	setlocale(0, "Russian");
	vector <string> prizes({ "3 000 000", "1 500 000", "800 000", "400 000", "200 000", "100 000", "50 000", "25 000", "15 000", "10 000", "5 000", "3 000", "2 000", "1 000", "500" });

	// +++++++++++++++++++++++++++++++++++++++++++++++
	// ВЫВОД ЗВУКА

	if (!device) {
		cout << "Ошибка открытия AudioDevice. Нажмите любую клавишу для выхода..";
		system("pause");
		return 0; //выходим из программы
	}
	if (!sound) {
		cout << "Ошибка открытия файла! Для выхода нажмите любую клавишу..";
		system("pause");
		return 0;
	}
	sound->play(); //проигрываем наш звук
	
	// ВОПРОСЫ + РАНДОМАЙЗ
	Phase easy;
	ifstream fout;
	int list;
	fout.open("questions.txt");
	set_question(fout, easy);
	//print_questions(easy);
	srand(time(0));

	cout << "Игра \"Кто хочет стать миллионером!\"" << endl;
	system("pause");
	
	for (int i = 0; i <= prizes.size() - 1; i++)
	{
		
		list = rand() % easy.question.size();
		print_dib(prizes);
		print_one_question(easy, list);
		sound = OpenSound(device, "next.mp3", false);
		sound->play();
		Sleep(3000);
		sound->stop();
		sound = OpenSound(device, "mind.mp3", false);
		sound->play();
		choice(easy, list, prizes);
		cur_prize++;
		system("pause");
		system("cls");
	}
	// +++++++++++++++++++++++++++++++++++++++++++++++

}