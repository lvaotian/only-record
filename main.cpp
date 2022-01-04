#include "control/rm_link.h"
#include<ctime>
int main()
{
#if RECORD == 1
    cv::Mat src_img;
    //RM_VideoCapture* cap=new RM_VideoCapture(1);
    RM_Vision_Init run;
    double sum=0;
    while(true)
    {
        //double t = double(getTickCount());
        clock_t start=std::clock();
        /** run **/
        if(run.cap.isindustryimgInput()){
            src_img = cvarrToMat(run.cap.iplImage,true);//这里只是进行指针转换，将IplImage转换成Mat类型
        }else{
            run.capture >> src_img;
        }
        imshow("src_img",src_img);
        run.Run(src_img);
        run.cap.cameraReleasebuff();
        //t = (double(getTickCount() - t)) / getTickFrequency();
        clock_t end=std::clock();
        double endtime=(double)(end-start)/CLOCKS_PER_SEC;
        sum+=endtime;
        if(sum>=10){
            run.close(src_img);
            sum=sum-10;
        }
#if COUT_FPS == 1
        int fps = int(1.0 / t);
        cout<< endl << "FPS: " << fps<< endl;
#endif

        #if ANALYZE_EACH_FRAME == 1
        if(run.is_continue()){
            continue;
        }
        #endif

        if(run.is_exit()){
            break;
        }
    }

    destroyAllWindows();

    return EXIT_SUCCESS;
#endif
#if RECORD == 2
    RM_Vision_Init run;
    for (;;)
    {
        run.PHOTO_RUN();
        if(run.is_exit()){
            break;
        }
    }
    

#endif
}
