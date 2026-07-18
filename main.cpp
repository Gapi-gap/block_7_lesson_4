#include"menu.h"
#include "Windows.h"



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

		Menu menu;
	
		menu.Inquiry();
		
		std::vector<int>result;
		bool b_action = true;
		while (b_action)
		{
			int action;
		
			
			std::cout << "Input action: ";
			std::cin >> action;

			switch (action)
			{
			case 1:
				
				menu.InputInfoClients();
				c.AddClientsInto(menu.GetName(), menu.GetLastName(), menu.GetEmail());
				break;

			case 2:
				
				int id_clients;
				menu.InputTelephone();
				c.AddMobile(menu.GetPhone(), menu.GetIdClients());
				break;
			case 3:
				menu.InputInfoClients();
				menu.InputDeleteClient();
				c.ChangingCustomerData(menu.GetName(), menu.GetLastName(), menu.GetEmail(), menu.GetIdClients());
				break;
			case 4:
			
				menu.InputDeleteModile();
				c.DeleteMobile(menu.GetIdPhone());
				break;
			case 5:
				
				menu.InputDeleteClient();
				c.DeleteClient(menu.GetIdClients());
				break;
			case 6:
				result =   c.FindClient();
				for (auto x : result)
				{
					std::cout << x << std::endl;
				}
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