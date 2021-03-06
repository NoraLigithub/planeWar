
# 《飞机游戏实验报告》
学号：131220050
姓名：李楠

## 一.总体设计方案
###   运行框架：
1. 初始化屏幕中的显示，包括边框，飞机，提示信息，战况。
2. 进入游戏主循环，每次循环间隔一定时间。循环体中，可以用标志量控制此次循环是否执行该部分内容，如敌机的移动与时间间隔有关需判断。
	* 根据时间间隔随机产生敌机，移动敌机，移动子弹。
	* 用一个变量over标志游戏是否结束，检测over判断是否结束，结束则进入相应函数,不结束则继续。
	* 执行Commandcontro()判断此时是否有键盘输入，若有则执行相应要求。
### 显示：
通过移动光标对屏幕中某一个点进行输出实现基本的显示，组合实现飞机，敌人，子弹，提示文字的显示。

* 移动：
物体的移动基于“擦除旧的，画上新的”这一思路，其中的时间控制通过运用sleep函数与一些计时的标志量实现，不同的飞机可以有不同的速度。
* 碰撞：
每一个出现的物体都有其坐标，通过其坐标的相互值作为检测碰撞的依据。

## 二.类的层次结构设计
   基类：Point;  派生类：Enemy,Ballet
   类：GameControl; 聚合：Point,Enemy,Ballet.

## 三.实验中遇到的难点问题和解决方案
###   1. 怎么让不同飞机可以有不同速度？
   
 首先尝试利用time函数，但它的精度是一秒，对这样慢的速度不太满意。后来尝试利用sleep函数，它的功能是挂起一段时间，单位是ms。思路如下：每次循环间隔一段时间T，作为一个基本时间。GameControl类定义一个敌机速度speed，作为敌机速度的基本单位(越大速度越慢==)，每隔speed*T时间运行一次enemy.move()函数。该函数进一步控制相应敌机的不同速度，如可以只有第n次运行该函数时进行一次真正的移动（n为k的倍数），则该飞机的速度可用它的一个变量k来表示。
###   2. 怎么解决敌机随机产生会有的碰撞问题？
   
  敌机产生时可能出现在同一个位置或者相邻的会互相干扰的位置，会造成一些显示的错乱和判断的凌乱。我的敌机产生主要有两个途径一个是，每隔相应时间产生一个敌机，另外一个是每隔一段时间随机决定是否产生一个敌机。 同时产生的敌机，我检测他们的横坐标是否距离合适，不合适则抹去已经产生的一个冲突的敌机。 不同时产生的敌机为防止他们纵坐标距离过近，我采取每隔几个敌机移动操作产生一次敌机。
###   3. 怎么解决闪屏问题？
   
  利用移动光标，输出，每次更新只是局部更新，比如敌机，旧的位置输出空，新的位置重新绘制。这样消耗的代价比较小，自然就解决了闪屏问题。

###   4. 怎么解决敌机和子弹动态产生动态消失的问题？

   敌机和子弹都属于动态产生动态消失，是比较适合用链表来表示的。但我为了简化程序，同时考虑到用数组可以控制屏幕中出现敌机的最大数目，且操作比较简单。最后采用了一个数组。使用方法如下：每次需要产生一个敌机（子弹），检测已有数组是否有空位置，若有则分配赋值产生，若无则不产生。当敌机（子弹）自然消失到“天尽头”，或者发生碰撞，则置该位置为空，逻辑上删除了该对象。

## 四.程序的功能特点和运行操作方法
   1. 飞机和敌机的形状比较符合认知，较逼真，碰撞的处理比较细节，易于玩家把握击落敌机的位置。
   2.可以进行速度的调整，适合中高级玩家的选择（暂时代码中调整）
   3.可以计分，显示成绩。
   4.有结束画面，可以选择是否继续。
   2. 运行操作方法：
 
	w a s d分别表示飞机的上 左  下 右 的移动，k表示发射子弹。
