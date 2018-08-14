#include <windows.h>
#include <tchar.h>
#include "Screen.h"
#include "Object.h"
#include "Camera.h"
#include "Ray.h"
#include <thread>

HINSTANCE g_hInstance = 0;
HANDLE g_hOutput = 0;

int screen_width=601;
int screen_height=601;


Camera MainCamera = Camera(Point(0, -600, 0));
//设置相机位置


void UseThread(HDC hdc,Vector3f buffer[WIN_HIGH][WIN_WIDTH]) {
	std::thread draw_threads[WIN_HIGH*WIN_WIDTH];
	//std::vector<std::thread> drawthreads;
	//std::thread t1(SetPixel, hdc, 10, 10, RGB(200, 200, 200));
	//t1.join();
	for (int i = 0; i < WIN_HIGH; i++) {
		for (int j = 0; j < WIN_WIDTH; j++) {
			draw_threads[i*WIN_WIDTH+j] = std::thread(SetPixel,hdc ,j, i, RGB(ScreenColorBuffer[i][j].x * 255, ScreenColorBuffer[i][j].y * 255, ScreenColorBuffer[i][j].z * 255));
			//SetPixel(hdc, j, i, RGB(ScreenColorBuffer[i][j].x * 255, ScreenColorBuffer[i][j].y * 255, ScreenColorBuffer[i][j].z * 255));
			//draw_threads[i][j] = std::thread(add,1);
		}
	}
	for (int i = 0; i < WIN_HIGH*WIN_WIDTH; i++) draw_threads[i].join();
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); //窗口函数说明

int WINAPI WinMain(HINSTANCE hInstance, //WinMain函数说明
	HINSTANCE hPrevInst,
	LPSTR lpszCmdLine,
	int nCmdShow)
{
	HWND hwnd;
	MSG Msg;
	WNDCLASS wndclass;
	TCHAR lpszClassName[] = _T("window"); //窗口类名
	TCHAR lpszTitle[] = _T("demo"); //窗口标题名
										  //窗口类的定义
	wndclass.style = 0; //窗口类型为缺省类型
	wndclass.lpfnWndProc = WndProc; //窗口处理函数为WndProc
	wndclass.cbClsExtra = 0; //窗口类无扩展
	wndclass.cbWndExtra = 0; //窗口实例无扩展
	wndclass.hInstance = hInstance; //当前实例句柄
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//窗口的最小化图标为缺省图标
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);					//窗口采用箭头光标
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);	//窗口背景为白色
	wndclass.lpszMenuName = NULL;									//窗口中无菜单
	wndclass.lpszClassName = lpszClassName;							//窗口类名为"窗口示例"


	if (!RegisterClass(&wndclass)) //如果注册失败则发出警告声音
	{
		//MessageBeep(0);
		return FALSE;
	}
	//创建窗口
	hwnd = CreateWindow(lpszClassName, //窗口类名
		lpszTitle, //窗口实例的标题名
		WS_OVERLAPPEDWINDOW, //窗口的风格
		CW_USEDEFAULT,
		CW_USEDEFAULT, //窗口左上角坐标为缺省值
		600,
		600, //窗口的高和宽为缺省值
		NULL, //此窗口无父窗口
		NULL, //此窗口无主菜单
		hInstance, //创建此窗口的应用程序的当前句柄
		NULL); //不使用该值
			   //显示窗口
	ShowWindow(hwnd, nCmdShow);
	//绘制用户区
	UpdateWindow(hwnd);
	//消息循环
	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam; //消息循环结束即程序终止时将信息返回系统
}

//窗口函数
LRESULT CALLBACK WndProc(HWND hwnd,
						UINT message,
						WPARAM wParam,
						LPARAM lParam)
{
	HDC hdc; // 定义指向设备的句柄
	HPEN hPen; // 定义指向画笔的句柄
	PAINTSTRUCT PtStr; //定义指向包含绘图信息的结构体变量

	//vector<double> zBuffer;
	//初始化摄像机
	MainCamera.lookat(0, 0, 0, 0, 0, 1);
	MainCamera.GetPixelPos();


	switch (message) {
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &PtStr);
		hPen = (HPEN)GetStockObject(WHITE_PEN); // 黑色画笔
		SelectObject(hdc, hPen); // 选择画笔
		

		//首先初始化场景
		SetObject(Vector3f(0,0,0),100, Vector3f(0.f,0.74f,1.f));
		SetObject(Vector3f(0, 0, -10000), 9900 , Vector3f(0.254f,0.411f,1.f));
		//初始化背景
		InitScreen();

		//开始扫描，传入每个像素的坐标和相机坐标
		Ray::scanScreen(MainCamera, ScreenColorBuffer, THREE_SAMPLE);		

		//投影到屏幕
		for (int i = 0; i < WIN_HIGH; i++) {
			for (int j = 0; j < WIN_WIDTH; j++) {
				SetPixel(hdc, j, i, RGB(ScreenColorBuffer[i][j].x *255, ScreenColorBuffer[i][j].y*255, ScreenColorBuffer[i][j].z*255));
				//实际上 数组的排列和窗体像素的坐标是一致的所以不用交换
			}
		}
		//UseThread(hdc, ScreenColorBuffer);

		//此处日后使用多线程绘制

		EndPaint(hwnd, &PtStr); // 结束绘图
		break;
	case WM_DESTROY:
		PostQuitMessage(0); //调用PostQuitMessage发出WM_QUIT消息
		break;
	default: //缺省时采用系统消息缺省处理函
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return (0);
}

