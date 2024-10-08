# day16：牵丝蝠zExNocs

# 我干了什么？
## 抽搐问题
首先第一个就是困扰了前面很多大犇的一件事：在上面末地石上下抽搐但是在下面灰色羊毛却不上下抽搐的问题。

出现这个问题的原因其实很简单：精度问题。浮点应该添加相应的精度以达到相对准确的判断。
在碰撞类的 `CollisionManager` 中对静态和动态的碰撞箱位置修正是直接让动态碰撞箱加上相应的偏移量 `offset`，这是使得两个碰撞箱修正的对应值是相等的，而判断两个碰撞箱是否相撞的条件中并没有判断边界重合相等的情况，因此在位置修正后两个碰撞箱又会被判断为非碰撞的状态，此时玩家类会受重力影响往下落，往下落后又判断为碰撞状态进行修整，而修整的位置比此时玩家的位置偏高，依次循环产生了上下抽搐。

## 修改现有的 `PAnimation` 类和 `PAnimator` 类
之前的 `PAnimation` 只能储存 `int`，`float`，`double` 类型。将 `PAnimation` 和定时器结合起来完善了动画类。但是并没有做图片分割和渲染接口(因为是用模板类写的，按理来说应该用一个可渲染抽象接口来写)，而是给出当前动画帧的接口。
`PAnimator` 类使用工厂设计模式，可以让一个 `Entity` 类拥有多个动画。使用 `createAnimation(动画名字，是否循环，切换间隔)`来注册新的动画。

## 添加资源管理器 `PResourseManager` 类
使用单例模式来调用该唯一类。该类使用智能指针来永久加载图片类`PImage`（也可以做一些暂时加载的图片，但是因为体量暂时不大就没写）。

## 全新的钓鱼场景
综合前人写的碰撞箱和新改的 `PAnimation` 类来创建了全新版本的钓鱼场景。
在主界面中选择 `ZFishing` 按钮进入该场景，使用 `空格` 或者 `鼠标左键` 来抓鱼。
使用 `Esc` 返回到主菜单（数据会清空）。

事实证明目前的底层代码还算是比较完善。

## 其他
本来想用状态机来实现钩子和鱼的状态，但是发现状态机并没有被完善。如果再写状态机的话我的时间是不够的，因此就使用了类状态机的方法(本质上还是if else嵌套，真正的状态机应该是使用状态设计模式来实现)来实现了我的 `ZHook` 和 `ZFish`。
我发现前人大部分都在想办法增加游戏的功能（例如buff、背包之类的），而并没有完善底层代码，又或者为画的大饼没有添加相应的引导（例如提供抽象接口），这导致不仅仅想要完成原来的 2D mc 游戏遥遥无期，也导致想要制作新的游戏场景变得很困难。
如果一开始的目标并不是制作2D mc游戏，而是去制作一些简单的横版场景，结合v老师的视频，可能完成度会比这高的多。

到目前已经可以使用现有的功能制作一些简单的游戏场景了，我希望后人能够去制作自己的场景而不是局限于制作2D mc游戏中。