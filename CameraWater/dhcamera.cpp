#include "dhcamera.h"

CaptureHander* CaptureHander::p = NULL;

CaptureHander::CaptureHander(bool isColor,bool& isScan,std::queue<cv::Mat>& imgQueTem)
{
    m_isColorCamera = isColor;
    m_isScan = &isScan;
    imgQueue = &imgQueTem;
}

void GX_STDC CaptureHander::OnFrameCallbackFun(GX_FRAME_CALLBACK_PARAM* pFrame)
{
    //CaptureHander *p =(CaptureHander*) pFrame;
    if (pFrame->status == GX_FRAME_STATUS_SUCCESS)
    {
        //彩色相机
        if(p->m_isColorCamera)
        {
            //cout<<get_time()<<endl;
            DxRaw8toRGB24((void*)pFrame->pImgBuf, p->g_pRGBImageBuf,
                          pFrame->nWidth, pFrame->nHeight, RAW2RGB_NEIGHBOUR, BAYERRG, false);
            if(p->colorCameraOutput)
            {
                p->img = cv::Mat(pFrame->nHeight, pFrame->nWidth, CV_8UC3,p->g_pRGBImageBuf);
                //cout<<"111"<<endl;
            }
            else
            {
                cv::cvtColor(cv::Mat(pFrame->nHeight, pFrame->nWidth, CV_8UC3,p->g_pRGBImageBuf),p->img,cv::COLOR_RGB2GRAY);
            }
            if(*(p->m_isScan))
            {
                p->imgQueue->push(p->img);
            }
        }
        else //黑白相机
        {
            DxRaw16toRaw8((void*)pFrame->pImgBuf, p->g_pMonoImageBuf,
                          pFrame->nWidth, pFrame->nHeight, DX_BIT_2_9);
            p->img = cv::Mat(pFrame->nHeight, pFrame->nWidth, CV_8UC1,p->g_pMonoImageBuf);
            if(*(p->m_isScan))
            {
                p->imgQueue->push(p->img);
            }
        }

    }
    *(bool*)(pFrame->pUserParam) = true;

}

DhCamera::DhCamera()
{
    GX_STATUS emStatus = GX_STATUS_SUCCESS;

    emStatus = GXInitLib();
    if(emStatus != GX_STATUS_SUCCESS)
    {
        GetErrorString(emStatus);
        return;
    }
    m_ImgGet =false;
    m_Exposure = 100;
    m_Gain = 0;
}


DhCamera::~DhCamera()
{
    GX_STATUS emStatus = GX_STATUS_SUCCESS;

    emStatus = GXCloseLib();
    if(emStatus != GX_STATUS_SUCCESS)
    {
        GetErrorString(emStatus);
        return;
    }
}

bool DhCamera::ConnectCamera(int index,std::queue<cv::Mat>& imaQue,float Exposure,float Gain)
{
    //初始化打开设备
    GX_STATUS emStatus = GX_STATUS_SUCCESS;
    uint32_t ui32DeviceNum = 0;

    emStatus = GXUpdateDeviceList(&ui32DeviceNum, 1000);
    if(emStatus != GX_STATUS_SUCCESS)
    {
        GetErrorString(emStatus);
        GXCloseLib();
        return false;
    }
    if(ui32DeviceNum <= 0)
    {
        printf("<No device found>\n");
        GXCloseLib();
        return false;
    }

    emStatus = GXOpenDeviceByIndex(index, &m_hDevice);
    if(emStatus != GX_STATUS_SUCCESS)
    {
        GetErrorString(emStatus);
        GXCloseLib();
        return false;
    }

    //判断相机是否为彩色
    emStatus = GXIsImplemented(m_hDevice, GX_ENUM_PIXEL_COLOR_FILTER, &m_IsColor);
    GX_VERIFY_EXIT(emStatus);

    cout<< "m_IsColor:"<<m_IsColor<<endl;

    if (!m_IsColor)
    {
        printf("<This app only support color cameras! App Exit!>\n");
        GXCloseDevice(m_hDevice);
        m_hDevice = NULL;
        GXCloseLib();
        return 0;
    }
    else
    {
        emStatus = GXGetEnum(m_hDevice, GX_ENUM_PIXEL_COLOR_FILTER, &m_ColorFilter);
        GX_VERIFY_EXIT(emStatus);
    }
    //获取单帧图像4
    emStatus = GXGetInt(m_hDevice, GX_INT_PAYLOAD_SIZE, &m_nPayloadSize);
    GX_VERIFY(emStatus);

    //将容器赋值
    ImgQue = &imaQue;

    //设置触发模式 true软触发---false硬出发
    SetTriggerMode(true);

    //关闭自动曝光/增益
    emStatus = GXSetEnum(m_hDevice,GX_ENUM_EXPOSURE_AUTO,GX_EXPOSURE_AUTO_OFF);
    GX_VERIFY_EXIT(emStatus);
    emStatus = GXSetEnum(m_hDevice,GX_ENUM_GAIN_AUTO,GX_GAIN_AUTO_OFF);
    GX_VERIFY_EXIT(emStatus);

    //设置白平衡
    if(m_IsColor)
    {
        //
        emStatus = GXSetEnum(m_hDevice, GX_ENUM_BALANCE_WHITE_AUTO, GX_BALANCE_WHITE_AUTO_CONTINUOUS);
        GX_VERIFY_EXIT(emStatus);

        emStatus = GXSetEnum(m_hDevice, GX_ENUM_ACQUISITION_FRAME_RATE_MODE, GX_ACQUISITION_FRAME_RATE_MODE_OFF);
        GX_VERIFY_EXIT(emStatus);
    }
    //获取最大的增益和曝光值
    emStatus = GXGetFloat(m_hDevice, GX_FLOAT_AUTO_EXPOSURE_TIME_MAX, &m_ExposureMax);
    GX_VERIFY(emStatus);
    emStatus = GXGetFloat(m_hDevice, GX_FLOAT_AUTO_EXPOSURE_TIME_MIN, &m_ExposureMin);
    GX_VERIFY(emStatus);

    emStatus = GXGetFloat(m_hDevice, GX_FLOAT_AUTO_GAIN_MAX, &m_GainMax);
    GX_VERIFY(emStatus);
    emStatus = GXGetFloat(m_hDevice, GX_FLOAT_AUTO_GAIN_MIN, &m_GainMin);
    GX_VERIFY(emStatus);

    SetExposure(Exposure);
    SetGain(Gain);

    //初始化回调处理类
    captureImgHander=new CaptureHander(m_IsColor,m_IsScan,*ImgQue);
    captureImgHander->setCur();
    PreForAcquisition();
    //注册回调函数
    emStatus = GXRegisterCaptureCallback(m_hDevice,&m_ImgGet,captureImgHander->OnFrameCallbackFun);
    GX_VERIFY(emStatus);

    emStatus = GXStreamOn(m_hDevice);
    GX_VERIFY(emStatus);

    emStatus = GXSendCommand(m_hDevice,GX_COMMAND_ACQUISITION_START);
    GX_VERIFY(emStatus);

    return true;
}

bool DhCamera::ConnectCamera(GX_OPEN_PARAM *pOpenParam,std::queue<cv::Mat>& imaQue,float Exposure,float Gain)
{
    //初始化打开设备
    GX_STATUS emStatus = GX_STATUS_SUCCESS;
    uint32_t ui32DeviceNum = 0;

    emStatus = GXUpdateDeviceList(&ui32DeviceNum, 1000);
    if(emStatus != GX_STATUS_SUCCESS)
    {
        GetErrorString(emStatus);
        GXCloseLib();
        return false;
    }
    if(ui32DeviceNum <= 0)
    {
        printf("<No device found>\n");
        GXCloseLib();
        return false;
    }

    emStatus = GXOpenDevice(pOpenParam, &m_hDevice);
    if(emStatus != GX_STATUS_SUCCESS)
    {
        GetErrorString(emStatus);
        GXCloseLib();
        return false;
    }

    //判断相机是否为彩色
    emStatus = GXIsImplemented(m_hDevice, GX_ENUM_PIXEL_COLOR_FILTER, &m_IsColor);
    GX_VERIFY_EXIT(emStatus);

    if (!m_IsColor)
    {
        printf("<This app only support color cameras! App Exit!>\n");
        GXCloseDevice(m_hDevice);
        m_hDevice = NULL;
        GXCloseLib();
        return 0;
    }
    else
    {
        emStatus = GXGetEnum(m_hDevice, GX_ENUM_PIXEL_COLOR_FILTER, &m_ColorFilter);
        GX_VERIFY_EXIT(emStatus);
    }
    //获取单帧图像所需内存
    emStatus = GXGetInt(m_hDevice, GX_INT_PAYLOAD_SIZE, &m_nPayloadSize);
    GX_VERIFY(emStatus);

    //将容器赋值
    ImgQue = &imaQue;

    //设置触发模式 true软触发---false硬出发
    SetTriggerMode(true);

    //关闭自动曝光/增益
    emStatus = GXSetEnum(m_hDevice,GX_ENUM_EXPOSURE_AUTO,GX_EXPOSURE_AUTO_OFF);
    GX_VERIFY_EXIT(emStatus);
    emStatus = GXSetEnum(m_hDevice,GX_ENUM_GAIN_AUTO,GX_GAIN_AUTO_OFF);
    GX_VERIFY_EXIT(emStatus);

    //设置白平衡
    if(m_IsColor)
    {
        emStatus = GXSetEnum(m_hDevice, GX_ENUM_BALANCE_WHITE_AUTO, GX_BALANCE_WHITE_AUTO_OFF);
        GX_VERIFY_EXIT(emStatus);

  //      emStatus = GXSetEnum(m_hDevice, GX_ENUM_COLOR_TRANSFORMATION_MODE, GX_COLOR_CORRECT_ON);
  //      GX_VERIFY_EXIT(emStatus);

       emStatus = GXSetEnum(m_hDevice, GX_ENUM_BALANCE_RATIO_SELECTOR, GX_BALANCE_RATIO_SELECTOR_BLUE);
        GX_VERIFY_EXIT(emStatus);
        emStatus = GXSetFloat(m_hDevice, GX_FLOAT_BALANCE_RATIO, 1.3);
        GX_VERIFY_EXIT(emStatus);
//        emStatus = GXSetEnum(m_hDevice, GX_ENUM_BALANCE_RATIO_SELECTOR, GX_BALANCE_RATIO_SELECTOR_BLUE);
//        GX_VERIFY_EXIT(emStatus);
//        emStatus = GXSetFloat(m_hDevice, GX_FLOAT_BALANCE_RATIO, 1.3);
 //       GX_VERIFY_EXIT(emStatus);

 //       emStatus = GXSetEnum(m_hDevice, GX_ENUM_BALANCE_RATIO_SELECTOR, GX_BALANCE_RATIO_SELECTOR_GREEN);
//        GX_VERIFY_EXIT(emStatus);
 //       emStatus = GXSetFloat(m_hDevice, GX_FLOAT_BALANCE_RATIO, 1.3);
//        GX_VERIFY_EXIT(emStatus);


        emStatus = GXSetEnum(m_hDevice, GX_ENUM_ACQUISITION_FRAME_RATE_MODE, GX_ACQUISITION_FRAME_RATE_MODE_OFF);
        GX_VERIFY_EXIT(emStatus);
    }
    //获取最大的增益和曝光值
    emStatus = GXGetFloat(m_hDevice, GX_FLOAT_AUTO_EXPOSURE_TIME_MAX, &m_ExposureMax);
    GX_VERIFY(emStatus);
    emStatus = GXGetFloat(m_hDevice, GX_FLOAT_AUTO_EXPOSURE_TIME_MIN, &m_ExposureMin);
    GX_VERIFY(emStatus);

    emStatus = GXGetFloat(m_hDevice, GX_FLOAT_AUTO_GAIN_MAX, &m_GainMax);
    GX_VERIFY(emStatus);
    emStatus = GXGetFloat(m_hDevice, GX_FLOAT_AUTO_GAIN_MIN, &m_GainMin);
    GX_VERIFY(emStatus);

    SetExposure(Exposure);
    SetGain(Gain);

    //初始化回调处理类
    captureImgHander=new CaptureHander(m_IsColor,m_IsScan,*ImgQue);
    captureImgHander->setCur();
    PreForAcquisition();
    //注册回调函数
    emStatus = GXRegisterCaptureCallback(m_hDevice,&m_ImgGet,captureImgHander->OnFrameCallbackFun);
    GX_VERIFY(emStatus);

    emStatus = GXStreamOn(m_hDevice);
    GX_VERIFY(emStatus);

    emStatus = GXSendCommand(m_hDevice,GX_COMMAND_ACQUISITION_START);
    GX_VERIFY(emStatus);

    return true;
}


bool DhCamera::GrabAImg(cv::Mat& img,bool imgColor,double timeOut)
{
    GX_STATUS emStatus = GX_STATUS_SUCCESS;
    double Time0,SumTime0;
    captureImgHander->colorCameraOutput = imgColor;

    emStatus = GXSendCommand(m_hDevice, GX_COMMAND_TRIGGER_SOFTWARE);
    GX_VERIFY(emStatus);

    //time(&lInit);
    //cout<<"Time_lInit:"<<lInit<<endl;
    Time0 = static_cast<double>(cv::getTickCount());

    //cout<<"Time_BEGIN:"<<Time0<<endl;
    //cout<<"m_ImgGet"<<m_ImgGet<<endl;
    while(true)
    {
        if(m_ImgGet)
        {
            img = captureImgHander->img.clone();
            m_ImgGet = false;
            captureImgHander->colorCameraOutput= false;
            return true;
        }
        //cout<<"Time_BEGIN:"<<Time1<<endl;
        //double Time1 = (double)cv::getTickCount();
        //cout<<"Time_END:"<<Time1<<endl;
        SumTime0 = ((static_cast<double>(cv::getTickCount()))-Time0) /(cv::getTickFrequency()); //终止时间
        //time(&lEnd);
        //cout<<"Time_lEnd:"<<lEnd<<endl;
        if(SumTime0 >= timeOut)
        {
            captureImgHander->colorCameraOutput= false;
            return false;
        }

    }

    captureImgHander->colorCameraOutput= false;
    return true;
}

bool DhCamera::RegisterCaptuer()
{
    GX_STATUS emStatus = GX_STATUS_SUCCESS;

    emStatus = GXSendCommand(m_hDevice,GX_COMMAND_ACQUISITION_STOP);
    GX_VERIFY(emStatus);

    emStatus = GXStreamOff(m_hDevice);
    GX_VERIFY(emStatus);

    emStatus = GXUnregisterCaptureCallback(m_hDevice);
    GX_VERIFY(emStatus);

    UnPreForAcquisition();

    return true;
}

bool DhCamera::DisConnectCamera()
{
    GX_STATUS emStatus = GX_STATUS_SUCCESS;
    emStatus = GXCloseDevice(m_hDevice);
    if(emStatus != GX_STATUS_SUCCESS)
    {
        GetErrorString(emStatus);
        m_hDevice = NULL;
        GXCloseLib();
        return false;
    }
    return true;
}


bool DhCamera::SetTriggerMode(bool flag)
{
    //将触发模式打开
    GX_STATUS emStatus = GX_STATUS_SUCCESS;
    emStatus = GXSetEnum(m_hDevice, GX_ENUM_TRIGGER_MODE, GX_TRIGGER_MODE_ON);
    GX_VERIFY_EXIT(emStatus);

    if(flag)
    {
        emStatus = GXSetEnum(m_hDevice, GX_ENUM_TRIGGER_SOURCE, GX_TRIGGER_SOURCE_SOFTWARE);
        GX_VERIFY_EXIT(emStatus);

        m_IsScan = false;
        m_IsSourceTrigger = true;


        /*
        emStatus = GXSetEnum(g_hDevice, GX_ENUM_LINE_SELECTOR, GX_ENUM_LINE_SELECTOR_LINE2);
        GX_VERIFY_EXIT(emStatus);

        emStatus = GXSetEnum(g_hDevice, GX_ENUM_LINE_MODE, GX_ENUM_LINE_MODE_OUTPUT);
        GX_VERIFY_EXIT(emStatus);

        emStatus = GXSetEnum(g_hDevice, GX_ENUM_LINE_SOURCE, GX_ENUM_LINE_SOURCE_STROBE);
        GX_VERIFY_EXIT(emStatus);
        */
    }
    else
    {
        emStatus = GXSetEnum(m_hDevice, GX_ENUM_TRIGGER_SOURCE, GX_TRIGGER_SOURCE_LINE2);
        GX_VERIFY_EXIT(emStatus);

        emStatus = GXSetEnum(m_hDevice, GX_ENUM_LINE_SELECTOR, GX_ENUM_LINE_SELECTOR_LINE2);
        GX_VERIFY_EXIT(emStatus);

        emStatus = GXSetEnum(m_hDevice, GX_ENUM_LINE_MODE, GX_ENUM_LINE_MODE_INPUT);
        GX_VERIFY_EXIT(emStatus);

        emStatus = GXSetEnum(m_hDevice, GX_ENUM_LINE_SOURCE, GX_ENUM_LINE_SOURCE_STROBE);
        GX_VERIFY_EXIT(emStatus);

        m_IsScan = true;
        m_IsSourceTrigger = false;
    }
    return true;
}

bool DhCamera::SetExposure(float val)
{
    GX_STATUS emStatus = GX_STATUS_SUCCESS;

    m_ExposureOld = m_Exposure;
    if(val > m_ExposureMax)
    {
        val = m_ExposureMax;
    }
    if(val < m_ExposureMin)
    {
        val = m_ExposureMin;
    }

    emStatus = GXSetFloat(m_hDevice, GX_FLOAT_EXPOSURE_TIME, val);
    if(emStatus != GX_STATUS_SUCCESS)
    {
        m_Exposure = m_ExposureOld;
        GetErrorString(emStatus);
        return false;
    }
    return true;
}

bool DhCamera::SetGain(float val)
{
    GX_STATUS emStatus = GX_STATUS_SUCCESS;

    m_GainOld = m_Gain;
    if(val > m_GainMax)
    {
        val = m_GainMax;
    }
    if(val < m_GainMin)
    {
        val = m_GainMin;
    }

    emStatus = GXSetFloat(m_hDevice, GX_FLOAT_GAIN, val);
    if(emStatus != GX_STATUS_SUCCESS)
    {
        m_Gain = m_GainOld;
        GetErrorString(emStatus);
        return false;
    }
    return true;
}

bool DhCamera::SetFramerate(double val)
{
    GX_STATUS emStatus = GX_STATUS_SUCCESS;

    emStatus=GXSetEnum(m_hDevice,GX_ENUM_ACQUISITION_FRAME_RATE_MODE,GX_ACQUISITION_FRAME_RATE_MODE_OFF);
    GX_VERIFY(emStatus);

    emStatus=GXSetFloat(m_hDevice,GX_FLOAT_ACQUISITION_FRAME_RATE,val);
    GX_VERIFY(emStatus);

    return true;
}

void DhCamera::PreForAcquisition()
{
    captureImgHander->g_pRGBImageBuf = new void* [m_nPayloadSize * 3];
    captureImgHander->g_pMonoImageBuf = new void* [m_nPayloadSize];

    return;
}

void DhCamera::UnPreForAcquisition()
{
    //Release resources
    if (captureImgHander->g_pRGBImageBuf != NULL)
    {
        delete[] (void*)captureImgHander->g_pRGBImageBuf;
        captureImgHander->g_pRGBImageBuf = NULL;
    }
    if (captureImgHander->g_pMonoImageBuf != NULL)
    {
        delete[] (void*)captureImgHander->g_pMonoImageBuf;
        captureImgHander->g_pMonoImageBuf = NULL;
    }

    return;
}



//======================================================================================================================//
void GetErrorString(GX_STATUS emErrorStatus)
{
    char *error_info = NULL;
    size_t size = 0;
    GX_STATUS emStatus = GX_STATUS_SUCCESS;

    // Get length of error description
    emStatus = GXGetLastError(&emErrorStatus, NULL, &size);
    if(emStatus != GX_STATUS_SUCCESS)
    {
        printf("<Error when calling GXGetLastError>\n");
        return;
    }

    // Alloc error resources
    error_info = new char[size];
    if (error_info == NULL)
    {
        printf("<Failed to allocate memory>\n");
        return ;
    }

    // Get error description
    emStatus = GXGetLastError(&emErrorStatus, error_info, &size);
    if (emStatus != GX_STATUS_SUCCESS)
    {
        printf("<Error when calling GXGetLastError>\n");
    }
    else
    {
        printf("%s\n", (char*)error_info);
    }

    // Realease error resources
    if (error_info != NULL)
    {
        delete []error_info;
        error_info = NULL;
    }

}

string get_time()
{
    string time;
    timeval tv;
    gettimeofday(&tv,NULL);

    struct tm* ptm;
    ptm = localtime (&(tv.tv_sec));

    char time_string[40];
    long milliseconds;

    strftime (time_string, sizeof(time_string), "%Y-%m-%d-%H-%M-%S-", ptm);
    milliseconds = tv.tv_usec / 1000;

    time= time_string+to_string(milliseconds);
    return time;
}
void List(const char *path, int level, vector<string> &strvec) \
    {
    struct dirent* ent = NULL;
    DIR *pDir;
    pDir = opendir(path);
    if (pDir == NULL)
    {
        return;
    }
    while (NULL != (ent = readdir(pDir)))
    {
        if (ent->d_type == 0 && ent->d_reclen == 48)
        {
            strvec.push_back(ent->d_name);
        }
    else
    {
            if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
            {
                continue;
            }
            //directory
            string _path(path);
            string _dirName(ent->d_name);
            string fullDirPath = _path + "/" + _dirName;
            List(fullDirPath.c_str(), level + 1, strvec);
        }
    }
}
