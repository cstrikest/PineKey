# PineKey BMS/IIDX 按键输入可视化

音乐游戏按键输入辅助显示

高亮按下的按键，统计各按键的按下次数，时长，频率，并图形化显示。显示内容可使用OBS等直播推流应用抓取窗口。  
支持键盘，手柄，游戏控制器（手台）等输入。  
目前无意release。有能力的朋友可以自行编译，或者+QQ384065633找我要。

![PineKey_v1.0.1](https://github.com/cstrikest/PineKey/blob/main/PineKey_v1.0.1.jpg?raw=true)

## TODO

- 1p 2p切换时，直方图对应数据顺序也切换
- 手柄，游戏控制器的输入（数字与模拟两者都要支持）
- 更好的KPS计算方法
- config布局重构，可以放在一个单独的滚动区域内
- 按键overlay独立窗口显示，并且可选背景透明度
- 更多的按键映射位置

## 历史版本

### v1.0.1

- XInput 手柄支持
- 修正界面错误
- 修正布局错误

### v1.0

- 增加按键UI独立窗口
- 增加总计数显示开关
- 增加kps显示开关
- DEBUG
  
### v0.6 (pre)

- 增加皿双按键绑定
- 调整界面大小与滚动

### v0.5.1 (pre)

- 完善kps折线图显示

### v0.5 (pre)

- 可保存的config
- 自动保存全局按键计数
- 添加按键计数归零按钮
- 调整数值
- 调整布局

### v0.4 (pre)

- 添加kps计算，显示kps折线图
- 可调整的按键计数与按下时长的直方图显示

### v0.3 (pre)

- 键盘输入支持

### v0.2 (pre)

- 完善按键布局，支持直列以及iidx式排列