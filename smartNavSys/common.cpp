#include "common.hpp"

common::common() {
    std::ostringstream err;
    common::__state.open(nCommon::STATE);
    if (__state.fail()) {
        err << "__state fail";
        throw std::runtime_error(err.str());
    }  
}

common::~common() {
    __state.close();
}

void common::saveToState(int data, enum dataType dataType) {
    char readed[10];
    std::string line;
    const char *lookingFor = NULL;
    std::string slookingFor;
    std::ostringstream err;
    std::ostringstream dataToReplace;

    switch (dataType) {
    case common::dataType::Sensor1 :
        lookingFor = nCommon::SENSOR1;
        break;
    case common::dataType::Sensor2 :
        lookingFor = nCommon::SENSOR2;
        break;
    case common::dataType::Sensor3 :
        lookingFor = nCommon::SENSOR3;
        break;
    case common::dataType::Speed :
        lookingFor = nCommon::SPEED;
        break;
    case common::dataType::Heading :
        lookingFor = nCommon::HEADING;
        break;
    default:
        err << "dataType unKnown";
        throw std::runtime_error(err.str());
        break;
    }

    __state.seekg(0, std::ios::beg);
    std::streampos oldpos = __state.tellg();
    std::streampos newpos = __state.tellg();
    while (std::getline(__state, line)) {
        newpos = __state.tellg();
        switch (std::sscanf(line.data(), lookingFor, readed)) {
        case EOF:
            err << "Not found in state.txt: " << lookingFor;
            throw std::runtime_error(err.str());    
            break;
        case 0: 
            break;
        default:
            slookingFor = lookingFor;
            dataToReplace << slookingFor.substr(0, slookingFor.find("%s"))
            << std::setfill('0') << std::setw(3)   // To get 3 digit data
            << data << std::endl; 
            __state.seekg(oldpos, std::ios::beg);
            __state << dataToReplace.str();
            __state.seekg(newpos, std::ios::beg);
            goto exit_loop;
            break;
        }
        oldpos = __state.tellg();
    }
exit_loop:
    return;
}

int common::readFromState(enum dataType dataType) { 
    char readed[20];
    std::string line;
    const char *lookingFor = NULL;
    int ret = EXIT_FAILURE;

    switch (dataType) {
    case common::dataType::Sensor1 :
        lookingFor = nCommon::SENSOR1;
        break;
    case common::dataType::Sensor2 :
        lookingFor = nCommon::SENSOR2;
        break;
    case common::dataType::Sensor3 :
        lookingFor = nCommon::SENSOR3;
        break;
    default:
        std::ostringstream err;
        err << "dataType unKnown";
        throw std::runtime_error(err.str());
        break;
    }
    __state.seekg(0, std::ios::beg);
    while ( std::getline(__state, line) ) {
        switch (std::sscanf(line.data(), lookingFor, readed )) {
        case EOF:
            ret = EXIT_FAILURE; 
            goto exit_loop;
            break;
        case 0: 
            break;
        default:
            ret = atoi(readed);
            goto exit_loop;
            break;
        }
    }
exit_loop:
    return ret;
}

