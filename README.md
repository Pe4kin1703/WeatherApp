# Weather monitoring application

## Assignment
Write a realization for weather conditions monitoring using OpenWeatherMap API and components from Boost library.

The program is divided into 3 modules:
- `network` - is responsible for connecting to the external server, sending a request, and receiving a response.
- `client` - is responsible for passing data to `network`, processing results from it, and printing results on a screen.
- `application` - is responsible for processing command-line arguments and passing them to `client`.

The program must be capable of:
- Showing help (as shown in `application.hpp`), if no arguments present or it was `-h` or `--help` argument;
- Reading city from the console;
- Reading token from console (If not present, check the file `token.txt` in the same directory as executable). Remember, token - is your secret information.
- Showing information about the weather in specified city. (as shown in `application.hpp`):
    - Name of the city
    - Temperature (degree Celsius)
    - Wind velocity (meters per second)
    - Wind direction (degrees)
- Connection to the server:
    - Reading host - `api.openweathermap.org` (must be set as default)
    - Reading port - `80` (must be set as default)
- Correct behavior when it can't connect to the server:
    - Prints `"Can't reach server"` when a connection could not be established
    - Prints `"Can't get weather in %city_name%"` when a city does not exist
    - Does not terminate with a non-zero error code in other cases

For header files, only appending is allowed.\
`main.cpp` is forbidden for modification.\
Must use Boost.Asio and Boost.Beast to work with the network, and Boost.Program to handle command-line arguments.\
Must use CMake to build the application. Name of the program must be `Weather`.\
`.gitlab-ci.yml` is forbidden for modification.

### Receiving a token
1. Open the following site: https://home.openweathermap.org/users/sign_up
2. Sing up there
3. In the purpose field select "Education/science"
4. Check your email, open letter, and press "Verify"
5. Your API will be here: https://home.openweathermap.org/api_keys
6. Read the API doc: https://openweathermap.org/current

### Setting up a pipeline
1. Go to Settings -> CI/CD -> General pipelines
2. Set CI/CD configuration file as `Weather/.gitlab-ci.yml`
3. Manually triger new pipeline (once only, later it will be triggered automatically)
    1. Go to CI/CD -> Pipelines -> Run Pipeline (Blue button on top)
    2. Select branch with your solution
    3. Start it

## Maintainer

#### Preconditions
- [ ] Pipeline passes 

### Test cases
- [ ] Shows help
- [ ] Can read city from a console
- [ ] Can read token from a console
- [ ] Can read token from a file
- [ ] Prints weather in existing city
- [ ] Uses default address and port, can select other address and port
- [ ] Prints correct message when a connection could not be established
- [ ] Prints correct message when a city does not exist
- [ ] Always finishes with exit code 0

### Code review
Technologies used:
- [ ] CMake for building
- [ ] boost::asio
- [ ] boost::beast
- [ ] boost::program

Style:
- [ ] No raw pointers used and no potential memory leaks exist
- [ ] Potential errors are wrapped in try-catch
- [ ] Header guards are present

Task requirements:
- [ ] Only additions are present in header files

## How to build the project

- create build directory
- put "cmake ../src && make" in command line to build project
- put "./Weather" to run