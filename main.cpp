#include <iostream>
#include <vector>
#include <asio.hpp>

using namespace std;
using namespace asio;
using namespace asio::ip;

int main(){
	string choise;
	bool good = false;

	io_context io_context;


	while (!good){
		cout << "Принимаю [1]\nПодключаюсь [2]\nВыбор: ";
		getline(cin, choise);
		if (choise == "1"){
			tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 45556));
			tcp::socket user2 = acceptor.accept();

			cout << "Cl" << endl;

			good = true;
		}
		else if (choise == "2"){
			cout << "Введите IP адресс нужного устройства в локальной сети: ";
			string serv_ip;
			getline(cin, serv_ip);

			tcp::socket user1(io_context);
			user1.connect(tcp::endpoint(make_address(serv_ip), 45556));

			cout << "Serv" << endl;

			good = true;
		}
		else{
			cout << "Вводите только цифры!\n\n";
		}
	}


	return 0;
}
