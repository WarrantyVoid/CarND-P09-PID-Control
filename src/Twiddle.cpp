#include "Twiddle.h"
#include "PID.h"
#include <iostream>
#include <math.h>
#include <numeric>
#include <limits>

Twiddle::Twiddle(PID &pid1, PID &pid2, double tolerance)
: mPID1(pid1)
, mPID2(pid2)
, mTolerance(tolerance)
, mNumRuns(0)
, mCurRun(0)
, mParameters()
, mDeltas()
, mCurParameter(0)
, mBestError(std::numeric_limits<double>::max())
, mIsIniRun(true)
, mIsInvRun(false)
{

}


Twiddle::~Twiddle()
{

}

void Twiddle::Init(int numRuns, const TParameters &parameters, const TParameters &deltas)
{
  mNumRuns = numRuns;
  mCurRun = 0;
  mParameters = parameters;
  mDeltas = deltas;
  mCurParameter = 0;
  mBestError = std::numeric_limits<double>::max();
  mIsIniRun = true;
  mIsInvRun = false;
  mPID1.Init(mParameters[0], mParameters[1], mParameters[2]);
  mPID2.Init(1.0, 0, 0);
  mPID2.UpdateError(0.7);
}

ETwiddleResult Twiddle::Update(double cte)
{
  mPID1.UpdateError(cte);
  ++mCurRun;
  if (mNumRuns > 0 && mCurRun >= mNumRuns)
  {
    double error = mPID1.GetMeanSquaredError();
    if (mIsIniRun)
    {
      mBestError = error;
      mIsIniRun = false;
    }
    else if (mIsInvRun)
    {
      if (error < mBestError)
      {
        mBestError = error;
        mDeltas[mCurParameter] *= 1.1;
      }
      else
      {
         mParameters[mCurParameter] += mDeltas[mCurParameter];
         mDeltas[mCurParameter] *= 0.9;
      }
      mIsInvRun = false;
      ++mCurParameter;
    }
    else
    {
      if (error < mBestError)
      {
        mBestError = error;
        mDeltas[mCurParameter] *= 1.1;
        ++mCurParameter;
      }
      else
      {
        mParameters[mCurParameter] -= 2 * mDeltas[mCurParameter];
        mIsInvRun = true;
      }
    }

    mCurRun = 0;
    if (mCurParameter >= mParameters.size())
    {
      mCurParameter = 0;
      if (std::accumulate(mDeltas.begin(), mDeltas.end(), 0.0) <= mTolerance)
      {
        std::cout << "Final twiddle params = ";
        for (TParameters::const_iterator i = mParameters.begin(); i != mParameters.end(); ++i)
        {
          if (i != mParameters.begin())
          {
             std::cout << ", ";
          }
          std::cout << *i;
        }
        std::cout << std::endl;
        return TwiddleFinished;
      }
    }
    std::cout << "Cur twiddle error = " << mBestError << std::endl;
    mParameters[mCurParameter] += mDeltas[mCurParameter];
    mPID1.Init(mParameters[0], mParameters[1], mParameters[2]);
    return RunFinished;
  }
  return None;
}


