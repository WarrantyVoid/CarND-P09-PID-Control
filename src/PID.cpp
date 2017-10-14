#include "PID.h"
#include <iostream>
#include <math.h>

PID::PID()
: mErrorP(0.0)
, mErrorI(0.0)
, mErrorD(0.0)
, mNumUpdates(0)
, mLastError(0.0)
, mTotalError(0.0)
, mKP(0.2)
, mKI(3.0)
, mKD(0.004)
, mControl(0.0)
{

}


PID::~PID()
{

}


void PID::Init(double KP, double KI, double KD)
{
  mErrorP= 0.0;
  mErrorI = 0.0;
  mErrorD = 0.0;
  mNumUpdates = 0;
  mLastError = 0.0;
  mTotalError = 0.0;
  mKP = KP;
  mKI = KI;
  mKD = KD;
  mControl = 0.0;
}


void PID::UpdateError(double cte)
{
  mErrorP = cte;
  mErrorI += cte;
  mErrorD = mNumUpdates > 0 ? (cte - mLastError) : 0.0;
  mLastError = cte;
  ++mNumUpdates;
  mTotalError += pow(cte, 2);
  mControl = -mKP * mErrorP - mKI * mErrorI - mKD * mErrorD;
  mTotalError += 0.5 * pow(mControl, 2);
  //std::cout << "CTE: " << cte << "(" << mErrorP << ", " << mErrorI << ", " << mErrorD << ")" << std::endl;
}


double PID::GetMeanSquaredError() const
{
  return mTotalError / mNumUpdates;
}


double PID::GetControl() const
{
  //std::cout << " Control Value: " << mControl << std::endl;
  return mControl;
}

