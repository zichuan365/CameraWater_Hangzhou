#include "xmlreader.h"

//bool XMLReader::ReadStereoPara(std::string filename, CamPara& camLPara, CamPara& camRPara, struct RT& relativeRT, Size& imgSize)
//{
//	//加载文件
//	TiXmlDocument doc;
//	if (!doc.LoadFile(filename.c_str()))
//	{
//		return false;
//	}
//	TiXmlHandle hDoc(&doc);

//	if (!parseCamLIntrinsicparametersElement(hDoc, camLPara))
//	{
//		return false;
//	}

//	if (!parseCamRIntrinsicparametersElement(hDoc, camRPara))
//	{
//		return false;
//	}

//	if (!parseCamLDistortionsElement(hDoc, camLPara))
//	{
//		return false;
//	}

//	if (!parseCamRDistortionsElement(hDoc, camRPara))
//	{
//		return false;
//	}

//	if (!parseRTElement(hDoc, relativeRT))
//	{
//		return false;
//	}

//	if (!parseStereoParaSize(hDoc, imgSize))
//	{
//		return false;
//	}

//	return true;
//}
//bool XMLReader::readCamPara(std::string filename, CamPara& m_camPara)
//{
//	//加载文件
//	TiXmlDocument doc;
//	if (!doc.LoadFile(filename.c_str()))
//	{
//		return false;
//	}
//	TiXmlHandle hDoc(&doc);

//	if (!parseIntrinsicparametersElement(hDoc, m_camPara))
//		return false;
//	if (!parseDistortionsElement(hDoc, m_camPara))
//		return false;
//	if (!parseImageRTElement(hDoc, m_camPara))
//		return false;

//	return true;
//}
//bool XMLReader::parseIntrinsicparametersElement(TiXmlHandle hDoc, CamPara& m_camPara)
//{
//	char* segmentation = " ";
//	TiXmlElement* pElem;
//	pElem = hDoc.FirstChild("Intrinsic_parameters").Element();
//	if (pElem->ValueTStr() == "Intrinsic_parameters")
//	{
//		TiXmlElement* tElem;
//		tElem = pElem->FirstChild("fc")->ToElement();
//		if (tElem->ValueTStr() == "fc")
//		{
//			std::vector<std::string> nums = SharedMethod::mySplit(tElem->GetText(), segmentation);
//			float fc0, fc1;
//			sscanf(nums[0].c_str(), "%f", &fc0);
//			sscanf(nums[1].c_str(), "%f", &fc1);
//			m_camPara.CameraIntrinsic[0][0] = fc0;
//			m_camPara.CameraIntrinsic[1][1] = fc1;
//		}
//		tElem = pElem->FirstChild("cc")->ToElement();
//		if (tElem->ValueTStr() == "cc")
//		{
//			std::vector<std::string> nums = SharedMethod::mySplit(tElem->GetText(), segmentation);
//			float cc0, cc1;
//			sscanf(nums[0].c_str(), "%f", &cc0);
//			sscanf(nums[1].c_str(), "%f", &cc1);
//			m_camPara.CameraIntrinsic[0][2] = cc0;
//			m_camPara.CameraIntrinsic[1][2] = cc1;
//		}
//	}
//	else
//	{
//		return false;
//	}

//	return true;
//}

//bool XMLReader::parseDistortionsElement(TiXmlHandle hDoc, CamPara& m_camPara)
//{
//	char* segmentation = " ";
//	TiXmlElement* pElem;
//	pElem = hDoc.FirstChild("Distortions").Element();
//	if (pElem->ValueTStr() == "Distortions")
//	{
//		TiXmlElement* tElem;
//		tElem = pElem->FirstChild("kc")->ToElement();
//		if (tElem->ValueTStr() == "kc")
//		{
//			std::vector<std::string> nums = SharedMethod::mySplit(tElem->GetText(), segmentation);
//			float kc[5];
//			for (int i = 0; i < 5; i++)
//			{
//				sscanf(nums[i].c_str(), "%f", &kc[i]);
//				m_camPara.DistortionCoeffs[i] = kc[i];
//			}
//		}
//	}
//	else
//	{
//		return false;
//	}

//	return true;
//}

//bool XMLReader::parseImageRTElement(TiXmlHandle hDoc, CamPara& m_camPara)
//{
//	char* segmentation = " ";
//	TiXmlElement* pElem;
//	pElem = hDoc.FirstChild("Image_RT").Element();
//	if (pElem->ValueTStr() == "Image_RT")
//	{
//		int num = pElem->FirstAttribute()->IntValue();
//		TiXmlElement* tElem;
//		tElem = pElem->FirstChild()->ToElement();
//		for (int i = 0; i < num; i++)
//		{
//			RT rt; rt.R = Mat(3, 1, CV_64F); rt.T = Mat(3, 1, CV_64F);
//			TiXmlElement* _tElem;
//			_tElem = tElem->FirstChild()->ToElement();
//			for (_tElem; _tElem; _tElem = _tElem->NextSiblingElement())
//			{
//				std::vector<std::string> nums = SharedMethod::mySplit(_tElem->GetText(), segmentation);
//				float vec[3];
//				for (int j = 0; j < 3; j++)
//				{
//					sscanf(nums[j].c_str(), "%f", &vec[j]);
//					if (_tElem->ValueTStr() == "R")
//						rt.R.at<double>(j, 0) = vec[j];
//					else if (_tElem->ValueTStr() == "T")
//						rt.T.at<double>(j, 0) = vec[j];
//					else
//						break;
//				}
//			}
//			m_camPara.imgRTVec.push_back(rt);
//			tElem = tElem->NextSiblingElement();
//		}
//	}
//	else
//	{
//		return false;
//	}

//	return true;
//}

//bool XMLReader::ReadPoints(std::string filename, vector<Point>& points)
//{
//	//加载文件
//	TiXmlDocument doc;
//	if (!doc.LoadFile(filename.c_str()))
//	{
//		return false;
//	}
//	TiXmlHandle hDoc(&doc);

//	if (!parsePoints(hDoc, points))
//	{
//		return false;
//	}
//	return true;
//}

//#if 0

//bool XMLReader::Read3DdetectSetingParams( std::string filename, detectorParams &DetectorParams, vector <detectObjParams> &DetectObjsParams)
//{
//	char* seg = " ";
//	TiXmlDocument doc;
//	if (!doc.LoadFile(filename.c_str()))
//	{
//		string str = doc.ErrorDesc();
//		return false;
//	}
//	TiXmlHandle hDoc(&doc);
//	if (!parseDetectorParams(hDoc,DetectorParams))
//	{
//		return false;
//	}
//	if (!parseDetectObjParams(hDoc,DetectObjsParams))
//	{
//		return false;
//	}
//	return true;

//}

//#endif
////
////bool XMLReader::Read3DdetectSetingParams(const std::string filename, ObjectsDetect3D &ObjsDetect3D)
////{
////	detectorParams DetectorParams;
////	vector <detectObjParams> DetectObjsParams;
////	if (Read3DdetectSetingParams(filename, DetectorParams, DetectObjsParams))
////	{
////		for (int i = 0; )
////		{
////		}
////	}
////	else
////		return false;
////
////}

//bool XMLReader::parseCamLIntrinsicparametersElement(TiXmlHandle hDoc, CamPara& camPara)
//{
//	char* segmentation = " ";

//	TiXmlElement* rElem;
//	rElem = hDoc.FirstChild("StereoParas").Element();
//	if (rElem->ValueTStr() == "StereoParas")
//	{

//		TiXmlElement* pElem;
//		pElem = rElem->FirstChild("CamL_Intrinsic_Parameters")->ToElement();
//		if (pElem->ValueTStr() == "CamL_Intrinsic_Parameters")
//		{
//			TiXmlElement* tElem;
//			tElem = pElem->FirstChild("fc")->ToElement();
//			if (tElem->ValueTStr() == "fc")
//			{
//				std::vector<std::string> nums = SharedMethod::mySplit(tElem->GetText(), segmentation);
//				float fc0, fc1;
//				sscanf(nums[0].c_str(), "%f", &fc0);
//				sscanf(nums[1].c_str(), "%f", &fc1);
//				camPara.CameraIntrinsic[0][0] = fc0;
//				camPara.CameraIntrinsic[1][1] = fc1;
//			}
//			tElem = pElem->FirstChild("cc")->ToElement();
//			if (tElem->ValueTStr() == "cc")
//			{
//				std::vector<std::string> nums = SharedMethod::mySplit(tElem->GetText(), segmentation);
//				float cc0, cc1;
//				sscanf(nums[0].c_str(), "%f", &cc0);
//				sscanf(nums[1].c_str(), "%f", &cc1);
//				camPara.CameraIntrinsic[0][2] = cc0;
//				camPara.CameraIntrinsic[1][2] = cc1;
//			}
//		}
//		else
//		{
//			return false;
//		}

//	}
//	else
//	{
//		return false;
//	}
//	return true;
//}

//bool XMLReader::parseCamRIntrinsicparametersElement(TiXmlHandle hDoc, CamPara& camPara)
//{
//	char* segmentation = " ";

//	TiXmlElement* rElem;
//	rElem = hDoc.FirstChild("StereoParas").Element();
//	if (rElem->ValueTStr() == "StereoParas")
//	{
//		TiXmlElement* pElem;
//		pElem = rElem->FirstChild("CamR_Intrinsic_Parameters")->ToElement();
//		//pElem = hDoc.FirstChildElement("CamR_Intrinsic_Parameters").Element();

//		if (pElem->ValueTStr() == "CamR_Intrinsic_Parameters")
//		{
//			TiXmlElement* tElem;
//			tElem = pElem->FirstChild("fc")->ToElement();
//			if (tElem->ValueTStr() == "fc")
//			{
//				std::vector<std::string> nums = SharedMethod::mySplit(tElem->GetText(), segmentation);
//				float fc0, fc1;
//				sscanf(nums[0].c_str(), "%f", &fc0);
//				sscanf(nums[1].c_str(), "%f", &fc1);
//				camPara.CameraIntrinsic[0][0] = fc0;
//				camPara.CameraIntrinsic[1][1] = fc1;
//			}
//			tElem = pElem->FirstChild("cc")->ToElement();
//			if (tElem->ValueTStr() == "cc")
//			{
//				std::vector<std::string> nums = SharedMethod::mySplit(tElem->GetText(), segmentation);
//				float cc0, cc1;
//				sscanf(nums[0].c_str(), "%f", &cc0);
//				sscanf(nums[1].c_str(), "%f", &cc1);
//				camPara.CameraIntrinsic[0][2] = cc0;
//				camPara.CameraIntrinsic[1][2] = cc1;
//			}
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		return false;
//	}


//	return true;
//}

//bool XMLReader::parseCamLDistortionsElement(TiXmlHandle hDoc, CamPara& camPara)
//{
//	char* segmentation = " ";
//	TiXmlElement* rElem;
//	rElem = hDoc.FirstChild("StereoParas").Element();
//	if (rElem->ValueTStr() == "StereoParas")
//	{

//		TiXmlElement* pElem;
//		pElem = rElem->FirstChild("CamL_Distortion")->ToElement();
//		if (pElem->ValueTStr() == "CamL_Distortion")
//		{
//			TiXmlElement* tElem;
//			tElem = pElem->FirstChild("kc")->ToElement();
//			if (tElem->ValueTStr() == "kc")
//			{
//				std::vector<std::string> nums = SharedMethod::mySplit(tElem->GetText(), segmentation);
//				float kc[4];
//				for (int i = 0; i < 4; i++)
//				{
//					sscanf(nums[i].c_str(), "%f", &kc[i]);
//					camPara.DistortionCoeffs[i] = kc[i];
//				}
//			}
//		}
//		else
//		{
//			return false;
//		}
//	}

//	return true;
//}

//bool XMLReader::parseCamRDistortionsElement(TiXmlHandle hDoc, CamPara& camPara)
//{
//	char* segmentation = " ";
//	TiXmlElement* rElem;
//	rElem = hDoc.FirstChild("StereoParas").Element();
//	if (rElem->ValueTStr() == "StereoParas")
//	{
//		TiXmlElement* pElem;
//		pElem = rElem->FirstChild("CamR_Distortion")->ToElement();
//		if (pElem->ValueTStr() == "CamR_Distortion")
//		{
//			TiXmlElement* tElem;
//			tElem = pElem->FirstChild("kc")->ToElement();
//			if (tElem->ValueTStr() == "kc")
//			{
//				std::vector<std::string> nums = SharedMethod::mySplit(tElem->GetText(), segmentation);
//				float kc[4];
//				for (int i = 0; i < 4; i++)
//				{
//					sscanf(nums[i].c_str(), "%f", &kc[i]);
//					camPara.DistortionCoeffs[i] = kc[i];
//				}
//			}
//		}
//		else
//		{
//			return false;
//		}
//	}

//	return true;
//}

//bool XMLReader::parseRTElement(TiXmlHandle hDoc, struct RT& steroRTPara)
//{
//	char* segmentation = " ";
//	TiXmlElement* rElem;
//	rElem = hDoc.FirstChild("StereoParas").Element();
//	if (rElem->ValueTStr() == "StereoParas")
//	{
//		TiXmlElement* pElem;
//		pElem = rElem->FirstChild("RT_Parameter")->ToElement();
//		if (pElem->ValueTStr() == "RT_Parameter")
//		{
//			TiXmlElement* tElem;
//			tElem = pElem->FirstChild("R")->ToElement();
//			if (tElem->ValueTStr() == "R")
//			{
//				std::vector<std::string> nums = SharedMethod::mySplit(tElem->GetText(), segmentation);
//				float r0, r1, r2;
//				steroRTPara.R.create(3, 1, CV_64FC1);
//				sscanf(nums[0].c_str(), "%f", &r0);
//				sscanf(nums[1].c_str(), "%f", &r1);
//				sscanf(nums[2].c_str(), "%f", &r2);
//				steroRTPara.R.at<double>(0, 0) = r0;
//				steroRTPara.R.at<double>(1, 0) = r1;
//				steroRTPara.R.at<double>(2, 0) = r2;
//			}
//			tElem = pElem->FirstChild("T")->ToElement();
//			if (tElem->ValueTStr() == "T")
//			{
//				std::vector<std::string> nums = SharedMethod::mySplit(tElem->GetText(), segmentation);
//				float t0, t1, t2;
//				steroRTPara.T.create(3, 1, CV_64FC1);
//				sscanf(nums[0].c_str(), "%f", &t0);
//				sscanf(nums[1].c_str(), "%f", &t1);
//				sscanf(nums[2].c_str(), "%f", &t2);
//				steroRTPara.T.at<double>(0, 0) = t0;
//				steroRTPara.T.at<double>(1, 0) = t1;
//				steroRTPara.T.at<double>(2, 0) = t2;
//			}
//		}
//		else
//		{
//			return false;
//		}
//	}

//	return true;
//}

//bool XMLReader::parseStereoParaSize(TiXmlHandle hDoc, Size& imgSize)
//{
//	char* segmentation = " ";
//	TiXmlElement* rElem;
//	rElem = hDoc.FirstChild("StereoParas").Element();
//	if (rElem->ValueTStr() == "StereoParas")
//	{
//		TiXmlElement* pElem;
//		pElem = rElem->FirstChild("Image_Size")->ToElement();
//		if (pElem->ValueTStr() == "Image_Size")
//		{
//			std::vector<std::string> nums = SharedMethod::mySplit(pElem->GetText(), segmentation);
//			int width, height;
//			sscanf(nums[0].c_str(), "%d", &width);
//			sscanf(nums[1].c_str(), "%d", &height);
//			imgSize.width = width;
//			imgSize.height = height;
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		return false;
//	}

//	return true;
//}

//bool XMLReader::parsePoints(TiXmlHandle hDoc, vector<Point>& points)
//{
//	char* segmentation = " ";

//	TiXmlElement* rElem;
//	rElem = hDoc.FirstChild("Params").Element();
//	if (rElem->ValueTStr() == "Params")
//	{
//		TiXmlElement* tElem;
//		tElem = rElem->FirstChild("ROI")->ToElement();
//		if (tElem->ValueTStr()=="ROI")
//		{
//			TiXmlElement* pElem;
//			pElem = tElem->FirstChild("Point0")->ToElement();
//			if (pElem->ValueTStr() == "Point0")
//			{
//				std::vector<std::string> nums = SharedMethod::mySplit(pElem->GetText(), segmentation);
//				Point pnt1;
//				sscanf(nums[0].c_str(), "%d", &pnt1.x);
//				sscanf(nums[1].c_str(), "%d", &pnt1.y);
//				points.push_back(pnt1);
//			}
//			pElem = tElem->FirstChild("Point1")->ToElement();
//			if (pElem->ValueTStr() == "Point1")
//			{
//				std::vector<std::string> nums = SharedMethod::mySplit(pElem->GetText(), segmentation);
//				Point pnt2;
//				sscanf(nums[0].c_str(), "%d", &pnt2.x);
//				sscanf(nums[1].c_str(), "%d", &pnt2.y);
//				points.push_back(pnt2);
//			}
//			else
//			{
//				return false;
//			}
//		}
//	}
//	else
//	{
//		return false;
//	}
//	return true;
//}

bool XMLReader::parseCamLParams(TiXmlHandle hDoc, string& CamIndex,float& shutter, float& gain,
                                int& CamWaitTime,int& MemorySize)
{
    char* segmentation = " ";

    TiXmlElement* rElem;
    rElem = hDoc.FirstChild("Params").Element();
    if (rElem->ValueTStr() == "Params")
    {
        TiXmlElement* tElem;
        tElem = rElem->FirstChild("CamLParams")->ToElement();

        if (tElem->ValueTStr()=="CamLParams")
        {
            TiXmlElement* pElem;
            pElem = tElem->FirstChild("Shutter")->ToElement();
            if (pElem->ValueTStr() == "Shutter")
            {
                std::string shutterStr = pElem->GetText();
                sscanf(shutterStr.c_str(), "%f", &shutter);
            }
            pElem = tElem->FirstChild("Gain")->ToElement();
            if (pElem->ValueTStr() == "Gain")
            {
                std::string gainStr = pElem->GetText();
                sscanf(gainStr.c_str(), "%f", &gain);
            }
            else
            {
                return false;
            }
        }
        TiXmlElement* pElem;
        pElem = rElem->FirstChild("CamIndex")->ToElement();
        if (pElem->ValueTStr() == "CamIndex")
        {
            std::string indexStr = pElem->GetText();
            CamIndex = indexStr;

            //sscanf(indexStr.c_str(), "%s", &CamIndex);
        }
        else
        {
            return false;
        }

        //TiXmlElement* pElem;
        pElem = rElem->FirstChild("CamWaitTime")->ToElement();
        if (pElem->ValueTStr() == "CamWaitTime")
        {
            std::string indexStr = pElem->GetText();
            sscanf(indexStr.c_str(), "%d", &CamWaitTime);
        }
        else
        {
            return false;
        }

        //TiXmlElement* pElem;
        pElem = rElem->FirstChild("OnceGrapNums")->ToElement();
        if (pElem->ValueTStr() == "OnceGrapNums")
        {
            std::string indexStr = pElem->GetText();
            sscanf(indexStr.c_str(), "%d", &MemorySize);
        }
        else
        {
            return false;
        }

    }
    else
    {
        return false;
    }
    return true;
}

bool XMLReader::parseImgSize(TiXmlHandle hDoc, int& imgSize){

    char* segmentation = " ";

    TiXmlElement* rElem;
    rElem = hDoc.FirstChild("Params").Element();
    if (rElem->ValueTStr() == "Params")
    {
        TiXmlElement* tElem;
        tElem = rElem->FirstChild("ImageSize")->ToElement();

        TiXmlElement* pElem;
        pElem = rElem->FirstChild("ImageSize")->ToElement();
        if (pElem->ValueTStr() == "ImageSize")
        {
            std::string indexStr = pElem->GetText();
            imgSize = stoi(indexStr);

        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
    return true;

}

//bool XMLReader::parseMotorParams(TiXmlHandle hDoc, float& speed, float& distance)
//{
//	char* segmentation = " ";

//	TiXmlElement* rElem;
//	rElem = hDoc.FirstChild("Params").Element();
//	if (rElem->ValueTStr() == "Params")
//	{
//		TiXmlElement* tElem;
//		tElem = rElem->FirstChild("MotorParams")->ToElement();
//		if (tElem->ValueTStr()=="MotorParams")
//		{
//			TiXmlElement* pElem;
//			pElem = tElem->FirstChild("Speed")->ToElement();
//			if (pElem->ValueTStr() == "Speed")
//			{
//				std::string shutterStr = pElem->GetText();
//				sscanf(shutterStr.c_str(), "%f", &speed);
//			}
//			pElem = tElem->FirstChild("Angle")->ToElement();
//			if (pElem->ValueTStr() == "Angle")
//			{
//				std::string gainStr = pElem->GetText();
//				sscanf(gainStr.c_str(), "%f", &distance);
//			}
//			else
//			{
//				return false;
//			}
//		}
//	}
//	else
//	{
//		return false;
//	}
//	return true;
//}

//bool XMLReader::parseLaserDetectParams(TiXmlHandle hDoc, int& thre, int& windowWidth, int& centerRange)
//{
//	char* segmentation = " ";

//	TiXmlElement* rElem;
//	rElem = hDoc.FirstChild("Params").Element();
//	if (rElem->ValueTStr() == "Params")
//	{

//		TiXmlElement* tElem;
//		tElem = rElem->FirstChild("LaserDetectParams")->ToElement();
//		if (tElem->ValueTStr() == "LaserDetectParams")
//		{
//			TiXmlElement* pElem;
//			pElem = tElem->FirstChild("Thresh")->ToElement();
//			if (pElem->ValueTStr() == "Thresh")
//			{
//				std::string shutterStr = pElem->GetText();
//				sscanf(shutterStr.c_str(), "%d", &thre);
//			}
//			pElem = tElem->FirstChild("WindowWidth")->ToElement();
//			if (pElem->ValueTStr() == "WindowWidth")
//			{
//				std::string gainStr = pElem->GetText();
//				sscanf(gainStr.c_str(), "%d", &windowWidth);
//			}
//			pElem = tElem->FirstChild("CenterRange")->ToElement();
//			if (pElem->ValueTStr() == "CenterRange")
//			{
//				std::string gainStr = pElem->GetText();
//				sscanf(gainStr.c_str(), "%d", &centerRange);
//			}
//			else
//			{
//				return false;
//			}
//		}
//	}
//	else
//	{
//		return false;
//	}
//	return true;
//}

//bool XMLReader::parseDeviceID(TiXmlHandle hDoc, int& arduinoId, int& motorId)
//{
//	char* segmentation = " ";

//	TiXmlElement* rElem;
//	rElem = hDoc.FirstChild("Params").Element();
//	if (rElem->ValueTStr() == "Params")
//	{

//		TiXmlElement* pElem;
//		pElem = rElem->FirstChild("ArduinoID")->ToElement();
//		if (pElem->ValueTStr() == "ArduinoID")
//		{
//			std::string shutterStr = pElem->GetText();
//			sscanf(shutterStr.c_str(), "%d", &arduinoId);
//		}
//		pElem = rElem->FirstChild("MotorID")->ToElement();
//		if (pElem->ValueTStr() == "MotorID")
//		{
//			std::string gainStr = pElem->GetText();
//			sscanf(gainStr.c_str(), "%d", &motorId);
//		}
//		else
//		{
//			return false;
//		}

//	}
//	else
//	{
//		return false;
//	}
//	return true;
//}

//bool XMLReader::parseLeftParams(TiXmlHandle hDoc, int& groThresh)
//{
//	char* segmentation = " ";

//	TiXmlElement* rElem;
//	rElem = hDoc.FirstChild("Params").Element();
//	if (rElem->ValueTStr() == "Params")
//	{
//		TiXmlElement* pElem;
//		pElem = rElem->FirstChild("GroThresh")->ToElement();
//		if (pElem->ValueTStr() == "GroThresh")
//		{
//			std::string shutterStr = pElem->GetText();
//			sscanf(shutterStr.c_str(), "%d", &groThresh);
//		}
//		else
//		{
//			return false;
//		}

//	}
//	else
//	{
//		return false;
//	}
//	return true;
//}

//#if 0

//bool XMLReader::parseDetectorParams(TiXmlHandle hDoc, detectorParams &DetectorParams)
//{
//	char* seg = " ";

//	TiXmlElement* rElem;
//	rElem = hDoc.FirstChild("DetectParams3D").Element();
//	if (rElem->ValueTStr() == "DetectParams3D")
//	{
//		TiXmlElement *detector;
//		detector = rElem->FirstChild("DetectorParams")->ToElement();
//		if (detector->ValueTStr() == "DetectorParams")
//		{
//			std::vector<std::string> parms_str = split(detector->GetText(), seg);
//			DetectorParams.smoothKNN = atoi(parms_str[0].c_str());
//			DetectorParams.downSampleRatio = atof(parms_str[1].c_str());
//			DetectorParams.keypointerRatio = atof(parms_str[2].c_str());
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		return false;
//	}
//	return true;
//}
//bool XMLReader::parseDetectObjParams(TiXmlHandle hDoc, vector <detectObjParams> &DetectObjsParams)
//{
//	char* seg = " ";
//	TiXmlElement* rElem;
//	rElem = hDoc.FirstChild("DetectParams3D").Element();
//	if (rElem->ValueTStr() == "DetectParams3D")
//	{
//		TiXmlElement *detector;
//		detector = rElem->FirstChild("DetectObjectParams")->ToElement();
//		if (detector->ValueTStr() == "DetectObjectParams")
//		{
//			for (TiXmlElement *dectectObj = detector->FirstChild()->ToElement(); dectectObj; dectectObj = dectectObj->NextSiblingElement())
//			{
//				detectObjParams _temp;
//				std::vector<std::string> parms_str;
//				_temp.ObjectName = dectectObj->ValueTStr().c_str();
//				parms_str = split(dectectObj->GetText(), seg);
//				_temp.ShowColor = parms_str[0];
//				_temp.minScore = atof(parms_str[1].c_str());
//				_temp.mlsOrder = atoi(parms_str[2].c_str());
//				DetectObjsParams.push_back(_temp);
//			}
//		}
//		else
//			return false;
//	}
//	else
//	{
//		return false;
//	}
//	return true;
//}

//#endif

//bool XMLReader::ReadRT44(std::string filename, vector<Mat>& Inputs)
//{
//	char* segmentation = " ";
//	TiXmlDocument doc;
//	if (!doc.LoadFile(filename.c_str()))
//	{
//		return false;
//	}
//	TiXmlHandle hDoc(&doc);
//	TiXmlElement* pElem;

//	pElem = hDoc.FirstChild("MatRT44").Element();
//	if (pElem->ValueTStr() == "MatRT44")
//	{
//		int num = pElem->FirstAttribute()->IntValue();
//		TiXmlElement* tElem;
//		tElem = pElem->FirstChild()->ToElement();
//		for (int i = 0; i < num; i++)
//		{
//			Mat CamRT44 = Mat::zeros(4, 4, CV_64F);
//			//rt.R = Mat(3, 1, CV_64F); rt.T = Mat(3, 1, CV_64F);
//			TiXmlElement* _tElem;
//			_tElem = tElem->FirstChild()->ToElement();
//			for (_tElem; _tElem; _tElem = _tElem->NextSiblingElement())
//			{
//				std::vector<std::string> nums = SharedMethod::mySplit(_tElem->GetText(), segmentation);
//				float vec[16];
//				for (int j = 0; j < 16; j++)
//				{
//					sscanf(nums[j].c_str(), "%f", &vec[j]);
//					if (_tElem->ValueTStr() == "RT")
//					{
//						int l, k;
//						l = j % 4; //// 除以 代表列
//						k = int(j / 4); //// mode 代表行
//						CamRT44.at<double>(k, l) = vec[j];
//					}
//					else
//						break;
//				}
//			}
//			Inputs.push_back(CamRT44);
//			tElem = tElem->NextSiblingElement();
//		}
//	}
//	else
//	{
//		return false;
//	}

//	return true;
//}

//bool XMLReader::ReadLineParams(std::string filename, cv::Point3f& dir, cv::Point3f& pnt)
//{
//	//加载文件
//	TiXmlDocument doc;
//	if (!doc.LoadFile(filename.c_str()))
//	{
//		return false;
//	}
//	TiXmlHandle hDoc(&doc);

//	if (!parseLineParams(hDoc, dir, pnt))
//	{
//		return false;
//	}
//	return true;
//}

//bool XMLReader::parseLineParams(TiXmlHandle hDoc, cv::Point3f& dir, cv::Point3f& pnt)
//{
//	char* segmentation = " ";

//	TiXmlElement* rElem;
//	rElem = hDoc.FirstChild("LineParams").Element();
//	if (rElem->ValueTStr() == "LineParams")
//	{
//		TiXmlElement* pElem;
//		pElem = rElem->FirstChild("Direction")->ToElement();
//		if (pElem->ValueTStr() == "Direction")
//		{
//			std::vector<std::string> nums = SharedMethod::mySplit(pElem->GetText(), segmentation);
//			sscanf(nums[0].c_str(), "%f", &dir.x);
//			sscanf(nums[1].c_str(), "%f", &dir.y);
//			sscanf(nums[2].c_str(), "%f", &dir.z);
//		}
//		pElem = rElem->FirstChild("Point")->ToElement();
//		if (pElem->ValueTStr() == "Point")
//		{
//			std::vector<std::string> nums = SharedMethod::mySplit(pElem->GetText(), segmentation);
//			sscanf(nums[0].c_str(), "%f", &pnt.x);
//			sscanf(nums[1].c_str(), "%f", &pnt.y);
//			sscanf(nums[2].c_str(), "%f", &pnt.z);
//		}
//		else
//		{
//			return false;
//		}

//	}
//	else
//	{
//		return false;
//	}
//	return true;
//}

//bool XMLReader::readCornerData(std::string filename, CalibrationData& m_cornerData)
//{
//	TiXmlDocument doc;
//	if (!doc.LoadFile(filename.c_str()))
//	{
//		return false;
//	}
//	TiXmlHandle hDoc(&doc);

//	vector<int> CornerNumPerFrame;

//	if (!parseImageSizeElement(hDoc, m_cornerData))
//		return false;
//	if (!parseCornerNumPerFrameElement(hDoc, CornerNumPerFrame))
//		return false;
//	if (!parseCornerPointsElement(hDoc, CornerNumPerFrame, m_cornerData))
//		return false;
//	if (!parseFeaturePointsElement(hDoc, CornerNumPerFrame, m_cornerData))
//		return false;
//	if (!parseFrameNumListElement(hDoc, m_cornerData))
//		return false;

//	return true;
//}

bool XMLReader::ReadCamParams(std::string filename, string& CamIndex,float& shutter, float& gain,
                              int& CamWaitTime,int& MemorySize)
{
    //加载文件
    TiXmlDocument doc;
    if (!doc.LoadFile(filename.c_str()))
    {
        return false;
    }
    TiXmlHandle hDoc(&doc);

    if (!parseCamLParams(hDoc,CamIndex, shutter,gain,CamWaitTime, MemorySize))
    {
        return false;
    }
    return true;

}

bool XMLReader::ReadImgSize(std::string filename,int& imgSize){

    //加载文件
    TiXmlDocument doc;
    if (!doc.LoadFile(filename.c_str()))
    {
        return false;
    }
    TiXmlHandle hDoc(&doc);

    if (!parseImgSize(hDoc,imgSize))
    {
        return false;
    }
    return true;


}


//bool XMLReader::ReadMotorParams(std::string filename, float& speed, float& distance)
//{
//	//加载文件
//	TiXmlDocument doc;
//	if (!doc.LoadFile(filename.c_str()))
//	{
//		return false;
//	}
//	TiXmlHandle hDoc(&doc);

//	if (!parseMotorParams(hDoc, speed, distance))
//	{
//		return false;
//	}
//	return true;
//}

////bool XMLReader::ReadLaserDetectParams(std::string filename, int& thre, int& windowWidth, int& centerRange, int& GroThre)
////{
////	//加载文件
////	TiXmlDocument doc;
////	if (!doc.LoadFile(filename.c_str()))
////	{
////		return false;
////	}
////	TiXmlHandle hDoc(&doc);
////
////	if (!parseLaserDetectParams(hDoc, thre, windowWidth,centerRange,GroThre))
////	{
////		return false;
////	}
////	return true;
////}

//bool XMLReader::ReadLaserSystemConfig(std::string filename, ScanParams& params)
//{
//	//加载文件
//	TiXmlDocument doc;
//	if (!doc.LoadFile(filename.c_str()))
//	{
//		return false;
//	}
//	TiXmlHandle hDoc(&doc);
//	//读取设备ID
//	if (!parseDeviceID(hDoc,params.iArduinoPort,params.iMotorPort))
//	{
//		return false;
//	}
//	//读取左相机参数
//	if (!parseCamLParams(hDoc,params.shutterL,params.gainL))
//	{
//		return false;
//	}
//	//读取右相机参数
//	if (!parseCamRParams(hDoc,params.shutterR,params.gainR))
//	{
//		return false;
//	}
//	//读取条纹提取参数
//	if (!parseLaserDetectParams(hDoc, params.thre, params.windowWidth, params.centerRange))
//	{
//		return false;
//	}
//	//读取其他参数
//	if (!parseLeftParams(hDoc,params.groThresh))
//	{
//		return false;
//	}
//	//读取电机参数
//	if (!parseMotorParams(hDoc,params.scanSpeed,params.scanAngle))
//	{
//		return false;
//	}
//	//读取roi参数
//	if (!parsePoints(hDoc,params.roi))
//	{
//		return false;
//	}
//	return true;
//}

////ZZL
////bool XMLReader::Read3DdetectSetingParams(std::string filename, detectorParams &DetectorParams, vector <detectObjParams> &DetectObjsParams)
////{
////	char* seg = " ";
////	TiXmlDocument doc;
////	if (!doc.LoadFile(filename.c_str()))
////	{
////		string str = doc.ErrorDesc();
////		return false;
////	}
////	TiXmlHandle hDoc(&doc);
////	if (!parseDetectorParams(hDoc, DetectorParams))
////	{
////		return false;
////	}
////	if (!parseDetectObjParams(hDoc, DetectObjsParams))
////	{
////		return false;
////	}
////	return true;
////
////}

////bool XMLReader::parseDetectorParams(TiXmlHandle hDoc, detectorParams &DetectorParams)
////{
////	try
////	{
////		char* seg = " ";
////
////		TiXmlElement* rElem;
////		rElem = hDoc.FirstChild("DetectParams3D").Element();
////		if (rElem->ValueTStr() == "DetectParams3D")
////		{
////			TiXmlElement *detector;
////			detector = rElem->FirstChild("DetectorParams")->ToElement();
////			if (detector->ValueTStr() == "DetectorParams")
////			{
////				std::vector<std::string> parms_str = split(detector->GetText(), seg);
////				DetectorParams.smoothKNN = atoi(parms_str[0].c_str());
////				DetectorParams.downSampleRatio = atof(parms_str[1].c_str());
////				DetectorParams.keypointerRatio = atof(parms_str[2].c_str());
////			}
////			else
////			{
////				return false;
////			}
////		}
////		else
////		{
////			return false;
////		}
////		return true;
////	}
////	catch (...)
////	{
////		return false;
////	}
////}

////bool XMLReader::parseDetectObjParams(TiXmlHandle hDoc, vector <detectObjParams> &DetectObjsParams)
////{
////	try
////	{
////		char* seg = " ";
////		TiXmlElement* rElem;
////		rElem = hDoc.FirstChild("DetectParams3D").Element();
////		if (rElem->ValueTStr() == "DetectParams3D")
////		{
////			TiXmlElement *detector;
////			detector = rElem->FirstChild("DetectObjectParams")->ToElement();
////			if (detector->ValueTStr() == "DetectObjectParams")
////			{
////				for (TiXmlElement *dectectObj = detector->FirstChild()->ToElement(); dectectObj; dectectObj = dectectObj->NextSiblingElement())
////				{
////					detectObjParams _temp;
////					std::vector<std::string> parms_str;
////					_temp.ObjectName = dectectObj->ValueTStr().c_str();
////					parms_str = split(dectectObj->GetText(), seg);
////					_temp.ShowColor = parms_str[0];
////					_temp.minScore = atof(parms_str[1].c_str());
////					_temp.mlsOrder = atoi(parms_str[2].c_str());
////					_temp.isDetected = (bool)atoi(parms_str[3].c_str());
////					_temp.MaxOverlapDistRel = atof(parms_str[4].c_str());
////					DetectObjsParams.push_back(_temp);
////				}
////			}
////			else
////				return false;
////		}
////		else
////		{
////			return false;
////		}
////		return true;
////	}
////	catch (...)
////	{
////		return false;
////	}
////}

//bool XMLReader::parseImageSizeElement(TiXmlHandle hDoc, CalibrationData& m_cornerData)
//{
//	char* segmentation = " ";
//	TiXmlElement* pElem;
//	pElem = hDoc.FirstChild("ImageSize").Element();
//	if (pElem->ValueTStr() == "ImageSize")
//	{
//		TiXmlElement* tElem;
//		tElem = pElem->FirstChild("Height")->ToElement();
//		if (tElem->ValueTStr() == "Height")
//		{
//			std::vector<std::string> nums = SharedMethod::mySplit(tElem->GetText(), segmentation);
//			float height;
//			sscanf(nums[0].c_str(), "%f", &height);
//			m_cornerData.imgHeight = height;
//		}

//		tElem = pElem->FirstChild("Width")->ToElement();
//		if (tElem->ValueTStr() == "Width")
//		{
//			std::vector<std::string> nums = SharedMethod::mySplit(tElem->GetText(), segmentation);
//			float width;
//			sscanf(nums[0].c_str(), "%f", &width);
//			m_cornerData.imgWidth = width;
//		}
//	}
//	else
//	{
//		return false;
//	}

//	return true;
//}

//bool XMLReader::parseCornerNumPerFrameElement(TiXmlHandle hDoc, vector<int>& CornerNumPerFrame)
//{
//	char* segmentation = " ";
//	TiXmlElement* pElem;
//	pElem = hDoc.FirstChild("CornerNumPerFrame").Element();
//	if (pElem->ValueTStr() == "CornerNumPerFrame")
//	{
//		TiXmlElement* tElem;
//		tElem = pElem->FirstChildElement();
//		const char* jj = tElem->Value();
//		for (tElem; tElem; tElem = tElem->NextSiblingElement())
//		{
//			std::vector<std::string> nums = SharedMethod::mySplit(tElem->GetText(), segmentation);
//			int num;
//			sscanf(nums[0].c_str(), "%d", &num);
//			CornerNumPerFrame.push_back(num);
//		}
//	}
//	else
//	{
//		return false;
//	}
//	return true;
//}

//bool XMLReader::parseCornerPointsElement(TiXmlHandle hDoc, const vector<int>& CornerNumPerFrame, CalibrationData& m_cornerData)
//{
//	char* segmentation = " ";
//	TiXmlElement* pElem;
//	pElem = hDoc.FirstChild("Corner_Points").Element();
//	if (pElem->ValueTStr() == "Corner_Points")
//	{
//		TiXmlElement* tElem;
//		tElem = pElem->FirstChildElement();
//		const char* jj = tElem->Value();
//		for (int i = 0; i < CornerNumPerFrame.size(); i++)
//		{
//			vector<Point2f> pnts2d;
//			for (int j = 0; j < CornerNumPerFrame[i]; tElem = tElem->NextSiblingElement(), j++)
//			{
//				vector<string> nums = SharedMethod::mySplit(tElem->GetText(), segmentation);
//				float point[2];
//				sscanf(nums[0].c_str(), "%f", &point[0]);
//				sscanf(nums[1].c_str(), "%f", &point[1]);
//				pnts2d.push_back(cv::Point2f(point[0], point[1]));
//			}
//			m_cornerData.plane2dPntsVec.push_back(pnts2d);
//		}
//	}
//	else
//	{
//		return false;
//	}
//	return true;
//}

//bool XMLReader::parseFeaturePointsElement(TiXmlHandle hDoc, const vector<int>& CornerNumPerFrame, CalibrationData& m_cornerData)
//{
//	char* segmentation = " ";
//	TiXmlElement* pElem;
//	pElem = hDoc.FirstChild("Feature_Points").Element();
//	if (pElem->ValueTStr() == "Feature_Points")
//	{
//		TiXmlElement* tElem;
//		tElem = pElem->FirstChildElement();
//		for (int i = 0; i < CornerNumPerFrame.size(); i++)
//		{
//			vector<Point3f> pnts3d;
//			for (int j = 0; j < CornerNumPerFrame[i]; tElem = tElem->NextSiblingElement(), j++)
//			{
//				vector<string> nums = SharedMethod::mySplit(tElem->GetText(), segmentation);
//				float point[3];
//				sscanf(nums[0].c_str(), "%f", &point[0]);
//				sscanf(nums[1].c_str(), "%f", &point[1]);
//				sscanf(nums[2].c_str(), "%f", &point[2]);
//				pnts3d.push_back(Point3f(point[0], point[1], point[2]));
//			}
//			m_cornerData.plane3dPntsVec.push_back(pnts3d);
//		}
//	}
//	else
//	{
//		return false;
//	}
//	return true;
//}

//bool XMLReader::parseFrameNumListElement(TiXmlHandle hDoc, CalibrationData& m_cornerData)
//{
//	char* segmentation = " ";
//	TiXmlElement* pElem;
//	pElem = hDoc.FirstChild("FrameNumList").Element();
//	int n = pElem->FirstAttribute()->IntValue();
//	if (pElem->ValueTStr() == "FrameNumList")
//	{
//		TiXmlElement* tElem;
//		tElem = pElem->FirstChildElement();
//		const char* jj = tElem->Value();
//		for (tElem; tElem; tElem = tElem->NextSiblingElement())
//		{
//			std::vector<std::string> nums = SharedMethod::mySplit(tElem->GetText(), segmentation);
//			int index;
//			sscanf(nums[0].c_str(), "%d", &index);
//			m_cornerData.frameNumList.push_back(index);
//		}
//	}
//	else
//	{
//		return false;
//	}
//	return true;
//}
////************** Underwater parameter HPP ***************//
//bool XMLReader::ReadUnderWaterValue(std::string filename, Mat& DisL, Mat& MiuL, Mat& Nor_valueL, Mat&R_l2r, Mat& DisR, Mat& MiuR, Mat& Nor_valueR, Mat&t_l2r)
//{
//	//加载文件
//	TiXmlDocument doc;
//	if (!doc.LoadFile(filename.c_str()))
//	{
//		return false;
//	}
//	TiXmlHandle hDoc(&doc);

//	if (!ReadDisL(hDoc, DisL))
//	{
//		return false;
//	}

//	if (!ReadMiuL(hDoc, MiuL))
//	{
//		return false;
//	}

//	if (!ReadnormalvalueL(hDoc, Nor_valueL))
//	{
//		return false;
//	}
//	if (!ReadRvalue(hDoc, R_l2r))
//	{
//		return false;
//	}

//	if (!ReadDisR(hDoc, DisR))
//	{
//		return false;
//	}

//	if (!ReadMiuR(hDoc, MiuR))
//	{
//		return false;
//	}

//	if (!ReadnormalvalueR(hDoc, Nor_valueR))
//	{
//		return false;
//	}
//	if (!ReadTvalue(hDoc, t_l2r))
//	{
//		return false;
//	}
//}
////************** Underwater parameter HPP ***************//

//bool XMLReader::ReadDisL(TiXmlHandle hDoc, Mat&DisL)
//{
//	DisL = Mat(1, 2, CV_64F);
//	char* segmentation = " ";
//	TiXmlElement* lElem;
//	lElem = hDoc.FirstChild("data").Element();
//	if (lElem->ValueTStr() == "data")
//	{
//		TiXmlElement* pElem;
//		pElem = lElem->FirstChild("Left")->ToElement();
//		if (pElem->ValueTStr() == "Left")
//		{
//			TiXmlElement*tElem;
//			tElem = pElem->FirstChild("distance")->ToElement();
//			if (tElem->ValueTStr() == "distance")
//			{
//				//将distance数据存到DisL
//				std::vector<std::string> nums = SharedMethod::mySplit(tElem->GetText(), segmentation);
//				float fc0, fc1;

//				sscanf(nums[0].c_str(), "%f", &fc0);
//				sscanf(nums[1].c_str(), "%f", &fc1);

//				DisL.at<double>(0, 0) = fc0;
//				DisL.at<double>(0, 1) = fc1;
//			}
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		return false;
//	}
//	return true;
//}

//bool XMLReader::ReadMiuL(TiXmlHandle hDoc, Mat&MiuL)
//{
//	MiuL = Mat(1, 3, CV_64F);
//	char* segmentation = " ";
//	TiXmlElement* lElem;
//	lElem = hDoc.FirstChild("data").Element();
//	if (lElem->ValueTStr() == "data")
//	{
//		TiXmlElement* pElem;
//		pElem = lElem->FirstChild("Left")->ToElement();
//		if (pElem->ValueTStr() == "Left")
//		{
//			TiXmlElement*tElem;
//			tElem = pElem->FirstChild("miu")->ToElement();
//			if (tElem->ValueTStr() == "miu")
//			{
//				//将miu数据存到miuL
//				std::vector<std::string> nums = SharedMethod::mySplit(tElem->GetText(), segmentation);
//				float fc0, fc1, fc2;
//				sscanf(nums[0].c_str(), "%f", &fc0);
//				sscanf(nums[1].c_str(), "%f", &fc1);
//				sscanf(nums[2].c_str(), "%f", &fc2);
//				MiuL.at<double>(0, 0) = fc0;
//				MiuL.at<double>(0, 1) = fc1;
//				MiuL.at<double>(0, 2) = fc2;
//			}
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		return false;
//	}
//	return true;
//}

//bool XMLReader::ReadnormalvalueL(TiXmlHandle hDoc, Mat &Nor_valueL)
//{
//	Nor_valueL = Mat(2, 1, CV_64F);
//	char* segmentation = " ";
//	TiXmlElement* lElem;
//	lElem = hDoc.FirstChild("data").Element();
//	if (lElem->ValueTStr() == "data")
//	{
//		TiXmlElement* pElem;
//		pElem = lElem->FirstChild("Left")->ToElement();
//		if (pElem->ValueTStr() == "Left")
//		{
//			TiXmlElement*tElem;
//			tElem = pElem->FirstChild("normal")->ToElement();
//			if (tElem->ValueTStr() == "normal")
//			{
//				//将normal数据存到Nor_valueL
//				std::vector<std::string> nums = SharedMethod::mySplit(tElem->GetText(), segmentation);
//				float fc0, fc1;
//				sscanf(nums[0].c_str(), "%f", &fc0);
//				sscanf(nums[1].c_str(), "%f", &fc1);
//				Nor_valueL.at<double>(0, 0) = fc0;
//				Nor_valueL.at<double>(1, 0) = fc1;
//			}
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		return false;
//	}
//	return true;
//}
//bool XMLReader::ReadRvalue(TiXmlHandle hDoc, Mat &R_l2r)
//{
//	R_l2r = Mat(3, 1, CV_64F);
//	char* segmentation = " ";
//	TiXmlElement* lElem;
//	lElem = hDoc.FirstChild("data").Element();
//	if (lElem->ValueTStr() == "data")
//	{
//		TiXmlElement* pElem;
//		pElem = lElem->FirstChild("Rl2r")->ToElement();
//		if (pElem->ValueTStr() == "Rl2r")
//		{
//			std::vector<std::string> nums = SharedMethod::mySplit(pElem->GetText(), segmentation);
//			float fc0, fc1, fc2;
//			sscanf(nums[0].c_str(), "%f", &fc0);
//			sscanf(nums[1].c_str(), "%f", &fc1);
//			sscanf(nums[2].c_str(), "%f", &fc2);
//			R_l2r.at<double>(0, 0) = fc0;
//			R_l2r.at<double>(1, 0) = fc1;
//			R_l2r.at<double>(2, 0) = fc2;
//		}
//		else
//		{
//			return false;
//		}
//	}
//	return true;
//}

//bool XMLReader::ReadDisR(TiXmlHandle hDoc, Mat&DisR)
//{
//	DisR = Mat(1, 2, CV_64F);
//	char* segmentation = " ";
//	TiXmlElement* lElem;
//	lElem = hDoc.FirstChild("data").Element();
//	if (lElem->ValueTStr() == "data")
//	{
//		TiXmlElement* pElem;
//		pElem = lElem->FirstChild("Right")->ToElement();
//		if (pElem->ValueTStr() == "Right")
//		{
//			TiXmlElement*tElem;
//			tElem = pElem->FirstChild("distance")->ToElement();
//			if (tElem->ValueTStr() == "distance")
//			{
//				//将distance数据存到DisR
//				std::vector<std::string> nums = SharedMethod::mySplit(tElem->GetText(), segmentation);
//				float fc0, fc1;
//				sscanf(nums[0].c_str(), "%f", &fc0);
//				sscanf(nums[1].c_str(), "%f", &fc1);
//				DisR.at<double>(0, 0) = fc0;
//				DisR.at<double>(0, 1) = fc1;
//			}
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		return false;
//	}
//	return true;
//}

//bool XMLReader::ReadMiuR(TiXmlHandle hDoc, Mat&MiuR)
//{
//	MiuR = Mat(1, 3, CV_64F);
//	char* segmentation = " ";
//	TiXmlElement* lElem;
//	lElem = hDoc.FirstChild("data").Element();
//	if (lElem->ValueTStr() == "data")
//	{
//		TiXmlElement* pElem;
//		pElem = lElem->FirstChild("Right")->ToElement();
//		if (pElem->ValueTStr() == "Right")
//		{
//			TiXmlElement*tElem;
//			tElem = pElem->FirstChild("miu")->ToElement();
//			if (tElem->ValueTStr() == "miu")
//			{
//				//将miu数据存到miuR
//				std::vector<std::string> nums = SharedMethod::mySplit(tElem->GetText(), segmentation);
//				float fc0, fc1, fc2;
//				sscanf(nums[0].c_str(), "%f", &fc0);
//				sscanf(nums[1].c_str(), "%f", &fc1);
//				sscanf(nums[2].c_str(), "%f", &fc2);
//				MiuR.at<double>(0, 0) = fc0;
//				MiuR.at<double>(0, 1) = fc1;
//				MiuR.at<double>(0, 2) = fc2;

//				//Mat a;
//				//if (MiuR.depth() == CV_64F)
//				//{
//				//	a = MiuR;
//				//}
//				//else
//				//{
//				//	MiuR.convertTo(a, CV_64F);
//				//}

//			}
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		return false;
//	}
//	return true;
//}

//bool XMLReader::ReadnormalvalueR(TiXmlHandle hDoc, Mat &Nor_valueR)
//{
//	Nor_valueR = Mat(2, 1, CV_64F);
//	char* segmentation = " ";
//	TiXmlElement* lElem;
//	lElem = hDoc.FirstChild("data").Element();
//	if (lElem->ValueTStr() == "data")
//	{
//		TiXmlElement* pElem;
//		pElem = lElem->FirstChild("Right")->ToElement();
//		if (pElem->ValueTStr() == "Right")
//		{
//			TiXmlElement*tElem;
//			tElem = pElem->FirstChild("normal")->ToElement();
//			if (tElem->ValueTStr() == "normal")
//			{
//				//将normal数据存到Nor_valueR
//				std::vector<std::string> nums = SharedMethod::mySplit(tElem->GetText(), segmentation);
//				float fc0, fc1;
//				sscanf(nums[0].c_str(), "%f", &fc0);
//				sscanf(nums[1].c_str(), "%f", &fc1);
//				Nor_valueR.at<double>(0, 0) = fc0;
//				Nor_valueR.at<double>(1, 0) = fc1;
//			}
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		return false;
//	}
//	return true;
//}

//bool XMLReader::ReadTvalue(TiXmlHandle hDoc, Mat &t_l2r)
//{
//	t_l2r = Mat(3, 1, CV_64F);
//	char* segmentation = " ";
//	TiXmlElement* lElem;
//	lElem = hDoc.FirstChild("data").Element();
//	if (lElem->ValueTStr() == "data")
//	{
//		TiXmlElement* pElem;
//		pElem = lElem->FirstChild("tl2r")->ToElement();
//		if (pElem->ValueTStr() == "tl2r")
//		{
//			std::vector<std::string> nums = SharedMethod::mySplit(pElem->GetText(), segmentation);
//			float
//				fc0, fc1, fc2;
//			sscanf(nums[0].c_str(), "%f", &fc0);
//			sscanf(nums[1].c_str(), "%f", &fc1);
//			sscanf(nums[2].c_str(), "%f", &fc2);
//			t_l2r.at<double>(0, 0) = fc0;
//			t_l2r.at<double>(1, 0) = fc1;
//			t_l2r.at<double>(2, 0) = fc2;
//		}
//		else
//		{
//			return false;
//		}
//	}
//	return true;
//}
////////////水下参数
//bool XMLReader::ReadUnderWaterValue1Layer(std::string filename, Mat& DisL, Mat& MiuL, Mat& Nor_valueL, Mat&R_l2r, Mat& DisR, Mat& MiuR, Mat& Nor_valueR, Mat&t_l2r)
//{
//	//加载文件
//	TiXmlDocument doc;
//	if (!doc.LoadFile(filename.c_str()))
//	{
//		return false;
//	}
//	TiXmlHandle hDoc(&doc);

//	if (!ReadDisL1Layer(hDoc, DisL))
//	{
//		return false;
//	}

//	if (!ReadMiuL1Layer(hDoc, MiuL))
//	{
//		return false;
//	}

//	if (!ReadnormalvalueL(hDoc, Nor_valueL))
//	{
//		return false;
//	}
//	if (!ReadRvalue(hDoc, R_l2r))
//	{
//		return false;
//	}

//	if (!ReadDisR1Layer(hDoc, DisR))
//	{
//		return false;
//	}

//	if (!ReadMiuR1Layer(hDoc, MiuR))
//	{
//		return false;
//	}

//	if (!ReadnormalvalueR(hDoc, Nor_valueR))
//	{
//		return false;
//	}
//	if (!ReadTvalue(hDoc, t_l2r))
//	{
//		return false;
//	}
//}
//bool XMLReader::ReadDisL1Layer(TiXmlHandle hDoc, Mat&DisL)
//{
//	DisL = Mat(1, 1, CV_64F);
//	char* segmentation = " ";
//	TiXmlElement* lElem;
//	lElem = hDoc.FirstChild("data").Element();
//	if (lElem->ValueTStr() == "data")
//	{
//		TiXmlElement* pElem;
//		pElem = lElem->FirstChild("Left")->ToElement();
//		if (pElem->ValueTStr() == "Left")
//		{
//			TiXmlElement*tElem;
//			tElem = pElem->FirstChild("distance")->ToElement();
//			if (tElem->ValueTStr() == "distance")
//			{
//				//将distance数据存到DisL
//				std::vector<std::string> nums = SharedMethod::mySplit(tElem->GetText(), segmentation);
//				float fc0;

//				sscanf(nums[0].c_str(), "%f", &fc0);

//				DisL.at<double>(0, 0) = fc0;
//			}
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		return false;
//	}
//	return true;
//}

//bool XMLReader::ReadMiuL1Layer(TiXmlHandle hDoc, Mat&MiuL)
//{
//	MiuL = Mat(1, 2, CV_64F);
//	char* segmentation = " ";
//	TiXmlElement* lElem;
//	lElem = hDoc.FirstChild("data").Element();
//	if (lElem->ValueTStr() == "data")
//	{
//		TiXmlElement* pElem;
//		pElem = lElem->FirstChild("Left")->ToElement();
//		if (pElem->ValueTStr() == "Left")
//		{
//			TiXmlElement*tElem;
//			tElem = pElem->FirstChild("miu")->ToElement();
//			if (tElem->ValueTStr() == "miu")
//			{
//				//将miu数据存到miuL
//				std::vector<std::string> nums = SharedMethod::mySplit(tElem->GetText(), segmentation);
//				float fc0, fc1;
//				sscanf(nums[0].c_str(), "%f", &fc0);
//				sscanf(nums[1].c_str(), "%f", &fc1);
//				MiuL.at<double>(0, 0) = fc0;
//				MiuL.at<double>(0, 1) = fc1;
//			}
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		return false;
//	}
//	return true;
//}

//bool XMLReader::ReadDisR1Layer(TiXmlHandle hDoc, Mat&DisR)
//{
//	DisR = Mat(1, 1, CV_64F);
//	char* segmentation = " ";
//	TiXmlElement* lElem;
//	lElem = hDoc.FirstChild("data").Element();
//	if (lElem->ValueTStr() == "data")
//	{
//		TiXmlElement* pElem;
//		pElem = lElem->FirstChild("Right")->ToElement();
//		if (pElem->ValueTStr() == "Right")
//		{
//			TiXmlElement*tElem;
//			tElem = pElem->FirstChild("distance")->ToElement();
//			if (tElem->ValueTStr() == "distance")
//			{
//				//将distance数据存到DisR
//				std::vector<std::string> nums = SharedMethod::mySplit(tElem->GetText(), segmentation);
//				float fc0;
//				sscanf(nums[0].c_str(), "%f", &fc0);
//				DisR.at<double>(0, 0) = fc0;
//			}
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		return false;
//	}
//	return true;
//}

//bool XMLReader::ReadMiuR1Layer(TiXmlHandle hDoc, Mat&MiuR)
//{
//	MiuR = Mat(1, 2, CV_64F);
//	char* segmentation = " ";
//	TiXmlElement* lElem;
//	lElem = hDoc.FirstChild("data").Element();
//	if (lElem->ValueTStr() == "data")
//	{
//		TiXmlElement* pElem;
//		pElem = lElem->FirstChild("Right")->ToElement();
//		if (pElem->ValueTStr() == "Right")
//		{
//			TiXmlElement*tElem;
//			tElem = pElem->FirstChild("miu")->ToElement();
//			if (tElem->ValueTStr() == "miu")
//			{
//				//将miu数据存到miuR
//				std::vector<std::string> nums = SharedMethod::mySplit(tElem->GetText(), segmentation);
//				float fc0, fc1;
//				sscanf(nums[0].c_str(), "%f", &fc0);
//				sscanf(nums[1].c_str(), "%f", &fc1);
//				MiuR.at<double>(0, 0) = fc0;
//				MiuR.at<double>(0, 1) = fc1;
//			}
//		}
//		else
//		{
//			return false;
//		}
//	}
//	else
//	{
//		return false;
//	}
//	return true;
//}
