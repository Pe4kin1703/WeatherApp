// client.cpp
#include "../headers/client.hpp"
#include <fstream>
#include <iostream>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
ClientLayer::Client::Client(const NetworkLayer::ContextPtr & context_ptr, 
                            const std::string host, const std::string port)
                        :m_connection(new NetworkLayer::Network (context_ptr, {host,port}))
{
    
}

void ClientLayer::Client::setCity(const std::string & city_name)
{
    m_city = city_name;
}

void ClientLayer::Client::setToken(const std::string & token)
{
    m_token = token;
}

void ClientLayer::Client::setPort(const std::string & port)
{
    m_port = port;
}

void ClientLayer::Client::setAdress(const std::string & adress)
{
    m_adress = adress;
}


void ClientLayer::Client::process(){
    // if (m_city == ""){
    //     std::cout << "Please add city.\n";
    //     return;       
    // }
    if (!m_city.empty()){
        if (m_token.empty() && !readToken()){
            std::cout << "Please add token in command line or create token.txt and put it into the file.\n";
            return;
        }
        m_connection->setIP({m_adress, m_port});
        if (!m_connection->start()){
            std::cout<<"Can't reach server\n";
            return;
        }
        m_connection->send(m_city, m_token);
        //m_connection->p_receive();
        std::cout << parseJSONAnswerFromServer(m_connection->receive());
    }

}

bool ClientLayer::Client::readToken(){
    std::ifstream tokenFile ("token.txt");
    if (!tokenFile){
        return 0;
    }
    else {
        tokenFile >> m_token;
        return 1;
    }
}

std::string ClientLayer::Client::parseJSONAnswerFromServer(const std::string& res)
{
    try{
        std::stringstream jsonEncod(res);
        boost::property_tree::ptree root;
        boost::property_tree::read_json(jsonEncod, root);
        try{
            if (!root.get<std::string>("message").empty()){
                return "Can't get weather in " + m_city + "\n";
            }
        }
        catch (...){}
        std::string answerFromServer = "City: " + root.get<std::string>("name") + "\n" +
                                    "Temperature: " + root.get<std::string>("main.temp") + "°C\n" +
                                    "Wind's speed: " + root.get<std::string>("wind.speed") + " meter/sec\n" +
                                    "Wind's direction: " + root.get<std::string>("wind.deg") + "°\n";
    return answerFromServer;
    }
    catch(std::exception &e){
        std::cout<<"Oops, something wrong with parsing json answer.\n"<<e.what()<<"\n";
        return "";
    }
}