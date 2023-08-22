#ifndef TEXTUREBLEND2_FUNCTION_H
#define TEXTUREBLEND2_FUNCTION_H

#endif //TEXTUREBLEND2_FUNCTION_H
#include<map>
//#include<bits/stdc++.h>
#include <vector>
#include <queue>
#include <GLES3/gl3.h>
#define  NativeBridge_TAG  "NativeBridge"
#define  Bridge_LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,NativeBridge_TAG,__VA_ARGS__)
#define Pos(i, j) (i * width + j)
#define MAXAREA 500
#define HIGHLIGHT 200
using  namespace std;


struct m_queue
{
    int *m_vec;
    int cnt;
    int head, tail;
    void init(int sz)
    {
        m_vec = new int[sz + 2];
        cnt = 0, head = 0, tail = 0;
    }
    ~m_queue()
    {
        delete(m_vec);
    }
    void push(int val)
    {
        m_vec[tail++] = val;
        ++cnt;
    }
    bool empty()
    {
        return cnt == 0;
    }
    int pop()
    {
        if (cnt == 0)return -1;
        --cnt;
        return m_vec[head++];
    }
};

struct starInfo
{
    GLfloat *posArray;
    int cnt;
    starInfo()
    {
        posArray = NULL;
        cnt = 0;
    }
};

struct ImagestarPos
{
    vector< vector<int> > blockInfo;//图像连通块信息
    int *mask;
    GLubyte *pixels;
    starInfo starPos;
    int width, height;
    float k = 0.01;
    int offset[8][2] = { -1, 0, 0, -1, 1, 0, 0, 1, -1, -1, +1, -1, -1, +1, +1, +1 };
    //inline int Pos(const int i, const int j) { return i * width + j; }

    float init(float strength, unsigned char * data, int w, int h, bool yuv = false)//threshold可以是经验值
    {
        //strength = strength * float(0.01);
        clock_t start = clock(), finish;
        //free(starPos.posArray);
        int ret = 0;
        if (starPos.posArray)delete(starPos.posArray);
        starPos.cnt = 0;
        width = w, height = h;
        blockInfo.clear();
        int xstep, ystep;
        if (width > height)
        {
            xstep = width / 256, ystep = height / 192;
        }
        else
        {
            xstep = width / 192, ystep = height / 256;
        }
        width = width / xstep, height = height / ystep;
        mask = (int *)malloc(sizeof(int)*width*height + 10);
        if (!yuv)
        {
            pixels = data;

            for (int i = 0; i < height; ++i)
                for (int j = 0; j < width; ++j)
                {
                    bool f = false;
                    int p = (i * ystep +  (ystep >> 1))* w + j * xstep + (xstep >> 1);
                    int lightness = int(pixels[p * 4] * 0.299 + pixels[p * 4 + 1] * 0.587 + pixels[p * 4 + 2] * 0.114);
                    f |= (lightness > HIGHLIGHT);//220 高光部分的经验值

                    p = (i * ystep + (ystep >> 2)) * w + j * xstep + (xstep >> 2);
                    lightness = int(pixels[p * 4] * 0.299 + pixels[p * 4 + 1] * 0.587 + pixels[p * 4 + 2] * 0.114);
                    f |= (lightness > HIGHLIGHT);

                    p = (i * ystep + (ystep >> 2) * 3) * w + j * xstep + (xstep >> 2);
                    lightness = int(pixels[p * 4] * 0.299 + pixels[p * 4 + 1] * 0.587 + pixels[p * 4 + 2] * 0.114);
                    f |= (lightness > HIGHLIGHT);

                    p = (i * ystep + (ystep >> 2)) * w + j * xstep + (xstep >> 2) * 3;
                    lightness = int(pixels[p * 4] * 0.299 + pixels[p * 4 + 1] * 0.587 + pixels[p * 4 + 2] * 0.114);
                    f |= (lightness > HIGHLIGHT);

                    p = (i * ystep + (ystep >> 2) * 3) * w + j * xstep + (xstep >> 2) * 3;
                    lightness = int(pixels[p * 4] * 0.299 + pixels[p * 4 + 1] * 0.587 + pixels[p * 4 + 2] * 0.114);
                    f |= (lightness > HIGHLIGHT);

                    mask[Pos(i, j)] = int(f);
                }
        }
        else
        {
            for (int i = 0; i < height; ++i)
                for (int j = 0; j < width; ++j)
                {
                    int p = i * xstep * w + j * ystep;
                    mask[Pos(i,j)] = int(data[p] > 220);
                }
        }

        for (int i = 0; i < height; ++i)
            for (int j = 0; j < width; ++j)
            {
                if (mask[Pos(i, j)] ^ 1)continue;
                blockInfo.push_back(vector<int>());
                vector<int> &vv = blockInfo[blockInfo.size() - 1];
                vv.reserve((MAXAREA + 1) << 1);
                m_queue q;
                q.init(width * height);
                int x = i, y = j;
                q.push(x), q.push(y);
                vv.push_back(x), vv.push_back(y);
                mask[Pos(x, y)] = -1;
                while (!q.empty())
                {
                    x = q.pop(); y = q.pop();
                    //printf("%d %d\n", x, y);
                    for (int i = 0; i < 8; ++i)//八连通
                    {
                        int xx = x + offset[i][0], yy = y + offset[i][1];
                        if (0 <= xx && xx < height && 0 <= yy && yy < width && (mask[Pos(xx, yy)] == 1))
                        {
                            mask[Pos(xx, yy)] = -1;
                            q.push(xx), q.push(yy);
                            if(vv.size() <= (MAXAREA << 1))vv.push_back(xx), vv.push_back(yy);
                        }
                    }
                }
                if (vv.size() >(MAXAREA<<1))blockInfo.pop_back();
            }
        for (auto it : blockInfo)
        {
            //starPos.cnt += int(it.size()* strength * k + min(strength * it.size(), float(1.0)));
            starPos.cnt += int(it.size() * strength * k + min(float(0.15) * it.size() * strength, float(1.0)));
        }
        starPos.posArray = new GLfloat[2 * starPos.cnt];
        int p = 0;
        for (auto it : blockInfo)
        {
            //for (int i = 0, c = int(it.size() * strength * k + min(strength * it.size(), float(1.0))); i < c; ++i)
            for (int i = 0, c = int(it.size() * strength * k + min(float(0.15) * it.size() * strength  , float(1.0))); i < c; ++i)
            {
                int temp = rand() % (it.size() / 2);
                starPos.posArray[p * 2] = (GLfloat)(1.0 * it[temp * 2 + 1] / width * 2 - 1.0);
                starPos.posArray[p * 2 + 1] = -(GLfloat)(1.0 * it[temp * 2] / height * 2 - 1.0);
                ++p;
            }
        }
        free(mask);
        finish = clock();
        return float(finish - start) / 1000.0;
    }
};
