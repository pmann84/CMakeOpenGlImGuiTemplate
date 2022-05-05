#include "application.hpp"

//static void error_callback(int error, const char* description)
//{
//    fprintf(stderr, "Error: %s\n", description);
//}

class my_app : public application
{
public:
    my_app(application_data props) : application(props)
    {
    }

    void on_update() override
    {
    }
};

int main()
{
    application_data props;
    my_app app(props);
    app.run();

    return 0;
}
