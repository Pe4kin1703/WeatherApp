// application.cpp

#include <string>
#include <iostream>
#include "../headers/application.hpp"
#include "../headers/client.hpp"


Application::Application(int argc, char **argv) : argc(argc), argv(argv), myOptions("Options")
{}

void Application::setup()   
{
    myOptions.add_options()
            ("help,h", "Show help")
            ("city,c", po::value<std::string>(), "Enter city (If the city name is divided into several words - use _ instead of space)")
            ("token,t", po::value<std::string>(), "Enter token")
            ("address,a", po::value<std::string>(), "Enter host address")
            ("port,p", po::value<std::string>(), "Enter port");
}

int Application::parse()
{
    po::variables_map vm;
    ClientLayer::Client client(std::make_shared<boost::asio::io_context>(), "api.openweathermap.org", "80");
    try
    {
        po::store(po :: parse_command_line (argc, argv, myOptions), vm);
       //po::notify(vm);

        if (vm.count("help") || argc == 1)
        {
            std::cout << myOptions << std::endl;
        }
        if (vm.count("city"))
        {
            client.setCity(vm["city"].as<std::string>());
        }

        if (vm.count("token")){
            client.setToken(vm["token"].as<std::string>());
        }

        if (vm.count("address")){
            client.setAdress(vm["address"].as<std::string>());
        }

        if (vm.count("port")){
            client.setPort(vm["port"].as<std::string>());
        }
        
        
    }
    catch( std::exception &e )
   {
      std::cerr << "ERROR - parsing error: " << e.what() << std::endl;
      std::cout << myOptions << std::endl;
      return 0;
   }
   catch( ... )
   {
      std::cerr << "ERROR - parsing error (unknown type)." << std::endl;
      std::cout << myOptions << std::endl;
      return 0;
   }
   client.process();
   return 0;
}

int Application::exec()
{
    setup();
    return parse();
}
