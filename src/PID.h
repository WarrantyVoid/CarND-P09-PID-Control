#ifndef PID_H
#define PID_H

class PID
{
public:
  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();


public:
  /*
  * Initialize PID.
  */
  void Init(double KP, double KI, double KD);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the mean squared PID error.
  */
  double GetMeanSquaredError() const;

  /*
  * Calculate the control value.
  */
  double GetControl() const;

private:
  double mErrorP;
  double mErrorI;
  double mErrorD;
  int mNumUpdates;
  double mLastError;
  double mTotalError;
  double mKP;
  double mKI;
  double mKD;
  double mControl;
};

#endif /* PID_H */
