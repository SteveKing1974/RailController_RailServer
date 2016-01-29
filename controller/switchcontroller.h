#ifndef SWITCHCONTROLLER_H
#define SWITCHCONTROLLER_H


class SwitchController
{
public:
    enum SwitchState {
        eSwitchOpen,
        eSwitchClosed
    };

    SwitchController();

    void setState(SwitchState dir);
    SwitchState state() const;

private:
    SwitchState m_State;
};

#endif // SWITCHCONTROLLER_H
