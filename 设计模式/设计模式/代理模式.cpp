#ifdef 代理模式
#include<iostream>
#include<memory>
using namespace std;

class VideoSite
{
public:
	virtual void freeMovie() = 0;
	virtual void vipMovie() = 0;
	virtual void ticketMovie() = 0;
};
class FixBugVideoSite :public VideoSite//委托类
{
public:
	virtual void freeMovie()
	{
		cout << "观看免费电影" << endl;
	}
	virtual void vipMovie()
	{
		cout << "观看VIP电影" << endl;
	}
	virtual void ticketMovie()
	{
		cout << "用卷观看电影" << endl;
	}
};
//代理类
class FreeVideoSiteProxy :public VideoSite
{
public:
	FreeVideoSiteProxy()
	{
		pVideo = new FixBugVideoSite();
	}
	virtual void freeMovie()
	{
		pVideo->freeMovie();
	}
	virtual void vipMovie()
	{
		cout << "您目前只是普通游客，需要升级为vip" << endl;
	}
	virtual void ticketMovie()
	{
		cout << "您目前需要充值" << endl;
	}
	~FreeVideoSiteProxy()
	{
		delete pVideo;
	}
private:
	VideoSite* pVideo;
};
class VipVideoSiteProxy :public VideoSite
{
public:
	VipVideoSiteProxy()
	{
		pVideo = new FixBugVideoSite();
	}
	virtual void freeMovie()
	{
		pVideo->freeMovie();
	}
	virtual void vipMovie()
	{
		pVideo->vipMovie();
	}
	virtual void ticketMovie()
	{
		cout << "您目前需要充值" << endl;
	}
	~VipVideoSiteProxy()
	{
		delete pVideo;
	}
private:
	VideoSite* pVideo;
};
void watchMovie(unique_ptr<VideoSite>& p1)
{
	p1->freeMovie();
	p1->ticketMovie();
	p1->vipMovie();
}
int main()
{
	/*VideoSite* p1 = new FixBugVideoSite();
	p1->freeMovie();
	p1->ticketMovie();
	p1->vipMovie();*/
	unique_ptr<VideoSite>p1(new FreeVideoSiteProxy());
	unique_ptr<VideoSite>p2(new VipVideoSiteProxy());
	watchMovie(p1);
	watchMovie(p2);
	return 0;
}
#endif // 代理模式

