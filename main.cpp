#include <windows.h>
#include <tchar.h>
#include "Screen.h"
#include "Object.h"
#include "Camera.h"
#include "Ray.h"

HINSTANCE g_hInstance = 0;
HANDLE g_hOutput = 0;

int screen_width=601;
int screen_height=601;


Camera MainCamera = Camera(Point(0, -600, 0));


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); //���ں���˵��

int WINAPI WinMain(HINSTANCE hInstance, //WinMain����˵��
	HINSTANCE hPrevInst,
	LPSTR lpszCmdLine,
	int nCmdShow)
{
	HWND hwnd;
	MSG Msg;
	WNDCLASS wndclass;
	TCHAR lpszClassName[] = _T("window"); //��������
	TCHAR lpszTitle[] = _T("demo"); //���ڱ�����
										  //������Ķ���
	wndclass.style = 0; //��������Ϊȱʡ����
	wndclass.lpfnWndProc = WndProc; //���ڴ�������ΪWndProc
	wndclass.cbClsExtra = 0; //����������չ
	wndclass.cbWndExtra = 0; //����ʵ������չ
	wndclass.hInstance = hInstance; //��ǰʵ�����
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//���ڵ���С��ͼ��Ϊȱʡͼ��
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);					//���ڲ��ü�ͷ���
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);	//���ڱ���Ϊ��ɫ
	wndclass.lpszMenuName = NULL;									//�������޲˵�
	wndclass.lpszClassName = lpszClassName;							//��������Ϊ"����ʾ��"


	if (!RegisterClass(&wndclass)) //���ע��ʧ���򷢳���������
	{
		//MessageBeep(0);
		return FALSE;
	}
	//��������
	hwnd = CreateWindow(lpszClassName, //��������
		lpszTitle, //����ʵ���ı�����
		WS_OVERLAPPEDWINDOW, //���ڵķ��
		CW_USEDEFAULT,
		CW_USEDEFAULT, //�������Ͻ�����Ϊȱʡֵ
		600,
		600, //���ڵĸߺͿ�Ϊȱʡֵ
		NULL, //�˴����޸�����
		NULL, //�˴��������˵�
		hInstance, //�����˴��ڵ�Ӧ�ó���ĵ�ǰ���
		NULL); //��ʹ�ø�ֵ
			   //��ʾ����
	ShowWindow(hwnd, nCmdShow);
	//�����û���
	UpdateWindow(hwnd);
	//��Ϣѭ��
	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam; //��Ϣѭ��������������ֹʱ����Ϣ����ϵͳ
}

//���ں���
LRESULT CALLBACK WndProc(HWND hwnd,
						UINT message,
						WPARAM wParam,
						LPARAM lParam)
{
	HDC hdc; // ����ָ���豸�ľ��
	HPEN hPen; // ����ָ�򻭱ʵľ��
	PAINTSTRUCT PtStr; //����ָ�������ͼ��Ϣ�Ľṹ�����

	//vector<double> zBuffer;
	//��ʼ�������
	MainCamera.lookat(0, 0, 0, 0, 0, 1);
	MainCamera.GetPixelPos(ONE_SAMPLE);

	switch (message) {
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &PtStr);
		hPen = (HPEN)GetStockObject(WHITE_PEN); // ��ɫ����
		SelectObject(hdc, hPen); // ѡ�񻭱�
		

		//���ȳ�ʼ������
		SetObject(Vector3f(0,0,0),100);
		//��ʼ������
		InitScreen();

		//��ʼɨ�裬����ÿ�����ص�������������
		Ray::scanScreen(MainCamera, ScreenColorBuffer);

		//����
		Buffer2RealScreen();
		

		//ͶӰ����Ļ
		for (int i = 0; i < WIN_HIGH; i++) {
			for (int j = 0; j < WIN_WIDTH; j++) {
				SetPixel(hdc, j, i, RGB(ScreenColorBuffer[i][j].x *255, ScreenColorBuffer[i][j].y*255, ScreenColorBuffer[i][j].z*255));
			}
		}

		//�˴��պ�ʹ�ö��̻߳���

		EndPaint(hwnd, &PtStr); // ������ͼ
		break;
	case WM_DESTROY:
		PostQuitMessage(0); //����PostQuitMessage����WM_QUIT��Ϣ
		break;
	default: //ȱʡʱ����ϵͳ��Ϣȱʡ������
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return (0);
}
