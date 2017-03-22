#include <core/future.hh>
#include <core/sleep.hh>

future<> f() {
    std::cout << "Sleeping..." << std::flush;
    using namespace std::chrono_literals;
    sleep(2s).then([]() {
        std::cout << "2s" << std::endl;
    });

    sleep(1s).then([]() {
        std::cout << "1s" << std::endl;
    });

    return sleep(3s).then([]() {
        std::cout << "Done..." << std::endl;
    });
}