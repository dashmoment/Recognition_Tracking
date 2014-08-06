GetLocalEntroyImage( const IplImage*gray_src,IplImage*entopy_image){
    int hist_size[]={256};
float gray_range[]={0,255};
float* ranges[] = { gray_range};
    CvHistogram * hist = cvCreateHist( 1, hist_size, CV_HIST_SPARSE, ranges,1);
    for(int i=0;i<gray_src.width;i++){
            for(int j=0;j<gray_src.height;j++){
                //calculate entropy for pixel(i,j) 
                //1.set roi rect(9*9),handle edge pixel
                CvRect roi;
                int threshold=Max(0,i-4);
                roi.x=threshold;
                threshold=Max(0,j-4);
                roi.y=threshold;
                roi.width=(i-Max(0,i-4))+1+(Min(gray_src->width-1,i+4)-i);
                roi.height=(j-Max(0,j-4))+1+(Min(gray_src->height-1,j+4)-j);
                cvSetImageROI(const_cast<IplImage*>(gray_src),roi);
                IplImage*gray_src_non_const=const_cast<IplImage*>(gray_src);                            

                //2.calHist,here I chose CV_HIST_SPARSE to speed up
                cvCalcHist( &gray_src_non_const, hist, 0, 0 );*/
                cvNormalizeHist(hist,1.0);
                float total=0;
                float entroy=0;

               //3.get entroy
                CvSparseMatIterator it;
                for(CvSparseNode*node=cvInitSparseMatIterator((CvSparseMat*)hist-   >bins,&it);node!=0;node=cvGetNextSparseNode(&it)){
                float gray_frequency=*(float*)CV_NODE_VAL((CvSparseMat*)hist->bins,node);
                entroy=entroy-gray_frequency*(log(gray_frequency)/log(2.0f));//*(log(gray_frequency)/log(2.0))
                }
                ((float*)(local_entroy_image->imageData + j*local_entroy_image->widthStep))[i]=entroy;
                cvReleaseHist(&hist);

            }
        }
        cvResetImageROI(const_cast<IplImage*>(gray_src));
    }