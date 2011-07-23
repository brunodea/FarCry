#ifndef _SOME_ISLAND_CONTROLLER_HPP_
#define _SOME_ISLAND_CONTROLLER_HPP_

#include "IslandEngine.h"

/* Singleton */

namespace someisland
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

    view::DrawableUnit m_DUnit;
    view::DrawableUnit m_DCircleUnit;
};
} //end of namespace someisland.
#endif // _SOME_ISLAND_CONTROLLER_HPP_
