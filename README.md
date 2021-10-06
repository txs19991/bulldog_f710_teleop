# F710控制bulldog进行移动
## 启动方式:
* roslaunch
```bash
    roslaunch bulldog_F710_teleop.launch vel_linear:=0.3 vel_angular:=1.0 pub_rate:=20
```
* 参数说明:
  * vel_linear:移动速度,m/s,缺省为0.3m/s
  * vel_angular:旋转速度,rad/s,缺省为1.0rad/s
  * pub_rate:控制指令频率,Hz,缺省为20Hz
## 控制方式:
* 将F710调整为DirectInput模式
* 按住LS键的同时,右摇杆前后控制前后移动,右摇杆左右控制顺逆时针旋转
## F710按键映射
* joy.axes:按键左右，按键上下，右摇杆左右，右摇杆上下，左摇杆左右，左摇杆上下
* joy.buttons:x,a,b,y,LB,RB,LT,RT,BACK...