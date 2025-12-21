#include <iostream>
#include <vector>
#include <asio.hpp>
#include <fstream>
#include <filesystem>
#include <cstring>

using namespace std;
using namespace filesystem;
using namespace asio;
using namespace asio::ip;

struct FileHeader{
	size_t fsize;
	size_t nsize;
};

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

						unsigned char buff[1024];

						size_t s = read(user2, asio::buffer(&buff, sizeof(FileHeader)));

						FileHeader fh;
						memcpy(&fh.fsize, buff, sizeof(size_t));
						memcpy(&fh.nsize, buff+8, sizeof(size_t));

						cout << endl << fh.fsize << endl << fh.nsize << endl;

						read(user2, asio::buffer(buff, sizeof(buff)));

						string namefile = "";

						for (int i = 0; i < fh.nsize; ++i){
							namefile += buff[i];
						}

						cout << namefile << endl;

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

						//Отправка заголовка
						unsigned char buff[1024];
						FileHeader fh;
						fh.fsize = file_size(path_);
						path p(path_);
						fh.nsize = p.filename().string().size();
						memcpy(buff, &fh, sizeof(FileHeader));

						write(user1, asio::buffer(&buff, sizeof(buff)));

						//Отправка имени
						unsigned char name[1024];
						string n = p.filename().string();
						write(user1, asio::buffer(n, n.size()));

						//Отправка файла
						char chunk[1024];
						ifstream learn_file(p, ios::binary);
						size_t tr = 0;

						/*
						while (tr < fh.fsize){
							learn_file.read(chunk, 1024);
							tr += min(1024, (int)learn_file.gcount());
							write(user1, asio::buffer(chunk, min(1024, (int)learn_file.gcount())));
						}
						*/

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
