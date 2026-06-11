#pragma once
#include<pqxx/pqxx>

#include <iostream>
#include <vector>
 
class Clients
{
public:
	Clients(const std::string&);
	void AddTables(const std::string&);
	void AddClientsInto(const std::string&, const std::string&, const std::string&);
	void AddMobile(const std::string&, const int&);
	void DeleteMobile(const int&);
	void DeleteClient(const int&);
	void FindClient();
	void ChangingCustomerData(const std::string&, const std::string&, const std::string&, const int&);
private:
	pqxx::connection conn;
	//std::string query_add_clients_info;
	void FindClientsNumberPhone(const std::string&);
	void FindClientsByInformation(const std::string&, const std::string&,const std::string&);
};