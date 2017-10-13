#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID()
: mErrorP(0.0)
, mErrorI(0.0)
, mErrorD(0.0)
, mHasLastError(false)
, mLastError(0.0)
, mKP(0.2)
, mKI(3.0)
, mKD(0.004)
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
  mHasLastError = false;
  mLastError = 0;
  mKP = KP;
  mKI = KI;
  mKD = KD;
}

#include <iostream>

void PID::UpdateError(double cte)
{
  mErrorP = cte;
  mErrorI += cte;
  mErrorD = mHasLastError ? (cte - mLastError) : 0.0;
  mLastError = cte;
  mHasLastError = true;
  std::cout << "CTE: " << cte << "(" << mErrorP << ", " << mErrorI << ", " << mErrorD << ")" << std::endl;
}

double PID::GetSteering() const
{
  double steer = -mKP * mErrorP - mKI * mErrorI - mKD * mErrorD;
  std::cout << " Steering Value: " << steer << std::endl;
  return steer;
}

