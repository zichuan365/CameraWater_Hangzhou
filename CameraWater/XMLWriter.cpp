#include "XMLWriter.h"

//void XMLWriter::WriteStereoPara(std::string filename, const CamPara& camLPara, const CamPara& camRPara, const struct RT& relativeRT, const Size imgSize)
//{
//	char text[100];		//用于把文本写到文件中的临时字符串
//	char* segmentation = " ";		//文本内容之间的分隔符
//	TiXmlDocument doc;		//新建一个xml文本类
//	TiXmlDeclaration *decl = new TiXmlDeclaration("1.0", "", "");		//xml文件第一行的声明部分，必须要有的
//	doc.LinkEndChild(decl);		//把声明decl放到文本doc的末尾

//	//*************插入左相机元素******************//

//	TiXmlElement *Stero_Paras_root = new TiXmlElement("StereoParas");
//	doc.LinkEndChild(Stero_Paras_root);

//	//先把xml文件的元素名称写好

//	TiXmlElement *camLParas = new TiXmlElement("CamL_Intrinsic_Parameters");
//	Stero_Paras_root->LinkEndChild(camLParas);		//左相机内参元素名称

//	TiXmlElement *fc_element = new TiXmlElement("fc");
//	camLParas->LinkEndChild(fc_element);		//fc元素

//	TiXmlElement *cc_element = new TiXmlElement("cc");
//	camLParas->LinkEndChild(cc_element);		//cc元素

//	TiXmlElement *distL_element = new TiXmlElement("CamL_Distortion");
//	Stero_Paras_root->LinkEndChild(distL_element);

//	TiXmlElement *kc_element1 = new TiXmlElement("kc");
//	distL_element->LinkEndChild(kc_element1);

//	//对左相机元素添加内容
//	sprintf(text, "%.9f%s%.9f", camLPara.CameraIntrinsic[0][0], segmentation, camLPara.CameraIntrinsic[1][1]);
//	TiXmlText *fc_text1 = new TiXmlText(text);
//	fc_element->LinkEndChild(fc_text1);		//CamL  fc

//	sprintf(text, "%.9f%s%.9f", camLPara.CameraIntrinsic[0][2], segmentation, camLPara.CameraIntrinsic[1][2]);
//	TiXmlText *cc_text1 = new TiXmlText(text);
//	cc_element->LinkEndChild(cc_text1);		//CamL cc

//	sprintf(text, "%.9f%s%.9f%s%.9f%s%.9f", camLPara.DistortionCoeffs[0], segmentation,
//		camLPara.DistortionCoeffs[1], segmentation, camLPara.DistortionCoeffs[2], segmentation, camLPara.DistortionCoeffs[3]);
//	TiXmlText *distL_text = new TiXmlText(text);
//	kc_element1->LinkEndChild(distL_text);		//DistortionL


//	//*************右相机元素************//
//	TiXmlElement *camRParas = new TiXmlElement("CamR_Intrinsic_Parameters");
//	Stero_Paras_root->LinkEndChild(camRParas);

//	TiXmlElement *fc_element2 = new TiXmlElement("fc");
//	camRParas->LinkEndChild(fc_element2);

//	TiXmlElement *cc_element2 = new TiXmlElement("cc");
//	camRParas->LinkEndChild(cc_element2);

//	TiXmlElement *distR_element = new TiXmlElement("CamR_Distortion");
//	Stero_Paras_root->LinkEndChild(distR_element);

//	TiXmlElement *kc_element2 = new TiXmlElement("kc");
//	distR_element->LinkEndChild(kc_element2);

//	//对右相机元素添加内容
//	sprintf(text, "%.9f%s%.9f", camRPara.CameraIntrinsic[0][0], segmentation, camRPara.CameraIntrinsic[1][1]);
//	TiXmlText *fc_text2 = new TiXmlText(text);
//	fc_element2->LinkEndChild(fc_text2);		//CamR  fc

//	sprintf(text, "%.9f%s%.9f", camRPara.CameraIntrinsic[0][2], segmentation, camRPara.CameraIntrinsic[1][2]);
//	TiXmlText *cc_text2 = new TiXmlText(text);
//	cc_element2->LinkEndChild(cc_text2);		//CamR cc

//	sprintf(text, "%.9f%s%.9f%s%.9f%s%.9f", camRPara.DistortionCoeffs[0], segmentation,
//		camRPara.DistortionCoeffs[1], segmentation, camRPara.DistortionCoeffs[2], segmentation, camRPara.DistortionCoeffs[3]);
//	TiXmlText *distR_text = new TiXmlText(text);
//	kc_element2->LinkEndChild(distR_text);		//DistortionR

//	//*****************插入两相机相对位姿元素**********************//
//	TiXmlElement *RT_element = new TiXmlElement("RT_Parameter");
//	Stero_Paras_root->LinkEndChild(RT_element);

//	TiXmlElement *R_element = new TiXmlElement("R");
//	RT_element->LinkEndChild(R_element);

//	TiXmlElement *T_element = new TiXmlElement("T");
//	RT_element->LinkEndChild(T_element);


//	//添加RT内容
//	sprintf(text, "%.9f%s%.9f%s%.9f", relativeRT.R.at<double>(0, 0), segmentation, relativeRT.R.at<double>(1, 0), segmentation, relativeRT.R.at<double>(2, 0));
//	TiXmlText *R_text = new TiXmlText(text);
//	R_element->LinkEndChild(R_text);		//R


//	//test
//	//double x1 = relativeRT.T.at<double>(0, 0);
//	//double x2 = relativeRT.T.at<double>(1, 0);
//	//double x3 = relativeRT.T.at<double>(2, 0);
//	//test

//	sprintf(text, "%.9f%s%.9f%s%.9f", relativeRT.T.at<double>(0, 0), segmentation, relativeRT.T.at<double>(1, 0), segmentation, relativeRT.T.at<double>(2, 0));
//	TiXmlText *T_text = new TiXmlText(text);
//	T_element->LinkEndChild(T_text);		//T

//	//*************添加图像尺寸元素******************//
//	TiXmlElement* size_element = new TiXmlElement("Image_Size");
//	Stero_Paras_root->LinkEndChild(size_element);

//	//添加图像尺寸内容
//	sprintf(text, "%d%s%d", imgSize.width, segmentation, imgSize.height);
//	TiXmlText* size_text = new TiXmlText(text);
//	size_element->LinkEndChild(size_text);

//	doc.SaveFile(filename.c_str());
//}

////保存两点坐标--------庄磊磊
//void XMLWriter::WritePoints(std::string filename, vector<Point>& points)
//{
//	char text[1000];
//	char* segmentation = " ";
//	TiXmlDocument doc;
//	TiXmlDeclaration * decl = new TiXmlDeclaration("1.0", "", "");
//	doc.LinkEndChild(decl);

//	TiXmlElement * root_element = new TiXmlElement("Points");
//	root_element->SetAttribute("size", points.size());
//	doc.LinkEndChild(root_element);

//	for (int i = 0; i < points.size(); ++i)
//	{
//		sprintf(text, "%s%d", "Point", i);
//		TiXmlElement *index_element = new TiXmlElement(text);
//		root_element->LinkEndChild(index_element);

//		sprintf(text, "%d%s%d", points[i].x, segmentation, points[i].y);
//		TiXmlText * P_text = new TiXmlText(text);
//		index_element->LinkEndChild(P_text);
//	}

//	doc.SaveFile(filename.c_str());

//}

//#if 0

//void XMLWriter::Write3DdetectSetingParams(const std::string &filename, const detectorParams &DetectorParams,const vector <detectObjParams> &DetectObjsParams)
//{
//	char text[1000];
//	char* seg = " ";
//	TiXmlDocument doc;
//	TiXmlDeclaration * decl = new TiXmlDeclaration("1.0", "", "");
//	doc.LinkEndChild(decl);
	
//	TiXmlElement * root_element = new TiXmlElement("DetectParams3D");
//	doc.LinkEndChild(root_element);
//	//识别器参数
//	TiXmlElement *detector = new TiXmlElement("DetectorParams");
//	root_element->LinkEndChild(detector);

//	sprintf(text, "%d%s%f%s%f", DetectorParams.smoothKNN, seg, DetectorParams.downSampleRatio, seg, DetectorParams.keypointerRatio);
//	TiXmlText *paramValue = new TiXmlText(text);
//	detector->LinkEndChild(paramValue);

//	//识别对象参数
//	TiXmlElement *detectObjs = new TiXmlElement("DetectObjectParams");
//	root_element->LinkEndChild(detectObjs);

//	for (int i = 0; i < DetectObjsParams.size(); i++)
//	{
//		TiXmlElement *detectObject = new TiXmlElement(DetectObjsParams[i].ObjectName.c_str());
//		detectObjs->LinkEndChild(detectObject);
//		sprintf(text, "%s%s%f%s%d", DetectObjsParams[i].ShowColor.c_str(), seg, DetectObjsParams[i].minScore, seg, DetectObjsParams[i].mlsOrder);
//		TiXmlText *paramValue = new TiXmlText(text);
//		detectObject->LinkEndChild(paramValue);
//	}
//	doc.SaveFile(filename.c_str());
//}

//void XMLWriter::Write3DdetectResult(const std::string &filename, const ObjectsDetect3D &detector)
//{
//	//待写
//	char text[1000];
//	char* seg = " ";
//	TiXmlDocument doc;
//	TiXmlDeclaration * decl = new TiXmlDeclaration("1.0", "", "");
//	doc.LinkEndChild(decl);
//	TiXmlElement * root_element = new TiXmlElement("DetectResult3D");
//	doc.LinkEndChild(root_element);

//	for (int i = 0; i < detector.detectObjects.size();i++)
//	{
//		TiXmlElement *detObj = new TiXmlElement(detector.detectObjects[i].DetectObjParams.ObjectName.c_str());
//		root_element->LinkEndChild(detObj);
//		for (int j = 0; j < detector.detectObjects[i].hv_Score.Length(); j++)
//		{
//			sprintf(text, "%s%d", "Part_", j);
//			TiXmlElement *detResult = new TiXmlElement(text);
//			detObj->LinkEndChild(detResult);
//			TiXmlElement *score = new TiXmlElement("Priority");
//			detResult->LinkEndChild(score);
//			sprintf(text, "%f", detector.detectObjects[i].hv_Score[j].D());
//			TiXmlText *_value = new TiXmlText(text);
//			score->LinkEndChild(_value);
//			TiXmlElement *pose = new TiXmlElement("PoseInWord");
//			detResult->LinkEndChild(pose);
//			//将位子向量转化成3*4矩阵
//			HTuple hv_pose44;
//			PoseToHomMat3d(detector.detectObjects[i].hv_Pose[j], &hv_pose44);
//			sprintf(text, "%f%s%f%s%f%s%f%s%f%s%f%s%f%s%f%s%f%s%f%s%f%s%f",
//				hv_pose44[0].D(), seg, hv_pose44[1].D(), seg, hv_pose44[2].D(), seg, hv_pose44[3].D(),
//				seg, hv_pose44[4].D(), seg, hv_pose44[5].D(), seg, hv_pose44[6].D(), seg, hv_pose44[7].D(),
//				seg, hv_pose44[8].D(), seg, hv_pose44[9].D(), seg, hv_pose44[10].D(), seg, hv_pose44[11].D());
//			_value = new TiXmlText(text);
//			pose->LinkEndChild(_value);
//		}
//		doc.SaveFile(filename.c_str());
//	}
//}

//#endif

//void XMLWriter::WriteLineParams(std::string filename, cv::Point3f dir, cv::Point3f pointInAxis)
//{
//	char text[1000];
//	char* segmentation = " ";
//	TiXmlDocument doc;
//	TiXmlDeclaration * decl = new TiXmlDeclaration("1.0", "", "");
//	doc.LinkEndChild(decl);

//	TiXmlElement * root_element = new TiXmlElement("LineParams");
//	doc.LinkEndChild(root_element);

//	sprintf(text, "%s", "Direction");
//	TiXmlElement *index_element1 = new TiXmlElement(text);
//	root_element->LinkEndChild(index_element1);

//	sprintf(text, "%f%s%f%s%f", dir.x, segmentation, dir.y, segmentation, dir.z);
//	TiXmlText * D_text = new TiXmlText(text);
//	index_element1->LinkEndChild(D_text);

//	sprintf(text, "%s", "Point");
//	TiXmlElement *index_element2 = new TiXmlElement(text);
//	root_element->LinkEndChild(index_element2);

//	sprintf(text, "%f%s%f%s%f", pointInAxis.x, segmentation, pointInAxis.y, segmentation, pointInAxis.z);
//	TiXmlText * P_text = new TiXmlText(text);
//	index_element2->LinkEndChild(P_text);

//	doc.SaveFile(filename.c_str());
//}

//void XMLWriter::WriteCamParams(std::string filename, float shutter, float gain)
//{
//	char text[1000];
//	char* segmentation = " ";
//	TiXmlDocument doc;
//	TiXmlDeclaration * decl = new TiXmlDeclaration("1.0", "", "");
//	doc.LinkEndChild(decl);

//	TiXmlElement * root_element = new TiXmlElement("Params");
//	root_element->SetAttribute("num", 2);
//	doc.LinkEndChild(root_element);

//	sprintf(text, "%s", "Shutter");
//	TiXmlElement *index_element = new TiXmlElement(text);
//	root_element->LinkEndChild(index_element);

//	sprintf(text, "%f", shutter);
//	TiXmlText * P_text = new TiXmlText(text);
//	index_element->LinkEndChild(P_text);

//	sprintf(text, "%s", "Gain");
//	index_element = new TiXmlElement(text);
//	root_element->LinkEndChild(index_element);

//	sprintf(text, "%f", gain);
//	P_text = new TiXmlText(text);
//	index_element->LinkEndChild(P_text);

//	doc.SaveFile(filename.c_str());
//	return;
//}

//void XMLWriter::WriteMotorParams(std::string filename, float speed,float distance)
//{
//	char text[1000];
//	char* segmentation = " ";
//	TiXmlDocument doc;
//	TiXmlDeclaration * decl = new TiXmlDeclaration("1.0", "", "");
//	doc.LinkEndChild(decl);

//	TiXmlElement * root_element = new TiXmlElement("Params");
//	root_element->SetAttribute("num", 1);
//	doc.LinkEndChild(root_element);

//	sprintf(text, "%s", "Speed");
//	TiXmlElement *index_element = new TiXmlElement(text);
//	root_element->LinkEndChild(index_element);

//	sprintf(text, "%f", speed);
//	TiXmlText * P_text = new TiXmlText(text);
//	index_element->LinkEndChild(P_text);

//	sprintf(text, "%s", "Distance");
//	index_element = new TiXmlElement(text);
//	root_element->LinkEndChild(index_element);

//	sprintf(text, "%f", distance);
//	P_text = new TiXmlText(text);
//	index_element->LinkEndChild(P_text);

//	doc.SaveFile(filename.c_str());
//	return;
//}

//void XMLWriter::WriteLaserDetectParams(std::string filename,  int thre, int windowWidth, int centerRange, int groThre)
//{
//	char text[1000];
//	char* segmentation = " ";
//	TiXmlDocument doc;
//	TiXmlDeclaration * decl = new TiXmlDeclaration("1.0", "", "");
//	doc.LinkEndChild(decl);

//	TiXmlElement * root_element = new TiXmlElement("Params");
//	root_element->SetAttribute("num", 1);
//	doc.LinkEndChild(root_element);

//	sprintf(text, "%s", "Thresh");
//	TiXmlElement *index_element = new TiXmlElement(text);
//	root_element->LinkEndChild(index_element);

//	sprintf(text, "%d", thre);
//	TiXmlText * P_text = new TiXmlText(text);
//	index_element->LinkEndChild(P_text);

//	sprintf(text, "%s", "WindowWidth");
//	index_element = new TiXmlElement(text);
//	root_element->LinkEndChild(index_element);

//	sprintf(text, "%d", windowWidth);
//	P_text = new TiXmlText(text);
//	index_element->LinkEndChild(P_text);

//	sprintf(text, "%s", "CenterRange");
//	index_element = new TiXmlElement(text);
//	root_element->LinkEndChild(index_element);

//	sprintf(text, "%d", centerRange);
//	P_text = new TiXmlText(text);
//	index_element->LinkEndChild(P_text);

//	sprintf(text, "%s", "GroThresh");
//	index_element = new TiXmlElement(text);
//	root_element->LinkEndChild(index_element);

//	sprintf(text, "%d", groThre);
//	P_text = new TiXmlText(text);
//	index_element->LinkEndChild(P_text);

//	doc.SaveFile(filename.c_str());
//	return;
//}

void XMLWriter::WriteLaserSystemConfig(std::string filename, int& imgSize)
{
	char text[1000];
//	char* segmentation = " ";
	TiXmlDocument doc;
    //版本号
	TiXmlDeclaration * decl = new TiXmlDeclaration("1.0", "", "");
	doc.LinkEndChild(decl);

    //父
	TiXmlElement * root_element = new TiXmlElement("Params");
    root_element->SetAttribute("num", 1);
	doc.LinkEndChild(root_element);


        //子1,只有一个元素
        //先保存Arduino、Motor ID
        sprintf(text, "%s", "ImageSize");
        TiXmlElement *index_element = new TiXmlElement(text);
        root_element->LinkEndChild(index_element);
        sprintf(text, "%d", imgSize);
        TiXmlText * P_text = new TiXmlText(text);
        index_element->LinkEndChild(P_text);

	doc.SaveFile(filename.c_str());
	return;
}

