// GrahamConvexHull.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"

//http://i-health.u-aizu.ac.jp/CompuGeo/2013/handouts/chapter3/Chapter3H.pdf
void GrahamConvexHull(vector<vector<Point>> _contours,vector<vector<Point>> &_convexhulls)
{
    typedef struct ContourPoint
    {
        Point p;
        double rad;
        double len; //p0-p間の距離
        bool operator<(const ContourPoint& right) const{
            return rad < right.rad;
        }
    };

    //初期化
    _convexhulls.clear();   //結果の初期化
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
    double e = 0.000001;    //誤差がこれ以下なら同じと判定

    //ループ
    for (int i = 0; i < numOfContour; i++)
    {
        vector<ContourPoint> cont = Contours[i];
        int N = (int)cont.size(); 
        
        //Step1. 最小のy座標を持つ点p0を見つける
        ContourPoint p0 = { Point(0, INT_MAX), 0.0, 0.0 };
        for (int j = 0; j < N; j++)
        {
            if (p0.p.y > cont[j].p.y)
            {
                p0 = cont[j];
            }
        }

        //Step2. 他の点とp0との偏角の昇順に並び替え
        for (int j = 0; j < N; j++) //radとlenを計算
        {
            Point p0pn = cont[j].p - p0.p;            
            Point base = { 1, 0 };

            cont[j].len = (double)sqrt(p0pn.x * p0pn.x + p0pn.y * p0pn.y);
            if (cont[j].len == 0) cont[j].rad = 0.0;
            else{
                cont[j].rad = (double)acos(base.dot(p0pn) / cont[j].len);
            }
        }

        sort(cont.begin(), cont.end()); //ソート

        vector<ContourPoint>::iterator prevIt;
        for (vector<ContourPoint>::iterator it = cont.begin(); it < cont.end(); it++) //ついでに間の点を除去
        {
            if (it == cont.begin())
            {
                it++;
            }
            else
            {
                if (fabs((*it).rad - (*prevIt).rad) < e)   //同じ偏角の点は遠い方を残す
                {
                    if ((*it).len > (*prevIt).len)
                    {
                        it = cont.erase(prevIt);
                    }
                    else
                    {
                        it = cont.erase(it);
                    }
                    it--;
                }
            }
            prevIt = it;
        }
        N = (int)cont.size();   //点数が変わったので更新
        for (int j = 0; j < N; j++)
        {
            cout << j << ":" << cont[j].p << " rad:" << cont[j].rad << " len:" << cont[j].len << endl;
        }

        //Step.3 スタックにp0,p1を入れる
        vector<Point> S; //スタックS
        S.push_back(p0.p);        //p0
        S.push_back(cont[1].p);   //p1
        
        //Step4. ループ
        for (int j = 2; j < N; j++)
        {
            cout << "j=" << j << endl;
            int SSize = (int)S.size();
            Point cp = cont[j].p;
            Point top0 = S[SSize - 1];   //top
            Point top1 = S[SSize - 2];   //top-1
            double cw_ccw = (top0 - top1).cross((cp - top1));   //時計回り>0,反時計回り<0

            while (cw_ccw < 0)
            {
                S.pop_back();
                SSize = (int)S.size();
                top0 = S[SSize - 1];
                top1 = S[SSize - 2];
                cw_ccw = (top0 - top1).cross((cp - top1));

            }
            S.push_back(cp);
        }

        //結果の格納
        _convexhulls.push_back(S);
        //for (int j = 0; j < (int)S.size(); j++)
        //{
        //    cout << "r" << j << ":" << S[j] << endl;
        //}
        
    }
}

int main(int argc, char **argv)
{
    Mat img = imread("C:\\Users\\Yosuke\\Desktop\\test2.bmp",0);
    Mat cImg;
    cvtColor(img, cImg, CV_GRAY2RGB);
    vector<vector<Point>> contours;

    findContours(img, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
    //drawContours(cImg, contours, 1, Scalar(0, 0, 255), 2);

    vector<vector<Point>> convexhulls;
    GrahamConvexHull(contours, convexhulls);
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
    imshow("cImg", cImg);
    waitKey();

	return 0;
}

