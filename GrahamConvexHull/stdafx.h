
// stdafx.h : �W���̃V�X�e�� �C���N���[�h �t�@�C���̃C���N���[�h �t�@�C���A�܂���
// �Q�Ɖ񐔂������A�����܂�ύX����Ȃ��A�v���W�F�N�g��p�̃C���N���[�h �t�@�C��
// ���L�q���܂��B
//

#pragma once
#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include "targetver.h"
#include <stdio.h>
#include <tchar.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <fstream>
#include <time.h>
#include <math.h>
#include <opencv2/opencv.hpp>
//#include <opencv2/nonfree/nonfree.hpp>
using namespace std;
using namespace cv;

#ifdef _DEBUG
//Debug���[�h�̏ꍇ
#pragma comment(lib,"C:\\opencv248\\build\\x86\\vc12\\lib\\opencv_core248d.lib")		// opencv_core
#pragma comment(lib,"C:\\opencv248\\build\\x86\\vc12\\lib\\opencv_imgproc248d.lib")		// opencv_imgproc
#pragma comment(lib,"C:\\opencv248\\build\\x86\\vc12\\lib\\opencv_highgui248d.lib")		// opencv_highgui
#pragma comment(lib,"C:\\opencv248\\build\\x86\\vc12\\lib\\opencv_objdetect248d.lib")	// opencv_objdetect
//�ȉ��A�K�v�ɉ����Ēǉ�
#pragma comment(lib,"C:\\opencv248\\build\\x86\\vc12\\lib\\opencv_ml248d.lib")			// opencv_ml
#pragma comment(lib,"C:\\opencv248\\build\\x86\\vc12\\lib\\opencv_features2d248d.lib")	// opencv_features2d
#pragma comment(lib,"C:\\opencv248\\build\\x86\\vc12\\lib\\opencv_video248d.lib")		// opencv_video
#pragma comment(lib,"C:\\opencv248\\build\\x86\\vc12\\lib\\opencv_calib3d248d.lib")		// opencv_calib3d
#pragma comment(lib,"C:\\opencv248\\build\\x86\\vc12\\lib\\opencv_flann248d.lib")		// opencv_flann
#pragma comment(lib,"C:\\opencv248\\build\\x86\\vc12\\lib\\opencv_contrib248d.lib")		// opencv_contrib
#pragma comment(lib,"C:\\opencv248\\build\\x86\\vc12\\lib\\opencv_legacy248d.lib")		// opencv_legacy
#pragma comment(lib,"C:\\opencv248\\build\\x86\\vc12\\lib\\opencv_gpu248d.lib")			// opencv_gpu
#else
//Release���[�h�̏ꍇ
#pragma comment(lib,"C:\\opencv248\\build\\x86\\vc12\\lib\\opencv_core248.lib")			// opencv_core
#pragma comment(lib,"C:\\opencv248\\build\\x86\\vc12\\lib\\opencv_imgproc248.lib")		// opencv_imgproc
#pragma comment(lib,"C:\\opencv248\\build\\x86\\vc12\\lib\\opencv_highgui248.lib")		// opencv_highgui
#pragma comment(lib,"C:\\opencv248\\build\\x86\\vc12\\lib\\opencv_objdetect248.lib")	// opencv_objdetect
//�ȉ��A�K�v�ɉ����Ēǉ�
#pragma comment(lib,"C:\\opencv248\\build\\x86\\vc12\\lib\\opencv_ml248.lib")			// opencv_ml
#pragma comment(lib,"C:\\opencv248\\build\\x86\\vc12\\lib\\opencv_features2d248.lib")	// opencv_features2d
#pragma comment(lib,"C:\\opencv248\\build\\x86\\vc12\\lib\\opencv_video248.lib")		// opencv_video
#pragma comment(lib,"C:\\opencv248\\build\\x86\\vc12\\lib\\opencv_calib3d248.lib")		// opencv_calib3d
#pragma comment(lib,"C:\\opencv248\\build\\x86\\vc12\\lib\\opencv_flann248.lib")		// opencv_flann
#pragma comment(lib,"C:\\opencv248\\build\\x86\\vc12\\lib\\opencv_contrib248.lib")		// opencv_contrib
#pragma comment(lib,"C:\\opencv248\\build\\x86\\vc12\\lib\\opencv_legacy248.lib") 		// opencv_legacy
#pragma comment(lib,"C:\\opencv248\\build\\x86\\vc12\\lib\\opencv_gpu248.lib")			// opencv_gpu
#endif
