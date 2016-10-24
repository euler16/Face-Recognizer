#ifndef __CLASSIFIER__
#define __CLASSIFIER__


#include <opencv2/opencv.hpp>

using namespace cv;

struct Vectors
{
    int type;
    int dims, count;
    Vectors* next;
    union
    {
        uchar** ptr;
        float** fl;
        double** db;
    } data;
};

float find_nearestCore( const Mat& _samples, int k0, const Range& range,
                          Mat* results, Mat* neighbor_responses,
                          Mat* dists, float* presult ) const
    {
        int testidx, baseidx, i, j, d = samples.cols, nsamples = samples.rows;
        int testcount = range.end - range.start;
        int k = std::min(k0, nsamples);

        AutoBuffer<float> buf(testcount*k*2);
        float* dbuf = buf;
        float* rbuf = dbuf + testcount*k;

        const float* rptr = responses.ptr<float>();

        for( testidx = 0; testidx < testcount; testidx++ )
        {
            for( i = 0; i < k; i++ )
            {
                dbuf[testidx*k + i] = FLT_MAX;
                rbuf[testidx*k + i] = 0.f;
            }
        }

        for( baseidx = 0; baseidx < nsamples; baseidx++ )
        {
            for( testidx = 0; testidx < testcount; testidx++ )
            {
                const float* v = samples.ptr<float>(baseidx);
                const float* u = _samples.ptr<float>(testidx + range.start);

                float s = 0;
                for( i = 0; i <= d - 4; i += 4 )
                {
                    float t0 = u[i] - v[i], t1 = u[i+1] - v[i+1];
                    float t2 = u[i+2] - v[i+2], t3 = u[i+3] - v[i+3];
                    s += t0*t0 + t1*t1 + t2*t2 + t3*t3;
                }

                for( ; i < d; i++ )
                {
                    float t0 = u[i] - v[i];
                    s += t0*t0;
                }

                Cv32suf si;
                si.f = (float)s;
                Cv32suf* dd = (Cv32suf*)(&dbuf[testidx*k]);
                float* nr = &rbuf[testidx*k];

                for( i = k; i > 0; i-- )
                    if( si.i >= dd[i-1].i )
                        break;
                if( i >= k )
                    continue;

                for( j = k-2; j >= i; j-- )
                {
                    dd[j+1].i = dd[j].i;
                    nr[j+1] = nr[j];
                }
                dd[i].i = si.i;
                nr[i] = rptr[baseidx];
            }
        }

        float result = 0.f;
        float inv_scale = 1.f/k;

        for( testidx = 0; testidx < testcount; testidx++ )
        {
            if( neighbor_responses )
            {
                float* nr = neighbor_responses->ptr<float>(testidx + range.start);
                for( j = 0; j < k; j++ )
                    nr[j] = rbuf[testidx*k + j];
                for( ; j < k0; j++ )
                    nr[j] = 0.f;
            }

            if( dists )
            {
                float* dptr = dists->ptr<float>(testidx + range.start);
                for( j = 0; j < k; j++ )
                    dptr[j] = dbuf[testidx*k + j];
                for( ; j < k0; j++ )
                    dptr[j] = 0.f;
            }

            if( results || testidx+range.start == 0 )
            {
                if( !isclassifier || k == 1 )
                {
                    float s = 0.f;
                    for( j = 0; j < k; j++ )
                        s += rbuf[testidx*k + j];
                    result = (float)(s*inv_scale);
                }
                else
                {
                    float* rp = rbuf + testidx*k;
                    for( j = k-1; j > 0; j-- )
                    {
                        bool swap_fl = false;
                        for( i = 0; i < j; i++ )
                        {
                            if( rp[i] > rp[i+1] )
                            {
                                std::swap(rp[i], rp[i+1]);
                                swap_fl = true;
                            }
                        }
                        if( !swap_fl )
                            break;
                    }

                    result = rp[0];
                    int prev_start = 0;
                    int best_count = 0;
                    for( j = 1; j <= k; j++ )
                    {
                        if( j == k || rp[j] != rp[j-1] )
                        {
                            int count = j - prev_start;
                            if( best_count < count )
                            {
                                best_count = count;
                                result = rp[j-1];
                            }
                            prev_start = j;
                        }
                    }
                }
                if( results )
                    results->at<float>(testidx + range.start) = result;
                if( presult && testidx+range.start == 0 )
                    *presult = result;
            }
}


  struct find_nearest_Invoker
    {
        find_nearest_Invoker( int _k, const Mat& __samples,
                            Mat* __results, Mat* __neighbor_responses, Mat* __dists, float* _presult)
        {
            p = _p;
            k = _k;
            _samples = &__samples;
            _results = __results;
            _neighbor_responses = __neighbor_responses;
            _dists = __dists;
            presult = _presult;
        }

        void operator()( const Range& range ) const
        {
            int delta = std::min(range.end - range.start, 256);
            for( int start = range.start; start < range.end; start += delta )
            {
                p->find_nearestCore( *_samples, k, Range(start, std::min(start + delta, range.end)),
                                    _results, _neighbor_responses, _dists, presult );
            }
        }

        const BruteForceImpl* p;
        int k;
        const Mat* _samples;
        Mat* _results;
        Mat* _neighbor_responses;
        Mat* _dists;
        float* presult;
    };


float find_nearest( InputArray _samples, int k,
                       OutputArray _results,
                       OutputArray _neighborResponses,
                       OutputArray _dists ) const
    {
        float result = 0.f;
        CV_Assert( 0 < k );

        Mat test_samples = _samples.getMat();
        CV_Assert( test_samples.type() == CV_32F && test_samples.cols == samples.cols );
        int testcount = test_samples.rows;

        if( testcount == 0 )
        {
            _results.release();
            _neighborResponses.release();
            _dists.release();
            return 0.f;
        }

        Mat res, nr, d, *pres = 0, *pnr = 0, *pd = 0;
        if( _results.needed() )
        {
            _results.create(testcount, 1, CV_32F);
            pres = &(res = _results.getMat());
        }
        if( _neighborResponses.needed() )
        {
            _neighborResponses.create(testcount, k, CV_32F);
            pnr = &(nr = _neighborResponses.getMat());
        }
        if( _dists.needed() )
        {
            _dists.create(testcount, k, CV_32F);
            pd = &(d = _dists.getMat());
        }

        find_nearest_Invoker invoker(this, k, test_samples, pres, pnr, pd, &result);
        parallel_for_(Range(0, testcount), invoker);
        //invoker(Range(0, testcount));
        return result;
    }
};


class CV_EXPORTS_W KNearest : public CvStatModel
{
public:

    CV_WRAP KNearest();
    virtual ~KNearest();

    KNearest( const CvMat* trainData, const CvMat* responses,
                const CvMat* sampleIdx=0, bool isRegression=false, int max_k=32 );

    virtual bool train( const CvMat* trainData, const CvMat* responses,
                        const CvMat* sampleIdx=0, bool is_regression=false,
                        int maxK=32, bool updateBase=false );

    virtual float find_nearest( const CvMat* samples, int k, CV_OUT CvMat* results=0,
        const float** neighbors=0, CV_OUT CvMat* neighborResponses=0, CV_OUT CvMat* dist=0 ) const;

    CV_WRAP KNearest( const cv::Mat& trainData, const cv::Mat& responses,
               const cv::Mat& sampleIdx=cv::Mat(), bool isRegression=false, int max_k=32 );

    CV_WRAP virtual bool train( const cv::Mat& trainData, const cv::Mat& responses,
                       const cv::Mat& sampleIdx=cv::Mat(), bool isRegression=false,
                       int maxK=32, bool updateBase=false );

    float find_nearest( InputArray samples, int k,
                       OutputArray results,
                       OutputArray neighborResponses=noArray(),
                       OutputArray dist=noArray() ) const
    {
        return find_nearest(samples, k, results, neighborResponses, dist);
}

   	void find_neighbors_direct( const CvMat* _samples, int k, int start, int end,
        float* neighbor_responses, const float** neighbors, float* dist ) const;

   	float predict(InputArray inputs, OutputArray outputs, int) const
    {
        return impl->find_nearest( inputs, impl->defaultK, outputs, noArray(), noArray() );
	}

	void read( const FileNode& fn )
    {
        int algorithmType = BRUTE_FORCE;
        if (fn.name() == NAME_KDTREE)
            algorithmType = KDTREE;
        initImpl(algorithmType);
        impl->read(fn);
    }

protected:

    int max_k, var_count;
    int total;
    bool regression;
    CvVectors* samples;
};