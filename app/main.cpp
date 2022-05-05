#include "application.hpp"

class my_app : public application
{
public:
    my_app(application_data props) : application(props)
    {
    }

    // This function is run every frame
    void on_update() override
    {

    }
};

int main()
{
    application_data props { "My Amazing App", 1024, 768  };
    my_app app(props);
    app.run();

    return 0;
}
