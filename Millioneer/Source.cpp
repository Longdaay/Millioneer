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
bool fl_stop = TRUE; // первый флаг для отмены ввода 50 на 50
bool fl_s_half = FALSE;// второй флаг для 50 на 50
bool fl_endgame = FALSE;
bool fl_stop_life = TRUE;
int cur_prize = 0;
int ex_prize = 0;
int temp = 5;// перменная в которую запишем дополнительный номер ответа после 50 на 50, также это номер ошибочного ответа ( право на ошибку)
int temp_life = 5;
int m_count = 0;
int sub_m_count = 0;
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
			getline(fout, easy.question[i].key, '\n');
			i++;
			count++;
		}
	}
}

void menu(const Phase& ques, const vector <string>& prizes);
void menu_prize(const Phase& ques, const vector <string>& prizes);
void play(const Phase& ques, const vector <string>& prizes);
void millioneer(const Phase& ques, const vector <string>& prizes);


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

bool half_answers(const Phase& ques, string key, int temp, int cur_ans, int list)
{
	if (!fl_life or fl_stop)
	{
		if (temp != 5)
		{
			if (fl_half and fl_stop)
			{
				SetColor(0, 0);
				if (ques.question[list].answer[cur_ans] == ques.question[list].answer[temp])
					SetColor(7, 0);
				if (ques.question[list].answer[cur_ans] == key)
					SetColor(7, 0);
				return 1;
			}
		}
	}
	return 0;
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
	if (temp == 5)
	{
		temp = 0;
		while (fl)
		{
			temp = rand() % ques.question[list].answer.size();
			if (ques.question[list].answer[temp] != key)
				fl = FALSE;
		}
	}

	sound->stop();
	sound = OpenSound(device, "half.mp3", false); //открываем наш звук
	sound->play();


	cout << " -------------------------------------------------------------------------------------------------------" << endl;
	cout << "\t" << ques.question[list].question << "" << endl;
	cout << " -------------------------------------------------------------------------------------------------------" << endl;
	cout << "\t -------------------------" << "               " << "------------------------ " << endl;

	if (ques.question[list].answer[0].length() <= 5)
	{
		half_answers(ques, key, temp, 0, list); cout << "\t A" << ": " << ques.question[list].answer[0]; SetColor(7, 0); cout << "     \t\t\t\t"; half_answers(ques, key, temp, 1, list); cout << " B" << ": " << ques.question[list].answer[1]; SetColor(7, 0); cout << endl;
	}
	if (ques.question[list].answer[0].length() > 5 and ques.question[list].answer[0].length() <= 10)
	{
		half_answers(ques, key, temp, 0, list); cout << "\t A" << ": " << ques.question[list].answer[0]; SetColor(7, 0); cout << "        \t\t\t"; half_answers(ques, key, temp, 1, list); cout << " B" << ": " << ques.question[list].answer[1]; SetColor(7, 0); cout << endl;
	}
	if (ques.question[list].answer[0].length() > 10 and ques.question[list].answer[0].length() != 14 and ques.question[list].answer[0].length() < 15)
	{
		half_answers(ques, key, temp, 0, list); cout << "\t A" << ": " << ques.question[list].answer[0]; SetColor(7, 0); cout << "      \t\t\t"; half_answers(ques, key, temp, 1, list); cout << " B" << ": " << ques.question[list].answer[1]; SetColor(7, 0); cout << endl;
	}
	if (ques.question[list].answer[0].length() == 14)
	{
		half_answers(ques, key, temp, 0, list); cout << "\t A" << ": " << ques.question[list].answer[0]; SetColor(7, 0); cout << "      \t\t"; half_answers(ques, key, temp, 1, list); cout << " B" << ": " << ques.question[list].answer[1]; SetColor(7, 0); cout << endl;
	}
	if (ques.question[list].answer[0].length() >= 15 and ques.question[list].answer[0].length() < 20)
	{
		half_answers(ques, key, temp, 0, list); cout << "\t A" << ": " << ques.question[list].answer[0]; SetColor(7, 0); cout << "        \t\t"; half_answers(ques, key, temp, 1, list); cout << " B" << ": " << ques.question[list].answer[1]; SetColor(7, 0); cout << endl;
	}
	if (ques.question[list].answer[0].length() >= 20)
	{
		half_answers(ques, key, temp, 0, list); cout << "\t A" << ": " << ques.question[list].answer[0]; SetColor(7, 0); cout << "        \t"; half_answers(ques, key, temp, 1, list); cout << " B" << ": " << ques.question[list].answer[1]; SetColor(7, 0); cout << endl;
	}
	cout << "\t -------------------------" << "               " << "------------------------ " << endl << endl;
	cout << "\t -------------------------" << "               " << "------------------------ " << endl;
	if (ques.question[list].answer[2].length() <= 5)
	{
		half_answers(ques, key, temp, 2, list); cout << "\t C" << ": " << ques.question[list].answer[2]; SetColor(7, 0); cout << "     \t\t\t\t"; half_answers(ques, key, temp, 3, list); cout << " D" << ": " << ques.question[list].answer[3]; SetColor(7, 0); cout << endl;
	}
	if (ques.question[list].answer[2].length() > 5 and ques.question[list].answer[2].length() <= 10)
	{
		half_answers(ques, key, temp, 2, list); cout << "\t C" << ": " << ques.question[list].answer[2]; SetColor(7, 0); cout << "        \t\t\t"; half_answers(ques, key, temp, 3, list); cout << " D" << ": " << ques.question[list].answer[3]; SetColor(7, 0); cout << endl;
	}
	if (ques.question[list].answer[2].length() > 10 and ques.question[list].answer[2].length() != 14 and ques.question[list].answer[2].length() < 15)
	{
		half_answers(ques, key, temp, 2, list); cout << "\t C" << ": " << ques.question[list].answer[2]; SetColor(7, 0); cout << "      \t\t\t"; half_answers(ques, key, temp, 3, list); cout << " D" << ": " << ques.question[list].answer[3]; SetColor(7, 0); cout << endl;
	}
	if (ques.question[list].answer[2].length() == 14)
	{
		half_answers(ques, key, temp, 2, list); cout << "\t C" << ": " << ques.question[list].answer[2]; SetColor(7, 0); cout << "      \t\t"; half_answers(ques, key, temp, 3, list); cout << " D" << ": " << ques.question[list].answer[3]; SetColor(7, 0); cout << endl;
	}
	if (ques.question[list].answer[2].length() >= 15 and ques.question[list].answer[2].length() < 20)
	{
		half_answers(ques, key, temp, 2, list); cout << "\t C" << ": " << ques.question[list].answer[2]; SetColor(7, 0); cout << "        \t\t"; half_answers(ques, key, temp, 3, list); cout << " D" << ": " << ques.question[list].answer[3]; SetColor(7, 0); cout << endl;
	}
	if (ques.question[list].answer[2].length() >= 20)
	{
		half_answers(ques, key, temp, 2, list); cout << "\t C" << ": " << ques.question[list].answer[2]; SetColor(7, 0); cout << "        \t"; half_answers(ques, key, temp, 3, list); cout << " D" << ": " << ques.question[list].answer[3]; SetColor(7, 0); cout << endl;
	}
	cout << "\t -------------------------" << "               " << "------------------------ " << endl;
	Sleep(1000);
	sound->stop();
	sound = OpenSound(device, "mind.mp3", false); //открываем наш звук
	sound->play();
	sound->setRepeat(true);
}

void print_life_color(const Phase& ques, int list, int current_conf)
{
	if (!fl_stop_life)
	{
		if (current_conf == temp_life)
			SetColor(4, 0);
	}
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

	string key = check_key(ques, list);

	cout << " -------------------------------------------------------------------------------------------------------" << endl;
	cout << "\t" << ques.question[list].question << "" << endl;
	cout << " -------------------------------------------------------------------------------------------------------" << endl;
	print_conf_color(ques, list, current_conf, 0, flag); print_life_color(ques, list, 0); cout << "\t -------------------------"; SetColor(7, 0); cout << "               "; print_conf_color(ques, list, current_conf, 1, flag); print_life_color(ques, list, 1); cout << "------------------------ "; SetColor(7, 0); cout << endl;

	if (ques.question[list].answer[0].length() <= 5)
	{
		print_conf_color(ques, list, current_conf, 0, flag); half_answers(ques, key, temp, 0, list); print_life_color(ques, list, 0); cout << "\t A" << ": " << ques.question[list].answer[0];  SetColor(7, 0); cout << "     \t\t\t\t"; print_conf_color(ques, list, current_conf, 1, flag); half_answers(ques, key, temp, 1, list); cout << " B" << ": " << ques.question[list].answer[1]; SetColor(7, 0); cout << endl;
	}
	if (ques.question[list].answer[0].length() > 5 and ques.question[list].answer[0].length() <= 10)
	{
		print_conf_color(ques, list, current_conf, 0, flag); half_answers(ques, key, temp, 0, list); print_life_color(ques, list, 0); cout << "\t A" << ": " << ques.question[list].answer[0]; SetColor(7, 0); cout << "        \t\t\t"; print_conf_color(ques, list, current_conf, 1, flag); half_answers(ques, key, temp, 1, list); print_life_color(ques, list, 1); cout << " B" << ": " << ques.question[list].answer[1]; SetColor(7, 0); cout << endl;
	}
	if (ques.question[list].answer[0].length() > 10 and ques.question[list].answer[0].length() != 14 and ques.question[list].answer[0].length() < 15)
	{
		print_conf_color(ques, list, current_conf, 0, flag); half_answers(ques, key, temp, 0, list); print_life_color(ques, list, 0); cout << "\t A" << ": " << ques.question[list].answer[0]; SetColor(7, 0); cout << "      \t\t\t"; print_conf_color(ques, list, current_conf, 1, flag); half_answers(ques, key, temp, 1, list); print_life_color(ques, list, 1); cout << " B" << ": " << ques.question[list].answer[1]; SetColor(7, 0); cout << endl;
	}
	if (ques.question[list].answer[0].length() == 14)
	{
		print_conf_color(ques, list, current_conf, 0, flag); half_answers(ques, key, temp, 0, list); print_life_color(ques, list, 0); cout << "\t A" << ": " << ques.question[list].answer[0]; SetColor(7, 0); cout << "      \t\t"; print_conf_color(ques, list, current_conf, 1, flag); half_answers(ques, key, temp, 1, list); print_life_color(ques, list, 1); cout << " B" << ": " << ques.question[list].answer[1]; SetColor(7, 0); cout << endl;
	}
	if (ques.question[list].answer[0].length() >= 15 and ques.question[list].answer[0].length() < 20)
	{
		print_conf_color(ques, list, current_conf, 0, flag); half_answers(ques, key, temp, 0, list); print_life_color(ques, list, 0); cout << "\t A" << ": " << ques.question[list].answer[0]; SetColor(7, 0); cout << "        \t\t"; print_conf_color(ques, list, current_conf, 1, flag); half_answers(ques, key, temp, 1, list); print_life_color(ques, list, 1); cout << " B" << ": " << ques.question[list].answer[1]; SetColor(7, 0); cout << endl;
	}
	if (ques.question[list].answer[0].length() >= 20)
	{
		print_conf_color(ques, list, current_conf, 0, flag); half_answers(ques, key, temp, 0, list); print_life_color(ques, list, 0); cout << "\t A" << ": " << ques.question[list].answer[0]; SetColor(7, 0); cout << "        \t"; print_conf_color(ques, list, current_conf, 1, flag); half_answers(ques, key, temp, 1, list); print_life_color(ques, list, 1); cout << " B" << ": " << ques.question[list].answer[1]; SetColor(7, 0); cout << endl;
	}

	print_conf_color(ques, list, current_conf, 0, flag); print_life_color(ques, list, 0); cout << "\t -------------------------"; SetColor(7, 0); cout << "               "; print_conf_color(ques, list, current_conf, 1, flag); print_life_color(ques, list, 1); cout << "------------------------ "; SetColor(7, 0); cout << endl << endl;
	print_conf_color(ques, list, current_conf, 2, flag); print_life_color(ques, list, 2); cout << "\t -------------------------"; SetColor(7, 0); cout << "               "; print_conf_color(ques, list, current_conf, 3, flag); print_life_color(ques, list, 3); cout << "------------------------ "; SetColor(7, 0); cout << endl;

	if (ques.question[list].answer[2].length() <= 5)
	{
		print_conf_color(ques, list, current_conf, 2, flag); half_answers(ques, key, temp, 2, list); print_life_color(ques, list, 2); cout << "\t C" << ": " << ques.question[list].answer[2]; SetColor(7, 0); cout << "     \t\t\t\t"; print_conf_color(ques, list, current_conf, 3, flag); half_answers(ques, key, temp, 3, list); print_life_color(ques, list, 3); cout << " D" << ": " << ques.question[list].answer[3]; SetColor(7, 0); cout << endl;
	}
	if (ques.question[list].answer[2].length() > 5 and ques.question[list].answer[2].length() <= 10)
	{
		print_conf_color(ques, list, current_conf, 2, flag); half_answers(ques, key, temp, 2, list); print_life_color(ques, list, 2); cout << "\t C" << ": " << ques.question[list].answer[2]; SetColor(7, 0); cout << "        \t\t\t"; print_conf_color(ques, list, current_conf, 3, flag); half_answers(ques, key, temp, 3, list); print_life_color(ques, list, 3); cout << " D" << ": " << ques.question[list].answer[3]; SetColor(7, 0); cout << endl;
	}
	if (ques.question[list].answer[2].length() > 10 and ques.question[list].answer[2].length() != 14 and ques.question[list].answer[2].length() < 15)
	{
		print_conf_color(ques, list, current_conf, 2, flag); half_answers(ques, key, temp, 2, list); print_life_color(ques, list, 2); cout << "\t C" << ": " << ques.question[list].answer[2]; SetColor(7, 0); cout << "      \t\t\t"; print_conf_color(ques, list, current_conf, 3, flag); half_answers(ques, key, temp, 3, list); print_life_color(ques, list, 3); cout << " D" << ": " << ques.question[list].answer[3]; SetColor(7, 0); cout << endl;
	}
	if (ques.question[list].answer[2].length() == 14)
	{
		print_conf_color(ques, list, current_conf, 2, flag); half_answers(ques, key, temp, 2, list); print_life_color(ques, list, 2); cout << "\t C" << ": " << ques.question[list].answer[2]; SetColor(7, 0); cout << "      \t\t"; print_conf_color(ques, list, current_conf, 3, flag); half_answers(ques, key, temp, 3, list); print_life_color(ques, list, 3); cout << " D" << ": " << ques.question[list].answer[3]; SetColor(7, 0); cout << endl;
	}
	if (ques.question[list].answer[2].length() >= 15 and ques.question[list].answer[2].length() < 20)
	{
		print_conf_color(ques, list, current_conf, 2, flag); half_answers(ques, key, temp, 2, list); print_life_color(ques, list, 2); cout << "\t C" << ": " << ques.question[list].answer[2]; SetColor(7, 0); cout << "        \t\t"; print_conf_color(ques, list, current_conf, 3, flag); half_answers(ques, key, temp, 3, list); print_life_color(ques, list, 3); cout << " D" << ": " << ques.question[list].answer[3]; SetColor(7, 0); cout << endl;
	}
	if (ques.question[list].answer[2].length() >= 20)
	{
		print_conf_color(ques, list, current_conf, 2, flag); half_answers(ques, key, temp, 2, list); print_life_color(ques, list, 2); cout << "\t C" << ": " << ques.question[list].answer[2]; SetColor(7, 0); cout << "        \t"; print_conf_color(ques, list, current_conf, 3, flag); half_answers(ques, key, temp, 3, list); print_life_color(ques, list, 3); cout << " D" << ": " << ques.question[list].answer[3]; SetColor(7, 0); cout << endl;
	}

	print_conf_color(ques, list, current_conf, 2, flag); print_life_color(ques, list, 2); cout << "\t -------------------------"; SetColor(7, 0); cout << "               "; print_conf_color(ques, list, current_conf, 3, flag); print_life_color(ques, list, 3); cout << "------------------------ "; SetColor(7, 0); cout << endl;

	if (!fl_life)
	{
		if (fl_half and fl_s_half) // если после 50 на 50 мы и выбрали ответ и подтвердили его, больше не выводим по 2 ответа
		{
			fl_stop = FALSE;
		}
		if (fl_half)
			fl_s_half = TRUE; // переводим второй флаг в 1, чтобы перестать выводить только 2 ответа
	}
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

void end_game(const Phase& ques, const vector <string>& prizes)
{
	sound->stop();
	sound = OpenSound(device, "wrong.mp3", false); //открываем наш звук
	sound->play();
	cout << endl;
	cout << setw(75) << right << "---------------------------------------------" << endl;
	cout << setw(60) << right << "Вы проиграли!" << endl;
	cout << setw(75) << right << "---------------------------------------------" << endl;
	if (cur_prize >= ex_prize)
	{
		cout << "Ваш выигрыш : "; SetColor(3, 0); cout << prizes[ex_prize]; SetColor(7, 0); cout << endl;
	}
	else
	{
		cout << "Ваш выигрыш: "; SetColor(3, 0); cout << "0"; SetColor(7, 0); cout << endl;
	}
	system("pause");
	millioneer(ques, prizes);
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
	cout << endl;
	cout << setw(75) << right << "---------------------------------------------" << endl;
	cout << setw(60) << right << "Правильный ответ!" << endl;
	cout << setw(75) << right << "---------------------------------------------" << endl;
}

void print_logo()
{
	cout << endl;
	cout << "=##############################################################################################################################################################=" << endl;
	cout << "=##############################################################################################################################################################=" << endl;
	cout << "=##############################################################################################################################################################=" << endl;
	cout << "=##############################################################################################################################################################=" << endl;
	cout << "=############      %###@      @################################################################################################################################=" << endl;
	cout << "=############       ###%      @################################################################################################################################=" << endl;
	cout << "=############       %#@       @##    @##@    @###           %###%           ##@   %###%    ####@%     %@###@    @###    @###@%      %####%   @%    @###########=" << endl;
	cout << "=############    @   #%  %%   @##    @#%     @###           %###            ##@   %#@      ##@     %     @#@    @###    @##%    @@    %##%           ##########=" << endl;
	cout << "=############    #   %   @%   @##    @       @###    @##%   %###    %##@    ##@   %%       ##    %###%   %#@            @#%    %%%%    @#%   %###    @#########=" << endl;
	cout << "=############    #@     %#%   @##       %    @###    @##%   %###    %##@    ##@       @    ##    %###%   %#@            @#%    %%%%%%%%@#%   %###    %#########=" << endl;
	cout << "=############    ##     @#%   @##      @#    @#      @##%   %#%     %##@    ##@     %#@    ##@     %     @#@    @###    @##    %@@%   %##%           @#########=" << endl;
	cout << "=############    ##@   %##%   @##    %###    @#     %###%   %#     %###@    ##@    @##@    ####@      %@###@    @###    @###@%      %@###%   %%    %###########=" << endl;
	cout << "=########################################################################################################################################%   %#################=" << endl;
	cout << "=########################################################################################################################################%   %#################=" << endl;
	cout << "=##############################################################################################################################################################=" << endl;
	cout << "=##############################################################################################################################################################=" << endl;
	cout << "=##############################################################################################################################################################=" << endl;
	cout << "=##############################################################################################################################################################=" << endl;
	cout << endl << endl;
}

void print_voting(const Phase& ques, int list)
{
	sound->stop();
	sound = OpenSound(device, "voting.mp3", false); //открываем наш звук
	sound->play();
	int maxim_val = 0;
	int temp1 = 0;
	int temp2 = 0;
	int number_of_answer;
	int A, B, C, D;
	A = rand() % 1000;
	B = (1000 - A) - (rand() % (1000 - A));
	C = (1000 - A - B) - (rand() % (1000 - A - B));
	D = 1000 - A - B - C;

	cout << "A (" << A << "):  \t";
	SetColor(0, 8);
	for (int i = 0; i <= A / 10; i++)
	{
		cout << " ";
	}
	SetColor(7, 0);
	cout << endl;
	Sleep(3000);
	cout << "B (" << B << "):  \t";
	SetColor(0, 9);
	for (int i = 0; i <= B / 10; i++)
	{
		cout << " ";
	}
	SetColor(7, 0);
	cout << endl;
	Sleep(3000);
	cout << "C (" << C << "):  \t";
	SetColor(0, 10);
	for (int i = 0; i <= C / 10; i++)
	{
		cout << " ";
	}
	SetColor(7, 0);
	cout << endl;
	Sleep(3000);
	cout << "D (" << D << "):  \t";
	SetColor(0, 11);
	for (int i = 0; i <= D / 10; i++)
	{
		cout << " ";
	}
	SetColor(7, 0);
	cout << endl << endl;
	temp1 = max(A, B);
	temp2 = max(C, D);
	maxim_val = max(temp1, temp2);
	if (maxim_val == A)
		number_of_answer = 0;
	if (maxim_val == B)
		number_of_answer = 1;
	if (maxim_val == C)
		number_of_answer = 2;
	if (maxim_val == D)
		number_of_answer = 3;
	cout << setw(80) << right << "---------------------------------------------" << endl;
	cout << setw(43) << right << "Ответ: " << ques.question[list].answer[number_of_answer] << endl;
	cout << setw(80) << right << "---------------------------------------------" << endl;

	sound->stop();
	sound = OpenSound(device, "mind.mp3", false); //открываем наш звук
	sound->play();
	sound->setRepeat(true);
}

void print_call(const Phase& ques, int list, const vector <string>& prizes)
{
	sound->stop();
	sound = OpenSound(device, "file.wav", false); //открываем наш звук
	sound->play();

	cout << setw(100) << right << "                                                  " << endl;
	cout << setw(100) << right << "                                                  " << endl;
	cout << setw(100) << right << "                --:************:--                " << endl;
	cout << setw(100) << right << "           - ************************-            " << endl;
	cout << setw(100) << right << "         :******************************:         " << endl;
	cout << setw(100) << right << "      -************************************-      " << endl;
	cout << setw(100) << right << "    -****************************************-    " << endl;
	cout << setw(100) << right << "   -********+%#####%+********+%#####%+********-   " << endl;
	cout << setw(100) << right << "  :********=#@+***+@#=******=#@+***+@#=********:  " << endl;
	cout << setw(100) << right << " -**********************************************- " << endl;
	cout << setw(100) << right << " *****+@@%%====++++++*********++++++====%%@@***** " << endl;
	cout << setw(100) << right << ":*****+#@::=#====%#@%%@@@#@@@%@#@%==+@@*:*#@*****:" << endl;
	cout << setw(100) << right << ":******+#@.*#*    @%    +#-   -#+    %@ :#@******:" << endl;
	cout << setw(100) << right << "********+@#=#*    @%	   +#-   -#+    %@=#%********" << endl;
	cout << setw(100) << right << "**********=##=.   @%    +#-   -#+   -@#@+*********" << endl;
	cout << setw(100) << right << ":***********+%##@+#%    +#-   -#==@#@=***********:" << endl;
	cout << setw(100) << right << " ***************+=@############@%=*************** " << endl;
	cout << setw(100) << right << " ************************************************ " << endl;
	cout << setw(100) << right << "  **********************************************  " << endl;
	cout << setw(100) << right << "   ********************************************   " << endl;
	cout << setw(100) << right << "    ******************************************    " << endl;
	cout << setw(100) << right << "      :************************************:      " << endl;
	cout << setw(100) << right << "          -:**************************:-          " << endl;
	cout << setw(100) << right << "               --:**************:--               " << endl;
	cout << setw(100) << right << "                                                  " << endl;
	Sleep(8000);
	int number_of_answer = rand() % ques.question[list].answer.size();
	print_dib(prizes);
	print_one_question(ques, list);


	cout << setw(80) << right << "---------------------------------------------" << endl;
	cout << setw(43) << right << "Ответ: " << ques.question[list].answer[number_of_answer] << endl;
	cout << setw(80) << right << "---------------------------------------------" << endl;
	cout << setw(100) << right << "                                                  " << endl;
	cout << setw(100) << right << "                                                  " << endl;
	cout << setw(100) << right << "                --:************:--                " << endl;
	cout << setw(100) << right << "           - ************************-            " << endl;
	cout << setw(100) << right << "         :******************************:         " << endl;
	cout << setw(100) << right << "      -************************************-      " << endl;
	cout << setw(100) << right << "    -****************************************-    " << endl;
	cout << setw(100) << right << "   -********+%#####%+********+%#####%+********-   " << endl;
	cout << setw(100) << right << "  :********=#@+***+@#=******=#@+***+@#=********:  " << endl;
	cout << setw(100) << right << " -**********************************************- " << endl;
	cout << setw(100) << right << " *****+@@%%====++++++*********++++++====%%@@***** " << endl;
	cout << setw(100) << right << ":*****+#@::=#====%#@%%@@@#@@@%@#@%==+@@*:*#@*****:" << endl;
	cout << setw(100) << right << ":******+#@.*#*    @%    +#-   -#+    %@ :#@******:" << endl;
	cout << setw(100) << right << "********+@#=#*    @%	   +#-   -#+    %@=#%********" << endl;
	cout << setw(100) << right << "**********=##=.   @%    +#-   -#+   -@#@+*********" << endl;
	cout << setw(100) << right << ":***********+%##@+#%    +#-   -#==@#@=***********:" << endl;
	cout << setw(100) << right << " ***************+=@############@%=*************** " << endl;
	cout << setw(100) << right << " ************************************************ " << endl;
	cout << setw(100) << right << "  **********************************************  " << endl;
	cout << setw(100) << right << "   ********************************************   " << endl;
	cout << setw(100) << right << "    ******************************************    " << endl;
	cout << setw(100) << right << "      :************************************:      " << endl;
	cout << setw(100) << right << "          -:**************************:-          " << endl;
	cout << setw(100) << right << "               --:**************:--               " << endl;
	cout << setw(100) << right << "                                                  " << endl;

	sound->stop();
	sound = OpenSound(device, "mind.mp3", false); //открываем наш звук
	sound->play();
	sound->setRepeat(true);
}

void choice_life(const Phase& ques, int list, const vector <string>& prizes)
{
	sound->stop();
	sound = OpenSound(device, "mind.mp3", false); //открываем наш звук
	sound->play();
	sound->setRepeat(true);
	int k1;
	k1 = _getch();
	switch (k1)
	{
	case 65: // A
		print_conf_question(ques, prizes, list, 0, 0);
		fl_stop_life = FALSE;
		if (conf(k1))
		{
			sound->stop();
			sound = OpenSound(device, "conf.mp3", false); //открываем наш звук
			sound->play();
			Sleep(4000);
			if (ques.question[list].key == ques.question[list].answer[0])
			{
				print_conf_question(ques, prizes, list, 0, 1);
				winner();
				fl_stop = TRUE;
			}
			else
			{
				//print_conf_question(ques, prizes, list, 0, 1);
				if (!fl_endgame)
				{
					sound->stop();
					sound = OpenSound(device, "lifewrong.mp3", false); //открываем наш звук
					sound->play();
					temp_life = 0;
					print_conf_question(ques, prizes, list, 0, 0);
					Sleep(3000);
					fl_endgame = TRUE;
					choice_life(ques, list, prizes);
				}
				else
				{
					print_conf_question(ques, prizes, list, 0, 1);
					fl_stop = TRUE;
					end_game(ques, prizes);
				}
			}
		}
		else
			choice_life(ques, list, prizes);
		break;
	case 66: // B
		print_conf_question(ques, prizes, list, 1, 0);
		fl_stop_life = FALSE;
		if (conf(k1))
		{
			sound->stop();
			sound = OpenSound(device, "conf.mp3", false); //открываем наш звук
			sound->play();
			Sleep(4000);
			if (ques.question[list].key == ques.question[list].answer[1])
			{
				print_conf_question(ques, prizes, list, 1, 1);
				winner();
				fl_stop = TRUE;
			}
			else
				if (!fl_endgame)
				{
					sound->stop();
					sound = OpenSound(device, "lifewrong.mp3", false); //открываем наш звук
					sound->play();
					temp_life = 1;
					print_conf_question(ques, prizes, list, 1, 0);
					Sleep(3000);
					fl_endgame = TRUE;
					choice_life(ques, list, prizes);
				}
				else
				{
					print_conf_question(ques, prizes, list, 1, 1);
					fl_stop = TRUE;
					end_game(ques, prizes);
				}
		}
		else
			choice_life(ques, list, prizes);
		break;
	case 67: // C
		print_conf_question(ques, prizes, list, 2, 0);
		fl_stop_life = FALSE;
		if (conf(k1))
		{
			sound->stop();
			sound = OpenSound(device, "conf.mp3", false); //открываем наш звук
			sound->play();
			Sleep(4000);
			if (ques.question[list].key == ques.question[list].answer[2])
			{
				print_conf_question(ques, prizes, list, 2, 1);
				winner();
				fl_stop = TRUE;
			}
			else
				if (!fl_endgame)
				{
					sound->stop();
					sound = OpenSound(device, "lifewrong.mp3", false); //открываем наш звук
					sound->play();
					temp_life = 2;
					print_conf_question(ques, prizes, list, 2, 0);
					Sleep(3000);
					fl_endgame = TRUE;
					choice_life(ques, list, prizes);
				}
				else
				{
					print_conf_question(ques, prizes, list, 2, 1);
					fl_stop = TRUE;
					end_game(ques, prizes);
				}
		}
		else
			choice_life(ques, list, prizes);
		break;
	case 68: // D
		print_conf_question(ques, prizes, list, 3, 0);
		fl_stop_life = FALSE;
		if (conf(k1))
		{
			sound->stop();
			sound = OpenSound(device, "conf.mp3", false); //открываем наш звук
			sound->play();
			Sleep(4000);
			if (ques.question[list].key == ques.question[list].answer[3])
			{
				print_conf_question(ques, prizes, list, 3, 1);
				winner();
				fl_stop = TRUE;
			}
			else
				if (!fl_endgame)
				{
					sound->stop();
					sound = OpenSound(device, "lifewrong.mp3", false); //открываем наш звук
					sound->play();
					temp_life = 3;
					print_conf_question(ques, prizes, list, 3, 0);
					Sleep(3000);
					fl_endgame = TRUE;
					choice_life(ques, list, prizes);
				}
				else
				{
					print_conf_question(ques, prizes, list, 3, 1);
					fl_stop = TRUE;
					end_game(ques, prizes);
				}
		}
		else
			choice_life(ques, list, prizes);
		break;
	default:
		break;
	}
}

void choice(const Phase& ques, int list, const vector <string>& prizes) // 
{
	int k1;
	k1 = _getch(); // получаем символ без вывода знака
	switch (k1)
	{
	case 65: // A
		print_conf_question(ques, prizes, list, 0, 0);
		if (conf(k1))
		{
			sound->stop();
			sound = OpenSound(device, "conf.mp3", false); //открываем наш звук
			sound->play();
			Sleep(4000);
			print_conf_question(ques, prizes, list, 0, 1);
			if (ques.question[list].key == ques.question[list].answer[0])
			{
				winner();
			}
			else
				end_game(ques, prizes);
		}
		else
			choice(ques, list, prizes);
		break;
	case 66: // B
		print_conf_question(ques, prizes, list, 1, 0);
		if (conf(k1))
		{
			sound->stop();
			sound = OpenSound(device, "conf.mp3", false); //открываем наш звук
			sound->play();
			Sleep(4000);
			print_conf_question(ques, prizes, list, 1, 1);
			if (ques.question[list].key == ques.question[list].answer[1])
			{
				winner();
			}
			else
				end_game(ques, prizes);
		}
		else
			choice(ques, list, prizes);
		break;
	case 67: // C
		print_conf_question(ques, prizes, list, 2, 0);
		if (conf(k1))
		{
			sound->stop();
			sound = OpenSound(device, "conf.mp3", false); //открываем наш звук
			sound->play();
			Sleep(4000);
			print_conf_question(ques, prizes, list, 2, 1);
			if (ques.question[list].key == ques.question[list].answer[2])
			{
				winner();
			}
			else
				end_game(ques, prizes);
		}
		else
			choice(ques, list, prizes);
		break;
	case 68: // D
		print_conf_question(ques, prizes, list, 3, 0);
		if (conf(k1))
		{
			sound->stop();
			sound = OpenSound(device, "conf.mp3", false); //открываем наш звук
			sound->play();
			Sleep(4000);
			print_conf_question(ques, prizes, list, 3, 1);
			if (ques.question[list].key == ques.question[list].answer[3])
			{
				winner();
			}
			else
				end_game(ques, prizes);
		}
		else
			choice(ques, list, prizes);
		break;
	case 72: // H
		if (!fl_half)
		{
			sound->stop();
			sound = OpenSound(device, "line.mp3", false); //открываем наш звук
			sound->play();
			Sleep(700);
			fl_half = TRUE;
			print_dib(prizes);
			print_half_answer(ques, list);
			choice(ques, list, prizes);
		}
		else
			choice(ques, list, prizes);
		break;
	case 70: // F
		if (!fl_friends)
		{
			sound->stop();
			sound = OpenSound(device, "line.mp3", false); //открываем наш звук
			sound->play();
			Sleep(700);
			fl_friends = TRUE;
			print_dib(prizes);
			print_one_question(ques, list);
			print_voting(ques, list);
			choice(ques, list, prizes);
		}
		else
			choice(ques, list, prizes);
		break;
	case 80: // P
		if (!fl_phone)
		{
			sound->stop();
			sound = OpenSound(device, "line.mp3", false); //открываем наш звук
			sound->play();
			Sleep(700);
			fl_phone = TRUE;
			print_call(ques, list, prizes);
			choice(ques, list, prizes);
		}
		else
			choice(ques, list, prizes);
		break;
	case 76: // L
		if (!fl_life)
		{
			sound->stop();
			sound = OpenSound(device, "line.mp3", false); //открываем наш звук
			sound->play();
			Sleep(700);
			fl_life = TRUE;
			fl_phone = TRUE;
			fl_friends = TRUE;
			if (fl_half and fl_stop)
			{
				print_dib(prizes);
				print_half_answer(ques, list);
			}
			else
			{
				fl_half = TRUE;
				print_dib(prizes);
				print_one_question(ques, list);
			}
			choice_life(ques, list, prizes);
		}
		else
			choice(ques, list, prizes);
		break;
	default:
		choice(ques, list, prizes);
	}
}

void print_prize(int list)
{
	if (ex_prize == list)
		SetColor(9, 0);
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

void conf_menu_prizes(const Phase& ques, const vector <string>& prizes)
{
	switch (sub_m_count) // проверям, взяв первый символ переменной value
	{
	case 0: // если соглашаемся
		ex_prize = 0;
		play(ques, prizes);
		break;
	case 1: // если отказываемся
		ex_prize = 1;
		play(ques, prizes);
		break;
	case 2: // если отказываемся
		ex_prize = 2;
		play(ques, prizes);
		break;
	case 3: // если отказываемся
		ex_prize = 3;
		play(ques, prizes);
		break;
	case 4: // если отказываемся
		ex_prize = 4;
		play(ques, prizes);
		break;
	case 5: // если отказываемся
		ex_prize = 5;
		play(ques, prizes);
		break;
	case 6: // если отказываемся
		ex_prize = 6;
		play(ques, prizes);
		break;
	case 7: // если отказываемся
		ex_prize = 7;
		play(ques, prizes);;
		break;
	case 8: // если отказываемся
		ex_prize = 8;
		play(ques, prizes);
		break;
	case 9: // если отказываемся
		ex_prize = 9;
		play(ques, prizes);
		break;
	case 10: // если отказываемся
		ex_prize = 10;
		play(ques, prizes);
		break;
	case 11: // если отказываемся
		ex_prize = 11;
		play(ques, prizes);
		break;
	case 12: // если отказываемся
		ex_prize = 12;
		play(ques, prizes);
		break;
	case 13: // если отказываемся
		ex_prize = 13;
		play(ques, prizes);
		break;
	case 14: // если отказываемся
		ex_prize = 14;
		play(ques, prizes);
		break;
	default:
		break;
	}
}

void menu_prize_choice(const Phase& ques, const vector <string>& prizes)
{
	int k1;
	k1 = _getch(); // получаем символ стрелки без вывода знака
	if (k1 == 0xE0) // если стрелки
	{
		switch (k1)
		{
		case 0x48: // стрелка вверх
			sub_m_count--;
			if (sub_m_count < 0) sub_m_count = 0;
			menu_prize(ques, prizes);
			break;

		case 0x50: // стрелка вниз
			sub_m_count++;
			if (sub_m_count > 14) sub_m_count = 14;
			menu_prize(ques, prizes);
			break;
		case 0xD: // подтвердить
			conf_menu_prizes(ques, prizes);
			break;
		default:
			menu_prize_choice(ques, prizes);
		}
	}
	switch (k1)
	{
	case 0x48: // стрелка вверх
		sub_m_count--;
		if (sub_m_count < 0) sub_m_count = 0;
		menu_prize(ques, prizes);
		break;

	case 0x50: // стрелка вниз
		sub_m_count++;
		if (sub_m_count > 14) sub_m_count = 14;
		menu_prize(ques, prizes);
		break;
	case 0xD: // подтвердить
		conf_menu_prizes(ques, prizes);
		break;
	default:
		menu_prize_choice(ques, prizes);
	}
}

void menu_prize(const Phase& ques, const vector <string>& prizes)
{
	system("cls");
	cout << endl;
	cout << "Выберите несгораемую сумму: " << endl;
	for (int i = 0; i <= prizes.size() - 1; i++)
	{
		if (i <= 8)
		{
			if (sub_m_count == i)
				SetColor(6, 0);
			cout << i + 1 << ".  " << setw(13) << right << prizes[i] << endl;
			SetColor(7, 0);
		}
		else
		{
			if (sub_m_count == i)
				SetColor(6, 0);
			cout << i + 1 << ". " << setw(13) << right << prizes[i] << endl;
			SetColor(7, 0);
		}
	}
	menu_prize_choice(ques, prizes);
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
	cout << "...................--+@%@###@%==+++***:::::::::-:-:::::::********+=#######%%=:........-------------------" << "         " << "15 " << setw(13) << right; print_prize(14); cout << prizes[14]; SetColor(7, 0); cout << endl;
	cout << "....................:%@@####@%==+++***::::::::::::---::::::::***+++%#######@%+........-------------------" << "         " << "14 " << setw(13) << right; print_prize(13); cout << prizes[13]; SetColor(7, 0); cout << endl;
	cout << "....................*@@#####@@=+++****:::::---::::-:::::****+***++++%######@@%-.......----------.--------" << "         " << "13 " << setw(13) << right; print_prize(12); cout << prizes[12]; SetColor(7, 0); cout << endl;
	cout << "....................:#######@%=++*******:::::::::::**=%@#@@%=====++*+%########-.......-..----------------" << "         " << "12 " << setw(13) << right; print_prize(11); cout << prizes[11]; SetColor(7, 0); cout << endl;
	cout << ".....................@#######@%=%%@@@@@%=+*********=%#@=+*:**+=%%+**++@##@####=-......-------------------" << "         " << "11 " << setw(13) << right; print_prize(10); cout << prizes[10]; SetColor(7, 0); cout << endl;
	cout << "....................-=#######@@@%%=++=%@@#@%+++**+=@@%@%#####@=+*+**+=%#######=.......-------------------" << "         " << "10 " << setw(13) << right; print_prize(9); cout << prizes[9]; SetColor(7, 0); cout << endl;
	cout << "....................:@#######@@#@==+=@###@%@@%*::*==+**********::***+=@#######-.......-------------------" << "         " << "9  " << setw(13) << right; print_prize(8); cout << prizes[8]; SetColor(7, 0); cout << endl;
	cout << ".....................*######@%%%%%@@===*::::*+*::**::::*++=++*:::***+=@####@#=......-.-------------------" << "         " << "8  " << setw(13) << right; print_prize(7); cout << prizes[7]; SetColor(7, 0); cout << endl;
	cout << "....-.................:#@####%+++++++****::**+*:-:**:::::::::::::***+=%@###===-....----------------------" << "         " << "7  " << setw(13) << right; print_prize(6); cout << prizes[6]; SetColor(7, 0); cout << endl;
	cout << "....--..................-=####++****++++*:***++:::*****::::::::::***++=%#@%=--.....----------------------" << "         " << "6  " << setw(13) << right; print_prize(5); cout << prizes[5]; SetColor(7, 0); cout << endl;
	cout << "..-...--.-................:###=++***::::::*++=*:::***:*+=+**:::****++++%@#+:--....-----------------------" << "         " << "5  " << setw(13) << right; print_prize(4); cout << prizes[4]; SetColor(7, 0); cout << endl;
	cout << "-...------.-..-...........-%##%++***:*:**+++*+*::-:****+*+==+****++==+=+%#%:-......----------------------" << "         " << "4  " << setw(13) << right; print_prize(3); cout << prizes[3]; SetColor(7, 0); cout << endl;
	cout << ".---------.-.-..........--:-*@@==++****+===%==+*****+@@+****==+++===++==@#=.......-----------------------" << "         " << "3  " << setw(13) << right; print_prize(2); cout << prizes[2]; SetColor(7, 0); cout << endl;
	cout << "-----------..-..............--:@%%%====%++=%@@@%%@@@@+*******+++++++++=%##*.......-.---------------------" << "         " << "2  " << setw(13) << right; print_prize(1); cout << prizes[1]; SetColor(7, 0); cout << endl;
	cout << "--------.----...--..-.-.......-=@@@@%%=+====%%%@@@%=****++++++****++++%%=-........-----------------------" << "         " << "1  " << setw(13) << right; print_prize(0); cout << prizes[0]; SetColor(7, 0); cout << endl;
	cout << "------------.---------.........-%%%=+*=%%@##@@@%%%@@@%%@%=+*******+*+=%+%@-.........---------------------" << " " << endl;
	cout << "----------.....------...........:%%%=*:****+=%=++**+*************+*+%@==+###-.............-.-------------" << " " << endl;
	cout << "--.---.-.-.---------.............-=%%%=+*+**++++++++***:::::***++*=@@@%%+=####+.................---------" << "	 "; SetColor(10, 0); cout << "A B C D - варианты ответа"; SetColor(7, 0); cout << endl;
	cout << "--.---------------.................+@%=%%=****+*****::::::::*+=+=@@@@@%%*+#######%-......................" << "	 "; SetColor(10, 0); cout << "H - HALF 50 на 50"; SetColor(7, 0); cout << endl;
	cout << "....----------.-..................%#=%@@%@=+****:::::::::::*+%%@@@@@@%%=**############%+:-..............." << "	 "; SetColor(10, 0); cout << "P - CALL звонок другу"; SetColor(7, 0); cout << endl;
	cout << "----------...-..................+###%#@@@@@=+******:::::***=@@##@@@@%%%**:####################@%+*-......" << "	 "; SetColor(10, 0); cout << "F - HELP помощь зала"; SetColor(7, 0); cout << endl;
	cout << "------......................:%######+####@@@%=+******++++=@@@###@@@%%==**:###############################" << "	 "; SetColor(10, 0); cout << "L - X2 право на ошибку"; SetColor(7, 0); cout << endl;
	cout << "........................*@##########==@#####@@@%%====%%@@@@@@@@@%%====+**:@##############################" << " " << endl;
	cout << endl << endl << endl;
}

void play(const Phase& ques, const vector <string>& prizes)
{
	sound->stop();
	sound = OpenSound(device, "begin.mp3", false);
	sound->play();
	Sleep(6000);
	fl_endgame = FALSE;
	fl_friends = FALSE;
	fl_half = FALSE;
	fl_life = FALSE;
	fl_phone = FALSE;
	fl_stop = TRUE;
	fl_s_half = FALSE;
	temp = 5;
	//system("pause"); ///////////////////////////////////////////////////////////////////////
	for (int i = 0; i <= prizes.size() - 1; i++)
	{
		if (i == 14)
		{
			sound->stop();
			sound = OpenSound(device, "siren.mp3", false);
			sound->play();
			Sleep(4000);
		}
		int list = rand() % ques.question.size();
		print_dib(prizes);
		print_one_question(ques, list);
		sound->stop();
		sound = OpenSound(device, "next.mp3", false);
		sound->play();
		Sleep(3000);
		sound->stop();
		sound = OpenSound(device, "mind.mp3", false);
		sound->play();
		sound->setRepeat(true);
		choice(ques, list, prizes);
		cur_prize++;
		system("pause");
		fl_stop_life = TRUE;
		fl_endgame = FALSE;
		temp = 5;
		temp_life = 5;
		system("cls");
	}

	sound->stop();
	sound = OpenSound(device, "total.mp3", false);
	sound->play();
	cout << setw(100) << right << "Поздравляю, вы победили!" << endl;
	Sleep(5000);
	millioneer(ques, prizes);
}

void instruction(const Phase& ques, const vector<string>& prizes)
{
	system("cls");
	print_logo();
	cout << endl << endl;
	cout << "A B C D - варианты ответа. Нажимать с \"Капсом\"" << endl;
	cout << "H - HALF 50 на 50 - Компьютер убирает два неправильных ответа" << endl;
	cout << "P - CALL звонок другу - Игрок может посоветоваться либо с другом по телефону, либо со зрителем в студии" << endl;
	cout << "F - HELP помощь зала - Каждый зритель в студии голосует за правильный, на его взгляд, ответ, и игроку предоставляется статистика голосования" << endl;
	cout << "L - X2 право на ошибку - Игрок имеет право дать два варианта ответа, в том случае, если первый ответ оказался неверным, но только один раз за игру." << endl;
	cout << "Использование этой подсказки вместе с подсказкой \"50 на 50\" дает 100-процентное прохождение вопроса." << endl << endl;
	cout << "Для подтверждения ответа необходимо повторно выбрать необходимый ответ" << endl << endl;
	cout << "\t\t Приятной игры!" << endl << endl;
	system("pause");
	menu(ques, prizes);
}

void conf_menu(const Phase& ques, const vector <string>& prizes)
{
	switch (m_count)
	{
	case 0:
		menu_prize(ques, prizes);
		break;
	case 1:
		instruction(ques, prizes);
		break;
	case 2:
		cout << endl << setw(90) << right << "Всего доброго!" << endl;
		system("pause");
		exit(1);
		break;
	default:
		break;
	}
}

void menu_choice(const Phase& ques, const vector <string>& prizes) // в зависимости от стрелок изменяем меню
{
	int k1;
	k1 = _getch(); // получаем символ стрелки без вывода знака
	if (k1 == 0xE0) // если стрелки
	{
		switch (k1)
		{
		case 0x48: // стрелка вверх
			m_count--;
			if (m_count < 0) m_count = 0;
			menu(ques, prizes);
			break;

		case 0x50: // стрелка вниз
			m_count++;
			if (m_count > 2) m_count = 2;
			menu(ques, prizes);
			break;
		case 0xD: // подтвердить
			conf_menu(ques, prizes);
			break;
		default:
			menu_choice(ques, prizes);
		}
	}
	switch (k1)
	{
	case 0x48: // стрелка вверх
		m_count--;
		if (m_count < 0) m_count = 0;
		menu(ques, prizes);
		break;

	case 0x50: // стрелка вниз
		m_count++;
		if (m_count > 2) m_count = 2;
		menu(ques, prizes);
		break;
	case 0xD: // подтвердить
		conf_menu(ques, prizes);
		break;
	default:
		menu_choice(ques, prizes);
	}
}

void menu(const Phase& ques, const vector <string>& prizes)
{

	system("cls");
	print_logo();
	if (m_count == 0)
	{
		cout << setw(100) << right << "Игра \"Кто хочет стать миллионером?\"" << endl;
		cout << endl;
		SetColor(6, 0);
		cout << setw(80) << right << "\tИграть" << endl;
		SetColor(7, 0);
		cout << setw(85) << right << "\tИнструкция" << endl;
		cout << setw(80) << right << "\tВыход" << endl;
		menu_choice(ques, prizes);
	}
	if (m_count == 1)
	{
		cout << setw(100) << right << "Игра \"Кто хочет стать миллионером?\"" << endl;
		cout << endl;
		cout << setw(80) << right << "\tИграть" << endl;
		SetColor(6, 0);
		cout << setw(85) << right << "\tИнструкция" << endl;
		SetColor(7, 0);
		cout << setw(80) << right << "\tВыход" << endl;
		menu_choice(ques, prizes);
	}
	if (m_count == 2)
	{
		cout << setw(100) << right << "Игра \"Кто хочет стать миллионером?\"" << endl;
		cout << endl;
		cout << setw(80) << right << "\tИграть" << endl;
		cout << setw(85) << right << "\tИнструкция" << endl;
		SetColor(6, 0);
		cout << setw(80) << right << "\tВыход" << endl;
		SetColor(7, 0);
		menu_choice(ques, prizes);
	}
}

void millioneer(const Phase& ques, const vector <string> &prizes)
{
	system("cls");
	sound->stop();
	sound = OpenSound(device, "intro.mp3", false);
	sound->play();
	print_logo();
	cur_prize = 0;
	Sleep(7500);
	sound->stop();
	sound = OpenSound(device, "back.mp3", false); //открываем наш звук
	sound->play();
	sound->setRepeat(true);
	menu(ques, prizes);
}

int main()
{
	ifstream out;
	string str;

	setlocale(0, "Russian");
	vector <string> prizes({ "500", "1 000", "2 000", "3 000", "5 000", "10 000", "15 000", "25 000", "50 000", "100 000", "200 000", "400 000", "800 000", "1 500 000", "3 000 000" });
	system("mode con cols=300 lines=100");

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
	srand(time(NULL));

	//sound->play(); //проигрываем наш звук
	// ВОПРОСЫ + РАНДОМАЙЗ
	Phase easy;
	ifstream fout;
	//int list;
	fout.open("questions.txt");
	set_question(fout, easy);
	//print_questions(easy); // выводим все вопросы для проверки

	/*print_logo();
	cout << setw(100) << right << "Игра \"Кто хочет стать миллионером?\"" << endl;
	system("pause");*/
	millioneer(easy, prizes);
	
	//sound->stop();

	// +++++++++++++++++++++++++++++++++++++++++++++++
	return 0;
}