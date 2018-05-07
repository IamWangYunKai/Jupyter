#ifndef STATICPARAM_H
#define STATICPARAM_H
namespace ZSS{
namespace Jupyter {
    const QString UDP_ADDRESS = "233.233.233.233";
    const int UDP_SEND_PORT = 10002;
    const int UDP_RECEIVE_PORT = 10001;
}
namespace Vehicle{
    const float MAX_SPEED = 3.0;// (m/s)
    const float MAX_ROTATION_SPEED = 10.0;// (rad/s)
    const float MAX_ACC = 2.0;// m/s^2
    const float MAX_ROTATION_ACC = 10.0;//rad/s^2
}
}
#endif // STATICPARAM_H
