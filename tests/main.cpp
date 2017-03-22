//
// Created by thongpv87 on 21/03/2017.
//

#include <core/future.hh>
#include <core/app-template.hh>
#include <core/sleep.hh>
#include <iostream>

extern future<> f();

int main(int argc, char** argv) {
    app_template app;
    try {
        app.run(argc, argv, f);
        using namespace std::chrono_literals;
        sleep(100s);
    } catch (std::runtime_error &e) {
        std::cout << "Could not start app: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}