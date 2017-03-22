//
// Created by thongpv87 on 20/03/2017.
//

#include <core/future.hh>
#include <core/distributed.hh>
#include <core/sleep.hh>
#include <core/seastar.hh>

class computing_service : public seastar::async_sharded_service<computing_service> {
public:
    future<> status() {
        std::cout << "Math service currently active on cpu #" << engine().cpu_id() << std::endl;
        return make_ready_future();
    }

    future<uint64_t> factorial(const uint32_t n) {
        using namespace std::chrono_literals;
        sleep(2s);
        uint64_t p = 1;
        for (uint32_t i = 1; i < n; i++)
            p *= i;
        std::cout << "factorial of (" << n <<") is " << p << std::endl;
        return make_ready_future<uint64_t>(p);
    }

    future<uint64_t> sum(const uint32_t n) {
        using namespace std::chrono_literals;
        sleep(1s);
        uint64_t s = 0;
        for (uint32_t i = 0; i < n; i++) {
            s += i;
        }
        std::cout << "sum form 1 to " << n <<" is " << s << std::endl;
        return make_ready_future<uint64_t>(s);
    }

    future<> stop() {
        return make_ready_future();
    }
};

uint8_t getCpu(uint32_t n) {
    return n % smp::count;
}

future<> f() {
    enum class Operation {
        SUM, FACTORIAL
    };
    std::vector<std::pair<Operation, uint32_t>> parms{{Operation::SUM,       5},
                                                      {Operation::FACTORIAL, 7},
                                                      {Operation::SUM,       20},
                                                      {Operation::SUM,       13},
                                                      {Operation::FACTORIAL, 13}};

    auto &&sv = std::make_shared<distributed<computing_service>>();
    return sv->start().then([sv]{
        return sv->invoke_on_all(&computing_service::status);
    }).then([sv, parms{parms}] {
        for (auto const &i:parms) {
            switch (i.first) {
                case Operation::SUM: {
                    sv->invoke_on(getCpu(i.second), &computing_service::sum, i.second).then([i](uint64_t result) {
                        std::cout << "RESULT: Sum from 1 to " << i.second << ": " << result << std::endl;
                    });
                    break;
                }
                case Operation::FACTORIAL: {
                    sv->invoke_on(getCpu(i.second), &computing_service::factorial, i.second).then([i](uint64_t result) {
                        std::cout << "RESULT: Factorial of " << i.second << ": " << result << std::endl;
                    });

                    break;
                }
            }
        }
        return sv->stop();
    });
}