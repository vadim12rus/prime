#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

int main() {
	setlocale(LC_ALL, "");							// Поддержка кириллицы в консоли Windows
	IpAddress ip = IpAddress::getLocalAddress();	//Локальный ip Адресс
	TcpSocket socket;//программный интерфейс для обеспечения обмена данными между процессами
	Packet packet;	//Для осуществления пакетной передачи дынных

	sf::SocketSelector selector;
	selector.add(socket);

	char type;
	char mode = ' ';//Мод s- сервер, с - клиент
	int x = 0;      //координаты шара
	int y = 0;
	char buffer[2000];
	size_t received;	//??
	string text = "connect to: ";

	//***********Подключение***************//
	cout << ip << endl;
	cout << "Введите тип подключения:  c -клиент, s -сервер" << endl;
	cin >> type;
	if (type == 's') {
		TcpListener listener;
		listener.listen(2000);
		listener.accept(socket);    //который будет содержать новое соединение
		text += "Serwer";
		mode = 's';

	}
	else if (type == 'c') {
		cout << "new ip:";
		cin >> ip;

		socket.connect(ip, 2000); //ip и Порт
		text += "client";
		mode = 'r';
	}
	socket.send(text.c_str(), text.length() + 1);
	socket.receive(buffer, sizeof(buffer), received);
	cout << buffer << endl;



	//**********Отрисовка Формы***********************//
	RenderWindow window(sf::VideoMode(800, 600), "Network");//Создаем размер Главного окна
															//*******Элементы********************//
	CircleShape shape(10);     //создаем шар с радиусом 50

	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}


		}
		if (mode == 's') {
			socket.receive(packet);				//Команда которая ожидает данных в виде пакета от клиентской части
			if (packet >> x >> y) {				//вытаскиваем значение из пакета в переменную x и у (действие уже происходит)
				cout << x << ":" << y << endl; 	//..и если все прошло успешно то выводим её координаты
			}
		}

		if (mode == 'r') {
			if (Keyboard::isKeyPressed(Keyboard::Right)) { //первая координата Х отрицательна =>идём влево
				x++;
			}
			if (Keyboard::isKeyPressed(Keyboard::Left)) { //первая координата Х отрицательна =>идём влево
				x--;
			}

			if (Keyboard::isKeyPressed(Keyboard::Down)) { //первая координата Х отрицательна =>идём влево
				y++;
			}
			if (Keyboard::isKeyPressed(Keyboard::Up)) { //первая координата Х отрицательна =>идём влево
				y--;
			}

			packet << x << y;		//Пакуем значения координат в Пакет
			packet << x << y;
			socket.send(packet);	//Отправка данных
			packet.clear();			//Чистим пакет
		}
		window.clear();
		shape.setPosition(x, y);	//выставляем шар на координаты
		window.draw(shape);			//отрисовываем шар
		window.display();
		sleep(sf::milliseconds(10));//Задержка
	}//END

	system("pause");
	return 0;
}

#include <SFML/Network.hpp>
#include <string>
#include <thread>
#include <chrono>
#include <iostream>
 
using namespace std::chrono_literals;
 
struct Dane {
    int x, y;
};
 
void sendThread()
{
    sf::TcpSocket socket;
    sf::Socket::Status status = socket.connect("127.0.0.1", 53000);
 
    if (status != sf::Socket::Done) {
        std::cout << "socket error" << std::endl;
        std::this_thread::sleep_for(500ms);
        return;
    }
 
    Dane dane = { 123, 456 };
 
    while(true) {
        if (socket.send(&dane, sizeof(dane)) != sf::Socket::Done) {
            std::cout << "send error" << std::endl;
            std::this_thread::sleep_for(500ms);
            return;
        }
 
        std::this_thread::sleep_for(50ms);
    }
}
 
void receiveThread()
{
    sf::TcpListener listener;
 
    if (listener.listen(53000) != sf::Socket::Done) {
        std::cout << "listen error" << std::endl;
        std::this_thread::sleep_for(500ms);
        return;
    }
 
    sf::TcpSocket socket;
    if (listener.accept(socket) != sf::Socket::Done) {
        std::cout << "accept error" << std::endl;
        std::this_thread::sleep_for(500ms);
        return;
    }
 
    while (true) {
 
        Dane dane;
        std::size_t received;
 
        if (socket.receive(&dane, sizeof(dane), received) != sf::Socket::Done) {
            std::cout << "receive error" << std::endl;
            std::this_thread::sleep_for(500ms);
            return;
        }
 
        std::cout << dane.x << " " << dane.y << std::endl;
 
        std::this_thread::sleep_for(50ms);
    }
}
 
int main()
{
    std::thread thread(sendThread);
    //std::thread thread(receiveThread);
 
    thread.join();
}
