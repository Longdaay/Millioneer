#include <iostream> //����� ��� ������ ����� "cout<<"
#include "conio.h" //����� ��������� ��� "getche()" , � �� "cin>>"
#include <fstream>
#include <string>
#include "windows.h" //���������� audiere � �������
#include "audiere.h" //���� ����������


using namespace std;
using namespace audiere; //���������� ������������ ��� ��� ����� �������� ������ ����

int main()
{
	ifstream out;
	string str;

	setlocale(0, "Russian"); //����� ���� ������� ������� ��-������
	cout << "���������� ��������������� �����" << endl;

	AudioDevicePtr device = OpenDevice(); //��� ������ ����� ������� AudioDevice
	if (!device) {
		cout << "������ �������� AudioDevice. ������� ����� ������� ��� ������..";
		_getch();
		return 0; //������� �� ���������
	}

	OutputStreamPtr sound = OpenSound(device, "track.mp3", false); //��������� ��� ����
	if (!sound) {
		cout << "������ �������� �����! ��� ������ ������� ����� �������..";
		_getch();
		return 0;
	}

	sound->play(); //����������� ��� ����
	out.open("dib.txt");
	if (out.is_open())
	{
		while (!out.eof())
		{
			out >> str;
			cout << str << endl;
			str = "";
		}
	}

	_getch(); //��� ������� ����� ������� ������ ��� ����� �� ���������
}