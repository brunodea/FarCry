#ifndef _FAR_CRY_CONTROLLER_HPP_
#define _FAR_CRY_CONTROLLER_HPP_

/* Singleton */

namespace util
{
    class Controller
    {
    public:
        static Controller *instance();

        void run();
        void onKeyEvent(int key, int state);

    private:
        Controller();

        void onRender();
        void onUpdate();

        bool isRunning() { return m_bRunning; }
    private:
        static Controller *m_sInstance;
        bool m_bRunning;
    };
} //end of namespace util.
#endif // _FAR_CRY_CONTROLLER_HPP_
