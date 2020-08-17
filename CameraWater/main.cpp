#include <iostream>
#include <dcamera.h>
#include <xmlreader.h>
#include <XMLWriter.h>
#include <string.h>
#include <gpioset.h>
#include <unistd.h>

using namespace std;
int scanFiles(vector<string> &fileList, string inputDirectory);
std::string filename = "/home/nvidia/config.xml";
std::string filenameImg = "/home/nvidia/config_imgSize.xml";

std::string inputDirectory = "/media/nvidia";

//float imgSize = 36.8;


int main()
{
    gpio_set_dir(246,"out");
    gpio_set_value(246,0);
    //Windows close time
    sleep(2);

    string CamIndex;
    float shutter = 0;
    float gain = 0;
    int CamWaitTime = 0;
    int OnceImgSize = 0;

    int imgSize = 0;
    XMLReader::ReadCamParams(filename,CamIndex,shutter,gain,CamWaitTime,OnceImgSize);
    shutter = shutter*10000;
    XMLReader::ReadImgSize(filenameImg, imgSize);
    cout<<"Now img can save: "<<imgSize << endl;
    if(imgSize <= OnceImgSize){
        cout << "Memory is full!!!"<<endl;
        system("poweroff");

        return 0;
    }
    int imgNowSize = imgSize - OnceImgSize;
    XMLWriter::WriteLaserSystemConfig(filenameImg, imgNowSize);
    //XMLWriter::WriteLaserSystemConfig(filenameImg,  );
    //XMLReader::ReadImgSize(filenameImg,  );


    GX_OPEN_PARAM CAM;
    CAM.accessMode = GX_ACCESS_EXCLUSIVE;
    CAM.openMode   = GX_OPEN_SN;
    char* c = const_cast<char *>(CamIndex.c_str());
    CAM.pszContent = c;

    DhCamera cam;
    std::queue<cv::Mat> imaQue;
    if(!cam.ConnectCamera(&CAM,imaQue,shutter,gain)){
        cout<<"Camera initial error!"<<endl;
        return 0;
    }

    cv::Mat imgTemp;
    vector<string> fileList;
    int Num123 = scanFiles(fileList,inputDirectory);
    if(Num123 != 1){
        cout<< "SD size error!"<<endl;
        return 0;
    }

    int Nsize = OnceImgSize;
    string nameA = inputDirectory + "/" + fileList[0]+ "/";
    string getTime;
    while(Nsize--){
        //GPIO Light
        gpio_set_value(246,1);
        usleep(100);
        cam.GrabAImg(imgTemp,1);

        getTime = get_time();
        cout<< getTime << endl;
        imwrite(nameA + getTime + ".bmp",imgTemp);
        gpio_set_value(246,0);

        sleep(CamWaitTime);
    }
    cout << "Work has done!!!" << endl;
    system("poweroff");

    return 0;
}


int scanFiles(vector<string> &fileList, string inputDirectory)
{
    inputDirectory = inputDirectory.append("/");

    DIR *p_dir;
    const char* str = inputDirectory.c_str();

    p_dir = opendir(str);
    if( p_dir == NULL)
    {
        cout<< "can't open :" << inputDirectory << endl;
    }

    struct dirent *p_dirent;

    while ( p_dirent = readdir(p_dir))
    {
        string tmpFileName = p_dirent->d_name;
        if( tmpFileName == "." || tmpFileName == "..")
        {
            continue;
        }
        else
        {
            fileList.push_back(tmpFileName);
        }
    }
    closedir(p_dir);
    return fileList.size();
}
