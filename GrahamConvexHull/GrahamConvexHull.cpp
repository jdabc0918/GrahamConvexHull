// GrahamConvexHull.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"

//http://i-health.u-aizu.ac.jp/CompuGeo/2013/handouts/chapter3/Chapter3H.pdf
void GrahamConvexHull(vector<vector<Point>> _contours,vector<vector<Point>> &_convexhulls)
{
    typedef struct ContourPoint
    {
        Point p;
        double rad;
        double len; //p0-p�Ԃ̋���
        bool operator<(const ContourPoint& right) const{
            return rad < right.rad;
        }
    };

    //������
    _convexhulls.clear();   //���ʂ̏�����
    vector<vector<ContourPoint>> Contours;
    int numOfContour = (int)_contours.size();

    for (int i = 0; i < numOfContour; i++)
    {
        int N = (int)_contours[i].size();
        vector<ContourPoint> vecCont;
        for (int j = 0; j < N; j++)
        {
            Point p = _contours[i][j];
            ContourPoint cont = { p, 0.0, 0.0 };
            vecCont.push_back(cont);
        }
        Contours.push_back(vecCont);
    }
    double e = 0.000001;    //�덷������ȉ��Ȃ瓯���Ɣ���

    //���O�����F������̗֊s�́A�[���������c���ēr���̓_���폜����
    for (int i = 0; i < numOfContour; i++)
    {
        vector<ContourPoint>::iterator ppIt = Contours[i].begin();
        vector<ContourPoint>::iterator pIt = Contours[i].begin();
        pIt++;
        vector<ContourPoint>::iterator it = Contours[i].begin();
        it++;
        it++;
        
        while (1)
        {
            Point vec0 = (*pIt).p - (*ppIt).p;
            Point vec1 = (*it).p - (*pIt).p;
            if (fabs(vec0.cross(vec1)) < e)  //���������Ȃ�(sin��==0)
            {
                //�^�񒆂�����
                pIt = Contours[i].erase(pIt);
            }
            else
            {
                //��
                ppIt++;
                pIt++;
                it++;
            }

            if (it == Contours[i].end())   //�Ō�̓_�������ʈ���
            {
                vec0 = (*it).p - (*pIt).p;
                vec1 = Contours[i][0].p - (*it).p;
                if (fabs(vec0.cross(vec1)) < e)  //���������Ȃ�(sin��==0)
                {
                    //�Ō�̓_������
                    Contours[i].pop_back();
                }
                break;
            }
        }
    }

    //���[�v
    for (int i = 0; i < numOfContour; i++)
    {
        
        vector<ContourPoint> cont = Contours[i];
        int N = (int)cont.size();
        
        //Step1. �ŏ���y���W�����_p0��������
        ContourPoint p0 = { Point(0, INT_MAX), 0.0, 0.0 };
        for (int j = 0; j < N; j++)
        {
            if (p0.p.y > cont[j].p.y)
            {
                p0 = cont[j];
            }
        }

        //Step2. ���̓_��p0�Ƃ̕Ίp�̏����ɕ��ёւ�
        for (int j = 0; j < N; j++) //rad��len���v�Z
        {
            Point p0pn = cont[j].p - p0.p;            
            Point base = { 1, 0 };

            cont[j].len = (double)sqrt(p0pn.x * p0pn.x + p0pn.y * p0pn.y);
            if (cont[j].len == 0) cont[j].rad = 0.0;
            else{
                cont[j].rad = (double)acos(base.dot(p0pn) / cont[j].len);
            }
        }
        sort(cont.begin(), cont.end()); //�\�[�g

        //vector<ContourPoint>::iterator prevIt;
        //for (vector<ContourPoint>::iterator it = cont.begin(); it < cont.end(); it++) //���łɊԂ̓_������
        //{
        //    if (it == cont.begin())
        //    {
        //        it++;
        //    }
        //    else
        //    {
        //        if (fabs((*it).rad - (*prevIt).rad) < e)   //�����Ίp�̓_�͉��������c��
        //        {
        //            if ((*it).len > (*prevIt).len)
        //            {
        //                it = cont.erase(prevIt);
        //            }
        //            else
        //            {
        //                it = cont.erase(it);
        //            }
        //            it--;
        //        }
        //    }
        //    prevIt = it;
        //}
        //N = (int)cont.size();   //�_�����ς�����̂ōX�V

        //Step.3 �X�^�b�N��p0,p1������
        vector<Point> S; //�X�^�b�NS
        S.push_back(p0.p);        //p0
        S.push_back(cont[1].p);   //p1
        
        //Step4. ���[�v
        for (int j = 2; j < N; j++)
        {
            int SSize = (int)S.size();
            Point cp = cont[j].p;
            Point top0 = S[SSize - 1];   //top
            Point top1 = S[SSize - 2];   //top-1
            double cw_ccw = (top0 - top1).cross((cp - top1));   //���v���>0,�����v���<0

            while (cw_ccw <= 0)
            {
                S.pop_back();
                SSize = (int)S.size();
                top0 = S[SSize - 1];
                top1 = S[SSize - 2];
                cw_ccw = (top0 - top1).cross((cp - top1));
            }
            S.push_back(cp);
        }

        //���ʂ̊i�[
        _convexhulls.push_back(S);
    }
}

int main(int argc, char **argv)
{
    Mat img = imread("C:\\Users\\Yosuke\\Desktop\\test2.bmp",0);
    Mat cImg;
    cvtColor(img, cImg, CV_GRAY2RGB);
    vector<vector<Point>> contours;

    findContours(img, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE);
    //drawContours(cImg, contours, 1, Scalar(0, 0, 255), 2);

    vector<vector<Point>> convexhulls;
    GrahamConvexHull(contours, convexhulls);

    for (int i = 0; i < (int)convexhulls[0].size(); i++)
    //{
    //    cout << "i=" << i << endl;
    //    int x = convexhulls[0][i].x;
    //    int y = convexhulls[0][i].y;
    //    //cImg.at<Vec3b>(y, x) = Vec3b(0, 0, 255);
    //    circle(cImg, Point(x, y), 3, Scalar(0, 0, 255), -1);
    //    imshow("hoge", cImg);
    //    waitKey();
    //}

    for (int i = 0; i < (int)convexhulls.size(); i++)
    {
        for (int j = 0; j < (int)convexhulls[i].size(); j++)
        {
            if (j == 0)
            {
                line(cImg, convexhulls[i][convexhulls[i].size()-1], convexhulls[i][j], Scalar(0, 255, 0), 2);
            }
            else
            {
                line(cImg, convexhulls[i][j - 1], convexhulls[i][j], Scalar(0, 255, 0), 2);                
            }
        }
    }
    for (int i = 0; i < (int)convexhulls.size(); i++)
    {
        for (int j = 0; j < (int)convexhulls[i].size(); j++)
        {
            circle(cImg, convexhulls[i][j], 4, Scalar(0, 0, 255), -1);
        }
    }
    imshow("cImg", cImg);
    waitKey();

	return 0;
}

