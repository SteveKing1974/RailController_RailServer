#ifndef ISOLATORCONTROLLER_H
#define ISOLATORCONTROLLER_H


class IsolatorController
{
public:
    enum State {
        ISOLATED,
        CONNECTED
    } ;

    IsolatorController(int controlLine);

    void setState(IsolatorController::State newVal);
    void toggle();
    IsolatorController::State state() const { return m_State; }

private:
    int m_ControlLine;
    IsolatorController::State m_State;
};

#endif // ISOLATORCONTROLLER_H
