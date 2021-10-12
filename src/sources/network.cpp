// networklayer.cpp
#include "../headers/network.hpp"
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/version.hpp>
#include <boost/format.hpp>
#include <iostream>
#include <utility>


NetworkLayer::Network::Network(const ContextPtr &context_ptr, const IPAddress connectionIP) : 
                                                    m_ioPtr(context_ptr), m_connectionIP(connectionIP), 
                                                    m_stream(*context_ptr), m_e()
{
}

void NetworkLayer::Network::setIP(const IPAddress connectionIP){
    m_connectionIP.host = connectionIP.host;
    m_connectionIP.port = connectionIP.port;
}


bool NetworkLayer::Network::start()
{
        tcp::resolver resolver(*(m_ioPtr));
        auto const results = resolver.resolve(m_connectionIP.host, m_connectionIP.port, m_e);
        if (!m_e){
        m_stream.connect(results, m_e);
        }
        return m_stream.socket().is_open();
}

void NetworkLayer::Network::send(const std::string &city_name, const std::string &token)
{
    m_target = "/data/2.5/weather?q=" + city_name + "&appid=" + token + "&units=metric";

    http::request<http::string_body> req(http::verb::get, m_target, 11);

    req.set(http::field::host, m_connectionIP.host);
    req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    send(req);
}

void NetworkLayer::Network::send(const http::request<http::string_body> &request)
{
    if (m_stream.socket().is_open() && !m_e){
        http::write(m_stream, request, m_e);
    } 
}

NetworkLayer::http::response<NetworkLayer::http::dynamic_body> NetworkLayer::Network::p_receive()
{
    boost::beast::flat_buffer buffer;
    http::response<http::dynamic_body> res;
    if (!m_e){
    http::read(m_stream, buffer, res, m_e);
    }    
    return res;
}

std::string NetworkLayer::Network::receive(){
    return beast::buffers_to_string(p_receive().body().data());
}

NetworkLayer::Network::~Network()
{
    if (m_stream.socket().is_open() && !m_e){
        m_stream.socket().shutdown(tcp::socket::shutdown_both, m_e);
    }
}