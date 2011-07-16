#include "util/Controller.h"

using namespace util;

Controller *Controller::msInstance = NULL;

Controller::Controller()
{
}

Controller *Controller::instance()
{
    if(msInstance == NULL)
        msInstance = new Controller();
    return msInstance;
}

