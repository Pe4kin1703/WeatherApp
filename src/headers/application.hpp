#ifndef _WHEATHER_APPLICATION_APPLICATION_HPP_
#define _WHEATHER_APPLICATION_APPLICATION_HPP_

#include <string>
#include <boost/program_options.hpp>
namespace po = boost::program_options;



class Application
{

private:
    po::options_description myOptions;
    int argc;
    char** argv;

public:
    Application(int argc, char* argv[]);

    int parse();

    // The program should look like the example below, if no arguments are written
    /**
    Options:
      -h [ --help ]         Show help
      -c [ --city ] arg     Enter city (If the city name is divided into several 
                            words - use _ instead of space)
      -t [ --token ] arg    Enter token
      -a [ --address ] arg  Enter host address
      -p [ --port ] arg     Enter port
    */

    // A standart output should look like the example below
    /**
      $ ./WeatherApp --city=Kyiv
      City: Kyiv
      Temperature: 0°C
      Wind's speed: 2 meter/sec
      Wind's direction: 140°
     */

    /**
     * @brief Parse command-line arguments ( Need to use boost::program_options ). Call Client
     * */
    int exec();
protected:
    void setup();

};


#endif //_WHEATHER_APPLICATION_APPLICATION.HPP_
