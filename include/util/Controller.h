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

        bool isRunning() { return m_bRunning; }

    private:
        Controller();

        void onRender();
        void onUpdate();
        void onkeyEvent(int key, int state);

    private:
        static Controller *m_sInstance;
        bool m_bRunning;
    };
} //end of namespace util.
#endif // _FAR_CRY_CONTROLLER_HPP_
