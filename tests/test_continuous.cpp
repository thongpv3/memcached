#include <core/future.hh>
#include <core/sleep.hh>

future<> basic_use_of_future() {
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

future<> sleep_for_a_while(uint32_t s) {
    using namespace std::chrono_literals;
    std::chrono::seconds sec(s);
    return sleep(sec).then([s](){
        std::cout << s << "s" << std::endl;
        return make_ready_future();
    });
}

//FIXME: This code doesn't work
future<> wait_for_all() {
    using namespace std::chrono_literals;
    std::cout << "Wait for all" << std::endl;
    when_all(sleep_for_a_while(3),
        sleep_for_a_while(1),
        sleep_for_a_while(2)).get();
    std::cout << "All jobs were done!" << std::endl;
    return make_ready_future();
}

future<> parallel_data_processing() {
    std::vector<uint32_t> times{1,3,5,2};
    return parallel_for_each(times, sleep_for_a_while);
}

future<> without_do_with() {
    auto&& i=5;
    return sleep_for_a_while(i).then([&i](){
        std::cout << "Without do_with(), i = " << i << std::endl;
    });
}

//FIXME: This code doesn't work
future<> with_do_with() {
    auto&& i = (uint32_t)5;
    do_with(std::move(i), [](uint32_t& s){
        return sleep_for_a_while(s).then([s](){
            std::cout << "With do_with(), i= " << s << std::endl;
            return make_ready_future();
        });
    });
    return make_ready_future();
}

future<> done_without_exception() {
    std::cout << "Done without exception" << std::endl;
    return make_ready_future();
}

//function return a future that solved an exception
future<> return_exception_future() {
    std::cout << "Return an exception future" << std::endl;
    if (true)
        return make_exception_future(std::logic_error("Failed to complete "));
    else
        return make_ready_future();
}

//function will not return a future at all
future<> failed_to_return_future() {
    std::cout << "Throw an exception" << std::endl;
    if (true)
        throw std::logic_error("Failed to return a future");
    return make_ready_future();
}

future<> basic_handle_exception() {
    return done_without_exception().then([]{
        return return_exception_future().then([]{
            std::cout << "This line will be skipped" << std::endl;
            return make_ready_future();
        }).then_wrapped([](auto&& result) {
            try {
                result.get();
                std::cout << "Previous jobs return a ready future" << std::endl;
            } catch (...) {
                std::cout << "Previous jobs return an exception future" << std::endl;
            }
            return make_ready_future();
        });
    });
}

future<> handle_all_exception() {
    try {
        return_exception_future();
        failed_to_return_future();
        done_without_exception();
    } catch (...) {
        std::cout << "An exception happened" << std::endl;
        return make_exception_future(std::current_exception());
    }
    std::cout << "All task done correctly" << std::endl;
    return make_ready_future();
}

future<> dont_do_this_1() {
    return failed_to_return_future().then_wrapped([](auto&& f) {
        std::cout << "Then wrapped was not executed" << std::endl;
        return make_ready_future();
    }).finally([]{
        std::cout << "And finally wasn't, too" << std::endl;
        return make_ready_future(); //No need to write this line of code because finally already done
    });
}

future<> dont_do_this_2() {
    //because of then only forward the value capture by future into continuation
    return return_exception_future().then([]() {
        std::cout << "This way will never print" << std::endl;
        return make_ready_future();
    });
}

//test every single test by comment/uncomment these line of code of this function
future<> f() {
    //do these work concurrently
//    return basic_use_of_future();
//    return parallel_data_processing();
    return without_do_with();
//    return with_do_with();

//    return basic_handle_exception();
//    return handle_all_exception();
//    return dont_do_this_1();
//    return dont_do_this_2();

//    return wait_for_all(); //This test haven't worked yet
}