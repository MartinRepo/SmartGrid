#include "../../include/server/api_handler.h";

json::value RunAlgorithms(json::value){
    json::value obj;
    obj[U("name")] = json::value::string(U("John Doe"));
    obj[U("age")] = json::value::number(30);
    obj[U("isDeveloper")] = json::value::boolean(true);

    json::value hobbies = json::value::array();
    hobbies[0] = json::value::string(U("Reading"));
    hobbies[1] = json::value::string(U("Hiking"));
    obj[U("hobbies")] = hobbies;
    return obj;
}