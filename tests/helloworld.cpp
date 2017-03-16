//
// Created by thongpv87 on 16/03/2017.
//

#include <core/app-template.hh>
#include <core/reactor.hh>
#include <iostream>

int main(int argc, char** argv) {
    app_template app;
    app.run(argc, argv, [] {
        std::cout << "Hello world\n";
        return make_ready_future<>();
    });
}