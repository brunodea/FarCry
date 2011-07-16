#ifndef _FAR_CRY_CONTROLLER_HPP_
#define _FAR_CRY_CONTROLLER_HPP_

/* Singleton */

namespace util
{
    class Controller
    {
    public:
        Controller *instance();

        bool isRunning() { return mbRunning; }
        void setRunning(bool val) { mbRunning = val; }
    private:
        Controller();

    private:
        static Controller *msInstance;
        bool mbRunning;
    };
} //end of namespace util.
#endif // _FAR_CRY_CONTROLLER_HPP_
