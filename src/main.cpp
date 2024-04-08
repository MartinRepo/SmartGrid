#include <cpprest/http_listener.h>              // HTTP server
#include <cpprest/json.h>                        // JSON library
#include <iostream>
#include <csignal>
#include <thread>
#include "../include/algorithms/Greedy.h"
#include "../include/server/api_handler.h"

using namespace web;
using namespace web::http;
using namespace web::http::experimental::listener;

volatile sig_atomic_t stop;

void inthand(int signum) {
    stop = 1;
}

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
            for (size_t i = 0; i < results.size(); ++i) {
                json::value inner_array = json::value::array();
                for (size_t j = 0; j < results[i].size(); ++j) {
                    inner_array[j] = results[i][j];
                }
                if(i==0) {
                    response_json[U("TotalCost")] = inner_array;
                } else if(i==1) {
                    response_json[U("PeakCost")] = inner_array;
                } else if(i==2) {
                    response_json[U("RunningTime")] = inner_array;
                }
            }

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
    signal(SIGINT, inthand);
    signal(SIGTERM, inthand);
    uri_builder uri(U("http://0.0.0.0:8000"));
    auto addr = uri.to_uri().to_string();
    http_listener listener(addr);

    listener.support(methods::OPTIONS, handle_options);
    listener.support(methods::POST, handle_post);

    try {
        listener
                .open()
                .then([&listener](){std::cout << "Server is running at: " << listener.uri().to_string() << std::endl;})
                .wait();
        while(!stop){
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    } catch (const std::exception &e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }

    return 0;
}