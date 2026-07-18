#include "menu.h"

void Menu::InputInfoClients()
{
	std::cout << "input_first_name: ";
	std::cin >> __name;
	std::cout << "input_last_name: ";
	std::cin >> __last_name;
	std::cout << "input email: ";
	std::cin >> __email;
}

void Menu::InputTelephone()
{
	std::cout << "Input phone client: ";
	std::cin >> __phone;
	std::cout << "Input id_clients: ";
	std::cin >> __delete_id_client;
}

void Menu::InputDeleteModile()
{
	std::cout << "Enter the ID of the phone to be deleted: ";
	std::cin >> __delete_id;
}

void Menu::InputDeleteClient()
{
	std::cout << "Enter the ID of the client to be deleted: ";
	std::cin >> __delete_id_client;
}

void Menu::Inquiry()
{
	std::cout << "Inquiry: " << std::endl;
	std::cout << "1) - Add Clients. " << std::endl;
	std::cout << "2) - Add phone Clients" << std::endl;
	std::cout << "3) - Appdate info clients." << std::endl;
	std::cout << "4) - Delete phone" << std::endl;
	std::cout << "5) - Delete clients." << std::endl;
	std::cout << "6) - find clients" << std::endl;
	std::cout << "Exit" << std::endl;
}

std::string Menu::GetName()
{
	return __name;
}
std::string Menu::GetLastName()
{
	return __last_name;
}
std::string Menu::GetEmail()
{
	return __email;
}
std::string Menu::GetPhone()
{
	return __phone;
}
int Menu::GetIdClients()
{
	return __delete_id_client;
}
int Menu::GetIdPhone()
{
	return __delete_id;
}
void Menu::Clear()
{
	__name.clear();
	__phone.clear();
	__email.clear();
	__phone.clear();
	__delete_id_client = -1;
	__delete_id = -1;
}