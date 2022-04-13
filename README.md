# 演讲比赛系统

模仿B站黑马程序员的需求，自己写了一个相似的系统基本没有参考源码，IO部分因为不熟练是参考了一下，但是因为系统本身比较简单，所以问题也不多，但我觉得对自己后续的学习很有帮助就记录下来了。

## 遇到的问题

### map容器的理解问题

```c++
//this>m_record.insert(pair<int,vector<string>>(0,v));
this->m_record.insert(pair<int, vector<string>>(index, v));
```

在写这句话的时候一直在纠结赋值问题，index为什么只有取0可以，因为作为一个map而言仅仅是不支持重复的Key值，随后在编译过程中将map换成了multimap仍然没有用，后续才发现并不是因为map容器导致的而是因为vector容器在打印函数中超过了数字限制，这个问题会报vector越界的错误其实和matlab的超过数组上限很响，所以在接下来的工程实现中应该多注意**容器边界问题**。

### 迭代器命名问题

总体来说，本项目很多问题都是STL的理解问题，必须继续加强。迭代器问题很有意思是一个很奇怪的bug后面就自己消失了。

```c++
	for (vector<Person>::iterator it1 = v1.begin(); it1 < v1.end();it1++) {
		it1->m_sorce = 60 + rand() % 40;
	}
	for (vector<Person>::iterator it2 = v2.begin(); it2 != v2.end(); it2++) {
		sorce = 60 + rand() % 40;
		it2->m_sorce = sorce;
	}
```

这是一个最简单的迭代器遍历，但是在命名方向报了一个很奇怪的错误，一开始我以为是不允许重复命名导致的但是，迭代器是可以随意命名的后面的代码也证明了这一点，然后我发现是for循环条件中的it名字并不一致，但是我修改一致之后也没有解决，但在我重启第二天打开之后就不报错了非常奇怪。所以总结经验来说就是以**后迭代器命名尽量还是区别大一点，或者自己检查清楚**避免类似的问题发生。

## 和例子对比的不足

### 函数使用类封装

相比于例程，我的代码很多小的功能函数都没有选择封装，这就导致了内部的一些vector容器需要通过引用的方式传递，对于表达式的简洁不利，如果可以将大部分函数封装到一个统一的类里面的话会方便很多，也更美观。

```C++
//我的代码
class filemanager {
public:
	bool file_Isempty;
	void loadfile();
	void showfile();
	void clear();
	map <int, vector<string>> m_record;
};
void start(vector<Person>& v);

void loading();

void savefile(vector<Person>& v);
//例程代码
lass SpeechManager
{
public:

	//构造函数
	SpeechManager();

	//菜单功能
	void show_Menu();

	//退出系统
	void exitSystem();

	//析构函数
	~SpeechManager();

	//初始化容器和属性
	void initSpeech();

	//创建12名选手
	void createSpeaker();

	//开始比赛  比赛整个流程控制函数
	void startSpeech();

	//抽签
	void speechDraw();

	//比赛
	void speechContest();

	//显示得分
	void showScore();

	//保存记录
	void saveRecord();

	//读取记录
	void loadRecord();

	//显示往届记录
	void showRecord();

	//清空文件
	void clearRecord();


	//判断文件是否为空
	bool fileIsEmpty;

	//存放往届记录的容器
	map<int, vector<string>>m_Record;

	//成员属性
	//保存第一轮比赛选手编号容器
	vector<int>v1;

	//第一轮晋级选手编号容器
	vector<int>v2;

	//胜出前三名选手编号容器
	vector<int>vVictory;

	//存放编号以及对应具体选手容器
	map<int, Speaker>m_Speaker;

	//存放比赛轮数 
	int m_Index;

};
```

### 创建类的编程习惯

在创建类的时候，例程会本能的**创建析构函数和构造函数**，而我只会在需要的时候才会写大部分情况下还是只会在需要的时候写构造函数，养成这样的习惯可能会为后续的工程实现带来好处。

```c++
	//构造函数
	SpeechManager();

	//菜单功能
	void show_Menu();

	//退出系统
	void exitSystem();

	//析构函数
	~SpeechManager();
```

### I/O及类的初始化问题

在例程的I/O中会考虑到**各种不同的文件情况包括文件不存在和文件为空**，在参考之前我并没有这样的想法，需要在以后的工程实现中继续多加注意，类的初始化也是相同问题其实大多数情况下不**初始化**也不会带来什么问题，但是良好的编程习惯在大项目面前可能就会省去很多麻烦，毕竟C++的问题定位并不那么人性化，所以在后面的学习中要着重培养工程习惯。

```c++
//构造函数
SpeechManager::SpeechManager()
{
	//初始化容器和属性
	this->initSpeech();

	//创建12名选手
	this->createSpeaker();

	//加载往届记录
	this->loadRecord();
}

void SpeechManager::initSpeech()
{
	//容器都置空
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear();

	//初始化比赛轮数
	this->m_Index = 1;

	//将记录的容器 也清空
	this->m_Record.clear();
}
```



## 个人实现思路

本来是想写一下思路的，但这个系统比较简单就学习一下例程的思路，我觉得在一个项目实现前，将框架写好也是非常关键的，现在正是在过程和面向对象转换的时间，因此在下一个项目中会尝试**先分析需求记录一下框架结构**，再着手进行。