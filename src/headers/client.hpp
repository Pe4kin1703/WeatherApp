#pragma once
#include "network.hpp"
namespace ClientLayer
{
    using tcp = NetworkLayer::tcp;

    class Client
    {
    public:
        /**
         * @brief Ctor
         * @param context_ptr - smart pointer to io_context
         * @param host - server address
         * @param port - server port
         * */
        Client(const NetworkLayer::ContextPtr & context_ptr, const std::string host, const std::string port);

        /**
         * @brief Main function that connections to server, sends request and shows result
         * */
        void process();

        void setCity(const std::string & city_name);
        void setToken(const std::string & token);
        void setPort(const std::string & port);
        void setAdress(const std::string & adress);

    private:
        std::shared_ptr<NetworkLayer::Network> m_connection;
        std::string m_city = "";
        std::string m_token = "";
        std::string m_adress = "api.openweathermap.org";
        std::string m_port = "80";
        bool readToken();
        std::string parseJSONAnswerFromServer(const std::string& res);

    };
}