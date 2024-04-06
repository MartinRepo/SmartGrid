#include <cpprest/http_listener.h>              // HTTP server
#include <cpprest/json.h>                        // JSON library
#include <iostream>
#include "../include/algorithms/Greedy.h"
#include "../include/server/api_handler.h"

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

void handle_options(http_request request)
{
    http_response response(status_codes::OK);
    response.headers().add(U("Allow"), U("GET, POST, OPTIONS"));
    response.headers().add(U("Access-Control-Allow-Origin"), U("*"));
    response.headers().add(U("Access-Control-Allow-Methods"), U("GET, POST, OPTIONS"));
    response.headers().add(U("Access-Control-Allow-Headers"), U("Content-Type"));
    request.reply(response);
}

void handle_post(http_request request) {
    request.headers().add(U("Access-Control-Allow-Origin"), U("*"));
    auto path = request.relative_uri().path();
    if (path == U("/api/run-algorithms")) {
        request.extract_json().then([&](json::value req_json) {
            auto results = RunAlgorithms(req_json);

            json::value response_json = json::value::object();
            response_json[U("algorithmResults")] = results;

            http_response http_response(status_codes::OK);
            http_response.set_body(response_json);
            http_response.headers().add(U("Access-Control-Allow-Origin"), U("*"));
            request.reply(http_response);
        }).wait();
    } else {
        request.reply(status_codes::NotFound, U("Not Found"));
    }
}

int main() {
    uri_builder uri(U("http://localhost:8000"));
    auto addr = uri.to_uri().to_string();
    http_listener listener(addr);

    listener.support(methods::OPTIONS, handle_options);
    listener.support(methods::POST, handle_post);

    try {
        listener
                .open()
                .then([&listener](){std::cout << "Starting to listen at: " << listener.uri().to_string() << std::endl;})
                .wait();

        std::cout << "HTTP server is running... Press ENTER to exit." << std::endl;
        std::string line;
        std::getline(std::cin, line);
    } catch (const std::exception &e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }

    return 0;
}