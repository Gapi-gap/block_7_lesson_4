#pragma once
#include "Clients.h"


class Menu
{
public:
	void Inquiry();
	//Ввод информации о клиенте( ФИ почта)
	void InputInfoClients();
	//Ввод телефона для конкретного клиента
	void InputTelephone();
	//Удаляем номер телефона из бд
	void InputDeleteModile();
	//удаляем клиента из бд
	void InputDeleteClient();

	std::string GetName();
	std::string GetLastName();
	std::string GetEmail();
	std::string GetPhone();
	int GetIdClients();
	int GetIdPhone();
	void Clear();

private:
	std::string __name, __last_name, __email;
	std::string __phone;
	int __delete_id;
	int __delete_id_client;
};