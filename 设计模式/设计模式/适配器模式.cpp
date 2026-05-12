/*
适配器模式：让不兼容的接口可以在一起工作
*/
//#define 适配器模式
#ifdef 适配器模式

#include<iostream>
#include<string>
#include<memory>
using namespace std;
class VGA
{
public:
	virtual void play() = 0;
};
class TV01 :public VGA
{
public:
	void play()
	{
		cout << "通过VGA接口连接投影仪进行视频播放" << endl;
	}
};
class Computer
{
public:
	void playVideo(VGA* pVGA)
	{
		pVGA->play();
	}
};

//进了一批投影仪，但是支持HDMI接口
class HDMI
{
public:
	virtual void play() = 0;
};
class TV02 :public HDMI
{
public:
	void play()
	{
		cout << "通过HDMI接口连接投影仪进行视频播放" << endl;
	}
};
/*
法1：换一个电脑，这里直接改简单，但是实际场景就是代码重构
法2：买一个转换头(适配器)，能够把VGA->HDMI信号

*/
class VGAToHDMIAdapter :public VGA
{
public:
	VGAToHDMIAdapter(HDMI* p)
		:pHdmi(p)
	{

	}
	void play()
	{
		pHdmi->play();
	}
private:
	HDMI* pHdmi;
};
int main()
{
	Computer computer;
	computer.playVideo(new VGAToHDMIAdapter(new TV02()));
	return 0;
}

#endif // 适配器模式

