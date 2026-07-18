#include"Clients.h"

Clients::Clients(const std::string& conn_DB) : conn(conn_DB)
{

	if (!conn.is_open())
		throw std::runtime_error("Невозможно установить соединение к бд");
}

void Clients::AddTables(const std::string& query)
{
	pqxx::work tx{conn};
	tx.exec(query);
	tx.commit();
}

void Clients::AddClientsInto(const std::string& first_name, const std::string& last_name, const std::string& email)
{
    pqxx::work tx{ conn };
  

    tx.exec("INSERT INTO client ( first_name, last_name, email )"
        "VALUES ('" + tx.esc(first_name) + "', '" + tx.esc(last_name) + "', '" + tx.esc(email) + "');");
    tx.commit();
}

void Clients::AddMobile(const std::string& phone, const int& id_client)
{
    pqxx::work tx{ conn };
    std::string std_id_clients = std::to_string(id_client);
    int find_id_clients = tx.query_value<int>("SELECT COUNT(*) FROM client WHERE id = " + tx.esc(std_id_clients) + ";");
    tx.commit();
    if (find_id_clients == 0)
        std::cout << "A client with this ID was not found." << std::endl;
    else
    {
        pqxx::work insert_tx{ conn };
        insert_tx.exec_params("INSERT INTO telephone(id_clients, phone) VALUES ($1, $2)", id_client, phone);
        insert_tx.commit();
    }

}


void Clients::DeleteMobile(const int& id)
{
    pqxx::work tx{ conn };
    std::string std_id_phone = std::to_string(id);
    int find_id = tx.query_value<int>("SELECT COUNT(*) FROM telephone WHERE id = " + tx.esc(std_id_phone) + ";");
    tx.commit();

    if (find_id == 0)
        std::cout << "phone number not found." << std::endl;
    else
    {
        pqxx::work insert_tx{ conn };
        insert_tx.exec_params("DELETE FROM telephone WHERE ID = ($1)", find_id);
        insert_tx.commit();
    }
}



void Clients::DeleteClient(const int& id_clients)
{
    pqxx::work tx{ conn };
    int find_id = tx.query_value<int>("SELECT COUNT(*) FROM client WHERE id = ($1);", id_clients);
   

    if (find_id == 0)
    {
        std::cout << "client number not found." << std::endl;
        tx.commit();
        return;
    }
    else
    {
      
       auto vec_id_telephone = tx.query<int>("SELECT id FROM telephone WHERE id_clients = ($1)", id_clients);
       for (const auto& tuple : vec_id_telephone) 
       {
           int phone_id = std::get<0>(tuple);
           tx.exec_params("DELETE FROM telephone WHERE ID = ($1)", phone_id);
       }


   
       tx.exec_params("DELETE FROM client WHERE id = ($1)", id_clients);
       tx.commit();

    }
}

std::vector<int> Clients::FindClient()
{
    std::cout << "find a client by phone number? 1 - yes  ";
    std::string action;
    std::cin >> action;
    std::vector<int>result;
    if (action == "1")
    {
        std::string phone;
        std::cout << "Input phone numbers: ";
        std::cin >> phone;
        result = FindClientsNumberPhone(phone);
    }
    else
    {
        std::string first_name, last_name, email;
        std::cout << "Input first_name: ";
        std::cin >> first_name;
        std::cout << "Input last_name: ";
        std::cin >> last_name;
        std::cout << "Input emails: ";
        std::cin >> email;
        result = FindClientsByInformation(first_name, last_name, email);

    }
    return result;
}

std::vector<int> Clients::FindClientsByInformation(const std::string& first_name, const std::string& last_name, const std::string& emails)
{
    pqxx::work find_tx{ conn };

     auto client_id = find_tx.query<int>(
        "SELECT id FROM client WHERE first_name = '" + find_tx.esc(first_name) + "' AND email = '"
        + find_tx.esc(emails) + "' AND last_name = '" + find_tx.esc(last_name) + "'; ");
     std::vector<int>result;
     for (const auto& tuple : client_id)
     {
         int clients_id = std::get<0>(tuple);
         result.push_back(clients_id);
     }
   
     find_tx.commit();
     return result;
}

std::vector<int> Clients::FindClientsNumberPhone(const std::string& phone)
{
    pqxx::work find_tx{ conn };
    auto client_id = find_tx.query<int>(
        "SELECT id_clients FROM telephone WHERE phone = '" + find_tx.esc(phone) + "';");
    std::vector<int>result;
    for (const auto& tuple : client_id)
    {
        int clients_id = std::get<0>(tuple);
        result.push_back(clients_id);
    }
    
    find_tx.commit();
    return result;
}

void Clients::ChangingCustomerData(const std::string& first_name, const std::string& last_name, const std::string& email, const int&id)
{
    pqxx::work tx{ conn };

    tx.exec("UPDATE client SET first_name = '" + tx.esc(first_name) + "' , last_name = '" + tx.esc(last_name) + "', email = '" + tx.esc(email) + "' WHERE id = ($1)", id);

    tx.commit();
}