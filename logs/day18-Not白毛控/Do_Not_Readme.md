# 省流
- **F键**的bug太多了555, 能力有限不会改
- 突然意识到键盘响应应当封装到scene类里面的, 但是我好像改不完了...
- 我有🐟🐟症
- 天哪时间好少
- **\"Not\"**开头的部分都是我写的

### 1.1 钢琴类 Piano (命名空间 NotPiano )
- 可以演奏简单的铺面, 后续开发者可以用这个写一些简单的BGM, 简谱语法如下

| 字符  | 说明   | 使用示例                                               |
| ----- | ------ | ------------------------------------------------------ |
| `1~7` | 音符   | 如 `1 2 3 4 5` 表示播放 `do re mi fa sol` 五个音符     |
| `0`   | 休止符 | 略                                                     |
| `,`   | 低音   | 即音符向下附点，最多可以有三个低音号。如 `1,` `2,,` 等 |
| `^`   | 高音   | 类比低音                                               |
| `#`   | 升音   | 向上半音高。如 `4#`                                    |
| `-`   | 延音   | 每个延音号将为音符额外多出一个四分音符的延时           |
| `_`   | 分音   | 每个分音号将使音符的延时减半                           |
| `.`   | 附点   | 每个附点号将使音符的延时增半（×1.5）                   |
| `[]`  | 和弦   | 中括号内的音符将一次性演奏                             |
| `\|`   | 小节线 | 将忽略这个符号                                     |
| `*` `%` `&` | 分音 | 分别将音符的延时缩减为原先的三分之一，五分之一和七分之一。 |
 
- 我写的Piano是魔改的别人的的 (我的支持和弦多层嵌套<font size="1">**原版不行**</font>, 但不支持双线演奏<font size="1">**原版可以**</font>), 本来想贴参考的原作者链接的, 但是我找不到那个视频了555.
### 1.2 Piano 的初级食用方法:
```cpp

NotPiano::Piano piano;
// 加载简谱 会在内部递归调用translate函数
auto sheet = NotPiano::Piano::compose("1 7^^ 1 7^^ 7^ 1 0");

// 调用多线程演奏简谱
piano.play(/* 乐谱 */ sheet, /* 1/4拍的持续时间(ms) */ 500, /* 音量(0 ~ 127) */ 127);

piano.end(); // 乐谱演奏是否结束, 结束则返回 true

piano.stop(); // 暂停演奏

NotPiano::Piano::clearSheet(sheet); // 记得析构乐谱 (懒得写一个单独的类了)

```

### 2.1 KeyBoardControl 的维护
```cpp
/*
* 在消息循环传一个 ExMessage 给 KeyBoardControl 更新
* 这个函数的返回值意味着响应了一个 ExMessage (可以用于过滤事件)
*/
ExMessage message;
while (peekmessage(&message)) {
	NotKeyBoard::KeyBoardControl::manager()->OnMessage(message);
}
```

### 2.2 KeyBoardControl 的使用
例如
```cpp
// 当 F 键被按下时返回 true
if(NotKeyBoard::KeyBoardControl::manager()->isDown(NotKeyBoard::F))
{
	// do someting...
}

// 当松开 A 键时返回 true
if(NotKeyBoard::KeyBoardControl::manager()->isUp(NotKeyBoard::A))
{
	// do someting...
}

```
### 2.3 对KeyBoardControl的期待
我引用了 **functional** 头, 本来想着设置回调函数的, 现在交给你了 (嘻嘻).

### ?.0 更改日志
- 09-02 22:03
	- 又加了一个函数, 用于演奏单个音符, 声明如下:
```cpp
void NotPiano::Piano::play(unsigned char note, unsigned char level = 3, bool is_sharp = false, int delay = 500, int volume = 0x7f);
```

- 09-02 22:23
	- 突然发现没写循环播放, 加一下
```cpp
piano.loop(true); // 设置循环播放
```

- 09-03 12:48
	- 发现 bug: 多线程没写好, 卡点可能会失去音乐...

- 09-03 16:15
	- 大幅度调整了Piano的代码结构, 具体更改看代码吧, 我这懒得同步更新了.
	- 新增了NotKeyBoardControl类 (单例), 管理<font color = "red">**部分**</font>>键盘事件. 支持扩展
	- 新增了物品栏钢琴效果, 但是有一丢丢延迟 (?)

- 09-03 16:40
	- 不是哥们, 我 **SceneManager** 在哪? 感觉 **F键** 的问题可以通过一个 **SceneManager** 解决... (后生可畏.jpg)

- 09-03 17:07
	- 我的时间差不多到这了..., 晚上ACM集训