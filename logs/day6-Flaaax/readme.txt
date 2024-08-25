---更新日志---
修改了PWindow类，在debug模式下开启控制台窗口

修复了一部分类型转换警告

新建PScene类，支持原有gui系统的同时实现帧更新（游戏循环），类中注释有简略说明。如果gui组件消失，查看SetDrawPolicy函数
同时，将PLGame原有的ui部分迁移到了MainScene与LoadingScene，PLGame类现在负责更新不同scene
（总得有人写主循环

在Singleton.h创建了Singleton模板类以便其它单例类使用
*你仍然可以对继承Singleton的类安全使用PGetSingleton，它将返回唯一实例

将一些常数宏替换为了constexpr

新增Vec2，Hitbox，CollisionManager，RenderInfo等类
其中CollisionManager不仅处理碰撞，还处理物理模拟

关于后续游戏内容，请在scene/GameScene类中实现，获取窗口大小以及相机位置并依此设置RenderInfo。也可以在GameScene中添加gui组件
关于PScene类的使用方法，可以参考MainScene与LoadingScene


---待解决---
字体文件未关闭导致文件被锁定
输入框只支持ASCII字符，这部分逻辑在PInput::OnMessage中
实现纵坐标翻转绘制，目前y轴绘制方向是从上到下
关闭窗口时会出现空指针异常


---写给后人的话---
请不要忽视编译器警告
请在对应位置创建文件，例如，头文件在include文件夹，源文件在source文件夹


最后，祝开发顺利：）