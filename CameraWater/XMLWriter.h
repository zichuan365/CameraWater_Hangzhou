#pragma once
#include "./TinyXML/tinyxml.h"
#include "./TinyXML/tinystr.h"
#include <iostream>
//#include "DataType.h"
//#include "3D Recognition/ObjectsDetect3D.h"

//使用TinyXML
class XMLWriter
{
public:
	XMLWriter(){  }

//	//************************************庄磊磊***********************************//
//	//保存立体标定参数
//	static void WriteStereoPara(std::string filename, const CamPara& camLPara, const CamPara& camRPara, const struct RT& relativeRT,const Size imgSize);
//	//保存两点坐标
//	static void WritePoints(std::string filename,vector<Point>& points);
//	//保存直线参数 直线方向向量和直线上一点
//	static void WriteLineParams(std::string filename, cv::Point3f dir, cv::Point3f pointInAxis);
//	//保存相机拍摄参数
//	static void WriteCamParams(std::string filename, float shutter, float gain);
//	//保存电机扫描参数
//	static void WriteMotorParams(std::string filename, float speed,float distance);
//	//保存条纹中心提取参数
//	static void WriteLaserDetectParams(std::string filename, int thre, int windowWidth, int centerRange, int groThre);
	//保存双目扫描系统配置参数
    static void WriteLaserSystemConfig(std::string filename,int& imgNums);
	//保存激光条纹提取参数
	//static void WriteLaserDetectParams(std::string filename)


};

