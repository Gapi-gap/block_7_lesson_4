#include"Clients.h"
#include "Windows.h"

void InputInfoClients(std::string& name, std::string& last_name, std::string& email)
{
	std::cout << "input_first_name: ";
	std::cin >> name;
	std::cout << "input_last_name: ";
	std::cin >> last_name;
	std::cout << "input email: ";
	std::cin >> email;
}

void InputTelephone(std::string& phone, int& id_cliens)
{
	std::cout << "Input phone client: ";
	std::cin >> phone;
	std::cout << "Input id_clients: ";
	std::cin >> id_cliens;
}

void InputDeleteModile(int& delete_id_phone)
{
	std::cout << "Enter the ID of the phone to be deleted: ";
	std::cin >> delete_id_phone;
}

void InputDeleteClient(int& delete_id_client)
{
	std::cout << "Enter the ID of the client to be deleted: ";
	std::cin >> delete_id_client;
}

int main()
{
	SetConsoleCP(65001);       // Для ввода с клавиатуры
	SetConsoleOutputCP(65001); // Для вывода на экран

	try
	{

		Clients c("host=localhost port=5432 dbname=Clients user=postgres password=Mac+3012prog");


		std::string new_query_crete_tables_clietns = "CREATE TABLE IF NOT EXISTS client("
			" first_name VARCHAR(60) NOT NULL, "
			" last_name VARCHAR(60) NOT NULL, "
			"id SERIAL PRIMARY KEY, "
			" email VARCHAR(100) NOT NULL); ";

		c.AddTables(new_query_crete_tables_clietns);

		//std::string limitation_clietns = "ALTER TABLE client ADD CONSTRAINT unique_full_identity UNIQUE(first_name, last_name, email); ";
		//c.AddTables(limitation_clietns);

		std::string new_query_crete_tables_telephone = "CREATE TABLE IF NOT EXISTS telephone( "
			"id SERIAL PRIMARY KEY, "
			"id_clients INTEGER NOT NULL REFERENCES client(id), "
			"phone VARCHAR(16) UNIQUE NOT NULL);";
		c.AddTables(new_query_crete_tables_telephone);

		//std::string limitation_telephone("ALTER TABLE telephone ADD CONSTRAINT unique_full_identity_phone UNIQUE(id_clients, phone); ");
		//c.AddTables(limitation_telephone);


		std::cout << "Управление базы данных для пользователя: " << std::endl;
		std::cout << "1) - Add Clients. " << std::endl;
		std::cout <<"2) - Add phone Clients" << std::endl;
		std::cout <<"3) - Метод, позволяющий изменить данные о клиенте." << std::endl;
		std::cout <<"4) - Delete phone" << std::endl;
		std::cout <<"5) - Delete clients." << std::endl;
		std::cout <<"6) - find clients" << std::endl;
		std::cout << "иное значение выход с программы" << std::endl;

		bool b_action = true;
		while (b_action)
		{
			int action;
			std::string name, last_name, email;
			std::string phone;
			int delete_id;
			int delete_id_client;
			std::cout << "Input action: ";
			std::cin >> action;

			switch (action)
			{
			case 1:
				
				InputInfoClients(name, last_name, email);
				c.AddClientsInto(name, last_name, email);
				break;

			case 2:
				
				int id_clients;
				InputTelephone(phone, id_clients);
				c.AddMobile(phone, id_clients);
				break;
			case 3:
				InputInfoClients(name, last_name, email);
				InputDeleteClient(delete_id_client);
				c.ChangingCustomerData(name, last_name, email, delete_id_client);
				break;
			case 4:
			
				InputDeleteModile(delete_id);
				c.DeleteMobile(delete_id);
				break;
			case 5:
				
				InputDeleteClient(delete_id_client);
				c.DeleteClient(delete_id_client);
				break;
			case 6:
				c.FindClient();
				break;
			default:
				b_action = false;
			}
		}
	}
	catch (const pqxx::sql_error& e)
	{
		std::cerr << "Ошибка SQL: " << e.what() << std::endl;
		std::cerr << "Запрос: " << e.query() << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << "Ошибка: " << e.what() << std::endl;
	}
}