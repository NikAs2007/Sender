#include <iostream>
#include <vector>
#include <asio.hpp>
#include <fstream>
#include <filesystem>

using namespace std;
using namespace filesystem;
using namespace asio;
using namespace asio::ip;

int main(){
	string choise;
	bool good = false;

	io_context io_context;


	while (!good){
		cout << "Получаю файлы [1]\nОтправляю файлы [2]\nВыбор: ";
		getline(cin, choise);
		if (choise == "1"){
			tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 45556));
			tcp::socket user2 = acceptor.accept();

			cout << "Cl" << endl;

			bool true_path = false;

			while(!true_path){
				cout << "Введите путь к папке для копирования: ";
				string path_, repath;
				getline(cin, path_);
				for (int c = 0; c < path_.length(); ++c) {
					if (path_[c] != '"') repath += path_[c];
				}
				path_ = repath;

				if (exists(path_)){
					if (!is_regular_file(path_)){
						//
						true_path = true;
					}
					else{
						cout << "Требуеться ввести путь к папке!\n\n";
					}
				}
				else{
					cout << "Такого пути не существует!\n\n";
				}
			}


			good = true;
		}
		else if (choise == "2"){
			cout << "Введите IP адресс нужного устройства в локальной сети: ";
			string serv_ip;
			getline(cin, serv_ip);

			tcp::socket user1(io_context);
			user1.connect(tcp::endpoint(make_address(serv_ip), 45556));

			cout << "Serv" << endl;

			bool true_path = false;

			while(!true_path){
				cout << "Введите путь к файлу для копирования: ";
				string path_, repath;
				getline(cin, path_);
				for (int c = 0; c < path_.length(); ++c) {
					if (path_[c] != '"') repath += path_[c];
				}
				path_ = repath;

				if (exists(path_)){
					if (is_regular_file(path_)){
						//
						true_path = true;
					}
					else{
						cout << "Требуеться ввести путь к файлу!\n\n";
					}
				}
				else{
					cout << "Такого пути не существует!\n\n";
				}
			}

			good = true;
		}
		else{
			cout << "Вводите только цифры!\n\n";
		}
	}


	return 0;
}
